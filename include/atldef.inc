ifndef __ATLDEF_H__
__ATLDEF_H__ equ <>

ifndef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
ifdef WINAPI_FAMILY

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
_ATL_USE_WINAPI_FAMILY_DESKTOP_APP equ 1
else

ifdef WINAPI_FAMILY_PHONE_APP
if WINAPI_FAMILY eq WINAPI_FAMILY_PHONE_APP
_ATL_USE_WINAPI_FAMILY_PHONE_APP equ 1
endif
endif

ifdef WINAPI_FAMILY_APP
if WINAPI_FAMILY eq WINAPI_FAMILY_APP
_ATL_USE_WINAPI_FAMILY_APP equ 1
endif
endif

endif

else
_ATL_USE_WINAPI_FAMILY_DESKTOP_APP equ 1
endif
endif

ifndef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP

ifndef _ATL_NO_SERVICE
_ATL_NO_SERVICE equ <>
endif
ifndef _ATL_NO_COM_SUPPORT
_ATL_NO_COM_SUPPORT equ <>
endif
ifndef _ATL_NO_COMMODULE
_ATL_NO_COMMODULE equ <>
endif
ifndef _ATL_NO_WIN_SUPPORT
_ATL_NO_WIN_SUPPORT equ <>
endif

endif

include atlrc.inc
include errno.inc
include stdlib.inc
include sal.inc

ifndef _ATL_DISABLE_NOTHROW_NEW
;include new.inc
_ATL_NEW equ <.new>
else
_ATL_NEW equ <.new>
endif

ifndef RC_INVOKED
if defined(_ATL_MIXED) or not defined(_M_CEE)
if defined(_M_IX86) or defined(_M_ARM)
;.pragma comment(linker, "/include:??3@YAXPAX@Z")
elseif defined(_M_AMD64)
;.pragma comment(linker, "/include:??3@YAXPEAX@Z")
else
;.err <Unsupported target architecture.>
endif
ifndef _ATL_NATIVE_INITIALIZATION
_ATL_NATIVE_INITIALIZATION equ <>
endif
endif


ifdef _UNICODE
ifndef UNICODE
UNICODE equ 1
endif
endif

ifdef UNICODE
ifndef _UNICODE
_UNICODE equ 1
endif
endif

ifdef _DEBUG
ifndef DEBUG
DEBUG equ 1
endif
endif

if not defined(_ATL_USE_WINAPI_FAMILY_DESKTOP_APP) and not defined(_UNICODE)
.err <_UNICODE has to be defined to use ATL under the current WINAPI_FAMILY>
endif


if defined(_PREFAST_) and (_MSC_VER lt 1600)
ATLSTATIC_ASSERT macro expr, comment
exitm<>
endm
else
ATLSTATIC_ASSERT macro expr, comment_
exitm<static_assert(expr, comment_)>
endm
endif

ifdef _WIN64
_ATL_SUPPORT_VT_I8 equ 1
endif

ifndef AtlThrow
ifndef _ATL_CUSTOM_THROW
AtlThrow equ <ATL::AtlThrowImpl>
endif
endif

ifndef ATLASSERT
ATLASSERT equ <_ASSERTE>
endif


ifndef ATLASSUME
ATLASSUME macro expr
exitm<.err>
endm
endif

ifndef ATLVERIFY
ifdef _DEBUG
ATLVERIFY equ <ATLASSERT>
else
ATLVERIFY macro expr
exitm<(expr)>
endm
endif
endif

ifndef ATLENSURE_THROW
ATLENSURE_THROW macro expr, hr
exitm<(expr)>
endm
endif

ifndef ATLENSURE
ATLENSURE macro expr
exitm<ATLENSURE_THROW(expr, E_FAIL)>
endm
endif

ifndef ATLENSURE_SUCCEEDED
ATLENSURE_SUCCEEDED macro hrExpr
exitm<.err>
endm
endif

ifndef ATLENSURE_RETURN_VAL
ATLENSURE_RETURN_VAL macro expr, val
exitm<.err>
endm
endif

ifndef ATLENSURE_RETURN
ATLENSURE_RETURN macro expr
exitm<ATLENSURE_RETURN_HR(expr, E_FAIL)>
endm
endif

ifndef ATLENSURE_RETURN_HR
ATLENSURE_RETURN_HR macro expr, hr
exitm<ATLENSURE_RETURN_VAL(expr, hr)>
endm
endif

ifndef ATL_CRT_ERRORCHECK
ATL_CRT_ERRORCHECK macro expr
exitm<AtlCrtErrorCheck(expr)>
endm
endif

ifndef ATL_CRT_ERRORCHECK_SPRINTF
ATL_CRT_ERRORCHECK_SPRINTF macro expr
exitm<.err>
endm
endif

ifdef _ATL_DISABLE_NO_VTABLE
ATL_NO_VTABLE equ <>
else
ATL_NO_VTABLE equ <__declspec(novtable)>
endif

ifdef _ATL_DISABLE_NOTHROW
ATL_NOTHROW equ <>
else
ATL_NOTHROW equ <__declspec(nothrow)>
endif

ifdef _ATL_DISABLE_FORCEINLINE
ATL_FORCEINLINE equ <>
else
ATL_FORCEINLINE equ <__forceinline>
endif

ifdef _ATL_DISABLE_NOINLINE
ATL_NOINLINE equ <>
else
ATL_NOINLINE equ <__declspec( noinline )>
endif

ifdef _ATL_DISABLE_DEPRECATED
ATL_DEPRECATED macro _Message
exitm<>
endm
else
ATL_DEPRECATED macro _Message
exitm<__declspec( deprecated(_Message) )>
endm
endif

ifdef _ATL_DEBUG_REFCOUNT
ifndef _ATL_DEBUG_INTERFACES
_ATL_DEBUG_INTERFACES equ 1
endif
endif

ifdef _DEBUG
ifndef _ATL_DEBUG
_ATL_DEBUG equ 1
endif
endif

ifdef _ATL_DEBUG_INTERFACES
ifndef _ATL_DEBUG
_ATL_DEBUG equ 1
endif
endif

ifndef _ATL_HEAPFLAGS
ifdef _MALLOC_ZEROINIT
_ATL_HEAPFLAGS equ HEAP_ZERO_MEMORY
else
_ATL_HEAPFLAGS equ 0
endif
endif

ifndef _ATL_PACKING
_ATL_PACKING equ 8
endif

ATLAPI equ <WINAPI>
ATLAPI_ macro x
exitm<x WINAPI>
endm
ATLAPIINL equ <ATLAPI>
ATLAPIINL_ macro x
exitm<ATLAPI_(x)>
endm
ATLINLINE equ <inline>

ifdef _ATL_NO_EXCEPTIONS
	ifdef _AFX
	.err<MFC projects cannot define _ATL_NO_EXCEPTIONS>
	endif
else
	ifndef _CPPUNWIND
	_ATL_NO_EXCEPTIONS equ <>
	endif
endif

ifdef _CPPUNWIND

ifndef ATLTRYALLOC

ifdef _AFX
ATLTRYALLOC macro x
exitm<.err>
endm
else
ATLTRYALLOC macro x
exitm<.err>
endm
endif

endif

ifndef _ATLTRY
_ATLTRY equ <try>
ifdef _AFX
_ATLCATCH macro e
exitm<catch( CException* e )>
endm
else
_ATLCATCH macro e
exitm<catch( CAtlException e )>
endm
endif

_ATLCATCHALL macro
exitm<.err>
endm

ifdef _AFX
_ATLDELETEEXCEPTION macro e
exitm<.err>
endm
else
_ATLDELETEEXCEPTION macro e
exitm<e>
endm
endif

_ATLRETHROW equ <throw>
endif

ifndef _ATL_COM_BEGIN
_ATL_COM_BEGIN macro
exitm<.err>
endm
endif

ifdef _AFX
else
endif

ifndef _ATL_COM_END
endif

else ;;_CPPUNWIND

ifndef ATLTRYALLOC
endif

ifndef _ATLTRY
endif

endif

ifndef ATLTRY
endif

_ATL	 equ 1
_ATL_VER equ 0x0C00

ifndef _ATL_FILENAME_VER
_ATL_FILENAME_VER equ <"120">
endif

ifndef _ATL_FILENAME_VER_NUM
_ATL_FILENAME_VER_NUM equ 120
endif

ifndef _ATL_VER_RBLD
_ATL_VER_RBLD equ <"12.00">
endif

ifndef _ATL_SINGLE_THREADED
ifndef _ATL_APARTMENT_THREADED
ifndef _ATL_FREE_THREADED
_ATL_FREE_THREADED equ 1
endif
endif
endif

ifndef _ATL_NO_UUIDOF
_ATL_IIDOF macro x
exitm<__uuidof(x)>
endm
else
_ATL_IIDOF macro x
exitm<IID_&x>
endm
endif

ifndef ATL_NO_LEAN_AND_MEAN
ifndef WIN32_LEAN_AND_MEAN
WIN32_LEAN_AND_MEAN equ 1
endif
ifndef NOMCX
NOMCX equ 1
endif
endif

ifdef NOSERVICE
ifndef _ATL_NO_SERVICE
_ATL_NO_SERVICE equ 1
endif
else
ifdef _ATL_NO_SERVICE
ifndef NOSERVICE
NOSERVICE equ 1
endif
endif
endif

include malloc.inc
ifdef _DEBUG
include stdlib.inc
endif
ifndef _ATL_NO_DEBUG_CRT
include crtdbg.inc
endif

endif

ATLAXWIN_CLASS equ <"AtlAxWin120">
ATLAXWINLIC_CLASS equ <"AtlAxWinLic120">

if defined(_ATL_SECURE_NO_DEPRECATE) and not defined(_ATL_SECURE_NO_WARNINGS)
_ATL_SECURE_NO_WARNINGS equ 1
endif

ifndef _ATL_INSECURE_DEPRECATE
ifdef _ATL_SECURE_NO_WARNINGS
_ATL_INSECURE_DEPRECATE macro _Message
exitm<>
endm
else
_ATL_INSECURE_DEPRECATE macro _Message
exitm<__declspec(deprecated(_Message))>
endm
endif
endif

if not defined(_ATL_FATAL_SHUTDOWN) and defined(_ATL_USE_WINAPI_FAMILY_DESKTOP_APP)
_ATL_FATAL_SHUTDOWN macro
exitm<.err>
endm
endif

ifdef _ATL_ENABLE_PTM_WARNING
PTM_WARNING_DISABLE equ 1
PTM_WARNING_RESTORE equ 1
else
PTM_WARNING_DISABLE macro
exitm<.err>
endm
PTM_WARNING_RESTORE macro
exitm<.err>
endm
endif

ATL_MAKEINTRESOURCEA macro i
exitm<i>
endm
ATL_MAKEINTRESOURCEW macro i
exitm<(i)>
endm
ifdef _UNICODE
ATL_MAKEINTRESOURCE equ <ATL_MAKEINTRESOURCEW>
else
ATL_MAKEINTRESOURCE equ <ATL_MAKEINTRESOURCEA>
endif
ATL_IS_INTRESOURCE macro _r
if (((_r) shr 16) eq 0)
    exitm<1>
else
    exitm<0>
endif
endm

ATL_RT_CURSOR		equ ATL_MAKEINTRESOURCE(1)
ATL_RT_BITMAP		equ ATL_MAKEINTRESOURCE(2)
ATL_RT_ICON		equ ATL_MAKEINTRESOURCE(3)
ATL_RT_MENU		equ ATL_MAKEINTRESOURCE(4)
ATL_RT_DIALOG		equ ATL_MAKEINTRESOURCE(5)
ATL_RT_STRING		equ ATL_MAKEINTRESOURCE(6)
ATL_RT_FONTDIR		equ ATL_MAKEINTRESOURCE(7)
ATL_RT_FONT		equ ATL_MAKEINTRESOURCE(8)
ATL_RT_ACCELERATOR	equ ATL_MAKEINTRESOURCE(9)
ATL_RT_RCDATA		equ ATL_MAKEINTRESOURCE(10)
ATL_RT_MESSAGETABLE	equ ATL_MAKEINTRESOURCE(11)

ATL_DIFFERENCE		equ 11
ATL_RT_GROUP_CURSOR	equ ATL_MAKEINTRESOURCE(ATL_RT_CURSOR + ATL_DIFFERENCE)
ATL_RT_GROUP_ICON	equ ATL_MAKEINTRESOURCE(ATL_RT_ICON + ATL_DIFFERENCE)
ATL_RT_VERSION		equ ATL_MAKEINTRESOURCE(16)
ATL_RT_DLGINCLUDE	equ ATL_MAKEINTRESOURCE(17)
ATL_RT_PLUGPLAY		equ ATL_MAKEINTRESOURCE(19)
ATL_RT_VXD		equ ATL_MAKEINTRESOURCE(20)
ATL_RT_ANICURSOR	equ ATL_MAKEINTRESOURCE(21)
ATL_RT_ANIICON		equ ATL_MAKEINTRESOURCE(22)
ATL_RT_HTML		equ ATL_MAKEINTRESOURCE(23)

ATLPREFAST_SUPPRESS macro x
exitm<>
endm
ATLPREFAST_UNSUPPRESS macro
exitm<>
endm

ifndef _FormatMessage_format_string_
_FormatMessage_format_string_ equ <>
endif

endif
