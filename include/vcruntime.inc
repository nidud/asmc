ifndef _VCRUNTIME_H
define _VCRUNTIME_H
include libc.inc
include sal.inc
include vadefs.inc

_CRT_BEGIN_C_HEADER macro
    .pragma(pack(push, _CRT_PACKING))
    endm
_CRT_END_C_HEADER macro
    .pragma(pack(pop))
    endm

ifndef _HAS_EXCEPTIONS
define _HAS_EXCEPTIONS
endif

_CRT_STRINGIZE_ macro x
    exitm<x>
    endm
_CRT_STRINGIZE macro x
    exitm<_CRT_STRINGIZE_(x)>
    endm

_CRT_WIDE_ macro s
    exitm<L&s&>
    endm
_CRT_WIDE macro s
    exitm<_CRT_WIDE_(s)>
    endm
_CRT_CONCATENATE_ macro a, b
    exitm<&a&&b&>
    endm

_CRT_CONCATENATE macro a, b
    exitm<_CRT_CONCATENATE_(a, b)>
    endm

_CRT_UNPARENTHESIZE_ macro args:vararg
    exitm<__VA_ARGS__>
    endm
_CRT_UNPARENTHESIZE macro args:vararg
    exitm<_CRT_UNPARENTHESIZE_(__VA_ARGS__)>
    endm

__CLRCALL_OR_CDECL  equ <__cdecl>
__CLR_OR_THIS_CALL  equ <>
__CLRCALL_PURE_OR_CDECL equ <__cdecl>
__CRTDECL equ <__CLRCALL_PURE_OR_CDECL>

_VCRT_NOALIAS       equ <__declspec(noalias)>
_VCRT_RESTRICT      equ <__declspec(restrict)>

if not defined(_MSC_VER) or _MSC_VER ge 1900
    _VCRT_ALLOCATOR equ <__declspec(allocator)>
else
    _VCRT_ALLOCATOR equ <>
endif

if defined(_M_CEE) and defined(_M_X64)
    _VCRT_JIT_INTRINSIC equ <__declspec(jitintrinsic)>
else
    _VCRT_JIT_INTRINSIC equ <>
endif

_VCRT_ALIGN macro x
    endm

__vcrt_bool typedef sdword;_Bool

__crt_countof macro _Array
    exitm<(lengthof(_Array))>
    endm

_CRT_DEPRECATE_TEXT macro __Text
    exitm<__declspec(deprecated(__Text))>
    endm

if defined(_CRT_SECURE_NO_DEPRECATE) and not defined(_CRT_SECURE_NO_WARNINGS)
    _CRT_SECURE_NO_WARNINGS equ <>
endif

ifndef _CRT_INSECURE_DEPRECATE
    _CRT_INSECURE_DEPRECATE macro _Replacement
    ifndef _CRT_SECURE_NO_WARNINGS
        _CRT_DEPRECATE_TEXT( \
            "This function or variable may be unsafe. Consider using " \
            _Replacement \
            " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. " \
            "See online help for details.")
    endif
    endm
endif

if defined(_CRT_SECURE_DEPRECATE_MEMORY) and not defined(_CRT_SECURE_WARNINGS_MEMORY)
    _CRT_SECURE_WARNINGS_MEMORY equ <>
endif

ifndef _CRT_INSECURE_DEPRECATE_MEMORY
    _CRT_INSECURE_DEPRECATE_MEMORY macro _Replacement
    ifdef _CRT_SECURE_WARNINGS_MEMORY
        _CRT_INSECURE_DEPRECATE(_Replacement)
    endif
    endm
endif

ifndef _M_CEE
    __security_init_cookie proto __cdecl

    ifdef _M_IX86
        __security_check_cookie proto fastcall _StackCookie:uintptr_t
        __report_gsfailure proto __cdecl
    else
        __security_check_cookie proto __cdecl _StackCookie:uintptr_t
        __report_gsfailure proto __cdecl _StackCookie:uintptr_t
    endif
endif

externdef __security_cookie:uintptr_t

ifndef _VCRT_BUILD
    __vcrt_malloc_normal macro _Size
        exitm<malloc(_Size)>
        endm
    __vcrt_calloc_normal macro _Count, _Size
        exitm<calloc(_Count, _Size)>
        endm
    __vcrt_free_normal macro _Memory
        exitm<free(_Memory)>
        endm
endif

endif
