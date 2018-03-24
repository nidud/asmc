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
ifndef __objidl_h__
__objidl_h__ equ 1
.xlist

ifndef __IMarshal_FWD_DEFINED__
__IMarshal_FWD_DEFINED__ equ 1
endif

ifndef __IMalloc_FWD_DEFINED__
__IMalloc_FWD_DEFINED__ equ 1
endif

ifndef __IMallocSpy_FWD_DEFINED__
__IMallocSpy_FWD_DEFINED__ equ 1
endif

ifndef __IStdMarshalInfo_FWD_DEFINED__
__IStdMarshalInfo_FWD_DEFINED__ equ 1
endif

ifndef __IExternalConnection_FWD_DEFINED__
__IExternalConnection_FWD_DEFINED__ equ 1
endif

ifndef __IMultiQI_FWD_DEFINED__
__IMultiQI_FWD_DEFINED__ equ 1
endif

ifndef __IEnumUnknown_FWD_DEFINED__
__IEnumUnknown_FWD_DEFINED__ equ 1
endif

ifndef __IBindCtx_FWD_DEFINED__
__IBindCtx_FWD_DEFINED__ equ 1
endif

ifndef __IEnumMoniker_FWD_DEFINED__
__IEnumMoniker_FWD_DEFINED__ equ 1
endif

ifndef __IRunnableObject_FWD_DEFINED__
__IRunnableObject_FWD_DEFINED__ equ 1
endif

ifndef __IRunningObjectTable_FWD_DEFINED__
__IRunningObjectTable_FWD_DEFINED__ equ 1
endif

ifndef __IPersist_FWD_DEFINED__
__IPersist_FWD_DEFINED__ equ 1
endif

ifndef __IPersistStream_FWD_DEFINED__
__IPersistStream_FWD_DEFINED__ equ 1
endif

ifndef __IMoniker_FWD_DEFINED__
__IMoniker_FWD_DEFINED__ equ 1
endif

ifndef __IROTData_FWD_DEFINED__
__IROTData_FWD_DEFINED__ equ 1
endif

ifndef __IEnumString_FWD_DEFINED__
__IEnumString_FWD_DEFINED__ equ 1
endif

ifndef __ISequentialStream_FWD_DEFINED__
__ISequentialStream_FWD_DEFINED__ equ 1
endif

ifndef __IStream_FWD_DEFINED__
__IStream_FWD_DEFINED__ equ 1
endif

ifndef __IEnumSTATSTG_FWD_DEFINED__
__IEnumSTATSTG_FWD_DEFINED__ equ 1
endif

ifndef __IStorage_FWD_DEFINED__
__IStorage_FWD_DEFINED__ equ 1
endif

ifndef __IPersistFile_FWD_DEFINED__
__IPersistFile_FWD_DEFINED__ equ 1
endif

ifndef __IPersistStorage_FWD_DEFINED__
__IPersistStorage_FWD_DEFINED__ equ 1
endif

ifndef __ILockBytes_FWD_DEFINED__
__ILockBytes_FWD_DEFINED__ equ 1
endif

ifndef __IEnumFORMATETC_FWD_DEFINED__
__IEnumFORMATETC_FWD_DEFINED__ equ 1
endif

ifndef __IEnumSTATDATA_FWD_DEFINED__
__IEnumSTATDATA_FWD_DEFINED__ equ 1
endif

ifndef __IRootStorage_FWD_DEFINED__
__IRootStorage_FWD_DEFINED__ equ 1
endif

ifndef __IAdviseSink_FWD_DEFINED__
__IAdviseSink_FWD_DEFINED__ equ 1
endif

ifndef __IAdviseSink2_FWD_DEFINED__
__IAdviseSink2_FWD_DEFINED__ equ 1
endif

ifndef __IDataObject_FWD_DEFINED__
__IDataObject_FWD_DEFINED__ equ 1
endif

ifndef __IDataAdviseHolder_FWD_DEFINED__
__IDataAdviseHolder_FWD_DEFINED__ equ 1
endif

ifndef __IMessageFilter_FWD_DEFINED__
__IMessageFilter_FWD_DEFINED__ equ 1
endif

ifndef __IRpcChannelBuffer_FWD_DEFINED__
__IRpcChannelBuffer_FWD_DEFINED__ equ 1
endif

ifndef __IRpcChannelBuffer2_FWD_DEFINED__
__IRpcChannelBuffer2_FWD_DEFINED__ equ 1
endif

ifndef __IRpcChannelBuffer3_FWD_DEFINED__
__IRpcChannelBuffer3_FWD_DEFINED__ equ 1
endif

ifndef __IRpcProxyBuffer_FWD_DEFINED__
__IRpcProxyBuffer_FWD_DEFINED__ equ 1
endif

ifndef __IRpcStubBuffer_FWD_DEFINED__
__IRpcStubBuffer_FWD_DEFINED__ equ 1
endif

ifndef __IPSFactoryBuffer_FWD_DEFINED__
__IPSFactoryBuffer_FWD_DEFINED__ equ 1
endif

ifndef __IChannelHook_FWD_DEFINED__
__IChannelHook_FWD_DEFINED__ equ 1
endif

ifndef __IPropertyStorage_FWD_DEFINED__
__IPropertyStorage_FWD_DEFINED__ equ 1
endif

ifndef __IPropertySetStorage_FWD_DEFINED__
__IPropertySetStorage_FWD_DEFINED__ equ 1
endif

ifndef __IEnumSTATPROPSTG_FWD_DEFINED__
__IEnumSTATPROPSTG_FWD_DEFINED__ equ 1
endif

ifndef __IEnumSTATPROPSETSTG_FWD_DEFINED__
__IEnumSTATPROPSETSTG_FWD_DEFINED__ equ 1
endif

ifndef __IClientSecurity_FWD_DEFINED__
__IClientSecurity_FWD_DEFINED__ equ 1
endif

ifndef __IServerSecurity_FWD_DEFINED__
__IServerSecurity_FWD_DEFINED__ equ 1
endif

ifndef __IClassActivator_FWD_DEFINED__
__IClassActivator_FWD_DEFINED__ equ 1
endif

ifndef __IRpcOptions_FWD_DEFINED__
__IRpcOptions_FWD_DEFINED__ equ 1
endif

ifndef __IComBinding_FWD_DEFINED__
__IComBinding_FWD_DEFINED__ equ 1
endif

ifndef __IFillLockBytes_FWD_DEFINED__
__IFillLockBytes_FWD_DEFINED__ equ 1
endif

ifndef __IProgressNotify_FWD_DEFINED__
__IProgressNotify_FWD_DEFINED__ equ 1
endif

ifndef __ILayoutStorage_FWD_DEFINED__
__ILayoutStorage_FWD_DEFINED__ equ 1
endif

ifndef __ISurrogate_FWD_DEFINED__
__ISurrogate_FWD_DEFINED__ equ 1
endif

ifndef __IGlobalInterfaceTable_FWD_DEFINED__
__IGlobalInterfaceTable_FWD_DEFINED__ equ 1
endif

ifndef __IDirectWriterLock_FWD_DEFINED__
__IDirectWriterLock_FWD_DEFINED__ equ 1
endif

ifndef __ISynchronize_FWD_DEFINED__
__ISynchronize_FWD_DEFINED__ equ 1
endif

ifndef __ISynchronizeMutex_FWD_DEFINED__
__ISynchronizeMutex_FWD_DEFINED__ equ 1
endif

ifndef __IAsyncSetup_FWD_DEFINED__
__IAsyncSetup_FWD_DEFINED__ equ 1
endif

ifndef __ICancelMethodCalls_FWD_DEFINED__
__ICancelMethodCalls_FWD_DEFINED__ equ 1
endif

ifndef __IAsyncManager_FWD_DEFINED__
__IAsyncManager_FWD_DEFINED__ equ 1
endif

ifndef __IWaitMultiple_FWD_DEFINED__
__IWaitMultiple_FWD_DEFINED__ equ 1
endif

ifndef __ISynchronizeEvent_FWD_DEFINED__
__ISynchronizeEvent_FWD_DEFINED__ equ 1
endif

ifndef __IUrlMon_FWD_DEFINED__
__IUrlMon_FWD_DEFINED__ equ 1
endif

ifndef __IClassAccess_FWD_DEFINED__
__IClassAccess_FWD_DEFINED__ equ 1
endif

ifndef __IClassRefresh_FWD_DEFINED__
__IClassRefresh_FWD_DEFINED__ equ 1
endif

ifndef __IEnumPackage_FWD_DEFINED__
__IEnumPackage_FWD_DEFINED__ equ 1
endif

ifndef __IEnumClass_FWD_DEFINED__
__IEnumClass_FWD_DEFINED__ equ 1
endif

ifndef __IClassAdmin_FWD_DEFINED__
__IClassAdmin_FWD_DEFINED__ equ 1
endif

include unknwn.inc
.xlist

;void
MIDL_user_free proto WINAPI \
		      : PVOID

SRVINFO			typedef SDWORD
SRVINFO_F_COSERVERINFO	equ 0
SRVINFO_F_COSERVERINFO2 equ 1

LPCOAUTHINFO		typedef ptr COAUTHINFO

COSERVERINFO		STRUC
dwReserved1		dd ?
pwszName		LPWSTR ?
pAuthInfo		LPCOAUTHINFO ?
dwReserved2		dd ?
COSERVERINFO		ENDS

LPIUnknown		typedef ptr IUnknown

COSERVERINFO2		STRUC
dwFlags			dd ?
pwszName		LPWSTR ?
pAuthInfo		LPCOAUTHINFO ?
ppCall			LPIUnknown ?
pwszCodeURL		LPWSTR ?
dwFileVersionMS		dd ?
dwFileVersionLS		dd ?
pwszContentType		LPWSTR ?
COSERVERINFO2		ENDS

externdef		__MIDL_itf_objidl_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_objidl_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IMarshal_INTERFACE_DEFINED__
__IMarshal_INTERFACE_DEFINED__ equ 1

IMarshalVtbl struct
STDMETHOD QueryInterface, :REFIID, :ptr
STDMETHOD AddRef
STDMETHOD Release
STDMETHOD GetUnmarshalClass, :REFIID, :ptr ,:DWORD, :ptr, :DWORD, :ptr
STDMETHOD GetMarshalSizeMax, :REFIID, :ptr ,:DWORD, :ptr, :DWORD, :ptr
STDMETHOD MarshalInterface, :ptr, :REFIID, :ptr, :DWORD, :ptr, :DWORD
STDMETHOD UnmarshalInterface, :ptr, :REFIID, :ptr
STDMETHOD ReleaseMarshalData, :ptr
STDMETHOD DisconnectObject, :DWORD
IMarshalVtbl ends
IMarshal struct
	lpVtbl		PVOID ?
IMarshal ends
LPMARSHAL		typedef ptr IMarshal
externdef		IID_IMarshal:IID

;HRESULT
IMarshal_GetUnmarshalClass_Proxy proto WINAPI \
		 pThis: ptr IMarshal,
		  riid: REFIID,
		    pv: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
	     mshlflags: DWORD,
		  pCid: ptr CLSID

;void
IMarshal_GetUnmarshalClass_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMarshal_GetMarshalSizeMax_Proxy proto WINAPI \
		 pThis: ptr IMarshal,
		  riid: REFIID,
		    pv: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
	     mshlflags: DWORD,
		 pSize: LPDWORD

;void
IMarshal_GetMarshalSizeMax_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMarshal_MarshalInterface_Proxy proto WINAPI \
		 pThis: ptr IMarshal,
		  pStm: ptr IStream,
		  riid: REFIID,
		    pv: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
	     mshlflags: DWORD

;void
IMarshal_MarshalInterface_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMarshal_UnmarshalInterface_Proxy proto WINAPI \
		 pThis: ptr IMarshal,
		  pStm: ptr IStream,
		  riid: REFIID,
		   ppv: PVOID

;void
IMarshal_UnmarshalInterface_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMarshal_ReleaseMarshalData_Proxy proto WINAPI \
		 pThis: ptr IMarshal,
		  pStm: ptr IStream

;void
IMarshal_ReleaseMarshalData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMarshal_DisconnectObject_Proxy proto WINAPI \
		 pThis: ptr IMarshal,
	    dwReserved: DWORD

;void
IMarshal_DisconnectObject_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IMalloc_INTERFACE_DEFINED__
__IMalloc_INTERFACE_DEFINED__ equ 1

IMallocVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Alloc, :DWORD
	STDMETHOD	Realloc, :ptr ,:DWORD
	STDMETHOD	Free, :ptr
	STDMETHOD	GetSize, :ptr
	STDMETHOD	DidAlloc, :ptr
	STDMETHOD	HeapMinimize
IMallocVtbl ends
IMalloc struct
	lpVtbl		PVOID ?
IMalloc ends
LPMALLOC		typedef ptr IMalloc
externdef		IID_IMalloc:IID

;PVOID
IMalloc_Alloc_Proxy proto WINAPI \
		 pThis: ptr IMalloc,
		    cb: ULONG

;void
IMalloc_Alloc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;PVOID
IMalloc_Realloc_Proxy proto WINAPI \
		 pThis: ptr IMalloc,
		    pv: PVOID,
		    cb: ULONG

;void
IMalloc_Realloc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IMalloc_Free_Proxy proto WINAPI \
		 pThis: ptr IMalloc,
		    pv: PVOID

;void
IMalloc_Free_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;ULONG
IMalloc_GetSize_Proxy proto WINAPI \
		 pThis: ptr IMalloc,
		    pv: PVOID

;void
IMalloc_GetSize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;int
IMalloc_DidAlloc_Proxy proto WINAPI \
		 pThis: ptr IMalloc,
		    pv: PVOID

;void
IMalloc_DidAlloc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IMalloc_HeapMinimize_Proxy proto WINAPI \
		 pThis: ptr IMalloc

;void
IMalloc_HeapMinimize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif


ifndef __IMallocSpy_INTERFACE_DEFINED__
__IMallocSpy_INTERFACE_DEFINED__ equ 1

IMallocSpyVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	PreAlloc, :DWORD
	STDMETHOD	PostAlloc, :ptr
	STDMETHOD	PreFree, :ptr, :BOOL
	STDMETHOD	PostFree, :BOOL
	STDMETHOD	PreRealloc, :ptr, :DWORD, :ptr, :BOOL
	STDMETHOD	PostRealloc, :ptr, :BOOL
	STDMETHOD	PreGetSize, :ptr, :BOOL
	STDMETHOD	PostGetSize, :DWORD, :BOOL
	STDMETHOD	PreDidAlloc, :ptr, :BOOL
	STDMETHOD	PostDidAlloc, :ptr, :BOOL, :DWORD
	STDMETHOD	PreHeapMinimize
	STDMETHOD	PostHeapMinimize
IMallocSpyVtbl ends
IMallocSpy struct
	lpVtbl		PVOID ?
IMallocSpy ends
LPMALLOCSPY		typedef ptr IMallocSpy
externdef		IID_IMallocSpy:IID

;ULONG
IMallocSpy_PreAlloc_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy,
	     cbRequest: ULONG

;void
IMallocSpy_PreAlloc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;PVOID
IMallocSpy_PostAlloc_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy,
	       pActual: PVOID

;void
IMallocSpy_PostAlloc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;PVOID
IMallocSpy_PreFree_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL

;void
IMallocSpy_PreFree_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IMallocSpy_PostFree_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy,
		fSpyed: BOOL

;void
IMallocSpy_PostFree_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;ULONG
IMallocSpy_PreRealloc_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
	     cbRequest: ULONG,
	  ppNewRequest: PVOID,
		fSpyed: BOOL

;void
IMallocSpy_PreRealloc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;PVOID
IMallocSpy_PostRealloc_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy,
	       pActual: PVOID,
		fSpyed: BOOL

;void
IMallocSpy_PostRealloc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;PVOID
IMallocSpy_PreGetSize_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL

;void
IMallocSpy_PreGetSize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;ULONG
IMallocSpy_PostGetSize_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy,
	      cbActual: ULONG,
		fSpyed: BOOL

;void
IMallocSpy_PostGetSize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;PVOID
IMallocSpy_PreDidAlloc_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL

;void
IMallocSpy_PreDidAlloc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;int
IMallocSpy_PostDidAlloc_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL,
	       fActual: SINT

;void
IMallocSpy_PostDidAlloc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IMallocSpy_PreHeapMinimize_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy

;void
IMallocSpy_PreHeapMinimize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IMallocSpy_PostHeapMinimize_Proxy proto WINAPI \
		 pThis: ptr IMallocSpy

;void
IMallocSpy_PostHeapMinimize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IStdMarshalInfo_INTERFACE_DEFINED__
__IStdMarshalInfo_INTERFACE_DEFINED__ equ 1

IStdMarshalInfoVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassForHandler, :DWORD, :ptr, :ptr
IStdMarshalInfoVtbl ends
IStdMarshalInfo struct
	lpVtbl		PVOID ?
IStdMarshalInfo ends
LPSTDMARSHALINFO	typedef ptr IStdMarshalInfo
externdef		IID_IStdMarshalInfo:IID

;HRESULT
IStdMarshalInfo_GetClassForHandler_Proxy proto WINAPI \
		 pThis: ptr IStdMarshalInfo,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
		pClsid: ptr CLSID

;void
IStdMarshalInfo_GetClassForHandler_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IExternalConnection_INTERFACE_DEFINED__
__IExternalConnection_INTERFACE_DEFINED__ equ 1

tagEXTCONN		typedef SDWORD
EXTCONN_STRONG		equ 0x1
EXTCONN_WEAK		equ 0x2
EXTCONN_CALLABLE	equ 0x4

IExternalConnectionVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AddConnection, :DWORD, :DWORD
	STDMETHOD	ReleaseConnection, :DWORD, :DWORD, :BOOL
IExternalConnectionVtbl ends
IExternalConnection struct
	lpVtbl		PVOID ?
IExternalConnection ends
LPEXTERNALCONNECTION	typedef ptr IExternalConnection
externdef		IID_IExternalConnection:IID

;DWORD
IExternalConnection_AddConnection_Proxy proto WINAPI \
		 pThis: ptr IExternalConnection,
	       extconn: DWORD,
	      reserved: DWORD

;void
IExternalConnection_AddConnection_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;DWORD
IExternalConnection_ReleaseConnection_Proxy proto WINAPI \
		 pThis: ptr IExternalConnection,
	       extconn: DWORD,
	      reserved: DWORD,
    fLastReleaseCloses: BOOL


;void
IExternalConnection_ReleaseConnection_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif

ifndef __IMultiQI_INTERFACE_DEFINED__
__IMultiQI_INTERFACE_DEFINED__ equ 1

MULTI_QI		STRUC
pIID			LPIID ?
pItf			LPIUnknown ?
hr			HRESULT ?
MULTI_QI		ENDS

IMultiQIVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryMultipleInterfaces, :DWORD, :ptr
IMultiQIVtbl ends
IMultiQI struct
	lpVtbl		PVOID ?
IMultiQI ends
LPMULTIQI		typedef ptr IMultiQI
externdef		IID_IMultiQI:IID

;HRESULT
IMultiQI_QueryMultipleInterfaces_Proxy proto WINAPI \
		 pThis: ptr IMultiQI,
		 cMQIs: ULONG,
		 pMQIs: ptr MULTI_QI

;void
IMultiQI_QueryMultipleInterfaces_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IEnumUnknown_INTERFACE_DEFINED__
__IEnumUnknown_INTERFACE_DEFINED__ equ 1

IEnumUnknownVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :DWORD, :ptr, :ptr
	STDMETHOD	Skip, :DWORD
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumUnknownVtbl ends
IEnumUnknown struct
	lpVtbl		PVOID ?
IEnumUnknown ends
LPENUMUNKNOWN		typedef ptr IEnumUnknown
externdef		IID_IEnumUnknown:IID

;HRESULT
IEnumUnknown_RemoteNext_Proxy proto WINAPI \
		 pThis: ptr IEnumUnknown,
		  celt: ULONG,
		 rgelt: ptr IUnknown,
	  pceltFetched: LPDWORD


;void
IEnumUnknown_RemoteNext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumUnknown_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumUnknown,
		  celt: ULONG


;void
IEnumUnknown_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumUnknown_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumUnknown


;void
IEnumUnknown_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumUnknown_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumUnknown,
		ppenum: ptr IEnumUnknown


;void
IEnumUnknown_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IBindCtx_INTERFACE_DEFINED__
__IBindCtx_INTERFACE_DEFINED__ equ 1

BIND_OPTS		STRUC
cbStruct		dd ?
grfFlags		dd ?
grfMode			dd ?
dwTickCountDeadline	dd ?
BIND_OPTS		ENDS
LPBIND_OPTS		typedef ptr BIND_OPTS

LPCOSERVERINFO		typedef ptr COSERVERINFO

BIND_OPTS2		STRUC
cbStruct		dd ?
grfFlags		dd ?
grfMode			dd ?
dwTickCountDeadline	dd ?
dwTrackFlags		dd ?
dwClassContext		dd ?
locale			LCID ?
pServerInfo		LPCOSERVERINFO ?
BIND_OPTS2		ENDS
LPBIND_OPTS2		typedef ptr BIND_OPTS2

tagBIND_FLAGS		typedef SDWORD
BIND_MAYBOTHERUSER	equ 1
BIND_JUSTTESTEXISTENCE	equ 2

IBindCtxVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	RegisterObjectBound, :ptr
	STDMETHOD	RevokeObjectBound, :ptr
	STDMETHOD	ReleaseBoundObjects
	STDMETHOD	SetBindOptions, :ptr
	STDMETHOD	GetBindOptions, :ptr
	STDMETHOD	GetRunningObjectTable, :ptr
	STDMETHOD	RegisterObjectParam, :LPOLESTR, :ptr
	STDMETHOD	GetObjectParam, :LPOLESTR, :ptr
	STDMETHOD	EnumObjectParam, :ptr
	STDMETHOD	RevokeObjectParam, :LPOLESTR
IBindCtxVtbl ends
IBindCtx struct
	lpVtbl		PVOID ?
IBindCtx ends
LPBC			typedef ptr IBindCtx
LPBINDCTX		typedef ptr IBindCtx
externdef		IID_IBindCtx:IID

;HRESULT
IBindCtx_RegisterObjectBound_Proxy proto WINAPI \
		 pThis: ptr IBindCtx,
		  punk: ptr IUnknown

;void
IBindCtx_RegisterObjectBound_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindCtx_RevokeObjectBound_Proxy proto WINAPI \
		 pThis: ptr IBindCtx,
		  punk: ptr IUnknown

;void
IBindCtx_RevokeObjectBound_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindCtx_ReleaseBoundObjects_Proxy proto WINAPI \
		 pThis: ptr IBindCtx

;void
IBindCtx_ReleaseBoundObjects_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindCtx_RemoteSetBindOptions_Proxy proto WINAPI \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS2

;void
IBindCtx_RemoteSetBindOptions_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindCtx_RemoteGetBindOptions_Proxy proto WINAPI \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS2

;void
IBindCtx_RemoteGetBindOptions_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindCtx_GetRunningObjectTable_Proxy proto WINAPI \
		 pThis: ptr IBindCtx,
		 pprot: ptr IRunningObjectTable

;void
IBindCtx_GetRunningObjectTable_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindCtx_RegisterObjectParam_Proxy proto WINAPI \
		 pThis: ptr IBindCtx,
		pszKey: LPOLESTR,
		  punk: ptr IUnknown

;void
IBindCtx_RegisterObjectParam_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindCtx_GetObjectParam_Proxy proto WINAPI \
		 pThis: ptr IBindCtx,
		pszKey: LPOLESTR,
		 ppunk: ptr IUnknown

;void
IBindCtx_GetObjectParam_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindCtx_EnumObjectParam_Proxy proto WINAPI \
		 pThis: ptr IBindCtx,
		ppenum: ptr IEnumString

;void
IBindCtx_EnumObjectParam_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IBindCtx_RevokeObjectParam_Proxy proto WINAPI \
		 pThis: ptr IBindCtx,
		pszKey: LPOLESTR

;void
IBindCtx_RevokeObjectParam_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IEnumMoniker_INTERFACE_DEFINED__
__IEnumMoniker_INTERFACE_DEFINED__ equ 1

IEnumMonikerVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :DWORD, :ptr, :ptr
	STDMETHOD	Skip, :DWORD
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumMonikerVtbl ends
IEnumMoniker struct
	lpVtbl		PVOID ?
IEnumMoniker ends
LPENUMMONIKER		typedef ptr IEnumMoniker
externdef		IID_IEnumMoniker:IID

;HRESULT
IEnumMoniker_RemoteNext_Proxy proto WINAPI \
		 pThis: ptr IEnumMoniker,
		  celt: ULONG,
		 rgelt: ptr IMoniker,
	  pceltFetched: LPDWORD

;void
IEnumMoniker_RemoteNext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumMoniker_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumMoniker,
		  celt: ULONG

;void
IEnumMoniker_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumMoniker_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumMoniker

;void
IEnumMoniker_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumMoniker_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumMoniker,
		ppenum: ptr IEnumMoniker

;void
IEnumMoniker_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IRunnableObject_INTERFACE_DEFINED__
__IRunnableObject_INTERFACE_DEFINED__ equ 1

IRunnableObjectVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetRunningClass, :LPCLSID
	STDMETHOD	Run, :LPBINDCTX
	STDMETHOD	IsRunning
	STDMETHOD	LockRunning, :BOOL, :BOOL
	STDMETHOD	SetContainedObject, :BOOL
IRunnableObjectVtbl ends
IRunnableObject struct
	lpVtbl		PVOID ?
IRunnableObject ends
LPRUNNABLEOBJECT	typedef ptr IRunnableObject
externdef		IID_IRunnableObject:IID

;HRESULT
IRunnableObject_GetRunningClass_Proxy proto WINAPI \
		 pThis: ptr IRunnableObject,
	       lpClsid: LPCLSID

;void
IRunnableObject_GetRunningClass_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRunnableObject_Run_Proxy proto WINAPI \
		 pThis: ptr IRunnableObject,
		   pbc: LPBINDCTX

;void
IRunnableObject_Run_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRunnableObject_RemoteIsRunning_Proxy proto WINAPI \
		 pThis: ptr IRunnableObject

;void
IRunnableObject_RemoteIsRunning_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRunnableObject_LockRunning_Proxy proto WINAPI \
		 pThis: ptr IRunnableObject,
		 fLock: BOOL,
     fLastUnlockCloses: BOOL

;void
IRunnableObject_LockRunning_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRunnableObject_SetContainedObject_Proxy proto WINAPI \
		 pThis: ptr IRunnableObject,
	    fContained: BOOL

;void
IRunnableObject_SetContainedObject_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IRunningObjectTable_INTERFACE_DEFINED__
__IRunningObjectTable_INTERFACE_DEFINED__ equ 1

IRunningObjectTableVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Register, :DWORD, :ptr, :ptr, :ptr
	STDMETHOD	Revoke, :DWORD
	STDMETHOD	IsRunning, :ptr
	STDMETHOD	GetObject_, :ptr, :ptr
	STDMETHOD	NoteChangeTime, :DWORD, :ptr
	STDMETHOD	GetTimeOfLastChange, :ptr, :ptr
	STDMETHOD	EnumRunning, :ptr
IRunningObjectTableVtbl ends
IRunningObjectTable struct
	lpVtbl		PVOID ?
IRunningObjectTable ends
LPRUNNINGOBJECTTABLE	typedef ptr IRunningObjectTable
externdef		IID_IRunningObjectTable:IID

;HRESULT
IRunningObjectTable_Register_Proxy proto WINAPI \
		 pThis: ptr IRunningObjectTable,
	      grfFlags: DWORD,
	    punkObject: ptr IUnknown,
	 pmkObjectName: ptr IMoniker,
	   pdwRegister: LPDWORD

;void
IRunningObjectTable_Register_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRunningObjectTable_Revoke_Proxy proto WINAPI \
		 pThis: ptr IRunningObjectTable,
	    dwRegister: DWORD

;void
IRunningObjectTable_Revoke_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRunningObjectTable_IsRunning_Proxy proto WINAPI \
		 pThis: ptr IRunningObjectTable,
	 pmkObjectName: ptr IMoniker

;void
IRunningObjectTable_IsRunning_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRunningObjectTable_GetObject_Proxy proto WINAPI \
		 pThis: ptr IRunningObjectTable,
	 pmkObjectName: ptr IMoniker,
	   ppunkObject: ptr IUnknown

;void
IRunningObjectTable_GetObject_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRunningObjectTable_NoteChangeTime_Proxy proto WINAPI \
		 pThis: ptr IRunningObjectTable,
	    dwRegister: DWORD,
	     pfiletime: LPFILETIME

;void
IRunningObjectTable_NoteChangeTime_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRunningObjectTable_GetTimeOfLastChange_Proxy proto WINAPI \
		 pThis: ptr IRunningObjectTable,
	 pmkObjectName: ptr IMoniker,
	     pfiletime: LPFILETIME

;void
IRunningObjectTable_GetTimeOfLastChange_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRunningObjectTable_EnumRunning_Proxy proto WINAPI \
		 pThis: ptr IRunningObjectTable,
	 ppenumMoniker: ptr IEnumMoniker

;void
IRunningObjectTable_EnumRunning_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IPersist_INTERFACE_DEFINED__
__IPersist_INTERFACE_DEFINED__ equ 1

IPersistVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassID, :ptr
IPersistVtbl ends
IPersist struct
	lpVtbl		PVOID ?
IPersist ends
LPPERSIST		typedef ptr IPersist
externdef		IID_IPersist:IID

;HRESULT
IPersist_GetClassID_Proxy proto WINAPI \
		 pThis: ptr IPersist,
	      pClassID: ptr CLSID

;void
IPersist_GetClassID_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IPersistStream_INTERFACE_DEFINED__
__IPersistStream_INTERFACE_DEFINED__ equ 1

IPersistStreamVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassID, :ptr
	STDMETHOD	IsDirty
	STDMETHOD	Load, :ptr
	STDMETHOD	Save, :ptr, :BOOL
	STDMETHOD	GetSizeMax, :ptr
IPersistStreamVtbl ends
IPersistStream struct
	lpVtbl		PVOID ?
IPersistStream ends
LPPERSISTSTREAM		typedef ptr IPersistStream
externdef		IID_IPersistStream:IID

;HRESULT
IPersistStream_IsDirty_Proxy proto WINAPI \
		 pThis: ptr IPersistStream

;void
IPersistStream_IsDirty_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistStream_Load_Proxy proto WINAPI \
		 pThis: ptr IPersistStream,
		  pStm: ptr IStream

;void
IPersistStream_Load_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistStream_Save_Proxy proto WINAPI \
		 pThis: ptr IPersistStream,
		  pStm: ptr IStream,
	   fClearDirty: BOOL

;void
IPersistStream_Save_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistStream_GetSizeMax_Proxy proto WINAPI \
		 pThis: ptr IPersistStream,
	       pcbSize: ptr ULARGE_INTEGER

;void
IPersistStream_GetSizeMax_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IMoniker_INTERFACE_DEFINED__
__IMoniker_INTERFACE_DEFINED__ equ 1

tagMKSYS		typedef SDWORD
MKSYS_NONE		equ 0
MKSYS_GENERICCOMPOSITE	equ 1
MKSYS_FILEMONIKER	equ 2
MKSYS_ANTIMONIKER	equ 3
MKSYS_ITEMMONIKER	equ 4
MKSYS_POINTERMONIKER	equ 5
MKSYS_CLASSMONIKER	equ 7

tagMKREDUCE		typedef SDWORD
MKRREDUCE_ONE		equ 3 SHL 16
MKRREDUCE_TOUSER	equ 2 SHL 16
MKRREDUCE_THROUGHUSER	equ 1 SHL 16
MKRREDUCE_ALL		equ 0

IMonikerVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassID, :ptr
	STDMETHOD	IsDirty
	STDMETHOD	Load, :ptr
	STDMETHOD	Save, :ptr, :BOOL
	STDMETHOD	GetSizeMax, :ptr
	STDMETHOD	BindToObject, :ptr, :ptr, :REFIID, :ptr
	STDMETHOD	BindToStorage, :ptr, :ptr, :REFIID, :ptr
	STDMETHOD	Reduce, :ptr, :DWORD, :ptr, :ptr
	STDMETHOD	ComposeWith, :ptr, :BOOL, :ptr
	STDMETHOD	Enum, :BOOL, :ptr
	STDMETHOD	IsEqual, :ptr
	STDMETHOD	Hash, :ptr
	STDMETHOD	IsRunning, :ptr, :ptr, :ptr
	STDMETHOD	GetTimeOfLastChange, :ptr, :ptr, :ptr
	STDMETHOD	Inverse, :ptr
	STDMETHOD	CommonPrefixWith, :ptr, :ptr
	STDMETHOD	RelativePathTo, :ptr, :ptr
	STDMETHOD	GetDisplayName, :ptr, :ptr, :ptr
	STDMETHOD	ParseDisplayName, :ptr, :ptr, :LPOLESTR, :ptr, :ptr
	STDMETHOD	IsSystemMoniker, :ptr
IMonikerVtbl ends
IMoniker struct
	lpVtbl		PVOID ?
IMoniker ends
LPMONIKER		typedef ptr IMoniker
externdef		IID_IMoniker:IID

;HRESULT
IMoniker_RemoteBindToObject_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	    riidResult: REFIID,
	     ppvResult: ptr IUnknown

;void
IMoniker_RemoteBindToObject_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_RemoteBindToStorage_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
		  riid: REFIID,
		ppvObj: ptr IUnknown

;void
IMoniker_RemoteBindToStorage_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_Reduce_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	dwReduceHowFar: DWORD,
	    ppmkToLeft: ptr IMoniker,
	   ppmkReduced: ptr IMoniker

;void
IMoniker_Reduce_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_ComposeWith_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
	      pmkRight: ptr IMoniker,
     fOnlyIfNotGeneric: BOOL,
	 ppmkComposite: ptr IMoniker

;void
IMoniker_ComposeWith_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_Enum_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
	      fForward: BOOL,
	 ppenumMoniker: ptr IEnumMoniker

;void
IMoniker_Enum_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_IsEqual_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
       pmkOtherMoniker: ptr IMoniker

;void
IMoniker_IsEqual_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_Hash_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
	       pdwHash: LPDWORD

;void
IMoniker_Hash_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_IsRunning_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
       pmkNewlyRunning: ptr IMoniker

;void
IMoniker_IsRunning_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_GetTimeOfLastChange_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	     pFileTime: LPFILETIME

;void
IMoniker_GetTimeOfLastChange_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_Inverse_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
		  ppmk: ptr IMoniker

;void
IMoniker_Inverse_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_CommonPrefixWith_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
	      pmkOther: ptr IMoniker,
	    ppmkPrefix: ptr IMoniker

;void
IMoniker_CommonPrefixWith_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_RelativePathTo_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
	      pmkOther: ptr IMoniker,
	   ppmkRelPath: ptr IMoniker

;void
IMoniker_RelativePathTo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_GetDisplayName_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
       ppszDisplayName: ptr LPOLESTR

;void
IMoniker_GetDisplayName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_ParseDisplayName_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	pszDisplayName: LPOLESTR,
	      pchEaten: LPDWORD,
	       ppmkOut: ptr IMoniker

;void
IMoniker_ParseDisplayName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IMoniker_IsSystemMoniker_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
	      pdwMksys: LPDWORD

;void
IMoniker_IsSystemMoniker_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IROTData_INTERFACE_DEFINED__
__IROTData_INTERFACE_DEFINED__ equ 1

externdef		IID_IROTData:IID

IROTDataVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetComparisonData, :ptr, :DWORD, :ptr
IROTDataVtbl ends
IROTData struct
	lpVtbl		PVOID ?
IROTData ends
LPIROTData		typedef ptr IROTData

;HRESULT
IROTData_GetComparisonData_Proxy proto WINAPI \
		 pThis: ptr IROTData,
		pbData: LPBYTE,
		 cbMax: ULONG,
	       pcbData: LPDWORD

;void
IROTData_GetComparisonData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IEnumString_INTERFACE_DEFINED__
__IEnumString_INTERFACE_DEFINED__ equ 1

IEnumStringVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :DWORD, :ptr, :ptr
	STDMETHOD	Skip, :DWORD
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumStringVtbl ends
IEnumString struct
	lpVtbl		PVOID ?
IEnumString ends
LPENUMSTRING		typedef ptr IEnumString
externdef		IID_IEnumString:IID

;HRESULT
IEnumString_RemoteNext_Proxy proto WINAPI \
		 pThis: ptr IEnumString,
		  celt: ULONG,
		 rgelt: ptr LPOLESTR,
	  pceltFetched: LPDWORD

;void
IEnumString_RemoteNext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumString_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumString,
		  celt: ULONG

;void
IEnumString_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumString_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumString

;void
IEnumString_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumString_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumString,
		ppenum: ptr IEnumString

;void
IEnumString_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __ISequentialStream_INTERFACE_DEFINED__
__ISequentialStream_INTERFACE_DEFINED__ equ 1

externdef		IID_ISequentialStream:IID

ISequentialStreamVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Read, :ptr, :DWORD, :ptr
	STDMETHOD	Write, :ptr, :DWORD, :ptr
ISequentialStreamVtbl ends
ISequentialStream struct
	lpVtbl		PVOID ?
ISequentialStream ends

;HRESULT
ISequentialStream_RemoteRead_Proxy proto WINAPI \
		 pThis: ptr ISequentialStream,
		    pv: LPBYTE,
		    cb: ULONG,
	       pcbRead: LPDWORD

;void
ISequentialStream_RemoteRead_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ISequentialStream_RemoteWrite_Proxy proto WINAPI \
		 pThis: ptr ISequentialStream,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD

;void
ISequentialStream_RemoteWrite_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif

ifndef __IStream_INTERFACE_DEFINED__
__IStream_INTERFACE_DEFINED__ equ 1

STATSTG			STRUC
pwcsName		LPOLESTR ?
_type			dd ?
cbSize			ULARGE_INTEGER <>
mtime			FILETIME <>
ctime			FILETIME <>
atime			FILETIME <>
grfMode			dd ?
grfLocksSupported	dd ?
clsid			CLSID <>
grfStateBits		dd ?
reserved		dd ?
STATSTG			ENDS

STGTY			typedef SDWORD
STGTY_STORAGE		equ 1
STGTY_STREAM		equ 2
STGTY_LOCKBYTES		equ 3
STGTY_PROPERTY		equ 4

STREAM_SEEK		typedef SDWORD
STREAM_SEEK_SET		equ 0
STREAM_SEEK_CUR		equ 1
STREAM_SEEK_END		equ 2

LOCKTYPE		typedef SDWORD
LOCK_WRITE		equ 1
LOCK_EXCLUSIVE		equ 2
LOCK_ONLYONCE		equ 4

IStreamVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Read, :ptr, :DWORD, :ptr
	STDMETHOD	Write, :ptr, :DWORD, :ptr
	STDMETHOD	Seek, :LARGE_INTEGER, :DWORD, :ptr
	STDMETHOD	SetSize, :ULARGE_INTEGER
	STDMETHOD	CopyTo, :ptr, :ULARGE_INTEGER, :ptr, :ptr
	STDMETHOD	Commit, :DWORD
	STDMETHOD	Revert
	STDMETHOD	LockRegion, :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
	STDMETHOD	UnlockRegion, :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
	STDMETHOD	Stat, :ptr, :DWORD
	STDMETHOD	Clone, :ptr
IStreamVtbl ends
IStream struct
	lpVtbl		PVOID ?
IStream ends
LPSTREAM		typedef ptr IStream
externdef		IID_IStream:IID

;HRESULT
IStream_RemoteSeek_Proxy proto WINAPI \
		 pThis: ptr IStream,
	      dlibMove: LARGE_INTEGER,
	      dwOrigin: DWORD,
       plibNewPosition: ptr ULARGE_INTEGER

;void
IStream_RemoteSeek_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStream_SetSize_Proxy proto WINAPI \
		 pThis: ptr IStream,
	    libNewSize: ULARGE_INTEGER

;void
IStream_SetSize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStream_RemoteCopyTo_Proxy proto WINAPI \
		 pThis: ptr IStream,
		  pstm: ptr IStream,
		    cb: ULARGE_INTEGER,
	       pcbRead: ptr ULARGE_INTEGER,
	    pcbWritten: ptr ULARGE_INTEGER

;void
IStream_RemoteCopyTo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStream_Commit_Proxy proto WINAPI \
		 pThis: ptr IStream,
	grfCommitFlags: DWORD

;void
IStream_Commit_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStream_Revert_Proxy proto WINAPI \
		 pThis: ptr IStream

;void
IStream_Revert_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStream_LockRegion_Proxy proto WINAPI \
		 pThis: ptr IStream,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD

;void
IStream_LockRegion_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStream_UnlockRegion_Proxy proto WINAPI \
		 pThis: ptr IStream,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD

;void
IStream_UnlockRegion_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStream_Stat_Proxy proto WINAPI \
		 pThis: ptr IStream,
	      pstatstg: ptr STATSTG,
	   grfStatFlag: DWORD

;void
IStream_Stat_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStream_Clone_Proxy proto WINAPI \
		 pThis: ptr IStream,
		 ppstm: ptr IStream

;void
IStream_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IEnumSTATSTG_INTERFACE_DEFINED__
__IEnumSTATSTG_INTERFACE_DEFINED__ equ 1

IEnumSTATSTGVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :DWORD, :ptr, :ptr
	STDMETHOD	Skip, :DWORD
	STDMETHOD	Reset,
	STDMETHOD	Clone, :ptr
IEnumSTATSTGVtbl ends
IEnumSTATSTG struct
	lpVtbl		PVOID ?
IEnumSTATSTG ends
LPENUMSTATSTG		typedef ptr IEnumSTATSTG
externdef		IID_IEnumSTATSTG:IID

;HRESULT
IEnumSTATSTG_RemoteNext_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATSTG,
		  celt: ULONG,
		 rgelt: ptr STATSTG,
	  pceltFetched: LPDWORD

;void
IEnumSTATSTG_RemoteNext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATSTG_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATSTG,
		  celt: ULONG

;void
IEnumSTATSTG_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATSTG_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATSTG

;void
IEnumSTATSTG_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATSTG_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATSTG,
		ppenum: ptr IEnumSTATSTG

;void
IEnumSTATSTG_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IStorage_INTERFACE_DEFINED__
__IStorage_INTERFACE_DEFINED__ equ 1

RemSNB			STRUC
ulCntStr		dd ?
ulCntChar		dd ?
rgString		OLECHAR ?
RemSNB			ENDS

wireSNB			typedef ptr RemSNB
SNB			typedef ptr OLECHAR

IStorageVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CreateStream, :ptr, :DWORD, :DWORD, :DWORD, :ptr
	STDMETHOD	OpenStream, :ptr, :ptr, :DWORD, :DWORD, :ptr
	STDMETHOD	CreateStorage, :ptr, :DWORD, :DWORD, :DWORD, :ptr
	STDMETHOD	OpenStorage, :ptr, :ptr, :DWORD, :SNB, :DWORD, :ptr
	STDMETHOD	CopyTo, :DWORD, :ptr, :SNB, :ptr
	STDMETHOD	MoveElementTo, :ptr, :ptr, :ptr, :DWORD
	STDMETHOD	Commit, :DWORD
	STDMETHOD	Revert
	STDMETHOD	EnumElements, :DWORD, :ptr, :DWORD, :ptr
	STDMETHOD	DestroyElement, :ptr
	STDMETHOD	RenameElement, :ptr, :ptr
	STDMETHOD	SetElementTimes, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	SetClass, :REFCLSID
	STDMETHOD	SetStateBits, :DWORD, :DWORD
	STDMETHOD	Stat, :ptr, :DWORD
IStorageVtbl ends
IStorage struct
	lpVtbl		PVOID ?
IStorage ends
LPSTORAGE		typedef ptr IStorage
externdef		IID_IStorage:IID

;HRESULT
IStorage_CreateStream_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	       grfMode: DWORD,
	     reserved1: DWORD,
	     reserved2: DWORD,
		 ppstm: ptr IStream

;void
IStorage_CreateStream_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_RemoteOpenStream_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	   cbReserved1: DWORD,
	     reserved1: LPBYTE,
	       grfMode: DWORD,
	     reserved2: DWORD,
		 ppstm: ptr IStream

;void
IStorage_RemoteOpenStream_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_CreateStorage_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	       grfMode: DWORD,
	     reserved1: DWORD,
	     reserved2: DWORD,
		 ppstg: ptr IStorage

;void
IStorage_CreateStorage_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_OpenStorage_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	  pstgPriority: ptr IStorage,
	       grfMode: DWORD,
	    snbExclude: SNB,
	      reserved: DWORD,
		 ppstg: ptr IStorage

;void
IStorage_OpenStorage_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_CopyTo_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	   ciidExclude: DWORD,
	  rgiidExclude: ptr IID,
	    snbExclude: SNB,
	      pstgDest: ptr IStorage

;void
IStorage_CopyTo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_MoveElementTo_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	      pstgDest: ptr IStorage,
	   pwcsNewName: ptr OLECHAR,
	      grfFlags: DWORD

;void
IStorage_MoveElementTo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_Commit_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	grfCommitFlags: DWORD

;void
IStorage_Commit_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_Revert_Proxy proto WINAPI \
		 pThis: ptr IStorage

;void
IStorage_Revert_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_RemoteEnumElements_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	     reserved1: DWORD,
	   cbReserved2: DWORD,
	     reserved2: LPBYTE,
	     reserved3: DWORD,
		ppenum: ptr IEnumSTATSTG

;void
IStorage_RemoteEnumElements_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_DestroyElement_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR

;void
IStorage_DestroyElement_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_RenameElement_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	   pwcsOldName: ptr OLECHAR,
	   pwcsNewName: ptr OLECHAR

;void
IStorage_RenameElement_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_SetElementTimes_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
		pctime: LPFILETIME,
		patime: LPFILETIME,
		pmtime: LPFILETIME

;void
IStorage_SetElementTimes_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_SetClass_Proxy proto WINAPI \
		 pThis: ptr IStorage,
		 clsid: REFCLSID

;void
IStorage_SetClass_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_SetStateBits_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	  grfStateBits: DWORD,
	       grfMask: DWORD

;void
IStorage_SetStateBits_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IStorage_Stat_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	      pstatstg: ptr STATSTG,
	   grfStatFlag: DWORD

;void
IStorage_Stat_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IPersistFile_INTERFACE_DEFINED__
__IPersistFile_INTERFACE_DEFINED__ equ 1

IPersistFileVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassID, :ptr
	STDMETHOD	IsDirty
	STDMETHOD	Load, :LPCOLESTR, :DWORD
	STDMETHOD	Save, :LPCOLESTR, :BOOL
	STDMETHOD	SaveCompleted, :LPCOLESTR
	STDMETHOD	GetCurFile, :ptr
IPersistFileVtbl ends
IPersistFile struct
	lpVtbl		PVOID ?
IPersistFile ends
LPPERSISTFILE		typedef ptr IPersistFile
externdef		IID_IPersistFile:IID

;HRESULT
IPersistFile_IsDirty_Proxy proto WINAPI \
		 pThis: ptr IPersistFile

;void
IPersistFile_IsDirty_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistFile_Load_Proxy proto WINAPI \
		 pThis: ptr IPersistFile,
	   pszFileName: LPCOLESTR,
		dwMode: DWORD

;void
IPersistFile_Load_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistFile_Save_Proxy proto WINAPI \
		 pThis: ptr IPersistFile,
	   pszFileName: LPCOLESTR,
	     fRemember: BOOL

;void
IPersistFile_Save_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistFile_SaveCompleted_Proxy proto WINAPI \
		 pThis: ptr IPersistFile,
	   pszFileName: LPCOLESTR

;void
IPersistFile_SaveCompleted_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistFile_GetCurFile_Proxy proto WINAPI \
		 pThis: ptr IPersistFile,
	  ppszFileName: ptr LPOLESTR

;void
IPersistFile_GetCurFile_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IPersistStorage_INTERFACE_DEFINED__
__IPersistStorage_INTERFACE_DEFINED__ equ 1

IPersistStorageVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassID, :ptr
	STDMETHOD	IsDirty
	STDMETHOD	InitNew, :ptr
	STDMETHOD	Load, :ptr
	STDMETHOD	Save, :ptr, :BOOL
	STDMETHOD	SaveCompleted, :ptr
	STDMETHOD	HandsOffStorage
IPersistStorageVtbl ends
IPersistStorage struct
	lpVtbl		PVOID ?
IPersistStorage ends
LPPERSISTSTORAGE	typedef ptr IPersistStorage
externdef		IID_IPersistStorage:IID

;HRESULT
IPersistStorage_IsDirty_Proxy proto WINAPI \
		 pThis: ptr IPersistStorage

;void
IPersistStorage_IsDirty_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistStorage_InitNew_Proxy proto WINAPI \
		 pThis: ptr IPersistStorage,
		  pStg: ptr IStorage

;void
IPersistStorage_InitNew_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistStorage_Load_Proxy proto WINAPI \
		 pThis: ptr IPersistStorage,
		  pStg: ptr IStorage

;void
IPersistStorage_Load_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistStorage_Save_Proxy proto WINAPI \
		 pThis: ptr IPersistStorage,
	      pStgSave: ptr IStorage,
	   fSameAsLoad: BOOL

;void
IPersistStorage_Save_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistStorage_SaveCompleted_Proxy proto WINAPI \
		 pThis: ptr IPersistStorage,
	       pStgNew: ptr IStorage

;void
IPersistStorage_SaveCompleted_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPersistStorage_HandsOffStorage_Proxy proto WINAPI \
		 pThis: ptr IPersistStorage

;void
IPersistStorage_HandsOffStorage_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __ILockBytes_INTERFACE_DEFINED__
__ILockBytes_INTERFACE_DEFINED__ equ 1

ILockBytesVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ReadAt, :ULARGE_INTEGER, :ptr, :DWORD, :ptr
	STDMETHOD	WriteAt, :ULARGE_INTEGER, :ptr, :DWORD, :ptr
	STDMETHOD	Flush
	STDMETHOD	SetSize, :ULARGE_INTEGER
	STDMETHOD	LockRegion, :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
	STDMETHOD	UnlockRegion, :ULARGE_INTEGER, :ULARGE_INTEGER, :DWORD
	STDMETHOD	Stat, :ptr, :DWORD
ILockBytesVtbl ends
ILockBytes struct
	lpVtbl		PVOID ?
ILockBytes ends
LPLOCKBYTES		typedef ptr ILockBytes
externdef		IID_ILockBytes:IID

;HRESULT
ILockBytes_RemoteReadAt_Proxy proto WINAPI \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	       pcbRead: LPDWORD

;void
ILockBytes_RemoteReadAt_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ILockBytes_RemoteWriteAt_Proxy proto WINAPI \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD

;void
ILockBytes_RemoteWriteAt_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ILockBytes_Flush_Proxy proto WINAPI \
		 pThis: ptr ILockBytes

;void
ILockBytes_Flush_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ILockBytes_SetSize_Proxy proto WINAPI \
		 pThis: ptr ILockBytes,
		    cb: ULARGE_INTEGER

;void
ILockBytes_SetSize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ILockBytes_LockRegion_Proxy proto WINAPI \
		 pThis: ptr ILockBytes,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD

;void
ILockBytes_LockRegion_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ILockBytes_UnlockRegion_Proxy proto WINAPI \
		 pThis: ptr ILockBytes,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD

;void
ILockBytes_UnlockRegion_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ILockBytes_Stat_Proxy proto WINAPI \
		 pThis: ptr ILockBytes,
	      pstatstg: ptr STATSTG,
	   grfStatFlag: DWORD

;void
ILockBytes_Stat_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IEnumFORMATETC_INTERFACE_DEFINED__
__IEnumFORMATETC_INTERFACE_DEFINED__ equ 1

DVTARGETDEVICE		STRUC
tdSize			dd ?
tdDriverNameOffset	dw ?
tdDeviceNameOffset	dw ?
tdPortNameOffset	dw ?
tdExtDevmodeOffset	dw ?
tdData			db ?
DVTARGETDEVICE		ENDS
LPDVTARGETDEVICE	typedef ptr DVTARGETDEVICE

LPCLIPFORMAT		typedef ptr CLIPFORMAT

FORMATETC		STRUC
cfFormat		CLIPFORMAT ?
ptd			LPDVTARGETDEVICE ?
dwAspect		dd ?
lindex			LONG ?
tymed			dd ?
FORMATETC		ENDS
LPFORMATETC		typedef ptr FORMATETC

IEnumFORMATETCVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :DWORD, :ptr, :ptr
	STDMETHOD	Skip, :DWORD
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumFORMATETCVtbl ends
IEnumFORMATETC struct
	lpVtbl		PVOID ?
IEnumFORMATETC ends
LPENUMFORMATETC		typedef ptr IEnumFORMATETC
externdef		IID_IEnumFORMATETC:IID

;HRESULT
IEnumFORMATETC_RemoteNext_Proxy proto WINAPI \
		 pThis: ptr IEnumFORMATETC,
		  celt: ULONG,
		 rgelt: ptr FORMATETC,
	  pceltFetched: LPDWORD

;void
IEnumFORMATETC_RemoteNext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumFORMATETC_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumFORMATETC,
		  celt: ULONG

;void
IEnumFORMATETC_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumFORMATETC_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumFORMATETC

;void
IEnumFORMATETC_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumFORMATETC_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumFORMATETC,
		ppenum: ptr IEnumFORMATETC

;void
IEnumFORMATETC_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IEnumSTATDATA_INTERFACE_DEFINED__
__IEnumSTATDATA_INTERFACE_DEFINED__ equ 1

ADVF			typedef SDWORD
ADVF_NODATA		equ 1
ADVF_PRIMEFIRST		equ 2
ADVF_ONLYONCE		equ 4
ADVF_DATAONSTOP		equ 64
ADVFCACHE_NOHANDLER	equ 8
ADVFCACHE_FORCEBUILTIN	equ 16
ADVFCACHE_ONSAVE	equ 32

LPIAdviseSink		typedef ptr IAdviseSink

STATDATA		STRUC
formatetc		FORMATETC <>
advf			dd ?
pAdvSink		LPIAdviseSink ?
dwConnection		dd ?
STATDATA		ENDS
LPSTATDATA		typedef ptr STATDATA

IEnumSTATDATAVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :DWORD, :ptr, :ptr
	STDMETHOD	Skip, :DWORD
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumSTATDATAVtbl ends
IEnumSTATDATA struct
	lpVtbl		PVOID ?
IEnumSTATDATA ends
LPENUMSTATDATA		typedef ptr IEnumSTATDATA
externdef		IID_IEnumSTATDATA:IID

;HRESULT
IEnumSTATDATA_RemoteNext_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATDATA,
		  celt: ULONG,
		 rgelt: ptr STATDATA,
	  pceltFetched: LPDWORD

;void
IEnumSTATDATA_RemoteNext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATDATA_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATDATA,
		  celt: ULONG

;void
IEnumSTATDATA_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATDATA_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATDATA

;void
IEnumSTATDATA_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATDATA_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATDATA,
		ppenum: ptr IEnumSTATDATA

;void
IEnumSTATDATA_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IRootStorage_INTERFACE_DEFINED__
__IRootStorage_INTERFACE_DEFINED__ equ 1

IRootStorageVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SwitchToFile, :LPOLESTR
IRootStorageVtbl ends
IRootStorage struct
	lpVtbl		PVOID ?
IRootStorage ends
LPROOTSTORAGE		typedef ptr IRootStorage
externdef		IID_IRootStorage:IID

;HRESULT
IRootStorage_SwitchToFile_Proxy proto WINAPI \
		 pThis: ptr IRootStorage,
	       pszFile: LPOLESTR

;void
IRootStorage_SwitchToFile_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IAdviseSink_INTERFACE_DEFINED__
__IAdviseSink_INTERFACE_DEFINED__ equ 1

TYMED			typedef SDWORD
TYMED_HGLOBAL		equ 1
TYMED_FILE		equ 2
TYMED_ISTREAM		equ 4
TYMED_ISTORAGE		equ 8
TYMED_GDI		equ 16
TYMED_MFPICT		equ 32
TYMED_ENHMF		equ 64
TYMED_NULL		equ 0

RemSTGMEDIUM		STRUC
tymed			dd ?
dwHandleType		dd ?
pData			dd ?
pUnkForRelease		dd ?
cbData			dd ?
data_			db ?
RemSTGMEDIUM		ENDS

ifdef NONAMELESSUNION
uSTGMEDIUM		STRUC
tymed			dd ?
UNION u
 hBitmap		HBITMAP ?
 hMetaFilePict		HMETAFILEPICT ?
 hEnhMetaFile		HENHMETAFILE ?
 hGlobal		HGLOBAL ?
 lpszFileName		LPOLESTR ?
 pstm			LPIStream ?
 pstg			LPIStorage ?
ENDS
pUnkForRelease		LPIUnknown ?
uSTGMEDIUM		ENDS
else
LPIStream		typedef ptr IStream
LPIStorage		typedef ptr IStorage
uSTGMEDIUM		STRUC
tymed			dd ?
UNION u
 hBitmap		HBITMAP ?
 hMetaFilePict		HMETAFILEPICT ?
 hEnhMetaFile		HENHMETAFILE ?
 hGlobal		HGLOBAL ?
 lpszFileName		LPOLESTR ?
 pstm			LPIStream ?
 pstg			LPIStorage ?
ENDS
pUnkForRelease		LPIUnknown ?
uSTGMEDIUM		ENDS
endif

GDI_OBJECT		STRUC
ObjectType		dd ?
UNION u
 hBitmap		wireHBITMAP ?
 hPalette		wireHPALETTE ?
ENDS
GDI_OBJECT		ENDS

LPGDI_OBJECT		typedef ptr GDI_OBJECT

userSTGMEDIUM		STRUC
STRUC STGMEDIUM_UNION
 tymed			dd ?
 UNION u
  hMetaFilePict		wireHMETAFILEPICT ?
  hHEnhMetaFile		wireHENHMETAFILE ?
  hGdiHandle		LPGDI_OBJECT ?
  hGlobal		wireHGLOBAL ?
  lpszFileName		LPOLESTR ?
  pstm			LPBYTE ?
  pstg			LPBYTE ?
 ENDS
ENDS
pUnkForRelease		LPIUnknown ?
userSTGMEDIUM		ENDS

wireSTGMEDIUM		typedef ptr userSTGMEDIUM
STGMEDIUM		typedef uSTGMEDIUM
wireASYNC_STGMEDIUM	typedef ptr userSTGMEDIUM
ASYNC_STGMEDIUM		typedef STGMEDIUM
LPSTGMEDIUM		typedef ptr STGMEDIUM

userFLAG_STGMEDIUM	STRUC
ContextFlags		LONG ?
fPassOwnership		LONG ?
Stgmed			userSTGMEDIUM <>
userFLAG_STGMEDIUM	ENDS
wireFLAG_STGMEDIUM	typedef ptr userFLAG_STGMEDIUM

FLAG_STGMEDIUM		STRUC
ContextFlags		LONG ?
fPassOwnership		LONG ?
Stgmed			STGMEDIUM <>
FLAG_STGMEDIUM		ENDS

IAdviseSinkVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnDataChange, :ptr, :ptr
	STDMETHOD	OnViewChange, :DWORD, :SDWORD
	STDMETHOD	OnRename, :ptr
	STDMETHOD	OnSave
	STDMETHOD	OnClose
IAdviseSinkVtbl ends
IAdviseSink struct
	lpVtbl		PVOID ?
IAdviseSink ends
LPADVISESINK		typedef ptr IAdviseSink
externdef		IID_IAdviseSink:IID

;HRESULT
IAdviseSink_RemoteOnDataChange_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
	    pFormatetc: ptr FORMATETC,
	       pStgmed: ptr ASYNC_STGMEDIUM

;void
IAdviseSink_RemoteOnDataChange_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IAdviseSink_RemoteOnViewChange_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
	      dwAspect: DWORD,
		lindex: LONG

;void
IAdviseSink_RemoteOnViewChange_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IAdviseSink_RemoteOnRename_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
		   pmk: ptr IMoniker

;void
IAdviseSink_RemoteOnRename_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IAdviseSink_RemoteOnSave_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager

;void
IAdviseSink_RemoteOnSave_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IAdviseSink_RemoteOnClose_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink

;void
IAdviseSink_RemoteOnClose_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IAdviseSink2_INTERFACE_DEFINED__
__IAdviseSink2_INTERFACE_DEFINED__ equ 1

IAdviseSink2Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnDataChange, :ptr, :ptr
	STDMETHOD	OnViewChange, :DWORD, :SDWORD
	STDMETHOD	OnRename, :ptr
	STDMETHOD	OnSave
	STDMETHOD	OnClose
	STDMETHOD	OnLinkSrcChange, :ptr
IAdviseSink2Vtbl ends
IAdviseSink2 struct
	lpVtbl		PVOID ?
IAdviseSink2 ends
LPADVISESINK2		typedef ptr IAdviseSink2
externdef		IID_IAdviseSink2:IID

;HRESULT
IAdviseSink2_RemoteOnLinkSrcChange_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink2,
		 ppIAM: ptr IAsyncManager,
		   pmk: ptr IMoniker

;void
IAdviseSink2_RemoteOnLinkSrcChange_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IDataObject_INTERFACE_DEFINED__
__IDataObject_INTERFACE_DEFINED__ equ 1

DATADIR			typedef SDWORD
DATADIR_GET		equ 1
DATADIR_SET		equ 2

IDataObjectVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Begin_OnDataChange, :ptr, :ptr
	STDMETHOD	Finish_OnDataChange
	STDMETHOD	Begin_OnViewChange, :DWORD, :SDWORD
	STDMETHOD	Finish_OnViewChange
	STDMETHOD	Begin_OnRename, :ptr
	STDMETHOD	Finish_OnRename
	STDMETHOD	Begin_OnSave
	STDMETHOD	Finish_OnSave
	STDMETHOD	Begin_OnClose
	STDMETHOD	Finish_OnClose
	STDMETHOD	Begin_OnLinkSrcChange, :ptr
	STDMETHOD	Finish_OnLinkSrcChange
IDataObjectVtbl ends
IDataObject struct
	lpVtbl		PVOID ?
IDataObject ends
LPDATAOBJECT		typedef ptr IDataObject
externdef		IID_IDataObject:IID

;HRESULT
IDataObject_RemoteGetData_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	  pformatetcIn: ptr FORMATETC,
	 pRemoteMedium: ptr STGMEDIUM

;void
IDataObject_RemoteGetData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataObject_RemoteGetDataHere_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	 pRemoteMedium: ptr STGMEDIUM

;void
IDataObject_RemoteGetDataHere_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataObject_QueryGetData_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC

;void
IDataObject_QueryGetData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataObject_GetCanonicalFormatEtc_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	  pformatectIn: ptr FORMATETC,
	 pformatetcOut: ptr FORMATETC

;void
IDataObject_GetCanonicalFormatEtc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataObject_RemoteSetData_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr FLAG_STGMEDIUM,
	      fRelease: BOOL

;void
IDataObject_RemoteSetData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataObject_EnumFormatEtc_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	   dwDirection: DWORD,
       ppenumFormatEtc: ptr IEnumFORMATETC

;void
IDataObject_EnumFormatEtc_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataObject_DAdvise_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
		  advf: DWORD,
	      pAdvSink: ptr IAdviseSink,
	 pdwConnection: LPDWORD

;void
IDataObject_DAdvise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataObject_DUnadvise_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	  dwConnection: DWORD

;void
IDataObject_DUnadvise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataObject_EnumDAdvise_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	  ppenumAdvise: ptr IEnumSTATDATA

;void
IDataObject_EnumDAdvise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IDataAdviseHolder_INTERFACE_DEFINED__
__IDataAdviseHolder_INTERFACE_DEFINED__ equ 1

IDataAdviseHolderVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetData, :ptr, :ptr
	STDMETHOD	GetDataHere, :ptr, :ptr
	STDMETHOD	QueryGetData, :ptr
	STDMETHOD	GetCanonicalFormatEtc, :ptr, :ptr
	STDMETHOD	SetData, :ptr, :ptr, :BOOL
	STDMETHOD	EnumFormatEtc, :DWORD, :ptr
	STDMETHOD	DAdvise, :ptr, :DWORD, :ptr, :ptr
	STDMETHOD	DUnadvise, :DWORD
	STDMETHOD	EnumDAdvise, :ptr
IDataAdviseHolderVtbl ends
IDataAdviseHolder struct
	lpVtbl		PVOID ?
IDataAdviseHolder ends
LPDATAADVISEHOLDER	typedef ptr IDataAdviseHolder
externdef		IID_IDataAdviseHolder:IID

;HRESULT
IDataAdviseHolder_Advise_Proxy proto WINAPI \
		 pThis: ptr IDataAdviseHolder,
	   pDataObject: ptr IDataObject,
		 pFetc: ptr FORMATETC,
		  advf: DWORD,
	       pAdvise: ptr IAdviseSink,
	 pdwConnection: LPDWORD

;void
IDataAdviseHolder_Advise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataAdviseHolder_Unadvise_Proxy proto WINAPI \
		 pThis: ptr IDataAdviseHolder,
	  dwConnection: DWORD

;void
IDataAdviseHolder_Unadvise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataAdviseHolder_EnumAdvise_Proxy proto WINAPI \
		 pThis: ptr IDataAdviseHolder,
	  ppenumAdvise: ptr IEnumSTATDATA

;void
IDataAdviseHolder_EnumAdvise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDataAdviseHolder_SendOnDataChange_Proxy proto WINAPI \
		 pThis: ptr IDataAdviseHolder,
	   pDataObject: ptr IDataObject,
	    dwReserved: DWORD,
		  advf: DWORD

;void
IDataAdviseHolder_SendOnDataChange_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif

ifndef __IMessageFilter_INTERFACE_DEFINED__
__IMessageFilter_INTERFACE_DEFINED__ equ 1

CALLTYPE		typedef SDWORD
CALLTYPE_TOPLEVEL		equ 1
CALLTYPE_NESTED			equ 2
CALLTYPE_ASYNC			equ 3
CALLTYPE_TOPLEVEL_CALLPENDING	equ 4
CALLTYPE_ASYNC_CALLPENDING	equ 5

SERVERCALL		typedef SDWORD
SERVERCALL_ISHANDLED		equ 0
SERVERCALL_REJECTED		equ 1
SERVERCALL_RETRYLATER		equ 2

PENDINGTYPE		typedef SDWORD
PENDINGTYPE_TOPLEVEL		equ 1
PENDINGTYPE_NESTED		equ 2

PENDINGMSG		typedef SDWORD
PENDINGMSG_CANCELCALL		equ 0
PENDINGMSG_WAITNOPROCESS	equ 1
PENDINGMSG_WAITDEFPROCESS	equ 2

INTERFACEINFO		STRUC
pUnk			LPIUnknown ?
iid			IID <>
wMethod			dw ?
INTERFACEINFO		ENDS
LPINTERFACEINFO		typedef ptr INTERFACEINFO

IMessageFilterVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	HandleInComingCall, :DWORD, :HTASK, :DWORD, :LPINTERFACEINFO
	STDMETHOD	RetryRejectedCall, :HTASK, :DWORD, :DWORD
	STDMETHOD	MessagePending, :HTASK, :DWORD, :DWORD
IMessageFilterVtbl ends
IMessageFilter struct
	lpVtbl		PVOID ?
IMessageFilter ends
LPMESSAGEFILTER		typedef ptr IMessageFilter
externdef		IID_IMessageFilter:IID

;DWORD
IMessageFilter_HandleInComingCall_Proxy proto WINAPI \
		 pThis: ptr IMessageFilter,
	    dwCallType: DWORD,
	   htaskCaller: HTASK,
	   dwTickCount: DWORD,
       lpInterfaceInfo: LPINTERFACEINFO

;void
IMessageFilter_HandleInComingCall_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;DWORD
IMessageFilter_RetryRejectedCall_Proxy proto WINAPI \
		 pThis: ptr IMessageFilter,
	   htaskCallee: HTASK,
	   dwTickCount: DWORD,
	  dwRejectType: DWORD

;void
IMessageFilter_RetryRejectedCall_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;DWORD
IMessageFilter_MessagePending_Proxy proto WINAPI \
		 pThis: ptr IMessageFilter,
	   htaskCallee: HTASK,
	   dwTickCount: DWORD,
	 dwPendingType: DWORD

;void
IMessageFilter_MessagePending_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IRpcChannelBuffer_INTERFACE_DEFINED__
__IRpcChannelBuffer_INTERFACE_DEFINED__ equ 1

RPCOLEDATAREP		typedef DWORD

RPCOLEMESSAGE		STRUC
reserved1		PVOID ?
dataRepresentation	RPCOLEDATAREP ?
Buffer			PVOID ?
cbBuffer		ULONG ?
iMethod			ULONG ?
reserved2		PVOID 5 dup(?)
rpcFlags		ULONG ?
RPCOLEMESSAGE		ENDS

PRPCOLEMESSAGE		typedef ptr RPCOLEMESSAGE

externdef		IID_IRpcChannelBuffer:IID

IRpcChannelBufferVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetBuffer, :ptr, :REFIID
	STDMETHOD	SendReceive, :ptr, :ptr
	STDMETHOD	FreeBuffer, :ptr
	STDMETHOD	GetDestCtx, :ptr, :ptr
	STDMETHOD	IsConnected
IRpcChannelBufferVtbl ends
IRpcChannelBuffer struct
	lpVtbl		PVOID ?
IRpcChannelBuffer ends

;HRESULT
IRpcChannelBuffer_GetBuffer_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer,
	      pMessage: ptr RPCOLEMESSAGE,
		  riid: REFIID

;void
IRpcChannelBuffer_GetBuffer_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcChannelBuffer_SendReceive_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer,
	      pMessage: ptr RPCOLEMESSAGE,
	       pStatus: LPDWORD

;void
IRpcChannelBuffer_SendReceive_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcChannelBuffer_FreeBuffer_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer,
	      pMessage: ptr RPCOLEMESSAGE

;void
IRpcChannelBuffer_FreeBuffer_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcChannelBuffer_GetDestCtx_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer,
	pdwDestContext: LPDWORD,
	ppvDestContext: PVOID

;void
IRpcChannelBuffer_GetDestCtx_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcChannelBuffer_IsConnected_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer

;void
IRpcChannelBuffer_IsConnected_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IRpcChannelBuffer2_INTERFACE_DEFINED__
__IRpcChannelBuffer2_INTERFACE_DEFINED__ equ 1

externdef		IID_IRpcChannelBuffer2:IID

IRpcChannelBuffer2Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetBuffer, :ptr, :REFIID
	STDMETHOD	SendReceive, :ptr, :ptr
	STDMETHOD	FreeBuffer, :ptr
	STDMETHOD	GetDestCtx, :ptr, :ptr
	STDMETHOD	IsConnected
	STDMETHOD	GetProtocolVersion, :ptr
IRpcChannelBuffer2Vtbl ends
IRpcChannelBuffer2 struct
	lpVtbl		PVOID ?
IRpcChannelBuffer2 ends

;HRESULT
IRpcChannelBuffer2_GetProtocolVersion_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer2,
	    pdwVersion: LPDWORD

;void
IRpcChannelBuffer2_GetProtocolVersion_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IRpcChannelBuffer3_INTERFACE_DEFINED__
__IRpcChannelBuffer3_INTERFACE_DEFINED__ equ 1

externdef		IID_IRpcChannelBuffer3:IID

IRpcChannelBuffer3Vtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetBuffer, :ptr, :REFIID
	STDMETHOD	SendReceive, :ptr, :ptr
	STDMETHOD	FreeBuffer, :ptr
	STDMETHOD	GetDestCtx, :ptr, :ptr
	STDMETHOD	IsConnected
	STDMETHOD	GetProtocolVersion, :ptr
	STDMETHOD	Send, :ptr, :ptr
	STDMETHOD	Receive, :ptr, :DWORD, :ptr
	STDMETHOD	Cancel, :ptr
	STDMETHOD	GetCallContext, :ptr, :REFIID, :ptr
	STDMETHOD	GetDestCtxEx, :ptr, :ptr, :ptr
	STDMETHOD	GetState, :ptr, :ptr
	STDMETHOD	RegisterAsync, :ptr, :ptr
IRpcChannelBuffer3Vtbl ends
IRpcChannelBuffer3 struct
	lpVtbl		PVOID ?
IRpcChannelBuffer3 ends

;HRESULT
IRpcChannelBuffer3_Send_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
	     pulStatus: LPDWORD

;void
IRpcChannelBuffer3_Send_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcChannelBuffer3_Receive_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
		ulSize: ULONG,
	     pulStatus: LPDWORD

;void
IRpcChannelBuffer3_Receive_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcChannelBuffer3_Cancel_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE

;void
IRpcChannelBuffer3_Cancel_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcChannelBuffer3_GetCallContext_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
		  riid: REFIID,
	    pInterface: PVOID

;void
IRpcChannelBuffer3_GetCallContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcChannelBuffer3_GetDestCtxEx_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
	pdwDestContext: LPDWORD,
	ppvDestContext: PVOID

;void
IRpcChannelBuffer3_GetDestCtxEx_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcChannelBuffer3_GetState_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
		pState: LPDWORD

;void
IRpcChannelBuffer3_GetState_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcChannelBuffer3_RegisterAsync_Proxy proto WINAPI \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
	     pAsyncMgr: ptr IAsyncManager

;void
IRpcChannelBuffer3_RegisterAsync_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IRpcProxyBuffer_INTERFACE_DEFINED__
__IRpcProxyBuffer_INTERFACE_DEFINED__ equ 1

externdef		IID_IRpcProxyBuffer:IID

IRpcProxyBufferVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Connect, :ptr
	STDMETHOD	Disconnect
IRpcProxyBufferVtbl ends
IRpcProxyBuffer struct
	lpVtbl		PVOID ?
IRpcProxyBuffer ends

;HRESULT
IRpcProxyBuffer_Connect_Proxy proto WINAPI \
		 pThis: ptr IRpcProxyBuffer,
     pRpcChannelBuffer: ptr IRpcChannelBuffer

;void
IRpcProxyBuffer_Connect_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IRpcProxyBuffer_Disconnect_Proxy proto WINAPI \
		 pThis: ptr IRpcProxyBuffer

;void
IRpcProxyBuffer_Disconnect_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IRpcStubBuffer_INTERFACE_DEFINED__
__IRpcStubBuffer_INTERFACE_DEFINED__ equ 1

externdef		IID_IRpcStubBuffer:IID

IRpcStubBufferVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Connect, :ptr
	STDMETHOD	Disconnect
	STDMETHOD	_Invoke, :ptr, :ptr
	STDMETHOD	IsIIDSupported, :REFIID
	STDMETHOD	CountRefs
	STDMETHOD	DebugServerQueryInterface, :ptr
	STDMETHOD	DebugServerRelease, :ptr
IRpcStubBufferVtbl ends
IRpcStubBuffer struct
	lpVtbl		PVOID ?
IRpcStubBuffer ends

;HRESULT
IRpcStubBuffer_Connect_Proxy proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
	    pUnkServer: ptr IUnknown

;void
IRpcStubBuffer_Connect_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IRpcStubBuffer_Disconnect_Proxy proto WINAPI \
		 pThis: ptr IRpcStubBuffer

;void
IRpcStubBuffer_Disconnect_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcStubBuffer_Invoke_Proxy proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
	      _prpcmsg: ptr RPCOLEMESSAGE,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer

;void
IRpcStubBuffer_Invoke_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;IRpcStubBuffer *
;STDMETHODCALLTYPE
IRpcStubBuffer_IsIIDSupported_Proxy typedef proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
		  riid: REFIID

;void
IRpcStubBuffer_IsIIDSupported_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;ULONG
IRpcStubBuffer_CountRefs_Proxy proto WINAPI \
		 pThis: ptr IRpcStubBuffer

;void
IRpcStubBuffer_CountRefs_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcStubBuffer_DebugServerQueryInterface_Proxy proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
		   ppv: PVOID

;void
IRpcStubBuffer_DebugServerQueryInterface_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IRpcStubBuffer_DebugServerRelease_Proxy proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
		    pv: PVOID

;void
IRpcStubBuffer_DebugServerRelease_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IPSFactoryBuffer_INTERFACE_DEFINED__
__IPSFactoryBuffer_INTERFACE_DEFINED__ equ 1

externdef		IID_IPSFactoryBuffer:IID

IPSFactoryBufferVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CreateProxy, :ptr, :REFIID, :ptr, :ptr
	STDMETHOD	CreateStub, :REFIID, :ptr, :ptr
IPSFactoryBufferVtbl ends
IPSFactoryBuffer struct
	lpVtbl		PVOID ?
IPSFactoryBuffer ends

;HRESULT
IPSFactoryBuffer_CreateProxy_Proxy proto WINAPI \
		 pThis: ptr IPSFactoryBuffer,
	     pUnkOuter: ptr IUnknown,
		  riid: REFIID,
	       ppProxy: ptr IRpcProxyBuffer,
		   ppv: PVOID

;void
IPSFactoryBuffer_CreateProxy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPSFactoryBuffer_CreateStub_Proxy proto WINAPI \
		 pThis: ptr IPSFactoryBuffer,
		  riid: REFIID,
	    pUnkServer: ptr IUnknown,
		ppStub: ptr IRpcStubBuffer

;void
IPSFactoryBuffer_CreateStub_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

if  (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)
SChannelHookCallInfo	STRUC
iid			IID <>
cbSize			dd ?
uCausality		GUID <>
dwServerPid		dd ?
iMethod			dd ?
pObject			PVOID ?
SChannelHookCallInfo	ENDS

externdef		__MIDL_itf_objidl_0043_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_objidl_0043_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IChannelHook_INTERFACE_DEFINED__
__IChannelHook_INTERFACE_DEFINED__ equ 1

externdef		IID_IChannelHook:IID

IChannelHookVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ClientGetSize, :REFGUID, :REFIID, :ptr
	STDMETHOD	ClientFillBuffer, :REFGUID, :REFIID, :ptr, :ptr
	STDMETHOD	ClientNotify, :REFGUID, :REFIID, :DWORD, :ptr, :DWORD, :HRESULT
	STDMETHOD	ServerNotify, :REFGUID, :REFIID, :DWORD, :ptr, :DWORD
	STDMETHOD	ServerGetSize, :REFGUID, :REFIID, :HRESULT, :ptr
	STDMETHOD	ServerFillBuffer, :REFGUID, :REFIID, :ptr, :ptr, :HRESULT
IChannelHookVtbl ends
IChannelHook struct
	lpVtbl		PVOID ?
IChannelHook ends

;void
IChannelHook_ClientGetSize_Proxy proto WINAPI \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	     pDataSize: LPDWORD

;void
IChannelHook_ClientGetSize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IChannelHook_ClientFillBuffer_Proxy proto WINAPI \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	     pDataSize: LPDWORD,
	   pDataBuffer: PVOID

;void
IChannelHook_ClientFillBuffer_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IChannelHook_ClientNotify_Proxy proto WINAPI \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	    cbDataSize: ULONG,
	   pDataBuffer: PVOID,
	      lDataRep: DWORD,
	       hrFault: HRESULT

;void
IChannelHook_ClientNotify_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IChannelHook_ServerNotify_Proxy proto WINAPI \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	    cbDataSize: ULONG,
	   pDataBuffer: PVOID,
	      lDataRep: DWORD

;void
IChannelHook_ServerNotify_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IChannelHook_ServerGetSize_Proxy proto WINAPI \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	       hrFault: HRESULT,
	     pDataSize: LPDWORD

;void
IChannelHook_ServerGetSize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;void
IChannelHook_ServerFillBuffer_Proxy proto WINAPI \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	     pDataSize: LPDWORD,
	   pDataBuffer: PVOID,
	       hrFault: HRESULT

;void
IChannelHook_ServerFillBuffer_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif
endif

externdef		__MIDL_itf_objidl_0044_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_objidl_0044_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPropertyStorage_INTERFACE_DEFINED__
__IPropertyStorage_INTERFACE_DEFINED__ equ 1

externdef		FMTID_SummaryInformation:FMTID
externdef		FMTID_DocSummaryInformation:FMTID
externdef		FMTID_UserDefinedProperties:FMTID

PROPSETFLAG_DEFAULT	equ 0
PROPSETFLAG_NONSIMPLE	equ 1
PROPSETFLAG_ANSI	equ 2

PROPSETFLAG_UNBUFFERED	equ 4

CAUB			STRUC
cElems			ULONG ?
pElems			LPBYTE ?
CAUB			ENDS

LPSWORD			typedef ptr SWORD

CAI			STRUC
cElems			ULONG ?
pElems			PSHORT ?
CAI			ENDS

CAUI			STRUC
cElems			ULONG ?
pElems			LPWORD ?
CAUI			ENDS

CAL			STRUC
cElems			ULONG ?
pElems			LPLONG ?
CAL			ENDS

CAUL			STRUC
cElems			ULONG ?
pElems			LPDWORD ?
CAUL			ENDS

LPFLOAT			typedef ptr REAL4
CAFLT			STRUC
cElems			ULONG ?
pElems			LPFLOAT ?
CAFLT			ENDS

LPDOUBLE		typedef ptr DOUBLE

CADBL			STRUC
cElems			ULONG ?
pElems			LPDOUBLE ?
CADBL			ENDS

CACY			STRUC
cElems			ULONG ?
pElems			LPCY ?
CACY			ENDS

LPDATE			typedef ptr DATE

CADATE			STRUC
cElems			ULONG ?
pElems			LPDATE ?
CADATE			ENDS

CABSTR			STRUC
cElems			ULONG ?
pElems			LPBSTR ?
CABSTR			ENDS

CABSTRBLOB		STRUC
cElems			ULONG ?
pElems			LPBSTRBLOB ?
CABSTRBLOB		ENDS

LPVARIANT_BOOL		typedef ptr VARIANT_BOOL
CABOOL			STRUC
cElems			ULONG ?
pElems			LPVARIANT_BOOL ?
CABOOL			ENDS

LPSCODE			typedef ptr SCODE
CASCODE			STRUC
cElems			ULONG ?
pElems			LPSCODE ?
CASCODE			ENDS

LPPROPVARIANT		typedef ptr PROPVARIANT
CAPROPVARIANT		STRUC
cElems			ULONG ?
pElems			LPPROPVARIANT ?
CAPROPVARIANT		ENDS

LPLARGE_INTEGER		typedef ptr LARGE_INTEGER
CAH			STRUC
cElems			ULONG ?
pElems			LPLARGE_INTEGER ?
CAH			ENDS

LPULARGE_INTEGER	typedef ptr ULARGE_INTEGER
CAUH			STRUC
cElems			ULONG ?
pElems			LPULARGE_INTEGER ?
CAUH			ENDS

CALPSTR			STRUC
cElems			ULONG ?
pElems			LPSTR ?
CALPSTR			ENDS

CALPWSTR		STRUC
cElems			ULONG ?
pElems			LPWSTR ?
CALPWSTR		ENDS

CAFILETIME		STRUC
cElems			ULONG ?
pElems			LPFILETIME ?
CAFILETIME		ENDS

LPCLIPDATA		typedef ptr CLIPDATA
CACLIPDATA		STRUC
cElems			ULONG ?
pElems			LPCLIPDATA ?
CACLIPDATA		ENDS

CACLSID			STRUC
cElems			ULONG ?
pElems			LPCLSID ?
CACLSID			ENDS

PROPVARIANT		STRUC
vt			VARTYPE ?
wReserved1		dw ?
wReserved2		dw ?
wReserved3		dw ?
UNION
bVal			db ?
iVal			sword ?
uiVal			dw ?
boolVal			VARIANT_BOOL ?
bool			VARIANT_BOOL ?
lVal			LONG ?
ulVal			ULONG ?
fltVal			REAL4 ?
scode			SCODE ?
hVal			LARGE_INTEGER <>
uhVal			ULARGE_INTEGER <>
dblVal			DOUBLE ?
cyVal			CY <>
date			DATE ?
filetime		FILETIME <>
puuid			LPCLSID ?
blob			BLOB <>
pclipdata		LPCLIPDATA ?
pStream			LPIStream ?
pStorage		LPIStorage ?
bstrVal			BSTR ?
bstrblobVal		BSTRBLOB <>
pszVal			LPSTR ?
pwszVal			LPWSTR ?
caub			CAUB <>
cai			CAI <>
caui			CAUI <>
cabool			CABOOL <>
cal			CAL <>
caul			CAUL <>
caflt			CAFLT <>
cascode			CASCODE <>
cah			CAH <>
cauh			CAUH <>
cadbl			CADBL <>
cacy			CACY <>
cadate			CADATE <>
cafiletime		CAFILETIME <>
cauuid			CACLSID <>
caclipdata		CACLIPDATA <>
cabstr			CABSTR <>
cabstrblob		CABSTRBLOB <>
calpstr			CALPSTR <>
calpwstr		CALPWSTR <>
capropvar		CAPROPVARIANT <>
ENDS
PROPVARIANT		ENDS

LPPROPVARIANT		typedef ptr PROPVARIANT

PID_DICTIONARY		equ 0
PID_CODEPAGE		equ 0x1
PID_FIRST_USABLE	equ 0x2
PID_FIRST_NAME_DEFAULT	equ 0xfff
PID_LOCALE		equ 0x80000000
PID_MODIFY_TIME		equ 0x80000001
PID_SECURITY		equ 0x80000002
PID_ILLEGAL		equ 0xffffffff


PIDSI_TITLE		equ 0x00000002
PIDSI_SUBJECT		equ 0x00000003
PIDSI_AUTHOR		equ 0x00000004
PIDSI_KEYWORDS		equ 0x00000005
PIDSI_COMMENTS		equ 0x00000006
PIDSI_TEMPLATE		equ 0x00000007
PIDSI_LASTAUTHOR	equ 0x00000008
PIDSI_REVNUMBER		equ 0x00000009
PIDSI_EDITTIME		equ 0x0000000a
PIDSI_LASTPRINTED	equ 0x0000000b
PIDSI_CREATE_DTM	equ 0x0000000c
PIDSI_LASTSAVE_DTM	equ 0x0000000d
PIDSI_PAGECOUNT		equ 0x0000000e
PIDSI_WORDCOUNT		equ 0x0000000f
PIDSI_CHARCOUNT		equ 0x00000010
PIDSI_THUMBNAIL		equ 0x00000011
PIDSI_APPNAME		equ 0x00000012
PIDSI_DOC_SECURITY	equ 0x00000013
PRSPEC_INVALID		equ 0xffffffff

PRSPEC_LPWSTR		equ 0

PRSPEC_PROPID		equ 1

PROPSPEC		STRUC
ulKind			ULONG ?
UNION
 propid			PROPID ?
 lpwstr			LPOLESTR ?
ENDS
PROPSPEC		ENDS

STATPROPSTG		STRUC
lpwstrName		LPOLESTR ?
propid			PROPID ?
vt			VARTYPE ?
STATPROPSTG		ENDS

PROPSETHDR_OSVER_KIND macro dwOSVer
	exitm<HIWORD( (dwOSVer) )>
	endm
PROPSETHDR_OSVER_MAJOR macro dwOSVer
	exitm<LOBYTE(LOWORD( (dwOSVer) ))>
	endm
PROPSETHDR_OSVER_MINOR macro dwOSVer
	exitm<HIBYTE(LOWORD( (dwOSVer) ))>
	endm
PROPSETHDR_OSVERSION_UNKNOWN equ 0xFFFFFFFF
STATPROPSETSTG		STRUC
fmtid			FMTID <>
clsid			CLSID <>
grfFlags		dd ?
mtime			FILETIME <>
ctime			FILETIME <>
atime			FILETIME <>
dwOSVersion		dd ?
STATPROPSETSTG		ENDS


IPropertyStorageVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ReadMultiple, :ULONG, :PROPSPEC, :PROPVARIANT
	STDMETHOD	WriteMultiple, :ULONG, :PROPSPEC, :PROPVARIANT, :PROPID
	STDMETHOD	DeleteMultiple, :ULONG, :PROPSPEC
	STDMETHOD	ReadPropertyNames, :ULONG, :PROPID, :LPOLESTR
	STDMETHOD	WritePropertyNames, :ULONG, :PROPID, :LPOLESTR
	STDMETHOD	DeletePropertyNames, :ULONG, :PROPID
	STDMETHOD	Commit, :DWORD
	STDMETHOD	Revert
	STDMETHOD	Enum, :ptr
	STDMETHOD	SetTimes, :ptr, :ptr, :ptr
	STDMETHOD	SetClass, :REFCLSID
	STDMETHOD	Stat, :ptr
IPropertyStorageVtbl ends
IPropertyStorage struct
	lpVtbl		PVOID ?
IPropertyStorage ends
LPPROPERTYSTORAGE	typedef ptr IPropertyStorage
externdef		IID_IPropertyStorage:IID

;HRESULT
IPropertyStorage_ReadMultiple_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage,
		cpspec: ULONG,
	       rgpspec: PROPSPEC,
	     rgpropvar: PROPVARIANT

;void
IPropertyStorage_ReadMultiple_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertyStorage_WriteMultiple_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage,
		cpspec: ULONG,
	       rgpspec: PROPSPEC,
	     rgpropvar: PROPVARIANT,
       propidNameFirst: PROPID

;void
IPropertyStorage_WriteMultiple_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertyStorage_DeleteMultiple_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage,
		cpspec: ULONG,
	       rgpspec: PROPSPEC

;void
IPropertyStorage_DeleteMultiple_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertyStorage_ReadPropertyNames_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage,
	       cpropid: ULONG,
	      rgpropid: PROPID,
	  rglpwstrName: LPOLESTR

;void
IPropertyStorage_ReadPropertyNames_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertyStorage_WritePropertyNames_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage,
	       cpropid: ULONG,
	      rgpropid: PROPID,
	  rglpwstrName: LPOLESTR

;void
IPropertyStorage_WritePropertyNames_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertyStorage_DeletePropertyNames_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage,
	       cpropid: ULONG,
	      rgpropid: PROPID

;void
IPropertyStorage_DeletePropertyNames_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertyStorage_Commit_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage,
	grfCommitFlags: DWORD

;void
IPropertyStorage_Commit_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertyStorage_Revert_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage

;void
IPropertyStorage_Revert_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertyStorage_Enum_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage,
		ppenum: ptr IEnumSTATPROPSTG

;void
IPropertyStorage_Enum_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertyStorage_SetTimes_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage,
		pctime: LPFILETIME,
		patime: LPFILETIME,
		pmtime: LPFILETIME

;void
IPropertyStorage_SetTimes_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertyStorage_SetClass_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage,
		 clsid: REFCLSID

;void
IPropertyStorage_SetClass_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertyStorage_Stat_Proxy proto WINAPI \
		 pThis: ptr IPropertyStorage,
	    pstatpsstg: ptr STATPROPSETSTG

;void
IPropertyStorage_Stat_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IPropertySetStorage_INTERFACE_DEFINED__
__IPropertySetStorage_INTERFACE_DEFINED__ equ 1

IPropertySetStorageVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
IPropertySetStorageVtbl ends
IPropertySetStorage struct
	lpVtbl		PVOID ?
IPropertySetStorage ends
LPPROPERTYSETSTORAGE	typedef ptr IPropertySetStorage
externdef		IID_IPropertySetStorage:IID

;HRESULT
IPropertySetStorage_Create_Proxy proto WINAPI \
		 pThis: ptr IPropertySetStorage,
		rfmtid: REFFMTID,
		pclsid: ptr CLSID,
	      grfFlags: DWORD,
	       grfMode: DWORD,
	       ppprstg: ptr IPropertyStorage

;void
IPropertySetStorage_Create_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertySetStorage_Open_Proxy proto WINAPI \
		 pThis: ptr IPropertySetStorage,
		rfmtid: REFFMTID,
	       grfMode: DWORD,
	       ppprstg: ptr IPropertyStorage

;void
IPropertySetStorage_Open_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertySetStorage_Delete_Proxy proto WINAPI \
		 pThis: ptr IPropertySetStorage,
		rfmtid: REFFMTID

;void
IPropertySetStorage_Delete_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IPropertySetStorage_Enum_Proxy proto WINAPI \
		 pThis: ptr IPropertySetStorage,
		ppenum: ptr IEnumSTATPROPSETSTG

;void
IPropertySetStorage_Enum_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IEnumSTATPROPSTG_INTERFACE_DEFINED__
__IEnumSTATPROPSTG_INTERFACE_DEFINED__ equ 1

IEnumSTATPROPSTGVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
IEnumSTATPROPSTGVtbl ends
IEnumSTATPROPSTG struct
	lpVtbl		PVOID ?
IEnumSTATPROPSTG ends
LPENUMSTATPROPSTG	typedef ptr IEnumSTATPROPSTG
externdef		IID_IEnumSTATPROPSTG:IID

;HRESULT
IEnumSTATPROPSTG_RemoteNext_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATPROPSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSTG,
	  pceltFetched: LPDWORD

;void
IEnumSTATPROPSTG_RemoteNext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATPROPSTG_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATPROPSTG,
		  celt: ULONG

;void
IEnumSTATPROPSTG_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATPROPSTG_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATPROPSTG

;void
IEnumSTATPROPSTG_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATPROPSTG_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATPROPSTG,
		ppenum: ptr IEnumSTATPROPSTG

;void
IEnumSTATPROPSTG_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IEnumSTATPROPSETSTG_INTERFACE_DEFINED__
__IEnumSTATPROPSETSTG_INTERFACE_DEFINED__ equ 1

IEnumSTATPROPSETSTGVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
IEnumSTATPROPSETSTGVtbl ends
IEnumSTATPROPSETSTG struct
	lpVtbl		PVOID ?
IEnumSTATPROPSETSTG ends
LPENUMSTATPROPSETSTG	typedef ptr IEnumSTATPROPSETSTG
externdef		IID_IEnumSTATPROPSETSTG:IID

;HRESULT
IEnumSTATPROPSETSTG_RemoteNext_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATPROPSETSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSETSTG,
	  pceltFetched: LPDWORD


;void
IEnumSTATPROPSETSTG_RemoteNext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATPROPSETSTG_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATPROPSETSTG,
		  celt: ULONG

;void
IEnumSTATPROPSETSTG_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATPROPSETSTG_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATPROPSETSTG

;void
IEnumSTATPROPSETSTG_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumSTATPROPSETSTG_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATPROPSETSTG,
		ppenum: ptr IEnumSTATPROPSETSTG

;void
IEnumSTATPROPSETSTG_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

PropVariantCopy proto WINAPI \
	      pvarDest: ptr PROPVARIANT,
	       pvarSrc: ptr PROPVARIANT

PropVariantClear proto WINAPI \
		  pvar: ptr PROPVARIANT

FreePropVariantArray proto WINAPI \
	     cVariants: ULONG,
		rgvars: ptr PROPVARIANT

_PROPVARIANTINIT_DEFINED_ equ 1
PropVariantInit macro pvar
	exitm<memset ( pvar, 0, sizeof(PROPVARIANT) )>
	endm


ifndef _STGCREATEPROPSTG_DEFINED_
;WINOLEAPI
StgCreatePropStg proto WINAPI \
		  pUnk: ptr IUnknown,
		 fmtid: REFFMTID,
		pclsid: ptr CLSID,
	      grfFlags: DWORD,
	    dwReserved: DWORD,
	     ppPropStg: ptr IPropertyStorage

StgOpenPropStg proto WINAPI \
		  pUnk: ptr IUnknown,
		 fmtid: REFFMTID,
	      grfFlags: DWORD,
	    dwReserved: DWORD,
	     ppPropStg: ptr IPropertyStorage

StgCreatePropSetStg proto WINAPI \
	      pStorage: ptr IStorage,
	    dwReserved: DWORD,
	  ppPropSetStg: ptr IPropertySetStorage


CCH_MAX_PROPSTG_NAME	equ 31
;WINOLEAPI
FmtIdToPropStgName proto WINAPI \
		pfmtid: ptr FMTID,
	       oszName: LPOLESTR

PropStgNameToFmtId proto WINAPI \
	       oszName: LPOLESTR,
		pfmtid: ptr FMTID

endif
if  (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)


externdef		__MIDL_itf_objidl_0048_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_objidl_0048_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IClientSecurity_INTERFACE_DEFINED__
__IClientSecurity_INTERFACE_DEFINED__ equ 1

LPOLECHAR		typedef ptr OLECHAR

SOLE_AUTHENTICATION_SERVICE STRUC
dwAuthnSvc		dd ?
dwAuthzSvc		dd ?
pPrincipalName		LPOLECHAR ?
hr			HRESULT ?
SOLE_AUTHENTICATION_SERVICE ENDS

PSOLE_AUTHENTICATION_SERVICE typedef ptr SOLE_AUTHENTICATION_SERVICE

EOLE_AUTHENTICATION_CAPABILITIES typedef SDWORD
EOAC_NONE		equ 0
EOAC_MUTUAL_AUTH	equ 0x1
EOAC_CLOAKING		equ 0x10
EOAC_SECURE_REFS	equ 0x2
EOAC_ACCESS_CONTROL	equ 0x4
EOAC_APPID		equ 0x8

externdef		IID_IClientSecurity:IID

IClientSecurityVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryBlanket, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	SetBlanket, :ptr, :DWORD, :DWORD, :ptr, :DWORD, :DWORD, :ptr ,:DWORD
	STDMETHOD	CopyProxy, :ptr, :ptr
IClientSecurityVtbl ends
IClientSecurity struct
	lpVtbl		PVOID ?
IClientSecurity ends

;HRESULT
IClientSecurity_QueryBlanket_Proxy proto WINAPI \
		 pThis: ptr IClientSecurity,
		pProxy: ptr IUnknown,
	     pAuthnSvc: LPDWORD,
	     pAuthzSvc: LPDWORD,
      pServerPrincName: ptr OLECHAR,
	   pAuthnLevel: LPDWORD,
	     pImpLevel: LPDWORD,
	     pAuthInfo: PVOID,
	  pCapabilites: LPDWORD

;void
IClientSecurity_QueryBlanket_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClientSecurity_SetBlanket_Proxy proto WINAPI \
		 pThis: ptr IClientSecurity,
		pProxy: ptr IUnknown,
	      AuthnSvc: DWORD,
	      AuthzSvc: DWORD,
      pServerPrincName: ptr OLECHAR,
	    AuthnLevel: DWORD,
	      ImpLevel: DWORD,
	     pAuthInfo: PVOID,
	  Capabilities: DWORD

;void
IClientSecurity_SetBlanket_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClientSecurity_CopyProxy_Proxy proto WINAPI \
		 pThis: ptr IClientSecurity,
		pProxy: ptr IUnknown,
		ppCopy: ptr IUnknown

;void
IClientSecurity_CopyProxy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IServerSecurity_INTERFACE_DEFINED__
__IServerSecurity_INTERFACE_DEFINED__ equ 1

externdef		IID_IServerSecurity:IID

IServerSecurityVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryBlanket, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr, :ptr
	STDMETHOD	ImpersonateClient
	STDMETHOD	_RevertToSelf
	STDMETHOD	IsImpersonating
IServerSecurityVtbl ends
IServerSecurity struct
	lpVtbl		PVOID ?
IServerSecurity ends

;HRESULT
IServerSecurity_QueryBlanket_Proxy proto WINAPI \
		 pThis: ptr IServerSecurity,
	     pAuthnSvc: LPDWORD,
	     pAuthzSvc: LPDWORD,
      pServerPrincName: ptr OLECHAR,
	   pAuthnLevel: LPDWORD,
	     pImpLevel: LPDWORD,
		pPrivs: PVOID,
	 pCapabilities: LPDWORD

;void
IServerSecurity_QueryBlanket_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IServerSecurity_ImpersonateClient_Proxy proto WINAPI \
		 pThis: ptr IServerSecurity

;void
IServerSecurity_ImpersonateClient_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IServerSecurity_RevertToSelf_Proxy proto WINAPI \
		 pThis: ptr IServerSecurity

;void
IServerSecurity_RevertToSelf_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;BOOL
IServerSecurity_IsImpersonating_Proxy proto WINAPI \
		 pThis: ptr IServerSecurity

;void
IServerSecurity_IsImpersonating_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IClassActivator_INTERFACE_DEFINED__
__IClassActivator_INTERFACE_DEFINED__ equ 1

externdef		IID_IClassActivator:IID

IClassActivatorVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassObject, :REFCLSID, :DWORD, :LCID, :REFIID, :ptr
IClassActivatorVtbl ends
IClassActivator struct
	lpVtbl		PVOID ?
IClassActivator ends

;HRESULT
IClassActivator_GetClassObject_Proxy proto WINAPI \
		 pThis: ptr IClassActivator,
		rclsid: REFCLSID,
	dwClassContext: DWORD,
		locale: LCID,
		  riid: REFIID,
		   ppv: PVOID

;void
IClassActivator_GetClassObject_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IRpcOptions_INTERFACE_DEFINED__
__IRpcOptions_INTERFACE_DEFINED__ equ 1

externdef		IID_IRpcOptions:IID

IRpcOptionsVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Set, :ptr, :DWORD, :DWORD
	STDMETHOD	Query, :ptr, :DWORD, :ptr
IRpcOptionsVtbl ends
IRpcOptions struct
	lpVtbl		PVOID ?
IRpcOptions ends

;HRESULT
IRpcOptions_Set_Proxy proto WINAPI \
		 pThis: ptr IRpcOptions,
		  pPrx: ptr IUnknown,
	    dwProperty: DWORD,
	       dwValue: DWORD

;void
IRpcOptions_Set_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcOptions_Query_Proxy proto WINAPI \
		 pThis: ptr IRpcOptions,
		  pPrx: ptr IUnknown,
	    dwProperty: DWORD,
	      pdwValue: LPDWORD

;void
IRpcOptions_Query_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IRpcOptions_CopyProxy_Proxy proto WINAPI \
		 pThis: ptr IRpcOptions,
	     punkProxy: ptr IUnknown,
	     ppunkCopy: ptr IUnknown

;void
IRpcOptions_CopyProxy_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

COMBND_RPCSTRINGS	equ 0x1

externdef		__MIDL_itf_objidl_0052_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_objidl_0052_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IComBinding_INTERFACE_DEFINED__
__IComBinding_INTERFACE_DEFINED__ equ 1

externdef		IID_IComBinding:IID

IComBindingVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	InitBinding, :DWORD, :DWORD, :DWORD, :DWORD, :LPOLESTR
	STDMETHOD	QueryBinding, :ptr, :ptr, :ptr, :ptr, :ptr
IComBindingVtbl ends
IComBinding struct
	lpVtbl		PVOID ?
IComBinding ends

;HRESULT
IComBinding_InitBinding_Proxy proto WINAPI \
		 pThis: ptr IComBinding,
       dwEndpointFlags: DWORD,
	    dwNICFlags: DWORD,
	  mbzReserved1: DWORD,
	  mbzReserved2: DWORD,
	    pszBinding: LPOLESTR

;void
IComBinding_InitBinding_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IComBinding_QueryBinding_Proxy proto WINAPI \
		 pThis: ptr IComBinding,
      pdwEndpointFlags: LPDWORD,
	   pdwNICFlags: LPDWORD,
	  mbzReserved1: LPDWORD,
	  mbzReserved2: LPDWORD,
	   ppszBinding: ptr LPOLESTR

;void
IComBinding_QueryBinding_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif
endif

externdef		__MIDL_itf_objidl_0053_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_objidl_0053_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IFillLockBytes_INTERFACE_DEFINED__
__IFillLockBytes_INTERFACE_DEFINED__ equ 1

externdef		IID_IFillLockBytes:IID

IFillLockBytesVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	FillAppend, :ptr, :DWORD, :ptr
	STDMETHOD	FillAt, :ULARGE_INTEGER, :ptr, :DWORD, :ptr
	STDMETHOD	SetFillSize, :ULARGE_INTEGER
	STDMETHOD	Terminate, :BOOL
IFillLockBytesVtbl ends
IFillLockBytes struct
	lpVtbl		PVOID ?
IFillLockBytes ends

;HRESULT
IFillLockBytes_RemoteFillAppend_Proxy proto WINAPI \
		 pThis: ptr IFillLockBytes,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD

;void
IFillLockBytes_RemoteFillAppend_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IFillLockBytes_RemoteFillAt_Proxy proto WINAPI \
		 pThis: ptr IFillLockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD

;void
IFillLockBytes_RemoteFillAt_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IFillLockBytes_SetFillSize_Proxy proto WINAPI \
		 pThis: ptr IFillLockBytes,
		ulSize: ULARGE_INTEGER

;void
IFillLockBytes_SetFillSize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IFillLockBytes_Terminate_Proxy proto WINAPI \
		 pThis: ptr IFillLockBytes,
	     bCanceled: BOOL

;void
IFillLockBytes_Terminate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IProgressNotify_INTERFACE_DEFINED__
__IProgressNotify_INTERFACE_DEFINED__ equ 1

externdef		IID_IProgressNotify:IID

IProgressNotifyVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnProgress, :DWORD, :DWORD, :BOOL, :BOOL
IProgressNotifyVtbl ends
IProgressNotify struct
	lpVtbl		PVOID ?
IProgressNotify ends

;HRESULT
IProgressNotify_OnProgress_Proxy proto WINAPI \
		 pThis: ptr IProgressNotify,
     dwProgressCurrent: DWORD,
     dwProgressMaximum: DWORD,
	     fAccurate: BOOL,
		fOwner: BOOL

;void
IProgressNotify_OnProgress_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __ILayoutStorage_INTERFACE_DEFINED__
__ILayoutStorage_INTERFACE_DEFINED__ equ 1

StorageLayout		STRUC
LayoutType		dd ?
pwcsElementName		LPOLECHAR ?
cOffset			LARGE_INTEGER <>
cBytes			LARGE_INTEGER <>
StorageLayout		ENDS

externdef		IID_ILayoutStorage:IID

ILayoutStorageVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	LayoutScript, :ptr, :DWORD, :DWORD
	STDMETHOD	BeginMonitor
	STDMETHOD	EndMonitor
	STDMETHOD	ReLayoutDocfile, :ptr
	STDMETHOD	ReLayoutDocfileOnILockBytes, :ptr
ILayoutStorageVtbl ends
ILayoutStorage struct
	lpVtbl		PVOID ?
ILayoutStorage ends

;HRESULT
ILayoutStorage_LayoutScript_Proxy proto WINAPI \
		 pThis: ptr ILayoutStorage,
	pStorageLayout: ptr StorageLayout,
	      nEntries: DWORD,
    glfInterleavedFlag: DWORD

;void
ILayoutStorage_LayoutScript_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ILayoutStorage_BeginMonitor_Proxy proto WINAPI \
		 pThis: ptr ILayoutStorage

;void
ILayoutStorage_BeginMonitor_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ILayoutStorage_EndMonitor_Proxy proto WINAPI \
		 pThis: ptr ILayoutStorage

;void
ILayoutStorage_EndMonitor_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ILayoutStorage_ReLayoutDocfile_Proxy proto WINAPI \
		 pThis: ptr ILayoutStorage,
	 pwcsNewDfName: ptr OLECHAR

;void
ILayoutStorage_ReLayoutDocfile_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ILayoutStorage_ReLayoutDocfileOnILockBytes_Proxy proto WINAPI \
		 pThis: ptr ILayoutStorage,
	   pILockBytes: ptr ILockBytes

;void
ILayoutStorage_ReLayoutDocfileOnILockBytes_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __ISurrogate_INTERFACE_DEFINED__
__ISurrogate_INTERFACE_DEFINED__ equ 1

ISurrogateVtbl		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	LoadDllServer, :REFCLSID
	STDMETHOD	FreeSurrogate
ISurrogateVtbl		ENDS
ISurrogate		STRUC
	lpVtbl		PVOID ?
ISurrogate		ENDS
LPSURROGATE		typedef ptr ISurrogate
externdef		IID_ISurrogate:IID

;HRESULT
ISurrogate_LoadDllServer_Proxy proto WINAPI \
		 pThis: ptr ISurrogate,
		 Clsid: REFCLSID

;void
ISurrogate_LoadDllServer_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ISurrogate_FreeSurrogate_Proxy proto WINAPI \
		 pThis: ptr ISurrogate

;void
ISurrogate_FreeSurrogate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IGlobalInterfaceTable_INTERFACE_DEFINED__
__IGlobalInterfaceTable_INTERFACE_DEFINED__ equ 1

IGlobalInterfaceTableVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	RegisterInterfaceInGlobal, :ptr, :REFIID, :ptr
	STDMETHOD	RevokeInterfaceFromGlobal, :DWORD
	STDMETHOD	GetInterfaceFromGlobal, :DWORD, :REFIID, :ptr
IGlobalInterfaceTableVtbl ends
IGlobalInterfaceTable struct
	lpVtbl		PVOID ?
IGlobalInterfaceTable ends
LPGLOBALINTERFACETABLE	typedef ptr IGlobalInterfaceTable
externdef		IID_IGlobalInterfaceTable:IID

;HRESULT
IGlobalInterfaceTable_RegisterInterfaceInGlobal_Proxy proto WINAPI \
		 pThis: ptr IGlobalInterfaceTable,
		  pUnk: ptr IUnknown,
		  riid: REFIID,
	     pdwCookie: LPDWORD

;void
IGlobalInterfaceTable_RegisterInterfaceInGlobal_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IGlobalInterfaceTable_RevokeInterfaceFromGlobal_Proxy proto WINAPI \
		 pThis: ptr IGlobalInterfaceTable,
	      dwCookie: DWORD

;void
IGlobalInterfaceTable_RevokeInterfaceFromGlobal_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IGlobalInterfaceTable_GetInterfaceFromGlobal_Proxy proto WINAPI \
		 pThis: ptr IGlobalInterfaceTable,
	      dwCookie: DWORD,
		  riid: REFIID,
		   ppv: PVOID

;void
IGlobalInterfaceTable_GetInterfaceFromGlobal_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IDirectWriterLock_INTERFACE_DEFINED__
__IDirectWriterLock_INTERFACE_DEFINED__ equ 1

externdef		IID_IDirectWriterLock:IID

IDirectWriterLockVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	WaitForWriteAccess, :DWORD
	STDMETHOD	ReleaseWriteAccess
	STDMETHOD	HaveWriteAccess
IDirectWriterLockVtbl ends
IDirectWriterLock struct
	lpVtbl		PVOID ?
IDirectWriterLock ends

;HRESULT
IDirectWriterLock_WaitForWriteAccess_Proxy proto WINAPI \
		 pThis: ptr IDirectWriterLock,
	     dwTimeout: DWORD

;void
IDirectWriterLock_WaitForWriteAccess_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDirectWriterLock_ReleaseWriteAccess_Proxy proto WINAPI \
		 pThis: ptr IDirectWriterLock

;void
IDirectWriterLock_ReleaseWriteAccess_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IDirectWriterLock_HaveWriteAccess_Proxy proto WINAPI \
		 pThis: ptr IDirectWriterLock

;void
IDirectWriterLock_HaveWriteAccess_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __ISynchronize_INTERFACE_DEFINED__
__ISynchronize_INTERFACE_DEFINED__ equ 1

externdef		IID_ISynchronize:IID

ISynchronizeVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	_Wait, :DWORD, :DWORD
	STDMETHOD	Signal
	STDMETHOD	Reset
ISynchronizeVtbl ends
ISynchronize struct
	lpVtbl		PVOID ?
ISynchronize ends

;HRESULT
ISynchronize_Wait_Proxy proto WINAPI \
		 pThis: ptr ISynchronize,
	dwMilliseconds: DWORD

;void
ISynchronize_Wait_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ISynchronize_Signal_Proxy proto WINAPI \
		 pThis: ptr ISynchronize

;void
ISynchronize_Signal_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ISynchronize_Reset_Proxy proto WINAPI \
		 pThis: ptr ISynchronize

;void
ISynchronize_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __ISynchronizeMutex_INTERFACE_DEFINED__
__ISynchronizeMutex_INTERFACE_DEFINED__ equ 1

externdef		IID_ISynchronizeMutex:IID

ISynchronizeMutexVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	_Wait, :DWORD, :DWORD
	STDMETHOD	Signal
	STDMETHOD	Reset
	STDMETHOD	_ReleaseMutex
ISynchronizeMutexVtbl ends
ISynchronizeMutex struct
	lpVtbl		PVOID ?
ISynchronizeMutex ends

;HRESULT
ISynchronizeMutex_ReleaseMutex_Proxy proto WINAPI \
		 pThis: ptr ISynchronizeMutex

;void
ISynchronizeMutex_ReleaseMutex_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IAsyncSetup_INTERFACE_DEFINED__
__IAsyncSetup_INTERFACE_DEFINED__ equ 1

externdef		IID_IAsyncSetup:IID

IAsyncSetupVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetAsyncManager, :REFIID, :ptr, :DWORD, :ptr, :ptr
IAsyncSetupVtbl ends
IAsyncSetup struct
	lpVtbl		PVOID ?
IAsyncSetup ends

;HRESULT
IAsyncSetup_GetAsyncManager_Proxy proto WINAPI \
		 pThis: ptr IAsyncSetup,
		  riid: REFIID,
		pOuter: ptr IUnknown,
	       dwFlags: DWORD,
	       ppInner: ptr IUnknown,
	    ppAsyncMgr: ptr IAsyncManager

;void
IAsyncSetup_GetAsyncManager_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __ICancelMethodCalls_INTERFACE_DEFINED__
__ICancelMethodCalls_INTERFACE_DEFINED__ equ 1

ICancelMethodCallsVtbl	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Cancel, :DWORD
	STDMETHOD	TestCancel
ICancelMethodCallsVtbl	ENDS
ICancelMethodCalls struct
	lpVtbl		PVOID ?
ICancelMethodCalls ends
LPCANCELMETHODCALLS	typedef ptr ICancelMethodCalls
externdef		IID_ICancelMethodCalls:IID

;HRESULT
ICancelMethodCalls_Cancel_Proxy proto WINAPI \
		 pThis: ptr ICancelMethodCalls

;void
ICancelMethodCalls_Cancel_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ICancelMethodCalls_TestCancel_Proxy proto WINAPI \
		 pThis: ptr ICancelMethodCalls

;void
ICancelMethodCalls_TestCancel_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
ICancelMethodCalls_SetCancelTimeout_Proxy proto WINAPI \
		 pThis: ptr ICancelMethodCalls,
	     ulSeconds: ULONG

;void
ICancelMethodCalls_SetCancelTimeout_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IAsyncManager_INTERFACE_DEFINED__
__IAsyncManager_INTERFACE_DEFINED__ equ 1

DCOM_NONE		equ 0
DCOM_CALL_COMPLETE	equ 0x1
DCOM_CALL_CANCELED	equ 0x2

externdef		IID_IAsyncManager:IID

IAsyncManagerVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	CompleteCall, :HRESULT
	STDMETHOD	GetCallContext, :REFIID, :ptr
	STDMETHOD	GetState, :ptr
IAsyncManagerVtbl ends
IAsyncManager struct
	lpVtbl		PVOID ?
IAsyncManager ends

;HRESULT
IAsyncManager_CompleteCall_Proxy proto WINAPI \
		 pThis: ptr IAsyncManager,
		Result: HRESULT

;void
IAsyncManager_CompleteCall_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IAsyncManager_GetCallContext_Proxy proto WINAPI \
		 pThis: ptr IAsyncManager,
		  riid: REFIID,
	    pInterface: PVOID

;void
IAsyncManager_GetCallContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IAsyncManager_GetState_Proxy proto WINAPI \
		 pThis: ptr IAsyncManager,
	 pulStateFlags: LPDWORD

;void
IAsyncManager_GetState_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IWaitMultiple_INTERFACE_DEFINED__
__IWaitMultiple_INTERFACE_DEFINED__ equ 1

externdef		IID_IWaitMultiple:IID

IWaitMultipleVtbl	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	WaitMultiple, :DWORD, :ptr
	STDMETHOD	AddSynchronize, :ptr
IWaitMultipleVtbl	ENDS
IWaitMultiple		STRUC
	lpVtbl		PVOID ?
IWaitMultiple		ENDS

;HRESULT
IWaitMultiple_WaitMultiple_Proxy proto WINAPI \
		 pThis: ptr IWaitMultiple,
	       timeout: DWORD,
		 pSync: ptr ISynchronize

;void
IWaitMultiple_WaitMultiple_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IWaitMultiple_AddSynchronize_Proxy proto WINAPI \
		 pThis: ptr IWaitMultiple,
		 pSync: ptr ISynchronize

;void
IWaitMultiple_AddSynchronize_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif

ifndef __ISynchronizeEvent_INTERFACE_DEFINED__
__ISynchronizeEvent_INTERFACE_DEFINED__ equ 1

externdef		IID_ISynchronizeEvent:IID

ISynchronizeEventVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetHandle, :ptr
	STDMETHOD	SetEventHandle, :ptr
ISynchronizeEventVtbl ends
ISynchronizeEvent struct
	lpVtbl		PVOID ?
ISynchronizeEvent ends

;HRESULT
ISynchronizeEvent_GetEvent_Proxy proto WINAPI \
		 pThis: ptr ISynchronizeEvent,
		pEvent: ptr HANDLE

;void
ISynchronizeEvent_GetEvent_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif

ifndef __IUrlMon_INTERFACE_DEFINED__
__IUrlMon_INTERFACE_DEFINED__ equ 1

externdef		IID_IUrlMon:IID

IUrlMonVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	AsyncGetClassBits, :REFCLSID, :LPWSTR, :LPWSTR, :DWORD, :DWORD, :LPWSTR, :ptr, :DWORD, :REFIID, :DWORD
IUrlMonVtbl ends
IUrlMon struct
	lpVtbl		PVOID ?
IUrlMon ends

;HRESULT
IUrlMon_AsyncGetClassBits_Proxy proto WINAPI \
		 pThis: ptr IUrlMon,
		rclsid: REFCLSID,
	       pszTYPE: LPCWSTR,
		pszExt: LPCWSTR,
       dwFileVersionMS: DWORD,
       dwFileVersionLS: DWORD,
	   pszCodeBase: LPCWSTR,
		   pbc: ptr IBindCtx,
	dwClassContext: DWORD,
		  riid: REFIID,
		 flags: DWORD

;void
IUrlMon_AsyncGetClassBits_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif

ifndef __IClassAccess_INTERFACE_DEFINED__
__IClassAccess_INTERFACE_DEFINED__ equ 1

LPPUBLISHEDAPPINFO	typedef ptr PUBLISHEDAPPINFO

PUBLISHEDINFOLIST	STRUC
cPublApps		dd ?
pPublAppInfo		LPPUBLISHEDAPPINFO ?
PUBLISHEDINFOLIST	ENDS

externdef		IID_IClassAccess:IID

IClassAccessVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetClassInfo, :REFCLSID, :QUERYCONTEXT, :ptr
	STDMETHOD	GetClassSpecInfo, :ptr, :QUERYCONTEXT, :ptr
	STDMETHOD	GetInstallablePackages, :DWORD, :ptr
IClassAccessVtbl ends
IClassAccess struct
	lpVtbl		PVOID ?
IClassAccess ends

;HRESULT
IClassAccess_GetClassInfo_Proxy proto WINAPI \
		 pThis: ptr IClassAccess,
		 clsid: REFCLSID,
	    QryContext: QUERYCONTEXT,
	  pPackageInfo: ptr PACKAGEINFO

;void
IClassAccess_GetClassInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAccess_GetClassSpecInfo_Proxy proto WINAPI \
		 pThis: ptr IClassAccess,
	    pClassSpec: ptr uCLSSPEC,
	    QryContext: QUERYCONTEXT,
	  pPackageInfo: ptr PACKAGEINFO

;void
IClassAccess_GetClassSpecInfo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAccess_GetInstallablePackages_Proxy proto WINAPI \
		 pThis: ptr IClassAccess,
		 Count: DWORD,
	     pInfoList: ptr PUBLISHEDINFOLIST

;void
IClassAccess_GetInstallablePackages_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

ifndef __IClassRefresh_INTERFACE_DEFINED__
__IClassRefresh_INTERFACE_DEFINED__ equ 1

LPPACKAGEINFO		typedef ptr PACKAGEINFO

PACKAGEINFOLIST		STRUC
cPackInfo		dd ?
pPackageInfo		LPPACKAGEINFO ?
PACKAGEINFOLIST		ENDS

externdef		IID_IClassRefresh:IID

IClassRefreshVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetUpgrades, :ULONG, :ptr, :CSPLATFORM, :LCID, :ptr
	STDMETHOD	CommitUpgrades
IClassRefreshVtbl ends
IClassRefresh struct
	lpVtbl		PVOID ?
IClassRefresh ends

;HRESULT
IClassRefresh_GetUpgrades_Proxy proto WINAPI \
		 pThis: ptr IClassRefresh,
	      cClasses: ULONG,
	    pClassList: ptr CLSID,
	      Platform: CSPLATFORM,
		Locale: LCID,
      pPackageInfoList: ptr PACKAGEINFOLIST

;void
IClassRefresh_GetUpgrades_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassRefresh_CommitUpgrades_Proxy proto WINAPI \
		 pThis: ptr IClassRefresh

;void
IClassRefresh_CommitUpgrades_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

CLASSDETAIL		STRUC
Clsid			CLSID <>
pszDesc			LPOLESTR ?
pszIconPath		LPOLESTR ?
TreatAsClsid		CLSID <>
AutoConvertClsid	CLSID <>
cFileExt		dd ?
prgFileExt		LPOLESTR ?
pMimeType		LPOLESTR ?
pDefaultProgId		LPOLESTR ?
cOtherProgId		dd ?
prgOtherProgId		LPOLESTR ?
CLASSDETAIL		ENDS

ifndef _LPCSADMNENUM_DEFINED
_LPCSADMNENUM_DEFINED equ 1

externdef		__MIDL_itf_objidl_0069_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_objidl_0069_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IEnumPackage_INTERFACE_DEFINED__
__IEnumPackage_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumPackage:IID

IEnumPackageVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :DWORD, :ptr, :ptr
	STDMETHOD	Skip, :DWORD
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumPackageVtbl ends
IEnumPackage struct
	lpVtbl		PVOID ?
IEnumPackage ends

;HRESULT
IEnumPackage_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumPackage,
		  celt: ULONG,
		 rgelt: ptr PACKAGEDETAIL,
	  pceltFetched: LPDWORD

;void
IEnumPackage_Next_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumPackage_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumPackage,
		  celt: ULONG

;void
IEnumPackage_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumPackage_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumPackage

;void
IEnumPackage_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumPackage_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumPackage,
		ppenum: ptr IEnumPackage

;void
IEnumPackage_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD
endif

ifndef __IEnumClass_INTERFACE_DEFINED__
__IEnumClass_INTERFACE_DEFINED__ equ 1

externdef		IID_IEnumClass:IID

IEnumClassVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :DWORD, :ptr, :ptr
	STDMETHOD	Skip, :DWORD
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumClassVtbl ends
IEnumClass struct
	lpVtbl		PVOID ?
IEnumClass ends

;HRESULT
IEnumClass_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumClass,
		  celt: ULONG,
		 rgelt: ptr CLASSDETAIL,
	  pceltFetched: LPDWORD

;void
IEnumClass_Next_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumClass_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumClass,
		  celt: ULONG

;void
IEnumClass_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumClass_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumClass

;void
IEnumClass_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IEnumClass_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumClass,
		ppenum: ptr IEnumClass

;void
IEnumClass_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif
endif

externdef		__MIDL_itf_objidl_0071_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_objidl_0071_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IClassAdmin_INTERFACE_DEFINED__
__IClassAdmin_INTERFACE_DEFINED__ equ 1

externdef		IID_IClassAdmin:IID

IClassAdminVtbl struct
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	NewClass, :ptr
	STDMETHOD	DeleteClass, :REFCLSID
	STDMETHOD	NewInterface, :REFIID, :LPOLESTR, :REFCLSID, :REFCLSID
	STDMETHOD	DeleteInterface,:REFIID
	STDMETHOD	NewPackage, :ptr
	STDMETHOD	DeletePackage, :LPOLESTR
	STDMETHOD	GetClassesEnum, :ptr
	STDMETHOD	GetPackagesEnum, :REFCLSID, :LPOLESTR, :CSPLATFORM, :DWORD, :LCID, :ptr
	STDMETHOD	GetClassDetails, :REFCLSID, :ptr
	STDMETHOD	GetIidDetails, :REFIID, :ptr, :ptr, :ptr
	STDMETHOD	GetPackageDetails, :LPOLESTR, :ptr
IClassAdminVtbl ends
IClassAdmin struct
	lpVtbl		PVOID ?
IClassAdmin ends

;HRESULT
IClassAdmin_NewClass_Proxy proto WINAPI \
		 pThis: ptr IClassAdmin,
	  pClassDetail: ptr CLASSDETAIL

;void
IClassAdmin_NewClass_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAdmin_DeleteClass_Proxy proto WINAPI \
		 pThis: ptr IClassAdmin,
	     guidClsId: REFCLSID

;void
IClassAdmin_DeleteClass_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAdmin_NewInterface_Proxy proto WINAPI \
		 pThis: ptr IClassAdmin,
		   iid: REFIID,
	       pszDesc: LPOLESTR,
	       psclsid: REFCLSID,
	     typelibid: REFCLSID

;void
IClassAdmin_NewInterface_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAdmin_DeleteInterface_Proxy proto WINAPI \
		 pThis: ptr IClassAdmin,
		   iid: REFIID

;void
IClassAdmin_DeleteInterface_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAdmin_NewPackage_Proxy proto WINAPI \
		 pThis: ptr IClassAdmin,
	pPackageDetail: ptr PACKAGEDETAIL

;void
IClassAdmin_NewPackage_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAdmin_DeletePackage_Proxy proto WINAPI \
		 pThis: ptr IClassAdmin,
	pszPackageName: LPOLESTR

;void
IClassAdmin_DeletePackage_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAdmin_GetClassesEnum_Proxy proto WINAPI \
		 pThis: ptr IClassAdmin,
	  ppIEnumClass: ptr IEnumClass

;void
IClassAdmin_GetClassesEnum_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAdmin_GetPackagesEnum_Proxy proto WINAPI \
		 pThis: ptr IClassAdmin,
	     guidClsid: REFCLSID,
	     pszVendor: LPOLESTR,
	      Platform: CSPLATFORM,
	     dwContext: DWORD,
		Locale: LCID,
	ppIEnumPackage: ptr IEnumPackage

;void
IClassAdmin_GetPackagesEnum_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAdmin_GetClassDetails_Proxy proto WINAPI \
		 pThis: ptr IClassAdmin,
	     guidClsId: REFCLSID,
	  pClassDetail: ptr CLASSDETAIL

;void
IClassAdmin_GetClassDetails_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAdmin_GetIidDetails_Proxy proto WINAPI \
		 pThis: ptr IClassAdmin,
		   iid: REFIID,
	      ppszDesc: ptr LPOLESTR,
	       psClsid: ptr CLSID,
	    pTypeLibId: ptr CLSID

;void
IClassAdmin_GetIidDetails_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

;HRESULT
IClassAdmin_GetPackageDetails_Proxy proto WINAPI \
		 pThis: ptr IClassAdmin,
	pszPackageName: LPOLESTR,
	pPackageDetail: ptr PACKAGEDETAIL

;void
IClassAdmin_GetPackageDetails_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD

endif

externdef		__MIDL_itf_objidl_0072_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_objidl_0072_v0_0_s_ifspec:RPC_IF_HANDLE

;DWORD
ASYNC_STGMEDIUM_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr ASYNC_STGMEDIUM
;LPSTR
ASYNC_STGMEDIUM_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr ASYNC_STGMEDIUM
;LPSTR
ASYNC_STGMEDIUM_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr ASYNC_STGMEDIUM
;void
ASYNC_STGMEDIUM_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr ASYNC_STGMEDIUM

;DWORD
BSTR_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr BSTR
;LPSTR
BSTR_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr BSTR
;LPSTR
BSTR_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr BSTR
;void
BSTR_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr BSTR

;DWORD
CLIPFORMAT_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr CLIPFORMAT
;LPSTR
CLIPFORMAT_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT
;LPSTR
CLIPFORMAT_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT
;void
CLIPFORMAT_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr CLIPFORMAT

;DWORD
FLAG_STGMEDIUM_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr FLAG_STGMEDIUM
;LPSTR
FLAG_STGMEDIUM_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr FLAG_STGMEDIUM
;LPSTR
FLAG_STGMEDIUM_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr FLAG_STGMEDIUM
;void
FLAG_STGMEDIUM_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr FLAG_STGMEDIUM

;DWORD
SNB_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr SNB
;LPSTR
SNB_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr SNB
;LPSTR
SNB_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr SNB
;void
SNB_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr SNB

;DWORD
STGMEDIUM_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr STGMEDIUM
;LPSTR
STGMEDIUM_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr STGMEDIUM
;LPSTR
STGMEDIUM_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr STGMEDIUM
;void
STGMEDIUM_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr STGMEDIUM

;HRESULT
IEnumUnknown_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumUnknown,
		  celt: ULONG,
		 rgelt: ptr IUnknown,
	  pceltFetched: LPDWORD


;HRESULT
IEnumUnknown_Next_Stub proto WINAPI \
		 pThis: ptr IEnumUnknown,
		  celt: ULONG,
		 rgelt: ptr IUnknown,
	  pceltFetched: LPDWORD

;HRESULT
IBindCtx_SetBindOptions_Proxy proto WINAPI \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS


;HRESULT
IBindCtx_SetBindOptions_Stub proto WINAPI \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS2

;HRESULT
IBindCtx_GetBindOptions_Proxy proto WINAPI \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS


;HRESULT
IBindCtx_GetBindOptions_Stub proto WINAPI \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS2

;HRESULT
IEnumMoniker_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumMoniker,
		  celt: ULONG,
		 rgelt: ptr IMoniker,
	  pceltFetched: LPDWORD


;HRESULT
IEnumMoniker_Next_Stub proto WINAPI \
		 pThis: ptr IEnumMoniker,
		  celt: ULONG,
		 rgelt: ptr IMoniker,
	  pceltFetched: LPDWORD

;BOOL
IRunnableObject_IsRunning_Proxy proto WINAPI \
		 pThis: ptr IRunnableObject


;HRESULT
IRunnableObject_IsRunning_Stub proto WINAPI \
		 pThis: ptr IRunnableObject

;HRESULT
IMoniker_BindToObject_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	    riidResult: REFIID,
	     ppvResult: PVOID


;HRESULT
IMoniker_BindToObject_Stub proto WINAPI \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	    riidResult: REFIID,
	     ppvResult: ptr IUnknown

;HRESULT
IMoniker_BindToStorage_Proxy proto WINAPI \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
		  riid: REFIID,
		ppvObj: PVOID


;HRESULT
IMoniker_BindToStorage_Stub proto WINAPI \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
		  riid: REFIID,
		ppvObj: ptr IUnknown

;HRESULT
IEnumString_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumString,
		  celt: ULONG,
		 rgelt: ptr LPOLESTR,
	  pceltFetched: LPDWORD


;HRESULT
IEnumString_Next_Stub proto WINAPI \
		 pThis: ptr IEnumString,
		  celt: ULONG,
		 rgelt: ptr LPOLESTR,
	  pceltFetched: LPDWORD

;HRESULT
ISequentialStream_Read_Proxy proto WINAPI \
		 pThis: ptr ISequentialStream,
		    pv: PVOID,
		    cb: ULONG,
	       pcbRead: LPDWORD


;HRESULT
ISequentialStream_Read_Stub proto WINAPI \
		 pThis: ptr ISequentialStream,
		    pv: LPBYTE,
		    cb: ULONG,
	       pcbRead: LPDWORD

;HRESULT
ISequentialStream_Write_Proxy proto WINAPI \
		 pThis: ptr ISequentialStream,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;HRESULT
ISequentialStream_Write_Stub proto WINAPI \
		 pThis: ptr ISequentialStream,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD

;HRESULT
IStream_Seek_Proxy proto WINAPI \
		 pThis: ptr IStream,
	      dlibMove: LARGE_INTEGER,
	      dwOrigin: DWORD,
       plibNewPosition: ptr ULARGE_INTEGER


;HRESULT
IStream_Seek_Stub proto WINAPI \
		 pThis: ptr IStream,
	      dlibMove: LARGE_INTEGER,
	      dwOrigin: DWORD,
       plibNewPosition: ptr ULARGE_INTEGER

;HRESULT
IStream_CopyTo_Proxy proto WINAPI \
		 pThis: ptr IStream,
		  pstm: ptr IStream,
		    cb: ULARGE_INTEGER,
	       pcbRead: ptr ULARGE_INTEGER,
	    pcbWritten: ptr ULARGE_INTEGER


;HRESULT
IStream_CopyTo_Stub proto WINAPI \
		 pThis: ptr IStream,
		  pstm: ptr IStream,
		    cb: ULARGE_INTEGER,
	       pcbRead: ptr ULARGE_INTEGER,
	    pcbWritten: ptr ULARGE_INTEGER

;HRESULT
IEnumSTATSTG_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATSTG,
		  celt: ULONG,
		 rgelt: ptr STATSTG,
	  pceltFetched: LPDWORD


;HRESULT
IEnumSTATSTG_Next_Stub proto WINAPI \
		 pThis: ptr IEnumSTATSTG,
		  celt: ULONG,
		 rgelt: ptr STATSTG,
	  pceltFetched: LPDWORD

;HRESULT
IStorage_OpenStream_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	     reserved1: PVOID,
	       grfMode: DWORD,
	     reserved2: DWORD,
		 ppstm: ptr IStream


;HRESULT
IStorage_OpenStream_Stub proto WINAPI \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	   cbReserved1: DWORD,
	     reserved1: LPBYTE,
	       grfMode: DWORD,
	     reserved2: DWORD,
		 ppstm: ptr IStream

;HRESULT
IStorage_EnumElements_Proxy proto WINAPI \
		 pThis: ptr IStorage,
	     reserved1: DWORD,
	     reserved2: PVOID,
	     reserved3: DWORD,
		ppenum: ptr IEnumSTATSTG


;HRESULT
IStorage_EnumElements_Stub proto WINAPI \
		 pThis: ptr IStorage,
	     reserved1: DWORD,
	   cbReserved2: DWORD,
	     reserved2: LPBYTE,
	     reserved3: DWORD,
		ppenum: ptr IEnumSTATSTG

;HRESULT
ILockBytes_ReadAt_Proxy proto WINAPI \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: PVOID,
		    cb: ULONG,
	       pcbRead: LPDWORD


;HRESULT
ILockBytes_ReadAt_Stub proto WINAPI \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	       pcbRead: LPDWORD

;HRESULT
ILockBytes_WriteAt_Proxy proto WINAPI \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;HRESULT
ILockBytes_WriteAt_Stub proto WINAPI \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD

;HRESULT
IEnumFORMATETC_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumFORMATETC,
		  celt: ULONG,
		 rgelt: ptr FORMATETC,
	  pceltFetched: LPDWORD


;HRESULT
IEnumFORMATETC_Next_Stub proto WINAPI \
		 pThis: ptr IEnumFORMATETC,
		  celt: ULONG,
		 rgelt: ptr FORMATETC,
	  pceltFetched: LPDWORD

;HRESULT
IEnumSTATDATA_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATDATA,
		  celt: ULONG,
		 rgelt: ptr STATDATA,
	  pceltFetched: LPDWORD


;HRESULT
IEnumSTATDATA_Next_Stub proto WINAPI \
		 pThis: ptr IEnumSTATDATA,
		  celt: ULONG,
		 rgelt: ptr STATDATA,
	  pceltFetched: LPDWORD

;void
IAdviseSink_OnDataChange_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink,
	    pFormatetc: ptr FORMATETC,
	       pStgmed: ptr STGMEDIUM


;HRESULT
IAdviseSink_OnDataChange_Stub proto WINAPI \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
	    pFormatetc: ptr FORMATETC,
	       pStgmed: ptr ASYNC_STGMEDIUM

;void
IAdviseSink_OnViewChange_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink,
	      dwAspect: DWORD,
		lindex: LONG


;HRESULT
IAdviseSink_OnViewChange_Stub proto WINAPI \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
	      dwAspect: DWORD,
		lindex: LONG

;void
IAdviseSink_OnRename_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink,
		   pmk: ptr IMoniker


;HRESULT
IAdviseSink_OnRename_Stub proto WINAPI \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
		   pmk: ptr IMoniker

;void
IAdviseSink_OnSave_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink


;HRESULT
IAdviseSink_OnSave_Stub proto WINAPI \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager

;void
IAdviseSink_OnClose_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink


;HRESULT
IAdviseSink_OnClose_Stub proto WINAPI \
		 pThis: ptr IAdviseSink

;void
IAdviseSink2_OnLinkSrcChange_Proxy proto WINAPI \
		 pThis: ptr IAdviseSink2,
		   pmk: ptr IMoniker


;HRESULT
IAdviseSink2_OnLinkSrcChange_Stub proto WINAPI \
		 pThis: ptr IAdviseSink2,
		 ppIAM: ptr IAsyncManager,
		   pmk: ptr IMoniker

;HRESULT
IDataObject_GetData_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	  pformatetcIn: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM


;HRESULT
IDataObject_GetData_Stub proto WINAPI \
		 pThis: ptr IDataObject,
	  pformatetcIn: ptr FORMATETC,
	 pRemoteMedium: ptr STGMEDIUM

;HRESULT
IDataObject_GetDataHere_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM


;HRESULT
IDataObject_GetDataHere_Stub proto WINAPI \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	 pRemoteMedium: ptr STGMEDIUM

;HRESULT
IDataObject_SetData_Proxy proto WINAPI \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM,
	      fRelease: BOOL


;HRESULT
IDataObject_SetData_Stub proto WINAPI \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr FLAG_STGMEDIUM,
	      fRelease: BOOL

;HRESULT
IEnumSTATPROPSTG_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATPROPSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSTG,
	  pceltFetched: LPDWORD


;HRESULT
IEnumSTATPROPSTG_Next_Stub proto WINAPI \
		 pThis: ptr IEnumSTATPROPSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSTG,
	  pceltFetched: LPDWORD

;HRESULT
IEnumSTATPROPSETSTG_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumSTATPROPSETSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSETSTG,
	  pceltFetched: LPDWORD


;HRESULT
IEnumSTATPROPSETSTG_Next_Stub proto WINAPI \
		 pThis: ptr IEnumSTATPROPSETSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSETSTG,
	  pceltFetched: LPDWORD

;HRESULT
IFillLockBytes_FillAppend_Proxy proto WINAPI \
		 pThis: ptr IFillLockBytes,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;HRESULT
IFillLockBytes_FillAppend_Stub proto WINAPI \
		 pThis: ptr IFillLockBytes,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD

;HRESULT
IFillLockBytes_FillAt_Proxy proto WINAPI \
		 pThis: ptr IFillLockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;HRESULT
IFillLockBytes_FillAt_Stub proto WINAPI \
		 pThis: ptr IFillLockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD

.list
endif ; __objidl_h__
