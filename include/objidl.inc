.xlist
ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 440
endif

include rpc.inc
include rpcndr.inc
.xlist
ifndef __RPCNDR_H_VERSION__
.err < this stub requires an updated version of rpcndr.inc >
endif

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
.xlist
endif

ifndef __objidl_h__
__objidl_h__ equ 1


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


      QueryInterface@CT typedef proto \
		 pThis: PVOID,
		  riid: REFIID,
	     ppvObject: PVOID
      QueryInterface@MP typedef ptr QueryInterface@CT

	      AddRef@CT typedef proto \
		 pThis: PVOID
	      AddRef@MP typedef ptr AddRef@CT

	     Release@CT typedef proto \
		 pThis: PVOID
	     Release@MP typedef ptr Release@CT

BEGIN_INTERFACE		equ <>
END_INTERFACE		equ <>

ifndef __IMarshal_INTERFACE_DEFINED__
__IMarshal_INTERFACE_DEFINED__ equ 1



LPMARSHAL		typedef ptr IMarshal
externdef		IID_IMarshal:IID


IMarshalVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
      GetUnmarshalClass PVOID ?
      GetMarshalSizeMax PVOID ?
       MarshalInterface PVOID ?
     UnmarshalInterface PVOID ?
     ReleaseMarshalData PVOID ?
       DisconnectObject PVOID ?

	END_INTERFACE

IMarshalVtbl		ENDS

LPIMarshalVtbl		typedef ptr IMarshalVtbl
IMarshal		STRUC
lpVtbl			LPIMarshalVtbl ?
IMarshal		ENDS


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

LPMALLOC		typedef ptr IMalloc
externdef		IID_IMalloc:IID

IMallocVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		  Alloc PVOID ?
		Realloc PVOID ?
		   Free PVOID ?
		GetSize PVOID ?
	       DidAlloc PVOID ?
	   HeapMinimize PVOID ?

	END_INTERFACE

IMallocVtbl		ENDS

LPIMallocVtbl		typedef ptr IMallocVtbl
IMalloc			STRUC
lpVtbl			LPIMallocVtbl ?
IMalloc			ENDS


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



LPMALLOCSPY		typedef ptr IMallocSpy


externdef		IID_IMallocSpy:IID


IMallocSpyVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	       PreAlloc PVOID ?
	      PostAlloc PVOID ?
		PreFree PVOID ?
	       PostFree PVOID ?
	     PreRealloc PVOID ?
	    PostRealloc PVOID ?
	     PreGetSize PVOID ?
	    PostGetSize PVOID ?
	    PreDidAlloc PVOID ?
	   PostDidAlloc PVOID ?
	PreHeapMinimize PVOID ?
       PostHeapMinimize PVOID ?

	END_INTERFACE

IMallocSpyVtbl		ENDS

LPIMallocSpyVtbl	typedef ptr IMallocSpyVtbl
IMallocSpy		STRUC
lpVtbl			LPIMallocSpyVtbl ?
IMallocSpy		ENDS

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



LPSTDMARSHALINFO	typedef ptr IStdMarshalInfo


externdef		IID_IStdMarshalInfo:IID

IStdMarshalInfoVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

     GetClassForHandler PVOID ?

	END_INTERFACE

IStdMarshalInfoVtbl	ENDS

LPIStdMarshalInfoVtbl	typedef ptr IStdMarshalInfoVtbl
IStdMarshalInfo		STRUC
lpVtbl			LPIStdMarshalInfoVtbl ?
IStdMarshalInfo		ENDS



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



LPEXTERNALCONNECTION	typedef ptr IExternalConnection

tagEXTCONN		typedef SDWORD
EXTCONN_STRONG		equ 0x1
EXTCONN_WEAK		equ 0x2
EXTCONN_CALLABLE	equ 0x4

externdef		IID_IExternalConnection:IID

IExternalConnectionVtbl STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	  AddConnection PVOID ?
      ReleaseConnection PVOID ?

	END_INTERFACE

IExternalConnectionVtbl ENDS

LPIExternalConnectionVtbl typedef ptr IExternalConnectionVtbl
IExternalConnection	STRUC
lpVtbl			LPIExternalConnectionVtbl ?
IExternalConnection	ENDS

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



LPMULTIQI		typedef ptr IMultiQI

MULTI_QI		STRUC
pIID			LPIID ?
pItf			LPIUnknown ?
hr			HRESULT ?
MULTI_QI		ENDS


externdef		IID_IMultiQI:IID

IMultiQIVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

QueryMultipleInterfaces PVOID ?

	END_INTERFACE

IMultiQIVtbl		ENDS

LPIMultiQIVtbl		typedef ptr IMultiQIVtbl
IMultiQI		STRUC
lpVtbl			LPIMultiQIVtbl ?
IMultiQI		ENDS


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

	       Reset@CT typedef proto \
		 pThis: PVOID
	       Reset@MP typedef ptr Reset@CT

		Next@CT typedef proto \
		 pThis: PVOID,
		  celt: ULONG,
		 rgelt: PVOID,
	  pceltFetched: LPDWORD
		Next@MP typedef ptr Next@CT

		Skip@CT typedef proto \
		 pThis: PVOID,
		  celt: ULONG
		Skip@MP typedef ptr Skip@CT

	       Clone@CT typedef proto \
		 pThis: PVOID,
		ppenum: PVOID
	       Clone@MP typedef ptr Clone@CT

ifndef __IEnumUnknown_INTERFACE_DEFINED__
__IEnumUnknown_INTERFACE_DEFINED__ equ 1



LPENUMUNKNOWN		typedef ptr IEnumUnknown


externdef		IID_IEnumUnknown:IID

IEnumUnknownVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
		   Next Next@MP ?
		   Skip Skip@MP ?
		  Reset Reset@MP ?
		  Clone Clone@MP ?

	END_INTERFACE

IEnumUnknownVtbl	ENDS

LPIEnumUnknownVtbl	typedef ptr IEnumUnknownVtbl
IEnumUnknown		STRUC
lpVtbl			LPIEnumUnknownVtbl ?
IEnumUnknown		ENDS



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



LPBC			typedef ptr IBindCtx

LPBINDCTX		typedef ptr IBindCtx

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


externdef		IID_IBindCtx:IID

IBindCtxVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

    RegisterObjectBound PVOID ?
      RevokeObjectBound PVOID ?
    ReleaseBoundObjects PVOID ?
	 SetBindOptions PVOID ?
	 GetBindOptions PVOID ?
  GetRunningObjectTable PVOID ?
    RegisterObjectParam PVOID ?
	 GetObjectParam PVOID ?
	EnumObjectParam PVOID ?
      RevokeObjectParam PVOID ?

	END_INTERFACE

IBindCtxVtbl		ENDS

LPIBindCtxVtbl		typedef ptr IBindCtxVtbl
IBindCtx		STRUC
lpVtbl			LPIBindCtxVtbl ?
IBindCtx		ENDS



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



LPENUMMONIKER		typedef ptr IEnumMoniker


externdef		IID_IEnumMoniker:IID

IEnumMonikerVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
		   Next Next@MP ?
		   Skip Skip@MP ?
		  Reset Reset@MP ?
		  Clone Clone@MP ?

	END_INTERFACE

IEnumMonikerVtbl	ENDS

LPIEnumMonikerVtbl	typedef ptr IEnumMonikerVtbl
IEnumMoniker		STRUC
lpVtbl			LPIEnumMonikerVtbl ?
IEnumMoniker		ENDS



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



LPRUNNABLEOBJECT	typedef ptr IRunnableObject


externdef		IID_IRunnableObject:IID


IRunnableObjectVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	GetRunningClass PVOID ?
		    Run PVOID ?
	      IsRunning PVOID ?
	    LockRunning PVOID ?
     SetContainedObject PVOID ?

	END_INTERFACE

IRunnableObjectVtbl	ENDS

LPIRunnableObjectVtbl	typedef ptr IRunnableObjectVtbl
IRunnableObject		STRUC
lpVtbl			LPIRunnableObjectVtbl ?
IRunnableObject		ENDS
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



LPRUNNINGOBJECTTABLE	typedef ptr IRunningObjectTable


externdef		IID_IRunningObjectTable:IID

IRunningObjectTableVtbl STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	       Register PVOID ?
		 Revoke PVOID ?
	      IsRunning PVOID ?
	      GetObject PVOID ?
	 NoteChangeTime PVOID ?
    GetTimeOfLastChange PVOID ?
	    EnumRunning PVOID ?

	END_INTERFACE

IRunningObjectTableVtbl ENDS

LPIRunningObjectTableVtbl typedef ptr IRunningObjectTableVtbl
IRunningObjectTable	STRUC
lpVtbl			LPIRunningObjectTableVtbl ?
IRunningObjectTable	ENDS
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

	  GetClassID@CT typedef proto \
		 pThis: PVOID,
	      pClassID: ptr CLSID
	  GetClassID@MP typedef ptr GetClassID@CT


ifndef __IPersist_INTERFACE_DEFINED__
__IPersist_INTERFACE_DEFINED__ equ 1



LPPERSIST		typedef ptr IPersist


externdef		IID_IPersist:IID

IPersistVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
	     GetClassID GetClassID@MP ?

	END_INTERFACE

IPersistVtbl		ENDS

LPIPersistVtbl		typedef ptr IPersistVtbl
IPersist		STRUC
lpVtbl			LPIPersistVtbl ?
IPersist		ENDS



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

	     IsDirty@CT typedef proto pThis:PVOID
	     IsDirty@MP typedef ptr IsDirty@CT
		Load@CT typedef proto \
		 pThis: PVOID,
		  pStm: ptr IStream
		Load@MP typedef ptr Load@CT

ifndef __IPersistStream_INTERFACE_DEFINED__
__IPersistStream_INTERFACE_DEFINED__ equ 1



LPPERSISTSTREAM		typedef ptr IPersistStream


externdef		IID_IPersistStream:IID


IPersistStreamVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
	     GetClassID GetClassID@MP ?
		IsDirty IsDirty@MP ?
		   Load Load@MP ?

		   Save PVOID ?
	     GetSizeMax PVOID ?

	END_INTERFACE

IPersistStreamVtbl	ENDS

LPIPersistStreamVtbl	typedef ptr IPersistStreamVtbl
IPersistStream		STRUC
lpVtbl			LPIPersistStreamVtbl ?
IPersistStream		ENDS


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

LPMONIKER		typedef ptr IMoniker

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

externdef		IID_IMoniker:IID


IMonikerVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
	     GetClassID GetClassID@MP ?
		IsDirty IsDirty@MP ?
		   Load Load@MP ?

		   Save PVOID ?
	     GetSizeMax PVOID ?
	   BindToObject PVOID ?
	  BindToStorage PVOID ?
		 Reduce PVOID ?
	    ComposeWith PVOID ?
		   Enum PVOID ?
		IsEqual PVOID ?
		   Hash PVOID ?
	      IsRunning PVOID ?
    GetTimeOfLastChange PVOID ?
		Inverse PVOID ?
       CommonPrefixWith PVOID ?
	 RelativePathTo PVOID ?
	 GetDisplayName PVOID ?
       ParseDisplayName PVOID ?
	IsSystemMoniker PVOID ?

	END_INTERFACE

IMonikerVtbl		ENDS

LPIMonikerVtbl		typedef ptr IMonikerVtbl
IMoniker		STRUC
lpVtbl			LPIMonikerVtbl ?
IMoniker		ENDS


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


IROTDataVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

      GetComparisonData PVOID ?

	END_INTERFACE

IROTDataVtbl		ENDS

LPIROTDataVtbl		typedef ptr IROTDataVtbl
IROTData		STRUC
lpVtbl			LPIROTDataVtbl ?
IROTData		ENDS


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

LPENUMSTRING		typedef ptr IEnumString


externdef		IID_IEnumString:IID

IEnumStringVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
		   Next Next@MP ?
		   Skip Skip@MP ?
		  Reset Reset@MP ?
		  Clone Clone@MP ?

	END_INTERFACE

IEnumStringVtbl		ENDS

LPIEnumStringVtbl	typedef ptr IEnumStringVtbl
IEnumString		STRUC
lpVtbl			LPIEnumStringVtbl ?
IEnumString		ENDS



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


ISequentialStreamVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		   Read PVOID ?
		  Write PVOID ?

	END_INTERFACE

ISequentialStreamVtbl	ENDS

LPISequentialStreamVtbl typedef ptr ISequentialStreamVtbl
ISequentialStream	STRUC
lpVtbl			LPISequentialStreamVtbl ?
ISequentialStream	ENDS


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

LPSTREAM		typedef ptr IStream

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


externdef		IID_IStream:IID

IStreamVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		   Read PVOID ?
		  Write PVOID ?
		   Seek PVOID ?
		SetSize PVOID ?
		 CopyTo PVOID ?
		 Commit PVOID ?
		 Revert PVOID ?
	     LockRegion PVOID ?
	   UnlockRegion PVOID ?
		   Stat PVOID ?
		  Clone PVOID ?

	END_INTERFACE

IStreamVtbl		ENDS

LPIStreamVtbl		typedef ptr IStreamVtbl
IStream			STRUC
lpVtbl			LPIStreamVtbl ?
IStream			ENDS


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



LPENUMSTATSTG		typedef ptr IEnumSTATSTG


externdef		IID_IEnumSTATSTG:IID


IEnumSTATSTGVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
		   Next Next@MP ?
		   Skip Skip@MP ?
		  Reset Reset@MP ?
		  Clone Clone@MP ?

	END_INTERFACE

IEnumSTATSTGVtbl	ENDS

LPIEnumSTATSTGVtbl	typedef ptr IEnumSTATSTGVtbl
IEnumSTATSTG		STRUC
lpVtbl			LPIEnumSTATSTGVtbl ?
IEnumSTATSTG		ENDS


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



LPSTORAGE		typedef ptr IStorage

RemSNB			STRUC
ulCntStr		dd ?
ulCntChar		dd ?
rgString		OLECHAR ?
RemSNB			ENDS

wireSNB			typedef ptr RemSNB
SNB			typedef ptr OLECHAR


externdef		IID_IStorage:IID

IStorageVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	   CreateStream PVOID ?
	     OpenStream PVOID ?
	  CreateStorage PVOID ?
	    OpenStorage PVOID ?
		 CopyTo PVOID ?
	  MoveElementTo PVOID ?
		 Commit PVOID ?
		 Revert PVOID ?
	   EnumElements PVOID ?
	 DestroyElement PVOID ?
	  RenameElement PVOID ?
	SetElementTimes PVOID ?
	       SetClass PVOID ?
	   SetStateBits PVOID ?
		   Stat PVOID ?

	END_INTERFACE

IStorageVtbl		ENDS

LPIStorageVtbl		typedef ptr IStorageVtbl
IStorage		STRUC
lpVtbl			LPIStorageVtbl ?
IStorage		ENDS



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



LPPERSISTFILE		typedef ptr IPersistFile


externdef		IID_IPersistFile:IID


IPersistFileVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
	     GetClassID GetClassID@MP ?
		IsDirty IsDirty@MP ?

		   Load PVOID ?
		   Save PVOID ?
	  SaveCompleted PVOID ?
	     GetCurFile PVOID ?

	END_INTERFACE

IPersistFileVtbl	ENDS

LPIPersistFileVtbl	typedef ptr IPersistFileVtbl
IPersistFile		STRUC
lpVtbl			LPIPersistFileVtbl ?
IPersistFile		ENDS



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



LPPERSISTSTORAGE	typedef ptr IPersistStorage


externdef		IID_IPersistStorage:IID


IPersistStorageVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
	     GetClassID GetClassID@MP ?
		IsDirty IsDirty@MP ?

		InitNew PVOID ?
		   Load PVOID ?
		   Save PVOID ?
	  SaveCompleted PVOID ?
	HandsOffStorage PVOID ?

	END_INTERFACE

IPersistStorageVtbl	ENDS

LPIPersistStorageVtbl	typedef ptr IPersistStorageVtbl
IPersistStorage		STRUC
lpVtbl			LPIPersistStorageVtbl ?
IPersistStorage		ENDS



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



LPLOCKBYTES		typedef ptr ILockBytes


externdef		IID_ILockBytes:IID

ILockBytesVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		 ReadAt PVOID ?
		WriteAt PVOID ?
		  Flush PVOID ?
		SetSize PVOID ?
	     LockRegion PVOID ?
	   UnlockRegion PVOID ?
		   Stat PVOID ?

	END_INTERFACE

ILockBytesVtbl		ENDS

LPILockBytesVtbl	typedef ptr ILockBytesVtbl
ILockBytes		STRUC
lpVtbl			LPILockBytesVtbl ?
ILockBytes		ENDS


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



LPENUMFORMATETC		typedef ptr IEnumFORMATETC

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

externdef		IID_IEnumFORMATETC:IID


IEnumFORMATETCVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
		   Next Next@MP ?
		   Skip Skip@MP ?
		  Reset Reset@MP ?
		  Clone Clone@MP ?

	END_INTERFACE

IEnumFORMATETCVtbl	ENDS

LPIEnumFORMATETCVtbl	typedef ptr IEnumFORMATETCVtbl
IEnumFORMATETC		STRUC
lpVtbl			LPIEnumFORMATETCVtbl ?
IEnumFORMATETC		ENDS

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



LPENUMSTATDATA		typedef ptr IEnumSTATDATA
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


externdef		IID_IEnumSTATDATA:IID


IEnumSTATDATAVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
		   Next Next@MP ?
		   Skip Skip@MP ?
		  Reset Reset@MP ?
		  Clone Clone@MP ?

	END_INTERFACE

IEnumSTATDATAVtbl	ENDS

LPIEnumSTATDATAVtbl	typedef ptr IEnumSTATDATAVtbl
IEnumSTATDATA		STRUC
lpVtbl			LPIEnumSTATDATAVtbl ?
IEnumSTATDATA		ENDS



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



LPROOTSTORAGE		typedef ptr IRootStorage


externdef		IID_IRootStorage:IID


IRootStorageVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	   SwitchToFile PVOID ?

	END_INTERFACE

IRootStorageVtbl	ENDS

LPIRootStorageVtbl	typedef ptr IRootStorageVtbl
IRootStorage		STRUC
lpVtbl			LPIRootStorageVtbl ?
IRootStorage		ENDS



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



LPADVISESINK		typedef ptr IAdviseSink

TYMED			typedef SDWORD
TYMED_HGLOBAL		equ 1
TYMED_FILE		equ 2
TYMED_ISTREAM		equ 4
TYMED_ISTORAGE		equ 8
TYMED_GDI		equ 16
TYMED_MFPICT		equ 32
TYMED_ENHMF		equ 64
TYMED_NULL		equ 0

ifndef RC_INVOKED
;pragma warning(disable:4200)
endif
RemSTGMEDIUM		STRUC
tymed			dd ?
dwHandleType		dd ?
pData			dd ?
pUnkForRelease		dd ?
cbData			dd ?
data_			db ?
RemSTGMEDIUM		ENDS

ifndef RC_INVOKED
;pragma warning(default:4200)
endif
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


externdef		IID_IAdviseSink:IID

IAdviseSinkVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	   OnDataChange PVOID ?
	   OnViewChange PVOID ?
	       OnRename PVOID ?
		 OnSave PVOID ?
		OnClose PVOID ?

	END_INTERFACE

IAdviseSinkVtbl		ENDS

LPIAdviseSinkVtbl	typedef ptr IAdviseSinkVtbl
IAdviseSink		STRUC
lpVtbl			LPIAdviseSinkVtbl ?
IAdviseSink		ENDS


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



LPADVISESINK2		typedef ptr IAdviseSink2


externdef		IID_IAdviseSink2:IID

IAdviseSink2Vtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	   OnDataChange PVOID ?
	   OnViewChange PVOID ?
	       OnRename PVOID ?
		 OnSave PVOID ?
		OnClose PVOID ?
	OnLinkSrcChange PVOID ?

	END_INTERFACE

IAdviseSink2Vtbl	ENDS

LPIAdviseSink2Vtbl	typedef ptr IAdviseSink2Vtbl
IAdviseSink2		STRUC
lpVtbl			LPIAdviseSink2Vtbl ?
IAdviseSink2		ENDS



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

LPDATAOBJECT		typedef ptr IDataObject

DATADIR			typedef SDWORD
DATADIR_GET		equ 1
DATADIR_SET		equ 2


externdef		IID_IDataObject:IID

IDataObjectVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		GetData PVOID ?
	    GetDataHere PVOID ?
	   QueryGetData PVOID ?
  GetCanonicalFormatEtc PVOID ?
		SetData PVOID ?
	  EnumFormatEtc PVOID ?
		DAdvise PVOID ?
	      DUnadvise PVOID ?
	    EnumDAdvise PVOID ?

	END_INTERFACE

IDataObjectVtbl		ENDS

LPIDataObjectVtbl	typedef ptr IDataObjectVtbl
IDataObject		STRUC
lpVtbl			LPIDataObjectVtbl ?
IDataObject		ENDS




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

LPDATAADVISEHOLDER	typedef ptr IDataAdviseHolder


externdef		IID_IDataAdviseHolder:IID

IDataAdviseHolderVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		 Advise PVOID ?
	       Unadvise PVOID ?
	     EnumAdvise PVOID ?
       SendOnDataChange PVOID ?

	END_INTERFACE

IDataAdviseHolderVtbl	ENDS

LPIDataAdviseHolderVtbl typedef ptr IDataAdviseHolderVtbl
IDataAdviseHolder	STRUC
lpVtbl			LPIDataAdviseHolderVtbl ?
IDataAdviseHolder	ENDS


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



LPMESSAGEFILTER		typedef ptr IMessageFilter

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

externdef		IID_IMessageFilter:IID

IMessageFilterVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

     HandleInComingCall PVOID ?
      RetryRejectedCall PVOID ?
	 MessagePending PVOID ?

	END_INTERFACE

IMessageFilterVtbl	ENDS

LPIMessageFilterVtbl	typedef ptr IMessageFilterVtbl
IMessageFilter		STRUC
lpVtbl			LPIMessageFilterVtbl ?
IMessageFilter		ENDS


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

IRpcChannelBufferVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	      GetBuffer PVOID ?
	    SendReceive PVOID ?
	     FreeBuffer PVOID ?
	     GetDestCtx PVOID ?
	    IsConnected PVOID ?

	END_INTERFACE

IRpcChannelBufferVtbl	ENDS

LPIRpcChannelBufferVtbl typedef ptr IRpcChannelBufferVtbl
IRpcChannelBuffer	STRUC
lpVtbl			LPIRpcChannelBufferVtbl ?
IRpcChannelBuffer	ENDS


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

IRpcChannelBuffer2Vtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	      GetBuffer PVOID ?
	    SendReceive PVOID ?
	     FreeBuffer PVOID ?
	     GetDestCtx PVOID ?
	    IsConnected PVOID ?
     GetProtocolVersion PVOID ?

	END_INTERFACE

IRpcChannelBuffer2Vtbl	ENDS

LPIRpcChannelBuffer2Vtbl typedef ptr IRpcChannelBuffer2Vtbl
IRpcChannelBuffer2	STRUC
lpVtbl			LPIRpcChannelBuffer2Vtbl ?
IRpcChannelBuffer2	ENDS

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

IRpcChannelBuffer3Vtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	      GetBuffer PVOID ?
	    SendReceive PVOID ?
	     FreeBuffer PVOID ?
	     GetDestCtx PVOID ?
	    IsConnected PVOID ?
     GetProtocolVersion PVOID ?
		   Send PVOID ?
		Receive PVOID ?
		 Cancel PVOID ?
	 GetCallContext PVOID ?
	   GetDestCtxEx PVOID ?
	       GetState PVOID ?
	  RegisterAsync PVOID ?

	END_INTERFACE

IRpcChannelBuffer3Vtbl	ENDS

LPIRpcChannelBuffer3Vtbl typedef ptr IRpcChannelBuffer3Vtbl
IRpcChannelBuffer3	STRUC
lpVtbl			LPIRpcChannelBuffer3Vtbl ?
IRpcChannelBuffer3	ENDS



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

IRpcProxyBufferVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		Connect PVOID ?
	     Disconnect PVOID ?

	END_INTERFACE

IRpcProxyBufferVtbl	ENDS

LPIRpcProxyBufferVtbl	typedef ptr IRpcProxyBufferVtbl
IRpcProxyBuffer		STRUC
lpVtbl			LPIRpcProxyBufferVtbl ?
IRpcProxyBuffer		ENDS


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

IRpcStubBufferVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		Connect PVOID ?
	     Disconnect PVOID ?
		_Invoke PVOID ?
	 IsIIDSupported PVOID ?
	      CountRefs PVOID ?

DebugServerQueryInterface@CT typedef proto \
		 pThis: ptr IRpcStubBuffer,
		   ppv: PVOID
DebugServerQueryInterface@MP typedef ptr DebugServerQueryInterface@CT
DebugServerQueryInterface DebugServerQueryInterface@MP ?

  DebugServerRelease@CT typedef proto \
		 pThis: ptr IRpcStubBuffer,
		    pv: PVOID
  DebugServerRelease@MP typedef ptr DebugServerRelease@CT
     DebugServerRelease DebugServerRelease@MP ?

	END_INTERFACE

IRpcStubBufferVtbl	ENDS

LPIRpcStubBufferVtbl	typedef ptr IRpcStubBufferVtbl
IRpcStubBuffer		STRUC
lpVtbl			LPIRpcStubBufferVtbl ?
IRpcStubBuffer		ENDS

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

IPSFactoryBufferVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	    CreateProxy PVOID ?
	     CreateStub PVOID ?

	END_INTERFACE

IPSFactoryBufferVtbl	ENDS

LPIPSFactoryBufferVtbl	typedef ptr IPSFactoryBufferVtbl
IPSFactoryBuffer	STRUC
lpVtbl			LPIPSFactoryBufferVtbl ?
IPSFactoryBuffer	ENDS

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

IChannelHookVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	  ClientGetSize PVOID ?
       ClientFillBuffer PVOID ?
	   ClientNotify PVOID ?
	   ServerNotify PVOID ?
	  ServerGetSize PVOID ?
       ServerFillBuffer PVOID ?

	END_INTERFACE

IChannelHookVtbl	ENDS

LPIChannelHookVtbl	typedef ptr IChannelHookVtbl
IChannelHook		STRUC
lpVtbl			LPIChannelHookVtbl ?
IChannelHook		ENDS

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

LPPROPERTYSTORAGE	typedef ptr IPropertyStorage

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
PIDSI_APPNAME		equ 0x00000012L
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


externdef		IID_IPropertyStorage:IID

IPropertyStorageVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	   ReadMultiple PVOID ?
	  WriteMultiple PVOID ?
	 DeleteMultiple PVOID ?
      ReadPropertyNames PVOID ?
     WritePropertyNames PVOID ?
    DeletePropertyNames PVOID ?
		 Commit PVOID ?
		 Revert PVOID ?
		   Enum PVOID ?
	       SetTimes PVOID ?
	       SetClass PVOID ?
		   Stat PVOID ?

	END_INTERFACE

IPropertyStorageVtbl	ENDS

LPIPropertyStorageVtbl	typedef ptr IPropertyStorageVtbl
IPropertyStorage	STRUC
lpVtbl			LPIPropertyStorageVtbl ?
IPropertyStorage	ENDS
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

LPPROPERTYSETSTORAGE	typedef ptr IPropertySetStorage


externdef		IID_IPropertySetStorage:IID

IPropertySetStorageVtbl STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		 Create PVOID ?
		   Open PVOID ?
		 Delete PVOID ?
		   Enum PVOID ?

	END_INTERFACE

IPropertySetStorageVtbl ENDS

LPIPropertySetStorageVtbl typedef ptr IPropertySetStorageVtbl
IPropertySetStorage	STRUC
lpVtbl			LPIPropertySetStorageVtbl ?
IPropertySetStorage	ENDS


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



LPENUMSTATPROPSTG	typedef ptr IEnumSTATPROPSTG


externdef		IID_IEnumSTATPROPSTG:IID

IEnumSTATPROPSTGVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
		   Next Next@MP ?
		   Skip Skip@MP ?
		  Reset Reset@MP ?
		  Clone Clone@MP ?

	END_INTERFACE

IEnumSTATPROPSTGVtbl	ENDS

LPIEnumSTATPROPSTGVtbl	typedef ptr IEnumSTATPROPSTGVtbl
IEnumSTATPROPSTG	STRUC
lpVtbl			LPIEnumSTATPROPSTGVtbl ?
IEnumSTATPROPSTG	ENDS


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



LPENUMSTATPROPSETSTG	typedef ptr IEnumSTATPROPSETSTG


externdef		IID_IEnumSTATPROPSETSTG:IID

IEnumSTATPROPSETSTGVtbl STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
		   Next Next@MP ?
		   Skip Skip@MP ?
		  Reset Reset@MP ?
		  Clone Clone@MP ?

	END_INTERFACE

IEnumSTATPROPSETSTGVtbl ENDS

LPIEnumSTATPROPSETSTGVtbl typedef ptr IEnumSTATPROPSETSTGVtbl
IEnumSTATPROPSETSTG	STRUC
lpVtbl			LPIEnumSTATPROPSETSTGVtbl ?
IEnumSTATPROPSETSTG	ENDS

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

IClientSecurityVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	   QueryBlanket PVOID ?
	     SetBlanket PVOID ?
	      CopyProxy PVOID ?

	END_INTERFACE

IClientSecurityVtbl	ENDS

LPIClientSecurityVtbl	typedef ptr IClientSecurityVtbl
IClientSecurity		STRUC
lpVtbl			LPIClientSecurityVtbl ?
IClientSecurity		ENDS


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

IServerSecurityVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	   QueryBlanket PVOID ?
      ImpersonateClient PVOID ?
	   RevertToSelf PVOID ?
	IsImpersonating PVOID ?

	END_INTERFACE

IServerSecurityVtbl	ENDS

LPIServerSecurityVtbl	typedef ptr IServerSecurityVtbl
IServerSecurity		STRUC
lpVtbl			LPIServerSecurityVtbl ?
IServerSecurity		ENDS


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

IClassActivatorVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	 GetClassObject PVOID ?

	END_INTERFACE

IClassActivatorVtbl	ENDS

LPIClassActivatorVtbl	typedef ptr IClassActivatorVtbl
IClassActivator		STRUC
lpVtbl			LPIClassActivatorVtbl ?
IClassActivator		ENDS



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

IRpcOptionsVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		    Set PVOID ?
		  Query PVOID ?
	      CopyProxy PVOID ?

	END_INTERFACE

IRpcOptionsVtbl		ENDS

LPIRpcOptionsVtbl	typedef ptr IRpcOptionsVtbl
IRpcOptions		STRUC
lpVtbl			LPIRpcOptionsVtbl ?
IRpcOptions		ENDS


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

IComBindingVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	    InitBinding PVOID ?
	   QueryBinding PVOID ?

	END_INTERFACE

IComBindingVtbl		ENDS

LPIComBindingVtbl	typedef ptr IComBindingVtbl
IComBinding		STRUC
lpVtbl			LPIComBindingVtbl ?
IComBinding		ENDS



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

IFillLockBytesVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	     FillAppend PVOID ?
		 FillAt PVOID ?
	    SetFillSize PVOID ?
	      Terminate PVOID ?

	END_INTERFACE

IFillLockBytesVtbl	ENDS

LPIFillLockBytesVtbl	typedef ptr IFillLockBytesVtbl
IFillLockBytes		STRUC
lpVtbl			LPIFillLockBytesVtbl ?
IFillLockBytes		ENDS

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

IProgressNotifyVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	     OnProgress PVOID ?

	END_INTERFACE

IProgressNotifyVtbl	ENDS

LPIProgressNotifyVtbl	typedef ptr IProgressNotifyVtbl
IProgressNotify		STRUC
lpVtbl			LPIProgressNotifyVtbl ?
IProgressNotify		ENDS



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

ILayoutStorageVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	   LayoutScript PVOID ?
	   BeginMonitor PVOID ?
	     EndMonitor PVOID ?
	ReLayoutDocfile PVOID ?
ReLayoutDocfileOnILockBytes PVOID ?

	END_INTERFACE

ILayoutStorageVtbl	ENDS

LPILayoutStorageVtbl	typedef ptr ILayoutStorageVtbl
ILayoutStorage		STRUC
lpVtbl			LPILayoutStorageVtbl ?
ILayoutStorage		ENDS



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



LPSURROGATE		typedef ptr ISurrogate


externdef		IID_ISurrogate:IID

ISurrogateVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	  LoadDllServer PVOID ?
	  FreeSurrogate PVOID ?

	END_INTERFACE

ISurrogateVtbl		ENDS

LPISurrogateVtbl	typedef ptr ISurrogateVtbl
ISurrogate		STRUC
lpVtbl			LPISurrogateVtbl ?
ISurrogate		ENDS



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



LPGLOBALINTERFACETABLE	typedef ptr IGlobalInterfaceTable


externdef		IID_IGlobalInterfaceTable:IID


IGlobalInterfaceTableVtbl STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

RegisterInterfaceInGlobal PVOID ?
RevokeInterfaceFromGlobal PVOID ?
 GetInterfaceFromGlobal PVOID ?

	END_INTERFACE

IGlobalInterfaceTableVtbl ENDS

LPIGlobalInterfaceTableVtbl typedef ptr IGlobalInterfaceTableVtbl
IGlobalInterfaceTable	STRUC
lpVtbl			LPIGlobalInterfaceTableVtbl ?
IGlobalInterfaceTable	ENDS

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

IDirectWriterLockVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

     WaitForWriteAccess PVOID ?
     ReleaseWriteAccess PVOID ?
	HaveWriteAccess PVOID ?

	END_INTERFACE

IDirectWriterLockVtbl	ENDS

LPIDirectWriterLockVtbl typedef ptr IDirectWriterLockVtbl
IDirectWriterLock	STRUC
lpVtbl			LPIDirectWriterLockVtbl ?
IDirectWriterLock	ENDS

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

ISynchronizeVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		  _Wait PVOID ?
		 Signal PVOID ?
		  Reset PVOID ?

	END_INTERFACE

ISynchronizeVtbl	ENDS

LPISynchronizeVtbl	typedef ptr ISynchronizeVtbl
ISynchronize		STRUC
lpVtbl			LPISynchronizeVtbl ?
ISynchronize		ENDS


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

ISynchronizeMutexVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		  _Wait PVOID ?
		 Signal PVOID ?
		  Reset PVOID ?
	   ReleaseMutex PVOID ?

	END_INTERFACE

ISynchronizeMutexVtbl	ENDS

LPISynchronizeMutexVtbl typedef ptr ISynchronizeMutexVtbl
ISynchronizeMutex	STRUC
lpVtbl			LPISynchronizeMutexVtbl ?
ISynchronizeMutex	ENDS


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

IAsyncSetupVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	GetAsyncManager PVOID ?

	END_INTERFACE

IAsyncSetupVtbl		ENDS

LPIAsyncSetupVtbl	typedef ptr IAsyncSetupVtbl
IAsyncSetup		STRUC
lpVtbl			LPIAsyncSetupVtbl ?
IAsyncSetup		ENDS



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



LPCANCELMETHODCALLS	typedef ptr ICancelMethodCalls


externdef		IID_ICancelMethodCalls:IID


ICancelMethodCallsVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		 Cancel PVOID ?
	     TestCancel PVOID ?
       SetCancelTimeout PVOID ?

	END_INTERFACE

ICancelMethodCallsVtbl	ENDS

LPICancelMethodCallsVtbl typedef ptr ICancelMethodCallsVtbl
ICancelMethodCalls	STRUC
lpVtbl			LPICancelMethodCallsVtbl ?
ICancelMethodCalls	ENDS



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

IAsyncManagerVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	   CompleteCall PVOID ?
	 GetCallContext PVOID ?
	       GetState PVOID ?

	END_INTERFACE

IAsyncManagerVtbl	ENDS

LPIAsyncManagerVtbl	typedef ptr IAsyncManagerVtbl
IAsyncManager		STRUC
lpVtbl			LPIAsyncManagerVtbl ?
IAsyncManager		ENDS



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

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	   WaitMultiple PVOID ?
	 AddSynchronize PVOID ?

	END_INTERFACE

IWaitMultipleVtbl	ENDS

LPIWaitMultipleVtbl	typedef ptr IWaitMultipleVtbl
IWaitMultiple		STRUC
lpVtbl			LPIWaitMultipleVtbl ?
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

ISynchronizeEventVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	       GetEvent PVOID ?

	END_INTERFACE

ISynchronizeEventVtbl	ENDS

LPISynchronizeEventVtbl typedef ptr ISynchronizeEventVtbl
ISynchronizeEvent	STRUC
lpVtbl			LPISynchronizeEventVtbl ?
ISynchronizeEvent	ENDS



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

IUrlMonVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

      AsyncGetClassBits PVOID ?

	END_INTERFACE

IUrlMonVtbl		ENDS

LPIUrlMonVtbl		typedef ptr IUrlMonVtbl
IUrlMon			STRUC
lpVtbl			LPIUrlMonVtbl ?
IUrlMon			ENDS



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

IClassAccessVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	   GetClassInfo PVOID ?
       GetClassSpecInfo PVOID ?
 GetInstallablePackages PVOID ?

	END_INTERFACE

IClassAccessVtbl	ENDS

LPIClassAccessVtbl	typedef ptr IClassAccessVtbl
IClassAccess		STRUC
lpVtbl			LPIClassAccessVtbl ?
IClassAccess		ENDS



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

IClassRefreshVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	    GetUpgrades PVOID ?
	 CommitUpgrades PVOID ?

	END_INTERFACE

IClassRefreshVtbl	ENDS

LPIClassRefreshVtbl	typedef ptr IClassRefreshVtbl
IClassRefresh		STRUC
lpVtbl			LPIClassRefreshVtbl ?
IClassRefresh		ENDS



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

IEnumPackageVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
		   Next Next@MP ?
		   Skip Skip@MP ?
		  Reset Reset@MP ?
		  Clone Clone@MP ?

	END_INTERFACE

IEnumPackageVtbl	ENDS

LPIEnumPackageVtbl	typedef ptr IEnumPackageVtbl
IEnumPackage		STRUC
lpVtbl			LPIEnumPackageVtbl ?
IEnumPackage		ENDS

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

IEnumClassVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?
		   Next Next@MP ?
		   Skip Skip@MP ?
		  Reset Reset@MP ?
		  Clone Clone@MP ?

	END_INTERFACE

IEnumClassVtbl		ENDS

LPIEnumClassVtbl	typedef ptr IEnumClassVtbl
IEnumClass		STRUC
lpVtbl			LPIEnumClassVtbl ?
IEnumClass		ENDS


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

IClassAdminVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	       NewClass PVOID ?
	    DeleteClass PVOID ?
	   NewInterface PVOID ?
	DeleteInterface PVOID ?
	     NewPackage PVOID ?
	  DeletePackage PVOID ?
	 GetClassesEnum PVOID ?
	GetPackagesEnum PVOID ?
	GetClassDetails PVOID ?
	  GetIidDetails PVOID ?
      GetPackageDetails PVOID ?

	END_INTERFACE

IClassAdminVtbl		ENDS

LPIClassAdminVtbl	typedef ptr IClassAdminVtbl
IClassAdmin		STRUC
lpVtbl			LPIClassAdminVtbl ?
IClassAdmin		ENDS

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





if ( _MSC_VER GE 800 )
;pragma warning(default:4201)
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

endif
