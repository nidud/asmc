ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 440
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err LT this stub requires an updated version of rpcndr.inc GT
endif
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif
ifndef __servprov_h__
.xlist
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

LPSERVICEPROVIDER	typedef ptr IServiceProvider

externdef		IID_IServiceProvider:IID

IServiceProviderVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface PVOID ?
		 AddRef PVOID ?
		Release PVOID ?
	   QueryService PVOID ?

	END_INTERFACE

IServiceProviderVtbl	ENDS

LPIServiceProviderVtbl	typedef ptr IServiceProviderVtbl
IServiceProvider	STRUC
lpVtbl			LPIServiceProviderVtbl ?
IServiceProvider	ENDS

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
endif
endif

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
endif
