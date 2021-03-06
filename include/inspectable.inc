ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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
__inspectable_h__ equ <>

ifndef __IInspectable_FWD_DEFINED__
__IInspectable_FWD_DEFINED__ equ <>
endif

include wtypes.inc
include unknwn.inc
include hstring.inc

LPINSPECTABLE typedef ptr IInspectable

.enum TrustLevel {
    BaseTrust	  = 0,
    PartialTrust  = ( BaseTrust + 1 ) ,
    FullTrust	  = ( PartialTrust + 1 )
    }

ifndef __IInspectable_INTERFACE_DEFINED__
__IInspectable_INTERFACE_DEFINED__ equ <>

DEFINE_IIDX(IInspectable, "AF86E2E0-B12D-4c6a-9C5A-D7AA65101E90")

.comdef IInspectable : public IUnknown

    GetIids proc :ptr ULONG, :ptr ptr IID
    GetRuntimeClassName proc :ptr HSTRING
    GetTrustLevel proc :ptr TrustLevel
    .ends

endif

HSTRING_UserSize	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree	proto WINAPI :ptr ULONG, :ptr HSTRING

HSTRING_UserSize64	proto WINAPI :ptr ULONG, :ULONG, :ptr HSTRING
HSTRING_UserMarshal64	proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserUnmarshal64 proto WINAPI :ptr ULONG, :ptr UCHAR, :ptr HSTRING
HSTRING_UserFree64	proto WINAPI :ptr ULONG, :ptr HSTRING

endif


