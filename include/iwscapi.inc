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

ifndef __iwscapi_h__
define __iwscapi_h__

ifndef __IWscProduct_FWD_DEFINED__
define __IWscProduct_FWD_DEFINED__
endif
ifndef __IWSCProductList_FWD_DEFINED__
define __IWSCProductList_FWD_DEFINED__
endif
ifndef __WSCProductList_FWD_DEFINED__
define __WSCProductList_FWD_DEFINED__
endif

include oaidl.inc
include ocidl.inc

include winapifamily.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

.enum WSC_SECURITY_PRODUCT_STATE {
    WSC_SECURITY_PRODUCT_STATE_ON	= 0,
    WSC_SECURITY_PRODUCT_STATE_OFF	= 1,
    WSC_SECURITY_PRODUCT_STATE_SNOOZED	= 2,
    WSC_SECURITY_PRODUCT_STATE_EXPIRED	= 3
    }

.enum WSC_SECURITY_SIGNATURE_STATUS {
    WSC_SECURITY_PRODUCT_OUT_OF_DATE	= 0,
    WSC_SECURITY_PRODUCT_UP_TO_DATE	= 1
    }

ifndef __IWscProduct_INTERFACE_DEFINED__
define __IWscProduct_INTERFACE_DEFINED__

DEFINE_IIDX(IWscProduct, "8C38232E-3A45-4A27-92B0-1A16A975F669")

.comdef IWscProduct : public IDispatch

    get_ProductName	proc :ptr
    get_ProductState	proc :ptr
    get_SignatureStatus proc :ptr
    get_RemediationPath proc :ptr
    get_ProductStateTimestamp proc :ptr
    .ends

endif

ifndef __IWSCProductList_INTERFACE_DEFINED__
define __IWSCProductList_INTERFACE_DEFINED__

DEFINE_IIDX(IWSCProductList, "722A338C-6E8E-4E72-AC27-1417FB0C81C2")

.comdef IWSCProductList : public IDispatch

    Initialize		proc :ULONG
    get_Count		proc :ptr
    get_Item		proc :ULONG, :ptr
    .ends

endif

ifndef __wscAPILib_LIBRARY_DEFINED__
define __wscAPILib_LIBRARY_DEFINED__

externdef LIBID_wscAPILib:IID

DEFINE_GUIDS(CLSID_WSCProductList, "17072F7B-9ABE-4A74-A261-1EB76B55107A")

endif

endif
endif

