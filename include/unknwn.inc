ifndef __unknwn_h__
.xlist
__unknwn_h__ equ 1

ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 440
endif

include rpc.inc
include rpcndr.inc
.xlist

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc >
endif ;; __RPCNDR_H_VERSION__

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif ;;COM_NO_WINDOWS_H

;; header files for imported files
include wtypes.inc
.xlist

externdef __MIDL_itf_unknwn_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_unknwn_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IUnknown_INTERFACE_DEFINED__
__IUnknown_INTERFACE_DEFINED__ equ 1
ifdef __PE__
option	dllimport:<rpcrt4>
endif

LPUNKNOWN  typedef ptr IUnknown

;HRESULT
IUnknown_QueryInterface_Proxy proto _CType \
		 _This: LPUNKNOWN,
		  riid: REFIID,
	     ppvObject: PVOID
;void
IUnknown_QueryInterface_Stub proto _CType \
		 _This: LPUNKNOWN,
    _pRpcChannelBuffer: ptr,;IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;ULONG
IUnknown_AddRef_Proxy proto _CType \
		 _This: ptr IUnknown


;void
IUnknown_AddRef_Stub proto _CType \
		 _This: ptr,;IRpcStubBuffer,
    _pRpcChannelBuffer: ptr,;IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;ULONG
IUnknown_Release_Proxy proto _CType \
		 _This: ptr,;IUnknown


;void
IUnknown_Release_Stub proto _CType \
		 _This: ptr,;IRpcStubBuffer,
    _pRpcChannelBuffer: ptr,;IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IUnknown_INTERFACE_DEFINED__


ifndef __IClassFactory_INTERFACE_DEFINED__
__IClassFactory_INTERFACE_DEFINED__ equ 1

LPCLASSFACTORY		typedef ptr IClassFactory

if 0

EXTERN_C IID IID_IClassFactory;


IClassFactoryVtbl	STRUC

( STDMETHODCALLTYPE *QueryInterface )( HRESULT ?
*This,			IClassFactory ?
riid,			REFIID ?
**ppvObject)		void ?

( STDMETHODCALLTYPE *AddRef )( ULONG ?
* This)			IClassFactory ?

( STDMETHODCALLTYPE *Release )( ULONG ?
* This)			IClassFactory ?

( STDMETHODCALLTYPE *CreateInstance )( HRESULT ?
* This,			IClassFactory ?
*pUnkOuter,		IUnknown ?
riid,			REFIID ?
**ppvObject)		void ?

( STDMETHODCALLTYPE *LockServer )( HRESULT ?
* This,			IClassFactory ?
fLock)			BOOL ?

IClassFactoryVtbl	ENDS

IClassFactory		interface ?
struct IClassFactoryVtbl *lpVtbl CONST_VTBL ?
			ENDS


endif	;; C style interface



;HRESULT
IClassFactory_RemoteCreateInstance_Proxy proto _CType \
		 _This: ptr IClassFactory,
		  riid: REFIID,
	     ppvObject: ptr IUnknown


;void
IClassFactory_RemoteCreateInstance_Stub proto _CType \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD


;HRESULT
IClassFactory_RemoteLockServer_Proxy proto _CType \
		 _This: ptr IClassFactory,
		 fLock: BOOL


;void
IClassFactory_RemoteLockServer_Stub proto _CType \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



endif	;; __IClassFactory_INTERFACE_DEFINED__


;; Additional Prototypes for ALL interfaces

;HRESULT
IClassFactory_CreateInstance_Proxy proto _CType \
		 _This: ptr IClassFactory,
	     pUnkOuter: ptr IUnknown,
		  riid: REFIID

;HRESULT
IClassFactory_CreateInstance_Stub proto _CType \
		 _This: ptr IClassFactory,
		  riid: REFIID,
	     ppvObject: ptr IUnknown

;HRESULT
IClassFactory_LockServer_Proxy proto _CType \
		 _This: ptr IClassFactory,
		 fLock: BOOL

;HRESULT
IClassFactory_LockServer_Stub proto _CType \
		 _This: ptr IClassFactory,
		 fLock: BOOL


;; end of Additional Prototypes

.list
endif	;; __unknwn_h__
