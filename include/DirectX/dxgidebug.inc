ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __dxgidebug_h__
define __dxgidebug_h__

include oaidl.inc
include ocidl.inc

DXGI_DEBUG_BINARY_VERSION equ 1

.enum DXGI_DEBUG_RLO_FLAGS {
    DXGI_DEBUG_RLO_SUMMARY	= 0x1,
    DXGI_DEBUG_RLO_DETAIL	= 0x2,
    DXGI_DEBUG_RLO_IGNORE_INTERNAL = 0x4,
    DXGI_DEBUG_RLO_ALL		= 0x7
    }

DXGI_DEBUG_ID typedef GUID

DEFINE_GUID(DXGI_DEBUG_ALL, 0xe48ae283, 0xda80, 0x490b, 0x87, 0xe6, 0x43, 0xe9, 0xa9, 0xcf, 0xda, 0x8);
DEFINE_GUID(DXGI_DEBUG_DX, 0x35cdd7fc, 0x13b2, 0x421d, 0xa5, 0xd7, 0x7e, 0x44, 0x51, 0x28, 0x7d, 0x64);
DEFINE_GUID(DXGI_DEBUG_DXGI, 0x25cddaa4, 0xb1c6, 0x47e1, 0xac, 0x3e, 0x98, 0x87, 0x5b, 0x5a, 0x2e, 0x2a);
DEFINE_GUID(DXGI_DEBUG_APP, 0x6cd6e01, 0x4219, 0x4ebd, 0x87, 0x9, 0x27, 0xed, 0x23, 0x36, 0xc, 0x62);

.enum DXGI_INFO_QUEUE_MESSAGE_CATEGORY {
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY_UNKNOWN,
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY_MISCELLANEOUS,
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY_INITIALIZATION,
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY_CLEANUP,
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY_COMPILATION,
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_CREATION,
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_SETTING,
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY_STATE_GETTING,
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY_RESOURCE_MANIPULATION,
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY_EXECUTION,
    DXGI_INFO_QUEUE_MESSAGE_CATEGORY_SHADER
    }

.enum DXGI_INFO_QUEUE_MESSAGE_SEVERITY {
    DXGI_INFO_QUEUE_MESSAGE_SEVERITY_CORRUPTION,
    DXGI_INFO_QUEUE_MESSAGE_SEVERITY_ERROR,
    DXGI_INFO_QUEUE_MESSAGE_SEVERITY_WARNING,
    DXGI_INFO_QUEUE_MESSAGE_SEVERITY_INFO,
    DXGI_INFO_QUEUE_MESSAGE_SEVERITY_MESSAGE
    }

DXGI_INFO_QUEUE_MESSAGE_ID typedef SINT

DXGI_INFO_QUEUE_MESSAGE_ID_STRING_FROM_APPLICATION equ 0
DXGI_INFO_QUEUE_MESSAGE STRUC
Producer		DXGI_DEBUG_ID <>
Category		DXGI_INFO_QUEUE_MESSAGE_CATEGORY ?
Severity		DXGI_INFO_QUEUE_MESSAGE_SEVERITY ?
ID			DXGI_INFO_QUEUE_MESSAGE_ID ?
pDescription		LPSTR ?
DescriptionByteLength	size_t ?
DXGI_INFO_QUEUE_MESSAGE ENDS

DXGI_INFO_QUEUE_FILTER_DESC STRUC
NumCategories		UINT ?
pCategoryList		PVOID ? ; DXGI_INFO_QUEUE_MESSAGE_CATEGORY *
NumSeverities		UINT ?
pSeverityList		PVOID ? ; DXGI_INFO_QUEUE_MESSAGE_SEVERITY *
NumIDs			UINT ?
pIDList			PVOID ? ; DXGI_INFO_QUEUE_MESSAGE_ID *
DXGI_INFO_QUEUE_FILTER_DESC ENDS

DXGI_INFO_QUEUE_FILTER	STRUC
AllowList		DXGI_INFO_QUEUE_FILTER_DESC <>
DenyList		DXGI_INFO_QUEUE_FILTER_DESC <>
DXGI_INFO_QUEUE_FILTER	ENDS

DXGI_INFO_QUEUE_DEFAULT_MESSAGE_COUNT_LIMIT equ 1024

DXGIGetDebugInterface proto WINAPI :REFIID, :ptr

ifndef __IDXGIInfoQueue_INTERFACE_DEFINED__
define __IDXGIInfoQueue_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIInfoQueue, "D67441C7-672A-476f-9E82-CD55B44949CE")

.comdef IDXGIInfoQueue : public IUnknown

    SetMessageCountLimit proc :DXGI_DEBUG_ID, :UINT64
    ClearStoredMessages proc :DXGI_DEBUG_ID
    GetMessage		proc :DXGI_DEBUG_ID, :UINT64
    GetNumStoredMessagesAllowedByRetrievalFilters proc :DXGI_DEBUG_ID
    GetNumStoredMessages proc :DXGI_DEBUG_ID
    GetNumMessagesDiscardedByMessageCountLimit proc :DXGI_DEBUG_ID
    GetMessageCountLimit proc :DXGI_DEBUG_ID
    GetNumMessagesAllowedByStorageFilter proc :DXGI_DEBUG_ID
    GetNumMessagesDeniedByStorageFilter proc :DXGI_DEBUG_ID
    AddStorageFilterEntries proc :DXGI_DEBUG_ID, :ptr
    GetStorageFilter	proc :DXGI_DEBUG_ID
    ClearStorageFilter	proc :DXGI_DEBUG_ID
    PushEmptyStorageFilter proc :DXGI_DEBUG_ID
    PushDenyAllStorageFilter proc :DXGI_DEBUG_ID
    PushCopyOfStorageFilter proc :DXGI_DEBUG_ID
    PushStorageFilter	proc :DXGI_DEBUG_ID, :ptr
    PopStorageFilter	proc :DXGI_DEBUG_ID
    GetStorageFilterStackSize proc :DXGI_DEBUG_ID
    AddRetrievalFilterEntries proc :DXGI_DEBUG_ID, :ptr
    GetRetrievalFilter	proc :DXGI_DEBUG_ID
    ClearRetrievalFilter proc :DXGI_DEBUG_ID
    PushEmptyRetrievalFilter proc :DXGI_DEBUG_ID
    PushDenyAllRetrievalFilter proc :DXGI_DEBUG_ID
    PushCopyOfRetrievalFilter proc :DXGI_DEBUG_ID
    PushRetrievalFilter proc :DXGI_DEBUG_ID, :ptr
    PopRetrievalFilter	proc :DXGI_DEBUG_ID
    GetRetrievalFilterStackSize proc :DXGI_DEBUG_ID
    AddMessage		proc :DXGI_DEBUG_ID, :DXGI_INFO_QUEUE_MESSAGE_CATEGORY, :DXGI_INFO_QUEUE_MESSAGE_SEVERITY, :DXGI_INFO_QUEUE_MESSAGE_ID, :LPCSTR
    AddApplicationMessage proc :DXGI_INFO_QUEUE_MESSAGE_SEVERITY, :LPCSTR
    SetBreakOnCategory	proc :DXGI_DEBUG_ID, :DXGI_INFO_QUEUE_MESSAGE_CATEGORY, :BOOL
    SetBreakOnSeverity	proc :DXGI_DEBUG_ID, :DXGI_INFO_QUEUE_MESSAGE_SEVERITY, :BOOL
    SetBreakOnID	proc :DXGI_DEBUG_ID, :DXGI_INFO_QUEUE_MESSAGE_ID, :BOOL
    GetBreakOnCategory	proc :DXGI_DEBUG_ID, :DXGI_INFO_QUEUE_MESSAGE_CATEGORY
    GetBreakOnSeverity	proc :DXGI_DEBUG_ID, :DXGI_INFO_QUEUE_MESSAGE_SEVERITY
    GetBreakOnID	proc :DXGI_DEBUG_ID, :DXGI_INFO_QUEUE_MESSAGE_ID
    SetMuteDebugOutput	proc :DXGI_DEBUG_ID, :BOOL
    GetMuteDebugOutput	proc :DXGI_DEBUG_ID
   .ends

endif

ifndef __IDXGIDebug_INTERFACE_DEFINED__
define __IDXGIDebug_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIDebug, "119E7452-DE9E-40fe-8806-88F90C12B441")

.comdef IDXGIDebug : public IUnknown

    ReportLiveObjects	proc :ptr, :DXGI_DEBUG_RLO_FLAGS
   .ends

endif

ifndef __IDXGIDebug1_INTERFACE_DEFINED__
define __IDXGIDebug1_INTERFACE_DEFINED__

DEFINE_IIDX(IDXGIDebug1, "c5a05f0c-16f2-4adf-9f4d-a8c4d58ac550")

.comdef IDXGIDebug1 : public IDXGIDebug

    EnableLeakTrackingForThread proc
    DisableLeakTrackingForThread proc
    IsLeakTrackingEnabledForThread proc
   .ends

endif
endif
