ifndef __ATLCOM_H__
__ATLCOM_H__ equ <>

ifndef __ATLBASE_H__
.err <atlcom.h requires atlbase.h to be included first>
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
include atlstdthunk.inc
endif

externdef IID_ITargetFrame:IID

include limits.inc

.pragma pack(push, _ATL_PACKING)

ifdef _ATL_DEBUG_QI
ifndef _ATL_DEBUG
_ATL_DEBUG equ 1
endif
endif

ifdef _ATL_DEBUG_QI
_ATLDUMPIID macro iid, name, hr
	exitm<AtlDumpIID(iid, name, hr)>
	endm
else
_ATLDUMPIID macro iid, name, hr
	exitm<hr>
	endm
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
endif
ifndef _ATL_PROP_ENTRY_NO_WARNING
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
ifdef _DEBUG
endif
endif

ifdef _ATL_DEBUG
else
endif

ifdef _ATL_DEBUG_INTERFACES
else
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
endif

ifdef _ATL_DEBUG
else
endif

ifndef _ATL_INSECURE_DEPRECATE
endif

ifndef OBJECT_ENTRY_PRAGMA
OBJECT_ENTRY_PRAGMA equ <>
if defined(_M_IX86)
else
;.err <Unknown Platform.>
endif
endif

ifndef _ATL_OLEDB_CONFORMANCE_TESTS
endif

if defined(_ATL_DEBUG_INTERFACES) OR defined(_ATL_DEBUG_QI)
endif
if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
endif

ifdef _DEBUG
else
endif

ifdef _DEBUG
else
endif

if defined(_WINDLL) OR defined(_USRDLL)
else
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
endif
ifndef _ATL_STATIC_LIB_IMPL
endif

ifndef _ATL_STATIC_LIB_IMPL
endif

if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif

if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif
if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif

if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif

if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif
ifdef _DEBUG
endif

if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif

ifdef _DEBUG
else
endif

ifdef _DEBUG
else
endif

if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif

if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
else
endif

if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif

if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif

if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif

ifndef _ATL_OLEDB_CONFORMANCE_TESTS
endif

if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif
if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif
if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif
if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif

ifndef _ATL_STATIC_LIB_IMPL
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
ifndef _ATL_STATIC_LIB_IMPL
endif
endif

ifndef _ATL_STATIC_LIB_IMPL
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP

ifndef _ATL_STATIC_LIB_IMPL
ifndef _UNICODE
endif
ifdef _DEBUG
endif
endif
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
endif


ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
ifdef _M_IA64
else
endif
endif

ifndef _ATL_MAX_VARTYPES
_ATL_MAX_VARTYPES equ 8
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif
ifndef _ATL_IGNORE_NAMED_ARGS
endif
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
endif

ifndef _ATL_NO_CONNECTION_POINTS
ifndef _DEFAULT_VECTORLENGTH
_DEFAULT_VECTORLENGTH	equ 4
endif
ifndef _ATL_OLEDB_CONFORMANCE_TESTS
endif
ifndef _ATL_OLEDB_CONFORMANCE_TESTS
endif
ifndef _ATL_OLEDB_CONFORMANCE_TESTS
endif
if defined(_ATL_DEBUG_INTERFACES) AND NOT defined(_ATL_STATIC_LIB_IMPL)
endif
endif

ifdef _ATL_USE_WINAPI_FAMILY_DESKTOP_APP
ifndef _UNICODE
endif
ifdef _DEBUG
endif
endif

.pragma pack(pop)

endif
