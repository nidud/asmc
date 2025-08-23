ifndef _INC_MALLOC
define _INC_MALLOC
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif
.pragma comment(lib, libc, msvcrt)

; All allocations are of size n * _GRANULARITY

define _GRANULARITY         0x10        ; align 16
define _PAGESIZE_           0x1000      ; one page
define _SEGSIZE_            0x10000     ; one segment (i.e., 64 Kb)
define _HEAP_REGIONMAX      0x40        ; Max number of regions: 64
                                        ; For small memory systems:
define _HEAP_REGIONSIZE_S   0x4000      ; Initial region size (16K)
define _HEAP_MAXREGSIZE_S   0x1000000   ; Maximum region size (16M)
                                        ; For large memory systems:
define _HEAP_REGIONSIZE_L   0x100000    ; Initial region size  (1M)
define _HEAP_MAXREGSIZE_L   0x1000000   ; Maximum region size (16M)
ifdef __UNIX__
ifdef _WIN64
define _HEAP_GROWSIZE       0x100000    ; --> 2M
else
define _HEAP_GROWSIZE       0x10000     ; --> 128K
endif
else
define _HEAP_GROWSIZE       0x20000     ; Default grow increment (64K)
endif
define _HEAP_GROWMIN        _PAGESIZE_  ; Minimum grow inc (1 page)
define _HEAP_GROWSTART      _PAGESIZE_  ; Startup grow increment
define _HEAP_COALESCE       (-1)        ; Coalesce heap value
define _HEAP_EMPTYLIST_SIZE (1 * _PAGESIZE_)

; Maximum heap request the heap manager will attempt

ifdef _WIN64
define _HEAP_MAXREQ 0xFFFFFFFFFFFFFFE0
else
define _HEAP_MAXREQ 0xFFFFFFE0
endif

.enum { _HEAP_FREE, _HEAP_LOCAL, _HEAP_GLOBAL, _HEAP_ALIGNED }

heap_t  typedef ptr HEAP

HEAP    struct size_t   ; Memory Block Header: 8/16/32 byte
size    size_t ?
type    uchar_t ?
prev    heap_t ?
next    heap_t ?
HEAP    ends

ifndef __UNIX__
externdef _crtheap:HANDLE
endif
externdef _amblksiz:uint_t
externdef _heap_base:heap_t
externdef _heap_free:heap_t

ifndef _CRT_ALLOCATION_DEFINED
define _CRT_ALLOCATION_DEFINED

calloc proto __cdecl :size_t, :size_t
free proto __cdecl :ptr
malloc proto __cdecl :size_t
realloc proto __cdecl :ptr, :size_t
_recalloc proto __cdecl :ptr, :size_t, :size_t

_aligned_free proto __cdecl :ptr
_aligned_malloc proto __cdecl :size_t, :size_t
_aligned_offset_malloc proto __cdecl :size_t, :size_t, :size_t
_aligned_realloc proto __cdecl :ptr, :size_t, :size_t
_aligned_recalloc proto __cdecl :ptr, :size_t, :size_t, :size_t
_aligned_offset_realloc proto __cdecl :ptr, :size_t, :size_t, :size_t
_aligned_offset_recalloc proto __cdecl :ptr, :size_t, :size_t, :size_t, :size_t
_aligned_msize proto __cdecl :ptr, :size_t, :size_t

define _mm_free     <_aligned_free>
define _mm_malloc   <_aligned_malloc>
endif

ifndef _HEAPINFO_DEFINED
define _HEAPINFO_DEFINED
_heapinfo       struct
_pentry         intptr_t ?
_size           size_t ?
_useflag        int_t ?
_heapinfo       ends
_HEAPINFO       typedef _heapinfo
endif

_msize proto __cdecl :ptr
_resetstkoflw proto __cdecl

ifdef _WIN64
alloca proto watcall :uint_t {
    add     eax,16-1 ; assume 16 aligned
    and     eax,-16
    sub     rsp,rax
    lea     rax,[rsp+@ReservedStack]
    }
else
alloca proto __cdecl :uint_t
endif
_freea proto fastcall :abs {
    }
_calloca proto watcall :uint_t, :uint_t {
    mul edx
    alloca(eax)
    }

if not defined(_MSVCRT) or defined(_CRTBLD)
_coreleft       proto __cdecl
endif

define _HEAPEMPTY       (-1)
define _HEAPOK          (-2)
define _HEAPBADBEGIN    (-3)
define _HEAPBADNODE     (-4)
define _HEAPEND         (-5)
define _HEAPBADPTR      (-6)
define _FREEENTRY       0
define _USEDENTRY       1

_heapwalk proto __cdecl :ptr _HEAPINFO
_get_heap_handle proto __cdecl

_heapadd proto __cdecl :ptr, :size_t
_heapchk proto __cdecl
_heapmin proto __cdecl
_heapset proto __cdecl :uint_t
_heapused proto __cdecl :ptr size_t, :ptr size_t

;;;;;;;;;;;;;;; kernel32

.pragma comment(lib, kernel32)

define GMEM_MOVEABLE    0x0002
define GMEM_DDESHARE    0x2000
define HEAP_ZERO_MEMORY 0x00000008

GlobalAlloc     proto WINAPI uFlags:UINT, dwBytes:size_t
GlobalFree      proto WINAPI :HANDLE
GlobalLock      proto WINAPI :HANDLE
GlobalUnlock    proto WINAPI :HANDLE
GetProcessHeap  proto WINAPI
HeapAlloc       proto WINAPI :HANDLE, dwFlags:DWORD, dwBytes:size_t
HeapFree        proto WINAPI :HANDLE, dwFlags:DWORD, lpMem:PVOID

.pragma list(pop)
endif
