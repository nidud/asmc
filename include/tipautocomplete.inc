ifndef _RPCNDR500_
include rpcndr500.inc
endif

ifndef __tipautocomplete_h__
define __tipautocomplete_h__

ifndef __oaidl_h__
include oaidl.inc
endif
ifndef __ocidl_h__
include ocidl.inc
endif
ifndef _WINAPIFAMILY_
include winapifamily.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

ifndef __ITipAutoCompleteProvider_INTERFACE_DEFINED__
define __ITipAutoCompleteProvider_INTERFACE_DEFINED__

DEFINE_IIDX(ITipAutoCompleteProvider, "7C6CF46D-8404-46b9-AD33-F5B6036D4007")

.comdef ITipAutoCompleteProvider : public IUnknown
    UpdatePendingText   proc :BSTR
    Show                proc :BOOL
   .ends

endif

ifndef __ITipAutoCompleteClient_INTERFACE_DEFINED__
define __ITipAutoCompleteClient_INTERFACE_DEFINED__

DEFINE_IIDX(ITipAutoCompleteClient, "5E078E03-8265-4bbe-9487-D242EDBEF910")

.comdef ITipAutoCompleteClient : public IUnknown
    AdviseProvider      proc :HWND, :ptr
    UnadviseProvider    proc :HWND, :ptr
    UserSelection       proc
    PreferredRects      proc :ptr, :ptr, :ptr, :ptr
    RequestShowUI       proc :HWND, :ptr
   .ends

endif

ifndef __TipAutoCompleteClientLib_LIBRARY_DEFINED__
define __TipAutoCompleteClientLib_LIBRARY_DEFINED__

DEFINE_GUID(LIBID_TipAutoCompleteClientLib, 0x6B56A75E,0xD676,0x4864,0x8B,0x36,0xA1,0x9B,0x89,0x73,0xDB,0x13)
DEFINE_GUID(CLSID_TipAutoCompleteClient, 0x807C1E6C,0x1D00,0x453f,0xB9,0x20,0xB6,0x1B,0xB7,0xCD,0xD9,0x97)

endif

endif

endif
