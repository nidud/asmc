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
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif

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
IUnknown_QueryInterface_Proxy proto WINAPI \
		 _This: LPUNKNOWN,
		  riid: REFIID,
	     ppvObject: PVOID
;void
IUnknown_QueryInterface_Stub proto WINAPI \
		 _This: LPUNKNOWN,
    _pRpcChannelBuffer: ptr,;IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;ULONG
IUnknown_AddRef_Proxy proto WINAPI \
		 _This: ptr IUnknown


;void
IUnknown_AddRef_Stub proto WINAPI \
		 _This: ptr,;IRpcStubBuffer,
    _pRpcChannelBuffer: ptr,;IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;ULONG
IUnknown_Release_Proxy proto WINAPI \
		 _This: ptr ;IUnknown


;void
IUnknown_Release_Stub proto WINAPI \
		 _This: ptr,;IRpcStubBuffer,
    _pRpcChannelBuffer: ptr,;IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IClassFactory_INTERFACE_DEFINED__
__IClassFactory_INTERFACE_DEFINED__ equ 1

IClassFactory		STRUC
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD CreateInstance, :ptr, :REFIID, :ptr
STDMETHOD LockServer, :BOOL
IClassFactory		ENDS
LPCLASSFACTORY		typedef ptr IClassFactory
externdef		IID_IClassFactory:IID

;HRESULT
IClassFactory_RemoteCreateInstance_Proxy proto WINAPI \
		 _This: ptr IClassFactory,
		  riid: REFIID,
	     ppvObject: ptr IUnknown


;void
IClassFactory_RemoteCreateInstance_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD


;HRESULT
IClassFactory_RemoteLockServer_Proxy proto WINAPI \
		 _This: ptr IClassFactory,
		 fLock: BOOL


;void
IClassFactory_RemoteLockServer_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

;HRESULT
IClassFactory_CreateInstance_Proxy proto WINAPI \
		 _This: ptr IClassFactory,
	     pUnkOuter: ptr IUnknown,
		  riid: REFIID

;HRESULT
IClassFactory_CreateInstance_Stub proto WINAPI \
		 _This: ptr IClassFactory,
		  riid: REFIID,
	     ppvObject: ptr IUnknown

;HRESULT
IClassFactory_LockServer_Proxy proto WINAPI \
		 _This: ptr IClassFactory,
		 fLock: BOOL

;HRESULT
IClassFactory_LockServer_Stub proto WINAPI \
		 _This: ptr IClassFactory,
		 fLock: BOOL

.list
endif
