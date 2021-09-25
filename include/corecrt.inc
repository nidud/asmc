include vcruntime.inc

ifdef __cplusplus
__crt_bool    typedef BOOL
elseifdef __midl
__crt_bool    typedef char_t
else
__crt_bool    typedef int_t
endif

_ARGMAX         equ 100
_TRUNCATE       equ -1
_CRT_INT_MAX    equ 2147483647
_CRT_SIZE_MAX   equ -1

__FILEW__     equ <_CRT_WIDE(__FILE__)>
__FUNCTIONW__ equ <_CRT_WIDE(__FUNCTION__)>

ifndef _STATIC_ASSERT
    _STATIC_ASSERT macro expr
        ;typedef char __static_assert_t[(expr) != 0]
        exitm<>
        endm
endif

ifndef NULL
NULL equ 0
endif

ifndef _CRT_FUNCTIONS_REQUIRED
    if defined(__assembler) or defined(__midl) or defined(RC_INVOKED)
        _CRT_FUNCTIONS_REQUIRED equ 0
    else
        _CRT_FUNCTIONS_REQUIRED equ 1
    endif
endif

if not defined(_NO_INLINING) and not _CRT_FUNCTIONS_REQUIRED
define _NO_INLINING ;; Suppress <tchar.h> inlines
endif

ifndef _CRT_UNUSED
    _CRT_UNUSED macro x
        exitm<>
        endm
endif

ifndef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
    ifdef WINAPI_FAMILY
        include winapifamily.inc
        if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
            define _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
        else
            ifdef WINAPI_FAMILY_PHONE_APP
                if WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
                    define _CRT_USE_WINAPI_FAMILY_PHONE_APP
                endif
            endif
        endif
    else
        define _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
    endif
endif

ifndef _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE
    _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE equ 0
endif

ifndef _CRT_BUILD_DESKTOP_APP
    ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
        _CRT_BUILD_DESKTOP_APP equ 1
    else
        _CRT_BUILD_DESKTOP_APP equ 0
    endif
endif

ifdef _M_ARM
    if _CRT_BUILD_DESKTOP_APP && !_ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE
        #error Compiling Desktop applications for the ARM platform is not supported.
    endif
endif



ifdef _DEBUG
_invalid_parameter proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :uint_t, :uintptr_t
endif

_invalid_parameter_noinfo macro
    exitm<>
    endm
_invalid_parameter_noinfo_noreturn macro
    exitm<>
    endm

_invoke_watson proto __cdecl :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :uint_t, :uintptr_t

ifndef _CRT_SECURE_INVALID_PARAMETER
    _CRT_SECURE_INVALID_PARAMETER macro expr
    ifdef _DEBUG
        _invalid_parameter(_CRT_WIDE(expr), __FUNCTIONW__, __FILEW__, __LINE__, 0)
    else
        _invalid_parameter_noinfo_noreturn()
    endif
    exitm<>
    endm
endif

_CRT_INTERNAL_NONSTDC_NAMES macro
    exitm<(defined(_CRT_DECLARE_NONSTDC_NAMES) and _CRT_DECLARE_NONSTDC_NAMES) or \
          (not defined(_CRT_DECLARE_NONSTDC_NAMES) and not __STDC__)>
    endm

if defined(_CRT_NONSTDC_NO_DEPRECATE) and not defined(_CRT_NONSTDC_NO_WARNINGS)
    define _CRT_NONSTDC_NO_WARNINGS
endif

ifndef _CRT_NONSTDC_DEPRECATE
    ifdef _CRT_NONSTDC_NO_WARNINGS
        _CRT_NONSTDC_DEPRECATE macro _NewName
            endm
    else
        _CRT_NONSTDC_DEPRECATE macro _NewName
            ;"The POSIX name for this item is deprecated. Instead, use the ISO C " \
            ;"and C++ conformant name: " #_NewName ". See online help for details.")
            endm
    endif
endif


ifndef _PGLOBAL
    ifdef _M_CEE
        ifdef __cplusplus_cli
            _PGLOBAL equ <__declspec(process)>
        else
            _PGLOBAL equ <>
        endif
    else
        _PGLOBAL equ <>
    endif
endif

ifndef _AGLOBAL
    ifdef _M_CEE
        _AGLOBAL equ <__declspec(appdomain)>
    else
        _AGLOBAL equ <>
    endif
endif

if defined(_M_CEE) and not defined(_M_CEE_PURE)
    _M_CEE_MIXED equ <>
endif



if defined(_CRTBLD) or defined(_CORECRT_BUILD) or defined(_VCRT_BUILD)

    _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES       equ 0
    _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT equ 0
    _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES         equ 0
endif

if _CRT_FUNCTIONS_REQUIRED eq 0

    undef  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
    undef  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT
    undef  _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
    undef  _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY
    undef  _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY

    _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES         equ 0
    _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT   equ 0
    _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES           equ 0
    _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY  equ 0
    _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY    equ 0
endif

__STDC_SECURE_LIB__ equ 200411
__GOT_SECURE_LIB__  equ __STDC_SECURE_LIB__ ;; For backwards compatibility

ifndef __STDC_WANT_SECURE_LIB__
define __STDC_WANT_SECURE_LIB__
endif

if not __STDC_WANT_SECURE_LIB__ and not defined(_CRT_SECURE_NO_WARNINGS)
    _CRT_SECURE_NO_WARNINGS equ 1
endif

ifndef RC_INVOKED
    if defined(_CRT_SECURE_NO_DEPRECATE_GLOBALS) and not defined(_CRT_SECURE_NO_WARNINGS_GLOBALS)
        define _CRT_SECURE_NO_WARNINGS_GLOBALS
    endif
endif

ifndef _CRT_INSECURE_DEPRECATE_GLOBALS
    ifdef RC_INVOKED
        _CRT_INSECURE_DEPRECATE_GLOBALS macro replacement
            endm
    else
        ifdef _CRT_SECURE_NO_WARNINGS_GLOBALS
            _CRT_INSECURE_DEPRECATE_GLOBALS macro replacement
                endm
        else
            _CRT_INSECURE_DEPRECATE_GLOBALS macro replacement
                exitm<_CRT_INSECURE_DEPRECATE(replacement)>
                endm
        endif
    endif
endif

if defined(_CRT_MANAGED_HEAP_NO_DEPRECATE) and not defined(_CRT_MANAGED_HEAP_NO_WARNINGS)
    define _CRT_MANAGED_HEAP_NO_WARNINGS
endif

_SECURECRT_FILL_BUFFER_PATTERN equ 0xFE

if defined(_CRT_OBSOLETE_NO_DEPRECATE) and not defined(_CRT_OBSOLETE_NO_WARNINGS)
    define _CRT_OBSOLETE_NO_WARNINGS
endif

ifndef _CRT_OBSOLETE
    ifdef _CRT_OBSOLETE_NO_WARNINGS
        _CRT_OBSOLETE macro _NewItem
            endm
    else
        _CRT_OBSOLETE maxro _NewItem
            endm
    endif
endif

ifndef RC_INVOKED
    ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
        _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES equ 0
    else
        if not __STDC_WANT_SECURE_LIB__ and _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
            .err <Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0>
        endif
    endif

    ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT
        _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT equ 0
    else
        if not __STDC_WANT_SECURE_LIB__ and _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT
            .err <Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0>
        endif
    endif

    ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
        if __STDC_WANT_SECURE_LIB__
              _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES equ 1
        else
              _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES equ 0
        endif
    else
        if not __STDC_WANT_SECURE_LIB__ and _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
            .err <Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0>
        endif
    endif

    ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY
        _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY equ 0
    else
        if not __STDC_WANT_SECURE_LIB__ and _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY
            .err <Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0>
        endif
    endif

    ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY
        _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY equ 0
    else
        if not __STDC_WANT_SECURE_LIB__ and _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY
           .err <Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0>
        endif
    endif
endif

ifndef _CRT_SECURE_CPP_NOTHROW
    _CRT_SECURE_CPP_NOTHROW <throw()>
endif



errno_t     typedef sdword
wint_t      typedef word
wctype_t    typedef word
__time32_t  typedef sdword
__time64_t  typedef sqword

__crt_locale_data_public struct
_locale_pctype          ptr_t ?
_locale_mb_cur_max      int_t ?
_locale_lc_codepage     uint_t ?
__crt_locale_data_public ends

__crt_locale_pointers   struct
locinfo                 ptr_t ?
mbcinfo                 ptr_t ?
__crt_locale_pointers   ends
;_locale_t               typedef ptr __crt_locale_pointers

_Mbstatet               struct
_Wchar                  dd ?
_Byte                   dw ?
_State                  dw ?
_Mbstatet               ends
mbstate_t               typedef _Mbstatet

if defined(_USE_32BIT_TIME_T) and defined(_WIN64)
    .err <You cannot use 32-bit time_t (_USE_32BIT_TIME_T) with _WIN64>
endif

if defined(_VCRT_BUILD) or defined(_CORECRT_BUILD)
    define _CRT_NO_TIME_T
endif

ifndef _CRT_NO_TIME_T
    ifdef _USE_32BIT_TIME_T
        time_t typedef __time32_t
    else
        time_t typedef __time64_t
    endif
endif

ifndef _TIME_T_DEFINED
define _TIME_T_DEFINED
endif

if __STDC_WANT_SECURE_LIB__
    rsize_t typedef size_t
endif

ifndef RC_INVOKED
    if defined(__cplusplus) and _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
    else
    endif
endif

ifndef RC_INVOKED
    if defined(__cplusplus) and _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
    endif
endif
