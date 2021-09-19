ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 440
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
define __servprov_h__

include objidl.inc

;void
MIDL_user_free proto WINAPI :PVOID

ifndef _LPSERVICEPROVIDER_DEFINED
define _LPSERVICEPROVIDER_DEFINED

ifndef __IServiceProvider_INTERFACE_DEFINED__
define __IServiceProvider_INTERFACE_DEFINED__

.comdef IServiceProvider : public IUnknown

    QueryService	proc :REFGUID, :REFIID, :ptr
    .ends
    LPSERVICEPROVIDER	typedef ptr IServiceProvider

externdef IID_IServiceProvider:IID

endif
endif

endif
