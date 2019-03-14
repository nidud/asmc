ifndef _INC_WINHEAP
_INC_WINHEAP equ <>

include crtdefs.inc

.pragma pack(push, _CRT_PACKING)

ifndef _CRTBLD
;;
;; This is an internal C runtime header file. It is used when building
;; the C runtimes only. It is not to be used as a public header file.
;;
.err <ERROR: Use of C runtime library internal header file.>
endif

include sal.inc
include windows.inc

BYTES_PER_PARA          equ 16
PARAS_PER_PAGE          equ 256
BYTES_PER_PAGE          equ <(BYTES_PER_PARA * PARAS_PER_PAGE)>

externdef               _crtheap:HANDLE

_nh_malloc              proto __cdecl :size_t, :int_t
_heap_alloc             proto __cdecl :size_t

_heap_init              proto __cdecl
_heap_term              proto __cdecl

_malloc_base            proto __cdecl :size_t

_free_base              proto __cdecl :ptr
_realloc_base           proto __cdecl :ptr, :size_t
_recalloc_base          proto __cdecl :ptr, :size_t, :size_t

_expand_base            proto __cdecl :ptr, :size_t
_calloc_base            proto __cdecl :size_t, :size_t

_msize_base             proto __cdecl :ptr
_aligned_msize_base     proto __cdecl :ptr, :size_t, :size_t

.pragma pack(pop)

endif ;; _INC_WINHEAP
