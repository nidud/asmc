ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 440
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err LT this stub requires an updated version of rpcndr.inc GT
endif ;; __RPCNDR_H_VERSION__
ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif ;;COM_NO_WINDOWS_H
ifndef __servprov_h__
.xlist
__servprov_h__ equ 1

;; Forward Declarations

ifndef __IServiceProvider_FWD_DEFINED__
__IServiceProvider_FWD_DEFINED__ equ 1
endif	;; __IServiceProvider_FWD_DEFINED__


;; header files for imported files
include objidl.inc
.xlist

;PVOID
;void
MIDL_user_free proto _CType \
		      : PVOID


;;#pragma comment(lib,"uuid.lib")

;;---------------------------------------------------------------------------=
;; IServiceProvider Interfaces.


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

    QueryInterface52@CT typedef proto \
		 pThis: ptr IServiceProvider,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface52@MP typedef ptr QueryInterface52@CT
	 QueryInterface QueryInterface52@MP ?

	    AddRef52@CT typedef proto \
		 pThis: ptr IServiceProvider

	    AddRef52@MP typedef ptr AddRef52@CT
		 AddRef AddRef52@MP ?

	   Release52@CT typedef proto \
		 pThis: ptr IServiceProvider

	   Release52@MP typedef ptr Release52@CT
		Release Release52@MP ?

      QueryService52@CT typedef proto \
		 pThis: ptr IServiceProvider,
	   guidService: REFGUID,
		  riid: REFIID,
	     ppvObject: PVOID

      QueryService52@MP typedef ptr QueryService52@CT
	   QueryService QueryService52@MP ?

	END_INTERFACE

IServiceProviderVtbl	ENDS

LPIServiceProviderVtbl	typedef ptr IServiceProviderVtbl
IServiceProvider	STRUC
lpVtbl			LPIServiceProviderVtbl ?
IServiceProvider	ENDS






;HRESULT
IServiceProvider_RemoteQueryService_Proxy proto _CType \
		 pThis: ptr IServiceProvider,
	   guidService: REFGUID,
		  riid: REFIID,
	     ppvObject: ptr IUnknown



;void
IServiceProvider_RemoteQueryService_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	;; __IServiceProvider_INTERFACE_DEFINED__
endif


externdef		__MIDL_itf_servprov_0074_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_servprov_0074_v0_0_s_ifspec:RPC_IF_HANDLE

;; Additional Prototypes for ALL interfaces

;HRESULT
IServiceProvider_QueryService_Proxy proto _CType \
		 pThis: ptr IServiceProvider,
	   guidService: REFGUID,
		  riid: REFIID,
	     ppvObject: PVOID



;HRESULT
IServiceProvider_QueryService_Stub proto _CType \
		 pThis: ptr IServiceProvider,
	   guidService: REFGUID,
		  riid: REFIID,
	     ppvObject: ptr IUnknown


;; end of Additional Prototypes
.list
endif
