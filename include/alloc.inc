ifndef __LIBC_INC
 include libc.inc
endif
.xlist
IFDEF __PE__
option	dllimport:<msvcrt>
ENDIF
;
; All allocations are of size n * _GRANULARITY
;
_GRANULARITY		equ 0x10	; align 16
_PAGESIZE_		equ 0x1000	; one page
_SEGSIZE_		equ 0x10000	; one segment (i.e., 64 Kb)
_HEAP_REGIONMAX		equ 0x40	; Max number of regions: 64
					; For small memory systems:
_HEAP_REGIONSIZE_S	equ 0x4000	; Initial region size (16K)
_HEAP_MAXREGSIZE_S	equ 0x1000000	; Maximum region size (16M)
					; For large memory systems:
_HEAP_REGIONSIZE_L	equ 0x100000	; Initial region size  (1M)
_HEAP_MAXREGSIZE_L	equ 0x1000000	; Maximum region size (16M)
_HEAP_GROWSIZE		equ 0x10000	; Default grow increment (64K)
_HEAP_GROWMIN		equ _PAGESIZE_	; Minimum grow inc (1 page)
_HEAP_GROWSTART		equ _PAGESIZE_	; Startup grow increment
_HEAP_COALESCE		equ -1		; Coalesce heap value
_HEAP_EMPTYLIST_SIZE	equ (1 * _PAGESIZE_)

S_HEAP		STRUC SIZE_T		; Memory Block Header: 16/32 byte
h_size		SIZE_T ?
h_type		BYTE ?			; 0 unused, 1 local, 2 global, 3 aligned
h_prev		PVOID ?			; global block's (user size)
h_next		PVOID ?			; local block's (chunck size)
S_HEAP		ENDS

externdef	_amblksiz:dword
externdef	_heap_base:size_t
externdef	_heap_free:size_t

malloc		proto :size_t
realloc		PROTO :ptr, :size_t
free		proto :ptr
calloc		proto :dword, :dword
_aligned_malloc proto dwSize:size_t, alignment:UINT

IFNDEF __PE__

_alloca64	proto :dword, :dword
ifdef _WIN64
alloca	macro dwSize:req, ReservedStack:=<@ReservedStack>
	exitm<_alloca64( dwSize, ReservedStack )>
	endm
else
alloca		proto :dword
endif
salloc		proto :LPSTR

__coreleft	proto
__purgeheap	proto

ELSE
alloca		proto :dword
option		dllimport:<kernel32>
ENDIF
;;;;;;;;;;;;;;; kernel32

PAGE_NOACCESS		equ 0x01
PAGE_READONLY		equ 0x02
PAGE_READWRITE		equ 0x04
PAGE_WRITECOPY		equ 0x08
PAGE_EXECUTE		equ 0x10
PAGE_EXECUTE_READ	equ 0x20
PAGE_EXECUTE_READWRITE	equ 0x40
PAGE_EXECUTE_WRITECOPY	equ 0x80
PAGE_GUARD		equ 0x0100
PAGE_NOCACHE		equ 0x0200
PAGE_WRITECOMBINE	equ 0x0400

MEM_COMMIT		equ 0x1000
MEM_RESERVE		equ 0x2000
MEM_DECOMMIT		equ 0x4000
MEM_RELEASE		equ 0x8000
MEM_FREE		equ 0x00010000
MEM_PRIVATE		equ 0x00020000
MEM_MAPPED		equ 0x00040000
MEM_RESET		equ 0x00080000
MEM_TOP_DOWN		equ 0x00100000
MEM_4MB_PAGES		equ 0x80000000
SEC_FILE		equ 0x00800000
SEC_IMAGE		equ 0x01000000
SEC_VLM			equ 0x02000000
SEC_RESERVE		equ 0x04000000
SEC_COMMIT		equ 0x08000000
SEC_NOCACHE		equ 0x10000000
MEM_IMAGE		equ SEC_IMAGE

; Global Memory Flags

GMEM_FIXED		equ 0x0000
GMEM_MOVEABLE		equ 0x0002
GMEM_NOCOMPACT		equ 0x0010
GMEM_NODISCARD		equ 0x0020
GMEM_ZEROINIT		equ 0x0040
GMEM_MODIFY		equ 0x0080
GMEM_DISCARDABLE	equ 0x0100
GMEM_NOT_BANKED		equ 0x1000
GMEM_SHARE		equ 0x2000
GMEM_DDESHARE		equ 0x2000
GMEM_NOTIFY		equ 0x4000
GMEM_LOWER		equ GMEM_NOT_BANKED
GMEM_VALID_FLAGS	equ 0x7F72
GMEM_INVALID_HANDLE	equ 0x8000

;GHND			equ GMEM_MOVEABLE or GMEM_ZEROINIT
;GPTR			equ GMEM_FIXED or GMEM_ZEROINIT

; Flags returned by GlobalFlags (in addition to GMEM_DISCARDABLE)

GMEM_DISCARDED		equ 0x4000
GMEM_LOCKCOUNT		equ 0x00FF

; Local Memory Flags

LMEM_FIXED		equ 0x0000
LMEM_MOVEABLE		equ 0x0002
LMEM_NOCOMPACT		equ 0x0010
LMEM_NODISCARD		equ 0x0020
LMEM_ZEROINIT		equ 0x0040
LMEM_MODIFY		equ 0x0080
LMEM_DISCARDABLE	equ 0x0F00
LMEM_VALID_FLAGS	equ 0x0F72
LMEM_INVALID_HANDLE	equ 0x8000

;LHND			equ LMEM_MOVEABLE OR LMEM_ZEROINIT
;LPTR			equ LMEM_FIXED OR LMEM_ZEROINIT
;NONZEROLHND		equ LMEM_MOVEABLE
;NONZEROLPTR		equ LMEM_FIXED

; Flags returned by LocalFlags (in addition to LMEM_DISCARDABLE)

LMEM_DISCARDED		equ 0x4000
LMEM_LOCKCOUNT		equ 0x00FF

PROCESS_HEAP_REGION		equ 0x0001
PROCESS_HEAP_UNCOMMITTED_RANGE	equ 0x0002
PROCESS_HEAP_ENTRY_BUSY		equ 0x0004
PROCESS_HEAP_ENTRY_MOVEABLE	equ 0x0010
PROCESS_HEAP_ENTRY_DDESHARE	equ 0x0020

HEAP_NO_SERIALIZE		equ 0x00000001
HEAP_GROWABLE			equ 0x00000002
HEAP_GENERATE_EXCEPTIONS	equ 0x00000004
HEAP_ZERO_MEMORY		equ 0x00000008
HEAP_REALLOC_IN_PLACE_ONLY	equ 0x00000010
HEAP_TAIL_CHECKING_ENABLED	equ 0x00000020
HEAP_FREE_CHECKING_ENABLED	equ 0x00000040
HEAP_DISABLE_COALESCE_ON_FREE	equ 0x00000080
HEAP_CREATE_ALIGN_16		equ 0x00010000
HEAP_CREATE_ENABLE_TRACING	equ 0x00020000
HEAP_MAXIMUM_TAG		equ 0x0FFF
HEAP_PSEUDO_TAG_FLAG		equ 0x8000
HEAP_TAG_SHIFT			equ 18

PROCESS_HEAP_ENTRY	STRUC SIZE_T
lpData			PVOID ?
cbData			DWORD ?
cbOverhead		BYTE ?
iRegionIndex		BYTE ?
wFlags			WORD ?
UNION
    STRUC ;Block
	hMem		HANDLE ?
	dwReserved	DD 3 dup(?)
    ENDS
    STRUC ;Region
	dwCommittedSize DWORD ?
	dwUnCommittedSize DWORD ?
	lpFirstBlock	PVOID ?
	lpLastBlock	PVOID ?
    ENDS
ENDS
PROCESS_HEAP_ENTRY	ENDS

MEMORY_BASIC_INFORMATION STRUC SIZE_T
BaseAddress		PVOID ?
AllocationBase		PVOID ?
AllocationProtect	DWORD ?
RegionSize		SIZE_T ?
State			DWORD ?
Protect			DWORD ?
_Type			DWORD ?
MEMORY_BASIC_INFORMATION ENDS

MEMORYSTATUS		STRUC
dwLength		dd ?	; sizeof(MEMORYSTATUS): no need to set..
dwMemoryLoad		dd ?	; percent of memory in use
dwTotalPhys		dd ?	; bytes of physical memory
dwAvailPhys		dd ?	; free physical memory bytes
dwTotalPageFile		dd ?	; bytes of paging file
dwAvailPageFile		dd ?	; free bytes of paging file
dwTotalVirtual		dd ?	; user bytes of address space
dwAvailVirtual		dd ?	; free user bytes
MEMORYSTATUS		ENDS

MEMORYSTATUSEX		STRUC
dwLength		dd ?	; Size of structure: must be set before call
dwMemoryLoad		dd ?
ullTotalPhys		dq ?
ullAvailPhys		dq ?
ullTotalPageFile	dq ?
ullAvailPageFile	dq ?
ullTotalVirtual		dq ?
ullAvailVirtual		dq ?
ullAvailExtendedVirtual dq ?	; Reserved. This value is always 0.
MEMORYSTATUSEX		ENDS

GlobalAlloc proto _CType \
	uFlags:		UINT,
	dwBytes:	SIZE_T

GlobalFree proto _CType \
	hMem:		HANDLE

GlobalReAlloc proto _CType \
	hMem:		HANDLE,
	dwBytes:	SIZE_T,
	uFlags:		UINT

GlobalSize proto _CType \
	hMem:		HANDLE

GlobalFlags proto _CType \
	hMem:		HANDLE

GlobalHandle proto _CType \
	pMem:		PVOID

GlobalLock proto _CType \
	hMem:		HANDLE

GlobalUnlock proto _CType \
	hMem:		HANDLE

GlobalCompact proto _CType \
	dwMinFree:	SIZE_T

GlobalFix proto _CType \
	hMem:		HANDLE

GlobalUnfix proto _CType \
	hMem:		HANDLE

GlobalWire proto _CType \
	hMem:		HANDLE

GlobalUnWire proto _CType \
	hMem:		HANDLE

GlobalMemoryStatus proto _CType \
	lpBuffer:	PTR MEMORYSTATUS

GlobalMemoryStatusEx proto _CType \
	lpBuffer:	PTR MEMORYSTATUSEX

LocalAlloc proto _CType \
	uFlags:		UINT,
	uBytes:		SIZE_T

LocalReAlloc proto _CType \
	hMem:		HANDLE,
	uBytes:		SIZE_T,
	uFlags:		UINT

LocalLock proto _CType \
	hMem:		HANDLE

LocalHandle proto _CType \
	pMem:		PVOID

LocalUnlock proto _CType \
	hMem:		HANDLE

LocalSize proto _CType \
	hMem:		HANDLE

LocalFlags proto _CType \
	hMem:		HANDLE

LocalFree proto _CType \
	hMem:		HANDLE

LocalShrink proto _CType \
	hMem:		HANDLE,
	cbNewSize:	SIZE_T

LocalCompact proto _CType \
	uMinFree:	SIZE_T

GetProcessHeap proto _CType

GetProcessHeaps proto _CType \
	NumberOfHeaps:	DWORD,
	ProcessHeaps:	PVOID

HeapCreate proto _CType \
	flOptions:	DWORD,
	dwInitialSize:	SIZE_T,
	dwMaximumSize:	SIZE_T

HeapDestroy proto _CType \
	hHeap:		HANDLE

HeapAlloc proto _CType \
	hHeap:		HANDLE,
	dwFlags:	DWORD,
	dwBytes:	SIZE_T

HeapReAlloc proto _CType \
	hHeap:		HANDLE,
	dwFlags:	DWORD,
	lpMem:		PVOID,
	dwBytes:	SIZE_T

HeapFree proto _CType \
	hHeap:		HANDLE,
	dwFlags:	DWORD,
	lpMem:		PVOID

HeapSize proto _CType \
	hHeap:		HANDLE,
	dwFlags:	DWORD,
	lpMem:		PVOID

HeapValidate proto _CType \
	hHeap:		HANDLE,
	dwFlags:	DWORD,
	lpMem:		PVOID

HeapCompact proto _CType \
	hHeap:		HANDLE,
	dwFlags:	DWORD

HeapLock proto _CType \
	hHeap:		HANDLE

HeapUnlock proto _CType \
	hHeap:		HANDLE

HeapWalk proto _CType \
	hHeap:		HANDLE,
	lpEntry:	PTR LPPROCESS_HEAP_ENTRY

VirtualAlloc proto _CType \
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	flAllocationType:DWORD,
	flProtect:	DWORD

VirtualFree proto _CType \
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	dwFreeType:	DWORD

VirtualProtect proto _CType \
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	flNewProtect:	DWORD,
	lpflOldProtect: PTR DWORD

VirtualQuery proto _CType \
	lpAddress:	PVOID,
	lpBuffer:	PTR MEMORY_BASIC_INFORMATION,
	dwLength:	SIZE_T

VirtualAllocEx proto _CType \
	hProcess:	HANDLE,
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	flAllocationType:DWORD,
	flProtect:	DWORD

VirtualFreeEx proto _CType \
	hProcess:	HANDLE,
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	dwFreeType:	DWORD

VirtualProtectEx proto _CType \
	hProcess:	HANDLE,
	lpAddress:	PVOID,
	dwSize:		SIZE_T,
	flNewProtect:	DWORD,
	lpflOldProtect: PTR DWORD

VirtualQueryEx proto _CType \
	hProcess:	HANDLE,
	lpAddress:	PVOID,
	lpBuffer:	PTR MEMORY_BASIC_INFORMATION,
	dwLength:	SIZE_T

.list
