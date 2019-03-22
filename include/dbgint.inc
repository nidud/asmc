ifndef _INC_DBGINT
_INC_DBGINT equ <>

ifndef _CRTBLD
;;
;; This is an internal C runtime header file. It is used when building
;; the C runtimes only. It is not to be used as a public header file.
;;
.err <ERROR: Use of C runtime library internal header file.>
endif

include crtdbg.inc

.pragma pack(push, _CRT_PACKING)

ifndef _CRTIMP
ifdef CRTDLL
_CRTIMP equ <__declspec(dllexport)>
else
ifdef _DLL
_CRTIMP equ <__declspec(dllimport)>
else
_CRTIMP equ <>
endif
endif
endif

_CRT_DEBUGGER_IGNORE		equ -1
_CRT_DEBUGGER_GSFAILURE		equ 1
_CRT_DEBUGGER_INVALIDPARAMETER	equ 2
_CRT_DEBUGGER_ABORT		equ 3

ifdef _M_IX86
_CRT_DEBUGGER_HOOK	equ <_crt_debugger_hook>
else
_CRT_DEBUGGER_HOOK	equ <__crt_debugger_hook>
endif

_CRT_DEBUGGER_HOOK proto :int_t

ifndef _DEBUG

ifdef __cplusplus
_new_crt equ <new>
endif

_expand_crt		equ <_expand>
_free_crt		equ <free>
_msize_crt		equ <_msize>

_dupenv_s_crt macro ps1, size, s2
	exitm<_dupenv_s(ps1, size, s2)>
	endm
_wdupenv_s_crt macro ps1, _size, s2
	exitm<_wdupenv_s(ps1, _size, s2)>
	endm

if defined (_SYSCRT) OR defined (MRTDLL) OR defined (_M_CEE_PURE)
_malloc_crt		equ <malloc>
_calloc_crt		equ <calloc>
_realloc_crt		equ <realloc>
_recalloc_crt		equ <_recalloc>
else
_malloc_crt		proto __cdecl :size_t
_calloc_crt		proto __cdecl :size_t, :size_t
_realloc_crt		proto __cdecl :ptr, :size_t
_recalloc_crt		proto __cdecl :ptr, :size_t, :size_t
endif

_malloc_base		equ <malloc>
_nh_malloc_base		equ <_nh_malloc>
_nh_malloc_dbg macro s, n, t, f, l
	exitm<_nh_malloc(s, n)>
	endm
_heap_alloc_dbg macro s, t, f, l
	exitm<_heap_alloc(s)>
	endm
_calloc_base		equ <calloc>
_realloc_base		equ <realloc>
_recalloc_base		equ <_recalloc>
_expand_base		equ <_expand>
_free_base		equ <free>
_msize_base		equ <_msize>
_aligned_msize_base	equ <_aligned_msize>
_aligned_malloc_base	equ <_aligned_malloc>
_aligned_realloc_base	equ <_aligned_realloc>
_aligned_recalloc_base	equ <_aligned_recalloc>
_aligned_offset_malloc_base equ <_aligned_offset_malloc>
_aligned_offset_realloc_base equ <_aligned_offset_realloc>
_aligned_offset_recalloc_base equ <_aligned_offset_recalloc>
_aligned_free_base	equ <_aligned_free>

_calloc_dbg_nolock macro c, s, t, f, l
	exitm<_calloc_nolock(c, s)>
	endm
_realloc_dbg_nolock macro p, s, t, f, l
	exitm<_realloc_nolock(p, s)>
	endm
_recalloc_dbg_nolock macro p, c, s, t, f, l
	exitm<_recalloc_nolock(p, c, s)>
	endm
_free_base_nolock	equ _free_nolock
_free_dbg_nolock macro p, t
	exitm<_free_nolock(p)>
	endm

else  ;; _DEBUG

_THISFILE		equ <@FileCur>

ifdef __cplusplus
_new_crt		equ <new(_CRT_BLOCK, _THISFILE, @Line)>
endif

_malloc_crt macro s
	exitm<_malloc_dbg(s, _CRT_BLOCK, _THISFILE, @Line)>
	endm
_calloc_crt macro c, s
	exitm<_calloc_dbg(c, s, _CRT_BLOCK, _THISFILE, @Line)>
	endm
_realloc_crt macro p, s
	exitm<_realloc_dbg(p, s, _CRT_BLOCK, _THISFILE, @Line)>
	endm
_recalloc_crt macro p, c, s
	exitm<_recalloc_dbg(p, c, s, _CRT_BLOCK, _THISFILE, @Line)>
	endm
_expand_crt macro p, s
	exitm<_expand_dbg(p, s, _CRT_BLOCK)>
	endm
_free_crt macro p
	exitm<_free_dbg(p, _CRT_BLOCK)>
	endm
_msize_crt macro p
	exitm<_msize_dbg(p, _CRT_BLOCK)>
	endm
_dupenv_s_crt macro ps1, size, s2
	exitm<_dupenv_s_dbg(ps1, size, s2, _CRT_BLOCK, _THISFILE, @Line)>
	endm
_wdupenv_s_crt macro ps1, size, s2
	exitm<_wdupenv_s_dbg(ps1, size, s2, _CRT_BLOCK, _THISFILE, @Line)>
	endm

_malloc_base		proto __cdecl :size_t
_nh_malloc_base		proto __cdecl :size_t, :int_t
_nh_malloc_dbg		proto __cdecl :size_t, :int_t, :int_t, :string_t, :int_t
_heap_alloc_dbg		proto __cdecl :size_t, :int_t, string_t, :int_t
_calloc_base		proto __cdecl :size_t, :size_t
_realloc_base		proto __cdecl :ptr, :size_t
_recalloc_base		proto __cdecl :ptr, :size_t, :size_t
_expand_base		proto __cdecl :ptr, :size_t
_free_base		proto __cdecl :ptr
_msize_base		proto __cdecl :ptr
_aligned_msize_base	proto __cdecl :ptr, :size_t, :size_t

_aligned_free_base	proto WINAPI :ptr

_aligned_malloc_base	proto __cdecl :size_t, :size_t
_aligned_offset_malloc_base proto __cdecl :size_t, :size_t, :size_t
_aligned_realloc_base	proto __cdecl :ptr, :size_t, :size_t
_aligned_recalloc_base	proto __cdecl :ptr, :size_t, :size_t, :size_t

_aligned_offset_realloc_base proto __cdecl :ptr, :size_t, :size_t, :size_t
_aligned_offset_recalloc_base proto __cdecl :ptr, :size_t, :size_t, :size_t, :size_t

_calloc_dbg_nolock	proto __cdecl :size_t, :size_t, :int_t, :string_t, :int_t
_realloc_dbg_nolock	proto __cdecl :ptr, :size_t, :int_t, :string_t, :int_t
_recalloc_dbg_nolock	proto __cdecl :ptr, :size_t, :size_t, :int_t, :string_t, :int_t


_free_base_nolock	proto WINAPI :ptr
_free_dbg_nolock	proto WINAPI :ptr, :SINT

nNoMansLandSize		equ 4

CrtMemBlockHeader	STRUC
pBlockHeaderNext	PVOID ?
pBlockHeaderPrev	PVOID ?
szFileName		LPSTR ?
nLine			SINT ?
ifdef _WIN64
nBlockUse		SINT ?
nDataSize		size_t ?
else
nDataSize		size_t ?
nBlockUse		SINT ?
endif
lRequest		dd ?
gap			db nNoMansLandSize dup(?)
CrtMemBlockHeader	ENDS

pbData macro pblock
	exitm<(pblock + 1)>
	endm
pHdr macro pbData
	exitm<((pbData)-1)>
	endm

_CrtSetDbgBlockType	proto __cdecl :ptr, :int_t

_BLOCK_TYPE_IS_VALID macro use
	exitm<(_BLOCK_TYPE(use) EQ _CLIENT_BLOCK \
	      or (use) == _NORMAL_BLOCK \
	      or _BLOCK_TYPE(use) == _CRT_BLOCK \
	      or (use) == _IGNORE_BLOCK)>
	endm


externdef		_pfnAllocHook:_CRT_ALLOC_HOOK

;int
_CrtDefaultAllocHook proto WINAPI \
		      : SINT,
		      : ptr,
		      : size_t,
		      : SINT,
		      : sdword,
		      : ptr,
		      : SINT


DBGRPT_MAX_MSG		equ 4096
DBGRPT_TOOLONGMSG	equ <"_CrtDbgReport: String too long or IO Error">
DBGRPT_INVALIDMSG	equ <"_CrtDbgReport: String too long or Invalid characters in String">

ReportHookNode		STRUC
prev			PVOID ?
next			PVOID ?
refcount		dd ?
pfnHookFunc		_CRT_REPORT_HOOK ?
ReportHookNode		ENDS

ReportHookNodeW		STRUC
prev			PVOID ?
next			PVOID ?
refcount		dd ?
pfnHookFunc		_CRT_REPORT_HOOKW ?
ReportHookNodeW		ENDS

endif  ;; _DEBUG

.pragma pack(pop)

endif  ;; _INC_DBGINT
