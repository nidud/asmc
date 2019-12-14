ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 440
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
 .err <this stub requires an updated version of rpcndr>
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif
ifndef __servprov_h__
__servprov_h__ equ <>

ifndef __IServiceProvider_FWD_DEFINED__
__IServiceProvider_FWD_DEFINED__ equ 1
endif
include objidl.inc

;void
MIDL_user_free proto WINAPI :PVOID

ifndef _LPSERVICEPROVIDER_DEFINED
_LPSERVICEPROVIDER_DEFINED equ 1

ifndef __IServiceProvider_INTERFACE_DEFINED__
__IServiceProvider_INTERFACE_DEFINED__ equ 1

.comdef IServiceProvider : public IUnknown

    QueryService	proc :REFGUID, :REFIID, :ptr
    .ends
    LPSERVICEPROVIDER	typedef ptr IServiceProvider

externdef IID_IServiceProvider:IID

endif
endif

endif
