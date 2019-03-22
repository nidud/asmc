include crtdefs.inc

ifndef _INC_CRTDBG
_INC_CRTDBG equ <>

.pragma pack(push, _CRT_PACKING)

ifndef NULL
NULL equ 0
endif

_HFILE			typedef ptr

_CRT_WARN		equ 0
_CRT_ERROR		equ 1
_CRT_ASSERT		equ 2
_CRT_ERRCNT		equ 3

_CRTDBG_MODE_FILE	equ 0x1
_CRTDBG_MODE_DEBUG	equ 0x2
_CRTDBG_MODE_WNDW	equ 0x4
_CRTDBG_REPORT_MODE	equ -1

ifdef _M_IX86
_CRTDBG_INVALID_HFILE	equ (-1)
_CRTDBG_HFILE_ERROR	equ (-2)
_CRTDBG_FILE_STDOUT	equ (-4)
_CRTDBG_FILE_STDERR	equ (-5)
_CRTDBG_REPORT_FILE	equ (-6)
else
_CRTDBG_INVALID_HFILE	equ (-1)
_CRTDBG_HFILE_ERROR	equ (-2)
_CRTDBG_FILE_STDOUT	equ (-4)
_CRTDBG_FILE_STDERR	equ (-5)
_CRTDBG_REPORT_FILE	equ (-6)
endif

ifndef _M_CEE_PURE
CALLBACK(_CRT_REPORT_HOOK, :int_t, :ptr, :int_t)
CALLBACK(_CRT_REPORT_HOOKW, :int_t, :ptr wchar_t, :ptr int_t)
else
CALLBACK(_CRT_REPORT_HOOK, :int_t, :string_t, :ptr int_t)
CALLBACK(_CRT_REPORT_HOOKW, :int_t, :ptr wchar_t, :ptr int_t)
endif

ifdef _M_CEE
CALLBACK(_CRT_REPORT_HOOK_M, :int_t, :string_t, :ptr int_t)
CALLBACK(_CRT_REPORT_HOOKW_M, :int_t, :ptr wchar_t, :ptr int_t)
endif

_CRT_RPTHOOK_INSTALL	equ 0
_CRT_RPTHOOK_REMOVE	equ 1

_HOOK_ALLOC		equ 1
_HOOK_REALLOC		equ 2
_HOOK_FREE		equ 3

ifndef _M_CEE_PURE
CALLBACK(_CRT_ALLOC_HOOK, :int_t, :ptr, :size_t, :int_t, :LONG, :string_t, :int_t)
else
CALLBACK(_CRT_ALLOC_HOOK, :int_t, :ptr, :size_t, :int_t, :LONG, :string_t, :int_t)
endif
ifdef _M_CEE
CALLBACK(_CRT_ALLOC_HOOK_M, :int_t, :ptr, :size_t, :int_t, :LONG, :string_t, :int_t)
endif

_CRTDBG_ALLOC_MEM_DF	equ 0x01
_CRTDBG_DELAY_FREE_MEM_DF equ 0x02
_CRTDBG_CHECK_ALWAYS_DF equ 0x04
_CRTDBG_RESERVED_DF	equ 0x08
_CRTDBG_CHECK_CRT_DF	equ 0x10
_CRTDBG_LEAK_CHECK_DF	equ 0x20

_CRTDBG_CHECK_EVERY_16_DF equ 0x00100000
_CRTDBG_CHECK_EVERY_128_DF equ 0x00800000
_CRTDBG_CHECK_EVERY_1024_DF equ 0x04000000

_CRTDBG_CHECK_DEFAULT_DF equ 0
_CRTDBG_REPORT_FLAG	equ -1

_BLOCK_TYPE macro block
	exitm<(block AND 0xFFFF)>
	endm
_BLOCK_SUBTYPE macro block
	exitm<(block SHR 16 AND 0xFFFF)>
	endm


_FREE_BLOCK		equ 0
_NORMAL_BLOCK		equ 1
_CRT_BLOCK		equ 2
_IGNORE_BLOCK		equ 3
_CLIENT_BLOCK		equ 4
_MAX_BLOCKS		equ 5

ifndef _M_CEE_PURE
CALLBACK(_CRT_DUMP_CLIENT, :ptr, :size_t)
else
CALLBACK(_CRT_DUMP_CLIENT, :ptr, :size_t)
endif
ifdef _M_CEE
CALLBACK(_CRT_DUMP_CLIENT_M, :ptr, :size_t)
endif

CrtMemState		STRUC
pBlockHeader		ptr_t ?
lCounts			size_t _MAX_BLOCKS dup(?)
lSizes			size_t _MAX_BLOCKS dup(?)
lHighWaterCount		size_t ?
lTotalCount		size_t ?
CrtMemState		ENDS

ifndef _STATIC_ASSERT
_STATIC_ASSERT macro expr
	exitm<typedef char __static_assert_t[ (expr) ]>
	endm
endif

ifndef _DEBUG

ifndef _ASSERT
_ASSERT macro expr
	exitm<>
	endm
endif

ifndef _ASSERTE
_ASSERTE macro expr
	exitm<>
	endm
endif

ifndef _ASSERT_EXPR
_ASSERT_EXPR macro expr, expr_str
	exitm<>
	endm
endif

ifndef _ASSERT_BASE
_ASSERT_BASE equ <_ASSERT_EXPR>
endif

_RPT0 macro rptno, msg
	exitm<>
	endm
_RPTW0 macro rptno, msg
	exitm<>
	endm

_RPT1 macro rptno, msg, arg1
	exitm<>
	endm
_RPTW1 macro rptno, msg, arg1
	exitm<>
	endm

_RPT2 macro rptno, msg, arg1, arg2
	exitm<>
	endm
_RPTW2 macro rptno, msg, arg1, arg2
	exitm<>
	endm

_RPT3 macro rptno, msg, arg1, arg2, arg3
	exitm<>
	endm
_RPTW3 macro rptno, msg, arg1, arg2, arg3
	exitm<>
	endm

_RPT4 macro rptno, msg, arg1, arg2, arg3, arg4
	exitm<>
	endm
_RPTW4 macro rptno, msg, arg1, arg2, arg3, arg4
	exitm<>
	endm

_RPT5 macro rptno, msg, arg1, arg2, arg3, arg4, arg5
	exitm<>
	endm
_RPTW5 macro rptno, msg, arg1, arg2, arg3, arg4, arg5
	exitm<>
	endm


_RPTF0 macro rptno, msg
	exitm<>
	endm
_RPTFW0 macro rptno, msg
	exitm<>
	endm

_RPTF1 macro rptno, msg, arg1
	exitm<>
	endm
_RPTFW1 macro rptno, msg, arg1
	exitm<>
	endm

_RPTF2 macro rptno, msg, arg1, arg2
	exitm<>
	endm
_RPTFW2 macro rptno, msg, arg1, arg2
	exitm<>
	endm

_RPTF3 macro rptno, msg, arg1, arg2, arg3
	exitm<>
	endm
_RPTFW3 macro rptno, msg, arg1, arg2, arg3
	exitm<>
	endm

_RPTF4 macro rptno, msg, arg1, arg2, arg3, arg4
	exitm<>
	endm
_RPTFW4 macro rptno, msg, arg1, arg2, arg3, arg4
	exitm<>
	endm

_RPTF5 macro rptno, msg, arg1, arg2, arg3, arg4, arg5
	exitm<>
	endm
_RPTFW5 macro rptno, msg, arg1, arg2, arg3, arg4, arg5
	exitm<>
	endm

_malloc_dbg macro s, t, f, l
	exitm<malloc(s)>
	endm
_calloc_dbg macro c, s, t, f, l
	exitm<calloc(c, s)>
	endm
_realloc_dbg macro p, s, t, f, l
	exitm<realloc(p, s)>
	endm
_recalloc_dbg macro p, c, s, t, f, l
	exitm<_recalloc(p, c, s)>
	endm
_expand_dbg macro p, s, t, f, l
	exitm<_expand(p, s)>
	endm
_free_dbg macro p, t
	exitm<free(p)>
	endm
_msize_dbg macro p, t
	exitm<_msize(p)>
	endm

_aligned_msize_dbg macro p, a, o
	exitm<_aligned_msize(p, a, o)>
	endm
_aligned_malloc_dbg macro s, a, f, l
	exitm<_aligned_malloc(s, a)>
	endm
_aligned_realloc_dbg macro p, s, a, f, l
	exitm<_aligned_realloc(p, s, a)>
	endm
_aligned_recalloc_dbg macro p, c, s, a, f, l
	exitm<_aligned_recalloc(p, c, s, a)>
	endm
_aligned_free_dbg macro p
	exitm<_aligned_free(p)>
	endm
_aligned_offset_malloc_dbg macro s, a, o, f, l
	exitm<_aligned_offset_malloc(s, a, o)>
	endm
_aligned_offset_realloc_dbg macro p, s, a, o, f, l
	exitm<_aligned_offset_realloc(p, s, a, o)>
	endm
_aligned_offset_recalloc_dbg macro p, c, s, a, o, f, l
	exitm<_aligned_offset_recalloc(p, c, s, a, o)>
	endm

_malloca_dbg macro s, t, f, l
	exitm<_malloca(s)>
	endm
_freea_dbg macro p, t
	exitm<_freea(p)>
	endm

_strdup_dbg macro s, t, f, l
	exitm<_strdup(s)>
	endm
_wcsdup_dbg macro s, t, f, l
	exitm<_wcsdup(s)>
	endm
_mbsdup_dbg macro s, t, f, l
	exitm<_mbsdup(s)>
	endm
_tempnam_dbg macro s1, s2, t, f, l
	exitm<_tempnam(s1, s2)>
	endm
_wtempnam_dbg macro s1, s2, t, f, l
	exitm<_wtempnam(s1, s2)>
	endm
_fullpath_dbg macro s1, s2, le, t, f, l
	exitm<_fullpath(s1, s2, le)>
	endm
_wfullpath_dbg macro s1, s2, le, t, f, l
	exitm<_wfullpath(s1, s2, le)>
	endm
_getcwd_dbg macro s, le, t, f, l
	exitm<_getcwd(s, le)>
	endm
_wgetcwd_dbg macro s, le, t, f, l
	exitm<_wgetcwd(s, le)>
	endm
_getdcwd_dbg macro d, s, le, t, f, l
	exitm<_getdcwd(d, s, le)>
	endm
_wgetdcwd_dbg macro d, s, le, t, f, l
	exitm<_wgetdcwd(d, s, le)>
	endm
_getdcwd_lk_dbg macro d, s, le, t, f, l
	exitm<_getdcwd(d, s, le)>
	endm
_wgetdcwd_lk_dbg macro d, s, le, t, f, l
	exitm<_wgetdcwd(d, s, le)>
	endm
_dupenv_s_dbg macro ps1, size, s2, t, f, l
	exitm<_dupenv_s(ps1, size, s2)>
	endm
_wdupenv_s_dbg macro ps1, size, s2, t, f, l
	exitm<_wdupenv_s(ps1, size, s2)>
	endm

_CrtSetReportHook macro f
	exitm<>
	endm
_CrtGetReportHook macro
	exitm<>
	endm
_CrtSetReportHook2 macro t, f
	exitm<>
	endm
_CrtSetReportHookW2 macro t, f
	exitm<>
	endm
_CrtSetReportMode macro t, f
	exitm<>
	endm
_CrtSetReportFile macro t, f
	exitm<>
	endm

_CrtDbgBreak macro
	exitm<>
	endm

_CrtSetBreakAlloc macro a
	exitm<>
	endm

_CrtSetAllocHook macro f
	exitm<>
	endm
_CrtGetAllocHook macro
	exitm<>
	endm

_CrtCheckMemory macro
	exitm<1>
	endm
_CrtSetDbgFlag macro f
	exitm<0>
	endm
_CrtDoForAllClientObjects macro f, c
	exitm<0>
	endm
_CrtIsValidPointer macro p, n, r
	exitm<1>
	endm
_CrtIsValidHeapPointer macro p
	exitm<1>
	endm
_CrtIsMemoryBlock macro p, t, r, f, l
	exitm<1>
	endm
_CrtReportBlockType macro p
	exitm<-1>
	endm

_CrtSetDumpClient macro f
	exitm<0>
	endm
_CrtGetDumpClient macro
	exitm<0>
	endm

_CrtMemCheckpoint macro s
	exitm<0>
	endm
_CrtMemDifference macro s1, s2, s3
	exitm<0>
	endm
_CrtMemDumpAllObjectsSince macro s
	exitm<0>
	endm
_CrtMemDumpStatistics macro s
	exitm<0>
	endm
_CrtDumpMemoryLeaks macro
	exitm<0>
	endm
_CrtSetDebugFillThreshold macro t
	exitm<0>
	endm

_CrtSetCheckCount macro f
	exitm<0>
	endm
_CrtGetCheckCount macro
	exitm<0>
	endm

else  ;; _DEBUG


ifndef _MRTIMP
if defined(MRTDLL) AND defined(_CRTBLD)
_MRTIMP equ <__declspec(dllexport)>
else
_MRTIMP equ <__declspec(dllimport)>
endif
endif

ifndef _CRTIMP
if defined(CRTDLL) AND defined(_CRTBLD)
_CRTIMP equ <__declspec(dllexport)>
else
ifdef _DLL
_CRTIMP equ <__declspec(dllimport)>
else
_CRTIMP equ <>
endif
endif
endif

ifdef _CRTBLD
if defined (_DLL) AND defined (_M_IX86)
__p__crtAssertBusy proto __cdecl
endif
endif

ifndef _M_CEE_PURE
externdef _crtAssertBusy:LONG
endif

ifndef _M_CEE_PURE
_CrtGetReportHook proto __cdecl
endif

ifndef _M_CEE_PURE
_CrtSetReportHook	proto __cdecl :_CRT_REPORT_HOOK
_CrtSetReportHook2	proto __cdecl :int_t, :_CRT_REPORT_HOOK
_CrtSetReportHookW2	proto __cdecl :int_t, :_CRT_REPORT_HOOKW
endif

_CrtSetReportMode	proto __cdecl :int_t, :int_t
_CrtSetReportFile	proto __cdecl :int_t, :_HFILE
_CrtDbgReport		proto __cdecl :int_t, :string_t, :int_t, :string_t, :string_t, :vararg
_CrtSetDebugFillThreshold proto __cdecl :size_t

if NOT defined (_NATIVE_WCHAR_T_DEFINED) AND defined (_M_CEE_PURE)
;externdef
endif
_CrtDbgReportW		proto __cdecl :int_t, :ptr wchar_t, :int_t, :ptr wchar_t, :ptr wchar_t

_ASSERT_EXPR macro expr, msg
	exitm<>
	endm

ifndef _ASSERT
_ASSERT macro expr
	exitm<_ASSERT_EXPR((expr), NULL)>
	endm
endif

ifndef _ASSERTE
_ASSERTE macro expr
	exitm<_ASSERT_EXPR((expr), _CRT_WIDE(#expr))>
	endm
endif

ifndef _ASSERT_BASE
_ASSERT_BASE		equ <_ASSERT_EXPR>
endif

_RPT_BASE macro args
	exitm<>
	endm

_RPT_BASE_W macro args
	exitm<>
	endm

_RPT0 macro rptno, msg
	exitm<_RPT_BASE(rptno, NULL, 0, NULL, "%s", msg)>
	endm

_RPTW0 macro rptno, msg
	exitm<_RPT_BASE_W((rptno, NULL, 0, NULL, L"%s", msg))>
	endm

_RPT1 macro rptno, msg, arg1
	exitm<_RPT_BASE((rptno, NULL, 0, NULL, msg, arg1))>
	endm

_RPTW1 macro rptno, msg, arg1
	exitm<_RPT_BASE_W((rptno, NULL, 0, NULL, msg, arg1))>
	endm

_RPT2 macro rptno, msg, arg1, arg2
	exitm<_RPT_BASE((rptno, NULL, 0, NULL, msg, arg1, arg2))>
	endm

_RPTW2 macro rptno, msg, arg1, arg2
	exitm<_RPT_BASE_W((rptno, NULL, 0, NULL, msg, arg1, arg2))>
	endm

_RPT3 macro rptno, msg, arg1, arg2, arg3
	exitm<_RPT_BASE((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3))>
	endm

_RPTW3 macro rptno, msg, arg1, arg2, arg3
	exitm<_RPT_BASE_W((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3))>
	endm

_RPT4 macro rptno, msg, arg1, arg2, arg3, arg4
	exitm<_RPT_BASE((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3, arg4))>
	endm

_RPTW4 macro rptno, msg, arg1, arg2, arg3, arg4
	exitm<_RPT_BASE_W((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3, arg4))>
	endm

_RPT5 macro rptno, msg, arg1, arg2, arg3, arg4, arg5
	exitm<_RPT_BASE((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3, arg4, arg5))>
	endm

_RPTW5 macro rptno, msg, arg1, arg2, arg3, arg4, arg5
	exitm<_RPT_BASE_W((rptno, NULL, 0, NULL, msg, arg1, arg2, arg3, arg4, arg5))>
	endm

_RPTF0 macro rptno, msg
	exitm<_RPT_BASE((rptno, @FileCur, @Line, NULL, "%s", msg))>
	endm

_RPTFW0 macro rptno, msg
	exitm<_RPT_BASE_W((rptno, _CRT_WIDE(@FileCur), @Line, NULL, L"%s", msg))>
	endm

_RPTF1 macro rptno, msg, arg1
	exitm<_RPT_BASE((rptno, @FileCur, @Line, NULL, msg, arg1))>
	endm

_RPTFW1 macro rptno, msg, arg1
	exitm<_RPT_BASE_W((rptno, _CRT_WIDE(@FileCur), @Line, NULL, msg, arg1))>
	endm

_RPTF2 macro rptno, msg, arg1, arg2
	exitm<_RPT_BASE((rptno, @FileCur, @Line, NULL, msg, arg1, arg2))>
	endm

_RPTFW2 macro rptno, msg, arg1, arg2
	exitm<_RPT_BASE_W((rptno, _CRT_WIDE(@FileCur), @Line, NULL, msg, arg1, arg2))>
	endm

_RPTF3 macro rptno, msg, arg1, arg2, arg3
	exitm<_RPT_BASE((rptno, @FileCur, @Line, NULL, msg, arg1, arg2, arg3))>
	endm

_RPTFW3 macro rptno, msg, arg1, arg2, arg3
	exitm<_RPT_BASE_W((rptno, _CRT_WIDE(@FileCur), @Line, NULL, msg, arg1, arg2, arg3))>
	endm

_RPTF4 macro rptno, msg, arg1, arg2, arg3, arg4
	exitm<_RPT_BASE((rptno,@FileCur, @Line, NULL, msg, arg1, arg2, arg3, arg4))>
	endm

_RPTFW4 macro rptno, msg, arg1, arg2, arg3, arg4
	exitm<_RPT_BASE_W((rptno, _CRT_WIDE(@FileCur), @Line, NULL, msg, arg1, arg2, arg3, arg4))>
	endm

_RPTF5 macro rptno, msg, arg1, arg2, arg3, arg4, arg5
	exitm<_RPT_BASE((rptno, @FileCur, @Line, NULL, msg, arg1, arg2, arg3, arg4, arg5))>
	endm

_RPTFW5 macro rptno, msg, arg1, arg2, arg3, arg4, arg5
	exitm<_RPT_BASE_W((rptno, _CRT_WIDE(@FileCur), @Line, NULL, msg, arg1, arg2, arg3, arg4, arg5))>
	endm

ifndef _CRT_PORTABLE
_CrtDbgBreak macro
	exitm<__debugbreak()>
	endm
else
_CrtDbgBreak proto __cdecl
endif

ifdef _CRTDBG_MAP_ALLOC

malloc macro s
	exitm<_malloc_dbg(s, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
calloc macro c, s
	exitm<_calloc_dbg(c, s, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
realloc macro p, s
	exitm<_realloc_dbg(p, s, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_recalloc macro p, c, s
	exitm<_recalloc_dbg(p, c, s, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_expand macro p, s
	exitm<_expand_dbg(p, s, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
free macro p
	exitm<_free_dbg(p, _NORMAL_BLOCK)>
	endm
_msize macro p
	exitm<_msize_dbg(p, _NORMAL_BLOCK)>
	endm
_aligned_msize macro p, a, o
	exitm<_aligned_msize_dbg(p, a, o)>
	endm
_aligned_malloc macro s, a
	exitm<_aligned_malloc_dbg(s, a, @FileCur, @Line)>
	endm
_aligned_realloc macro p, s, a
	exitm<_aligned_realloc_dbg(p, s, a, @FileCur, @Line)>
	endm
_aligned_recalloc macro p, c, s, a
	exitm<_aligned_recalloc_dbg(p, c, s, a, @FileCur, @Line)>
	endm
_aligned_offset_malloc macro s, a, o
	exitm<_aligned_offset_malloc_dbg(s, a, o, @FileCur, @Line)>
	endm
_aligned_offset_realloc macro p, s, a, o
	exitm<_aligned_offset_realloc_dbg(p, s, a, o, @FileCur, @Line)>
	endm
_aligned_offset_recalloc macro p, c, s, a, o
	exitm<_aligned_offset_recalloc_dbg(p, c, s, a, o, @FileCur, @Line)>
	endm
_aligned_free macro p
	exitm<_aligned_free_dbg(p)>
	endm

_malloca macro s
	exitm<_malloca_dbg(s, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_freea macro p
	exitm<_freea_dbg(p, _NORMAL_BLOCK)>
	endm

_strdup macro s
	exitm<_strdup_dbg(s, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_wcsdup macro s
	exitm<_wcsdup_dbg(s, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_mbsdup macro s
	exitm<_strdup_dbg(s, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_tempnam macro s1, s2
	exitm<_tempnam_dbg(s1, s2, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_wtempnam macro s1, s2
	exitm<_wtempnam_dbg(s1, s2, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_fullpath macro s1, s2, le
	exitm<_fullpath_dbg(s1, s2, le, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_wfullpath macro s1, s2, le
	exitm<_wfullpath_dbg(s1, s2, le, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_getcwd macro s, le
	exitm<_getcwd_dbg(s, le, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_wgetcwd macro s, le
	exitm<_wgetcwd_dbg(s, le, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_getdcwd macro d, s, le
	exitm<_getdcwd_dbg(d, s, le, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_wgetdcwd macro d, s, le
	exitm<_wgetdcwd_dbg(d, s, le, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_dupenv_s macro ps1, size, s2
	exitm<_dupenv_s_dbg(ps1, size, s2, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
_wdupenv_s macro ps1, size, s2
	exitm<_wdupenv_s_dbg(ps1, size, s2, _NORMAL_BLOCK, @FileCur, @Line)>
	endm

if (__STDC__ eq 0)
strdup macro s
	exitm<_strdup_dbg(s, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
wcsdup macro s
	exitm<_wcsdup_dbg(s, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
tempnam macro s1, s2
	exitm<_tempnam_dbg(s1, s2, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
getcwd macro s, le
	exitm<_getcwd_dbg(s, le, _NORMAL_BLOCK, @FileCur, @Line)>
	endm
endif


endif ;; _CRTDBG_MAP_ALLOC

ifdef _CRTBLD
if defined (_DLL) AND defined (_M_IX86)
__p__crtBreakAlloc proto __cdecl
endif
endif

ifndef _M_CEE_PURE
externdef _crtBreakAlloc:LONG
endif

_CrtSetBreakAlloc	proto __cdecl :LONG

_malloc_dbg		proto __cdecl :size_t, :int_t, :string_t, :int_t
_calloc_dbg		proto __cdecl :size_t, :size_t, :int_t, :string_t, :int_t
_realloc_dbg		proto __cdecl :ptr, :size_t, :int_t, :string_t, :int_t
_recalloc_dbg		proto __cdecl :ptr, :size_t, :size_t, :int_t, :string_t, :int_t
_expand_dbg		proto __cdecl :ptr, :size_t, :int_t, :string_t, :int_t
_free_dbg		proto __cdecl :ptr, :int_t
_msize_dbg		proto __cdecl :ptr, :int_t
_aligned_msize_dbg	proto __cdecl :ptr, :size_t, :size_t
_aligned_malloc_dbg	proto __cdecl :size_t, :size_t, :string_t, :int_t
_aligned_realloc_dbg	proto __cdecl :ptr, :size_t, :size_t, :string_t, :int_t
_aligned_recalloc_dbg	proto __cdecl :ptr, :size_t, :size_t, :size_t, :string_t, :int_t
_aligned_offset_malloc_dbg proto __cdecl :size_t, :size_t, :size_t, :string_t, :int_t
_aligned_offset_realloc_dbg proto __cdecl :ptr, :size_t, :size_t, :size_t, :string_t, :int_t
_aligned_offset_recalloc_dbg proto __cdecl :ptr, :size_t, :size_t, :size_t, :size_t, :string_t, :int_t
_aligned_free_dbg	proto __cdecl :ptr
_strdup_dbg		proto __cdecl :ptr, :int_t, :ptr, :int_t
_wcsdup_dbg		proto __cdecl :ptr wchar_t, :int_t, :string_t, :int_t
_tempnam_dbg		proto __cdecl :string_t, :string_t, :int_t, :string_t, :int_t
_wtempnam_dbg		proto __cdecl :ptr wchar_t, :ptr wchar_t, :int_t, :string_t, :int_t
_fullpath_dbg		proto __cdecl :string_t, :string_t, :size_t, :int_t, :string_t, :int_t
_wfullpath_dbg		proto __cdecl :ptr wchar_t, :ptr wchar_t, :size_t, :int_t, :string_t, :int_t
_getcwd_dbg		proto __cdecl :string_t, :int_t, :int_t, :string_t, :int_t
_wgetcwd_dbg		proto __cdecl :ptr wchar_t, :int_t, :int_t, :string_t, :int_t
_getdcwd_dbg		proto __cdecl :int_t, :string_t, :int_t, :int_t, :string_t, :int_t
_wgetdcwd_dbg		proto __cdecl :int_t, :ptr wchar_t, :int_t, :int_t, :string_t, :int_t
_getdcwd_lk_dbg		proto __cdecl :int_t, :string_t, :int_t, :int_t, :string_t, :int_t
_wgetdcwd_lk_dbg	proto __cdecl :int_t, :ptr wchar_t, :int_t, :int_t, :string_t, :int_t
_dupenv_s_dbg		proto __cdecl :ptr ptr, :ptr size_t, :string_t, :int_t, :string_t, :int_t
_wdupenv_s_dbg		proto __cdecl :ptr wchar_t, :ptr size_t, :ptr wchar_t, :int_t, :string_t, :int_t

_malloca_dbg macro s, t, f, l
	exitm<_malloc_dbg(s, t, f, l)>
	endm
_freea_dbg macro p, t
	exitm<_free_dbg(p, t)>
	endm

ifndef _M_CEE_PURE
_CrtGetAllocHook	proto __cdecl
endif

ifndef _M_CEE_PURE
_CrtSetAllocHook	proto __cdecl :_CRT_ALLOC_HOOK
endif

ifdef _CRTBLD
if defined (_DLL) AND defined (_M_IX86)
__p__crtDbgFlag		proto __cdecl
endif
endif

ifndef _M_CEE_PURE
externdef _crtDbgFlag:int_t
endif

_CrtCheckMemory		proto __cdecl
_CrtSetDbgFlag		proto __cdecl :int_t
_CrtDoForAllClientObjects proto __cdecl :ptr, :ptr
_CrtIsValidPointer	proto __cdecl :ptr, :uint_t, :int_t
_CrtIsValidHeapPointer	proto __cdecl :ptr
_CrtIsMemoryBlock	proto __cdecl :ptr, :dword, :ptr, :ptr, :ptr
_CrtReportBlockType	proto __cdecl :ptr

if NOT defined (_M_CEE_PURE)
_CrtGetDumpClient	proto __cdecl
endif

if NOT defined (_M_CEE_PURE)
_CrtSetDumpClient	proto __cdecl :_CRT_DUMP_CLIENT
endif

_CrtMemCheckpoint	proto __cdecl :ptr
_CrtMemDifference	proto __cdecl :ptr, :ptr, :ptr
_CrtMemDumpAllObjectsSince proto __cdecl :ptr
_CrtMemDumpStatistics	proto __cdecl :ptr
_CrtDumpMemoryLeaks	proto __cdecl
_CrtSetCheckCount	proto __cdecl :int_t
_CrtGetCheckCount	proto __cdecl

endif  ;; _DEBUG

;.pragma pop_macro("new")
.pragma pack(pop)

endif  ;; _INC_CRTDBG
