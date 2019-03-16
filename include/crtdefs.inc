include libc.inc

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

ifndef _INC_CRTDEFS
_INC_CRTDEFS equ <>

ifdef _CRTBLD

_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES equ 0
_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT equ 0
_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES equ 0

endif

ifdef __midl
undef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
undef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT
undef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
undef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY
undef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY
_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES equ 0
_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT equ 0
_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES equ 0
_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY equ 0
_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY equ 0
endif

ifndef _WIN32
.err <ERROR: Only Win32 target supported>
endif

include sal.inc

undef _CRT_PACKING
_CRT_PACKING equ 8

.pragma pack(push, _CRT_PACKING)

include vadefs.inc

ifndef _CRT_STRINGIZE
__CRT_STRINGIZE macro _Value
	exitm<&_Value>
	endm
_CRT_STRINGIZE macro _Value
	exitm<__CRT_STRINGIZE(_Value)>
	endm
endif

ifndef _CRT_WIDE
__CRT_WIDE macro _String
	exitm<L&_String&>
	endm
_CRT_WIDE macro _String
	exitm<__CRT_WIDE(_String)>
	endm
endif

ifndef _CRT_APPEND
__CRT_APPEND macro _Value1, _Value2
	exitm<&_Value1&&_Value2&>
	endm
_CRT_APPEND macro _Value1, _Value2
	exitm<__CRT_APPEND(_Value1, _Value2)>
	endm
endif

ifndef _W64
if NOT defined (__midl) AND (defined (_X86_) OR defined (_M_IX86))
_W64 equ __w64
else
_W64 equ <>
endif
endif

ifdef _CRTBLD
ifndef _CRTIMP1
ifdef CRTDLL1
_CRTIMP1 equ <__declspec(dllexport)>
else
_CRTIMP1 equ <_CRTIMP>
endif
endif
endif

ifndef _CRTIMP2
if defined (CRTDLL2) AND defined (_CRTBLD)
_CRTIMP2 equ <__declspec(dllexport)>
else
if defined (_DLL) AND NOT defined (_STATIC_CPPLIB)
_CRTIMP2 equ <__declspec(dllimport)>
else
_CRTIMP2 equ <>
endif
endif
endif

_CRTIMP_ALTERNATIVE equ <__declspec(dllimport)>
_CRTIMP_ALTERNATIVE equ <>

ifndef _CRTIMP_ALTERNATIVE
if defined(CRTDLL) AND defined(_CRTBLD)
ifdef _SAFECRT_IMPL
_CRTIMP_ALTERNATIVE equ <>
else
_CRTIMP_ALTERNATIVE equ <__declspec(dllexport)>
endif
else
ifdef _DLL
ifdef _CRT_ALTERNATIVE_INLINES
_CRTIMP_ALTERNATIVE equ <>
else
_CRTIMP_ALTERNATIVE equ <_CRTIMP>
_CRT_ALTERNATIVE_IMPORTED equ 1
endif
else
_CRTIMP_ALTERNATIVE equ <>
endif
endif
endif

ifndef _MRTIMP
if defined(MRTDLL) AND defined(_CRTBLD)
ifndef _M_CEE_PURE
_MRTIMP equ <__declspec(dllexport)>
else
_MRTIMP equ <>
endif
else
_MRTIMP equ <__declspec(dllimport)>
endif
endif

ifndef _MRTIMP2
if defined (CRTDLL2) AND defined(_CRTBLD)
_MRTIMP2 equ <__declspec(dllexport)>
elseif defined (MRTDLL) AND defined(_CRTBLD)
_MRTIMP2 equ <_MRTIMP>
else
if defined (_DLL) AND NOT defined (_STATIC_CPPLIB)
_MRTIMP2 equ <__declspec(dllimport)>
else
_MRTIMP2 equ <>
endif
endif
endif

ifndef _USE_32BIT_TIME_T
ifndef _WIN64
_USE_32BIT_TIME_T equ <>
endif
endif

ifndef __CLR_OR_THIS_CALL
if defined (MRTDLL) OR defined (_M_CEE_PURE)
__CLR_OR_THIS_CALL equ <__clrcall>
else
__CLR_OR_THIS_CALL equ <>
endif
endif

ifndef __CLRCALL_OR_CDECL
if defined (MRTDLL) OR defined (_M_CEE_PURE)
__CLRCALL_OR_CDECL equ <__clrcall>
else
__CLRCALL_OR_CDECL equ <__cdecl>
endif
endif

ifndef _CRTIMP_PURE
if defined (_M_CEE_PURE) OR defined (_STATIC_CPPLIB)
_CRTIMP_PURE equ <>
elseif defined (MRTDLL) AND defined (_CRTBLD)
_CRTIMP_PURE equ <>
else
_CRTIMP_PURE equ <_CRTIMP>
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

ifdef _GUARDOVERFLOW_CRT_ALLOCATORS
_CRT_GUARDOVERFLOW equ <__declspec(guard(overflow))>
else
_CRT_GUARDOVERFLOW equ <>
endif

ifdef _M_CEE
ifndef _M_CEE_PURE
_M_CEE_MIXED equ <>
endif
endif

__STDC_SECURE_LIB__	equ 200411
__GOT_SECURE_LIB__	equ __STDC_SECURE_LIB__

ifndef __STDC_WANT_SECURE_LIB__
__STDC_WANT_SECURE_LIB__ equ 1
endif
if ( __STDC_WANT_SECURE_LIB__ eq 0 ) AND ( defined(_CRT_SECURE_NO_WARNINGS) eq 0 )
_CRT_SECURE_NO_WARNINGS equ 1
endif

_CRT_DEPRECATE_TEXT macro _Text
	exitm<__declspec(deprecated(_Text))>
	endm

ifdef _CRT_SECURE_NO_DEPRECATE
ifndef _CRT_SECURE_NO_WARNINGS
_CRT_SECURE_NO_WARNINGS equ 1
endif
endif

ifndef _CRT_INSECURE_DEPRECATE
ifdef _CRT_SECURE_NO_WARNINGS
_CRT_INSECURE_DEPRECATE macro _Replacement
	exitm<>
	endm
else
_CRT_INSECURE_DEPRECATE macro _Replacement
	exitm<_CRT_DEPRECATE_TEXT("This function or variable may be unsafe. Consider using " #_Replacement " instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.")>
	endm
endif
endif

if defined (_CRT_SECURE_DEPRECATE_MEMORY) AND NOT defined (_CRT_SECURE_WARNINGS_MEMORY)
_CRT_SECURE_WARNINGS_MEMORY equ 1
endif

ifndef _CRT_INSECURE_DEPRECATE_MEMORY
ifndef _CRT_SECURE_WARNINGS_MEMORY
_CRT_INSECURE_DEPRECATE_MEMORY macro _Replacement
	exitm<>
	endm
else
_CRT_INSECURE_DEPRECATE_MEMORY macro _Replacement
	exitm<_CRT_INSECURE_DEPRECATE(_Replacement)>
	endm
endif
endif

ifndef RC_INVOKED
if defined (_CRT_SECURE_NO_DEPRECATE_GLOBALS) AND NOT defined (_CRT_SECURE_NO_WARNINGS_GLOBALS)
_CRT_SECURE_NO_WARNINGS_GLOBALS equ 1
endif
endif

ifndef _CRT_INSECURE_DEPRECATE_GLOBALS
ifndef RC_INVOKED
_CRT_INSECURE_DEPRECATE_GLOBALS macro _Replacement
	exitm<>
	endm
else
ifdef _CRT_SECURE_NO_WARNINGS_GLOBALS
_CRT_INSECURE_DEPRECATE_GLOBALS macro _Replacement
	exitm<>
	endm
else
_CRT_INSECURE_DEPRECATE_GLOBALS macro _Replacement
	exitm<_CRT_INSECURE_DEPRECATE(_Replacement)>
	endm
endif
endif
endif

if defined (_CRT_MANAGED_HEAP_NO_DEPRECATE) AND NOT defined (_CRT_MANAGED_HEAP_NO_WARNINGS)
_CRT_MANAGED_HEAP_NO_WARNINGS equ 1
endif

ifndef _CRT_MANAGED_HEAP_DEPRECATE
ifdef _CRT_MANAGED_HEAP_NO_WARNINGS
_CRT_MANAGED_HEAP_DEPRECATE equ 1
else
if defined (_M_CEE)
_CRT_MANAGED_HEAP_DEPRECATE equ 1
_CRT_DEPRECATE_TEXT("Direct heap access is not safely possible from managed code.")
else
_CRT_MANAGED_HEAP_DEPRECATE equ 1
endif
endif
endif

_SECURECRT_FILL_BUFFER_PATTERN equ 0xFE

ifdef _CRTBLD
_CRT_OBSOLETE macro _NewItem
	exitm<>
	endm
else

if defined (_CRT_OBSOLETE_NO_DEPRECATE) AND NOT defined (_CRT_OBSOLETE_NO_WARNINGS)
_CRT_OBSOLETE_NO_WARNINGS equ 1
endif

ifndef _CRT_OBSOLETE
ifdef _CRT_OBSOLETE_NO_WARNINGS
_CRT_OBSOLETE macro _NewItem
	exitm<>
	endm
else
_CRT_OBSOLETE macro _NewItem
	exitm<_CRT_DEPRECATE_TEXT("This function or variable has been superceded by newer library or operating system functionality. Consider using &_NewItem& instead. See online help for details.")>
	endm
endif
endif

endif

ifndef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
ifdef WINAPI_FAMILY
include winapifamily.inc
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
_CRT_USE_WINAPI_FAMILY_DESKTOP_APP equ 1
else
ifdef WINAPI_FAMILY_PHONE_APP
if WINAPI_FAMILY EQ WINAPI_FAMILY_PHONE_APP
_CRT_USE_WINAPI_FAMILY_PHONE_APP equ 1
endif
endif
endif
else
_CRT_USE_WINAPI_FAMILY_DESKTOP_APP equ 1
endif
endif

ifndef _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE
_ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE equ 0
endif

ifndef _CRT_BUILD_DESKTOP_APP
ifdef _CRT_USE_WINAPI_FAMILY_DESKTOP_APP
_CRT_BUILD_DESKTOP_APP	equ 1
else
_CRT_BUILD_DESKTOP_APP	equ 0
endif
endif

ifdef _M_ARM
if _CRT_BUILD_DESKTOP_APP AND NOT _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE
.err <Compiling Desktop applications for the ARM platform is not supported.>
endif
endif

ifndef _CRT_JIT_INTRINSIC
if defined (_M_CEE) AND defined (_M_X64)
_CRT_JIT_INTRINSIC equ <__declspec(jitintrinsic)>
else
_CRT_JIT_INTRINSIC equ <>
endif
endif

ifndef RC_INVOKED
ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES equ 0
else
if ( __STDC_WANT_SECURE_LIB__ eq 0 ) AND _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
.err <Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0>
endif
endif
endif

ifndef RC_INVOKED
ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT
_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT equ 0
else
if NOT __STDC_WANT_SECURE_LIB__ AND _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT
.err <Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0>
endif
endif
endif

ifndef RC_INVOKED
ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
if __STDC_WANT_SECURE_LIB__
_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES equ 1
else
_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES equ 0
endif
else
if NOT __STDC_WANT_SECURE_LIB__ AND _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
error Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0
endif
endif
endif

ifndef RC_INVOKED
ifndef _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY
_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY equ 0
else
if NOT __STDC_WANT_SECURE_LIB__ AND _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_MEMORY
error Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0
endif
endif
endif

ifndef RC_INVOKED
ifndef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY
_CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY equ 0
else
if NOT __STDC_WANT_SECURE_LIB__ AND _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES_MEMORY
.err <Cannot use Secure CRT C++ overloads when __STDC_WANT_SECURE_LIB__ is 0>
endif
endif
endif

ifndef _CRT_SECURE_CPP_NOTHROW
_CRT_SECURE_CPP_NOTHROW equ <throw()>
endif

if defined (_CRT_NONSTDC_NO_DEPRECATE) AND NOT defined (_CRT_NONSTDC_NO_WARNINGS)
_CRT_NONSTDC_NO_WARNINGS equ 1
endif

ifndef _CRT_NONSTDC_DEPRECATE
ifdef _CRT_NONSTDC_NO_WARNINGS
_CRT_NONSTDC_DEPRECATE macro _NewName
	exitm<>
	endm
else
_CRT_NONSTDC_DEPRECATE macro _NewName
	exitm<_CRT_DEPRECATE_TEXT("The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name: &_NewName&. See online help for details.")>
	endm
endif
endif

ifndef _SIZE_T_DEFINED
ifdef _WIN64
size_t typedef qword
else
size_t typedef dword
endif
_SIZE_T_DEFINED equ 1
endif

if __STDC_WANT_SECURE_LIB__
ifndef _RSIZE_T_DEFINED
rsize_t typedef size_t
_RSIZE_T_DEFINED equ 1
endif
endif

ifndef _INTPTR_T_DEFINED
ifdef _WIN64
intptr_t typedef sqword
else
intptr_t typedef sdword
endif
_INTPTR_T_DEFINED equ 1
endif

ifndef _UINTPTR_T_DEFINED
ifdef _WIN64
uintptr_t typedef qword
else
uintptr_t typedef dword
endif
_UINTPTR_T_DEFINED equ 1
endif

ifndef _PTRDIFF_T_DEFINED
ifdef _WIN64
ptrdiff_t typedef sqword
else
ptrdiff_t typedef sdword
endif
_PTRDIFF_T_DEFINED equ 1
endif

ifndef _WCHAR_T_DEFINED
wchar_t typedef word
_WCHAR_T_DEFINED equ 1
endif

ifndef _WCTYPE_T_DEFINED
wint_t typedef word
wctype_t typedef word
_WCTYPE_T_DEFINED equ 1
endif

ifndef _VA_LIST_DEFINED
ifdef _M_CEE_PURE
va_list typedef System::ArgIterator
else
va_list typedef ptr sbyte
endif
_VA_LIST_DEFINED equ 1
endif

ifdef _USE_32BIT_TIME_T
ifdef _WIN64
.err <You cannot use 32-bit time_t (_USE_32BIT_TIME_T) with _WIN64>
endif
endif

ifndef _ERRNO_T_DEFINED
_ERRNO_T_DEFINED equ 1
errno_t typedef sdword
endif

ifndef _TIME32_T_DEFINED
__time32_t typedef sdword
_TIME32_T_DEFINED equ 1
endif

ifndef _TIME64_T_DEFINED
__time64_t typedef sqword
_TIME64_T_DEFINED equ 1
endif

ifndef _TIME_T_DEFINED
_TIME_T_DEFINED equ <>
ifdef _WIN64
time_t		typedef sqword
else
time_t		typedef sdword
endif
endif

ifndef _CONST_RETURN
ifdef __cplusplus
_CONST_RETURN equ <const>
_CRT_CONST_CORRECT_OVERLOADS equ 1
else
_CONST_RETURN equ <>
endif
endif

if defined (_M_X64) OR defined (_M_ARM)
_UNALIGNED equ <__unaligned>
else
_UNALIGNED equ <>
endif

ifndef _CRT_ALIGN
ifdef __midl
_CRT_ALIGN macro x
	exitm<>
	endm
else
_CRT_ALIGN macro x
	exitm<__declspec(align(x))>
	endm
endif
endif

ifndef _CRTNOALIAS
_CRTNOALIAS equ <__declspec(noalias)>
endif

ifndef _CRTRESTRICT
_CRTRESTRICT equ <__declspec(restrict)>
endif

ifndef __CRTDECL
ifdef _M_CEE_PURE
__CRTDECL equ <>
else
__CRTDECL equ <__cdecl>
endif
endif

__STR2WSTR macro string
	exitm<L"&string&">
	endm
_STR2WSTR macro string
	exitm<__STR2WSTR(string)>
	endm

__FILEW__     equ <_STR2WSTR(__FILE__)>
__FUNCTIONW__ equ <_STR2WSTR(__FUNCTION__)>

ifdef _DEBUG
_invalid_parameter proto _CRTIMP :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :dword, :uintptr_t
else
_invalid_parameter_noinfo proto _CRTIMP
_invalid_parameter_noinfo_noreturn proto _CRTIMP
endif

;_CRTIMP __declspec(noreturn)
;void
_invoke_watson proto WINAPI \
		      : ptr wchar_t,
		      : ptr wchar_t,
		      : ptr wchar_t,
		      : dword,
		      : uintptr_t


ifdef _DEBUG
ifndef _CRT_SECURE_INVALID_PARAMETER
_CRT_SECURE_INVALID_PARAMETER macro expr
	exitm<::_invalid_parameter(__STR2WSTR(expr), __FUNCTIONW__, __FILEW__, __LINE__, 0)>
	endm
endif
else

ifndef _CRT_SECURE_INVALID_PARAMETER
_CRT_SECURE_INVALID_PARAMETER macro expr
	exitm<::_invalid_parameter_noinfo_noreturn()>
	endm
endif
endif

ifdef _CRTBLD
__UPDATE_LOCALE macro ptd, ptloci
	mov rax,ptloci
	mov ecx,ptd._ownlocale
	.if ( ( rax != __ptlocinfo ) && !( ecx & __globallocalestatus ) )
	    mov ptloci,__updatetlocinfo()
	.endif
	retm<>
	endm
__UPDATE_MBCP macro ptd, ptmbci
	mov rax,ptmbci
	mov ecx,ptd._ownlocale
	.if ( ( rax != __ptmbcinfo ) && !( ecx & __globallocalestatus ) )
	    mov ptmbci,__updatetmbcinfo()
	.endif
	retm<>
	endm
ifndef _DEFINE_SET_FUNCTION
_DEFINE_SET_FUNCTION macro _FuncName, _Type, _VarName
	exitm<>
	endm
endif
endif

_ARGMAX equ 100

ifndef _TRUNCATE
_TRUNCATE equ (-1)
endif

ifndef RC_INVOKED
if defined (__cplusplus) AND _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0 macro _ReturnType, _FuncName, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1 macro _ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2 macro _ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3 macro _ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4 macro _ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1 macro _ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2 macro _ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3 macro _ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0 macro _ReturnType, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST macro _ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST macro _ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH macro _ReturnType, _FuncName, _DstType, _Src
	exitm<>
	endm
else

__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_0 macro _ReturnType, _FuncName, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1 macro _ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2 macro _ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_3 macro _ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_4 macro _ReturnType, _FuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_1 macro _ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_2 macro _ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_1_3 macro _ReturnType, _FuncName, _HType1, _HArg1, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_2_0 macro _ReturnType, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_1_ARGLIST macro _ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_0_2_ARGLIST macro _ReturnType, _FuncName, _VFuncName, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_SECURE_FUNC_SPLITPATH macro _ReturnType, _FuncName, _DstType, _Src
	exitm<>
	endm

endif ;; defined (__cplusplus) AND _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
endif ;; NOT defined (RC_INVOKED)

__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, &_FuncName&_s, _SalAttributeDst, _DstType, _Dst)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, &_FuncName&_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _VFuncName, _VFuncName##_s, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _VFuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE macro _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE macro _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _SalAttributeDst, _DstType, _Dst)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _SalAttributeDst, _DstType, _DstType, _Dst, _TType1, _TArg1)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX(_ReturnType,_ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0 macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _FuncName##_s, _VFuncName, _VFuncName##_s, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE macro _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE macro _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _FuncName##_s, _DstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)>
	endm

ifndef RC_INVOKED
if defined (__cplusplus) AND _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES

__RETURN_POLICY_SAME macro _FunctionCall, _Dst
	exitm<return (_FunctionCall)>
	endm
__RETURN_POLICY_DST macro _FunctionCall, _Dst
	exitm<return ((_FunctionCall) EQ 0 ? _Dst : 0)>
	endm
__RETURN_POLICY_VOID macro _FunctionCall, _Dst
	exitm<(_FunctionCall); return>
	endm
__EMPTY_DECLSPEC equ 1

__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS macro _ReturnType, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureVFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX macro _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX macro _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst
	exitm<>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm

if NOT defined (RC_INVOKED) AND _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT

__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_CGETS macro _ReturnType, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS(_ReturnType, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX(_ReturnType,_ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX(_ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _VFuncName##_s, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX macro _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX macro _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX(_DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst
	exitm<__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType _DstType, _Dst)>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst
	exitm<__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst)>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1
	exitm<__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType _DstType, _Dst, _TType1, _TArg1)>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1
	exitm<__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1)>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX(_ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2)>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(_ReturnType,_ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX(_ReturnType,_ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3)>
	endm

else ;; NOT defined (RC_INVOKED) AND _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT

__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst
	exitm<_CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _FuncName proto __cdecl _Dst:ptr>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_GETS macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst
	exitm<_CRT_INSECURE_DEPRECATE(_FuncName##_s) _DeclSpec _ReturnType __cdecl _FuncName(_DstType *_Dst)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<_CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<_CRT_INSECURE_DEPRECATE(_SecureFuncName) _DeclSpec _ReturnType __cdecl _FuncName(_SalAttributeDst _DstType *_Dst, _TType1 _TArg1, _TType2 _TArg2)>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName,_VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX macro _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX macro _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst
	exitm<>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm

endif ;; NOT defined (RC_INVOKED) AND _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT

else  ;; defined (__cplusplus) AND _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES

__RETURN_POLICY_SAME macro _FunctionCall
	exitm<>
	endm
__RETURN_POLICY_DST macro _FunctionCall
	exitm<>
	endm
__RETURN_POLICY_VOID macro _FunctionCall
	exitm<>
	endm
__EMPTY_DECLSPEC equ 1

__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_0_CGETS macro _ReturnType, _DeclSpec, _FuncName, _SalAttributeDst, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_4_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_1_1_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_2_0_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_1_ARGLIST_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_ARGLIST_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureVFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_2_SIZE_EX macro _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_FUNC_0_3_SIZE_EX macro _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_0_GETS macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_4_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3, _TType4, _TArg4
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_1_1_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_2_0_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _HType1, _HArg1, _HType2, _HArg2, _SalAttributeDst, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_1_ARGLIST_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _SecureFuncName, _VFuncName, _SecureVFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_ARGLIST_EX macro _ReturnType, _ReturnPolicy, _DeclSpec, _FuncName, _VFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_2_SIZE_EX macro _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_STANDARD_NFUNC_0_3_SIZE_EX macro _DeclSpec, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst
	exitm<>
	endm

__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm

__DECLARE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_FUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_0_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst
	exitm<>
	endm

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_1_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1
	exitm<>
	endm

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_2_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2
	exitm<>
	endm

__DECLARE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm
__DEFINE_CPP_OVERLOAD_INLINE_NFUNC_0_3_EX macro _ReturnType, _ReturnPolicy, _FuncName, _SecureFuncName, _SecureDstType, _SalAttributeDst, _DstType, _Dst, _TType1, _TArg1, _TType2, _TArg2, _TType3, _TArg3
	exitm<>
	endm

endif ;; defined (__cplusplus) AND _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES
endif ;; NOT defined (RC_INVOKED)

pthreadlocinfo		typedef ptr threadlocinfo
pthreadmbcinfo		typedef ptr threadmbcinfo

_locale_tstruct		STRUC
locinfo			pthreadlocinfo ?
mbcinfo			pthreadmbcinfo ?
_locale_tstruct		ENDS
_locale_t		typedef ptr _locale_tstruct

ifndef _THREADLOCALEINFO
_THREADLOCALEINFO equ <>

ifndef LPSHORT
LPINT			typedef ptr sdword
LPSHORT			typedef ptr sword
endif
locrefcount		STRUC
locale			LPSTR ?
wlocale			LPWSTR ?
refcount		LPINT ?
wrefcount		LPINT ?
locrefcount		ENDS

threadlocinfo		STRUC
refcount		SINT ?
lc_codepage		dd ?
lc_collate_cp		dd ?
lc_time_cp		dd ?
lc_category		locrefcount 6 dup(<>)
lc_clike		SINT ?
mb_cur_max		SINT ?
lconv_intl_refcount	LPINT ?
lconv_num_refcount	LPINT ?
lconv_mon_refcount	LPINT ?
ctype1_refcount		LPINT ?
ctype1			LPSHORT ?
pctype			LPSHORT ?
pclmap			LPSTR ?
pcumap			LPSTR ?
lc_time_curr		ptr_t ?
locale_name		LPWSTR 6 dup(?)
threadlocinfo		ENDS
pthreadlocinfo		typedef ptr threadlocinfo
endif

if defined (_PREFAST_) AND defined (_CA_SHOULD_CHECK_RETURN)
_Check_return_opt_ equ <_Check_return_>
else
_Check_return_opt_ equ <>
endif

if defined (_PREFAST_) AND defined (_CA_SHOULD_CHECK_RETURN_WER)
_Check_return_wat_ equ <_Check_return_>
else
_Check_return_wat_ equ <>
endif

if NOT defined (__midl) AND NOT defined (MIDL_PASS) AND defined (_PREFAST_)
__crt_typefix macro ctype
	exitm<__declspec("SAL_typefix(" __CRT_STRINGIZE(ctype) ")")>
	endm
else
__crt_typefix macro ctype
	exitm<>
	endm
endif

ifdef __midl
ifndef _NO_INLINING
_NO_INLINING equ 1
endif
endif

ifndef _CRT_UNUSED
_CRT_UNUSED macro x
	exitm<(void)x>
	endm
endif

.pragma pack(pop)

endif ;; _INC_CRTDEFS
