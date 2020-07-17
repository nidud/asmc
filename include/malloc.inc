ifndef _INC_MALLOC
_INC_MALLOC equ <>
.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif
.pragma comment(lib, libc, msvcrt)
;
; All allocations are of size n * _GRANULARITY
;
_GRANULARITY        equ 0x10        ; align 16
_PAGESIZE_          equ 0x1000      ; one page
_SEGSIZE_           equ 0x10000     ; one segment (i.e., 64 Kb)
_HEAP_REGIONMAX     equ 0x40        ; Max number of regions: 64
                                    ; For small memory systems:
_HEAP_REGIONSIZE_S  equ 0x4000      ; Initial region size (16K)
_HEAP_MAXREGSIZE_S  equ 0x1000000   ; Maximum region size (16M)
                                    ; For large memory systems:
_HEAP_REGIONSIZE_L  equ 0x100000    ; Initial region size  (1M)
_HEAP_MAXREGSIZE_L  equ 0x1000000   ; Maximum region size (16M)
_HEAP_GROWSIZE      equ 0x40000     ; Default grow increment (64K)
_HEAP_GROWMIN       equ _PAGESIZE_  ; Minimum grow inc (1 page)
_HEAP_GROWSTART     equ _PAGESIZE_  ; Startup grow increment
_HEAP_COALESCE      equ -1          ; Coalesce heap value
_HEAP_EMPTYLIST_SIZE equ (1 * _PAGESIZE_)

;; Maximum heap request the heap manager will attempt

ifdef _WIN64
_HEAP_MAXREQ equ 0xFFFFFFFFFFFFFFE0
else
_HEAP_MAXREQ equ 0xFFFFFFE0
endif

.enum { _HEAP_FREE, _HEAP_LOCAL, _HEAP_GLOBAL, _HEAP_ALIGNED }

HEAP    struct size_t   ; Memory Block Header: 16/32 byte
size    size_t ?
type    uchar_t ?
prev    ptr_t ?
next    ptr_t ?
HEAP    ends
heap_t  typedef ptr HEAP

externdef _amblksiz:dword
externdef _heap_base:heap_t
externdef _heap_free:heap_t

ifndef _CRT_ALLOCATION_DEFINED
_CRT_ALLOCATION_DEFINED equ <>
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
endif
_msize proto __cdecl :ptr
_resetstkoflw proto __cdecl

ifndef _MSVCRT
_alloca64 proto __cdecl :dword, :dword
ifdef _WIN64
alloca macro dwSize:req, ReservedStack:=<@ReservedStack>
    exitm<_alloca64( dwSize, ReservedStack )>
    endm
else
alloca proto __cdecl :dword
endif
else
alloca proto __cdecl :dword
endif

;;;;;;;;;;;;;;; kernel32

.pragma comment(lib, kernel32)

GMEM_MOVEABLE   equ 0x0002
GMEM_DDESHARE   equ 0x2000
HEAP_ZERO_MEMORY equ 0x00000008

GlobalAlloc     proto WINAPI uFlags:UINT, dwBytes:SIZE_T
GlobalFree      proto WINAPI :HANDLE
GlobalLock      proto WINAPI :HANDLE
GlobalUnlock    proto WINAPI :HANDLE
GetProcessHeap  proto WINAPI
HeapAlloc       proto WINAPI :HANDLE, dwFlags:DWORD, dwBytes:SIZE_T
HeapFree        proto WINAPI :HANDLE, dwFlags:DWORD, lpMem:PVOID

.pragma list(pop)
endif
