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
__servprov_h__ equ 1

ifndef __IServiceProvider_FWD_DEFINED__
__IServiceProvider_FWD_DEFINED__ equ 1
endif
include objidl.inc
.xlist

;void
MIDL_user_free proto WINAPI :PVOID

ifndef _LPSERVICEPROVIDER_DEFINED
_LPSERVICEPROVIDER_DEFINED equ 1

externdef		__MIDL_itf_servprov_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_servprov_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IServiceProvider_INTERFACE_DEFINED__
__IServiceProvider_INTERFACE_DEFINED__ equ 1

IServiceProviderVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryService, :REFGUID, :REFIID, :ptr
IServiceProviderVtbl ends
IServiceProvider struct
	lpVtbl		PVOID ?
IServiceProvider ends
LPSERVICEPROVIDER	typedef ptr IServiceProvider
LPIServiceProvider	typedef ptr IServiceProvider
externdef		IID_IServiceProvider:IID

;HRESULT
IServiceProvider_RemoteQueryService_Proxy proto WINAPI \
		 pThis: ptr IServiceProvider,
	   guidService: REFGUID,
		  riid: REFIID,
	     ppvObject: ptr IUnknown

;void
IServiceProvider_RemoteQueryService_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif ; __IServiceProvider_INTERFACE_DEFINED__
endif ; _LPSERVICEPROVIDER_DEFINED

externdef		__MIDL_itf_servprov_0074_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_servprov_0074_v0_0_s_ifspec:RPC_IF_HANDLE

;HRESULT
IServiceProvider_QueryService_Proxy proto WINAPI \
		 pThis: ptr IServiceProvider,
	   guidService: REFGUID,
		  riid: REFIID,
	     ppvObject: PVOID

;HRESULT
IServiceProvider_QueryService_Stub proto WINAPI \
		 pThis: ptr IServiceProvider,
	   guidService: REFGUID,
		  riid: REFIID,
	     ppvObject: ptr IUnknown

.list
endif ; __servprov_h__
