ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

ifndef __inspectable_h__
define __inspectable_h__

include wtypes.inc
include unknwn.inc
include hstring.inc

.enum TrustLevel {
    BaseTrust	  = 0,
    PartialTrust  = ( BaseTrust + 1 ) ,
    FullTrust	  = ( PartialTrust + 1 )
    }

ifndef __IInspectable_INTERFACE_DEFINED__
define __IInspectable_INTERFACE_DEFINED__

DEFINE_IIDX(IInspectable, "AF86E2E0-B12D-4c6a-9C5A-D7AA65101E90")

.comdef IInspectable : public IUnknown

    GetIids proc :ptr, :ptr
    GetRuntimeClassName proc :ptr
    GetTrustLevel proc :ptr
   .ends
    LPINSPECTABLE typedef ptr IInspectable

endif

HSTRING_UserSize	proto WINAPI :ptr, :ULONG, :ptr
HSTRING_UserMarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree	proto WINAPI :ptr, :ptr

HSTRING_UserSize64	proto WINAPI :ptr, :ULONG, :ptr
HSTRING_UserMarshal64	proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HSTRING_UserFree64	proto WINAPI :ptr, :ptr

endif


