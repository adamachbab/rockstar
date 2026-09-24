# rockstar

A Windows x64 kernel-mode research driver exploring low-level paging manipulation techniques: **per-core PTE remapping** and **shadow page table injection**. Built as a manual-map payload with a custom entry point, zero CRT dependency, and dynamic kernel symbol resolution.

> ⚠️ **Educational / Research only.** This project is intended for learning Windows kernel internals, memory management, and the x64 paging architecture. Do not use it for anything that violates software terms of service or applicable laws.

---

## Overview

`rockstar` is a KMDF driver project designed to be **manual-mapped** (no `DriverEntry`, no device object, no service registration). It receives a symbol table and metadata from an external loader through a custom `entry` function and initializes two independent paging primitives for arbitrary physical/virtual memory access.

### Key characteristics

- **Custom entry point** (`entry`) instead of `DriverEntry` — designed for reflective loading.
- **No CRT, no imports** — a full `std::`-style runtime is implemented in `runtime/`.
- **Dynamic kernel API resolution** — every ntoskrnl function is called through a pointer resolved from PDB symbols by the loader and passed in as `entry_t::m_pdb`.
- **Two independent paging primitives** that can be used together or separately.
- **DPC-level synchronization** for TLB and PTE atomicity.

---

## Architecture

```
driver/
├── entry.cpp                       # entry point (receives entry_t*)
├── includes.hpp                    # umbrella include
│
├── runtime/                        # CRT-less runtime
│   ├── intrinsics.hpp              # MSVC intrinsics wrapper (intrin::)
│   ├── runtime.hpp
│   └── std/
│       ├── types.hpp               # fixed-width types, uint128_t, traits
│       ├── memory.hpp              # mem_copy/set/move/compare/hash + bit ops
│       ├── string.hpp              # str/wstr ops, int↔str conversion
│       └── algorithm.hpp           # min/max/sort/find/binary_search/...
│
├── platform/                       # platform definitions
│   ├── platform.hpp
│   ├── nt/
│   │   ├── constants.hpp           # POOL_TYPE, PAGE_*, IRQL levels, ...
│   │   ├── status.hpp              # NTSTATUS constants + helpers
│   │   └── structures.hpp          # EPROCESS-adjacent, PTE/PDE/..., MDL, IRP
│   └── pe/
│       └── headers.hpp             # DOS/NT/section/export/import/reloc/debug
│
├── kernel/                         # kernel API layer
│   ├── kernel.hpp
│   ├── symbols/
│   │   ├── symbols.hpp             # symbol table struct + call<fn_t>() helper
│   │   └── symbols.cpp
│   └── api/                        # namespaced wrappers around ntoskrnl
│       ├── dbg.hpp                 # DbgPrintEx, filter state
│       ├── ex.hpp                  # pool, handle table, push locks, resources
│       ├── io.hpp                  # IoCreateDevice, MDL, IRP
│       ├── kdp.hpp                 # KdpTrap/Report/Stub
│       ├── ke.hpp                  # IRQL, DPC, TLB, IPI, sync objects
│       ├── ki.hpp                  # KiSystemCall64, service table
│       ├── mm.hpp                  # Mm*, Mi* (paging internals)
│       ├── ob.hpp                  # object manager
│       ├── ps.hpp                  # process/thread + notify routines
│       ├── rtl.hpp                 # Rtl*, AVL tables, CRT-in-kernel
│       ├── zw.hpp                  # Zw* system services
│       └── misc.hpp                # HalPrivateDispatchTable, CI, PiDDB
│
└── core/                           # feature implementations
    ├── log/
    │   └── log.hpp                 # levelled logger + hex dump
    └── paging/
        ├── paging.hpp              # 4-level page walker, VA↔PA helpers
        ├── pte_remap.{hpp,cpp}     # per-core PTE remapping primitive
        └── shadow_pt.{hpp,cpp}     # shadow PML4 slot + PDPT/PD/PT
```

---

## Components

### 1. Runtime (`runtime/`)

A minimal freestanding replacement for the STL / CRT, safe to use at any IRQL:

- **`std::mem_copy/move/set/compare/zero`** — 8-byte-at-a-time optimized versions.
- **`std::uint128_t` / `int128_t`** — with full arithmetic and shift operators.
- **String utilities** — length, compare, hash (FNV-1a), int↔str conversion, hex formatting.
- **Algorithms** — `min_of`, `max_of`, `clamp`, `sort` (quicksort with insertion fallback), `binary_search`, `lower_bound`, etc.
- **`intrin::`** namespace — clean wrappers for `_Interlocked*`, `_mm_pause`, `__invlpg`, MSR/CR reads, `__cpuid`, etc.

### 2. Kernel symbols (`kernel/symbols/`)

The driver **does not import** any kernel functions. Instead, the external loader:

1. Parses `ntoskrnl.exe`'s PDB.
2. Fills an `entry_t` structure containing every needed function address, global address, and struct offset.
3. Calls `entry(entry_t*)`.

Inside the driver, `symbols::call<fn_t>(addr, args...)` invokes those pointers safely, returning a default-constructed value if the address is zero.

The symbol table is grouped by subsystem:
`sym_mm_t`, `sym_mi_t`, `sym_ps_t`, `sym_ke_t`, `sym_ki_t`, `sym_kdp_t`, `sym_ex_t`, `sym_ob_t`, `sym_rtl_t`, `sym_io_t`, `sym_zw_t`, `sym_dbg_t`, `sym_misc_t`, `sym_crt_t`, plus `sym_offsets_t` for struct field offsets (VAD root, DTB, ActiveProcessLinks, etc.).

### 3. Paging core (`core/paging/`)

#### `paging.hpp` — 4-level page walker

Walks PML4 → PDPT → PD → PT for an arbitrary CR3, correctly handling:
- 4 KB pages
- 2 MB huge pages (PDE.PS = 1)
- 1 GB huge pages (PDPTE.PS = 1)
- Non-present entries and sanity checks on PFN fields

Returns a `page_walk_t { result, physical_address, pte* }`.

#### `pte_remap` — Per-core PTE remapping

**Idea:** allocate one 4 KB scratch page **per CPU core**, cache the pointer to its final-level PTE, and to perform an arbitrary physical read/write:

1. Raise IRQL to DISPATCH_LEVEL (pins the thread to the current core → no reschedule → no TLB entry from another core to worry about).
2. Rewrite the cached PTE to point at the target PFN (present + RW, NX cleared).
3. `INVLPG` on the scratch VA (local TLB flush only).
4. `memcpy` in/out of the scratch VA at the correct in-page offset.
5. Restore the original PTE and invalidate again.
6. Lower IRQL.

This gives:
- **`read_physical` / `write_physical`** — byte-granular access to arbitrary physical addresses.
- **`read_virtual` / `write_virtual`** — takes a target `CR3`, walks it (respecting 2 MB / 1 GB pages), and pipes each chunk through the physical primitive.

No `MmMapIoSpace`, no `MmMapLockedPages`, no MDLs — just PTE mutation on memory the driver already owns.

#### `shadow_pt` — Shadow page table hierarchy

**Idea:** claim a free (unused) PML4 slot in the system directory, install our own PDPT/PD/PT chain under it, and use PT entries to map arbitrary physical pages into a range of virtual addresses that is invisible to standard kernel enumeration.

Initialization:
1. Scan PML4 slots `[256, 510)` for an entry with `Present = 0`.
2. Allocate three independent 4 KB pages (PDPT, PD, PT), zero them.
3. Wire `PDPT[0] → PD`, `PD[0] → PT` with Present + RW.
4. Atomically write the free PML4 slot to point at our PDPT.
5. Advance a `pt_index` cursor to hand out slots on demand.

`map_physical_page(pa, protection, user_accessible)` builds a PTE with the requested protection bits (RO, RW, RX, RWX, or no-access) and returns a canonical VA reconstructed from the cursor indices.

Cleanup wipes the PML4 slot and does a full TLB flush on all processors.

### 4. Logger (`core/log/`)

Compile-time-gated (`DEBUG_LOG` macro) leveled logger:

```
[rockstar][info][entry] image_base = 0x...
```

Uses `DbgPrintEx` under the hood. Includes a `hex_dump` helper that formats output line-by-line at 16 bytes per row.

---

## Build

### Requirements

- Visual Studio 2022 (v143 toolset)
- Windows Driver Kit (WDK) 10 — `WindowsKernelModeDriver10.0` platform toolset
- Target: **x64**, Windows 10+

### Configuration

- **ConfigurationType:** `Driver`
- **DriverType:** `KMDF` (Universal)
- **Entry point:** `entry` (custom, set via `<EntryPointSymbol>`)
- **C++ standard:** `stdcpplatest`, C standard: `stdclatest`
- **RTTI / EH / Buffer security check:** off
- **INF2CAT:** disabled

### Building

```
msbuild driver.sln /p:Configuration=Release /p:Platform=x64
```

Output lands in `build/release/driver.sys` (unsigned — this project is not designed to be loaded by the SCM).

---

## Loading

This driver is **not designed to be loaded via `sc create` / `NtLoadDriver`**. It has no `DriverEntry`, no `DriverObject`, no unload routine, no device. It is intended to be **manually mapped** by an external loader that:

1. Allocates non-paged executable memory of size `SizeOfImage`.
2. Copies headers + sections and applies base relocations.
3. Resolves ntoskrnl symbols from its PDB and fills an `entry_t`.
4. Fills `m_image_base`, `m_image_size`, `m_ntoskrnl_base`, `m_directory_table_base`, and `.rdata/.data` offsets.
5. Calls the mapped `entry` function with the pointer.

The loader is **not** part of this repository.

---

## Entry point contract

```cpp
bool entry(kernel::symbols::entry_t* entry);
```

Returns `true` on successful initialization. `entry_t` layout:

```cpp
struct entry_t {
    symbols_t     m_pdb;                    // resolved kernel symbol table
    std::uint64_t m_image_base;             // this driver's mapped base
    std::uint64_t m_image_size;
    std::uint64_t m_ntoskrnl_base;
    std::uint64_t m_directory_table_base;   // system CR3
    std::uint64_t m_rdata_offset;
    std::uint64_t m_rdata_size;
    std::uint64_t m_data_offset;
    std::uint64_t m_data_size;
};
```

On success, both `paging::pte_remap` and `paging::shadow_pt` are initialized and their public APIs are ready to use.

---

## API summary

```cpp
// paging::pte_remap
bool read_physical (uint64_t pa,           void* buf, size_t size);
bool write_physical(uint64_t pa,     const void* buf, size_t size);
bool read_virtual  (uint64_t cr3, uint64_t va,       void* buf, size_t size);
bool write_virtual (uint64_t cr3, uint64_t va, const void* buf, size_t size);

// paging::shadow_pt
void* map_physical_page(uint64_t pa,
                        page_protection_t prot = read_write,
                        bool user_accessible   = false);
bool  unmap_last();
```

---

## Design notes

- **IRQL discipline:** every operation that touches paging structures raises to `DISPATCH_LEVEL` via `KeRaiseIrqlToDpcLevel`, forbidding preemption and paging.
- **TLB coherency:** `pte_remap` uses local `invlpg` (safe because the thread is pinned); `shadow_pt` uses `KeFlushSingleTb(va, true, true)` for cross-CPU invalidation because shadow mappings may be observed from any core.
- **Atomicity:** PTE writes are 64-bit stores followed by `mfence` — sufficient on x64 for coherent observation of the new mapping.
- **Sanity:** `pte_is_sane` filters obviously-corrupt entries (present bit set with PFN == 0) before dereferencing tables.
- **No allocations at runtime hot paths:** all scratch pages are allocated at init.

---

## License

MIT — see [`LICENSE`](LICENSE).

---

## Disclaimer

This code is published for educational purposes as a study of the Windows x64 memory management subsystem. The author does not condone or support its use for cheating in software, bypassing anti-tamper systems, or any unauthorized access to computer systems. You are solely responsible for how you use this code.
