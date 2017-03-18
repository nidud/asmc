.xlist
ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 440
endif

include rpc.inc
include rpcndr.inc
.xlist
ifndef __RPCNDR_H_VERSION__
.err < this stub requires an updated version of rpcndr.inc >
endif ;; __RPCNDR_H_VERSION__

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
.xlist
endif ;;COM_NO_WINDOWS_H

ifndef __objidl_h__
__objidl_h__ equ 1

;; Forward Declarations

ifndef __IMarshal_FWD_DEFINED__
__IMarshal_FWD_DEFINED__ equ 1
endif	;; __IMarshal_FWD_DEFINED__


ifndef __IMalloc_FWD_DEFINED__
__IMalloc_FWD_DEFINED__ equ 1
endif	;; __IMalloc_FWD_DEFINED__


ifndef __IMallocSpy_FWD_DEFINED__
__IMallocSpy_FWD_DEFINED__ equ 1
endif	;; __IMallocSpy_FWD_DEFINED__


ifndef __IStdMarshalInfo_FWD_DEFINED__
__IStdMarshalInfo_FWD_DEFINED__ equ 1
endif	;; __IStdMarshalInfo_FWD_DEFINED__


ifndef __IExternalConnection_FWD_DEFINED__
__IExternalConnection_FWD_DEFINED__ equ 1
endif	;; __IExternalConnection_FWD_DEFINED__


ifndef __IMultiQI_FWD_DEFINED__
__IMultiQI_FWD_DEFINED__ equ 1
endif	;; __IMultiQI_FWD_DEFINED__


ifndef __IEnumUnknown_FWD_DEFINED__
__IEnumUnknown_FWD_DEFINED__ equ 1
endif	;; __IEnumUnknown_FWD_DEFINED__


ifndef __IBindCtx_FWD_DEFINED__
__IBindCtx_FWD_DEFINED__ equ 1
endif	;; __IBindCtx_FWD_DEFINED__


ifndef __IEnumMoniker_FWD_DEFINED__
__IEnumMoniker_FWD_DEFINED__ equ 1
endif	;; __IEnumMoniker_FWD_DEFINED__


ifndef __IRunnableObject_FWD_DEFINED__
__IRunnableObject_FWD_DEFINED__ equ 1
endif	;; __IRunnableObject_FWD_DEFINED__


ifndef __IRunningObjectTable_FWD_DEFINED__
__IRunningObjectTable_FWD_DEFINED__ equ 1
endif	;; __IRunningObjectTable_FWD_DEFINED__


ifndef __IPersist_FWD_DEFINED__
__IPersist_FWD_DEFINED__ equ 1
endif	;; __IPersist_FWD_DEFINED__


ifndef __IPersistStream_FWD_DEFINED__
__IPersistStream_FWD_DEFINED__ equ 1
endif	;; __IPersistStream_FWD_DEFINED__


ifndef __IMoniker_FWD_DEFINED__
__IMoniker_FWD_DEFINED__ equ 1
endif	;; __IMoniker_FWD_DEFINED__


ifndef __IROTData_FWD_DEFINED__
__IROTData_FWD_DEFINED__ equ 1
endif	;; __IROTData_FWD_DEFINED__


ifndef __IEnumString_FWD_DEFINED__
__IEnumString_FWD_DEFINED__ equ 1
endif	;; __IEnumString_FWD_DEFINED__


ifndef __ISequentialStream_FWD_DEFINED__
__ISequentialStream_FWD_DEFINED__ equ 1
endif	;; __ISequentialStream_FWD_DEFINED__


ifndef __IStream_FWD_DEFINED__
__IStream_FWD_DEFINED__ equ 1
endif	;; __IStream_FWD_DEFINED__


ifndef __IEnumSTATSTG_FWD_DEFINED__
__IEnumSTATSTG_FWD_DEFINED__ equ 1
endif	;; __IEnumSTATSTG_FWD_DEFINED__


ifndef __IStorage_FWD_DEFINED__
__IStorage_FWD_DEFINED__ equ 1
endif	;; __IStorage_FWD_DEFINED__


ifndef __IPersistFile_FWD_DEFINED__
__IPersistFile_FWD_DEFINED__ equ 1
endif	;; __IPersistFile_FWD_DEFINED__


ifndef __IPersistStorage_FWD_DEFINED__
__IPersistStorage_FWD_DEFINED__ equ 1
endif	;; __IPersistStorage_FWD_DEFINED__


ifndef __ILockBytes_FWD_DEFINED__
__ILockBytes_FWD_DEFINED__ equ 1
endif	;; __ILockBytes_FWD_DEFINED__


ifndef __IEnumFORMATETC_FWD_DEFINED__
__IEnumFORMATETC_FWD_DEFINED__ equ 1
endif	;; __IEnumFORMATETC_FWD_DEFINED__


ifndef __IEnumSTATDATA_FWD_DEFINED__
__IEnumSTATDATA_FWD_DEFINED__ equ 1
endif	;; __IEnumSTATDATA_FWD_DEFINED__


ifndef __IRootStorage_FWD_DEFINED__
__IRootStorage_FWD_DEFINED__ equ 1
endif	;; __IRootStorage_FWD_DEFINED__


ifndef __IAdviseSink_FWD_DEFINED__
__IAdviseSink_FWD_DEFINED__ equ 1
endif	;; __IAdviseSink_FWD_DEFINED__


ifndef __IAdviseSink2_FWD_DEFINED__
__IAdviseSink2_FWD_DEFINED__ equ 1
endif	;; __IAdviseSink2_FWD_DEFINED__


ifndef __IDataObject_FWD_DEFINED__
__IDataObject_FWD_DEFINED__ equ 1
endif	;; __IDataObject_FWD_DEFINED__


ifndef __IDataAdviseHolder_FWD_DEFINED__
__IDataAdviseHolder_FWD_DEFINED__ equ 1
endif	;; __IDataAdviseHolder_FWD_DEFINED__


ifndef __IMessageFilter_FWD_DEFINED__
__IMessageFilter_FWD_DEFINED__ equ 1
endif	;; __IMessageFilter_FWD_DEFINED__


ifndef __IRpcChannelBuffer_FWD_DEFINED__
__IRpcChannelBuffer_FWD_DEFINED__ equ 1
endif	;; __IRpcChannelBuffer_FWD_DEFINED__


ifndef __IRpcChannelBuffer2_FWD_DEFINED__
__IRpcChannelBuffer2_FWD_DEFINED__ equ 1
endif	;; __IRpcChannelBuffer2_FWD_DEFINED__


ifndef __IRpcChannelBuffer3_FWD_DEFINED__
__IRpcChannelBuffer3_FWD_DEFINED__ equ 1
endif	;; __IRpcChannelBuffer3_FWD_DEFINED__


ifndef __IRpcProxyBuffer_FWD_DEFINED__
__IRpcProxyBuffer_FWD_DEFINED__ equ 1
endif	;; __IRpcProxyBuffer_FWD_DEFINED__


ifndef __IRpcStubBuffer_FWD_DEFINED__
__IRpcStubBuffer_FWD_DEFINED__ equ 1
endif	;; __IRpcStubBuffer_FWD_DEFINED__


ifndef __IPSFactoryBuffer_FWD_DEFINED__
__IPSFactoryBuffer_FWD_DEFINED__ equ 1
endif	;; __IPSFactoryBuffer_FWD_DEFINED__


ifndef __IChannelHook_FWD_DEFINED__
__IChannelHook_FWD_DEFINED__ equ 1
endif	;; __IChannelHook_FWD_DEFINED__


ifndef __IPropertyStorage_FWD_DEFINED__
__IPropertyStorage_FWD_DEFINED__ equ 1
endif	;; __IPropertyStorage_FWD_DEFINED__


ifndef __IPropertySetStorage_FWD_DEFINED__
__IPropertySetStorage_FWD_DEFINED__ equ 1
endif	;; __IPropertySetStorage_FWD_DEFINED__


ifndef __IEnumSTATPROPSTG_FWD_DEFINED__
__IEnumSTATPROPSTG_FWD_DEFINED__ equ 1
endif	;; __IEnumSTATPROPSTG_FWD_DEFINED__


ifndef __IEnumSTATPROPSETSTG_FWD_DEFINED__
__IEnumSTATPROPSETSTG_FWD_DEFINED__ equ 1
endif	;; __IEnumSTATPROPSETSTG_FWD_DEFINED__


ifndef __IClientSecurity_FWD_DEFINED__
__IClientSecurity_FWD_DEFINED__ equ 1
endif	;; __IClientSecurity_FWD_DEFINED__


ifndef __IServerSecurity_FWD_DEFINED__
__IServerSecurity_FWD_DEFINED__ equ 1
endif	;; __IServerSecurity_FWD_DEFINED__


ifndef __IClassActivator_FWD_DEFINED__
__IClassActivator_FWD_DEFINED__ equ 1
endif	;; __IClassActivator_FWD_DEFINED__


ifndef __IRpcOptions_FWD_DEFINED__
__IRpcOptions_FWD_DEFINED__ equ 1
endif	;; __IRpcOptions_FWD_DEFINED__


ifndef __IComBinding_FWD_DEFINED__
__IComBinding_FWD_DEFINED__ equ 1
endif	;; __IComBinding_FWD_DEFINED__


ifndef __IFillLockBytes_FWD_DEFINED__
__IFillLockBytes_FWD_DEFINED__ equ 1
endif	;; __IFillLockBytes_FWD_DEFINED__


ifndef __IProgressNotify_FWD_DEFINED__
__IProgressNotify_FWD_DEFINED__ equ 1
endif	;; __IProgressNotify_FWD_DEFINED__


ifndef __ILayoutStorage_FWD_DEFINED__
__ILayoutStorage_FWD_DEFINED__ equ 1
endif	;; __ILayoutStorage_FWD_DEFINED__


ifndef __ISurrogate_FWD_DEFINED__
__ISurrogate_FWD_DEFINED__ equ 1
endif	;; __ISurrogate_FWD_DEFINED__


ifndef __IGlobalInterfaceTable_FWD_DEFINED__
__IGlobalInterfaceTable_FWD_DEFINED__ equ 1
endif	;; __IGlobalInterfaceTable_FWD_DEFINED__


ifndef __IDirectWriterLock_FWD_DEFINED__
__IDirectWriterLock_FWD_DEFINED__ equ 1
endif	;; __IDirectWriterLock_FWD_DEFINED__


ifndef __ISynchronize_FWD_DEFINED__
__ISynchronize_FWD_DEFINED__ equ 1
endif	;; __ISynchronize_FWD_DEFINED__


ifndef __ISynchronizeMutex_FWD_DEFINED__
__ISynchronizeMutex_FWD_DEFINED__ equ 1
endif	;; __ISynchronizeMutex_FWD_DEFINED__


ifndef __IAsyncSetup_FWD_DEFINED__
__IAsyncSetup_FWD_DEFINED__ equ 1
endif	;; __IAsyncSetup_FWD_DEFINED__


ifndef __ICancelMethodCalls_FWD_DEFINED__
__ICancelMethodCalls_FWD_DEFINED__ equ 1
endif	;; __ICancelMethodCalls_FWD_DEFINED__


ifndef __IAsyncManager_FWD_DEFINED__
__IAsyncManager_FWD_DEFINED__ equ 1
endif	;; __IAsyncManager_FWD_DEFINED__


ifndef __IWaitMultiple_FWD_DEFINED__
__IWaitMultiple_FWD_DEFINED__ equ 1
endif	;; __IWaitMultiple_FWD_DEFINED__


ifndef __ISynchronizeEvent_FWD_DEFINED__
__ISynchronizeEvent_FWD_DEFINED__ equ 1
endif	;; __ISynchronizeEvent_FWD_DEFINED__


ifndef __IUrlMon_FWD_DEFINED__
__IUrlMon_FWD_DEFINED__ equ 1
endif	;; __IUrlMon_FWD_DEFINED__


ifndef __IClassAccess_FWD_DEFINED__
__IClassAccess_FWD_DEFINED__ equ 1
endif	;; __IClassAccess_FWD_DEFINED__


ifndef __IClassRefresh_FWD_DEFINED__
__IClassRefresh_FWD_DEFINED__ equ 1
endif	;; __IClassRefresh_FWD_DEFINED__


ifndef __IEnumPackage_FWD_DEFINED__
__IEnumPackage_FWD_DEFINED__ equ 1
endif	;; __IEnumPackage_FWD_DEFINED__


ifndef __IEnumClass_FWD_DEFINED__
__IEnumClass_FWD_DEFINED__ equ 1
endif	;; __IEnumClass_FWD_DEFINED__


ifndef __IClassAdmin_FWD_DEFINED__
__IClassAdmin_FWD_DEFINED__ equ 1
endif	;; __IClassAdmin_FWD_DEFINED__


include unknwn.inc
.xlist

;void
MIDL_user_free proto _CType \
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

   GetUnmarshalClass@CT typedef proto \
		 pThis: ptr IMarshal,
		  riid: REFIID,
		    pv: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
	     mshlflags: DWORD,
		  pCid: ptr CLSID
   GetUnmarshalClass@MP typedef ptr GetUnmarshalClass@CT
      GetUnmarshalClass GetUnmarshalClass@MP ?

   GetMarshalSizeMax@CT typedef proto \
		 pThis: ptr IMarshal,
		  riid: REFIID,
		    pv: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
	     mshlflags: DWORD,
		 pSize: LPDWORD
   GetMarshalSizeMax@MP typedef ptr GetMarshalSizeMax@CT
      GetMarshalSizeMax GetMarshalSizeMax@MP ?

    MarshalInterface@CT typedef proto \
		 pThis: ptr IMarshal,
		  pStm: ptr IStream,
		  riid: REFIID,
		    pv: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
	     mshlflags: DWORD
    MarshalInterface@MP typedef ptr MarshalInterface@CT
       MarshalInterface MarshalInterface@MP ?

  UnmarshalInterface@CT typedef proto \
		 pThis: ptr IMarshal,
		  pStm: ptr IStream,
		  riid: REFIID,
		   ppv: PVOID
  UnmarshalInterface@MP typedef ptr UnmarshalInterface@CT
     UnmarshalInterface UnmarshalInterface@MP ?

  ReleaseMarshalData@CT typedef proto \
		 pThis: ptr IMarshal,
		  pStm: ptr IStream
  ReleaseMarshalData@MP typedef ptr ReleaseMarshalData@CT
     ReleaseMarshalData ReleaseMarshalData@MP ?

    DisconnectObject@CT typedef proto \
		 pThis: ptr IMarshal,
	    dwReserved: DWORD
    DisconnectObject@MP typedef ptr DisconnectObject@CT
       DisconnectObject DisconnectObject@MP ?

	END_INTERFACE

IMarshalVtbl		ENDS

LPIMarshalVtbl		typedef ptr IMarshalVtbl
IMarshal		STRUC
lpVtbl			LPIMarshalVtbl ?
IMarshal		ENDS


;HRESULT
IMarshal_GetUnmarshalClass_Proxy proto _CType \
		 pThis: ptr IMarshal,
		  riid: REFIID,
		    pv: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
	     mshlflags: DWORD,
		  pCid: ptr CLSID


;void
IMarshal_GetUnmarshalClass_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMarshal_GetMarshalSizeMax_Proxy proto _CType \
		 pThis: ptr IMarshal,
		  riid: REFIID,
		    pv: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
	     mshlflags: DWORD,
		 pSize: LPDWORD


;void
IMarshal_GetMarshalSizeMax_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMarshal_MarshalInterface_Proxy proto _CType \
		 pThis: ptr IMarshal,
		  pStm: ptr IStream,
		  riid: REFIID,
		    pv: PVOID,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
	     mshlflags: DWORD


;void
IMarshal_MarshalInterface_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMarshal_UnmarshalInterface_Proxy proto _CType \
		 pThis: ptr IMarshal,
		  pStm: ptr IStream,
		  riid: REFIID,
		   ppv: PVOID


;void
IMarshal_UnmarshalInterface_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMarshal_ReleaseMarshalData_Proxy proto _CType \
		 pThis: ptr IMarshal,
		  pStm: ptr IStream


;void
IMarshal_ReleaseMarshalData_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMarshal_DisconnectObject_Proxy proto _CType \
		 pThis: ptr IMarshal,
	    dwReserved: DWORD


;void
IMarshal_DisconnectObject_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IMarshal_INTERFACE_DEFINED__


ifndef __IMalloc_INTERFACE_DEFINED__
__IMalloc_INTERFACE_DEFINED__ equ 1

LPMALLOC		typedef ptr IMalloc
externdef		IID_IMalloc:IID

IMallocVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	       Alloc@CT typedef proto \
		 pThis: ptr IMalloc,
		    cb: ULONG
	       Alloc@MP typedef ptr Alloc@CT
		  Alloc Alloc@MP ?

	     Realloc@CT typedef proto \
		 pThis: ptr IMalloc,
		    pv: PVOID,
		    cb: ULONG
	     Realloc@MP typedef ptr Realloc@CT
		Realloc Realloc@MP ?

		Free@CT typedef proto \
		 pThis: ptr IMalloc,
		    pv: PVOID
		Free@MP typedef ptr Free@CT
		   Free Free@MP ?

	     GetSize@CT typedef proto \
		 pThis: ptr IMalloc,
		    pv: PVOID
	     GetSize@MP typedef ptr GetSize@CT
		GetSize GetSize@MP ?

	    DidAlloc@CT typedef proto \
		 pThis: ptr IMalloc,
		    pv: PVOID
	    DidAlloc@MP typedef ptr DidAlloc@CT
	       DidAlloc DidAlloc@MP ?

	HeapMinimize@CT typedef proto \
		 pThis: ptr IMalloc
	HeapMinimize@MP typedef ptr HeapMinimize@CT
	   HeapMinimize HeapMinimize@MP ?

	END_INTERFACE

IMallocVtbl		ENDS

LPIMallocVtbl		typedef ptr IMallocVtbl
IMalloc			STRUC
lpVtbl			LPIMallocVtbl ?
IMalloc			ENDS


;PVOID
IMalloc_Alloc_Proxy proto _CType \
		 pThis: ptr IMalloc,
		    cb: ULONG


;void
IMalloc_Alloc_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;PVOID
IMalloc_Realloc_Proxy proto _CType \
		 pThis: ptr IMalloc,
		    pv: PVOID,
		    cb: ULONG


;void
IMalloc_Realloc_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IMalloc_Free_Proxy proto _CType \
		 pThis: ptr IMalloc,
		    pv: PVOID


;void
IMalloc_Free_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;ULONG
IMalloc_GetSize_Proxy proto _CType \
		 pThis: ptr IMalloc,
		    pv: PVOID


;void
IMalloc_GetSize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;int
IMalloc_DidAlloc_Proxy proto _CType \
		 pThis: ptr IMalloc,
		    pv: PVOID


;void
IMalloc_DidAlloc_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IMalloc_HeapMinimize_Proxy proto _CType \
		 pThis: ptr IMalloc


;void
IMalloc_HeapMinimize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IMalloc_INTERFACE_DEFINED__


ifndef __IMallocSpy_INTERFACE_DEFINED__
__IMallocSpy_INTERFACE_DEFINED__ equ 1



LPMALLOCSPY		typedef ptr IMallocSpy


externdef		IID_IMallocSpy:IID


IMallocSpyVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	    PreAlloc@CT typedef proto \
		 pThis: ptr IMallocSpy,
	     cbRequest: ULONG
	    PreAlloc@MP typedef ptr PreAlloc@CT
	       PreAlloc PreAlloc@MP ?

	   PostAlloc@CT typedef proto \
		 pThis: ptr IMallocSpy,
	       pActual: PVOID
	   PostAlloc@MP typedef ptr PostAlloc@CT
	      PostAlloc PostAlloc@MP ?

	     PreFree@CT typedef proto \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL
	     PreFree@MP typedef ptr PreFree@CT
		PreFree PreFree@MP ?

	    PostFree@CT typedef proto \
		 pThis: ptr IMallocSpy,
		fSpyed: BOOL
	    PostFree@MP typedef ptr PostFree@CT
	       PostFree PostFree@MP ?

	  PreRealloc@CT typedef proto \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
	     cbRequest: ULONG,
	  ppNewRequest: PVOID,
		fSpyed: BOOL
	  PreRealloc@MP typedef ptr PreRealloc@CT
	     PreRealloc PreRealloc@MP ?

	 PostRealloc@CT typedef proto \
		 pThis: ptr IMallocSpy,
	       pActual: PVOID,
		fSpyed: BOOL
	 PostRealloc@MP typedef ptr PostRealloc@CT
	    PostRealloc PostRealloc@MP ?

	  PreGetSize@CT typedef proto \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL
	  PreGetSize@MP typedef ptr PreGetSize@CT
	     PreGetSize PreGetSize@MP ?

	 PostGetSize@CT typedef proto \
		 pThis: ptr IMallocSpy,
	      cbActual: ULONG,
		fSpyed: BOOL
	 PostGetSize@MP typedef ptr PostGetSize@CT
	    PostGetSize PostGetSize@MP ?

	 PreDidAlloc@CT typedef proto \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL
	 PreDidAlloc@MP typedef ptr PreDidAlloc@CT
	    PreDidAlloc PreDidAlloc@MP ?

	PostDidAlloc@CT typedef proto \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL,
	       fActual: SINT
	PostDidAlloc@MP typedef ptr PostDidAlloc@CT
	   PostDidAlloc PostDidAlloc@MP ?

     PreHeapMinimize@CT typedef proto \
		 pThis: ptr IMallocSpy
     PreHeapMinimize@MP typedef ptr PreHeapMinimize@CT
	PreHeapMinimize PreHeapMinimize@MP ?

    PostHeapMinimize@CT typedef proto \
		 pThis: ptr IMallocSpy
    PostHeapMinimize@MP typedef ptr PostHeapMinimize@CT
       PostHeapMinimize PostHeapMinimize@MP ?

	END_INTERFACE

IMallocSpyVtbl		ENDS

LPIMallocSpyVtbl	typedef ptr IMallocSpyVtbl
IMallocSpy		STRUC
lpVtbl			LPIMallocSpyVtbl ?
IMallocSpy		ENDS

;ULONG
IMallocSpy_PreAlloc_Proxy proto _CType \
		 pThis: ptr IMallocSpy,
	     cbRequest: ULONG


;void
IMallocSpy_PreAlloc_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;PVOID
IMallocSpy_PostAlloc_Proxy proto _CType \
		 pThis: ptr IMallocSpy,
	       pActual: PVOID


;void
IMallocSpy_PostAlloc_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;PVOID
IMallocSpy_PreFree_Proxy proto _CType \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL


;void
IMallocSpy_PreFree_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IMallocSpy_PostFree_Proxy proto _CType \
		 pThis: ptr IMallocSpy,
		fSpyed: BOOL


;void
IMallocSpy_PostFree_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;ULONG
IMallocSpy_PreRealloc_Proxy proto _CType \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
	     cbRequest: ULONG,
	  ppNewRequest: PVOID,
		fSpyed: BOOL


;void
IMallocSpy_PreRealloc_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;PVOID
IMallocSpy_PostRealloc_Proxy proto _CType \
		 pThis: ptr IMallocSpy,
	       pActual: PVOID,
		fSpyed: BOOL


;void
IMallocSpy_PostRealloc_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;PVOID
IMallocSpy_PreGetSize_Proxy proto _CType \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL


;void
IMallocSpy_PreGetSize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;ULONG
IMallocSpy_PostGetSize_Proxy proto _CType \
		 pThis: ptr IMallocSpy,
	      cbActual: ULONG,
		fSpyed: BOOL


;void
IMallocSpy_PostGetSize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;PVOID
IMallocSpy_PreDidAlloc_Proxy proto _CType \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL


;void
IMallocSpy_PreDidAlloc_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;int
IMallocSpy_PostDidAlloc_Proxy proto _CType \
		 pThis: ptr IMallocSpy,
	      pRequest: PVOID,
		fSpyed: BOOL,
	       fActual: SINT


;void
IMallocSpy_PostDidAlloc_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IMallocSpy_PreHeapMinimize_Proxy proto _CType \
		 pThis: ptr IMallocSpy


;void
IMallocSpy_PreHeapMinimize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IMallocSpy_PostHeapMinimize_Proxy proto _CType \
		 pThis: ptr IMallocSpy


;void
IMallocSpy_PostHeapMinimize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IMallocSpy_INTERFACE_DEFINED__


ifndef __IStdMarshalInfo_INTERFACE_DEFINED__
__IStdMarshalInfo_INTERFACE_DEFINED__ equ 1



LPSTDMARSHALINFO	typedef ptr IStdMarshalInfo


externdef		IID_IStdMarshalInfo:IID

IStdMarshalInfoVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

  GetClassForHandler@CT typedef proto \
		 pThis: ptr IStdMarshalInfo,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
		pClsid: ptr CLSID
  GetClassForHandler@MP typedef ptr GetClassForHandler@CT
     GetClassForHandler GetClassForHandler@MP ?

	END_INTERFACE

IStdMarshalInfoVtbl	ENDS

LPIStdMarshalInfoVtbl	typedef ptr IStdMarshalInfoVtbl
IStdMarshalInfo		STRUC
lpVtbl			LPIStdMarshalInfoVtbl ?
IStdMarshalInfo		ENDS



;HRESULT
IStdMarshalInfo_GetClassForHandler_Proxy proto _CType \
		 pThis: ptr IStdMarshalInfo,
	 dwDestContext: DWORD,
	 pvDestContext: PVOID,
		pClsid: ptr CLSID


;void
IStdMarshalInfo_GetClassForHandler_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IStdMarshalInfo_INTERFACE_DEFINED__


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

       AddConnection@CT typedef proto \
		 pThis: ptr IExternalConnection,
	       extconn: DWORD,
	      reserved: DWORD
       AddConnection@MP typedef ptr AddConnection@CT
	  AddConnection AddConnection@MP ?

   ReleaseConnection@CT typedef proto \
		 pThis: ptr IExternalConnection,
	       extconn: DWORD,
	      reserved: DWORD,
    fLastReleaseCloses: BOOL
   ReleaseConnection@MP typedef ptr ReleaseConnection@CT
      ReleaseConnection ReleaseConnection@MP ?

	END_INTERFACE

IExternalConnectionVtbl ENDS

LPIExternalConnectionVtbl typedef ptr IExternalConnectionVtbl
IExternalConnection	STRUC
lpVtbl			LPIExternalConnectionVtbl ?
IExternalConnection	ENDS

;DWORD
IExternalConnection_AddConnection_Proxy proto _CType \
		 pThis: ptr IExternalConnection,
	       extconn: DWORD,
	      reserved: DWORD


;void
IExternalConnection_AddConnection_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;DWORD
IExternalConnection_ReleaseConnection_Proxy proto _CType \
		 pThis: ptr IExternalConnection,
	       extconn: DWORD,
	      reserved: DWORD,
    fLastReleaseCloses: BOOL


;void
IExternalConnection_ReleaseConnection_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IExternalConnection_INTERFACE_DEFINED__


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

QueryMultipleInterfaces@CT typedef proto \
		 pThis: ptr IMultiQI,
		 cMQIs: ULONG,
		 pMQIs: ptr MULTI_QI
QueryMultipleInterfaces@MP typedef ptr QueryMultipleInterfaces@CT
QueryMultipleInterfaces QueryMultipleInterfaces@MP ?

	END_INTERFACE

IMultiQIVtbl		ENDS

LPIMultiQIVtbl		typedef ptr IMultiQIVtbl
IMultiQI		STRUC
lpVtbl			LPIMultiQIVtbl ?
IMultiQI		ENDS


;HRESULT
IMultiQI_QueryMultipleInterfaces_Proxy proto _CType \
		 pThis: ptr IMultiQI,
		 cMQIs: ULONG,
		 pMQIs: ptr MULTI_QI


;void
IMultiQI_QueryMultipleInterfaces_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IMultiQI_INTERFACE_DEFINED__

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
IEnumUnknown_RemoteNext_Proxy proto _CType \
		 pThis: ptr IEnumUnknown,
		  celt: ULONG,
		 rgelt: ptr IUnknown,
	  pceltFetched: LPDWORD


;void
IEnumUnknown_RemoteNext_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumUnknown_Skip_Proxy proto _CType \
		 pThis: ptr IEnumUnknown,
		  celt: ULONG


;void
IEnumUnknown_Skip_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumUnknown_Reset_Proxy proto _CType \
		 pThis: ptr IEnumUnknown


;void
IEnumUnknown_Reset_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumUnknown_Clone_Proxy proto _CType \
		 pThis: ptr IEnumUnknown,
		ppenum: ptr IEnumUnknown


;void
IEnumUnknown_Clone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IEnumUnknown_INTERFACE_DEFINED__


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

 RegisterObjectBound@CT typedef proto \
		 pThis: ptr IBindCtx,
		  punk: ptr IUnknown
 RegisterObjectBound@MP typedef ptr RegisterObjectBound@CT
    RegisterObjectBound RegisterObjectBound@MP ?

   RevokeObjectBound@CT typedef proto \
		 pThis: ptr IBindCtx,
		  punk: ptr IUnknown
   RevokeObjectBound@MP typedef ptr RevokeObjectBound@CT
      RevokeObjectBound RevokeObjectBound@MP ?

 ReleaseBoundObjects@CT typedef proto \
		 pThis: ptr IBindCtx
 ReleaseBoundObjects@MP typedef ptr ReleaseBoundObjects@CT
    ReleaseBoundObjects ReleaseBoundObjects@MP ?

      SetBindOptions@CT typedef proto \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS
      SetBindOptions@MP typedef ptr SetBindOptions@CT
	 SetBindOptions SetBindOptions@MP ?

      GetBindOptions@CT typedef proto \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS
      GetBindOptions@MP typedef ptr GetBindOptions@CT
	 GetBindOptions GetBindOptions@MP ?

GetRunningObjectTable@CT typedef proto \
		 pThis: ptr IBindCtx,
		 pprot: ptr IRunningObjectTable
GetRunningObjectTable@MP typedef ptr GetRunningObjectTable@CT
  GetRunningObjectTable GetRunningObjectTable@MP ?

 RegisterObjectParam@CT typedef proto \
		 pThis: ptr IBindCtx,
		pszKey: LPOLESTR,
		  punk: ptr IUnknown
 RegisterObjectParam@MP typedef ptr RegisterObjectParam@CT
    RegisterObjectParam RegisterObjectParam@MP ?

      GetObjectParam@CT typedef proto \
		 pThis: ptr IBindCtx,
		pszKey: LPOLESTR,
		 ppunk: ptr IUnknown
      GetObjectParam@MP typedef ptr GetObjectParam@CT
	 GetObjectParam GetObjectParam@MP ?

     EnumObjectParam@CT typedef proto \
		 pThis: ptr IBindCtx,
		ppenum: ptr IEnumString
     EnumObjectParam@MP typedef ptr EnumObjectParam@CT
	EnumObjectParam EnumObjectParam@MP ?

   RevokeObjectParam@CT typedef proto \
		 pThis: ptr IBindCtx,
		pszKey: LPOLESTR
   RevokeObjectParam@MP typedef ptr RevokeObjectParam@CT
      RevokeObjectParam RevokeObjectParam@MP ?

	END_INTERFACE

IBindCtxVtbl		ENDS

LPIBindCtxVtbl		typedef ptr IBindCtxVtbl
IBindCtx		STRUC
lpVtbl			LPIBindCtxVtbl ?
IBindCtx		ENDS



;HRESULT
IBindCtx_RegisterObjectBound_Proxy proto _CType \
		 pThis: ptr IBindCtx,
		  punk: ptr IUnknown


;void
IBindCtx_RegisterObjectBound_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IBindCtx_RevokeObjectBound_Proxy proto _CType \
		 pThis: ptr IBindCtx,
		  punk: ptr IUnknown


;void
IBindCtx_RevokeObjectBound_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IBindCtx_ReleaseBoundObjects_Proxy proto _CType \
		 pThis: ptr IBindCtx


;void
IBindCtx_ReleaseBoundObjects_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IBindCtx_RemoteSetBindOptions_Proxy proto _CType \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS2


;void
IBindCtx_RemoteSetBindOptions_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IBindCtx_RemoteGetBindOptions_Proxy proto _CType \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS2


;void
IBindCtx_RemoteGetBindOptions_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IBindCtx_GetRunningObjectTable_Proxy proto _CType \
		 pThis: ptr IBindCtx,
		 pprot: ptr IRunningObjectTable


;void
IBindCtx_GetRunningObjectTable_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IBindCtx_RegisterObjectParam_Proxy proto _CType \
		 pThis: ptr IBindCtx,
		pszKey: LPOLESTR,
		  punk: ptr IUnknown


;void
IBindCtx_RegisterObjectParam_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IBindCtx_GetObjectParam_Proxy proto _CType \
		 pThis: ptr IBindCtx,
		pszKey: LPOLESTR,
		 ppunk: ptr IUnknown


;void
IBindCtx_GetObjectParam_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IBindCtx_EnumObjectParam_Proxy proto _CType \
		 pThis: ptr IBindCtx,
		ppenum: ptr IEnumString


;void
IBindCtx_EnumObjectParam_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IBindCtx_RevokeObjectParam_Proxy proto _CType \
		 pThis: ptr IBindCtx,
		pszKey: LPOLESTR


;void
IBindCtx_RevokeObjectParam_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IBindCtx_INTERFACE_DEFINED__


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
IEnumMoniker_RemoteNext_Proxy proto _CType \
		 pThis: ptr IEnumMoniker,
		  celt: ULONG,
		 rgelt: ptr IMoniker,
	  pceltFetched: LPDWORD


;void
IEnumMoniker_RemoteNext_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumMoniker_Skip_Proxy proto _CType \
		 pThis: ptr IEnumMoniker,
		  celt: ULONG


;void
IEnumMoniker_Skip_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumMoniker_Reset_Proxy proto _CType \
		 pThis: ptr IEnumMoniker


;void
IEnumMoniker_Reset_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumMoniker_Clone_Proxy proto _CType \
		 pThis: ptr IEnumMoniker,
		ppenum: ptr IEnumMoniker


;void
IEnumMoniker_Clone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IEnumMoniker_INTERFACE_DEFINED__


ifndef __IRunnableObject_INTERFACE_DEFINED__
__IRunnableObject_INTERFACE_DEFINED__ equ 1



LPRUNNABLEOBJECT	typedef ptr IRunnableObject


externdef		IID_IRunnableObject:IID


IRunnableObjectVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

     GetRunningClass@CT typedef proto \
		 pThis: ptr IRunnableObject,
	       lpClsid: LPCLSID
     GetRunningClass@MP typedef ptr GetRunningClass@CT
	GetRunningClass GetRunningClass@MP ?

		 Run@CT typedef proto \
		 pThis: ptr IRunnableObject,
		   pbc: LPBINDCTX
		 Run@MP typedef ptr Run@CT
		    Run Run@MP ?

	   IsRunning@CT typedef proto \
		 pThis: ptr IRunnableObject
	   IsRunning@MP typedef ptr IsRunning@CT
	      IsRunning IsRunning@MP ?

	 LockRunning@CT typedef proto \
		 pThis: ptr IRunnableObject,
		 fLock: BOOL,
     fLastUnlockCloses: BOOL
	 LockRunning@MP typedef ptr LockRunning@CT
	    LockRunning LockRunning@MP ?

  SetContainedObject@CT typedef proto \
		 pThis: ptr IRunnableObject,
	    fContained: BOOL
  SetContainedObject@MP typedef ptr SetContainedObject@CT
     SetContainedObject SetContainedObject@MP ?

	END_INTERFACE

IRunnableObjectVtbl	ENDS

LPIRunnableObjectVtbl	typedef ptr IRunnableObjectVtbl
IRunnableObject		STRUC
lpVtbl			LPIRunnableObjectVtbl ?
IRunnableObject		ENDS
;HRESULT
IRunnableObject_GetRunningClass_Proxy proto _CType \
		 pThis: ptr IRunnableObject,
	       lpClsid: LPCLSID


;void
IRunnableObject_GetRunningClass_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRunnableObject_Run_Proxy proto _CType \
		 pThis: ptr IRunnableObject,
		   pbc: LPBINDCTX


;void
IRunnableObject_Run_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRunnableObject_RemoteIsRunning_Proxy proto _CType \
		 pThis: ptr IRunnableObject


;void
IRunnableObject_RemoteIsRunning_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRunnableObject_LockRunning_Proxy proto _CType \
		 pThis: ptr IRunnableObject,
		 fLock: BOOL,
     fLastUnlockCloses: BOOL


;void
IRunnableObject_LockRunning_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRunnableObject_SetContainedObject_Proxy proto _CType \
		 pThis: ptr IRunnableObject,
	    fContained: BOOL


;void
IRunnableObject_SetContainedObject_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IRunnableObject_INTERFACE_DEFINED__


ifndef __IRunningObjectTable_INTERFACE_DEFINED__
__IRunningObjectTable_INTERFACE_DEFINED__ equ 1



LPRUNNINGOBJECTTABLE	typedef ptr IRunningObjectTable


externdef		IID_IRunningObjectTable:IID

IRunningObjectTableVtbl STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	    Register@CT typedef proto \
		 pThis: ptr IRunningObjectTable,
	      grfFlags: DWORD,
	    punkObject: ptr IUnknown,
	 pmkObjectName: ptr IMoniker,
	   pdwRegister: LPDWORD
	    Register@MP typedef ptr Register@CT
	       Register Register@MP ?

	      Revoke@CT typedef proto \
		 pThis: ptr IRunningObjectTable,
	    dwRegister: DWORD
	      Revoke@MP typedef ptr Revoke@CT
		 Revoke Revoke@MP ?

	   IRunningObjectTableVtblIs@Running@CT typedef proto \
		 pThis: ptr IRunningObjectTable,
	 pmkObjectName: ptr IMoniker
	   IRunningObjectTableVtblIs@IsRunning@MP typedef ptr IRunningObjectTableVtblIs@IsRunning@CT
	      IsRunning IRunningObjectTableVtblIs@IsRunning@MP ?

	   GetObject@CT typedef proto \
		 pThis: ptr IRunningObjectTable,
	 pmkObjectName: ptr IMoniker,
	   ppunkObject: ptr IUnknown
	   GetObject@MP typedef ptr GetObject@CT
	      GetObject GetObject@MP ?

      NoteChangeTime@CT typedef proto \
		 pThis: ptr IRunningObjectTable,
	    dwRegister: DWORD,
	     pfiletime: LPFILETIME
      NoteChangeTime@MP typedef ptr NoteChangeTime@CT
	 NoteChangeTime NoteChangeTime@MP ?

 GetTimeOfLastChange@CT typedef proto \
		 pThis: ptr IRunningObjectTable,
	 pmkObjectName: ptr IMoniker,
	     pfiletime: LPFILETIME
 GetTimeOfLastChange@MP typedef ptr GetTimeOfLastChange@CT
    GetTimeOfLastChange GetTimeOfLastChange@MP ?

	 EnumRunning@CT typedef proto \
		 pThis: ptr IRunningObjectTable,
	 ppenumMoniker: ptr IEnumMoniker
	 EnumRunning@MP typedef ptr EnumRunning@CT
	    EnumRunning EnumRunning@MP ?

	END_INTERFACE

IRunningObjectTableVtbl ENDS

LPIRunningObjectTableVtbl typedef ptr IRunningObjectTableVtbl
IRunningObjectTable	STRUC
lpVtbl			LPIRunningObjectTableVtbl ?
IRunningObjectTable	ENDS
;HRESULT
IRunningObjectTable_Register_Proxy proto _CType \
		 pThis: ptr IRunningObjectTable,
	      grfFlags: DWORD,
	    punkObject: ptr IUnknown,
	 pmkObjectName: ptr IMoniker,
	   pdwRegister: LPDWORD


;void
IRunningObjectTable_Register_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRunningObjectTable_Revoke_Proxy proto _CType \
		 pThis: ptr IRunningObjectTable,
	    dwRegister: DWORD


;void
IRunningObjectTable_Revoke_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRunningObjectTable_IsRunning_Proxy proto _CType \
		 pThis: ptr IRunningObjectTable,
	 pmkObjectName: ptr IMoniker


;void
IRunningObjectTable_IsRunning_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRunningObjectTable_GetObject_Proxy proto _CType \
		 pThis: ptr IRunningObjectTable,
	 pmkObjectName: ptr IMoniker,
	   ppunkObject: ptr IUnknown


;void
IRunningObjectTable_GetObject_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRunningObjectTable_NoteChangeTime_Proxy proto _CType \
		 pThis: ptr IRunningObjectTable,
	    dwRegister: DWORD,
	     pfiletime: LPFILETIME


;void
IRunningObjectTable_NoteChangeTime_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRunningObjectTable_GetTimeOfLastChange_Proxy proto _CType \
		 pThis: ptr IRunningObjectTable,
	 pmkObjectName: ptr IMoniker,
	     pfiletime: LPFILETIME


;void
IRunningObjectTable_GetTimeOfLastChange_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRunningObjectTable_EnumRunning_Proxy proto _CType \
		 pThis: ptr IRunningObjectTable,
	 ppenumMoniker: ptr IEnumMoniker


;void
IRunningObjectTable_EnumRunning_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IRunningObjectTable_INTERFACE_DEFINED__

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
IPersist_GetClassID_Proxy proto _CType \
		 pThis: ptr IPersist,
	      pClassID: ptr CLSID


;void
IPersist_GetClassID_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IPersist_INTERFACE_DEFINED__

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

	       Save1@CT typedef proto \
		 pThis: ptr IPersistStream,
		  pStm: ptr IStream,
	   fClearDirty: BOOL
	       Save1@MP typedef ptr Save1@CT
		   Save Save1@MP ?

	  GetSizeMax@CT typedef proto \
		 pThis: ptr IPersistStream,
	       pcbSize: ptr ULARGE_INTEGER
	  GetSizeMax@MP typedef ptr GetSizeMax@CT
	     GetSizeMax GetSizeMax@MP ?

	END_INTERFACE

IPersistStreamVtbl	ENDS

LPIPersistStreamVtbl	typedef ptr IPersistStreamVtbl
IPersistStream		STRUC
lpVtbl			LPIPersistStreamVtbl ?
IPersistStream		ENDS


;HRESULT
IPersistStream_IsDirty_Proxy proto _CType \
		 pThis: ptr IPersistStream


;void
IPersistStream_IsDirty_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistStream_Load_Proxy proto _CType \
		 pThis: ptr IPersistStream,
		  pStm: ptr IStream


;void
IPersistStream_Load_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistStream_Save_Proxy proto _CType \
		 pThis: ptr IPersistStream,
		  pStm: ptr IStream,
	   fClearDirty: BOOL


;void
IPersistStream_Save_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistStream_GetSizeMax_Proxy proto _CType \
		 pThis: ptr IPersistStream,
	       pcbSize: ptr ULARGE_INTEGER


;void
IPersistStream_GetSizeMax_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IPersistStream_INTERFACE_DEFINED__


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

	       Save2@CT typedef proto \
		 pThis: ptr IMoniker,
		  pStm: ptr IStream,
	   fClearDirty: BOOL
	       Save2@MP typedef Save2@CT
		   Save Save2@MP ?

	  IMonikerVtbl@GetSizeMax@CT typedef proto \
		 pThis: ptr IMoniker,
	       pcbSize: ptr ULARGE_INTEGER
	  IMonikerVtbl@GetSizeMax@MP typedef ptr IMonikerVtbl@GetSizeMax@CT
	     GetSizeMax IMonikerVtbl@GetSizeMax@MP ?

	BindToObject@CT typedef proto \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	    riidResult: REFIID,
	     ppvResult: PVOID
	BindToObject@MP typedef ptr BindToObject@CT
	   BindToObject BindToObject@MP ?

       BindToStorage@CT typedef proto \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
		  riid: REFIID,
		ppvObj: PVOID
       BindToStorage@MP typedef ptr BindToStorage@CT
	  BindToStorage BindToStorage@MP ?

	      Reduce@CT typedef proto \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	dwReduceHowFar: DWORD,
	    ppmkToLeft: ptr IMoniker,
	   ppmkReduced: ptr IMoniker
	      Reduce@MP typedef ptr Reduce@CT
		 Reduce Reduce@MP ?

	 ComposeWith@CT typedef proto \
		 pThis: ptr IMoniker,
	      pmkRight: ptr IMoniker,
     fOnlyIfNotGeneric: BOOL,
	 ppmkComposite: ptr IMoniker
	 ComposeWith@MP typedef ptr ComposeWith@CT
	    ComposeWith ComposeWith@MP ?

		Enum@CT typedef proto \
		 pThis: ptr IMoniker,
	      fForward: BOOL,
	 ppenumMoniker: ptr IEnumMoniker
		Enum@MP typedef ptr Enum@CT
		   Enum Enum@MP ?

	     IsEqual@CT typedef proto \
		 pThis: ptr IMoniker,
       pmkOtherMoniker: ptr IMoniker
	     IsEqual@MP typedef ptr IsEqual@CT
		IsEqual IsEqual@MP ?

		Hash@CT typedef proto \
		 pThis: ptr IMoniker,
	       pdwHash: LPDWORD
		Hash@MP typedef ptr Hash@CT
		   Hash Hash@MP ?

	   IMonikerVtbl@IsRunning@CT typedef proto \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
       pmkNewlyRunning: ptr IMoniker
	   IMonikerVtbl@IsRunning@MP typedef ptr IMonikerVtbl@IsRunning@CT
	      IsRunning IMonikerVtbl@IsRunning@MP ?

 IMonikerVtbl@GetTimeOfLastChange@CT typedef proto \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	     pFileTime: LPFILETIME
 IMonikerVtbl@GetTimeOfLastChange@MP typedef ptr IMonikerVtbl@GetTimeOfLastChange@CT
    GetTimeOfLastChange IMonikerVtbl@GetTimeOfLastChange@MP ?

	     Inverse@CT typedef proto \
		 pThis: ptr IMoniker,
		  ppmk: ptr IMoniker
	     Inverse@MP typedef ptr Inverse@CT
		Inverse Inverse@MP ?

    CommonPrefixWith@CT typedef proto \
		 pThis: ptr IMoniker,
	      pmkOther: ptr IMoniker,
	    ppmkPrefix: ptr IMoniker
    CommonPrefixWith@MP typedef ptr CommonPrefixWith@CT
       CommonPrefixWith CommonPrefixWith@MP ?

      RelativePathTo@CT typedef proto \
		 pThis: ptr IMoniker,
	      pmkOther: ptr IMoniker,
	   ppmkRelPath: ptr IMoniker
      RelativePathTo@MP typedef ptr RelativePathTo@CT
	 RelativePathTo RelativePathTo@MP ?

      GetDisplayName@CT typedef proto \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
       ppszDisplayName: ptr LPOLESTR
      GetDisplayName@MP typedef ptr GetDisplayName@CT
	 GetDisplayName GetDisplayName@MP ?

    ParseDisplayName@CT typedef proto \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	pszDisplayName: LPOLESTR,
	      pchEaten: LPDWORD,
	       ppmkOut: ptr IMoniker
    ParseDisplayName@MP typedef ptr ParseDisplayName@CT
       ParseDisplayName ParseDisplayName@MP ?

     IsSystemMoniker@CT typedef proto \
		 pThis: ptr IMoniker,
	      pdwMksys: LPDWORD
     IsSystemMoniker@MP typedef ptr IsSystemMoniker@CT
	IsSystemMoniker IsSystemMoniker@MP ?

	END_INTERFACE

IMonikerVtbl		ENDS

LPIMonikerVtbl		typedef ptr IMonikerVtbl
IMoniker		STRUC
lpVtbl			LPIMonikerVtbl ?
IMoniker		ENDS


;HRESULT
IMoniker_RemoteBindToObject_Proxy proto _CType \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	    riidResult: REFIID,
	     ppvResult: ptr IUnknown


;void
IMoniker_RemoteBindToObject_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_RemoteBindToStorage_Proxy proto _CType \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
		  riid: REFIID,
		ppvObj: ptr IUnknown


;void
IMoniker_RemoteBindToStorage_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_Reduce_Proxy proto _CType \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	dwReduceHowFar: DWORD,
	    ppmkToLeft: ptr IMoniker,
	   ppmkReduced: ptr IMoniker


;void
IMoniker_Reduce_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_ComposeWith_Proxy proto _CType \
		 pThis: ptr IMoniker,
	      pmkRight: ptr IMoniker,
     fOnlyIfNotGeneric: BOOL,
	 ppmkComposite: ptr IMoniker


;void
IMoniker_ComposeWith_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_Enum_Proxy proto _CType \
		 pThis: ptr IMoniker,
	      fForward: BOOL,
	 ppenumMoniker: ptr IEnumMoniker


;void
IMoniker_Enum_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_IsEqual_Proxy proto _CType \
		 pThis: ptr IMoniker,
       pmkOtherMoniker: ptr IMoniker


;void
IMoniker_IsEqual_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_Hash_Proxy proto _CType \
		 pThis: ptr IMoniker,
	       pdwHash: LPDWORD


;void
IMoniker_Hash_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_IsRunning_Proxy proto _CType \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
       pmkNewlyRunning: ptr IMoniker


;void
IMoniker_IsRunning_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_GetTimeOfLastChange_Proxy proto _CType \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	     pFileTime: LPFILETIME


;void
IMoniker_GetTimeOfLastChange_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_Inverse_Proxy proto _CType \
		 pThis: ptr IMoniker,
		  ppmk: ptr IMoniker


;void
IMoniker_Inverse_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_CommonPrefixWith_Proxy proto _CType \
		 pThis: ptr IMoniker,
	      pmkOther: ptr IMoniker,
	    ppmkPrefix: ptr IMoniker


;void
IMoniker_CommonPrefixWith_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_RelativePathTo_Proxy proto _CType \
		 pThis: ptr IMoniker,
	      pmkOther: ptr IMoniker,
	   ppmkRelPath: ptr IMoniker


;void
IMoniker_RelativePathTo_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_GetDisplayName_Proxy proto _CType \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
       ppszDisplayName: ptr LPOLESTR


;void
IMoniker_GetDisplayName_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_ParseDisplayName_Proxy proto _CType \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	pszDisplayName: LPOLESTR,
	      pchEaten: LPDWORD,
	       ppmkOut: ptr IMoniker


;void
IMoniker_ParseDisplayName_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IMoniker_IsSystemMoniker_Proxy proto _CType \
		 pThis: ptr IMoniker,
	      pdwMksys: LPDWORD


;void
IMoniker_IsSystemMoniker_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IMoniker_INTERFACE_DEFINED__


ifndef __IROTData_INTERFACE_DEFINED__
__IROTData_INTERFACE_DEFINED__ equ 1

externdef		IID_IROTData:IID


IROTDataVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

   GetComparisonData@CT typedef proto \
		 pThis: ptr IROTData,
		pbData: LPBYTE,
		 cbMax: ULONG,
	       pcbData: LPDWORD
   GetComparisonData@MP typedef ptr GetComparisonData@CT
      GetComparisonData GetComparisonData@MP ?

	END_INTERFACE

IROTDataVtbl		ENDS

LPIROTDataVtbl		typedef ptr IROTDataVtbl
IROTData		STRUC
lpVtbl			LPIROTDataVtbl ?
IROTData		ENDS


;HRESULT
IROTData_GetComparisonData_Proxy proto _CType \
		 pThis: ptr IROTData,
		pbData: LPBYTE,
		 cbMax: ULONG,
	       pcbData: LPDWORD


;void
IROTData_GetComparisonData_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IROTData_INTERFACE_DEFINED__


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
IEnumString_RemoteNext_Proxy proto _CType \
		 pThis: ptr IEnumString,
		  celt: ULONG,
		 rgelt: ptr LPOLESTR,
	  pceltFetched: LPDWORD


;void
IEnumString_RemoteNext_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumString_Skip_Proxy proto _CType \
		 pThis: ptr IEnumString,
		  celt: ULONG


;void
IEnumString_Skip_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumString_Reset_Proxy proto _CType \
		 pThis: ptr IEnumString


;void
IEnumString_Reset_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumString_Clone_Proxy proto _CType \
		 pThis: ptr IEnumString,
		ppenum: ptr IEnumString


;void
IEnumString_Clone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IEnumString_INTERFACE_DEFINED__


ifndef __ISequentialStream_INTERFACE_DEFINED__
__ISequentialStream_INTERFACE_DEFINED__ equ 1

externdef		IID_ISequentialStream:IID


ISequentialStreamVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		Read@CT typedef proto \
		 pThis: ptr ISequentialStream,
		    pv: PVOID,
		    cb: ULONG,
	       pcbRead: LPDWORD
		Read@MP typedef ptr Read@CT
		   Read Read@MP ?

	       Write@CT typedef proto \
		 pThis: ptr ISequentialStream,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD
	       Write@MP typedef ptr Write@CT
		  Write Write@MP ?

	END_INTERFACE

ISequentialStreamVtbl	ENDS

LPISequentialStreamVtbl typedef ptr ISequentialStreamVtbl
ISequentialStream	STRUC
lpVtbl			LPISequentialStreamVtbl ?
ISequentialStream	ENDS


;HRESULT
ISequentialStream_RemoteRead_Proxy proto _CType \
		 pThis: ptr ISequentialStream,
		    pv: LPBYTE,
		    cb: ULONG,
	       pcbRead: LPDWORD


;void
ISequentialStream_RemoteRead_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ISequentialStream_RemoteWrite_Proxy proto _CType \
		 pThis: ptr ISequentialStream,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;void
ISequentialStream_RemoteWrite_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __ISequentialStream_INTERFACE_DEFINED__


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

    IStreamVtbl@Read@CT typedef proto \
		 pThis: ptr IStream,
		    pv: PVOID,
		    cb: ULONG,
	       pcbRead: LPDWORD
    IStreamVtbl@Read@MP typedef ptr IStreamVtbl@Read@CT
		   Read IStreamVtbl@Read@MP ?

   IStreamVtbl@Write@CT typedef proto \
		 pThis: ptr IStream,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD
   IStreamVtbl@Write@MP typedef ptr IStreamVtbl@Write@CT
		  Write IStreamVtbl@Write@MP ?

		Seek@CT typedef proto \
		 pThis: ptr IStream,
	      dlibMove: LARGE_INTEGER,
	      dwOrigin: DWORD,
       plibNewPosition: ptr ULARGE_INTEGER
		Seek@MP typedef ptr Seek@CT
		   Seek Seek@MP ?

	     SetSize@CT typedef proto \
		 pThis: ptr IStream,
	    libNewSize: ULARGE_INTEGER
	     SetSize@MP typedef ptr SetSize@CT
		SetSize SetSize@MP ?

	      CopyTo@CT typedef proto \
		 pThis: ptr IStream,
		  pstm: ptr IStream,
		    cb: ULARGE_INTEGER,
	       pcbRead: ptr ULARGE_INTEGER,
	    pcbWritten: ptr ULARGE_INTEGER
	      CopyTo@MP typedef ptr CopyTo@CT
		 CopyTo CopyTo@MP ?

	      Commit@CT typedef proto \
		 pThis: ptr IStream,
	grfCommitFlags: DWORD
	      Commit@MP typedef ptr Commit@CT
		 Commit Commit@MP ?

	      Revert@CT typedef proto \
		 pThis: ptr IStream
	      Revert@MP typedef ptr Revert@CT
		 Revert Revert@MP ?

	  LockRegion@CT typedef proto \
		 pThis: ptr IStream,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD
	  LockRegion@MP typedef ptr LockRegion@CT
	     LockRegion LockRegion@MP ?

	UnlockRegion@CT typedef proto \
		 pThis: ptr IStream,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD
	UnlockRegion@MP typedef ptr UnlockRegion@CT
	   UnlockRegion UnlockRegion@MP ?

		Stat@CT typedef proto \
		 pThis: ptr IStream,
	      pstatstg: ptr STATSTG,
	   grfStatFlag: DWORD
		Stat@MP typedef ptr Stat@CT
		   Stat Stat@MP ?

		  Clone Clone@MP ?

	END_INTERFACE

IStreamVtbl		ENDS

LPIStreamVtbl		typedef ptr IStreamVtbl
IStream			STRUC
lpVtbl			LPIStreamVtbl ?
IStream			ENDS


;HRESULT
IStream_RemoteSeek_Proxy proto _CType \
		 pThis: ptr IStream,
	      dlibMove: LARGE_INTEGER,
	      dwOrigin: DWORD,
       plibNewPosition: ptr ULARGE_INTEGER


;void
IStream_RemoteSeek_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStream_SetSize_Proxy proto _CType \
		 pThis: ptr IStream,
	    libNewSize: ULARGE_INTEGER


;void
IStream_SetSize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStream_RemoteCopyTo_Proxy proto _CType \
		 pThis: ptr IStream,
		  pstm: ptr IStream,
		    cb: ULARGE_INTEGER,
	       pcbRead: ptr ULARGE_INTEGER,
	    pcbWritten: ptr ULARGE_INTEGER


;void
IStream_RemoteCopyTo_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStream_Commit_Proxy proto _CType \
		 pThis: ptr IStream,
	grfCommitFlags: DWORD


;void
IStream_Commit_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStream_Revert_Proxy proto _CType \
		 pThis: ptr IStream


;void
IStream_Revert_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStream_LockRegion_Proxy proto _CType \
		 pThis: ptr IStream,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD


;void
IStream_LockRegion_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStream_UnlockRegion_Proxy proto _CType \
		 pThis: ptr IStream,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD


;void
IStream_UnlockRegion_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStream_Stat_Proxy proto _CType \
		 pThis: ptr IStream,
	      pstatstg: ptr STATSTG,
	   grfStatFlag: DWORD


;void
IStream_Stat_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStream_Clone_Proxy proto _CType \
		 pThis: ptr IStream,
		 ppstm: ptr IStream


;void
IStream_Clone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IStream_INTERFACE_DEFINED__


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
IEnumSTATSTG_RemoteNext_Proxy proto _CType \
		 pThis: ptr IEnumSTATSTG,
		  celt: ULONG,
		 rgelt: ptr STATSTG,
	  pceltFetched: LPDWORD


;void
IEnumSTATSTG_RemoteNext_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATSTG_Skip_Proxy proto _CType \
		 pThis: ptr IEnumSTATSTG,
		  celt: ULONG


;void
IEnumSTATSTG_Skip_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATSTG_Reset_Proxy proto _CType \
		 pThis: ptr IEnumSTATSTG


;void
IEnumSTATSTG_Reset_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATSTG_Clone_Proxy proto _CType \
		 pThis: ptr IEnumSTATSTG,
		ppenum: ptr IEnumSTATSTG


;void
IEnumSTATSTG_Clone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IEnumSTATSTG_INTERFACE_DEFINED__


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

	CreateStream@CT typedef proto \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	       grfMode: DWORD,
	     reserved1: DWORD,
	     reserved2: DWORD,
		 ppstm: ptr IStream
	CreateStream@MP typedef ptr CreateStream@CT
	   CreateStream CreateStream@MP ?

	  OpenStream@CT typedef proto \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	     reserved1: PVOID,
	       grfMode: DWORD,
	     reserved2: DWORD,
		 ppstm: ptr IStream
	  OpenStream@MP typedef ptr OpenStream@CT
	     OpenStream OpenStream@MP ?

       CreateStorage@CT typedef proto \
		_pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	       grfMode: DWORD,
	     reserved1: DWORD,
	     reserved2: DWORD,
		 ppstg: ptr IStorage
       CreateStorage@MP typedef ptr CreateStorage@CT
	  CreateStorage CreateStorage@MP ?

	 OpenStorage@CT typedef proto \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	  pstgPriority: ptr IStorage,
	       grfMode: DWORD,
	    snbExclude: SNB,
	      reserved: DWORD,
		 ppstg: ptr IStorage
	 OpenStorage@MP typedef ptr OpenStorage@CT
	    OpenStorage OpenStorage@MP ?

	     CopyTo2@CT typedef proto \
		 pThis: ptr IStorage,
	   ciidExclude: DWORD,
	  rgiidExclude: ptr IID,
	    snbExclude: SNB,
	      pstgDest: ptr IStorage
	     CopyTo2@MP typedef ptr CopyTo2@CT
		 CopyTo CopyTo2@MP ?

       MoveElementTo@CT typedef proto \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	      pstgDest: ptr IStorage,
	   pwcsNewName: ptr OLECHAR,
	      grfFlags: DWORD
       MoveElementTo@MP typedef ptr MoveElementTo@CT
	  MoveElementTo MoveElementTo@MP ?

	     Commit2@CT typedef proto \
		 pThis: ptr IStorage,
	grfCommitFlags: DWORD
	     Commit2@MP typedef ptr Commit2@CT
		 Commit Commit2@MP ?

	     Revert2@CT typedef proto \
		 pThis: ptr IStorage
	     Revert2@MP typedef ptr Revert2@CT
		 Revert Revert2@MP ?

	EnumElements@CT typedef proto \
		 pThis: ptr IStorage,
	     reserved1: DWORD,
	     reserved2: PVOID,
	     reserved3: DWORD,
		ppenum: ptr IEnumSTATSTG
	EnumElements@MP typedef ptr EnumElements@CT
	   EnumElements EnumElements@MP ?

      DestroyElement@CT typedef proto \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR
      DestroyElement@MP typedef ptr DestroyElement@CT
	 DestroyElement DestroyElement@MP ?

       RenameElement@CT typedef proto \
		 pThis: ptr IStorage,
	   pwcsOldName: ptr OLECHAR,
	   pwcsNewName: ptr OLECHAR
       RenameElement@MP typedef ptr RenameElement@CT
	  RenameElement RenameElement@MP ?

     SetElementTimes@CT typedef proto \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
		pctime: LPFILETIME,
		patime: LPFILETIME,
		pmtime: LPFILETIME
     SetElementTimes@MP typedef ptr SetElementTimes@CT
	SetElementTimes SetElementTimes@MP ?

	    SetClass@CT typedef proto \
		 pThis: ptr IStorage,
		 clsid: REFCLSID
	    SetClass@MP typedef ptr SetClass@CT
	       SetClass SetClass@MP ?

	SetStateBits@CT typedef proto \
		 pThis: ptr IStorage,
	  grfStateBits: DWORD,
	       grfMask: DWORD
	SetStateBits@MP typedef ptr SetStateBits@CT
	   SetStateBits SetStateBits@MP ?

   IStorageVtbl@Stat@CT typedef proto \
		 pThis: ptr IStorage,
	      pstatstg: ptr STATSTG,
	   grfStatFlag: DWORD
   IStorageVtbl@Stat@MP typedef ptr IStorageVtbl@Stat@CT
		   Stat IStorageVtbl@Stat@MP ?

	END_INTERFACE

IStorageVtbl		ENDS

LPIStorageVtbl		typedef ptr IStorageVtbl
IStorage		STRUC
lpVtbl			LPIStorageVtbl ?
IStorage		ENDS



;HRESULT
IStorage_CreateStream_Proxy proto _CType \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	       grfMode: DWORD,
	     reserved1: DWORD,
	     reserved2: DWORD,
		 ppstm: ptr IStream


;void
IStorage_CreateStream_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_RemoteOpenStream_Proxy proto _CType \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	   cbReserved1: DWORD,
	     reserved1: LPBYTE,
	       grfMode: DWORD,
	     reserved2: DWORD,
		 ppstm: ptr IStream


;void
IStorage_RemoteOpenStream_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_CreateStorage_Proxy proto _CType \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	       grfMode: DWORD,
	     reserved1: DWORD,
	     reserved2: DWORD,
		 ppstg: ptr IStorage


;void
IStorage_CreateStorage_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_OpenStorage_Proxy proto _CType \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	  pstgPriority: ptr IStorage,
	       grfMode: DWORD,
	    snbExclude: SNB,
	      reserved: DWORD,
		 ppstg: ptr IStorage


;void
IStorage_OpenStorage_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_CopyTo_Proxy proto _CType \
		 pThis: ptr IStorage,
	   ciidExclude: DWORD,
	  rgiidExclude: ptr IID,
	    snbExclude: SNB,
	      pstgDest: ptr IStorage


;void
IStorage_CopyTo_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_MoveElementTo_Proxy proto _CType \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	      pstgDest: ptr IStorage,
	   pwcsNewName: ptr OLECHAR,
	      grfFlags: DWORD


;void
IStorage_MoveElementTo_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_Commit_Proxy proto _CType \
		 pThis: ptr IStorage,
	grfCommitFlags: DWORD


;void
IStorage_Commit_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_Revert_Proxy proto _CType \
		 pThis: ptr IStorage


;void
IStorage_Revert_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_RemoteEnumElements_Proxy proto _CType \
		 pThis: ptr IStorage,
	     reserved1: DWORD,
	   cbReserved2: DWORD,
	     reserved2: LPBYTE,
	     reserved3: DWORD,
		ppenum: ptr IEnumSTATSTG


;void
IStorage_RemoteEnumElements_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_DestroyElement_Proxy proto _CType \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR


;void
IStorage_DestroyElement_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_RenameElement_Proxy proto _CType \
		 pThis: ptr IStorage,
	   pwcsOldName: ptr OLECHAR,
	   pwcsNewName: ptr OLECHAR


;void
IStorage_RenameElement_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_SetElementTimes_Proxy proto _CType \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
		pctime: LPFILETIME,
		patime: LPFILETIME,
		pmtime: LPFILETIME


;void
IStorage_SetElementTimes_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_SetClass_Proxy proto _CType \
		 pThis: ptr IStorage,
		 clsid: REFCLSID


;void
IStorage_SetClass_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_SetStateBits_Proxy proto _CType \
		 pThis: ptr IStorage,
	  grfStateBits: DWORD,
	       grfMask: DWORD


;void
IStorage_SetStateBits_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IStorage_Stat_Proxy proto _CType \
		 pThis: ptr IStorage,
	      pstatstg: ptr STATSTG,
	   grfStatFlag: DWORD


;void
IStorage_Stat_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IStorage_INTERFACE_DEFINED__


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

IPersistFileVtbl@Load@CT typedef proto \
		 pThis: ptr IPersistFile,
	   pszFileName: LPCOLESTR,
		dwMode: DWORD
IPersistFileVtbl@Load@MP typedef ptr IPersistFileVtbl@Load@CT
		   Load IPersistFileVtbl@Load@MP ?

	       Save3@CT typedef proto \
		 pThis: ptr IPersistFile,
	   pszFileName: LPCOLESTR,
	     fRemember: BOOL
	       Save3@MP typedef ptr Save3@CT
		   Save Save3@MP ?

       SaveCompleted@CT typedef proto \
		 pThis: ptr IPersistFile,
	   pszFileName: LPCOLESTR
       SaveCompleted@MP typedef ptr SaveCompleted@CT
	  SaveCompleted SaveCompleted@MP ?

	  GetCurFile@CT typedef proto \
		 pThis: ptr IPersistFile,
	  ppszFileName: ptr LPOLESTR
	  GetCurFile@MP typedef ptr GetCurFile@CT
	     GetCurFile GetCurFile@MP ?

	END_INTERFACE

IPersistFileVtbl	ENDS

LPIPersistFileVtbl	typedef ptr IPersistFileVtbl
IPersistFile		STRUC
lpVtbl			LPIPersistFileVtbl ?
IPersistFile		ENDS



;HRESULT
IPersistFile_IsDirty_Proxy proto _CType \
		 pThis: ptr IPersistFile


;void
IPersistFile_IsDirty_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistFile_Load_Proxy proto _CType \
		 pThis: ptr IPersistFile,
	   pszFileName: LPCOLESTR,
		dwMode: DWORD


;void
IPersistFile_Load_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistFile_Save_Proxy proto _CType \
		 pThis: ptr IPersistFile,
	   pszFileName: LPCOLESTR,
	     fRemember: BOOL


;void
IPersistFile_Save_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistFile_SaveCompleted_Proxy proto _CType \
		 pThis: ptr IPersistFile,
	   pszFileName: LPCOLESTR


;void
IPersistFile_SaveCompleted_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistFile_GetCurFile_Proxy proto _CType \
		 pThis: ptr IPersistFile,
	  ppszFileName: ptr LPOLESTR


;void
IPersistFile_GetCurFile_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IPersistFile_INTERFACE_DEFINED__


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

	     InitNew@CT typedef proto \
		 pThis: ptr IPersistStorage,
		  pStg: ptr IStorage
	     InitNew@MP typedef ptr InitNew@CT
		InitNew InitNew@MP ?

IPersistStorageVtbl@Load@CT typedef proto \
		 pThis: ptr IPersistStorage,
		  pStg: ptr IStorage
IPersistStorageVtbl@Load@MP typedef ptr IPersistStorageVtbl@Load@CT
		   Load IPersistStorageVtbl@Load@MP ?

	       Save4@CT typedef proto \
		 pThis: ptr IPersistStorage,
	      pStgSave: ptr IStorage,
	   fSameAsLoad: BOOL
	       Save4@MP typedef ptr Save4@CT
		   Save Save4@MP ?

      SaveCompleted2@CT typedef proto \
		 pThis: ptr IPersistStorage,
	       pStgNew: ptr IStorage
      SaveCompleted2@MP typedef ptr SaveCompleted2@CT
	  SaveCompleted SaveCompleted2@MP ?

     HandsOffStorage@CT typedef proto \
		 pThis: ptr IPersistStorage
     HandsOffStorage@MP typedef ptr HandsOffStorage@CT
	HandsOffStorage HandsOffStorage@MP ?

	END_INTERFACE

IPersistStorageVtbl	ENDS

LPIPersistStorageVtbl	typedef ptr IPersistStorageVtbl
IPersistStorage		STRUC
lpVtbl			LPIPersistStorageVtbl ?
IPersistStorage		ENDS



;HRESULT
IPersistStorage_IsDirty_Proxy proto _CType \
		 pThis: ptr IPersistStorage


;void
IPersistStorage_IsDirty_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistStorage_InitNew_Proxy proto _CType \
		 pThis: ptr IPersistStorage,
		  pStg: ptr IStorage


;void
IPersistStorage_InitNew_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistStorage_Load_Proxy proto _CType \
		 pThis: ptr IPersistStorage,
		  pStg: ptr IStorage


;void
IPersistStorage_Load_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistStorage_Save_Proxy proto _CType \
		 pThis: ptr IPersistStorage,
	      pStgSave: ptr IStorage,
	   fSameAsLoad: BOOL


;void
IPersistStorage_Save_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistStorage_SaveCompleted_Proxy proto _CType \
		 pThis: ptr IPersistStorage,
	       pStgNew: ptr IStorage


;void
IPersistStorage_SaveCompleted_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPersistStorage_HandsOffStorage_Proxy proto _CType \
		 pThis: ptr IPersistStorage


;void
IPersistStorage_HandsOffStorage_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IPersistStorage_INTERFACE_DEFINED__


ifndef __ILockBytes_INTERFACE_DEFINED__
__ILockBytes_INTERFACE_DEFINED__ equ 1



LPLOCKBYTES		typedef ptr ILockBytes


externdef		IID_ILockBytes:IID

ILockBytesVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	      ReadAt@CT typedef proto \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: PVOID,
		    cb: ULONG,
	       pcbRead: LPDWORD
	      ReadAt@MP typedef ptr ReadAt@CT
		 ReadAt ReadAt@MP ?

	     WriteAt@CT typedef proto \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD
	     WriteAt@MP typedef ptr WriteAt@CT
		WriteAt WriteAt@MP ?

	       Flush@CT typedef proto \
		 pThis: ptr ILockBytes
	       Flush@MP typedef ptr Flush@CT
		  Flush Flush@MP ?

	    SetSize2@CT typedef proto \
		 pThis: ptr ILockBytes,
		    cb: ULARGE_INTEGER
	    SetSize2@MP typedef ptr SetSize2@CT
		SetSize SetSize2@MP ?

	 LockRegion2@CT typedef proto \
		 pThis: ptr ILockBytes,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD
	 LockRegion2@MP typedef ptr LockRegion2@CT
	     LockRegion LockRegion2@MP ?

       UnlockRegion2@CT typedef proto \
		 pThis: ptr ILockBytes,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD
       UnlockRegion2@MP typedef ptr UnlockRegion2@CT
	   UnlockRegion UnlockRegion2@MP ?

	       Stat2@CT typedef proto \
		 pThis: ptr ILockBytes,
	      pstatstg: ptr STATSTG,
	   grfStatFlag: DWORD
	       Stat2@MP typedef ptr Stat2@CT
		   Stat Stat2@MP ?

	END_INTERFACE

ILockBytesVtbl		ENDS

LPILockBytesVtbl	typedef ptr ILockBytesVtbl
ILockBytes		STRUC
lpVtbl			LPILockBytesVtbl ?
ILockBytes		ENDS


;HRESULT
ILockBytes_RemoteReadAt_Proxy proto _CType \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	       pcbRead: LPDWORD


;void
ILockBytes_RemoteReadAt_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ILockBytes_RemoteWriteAt_Proxy proto _CType \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;void
ILockBytes_RemoteWriteAt_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ILockBytes_Flush_Proxy proto _CType \
		 pThis: ptr ILockBytes


;void
ILockBytes_Flush_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ILockBytes_SetSize_Proxy proto _CType \
		 pThis: ptr ILockBytes,
		    cb: ULARGE_INTEGER


;void
ILockBytes_SetSize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ILockBytes_LockRegion_Proxy proto _CType \
		 pThis: ptr ILockBytes,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD


;void
ILockBytes_LockRegion_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ILockBytes_UnlockRegion_Proxy proto _CType \
		 pThis: ptr ILockBytes,
	     libOffset: ULARGE_INTEGER,
		    cb: ULARGE_INTEGER,
	    dwLockType: DWORD


;void
ILockBytes_UnlockRegion_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ILockBytes_Stat_Proxy proto _CType \
		 pThis: ptr ILockBytes,
	      pstatstg: ptr STATSTG,
	   grfStatFlag: DWORD


;void
ILockBytes_Stat_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __ILockBytes_INTERFACE_DEFINED__


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
IEnumFORMATETC_RemoteNext_Proxy proto _CType \
		 pThis: ptr IEnumFORMATETC,
		  celt: ULONG,
		 rgelt: ptr FORMATETC,
	  pceltFetched: LPDWORD


;void
IEnumFORMATETC_RemoteNext_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumFORMATETC_Skip_Proxy proto _CType \
		 pThis: ptr IEnumFORMATETC,
		  celt: ULONG


;void
IEnumFORMATETC_Skip_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumFORMATETC_Reset_Proxy proto _CType \
		 pThis: ptr IEnumFORMATETC


;void
IEnumFORMATETC_Reset_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumFORMATETC_Clone_Proxy proto _CType \
		 pThis: ptr IEnumFORMATETC,
		ppenum: ptr IEnumFORMATETC


;void
IEnumFORMATETC_Clone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IEnumFORMATETC_INTERFACE_DEFINED__


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
IEnumSTATDATA_RemoteNext_Proxy proto _CType \
		 pThis: ptr IEnumSTATDATA,
		  celt: ULONG,
		 rgelt: ptr STATDATA,
	  pceltFetched: LPDWORD


;void
IEnumSTATDATA_RemoteNext_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATDATA_Skip_Proxy proto _CType \
		 pThis: ptr IEnumSTATDATA,
		  celt: ULONG


;void
IEnumSTATDATA_Skip_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATDATA_Reset_Proxy proto _CType \
		 pThis: ptr IEnumSTATDATA


;void
IEnumSTATDATA_Reset_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATDATA_Clone_Proxy proto _CType \
		 pThis: ptr IEnumSTATDATA,
		ppenum: ptr IEnumSTATDATA


;void
IEnumSTATDATA_Clone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IEnumSTATDATA_INTERFACE_DEFINED__


ifndef __IRootStorage_INTERFACE_DEFINED__
__IRootStorage_INTERFACE_DEFINED__ equ 1



LPROOTSTORAGE		typedef ptr IRootStorage


externdef		IID_IRootStorage:IID


IRootStorageVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	SwitchToFile@CT typedef proto \
		 pThis: ptr IRootStorage,
	       pszFile: LPOLESTR
	SwitchToFile@MP typedef ptr SwitchToFile@CT
	   SwitchToFile SwitchToFile@MP ?

	END_INTERFACE

IRootStorageVtbl	ENDS

LPIRootStorageVtbl	typedef ptr IRootStorageVtbl
IRootStorage		STRUC
lpVtbl			LPIRootStorageVtbl ?
IRootStorage		ENDS



;HRESULT
IRootStorage_SwitchToFile_Proxy proto _CType \
		 pThis: ptr IRootStorage,
	       pszFile: LPOLESTR


;void
IRootStorage_SwitchToFile_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IRootStorage_INTERFACE_DEFINED__


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
endif ;; NOT NONAMELESSUNION

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

	OnDataChange@CT typedef proto \
		 pThis: ptr IAdviseSink,
	    pFormatetc: ptr FORMATETC,
	       pStgmed: ptr STGMEDIUM
	OnDataChange@MP typedef ptr OnDataChange@CT
	   OnDataChange OnDataChange@MP ?

	OnViewChange@CT typedef proto \
		 pThis: ptr IAdviseSink,
	      dwAspect: DWORD,
		lindex: LONG
	OnViewChange@MP typedef ptr OnViewChange@CT
	   OnViewChange OnViewChange@MP ?

	    OnRename@CT typedef proto \
		 pThis: ptr IAdviseSink,
		   pmk: ptr IMoniker
	    OnRename@MP typedef ptr OnRename@CT
	       OnRename OnRename@MP ?

	      OnSave@CT typedef proto \
		 pThis: ptr IAdviseSink
	      OnSave@MP typedef ptr OnSave@CT
		 OnSave OnSave@MP ?

	     OnClose@CT typedef proto \
		 pThis: ptr IAdviseSink
	     OnClose@MP typedef ptr OnClose@CT
		OnClose OnClose@MP ?

	END_INTERFACE

IAdviseSinkVtbl		ENDS

LPIAdviseSinkVtbl	typedef ptr IAdviseSinkVtbl
IAdviseSink		STRUC
lpVtbl			LPIAdviseSinkVtbl ?
IAdviseSink		ENDS


;HRESULT
IAdviseSink_RemoteOnDataChange_Proxy proto _CType \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
	    pFormatetc: ptr FORMATETC,
	       pStgmed: ptr ASYNC_STGMEDIUM


;void
IAdviseSink_RemoteOnDataChange_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IAdviseSink_RemoteOnViewChange_Proxy proto _CType \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
	      dwAspect: DWORD,
		lindex: LONG


;void
IAdviseSink_RemoteOnViewChange_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IAdviseSink_RemoteOnRename_Proxy proto _CType \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
		   pmk: ptr IMoniker


;void
IAdviseSink_RemoteOnRename_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IAdviseSink_RemoteOnSave_Proxy proto _CType \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager


;void
IAdviseSink_RemoteOnSave_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IAdviseSink_RemoteOnClose_Proxy proto _CType \
		 pThis: ptr IAdviseSink


;void
IAdviseSink_RemoteOnClose_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IAdviseSink_INTERFACE_DEFINED__


ifndef __IAdviseSink2_INTERFACE_DEFINED__
__IAdviseSink2_INTERFACE_DEFINED__ equ 1



LPADVISESINK2		typedef ptr IAdviseSink2


externdef		IID_IAdviseSink2:IID

IAdviseSink2Vtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

       OnDataChange2@CT typedef proto \
		 pThis: ptr IAdviseSink2,
	    pFormatetc: ptr FORMATETC,
	       pStgmed: ptr STGMEDIUM
       OnDataChange2@MP typedef ptr OnDataChange2@CT
	   OnDataChange OnDataChange2@MP ?

       OnViewChange2@CT typedef proto \
		 pThis: ptr IAdviseSink2,
	      dwAspect: DWORD,
		lindex: LONG
       OnViewChange2@MP typedef ptr OnViewChange2@CT
	   OnViewChange OnViewChange2@MP ?

	   OnRename2@CT typedef proto \
		 pThis: ptr IAdviseSink2,
		   pmk: ptr IMoniker
	   OnRename2@MP typedef ptr OnRename2@CT
	       OnRename OnRename2@MP ?

	     OnSave2@CT typedef proto \
		 pThis: ptr IAdviseSink2
	     OnSave2@MP typedef ptr OnSave2@CT
		 OnSave OnSave2@MP ?

	    OnClose2@CT typedef proto \
		 pThis: ptr IAdviseSink2
	    OnClose2@MP typedef ptr OnClose2@CT
		OnClose OnClose2@MP ?

     OnLinkSrcChange@CT typedef proto \
		 pThis: ptr IAdviseSink2,
		   pmk: ptr IMoniker
     OnLinkSrcChange@MP typedef ptr OnLinkSrcChange@CT
	OnLinkSrcChange OnLinkSrcChange@MP ?

	END_INTERFACE

IAdviseSink2Vtbl	ENDS

LPIAdviseSink2Vtbl	typedef ptr IAdviseSink2Vtbl
IAdviseSink2		STRUC
lpVtbl			LPIAdviseSink2Vtbl ?
IAdviseSink2		ENDS



;HRESULT
IAdviseSink2_RemoteOnLinkSrcChange_Proxy proto _CType \
		 pThis: ptr IAdviseSink2,
		 ppIAM: ptr IAsyncManager,
		   pmk: ptr IMoniker


;void
IAdviseSink2_RemoteOnLinkSrcChange_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IAdviseSink2_INTERFACE_DEFINED__


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

	     GetData@CT typedef proto \
		 pThis: ptr IDataObject,
	  pformatetcIn: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM
	     GetData@MP typedef ptr GetData@CT
		GetData GetData@MP ?

	 GetDataHere@CT typedef proto \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM
	 GetDataHere@MP typedef ptr GetDataHere@CT
	    GetDataHere GetDataHere@MP ?

	QueryGetData@CT typedef proto \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC
	QueryGetData@MP typedef ptr QueryGetData@CT
	   QueryGetData QueryGetData@MP ?

GetCanonicalFormatEtc@CT typedef proto \
		 pThis: ptr IDataObject,
	  pformatectIn: ptr FORMATETC,
	 pformatetcOut: ptr FORMATETC
GetCanonicalFormatEtc@MP typedef ptr GetCanonicalFormatEtc@CT
  GetCanonicalFormatEtc GetCanonicalFormatEtc@MP ?

	     SetData@CT typedef proto \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM,
	      fRelease: BOOL
	     SetData@MP typedef ptr SetData@CT
		SetData SetData@MP ?

       EnumFormatEtc@CT typedef proto \
		 pThis: ptr IDataObject,
	   dwDirection: DWORD,
       ppenumFormatEtc: ptr IEnumFORMATETC
       EnumFormatEtc@MP typedef ptr EnumFormatEtc@CT
	  EnumFormatEtc EnumFormatEtc@MP ?

	     DAdvise@CT typedef proto \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
		  advf: DWORD,
	      pAdvSink: ptr IAdviseSink,
	 pdwConnection: LPDWORD
	     DAdvise@MP typedef ptr DAdvise@CT
		DAdvise DAdvise@MP ?

	   DUnadvise@CT typedef proto \
		 pThis: ptr IDataObject,
	  dwConnection: DWORD
	   DUnadvise@MP typedef ptr DUnadvise@CT
	      DUnadvise DUnadvise@MP ?

	 EnumDAdvise@CT typedef proto \
		 pThis: ptr IDataObject,
	  ppenumAdvise: ptr IEnumSTATDATA
	 EnumDAdvise@MP typedef ptr EnumDAdvise@CT
	    EnumDAdvise EnumDAdvise@MP ?

	END_INTERFACE

IDataObjectVtbl		ENDS

LPIDataObjectVtbl	typedef ptr IDataObjectVtbl
IDataObject		STRUC
lpVtbl			LPIDataObjectVtbl ?
IDataObject		ENDS




;HRESULT
IDataObject_RemoteGetData_Proxy proto _CType \
		 pThis: ptr IDataObject,
	  pformatetcIn: ptr FORMATETC,
	 pRemoteMedium: ptr STGMEDIUM


;void
IDataObject_RemoteGetData_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDataObject_RemoteGetDataHere_Proxy proto _CType \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	 pRemoteMedium: ptr STGMEDIUM


;void
IDataObject_RemoteGetDataHere_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDataObject_QueryGetData_Proxy proto _CType \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC


;void
IDataObject_QueryGetData_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDataObject_GetCanonicalFormatEtc_Proxy proto _CType \
		 pThis: ptr IDataObject,
	  pformatectIn: ptr FORMATETC,
	 pformatetcOut: ptr FORMATETC


;void
IDataObject_GetCanonicalFormatEtc_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDataObject_RemoteSetData_Proxy proto _CType \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr FLAG_STGMEDIUM,
	      fRelease: BOOL


;void
IDataObject_RemoteSetData_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDataObject_EnumFormatEtc_Proxy proto _CType \
		 pThis: ptr IDataObject,
	   dwDirection: DWORD,
       ppenumFormatEtc: ptr IEnumFORMATETC


;void
IDataObject_EnumFormatEtc_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDataObject_DAdvise_Proxy proto _CType \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
		  advf: DWORD,
	      pAdvSink: ptr IAdviseSink,
	 pdwConnection: LPDWORD


;void
IDataObject_DAdvise_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDataObject_DUnadvise_Proxy proto _CType \
		 pThis: ptr IDataObject,
	  dwConnection: DWORD


;void
IDataObject_DUnadvise_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDataObject_EnumDAdvise_Proxy proto _CType \
		 pThis: ptr IDataObject,
	  ppenumAdvise: ptr IEnumSTATDATA


;void
IDataObject_EnumDAdvise_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IDataObject_INTERFACE_DEFINED__


ifndef __IDataAdviseHolder_INTERFACE_DEFINED__
__IDataAdviseHolder_INTERFACE_DEFINED__ equ 1

LPDATAADVISEHOLDER	typedef ptr IDataAdviseHolder


externdef		IID_IDataAdviseHolder:IID

IDataAdviseHolderVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	      Advise@CT typedef proto \
		 pThis: ptr IDataAdviseHolder,
	   pDataObject: ptr IDataObject,
		 pFetc: ptr FORMATETC,
		  advf: DWORD,
	       pAdvise: ptr IAdviseSink,
	 pdwConnection: LPDWORD
	      Advise@MP typedef ptr Advise@CT
		 Advise Advise@MP ?

	    Unadvise@CT typedef proto \
		 pThis: ptr IDataAdviseHolder,
	  dwConnection: DWORD
	    Unadvise@MP typedef ptr Unadvise@CT
	       Unadvise Unadvise@MP ?

	  EnumAdvise@CT typedef proto \
		 pThis: ptr IDataAdviseHolder,
	  ppenumAdvise: ptr IEnumSTATDATA
	  EnumAdvise@MP typedef ptr EnumAdvise@CT
	     EnumAdvise EnumAdvise@MP ?

    SendOnDataChange@CT typedef proto \
		 pThis: ptr IDataAdviseHolder,
	   pDataObject: ptr IDataObject,
	    dwReserved: DWORD,
		  advf: DWORD
    SendOnDataChange@MP typedef ptr SendOnDataChange@CT
       SendOnDataChange SendOnDataChange@MP ?

	END_INTERFACE

IDataAdviseHolderVtbl	ENDS

LPIDataAdviseHolderVtbl typedef ptr IDataAdviseHolderVtbl
IDataAdviseHolder	STRUC
lpVtbl			LPIDataAdviseHolderVtbl ?
IDataAdviseHolder	ENDS


;HRESULT
IDataAdviseHolder_Advise_Proxy proto _CType \
		 pThis: ptr IDataAdviseHolder,
	   pDataObject: ptr IDataObject,
		 pFetc: ptr FORMATETC,
		  advf: DWORD,
	       pAdvise: ptr IAdviseSink,
	 pdwConnection: LPDWORD


;void
IDataAdviseHolder_Advise_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDataAdviseHolder_Unadvise_Proxy proto _CType \
		 pThis: ptr IDataAdviseHolder,
	  dwConnection: DWORD


;void
IDataAdviseHolder_Unadvise_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDataAdviseHolder_EnumAdvise_Proxy proto _CType \
		 pThis: ptr IDataAdviseHolder,
	  ppenumAdvise: ptr IEnumSTATDATA


;void
IDataAdviseHolder_EnumAdvise_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDataAdviseHolder_SendOnDataChange_Proxy proto _CType \
		 pThis: ptr IDataAdviseHolder,
	   pDataObject: ptr IDataObject,
	    dwReserved: DWORD,
		  advf: DWORD


;void
IDataAdviseHolder_SendOnDataChange_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IDataAdviseHolder_INTERFACE_DEFINED__


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

  HandleInComingCall@CT typedef proto \
		 pThis: ptr IMessageFilter,
	    dwCallType: DWORD,
	   htaskCaller: HTASK,
	   dwTickCount: DWORD,
       lpInterfaceInfo: LPINTERFACEINFO
  HandleInComingCall@MP typedef ptr HandleInComingCall@CT
     HandleInComingCall HandleInComingCall@MP ?

   RetryRejectedCall@CT typedef proto \
		 pThis: ptr IMessageFilter,
	   htaskCallee: HTASK,
	   dwTickCount: DWORD,
	  dwRejectType: DWORD
   RetryRejectedCall@MP typedef ptr RetryRejectedCall@CT
      RetryRejectedCall RetryRejectedCall@MP ?

      MessagePending@CT typedef proto \
		 pThis: ptr IMessageFilter,
	   htaskCallee: HTASK,
	   dwTickCount: DWORD,
	 dwPendingType: DWORD
      MessagePending@MP typedef ptr MessagePending@CT
	 MessagePending MessagePending@MP ?

	END_INTERFACE

IMessageFilterVtbl	ENDS

LPIMessageFilterVtbl	typedef ptr IMessageFilterVtbl
IMessageFilter		STRUC
lpVtbl			LPIMessageFilterVtbl ?
IMessageFilter		ENDS


;DWORD
IMessageFilter_HandleInComingCall_Proxy proto _CType \
		 pThis: ptr IMessageFilter,
	    dwCallType: DWORD,
	   htaskCaller: HTASK,
	   dwTickCount: DWORD,
       lpInterfaceInfo: LPINTERFACEINFO


;void
IMessageFilter_HandleInComingCall_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;DWORD
IMessageFilter_RetryRejectedCall_Proxy proto _CType \
		 pThis: ptr IMessageFilter,
	   htaskCallee: HTASK,
	   dwTickCount: DWORD,
	  dwRejectType: DWORD


;void
IMessageFilter_RetryRejectedCall_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;DWORD
IMessageFilter_MessagePending_Proxy proto _CType \
		 pThis: ptr IMessageFilter,
	   htaskCallee: HTASK,
	   dwTickCount: DWORD,
	 dwPendingType: DWORD


;void
IMessageFilter_MessagePending_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IMessageFilter_INTERFACE_DEFINED__


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

	   GetBuffer@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer,
	      pMessage: ptr RPCOLEMESSAGE,
		  riid: REFIID
	   GetBuffer@MP typedef ptr GetBuffer@CT
	      GetBuffer GetBuffer@MP ?

	 SendReceive@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer,
	      pMessage: ptr RPCOLEMESSAGE,
	       pStatus: LPDWORD
	 SendReceive@MP typedef ptr SendReceive@CT
	    SendReceive SendReceive@MP ?

	  FreeBuffer@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer,
	      pMessage: ptr RPCOLEMESSAGE
	  FreeBuffer@MP typedef ptr FreeBuffer@CT
	     FreeBuffer FreeBuffer@MP ?

	  GetDestCtx@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer,
	pdwDestContext: LPDWORD,
	ppvDestContext: PVOID
	  GetDestCtx@MP typedef ptr GetDestCtx@CT
	     GetDestCtx GetDestCtx@MP ?

	 IsConnected@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer
	 IsConnected@MP typedef ptr IsConnected@CT
	    IsConnected IsConnected@MP ?

	END_INTERFACE

IRpcChannelBufferVtbl	ENDS

LPIRpcChannelBufferVtbl typedef ptr IRpcChannelBufferVtbl
IRpcChannelBuffer	STRUC
lpVtbl			LPIRpcChannelBufferVtbl ?
IRpcChannelBuffer	ENDS


;HRESULT
IRpcChannelBuffer_GetBuffer_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer,
	      pMessage: ptr RPCOLEMESSAGE,
		  riid: REFIID


;void
IRpcChannelBuffer_GetBuffer_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcChannelBuffer_SendReceive_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer,
	      pMessage: ptr RPCOLEMESSAGE,
	       pStatus: LPDWORD


;void
IRpcChannelBuffer_SendReceive_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcChannelBuffer_FreeBuffer_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer,
	      pMessage: ptr RPCOLEMESSAGE


;void
IRpcChannelBuffer_FreeBuffer_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcChannelBuffer_GetDestCtx_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer,
	pdwDestContext: LPDWORD,
	ppvDestContext: PVOID


;void
IRpcChannelBuffer_GetDestCtx_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcChannelBuffer_IsConnected_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer


;void
IRpcChannelBuffer_IsConnected_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IRpcChannelBuffer_INTERFACE_DEFINED__


ifndef __IRpcChannelBuffer2_INTERFACE_DEFINED__
__IRpcChannelBuffer2_INTERFACE_DEFINED__ equ 1




externdef		IID_IRpcChannelBuffer2:IID

IRpcChannelBuffer2Vtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	  GetBuffer2@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer2,
	      pMessage: ptr RPCOLEMESSAGE,
		  riid: REFIID
	  GetBuffer2@MP typedef ptr GetBuffer2@CT
	      GetBuffer GetBuffer2@MP ?

	SendReceive2@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer2,
	      pMessage: ptr RPCOLEMESSAGE,
	       pStatus: LPDWORD
	SendReceive2@MP typedef ptr SendReceive2@CT
	    SendReceive SendReceive2@MP ?

	 FreeBuffer2@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer2,
	      pMessage: ptr RPCOLEMESSAGE
	 FreeBuffer2@MP typedef ptr FreeBuffer2@CT
	     FreeBuffer FreeBuffer2@MP ?

	 GetDestCtx2@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer2,
	pdwDestContext: LPDWORD,
	ppvDestContext: PVOID
	 GetDestCtx2@MP typedef ptr GetDestCtx2@CT
	     GetDestCtx GetDestCtx2@MP ?

	IsConnected2@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer2
	IsConnected2@MP typedef ptr IsConnected2@CT
	    IsConnected IsConnected2@MP ?

  GetProtocolVersion@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer2,
	    pdwVersion: LPDWORD
  GetProtocolVersion@MP typedef ptr GetProtocolVersion@CT
     GetProtocolVersion GetProtocolVersion@MP ?

	END_INTERFACE

IRpcChannelBuffer2Vtbl	ENDS

LPIRpcChannelBuffer2Vtbl typedef ptr IRpcChannelBuffer2Vtbl
IRpcChannelBuffer2	STRUC
lpVtbl			LPIRpcChannelBuffer2Vtbl ?
IRpcChannelBuffer2	ENDS

;HRESULT
IRpcChannelBuffer2_GetProtocolVersion_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer2,
	    pdwVersion: LPDWORD


;void
IRpcChannelBuffer2_GetProtocolVersion_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IRpcChannelBuffer2_INTERFACE_DEFINED__


ifndef __IRpcChannelBuffer3_INTERFACE_DEFINED__
__IRpcChannelBuffer3_INTERFACE_DEFINED__ equ 1




externdef		IID_IRpcChannelBuffer3:IID

IRpcChannelBuffer3Vtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	  GetBuffer3@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
	      pMessage: ptr RPCOLEMESSAGE,
		  riid: REFIID
	  GetBuffer3@MP typedef ptr GetBuffer3@CT
	      GetBuffer GetBuffer3@MP ?

	SendReceive@3CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
	      pMessage: ptr RPCOLEMESSAGE,
	       pStatus: LPDWORD
	SendReceive3@MP typedef ptr SendReceive3@CT
	    SendReceive SendReceive3@MP ?

	 FreeBuffer3@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
	      pMessage: ptr RPCOLEMESSAGE
	 FreeBuffer3@MP typedef ptr FreeBuffer3@CT
	     FreeBuffer FreeBuffer3@MP ?

	 GetDestCtx3@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
	pdwDestContext: LPDWORD,
	ppvDestContext: PVOID
	 GetDestCtx3@MP typedef ptr GetDestCtx3@CT
	     GetDestCtx GetDestCtx3@MP ?

	IsConnected3@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3
	IsConnected3@MP typedef ptr IsConnected3@CT
	    IsConnected IsConnected3@MP ?

 GetProtocolVersion3@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
	    pdwVersion: LPDWORD
 GetProtocolVersion3@MP typedef ptr GetProtocolVersion3@CT
     GetProtocolVersion GetProtocolVersion3@MP ?

		Send@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
	     pulStatus: LPDWORD
		Send@MP typedef ptr Send@CT
		   Send Send@MP ?

	     Receive@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
		ulSize: ULONG,
	     pulStatus: LPDWORD
	     Receive@MP typedef ptr Receive@CT
		Receive Receive@MP ?

	      Cancel@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE
	      Cancel@MP typedef ptr Cancel@CT
		 Cancel Cancel@MP ?

      GetCallContext@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
		  riid: REFIID,
	    pInterface: PVOID
      GetCallContext@MP typedef ptr GetCallContext@CT
	 GetCallContext GetCallContext@MP ?

	GetDestCtxEx@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
	pdwDestContext: LPDWORD,
	ppvDestContext: PVOID
	GetDestCtxEx@MP typedef ptr GetDestCtxEx@CT
	   GetDestCtxEx GetDestCtxEx@MP ?

	    GetState@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
		pState: LPDWORD
	    GetState@MP typedef ptr GetState@CT
	       GetState GetState@MP ?

       RegisterAsync@CT typedef proto \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
	     pAsyncMgr: ptr IAsyncManager
       RegisterAsync@MP typedef ptr RegisterAsync@CT
	  RegisterAsync RegisterAsync@MP ?

	END_INTERFACE

IRpcChannelBuffer3Vtbl	ENDS

LPIRpcChannelBuffer3Vtbl typedef ptr IRpcChannelBuffer3Vtbl
IRpcChannelBuffer3	STRUC
lpVtbl			LPIRpcChannelBuffer3Vtbl ?
IRpcChannelBuffer3	ENDS



;HRESULT
IRpcChannelBuffer3_Send_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
	     pulStatus: LPDWORD


;void
IRpcChannelBuffer3_Send_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcChannelBuffer3_Receive_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
		ulSize: ULONG,
	     pulStatus: LPDWORD


;void
IRpcChannelBuffer3_Receive_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcChannelBuffer3_Cancel_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE


;void
IRpcChannelBuffer3_Cancel_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcChannelBuffer3_GetCallContext_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
		  riid: REFIID,
	    pInterface: PVOID


;void
IRpcChannelBuffer3_GetCallContext_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcChannelBuffer3_GetDestCtxEx_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
	pdwDestContext: LPDWORD,
	ppvDestContext: PVOID


;void
IRpcChannelBuffer3_GetDestCtxEx_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcChannelBuffer3_GetState_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
		pState: LPDWORD


;void
IRpcChannelBuffer3_GetState_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcChannelBuffer3_RegisterAsync_Proxy proto _CType \
		 pThis: ptr IRpcChannelBuffer3,
		  pMsg: ptr RPCOLEMESSAGE,
	     pAsyncMgr: ptr IAsyncManager


;void
IRpcChannelBuffer3_RegisterAsync_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IRpcChannelBuffer3_INTERFACE_DEFINED__


ifndef __IRpcProxyBuffer_INTERFACE_DEFINED__
__IRpcProxyBuffer_INTERFACE_DEFINED__ equ 1




externdef		IID_IRpcProxyBuffer:IID

IRpcProxyBufferVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	     Connect@CT typedef proto \
		 pThis: ptr IRpcProxyBuffer,
     pRpcChannelBuffer: ptr IRpcChannelBuffer
	     Connect@MP typedef ptr Connect@CT
		Connect Connect@MP ?

	  Disconnect@CT typedef proto \
		 pThis: ptr IRpcProxyBuffer
	  Disconnect@MP typedef ptr Disconnect@CT
	     Disconnect Disconnect@MP ?

	END_INTERFACE

IRpcProxyBufferVtbl	ENDS

LPIRpcProxyBufferVtbl	typedef ptr IRpcProxyBufferVtbl
IRpcProxyBuffer		STRUC
lpVtbl			LPIRpcProxyBufferVtbl ?
IRpcProxyBuffer		ENDS


;HRESULT
IRpcProxyBuffer_Connect_Proxy proto _CType \
		 pThis: ptr IRpcProxyBuffer,
     pRpcChannelBuffer: ptr IRpcChannelBuffer


;void
IRpcProxyBuffer_Connect_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IRpcProxyBuffer_Disconnect_Proxy proto _CType \
		 pThis: ptr IRpcProxyBuffer


;void
IRpcProxyBuffer_Disconnect_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IRpcProxyBuffer_INTERFACE_DEFINED__


ifndef __IRpcStubBuffer_INTERFACE_DEFINED__
__IRpcStubBuffer_INTERFACE_DEFINED__ equ 1




externdef		IID_IRpcStubBuffer:IID

IRpcStubBufferVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	    Connect2@CT typedef proto \
		 pThis: ptr IRpcStubBuffer,
	    pUnkServer: ptr IUnknown
	    Connect2@MP typedef ptr Connect2@CT
		Connect Connect2@MP ?

	 Disconnect2@CT typedef proto \
		 pThis: ptr IRpcStubBuffer
	 Disconnect2@MP typedef ptr Disconnect2@CT
	     Disconnect Disconnect2@MP ?

	     _Invoke@CT typedef proto \
		 pThis: ptr IRpcStubBuffer,
	      _prpcmsg: ptr RPCOLEMESSAGE,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer
	     _Invoke@MP typedef ptr _Invoke@CT
		_Invoke _Invoke@MP ?

      IsIIDSupported@CT typedef proto \
		 pThis: ptr IRpcStubBuffer,
		  riid: REFIID
      IsIIDSupported@MP typedef ptr IsIIDSupported@CT
	 IsIIDSupported IsIIDSupported@MP ?

	   CountRefs@CT typedef proto \
		 pThis: ptr IRpcStubBuffer
	   CountRefs@MP typedef ptr CountRefs@CT
	      CountRefs CountRefs@MP ?

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
IRpcStubBuffer_Connect_Proxy proto _CType \
		 pThis: ptr IRpcStubBuffer,
	    pUnkServer: ptr IUnknown


;void
IRpcStubBuffer_Connect_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IRpcStubBuffer_Disconnect_Proxy proto _CType \
		 pThis: ptr IRpcStubBuffer


;void
IRpcStubBuffer_Disconnect_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcStubBuffer_Invoke_Proxy proto _CType \
		 pThis: ptr IRpcStubBuffer,
	      _prpcmsg: ptr RPCOLEMESSAGE,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer


;void
IRpcStubBuffer_Invoke_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;IRpcStubBuffer *
;STDMETHODCALLTYPE
IRpcStubBuffer_IsIIDSupported_Proxy typedef proto _CType \
		 pThis: ptr IRpcStubBuffer,
		  riid: REFIID


;void
IRpcStubBuffer_IsIIDSupported_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;ULONG
IRpcStubBuffer_CountRefs_Proxy proto _CType \
		 pThis: ptr IRpcStubBuffer


;void
IRpcStubBuffer_CountRefs_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcStubBuffer_DebugServerQueryInterface_Proxy proto _CType \
		 pThis: ptr IRpcStubBuffer,
		   ppv: PVOID


;void
IRpcStubBuffer_DebugServerQueryInterface_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IRpcStubBuffer_DebugServerRelease_Proxy proto _CType \
		 pThis: ptr IRpcStubBuffer,
		    pv: PVOID


;void
IRpcStubBuffer_DebugServerRelease_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IRpcStubBuffer_INTERFACE_DEFINED__


ifndef __IPSFactoryBuffer_INTERFACE_DEFINED__
__IPSFactoryBuffer_INTERFACE_DEFINED__ equ 1




externdef		IID_IPSFactoryBuffer:IID

IPSFactoryBufferVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	 CreateProxy@CT typedef proto \
		 pThis: ptr IPSFactoryBuffer,
	     pUnkOuter: ptr IUnknown,
		  riid: REFIID,
	       ppProxy: ptr IRpcProxyBuffer,
		   ppv: PVOID
	 CreateProxy@MP typedef ptr CreateProxy@CT
	    CreateProxy CreateProxy@MP ?

	  CreateStub@CT typedef proto \
		 pThis: ptr IPSFactoryBuffer,
		  riid: REFIID,
	    pUnkServer: ptr IUnknown,
		ppStub: ptr IRpcStubBuffer
	  CreateStub@MP typedef ptr CreateStub@CT
	     CreateStub CreateStub@MP ?

	END_INTERFACE

IPSFactoryBufferVtbl	ENDS

LPIPSFactoryBufferVtbl	typedef ptr IPSFactoryBufferVtbl
IPSFactoryBuffer	STRUC
lpVtbl			LPIPSFactoryBufferVtbl ?
IPSFactoryBuffer	ENDS

;HRESULT
IPSFactoryBuffer_CreateProxy_Proxy proto _CType \
		 pThis: ptr IPSFactoryBuffer,
	     pUnkOuter: ptr IUnknown,
		  riid: REFIID,
	       ppProxy: ptr IRpcProxyBuffer,
		   ppv: PVOID


;void
IPSFactoryBuffer_CreateProxy_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPSFactoryBuffer_CreateStub_Proxy proto _CType \
		 pThis: ptr IPSFactoryBuffer,
		  riid: REFIID,
	    pUnkServer: ptr IUnknown,
		ppStub: ptr IRpcStubBuffer


;void
IPSFactoryBuffer_CreateStub_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IPSFactoryBuffer_INTERFACE_DEFINED__





if  (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM) ;; DCOM
;; This interface is only valid on Windows NT 4.0
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

       ClientGetSize@CT typedef proto \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	     pDataSize: LPDWORD
       ClientGetSize@MP typedef ptr ClientGetSize@CT
	  ClientGetSize ClientGetSize@MP ?

    ClientFillBuffer@CT typedef proto \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	     pDataSize: LPDWORD,
	   pDataBuffer: PVOID
    ClientFillBuffer@MP typedef ptr ClientFillBuffer@CT
       ClientFillBuffer ClientFillBuffer@MP ?

	ClientNotify@CT typedef proto \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	    cbDataSize: ULONG,
	   pDataBuffer: PVOID,
	      lDataRep: DWORD,
	       hrFault: HRESULT
	ClientNotify@MP typedef ptr ClientNotify@CT
	   ClientNotify ClientNotify@MP ?

	ServerNotify@CT typedef proto \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	    cbDataSize: ULONG,
	   pDataBuffer: PVOID,
	      lDataRep: DWORD
	ServerNotify@MP typedef ptr ServerNotify@CT
	   ServerNotify ServerNotify@MP ?

       ServerGetSize@CT typedef proto \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	       hrFault: HRESULT,
	     pDataSize: LPDWORD
       ServerGetSize@MP typedef ptr ServerGetSize@CT
	  ServerGetSize ServerGetSize@MP ?

    ServerFillBuffer@CT typedef proto \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	     pDataSize: LPDWORD,
	   pDataBuffer: PVOID,
	       hrFault: HRESULT
    ServerFillBuffer@MP typedef ptr ServerFillBuffer@CT
       ServerFillBuffer ServerFillBuffer@MP ?

	END_INTERFACE

IChannelHookVtbl	ENDS

LPIChannelHookVtbl	typedef ptr IChannelHookVtbl
IChannelHook		STRUC
lpVtbl			LPIChannelHookVtbl ?
IChannelHook		ENDS

;void
IChannelHook_ClientGetSize_Proxy proto _CType \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	     pDataSize: LPDWORD


;void
IChannelHook_ClientGetSize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IChannelHook_ClientFillBuffer_Proxy proto _CType \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	     pDataSize: LPDWORD,
	   pDataBuffer: PVOID


;void
IChannelHook_ClientFillBuffer_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IChannelHook_ClientNotify_Proxy proto _CType \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	    cbDataSize: ULONG,
	   pDataBuffer: PVOID,
	      lDataRep: DWORD,
	       hrFault: HRESULT


;void
IChannelHook_ClientNotify_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IChannelHook_ServerNotify_Proxy proto _CType \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	    cbDataSize: ULONG,
	   pDataBuffer: PVOID,
	      lDataRep: DWORD


;void
IChannelHook_ServerNotify_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IChannelHook_ServerGetSize_Proxy proto _CType \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	       hrFault: HRESULT,
	     pDataSize: LPDWORD


;void
IChannelHook_ServerGetSize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;void
IChannelHook_ServerFillBuffer_Proxy proto _CType \
		 pThis: ptr IChannelHook,
	       uExtent: REFGUID,
		  riid: REFIID,
	     pDataSize: LPDWORD,
	   pDataBuffer: PVOID,
	       hrFault: HRESULT


;void
IChannelHook_ServerFillBuffer_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IChannelHook_INTERFACE_DEFINED__





endif ;;DCOM





externdef		__MIDL_itf_objidl_0044_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_objidl_0044_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IPropertyStorage_INTERFACE_DEFINED__
__IPropertyStorage_INTERFACE_DEFINED__ equ 1

;; Well-known Property Set Format IDs
externdef		FMTID_SummaryInformation:FMTID
externdef		FMTID_DocSummaryInformation:FMTID
externdef		FMTID_UserDefinedProperties:FMTID

;; Flags for IPropertySetStorage::Create
PROPSETFLAG_DEFAULT	equ 0
PROPSETFLAG_NONSIMPLE	equ 1
PROPSETFLAG_ANSI	equ 2

;; This flag is only supported on StgCreatePropStg & StgOpenPropStg
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

;; Disable the warning about the obsolete member named 'bool'
;; 'bool', 'true', 'false', 'mutable', 'explicit', & 'typename'
;; are reserved keywords
;;#pragma warning(disable:4237)
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

;; Reserved global Property IDs
PID_DICTIONARY		equ 0
PID_CODEPAGE		equ 0x1
PID_FIRST_USABLE	equ 0x2
PID_FIRST_NAME_DEFAULT	equ 0xfff
PID_LOCALE		equ 0x80000000
PID_MODIFY_TIME		equ 0x80000001
PID_SECURITY		equ 0x80000002
PID_ILLEGAL		equ 0xffffffff

;; Property IDs for the SummaryInformation Property Set

PIDSI_TITLE		equ 0x00000002	 ;; VT_LPSTR
PIDSI_SUBJECT		equ 0x00000003	 ;; VT_LPSTR
PIDSI_AUTHOR		equ 0x00000004	 ;; VT_LPSTR
PIDSI_KEYWORDS		equ 0x00000005	 ;; VT_LPSTR
PIDSI_COMMENTS		equ 0x00000006	 ;; VT_LPSTR
PIDSI_TEMPLATE		equ 0x00000007	 ;; VT_LPSTR
PIDSI_LASTAUTHOR	equ 0x00000008	 ;; VT_LPSTR
PIDSI_REVNUMBER		equ 0x00000009	 ;; VT_LPSTR
PIDSI_EDITTIME		equ 0x0000000a	 ;; VT_FILETIME (UTC)
PIDSI_LASTPRINTED	equ 0x0000000b	 ;; VT_FILETIME (UTC)
PIDSI_CREATE_DTM	equ 0x0000000c	 ;; VT_FILETIME (UTC)
PIDSI_LASTSAVE_DTM	equ 0x0000000d	 ;; VT_FILETIME (UTC)
PIDSI_PAGECOUNT		equ 0x0000000e	;; VT_I4
PIDSI_WORDCOUNT		equ 0x0000000f	;; VT_I4
PIDSI_CHARCOUNT		equ 0x00000010	;; VT_I4
PIDSI_THUMBNAIL		equ 0x00000011	;; VT_CF
PIDSI_APPNAME		equ 0x00000012L	 ;; VT_LPSTR
PIDSI_DOC_SECURITY	equ 0x00000013	;; VT_I4
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

;; Macros for parsing the OS Version of the Property Set Header
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

	ReadMultiple@CT typedef proto \
		 pThis: ptr IPropertyStorage,
		cpspec: ULONG,
	       rgpspec: PROPSPEC,
	     rgpropvar: PROPVARIANT
	ReadMultiple@MP typedef ptr ReadMultiple@CT
	   ReadMultiple ReadMultiple@MP ?

       WriteMultiple@CT typedef proto \
		 pThis: ptr IPropertyStorage,
		cpspec: ULONG,
	       rgpspec: PROPSPEC,
	     rgpropvar: PROPVARIANT,
       propidNameFirst: PROPID
       WriteMultiple@MP typedef ptr WriteMultiple@CT
	  WriteMultiple WriteMultiple@MP ?

      DeleteMultiple@CT typedef proto \
		 pThis: ptr IPropertyStorage,
		cpspec: ULONG,
	       rgpspec: PROPSPEC
      DeleteMultiple@MP typedef ptr DeleteMultiple@CT
	 DeleteMultiple DeleteMultiple@MP ?

   ReadPropertyNames@CT typedef proto \
		 pThis: ptr IPropertyStorage,
	       cpropid: ULONG,
	      rgpropid: PROPID,
	  rglpwstrName: LPOLESTR
   ReadPropertyNames@MP typedef ptr ReadPropertyNames@CT
      ReadPropertyNames ReadPropertyNames@MP ?

  WritePropertyNames@CT typedef proto \
		 pThis: ptr IPropertyStorage,
	       cpropid: ULONG,
	      rgpropid: PROPID,
	  rglpwstrName: LPOLESTR
  WritePropertyNames@MP typedef ptr WritePropertyNames@CT
     WritePropertyNames WritePropertyNames@MP ?

 DeletePropertyNames@CT typedef proto \
		 pThis: ptr IPropertyStorage,
	       cpropid: ULONG,
	      rgpropid: PROPID
 DeletePropertyNames@MP typedef ptr DeletePropertyNames@CT
    DeletePropertyNames DeletePropertyNames@MP ?

	     Commit3@CT typedef proto \
		 pThis: ptr IPropertyStorage,
	grfCommitFlags: DWORD
	     Commit3@MP typedef ptr Commit3@CT
		 Commit Commit3@MP ?

	     Revert3@CT typedef proto \
		 pThis: ptr IPropertyStorage
	     Revert3@MP typedef ptr Revert3@CT
		 Revert Revert3@MP ?

	       Enum3@CT typedef proto \
		 pThis: ptr IPropertyStorage,
		ppenum: ptr IEnumSTATPROPSTG
	       Enum3@MP typedef ptr Enum3@CT
		   Enum Enum3@MP ?

	    SetTimes@CT typedef proto \
		 pThis: ptr IPropertyStorage,
		pctime: LPFILETIME,
		patime: LPFILETIME,
		pmtime: LPFILETIME
	    SetTimes@MP typedef ptr SetTimes@CT
	       SetTimes SetTimes@MP ?

	   SetClass3@CT typedef proto \
		 pThis: ptr IPropertyStorage,
		 clsid: REFCLSID
	   SetClass3@MP typedef ptr SetClass3@CT
	       SetClass SetClass3@MP ?

	       Stat3@CT typedef proto \
		 pThis: ptr IPropertyStorage,
	    pstatpsstg: ptr STATPROPSETSTG
	       Stat3@MP typedef ptr Stat3@CT
		   Stat Stat3@MP ?

	END_INTERFACE

IPropertyStorageVtbl	ENDS

LPIPropertyStorageVtbl	typedef ptr IPropertyStorageVtbl
IPropertyStorage	STRUC
lpVtbl			LPIPropertyStorageVtbl ?
IPropertyStorage	ENDS
;HRESULT
IPropertyStorage_ReadMultiple_Proxy proto _CType \
		 pThis: ptr IPropertyStorage,
		cpspec: ULONG,
	       rgpspec: PROPSPEC,
	     rgpropvar: PROPVARIANT


;void
IPropertyStorage_ReadMultiple_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertyStorage_WriteMultiple_Proxy proto _CType \
		 pThis: ptr IPropertyStorage,
		cpspec: ULONG,
	       rgpspec: PROPSPEC,
	     rgpropvar: PROPVARIANT,
       propidNameFirst: PROPID


;void
IPropertyStorage_WriteMultiple_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertyStorage_DeleteMultiple_Proxy proto _CType \
		 pThis: ptr IPropertyStorage,
		cpspec: ULONG,
	       rgpspec: PROPSPEC


;void
IPropertyStorage_DeleteMultiple_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertyStorage_ReadPropertyNames_Proxy proto _CType \
		 pThis: ptr IPropertyStorage,
	       cpropid: ULONG,
	      rgpropid: PROPID,
	  rglpwstrName: LPOLESTR


;void
IPropertyStorage_ReadPropertyNames_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertyStorage_WritePropertyNames_Proxy proto _CType \
		 pThis: ptr IPropertyStorage,
	       cpropid: ULONG,
	      rgpropid: PROPID,
	  rglpwstrName: LPOLESTR


;void
IPropertyStorage_WritePropertyNames_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertyStorage_DeletePropertyNames_Proxy proto _CType \
		 pThis: ptr IPropertyStorage,
	       cpropid: ULONG,
	      rgpropid: PROPID


;void
IPropertyStorage_DeletePropertyNames_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertyStorage_Commit_Proxy proto _CType \
		 pThis: ptr IPropertyStorage,
	grfCommitFlags: DWORD


;void
IPropertyStorage_Commit_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertyStorage_Revert_Proxy proto _CType \
		 pThis: ptr IPropertyStorage


;void
IPropertyStorage_Revert_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertyStorage_Enum_Proxy proto _CType \
		 pThis: ptr IPropertyStorage,
		ppenum: ptr IEnumSTATPROPSTG


;void
IPropertyStorage_Enum_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertyStorage_SetTimes_Proxy proto _CType \
		 pThis: ptr IPropertyStorage,
		pctime: LPFILETIME,
		patime: LPFILETIME,
		pmtime: LPFILETIME


;void
IPropertyStorage_SetTimes_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertyStorage_SetClass_Proxy proto _CType \
		 pThis: ptr IPropertyStorage,
		 clsid: REFCLSID


;void
IPropertyStorage_SetClass_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertyStorage_Stat_Proxy proto _CType \
		 pThis: ptr IPropertyStorage,
	    pstatpsstg: ptr STATPROPSETSTG


;void
IPropertyStorage_Stat_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IPropertyStorage_INTERFACE_DEFINED__


ifndef __IPropertySetStorage_INTERFACE_DEFINED__
__IPropertySetStorage_INTERFACE_DEFINED__ equ 1

LPPROPERTYSETSTORAGE	typedef ptr IPropertySetStorage


externdef		IID_IPropertySetStorage:IID

IPropertySetStorageVtbl STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	      Create@CT typedef proto \
		 pThis: ptr IPropertySetStorage,
		rfmtid: REFFMTID,
		pclsid: ptr CLSID,
	      grfFlags: DWORD,
	       grfMode: DWORD,
	       ppprstg: ptr IPropertyStorage
	      Create@MP typedef ptr Create@CT
		 Create Create@MP ?

		Open@CT typedef proto \
		 pThis: ptr IPropertySetStorage,
		rfmtid: REFFMTID,
	       grfMode: DWORD,
	       ppprstg: ptr IPropertyStorage
		Open@MP typedef ptr Open@CT
		   Open Open@MP ?

	      Delete@CT typedef proto \
		 pThis: ptr IPropertySetStorage,
		rfmtid: REFFMTID
	      Delete@MP typedef ptr Delete@CT
		 Delete Delete@MP ?

	       Enum4@CT typedef proto \
		 pThis: ptr IPropertySetStorage,
		ppenum: ptr IEnumSTATPROPSETSTG
	       Enum4@MP typedef ptr Enum4@CT
		   Enum Enum4@MP ?

	END_INTERFACE

IPropertySetStorageVtbl ENDS

LPIPropertySetStorageVtbl typedef ptr IPropertySetStorageVtbl
IPropertySetStorage	STRUC
lpVtbl			LPIPropertySetStorageVtbl ?
IPropertySetStorage	ENDS


;HRESULT
IPropertySetStorage_Create_Proxy proto _CType \
		 pThis: ptr IPropertySetStorage,
		rfmtid: REFFMTID,
		pclsid: ptr CLSID,
	      grfFlags: DWORD,
	       grfMode: DWORD,
	       ppprstg: ptr IPropertyStorage


;void
IPropertySetStorage_Create_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertySetStorage_Open_Proxy proto _CType \
		 pThis: ptr IPropertySetStorage,
		rfmtid: REFFMTID,
	       grfMode: DWORD,
	       ppprstg: ptr IPropertyStorage


;void
IPropertySetStorage_Open_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertySetStorage_Delete_Proxy proto _CType \
		 pThis: ptr IPropertySetStorage,
		rfmtid: REFFMTID


;void
IPropertySetStorage_Delete_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IPropertySetStorage_Enum_Proxy proto _CType \
		 pThis: ptr IPropertySetStorage,
		ppenum: ptr IEnumSTATPROPSETSTG


;void
IPropertySetStorage_Enum_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IPropertySetStorage_INTERFACE_DEFINED__


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
IEnumSTATPROPSTG_RemoteNext_Proxy proto _CType \
		 pThis: ptr IEnumSTATPROPSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSTG,
	  pceltFetched: LPDWORD


;void
IEnumSTATPROPSTG_RemoteNext_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATPROPSTG_Skip_Proxy proto _CType \
		 pThis: ptr IEnumSTATPROPSTG,
		  celt: ULONG


;void
IEnumSTATPROPSTG_Skip_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATPROPSTG_Reset_Proxy proto _CType \
		 pThis: ptr IEnumSTATPROPSTG


;void
IEnumSTATPROPSTG_Reset_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATPROPSTG_Clone_Proxy proto _CType \
		 pThis: ptr IEnumSTATPROPSTG,
		ppenum: ptr IEnumSTATPROPSTG


;void
IEnumSTATPROPSTG_Clone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IEnumSTATPROPSTG_INTERFACE_DEFINED__


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
IEnumSTATPROPSETSTG_RemoteNext_Proxy proto _CType \
		 pThis: ptr IEnumSTATPROPSETSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSETSTG,
	  pceltFetched: LPDWORD


;void
IEnumSTATPROPSETSTG_RemoteNext_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATPROPSETSTG_Skip_Proxy proto _CType \
		 pThis: ptr IEnumSTATPROPSETSTG,
		  celt: ULONG


;void
IEnumSTATPROPSETSTG_Skip_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATPROPSETSTG_Reset_Proxy proto _CType \
		 pThis: ptr IEnumSTATPROPSETSTG


;void
IEnumSTATPROPSETSTG_Reset_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumSTATPROPSETSTG_Clone_Proxy proto _CType \
		 pThis: ptr IEnumSTATPROPSETSTG,
		ppenum: ptr IEnumSTATPROPSETSTG


;void
IEnumSTATPROPSETSTG_Clone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IEnumSTATPROPSETSTG_INTERFACE_DEFINED__


PropVariantCopy proto _CType \
	      pvarDest: ptr PROPVARIANT,
	       pvarSrc: ptr PROPVARIANT

PropVariantClear proto _CType \
		  pvar: ptr PROPVARIANT

FreePropVariantArray proto _CType \
	     cVariants: ULONG,
		rgvars: ptr PROPVARIANT

_PROPVARIANTINIT_DEFINED_ equ 1
PropVariantInit macro pvar
	exitm<memset ( pvar, 0, sizeof(PROPVARIANT) )>
	endm


ifndef _STGCREATEPROPSTG_DEFINED_
;WINOLEAPI
StgCreatePropStg proto _CType \
		  pUnk: ptr IUnknown,
		 fmtid: REFFMTID,
		pclsid: ptr CLSID,
	      grfFlags: DWORD,
	    dwReserved: DWORD,
	     ppPropStg: ptr IPropertyStorage

StgOpenPropStg proto _CType \
		  pUnk: ptr IUnknown,
		 fmtid: REFFMTID,
	      grfFlags: DWORD,
	    dwReserved: DWORD,
	     ppPropStg: ptr IPropertyStorage

StgCreatePropSetStg proto _CType \
	      pStorage: ptr IStorage,
	    dwReserved: DWORD,
	  ppPropSetStg: ptr IPropertySetStorage


CCH_MAX_PROPSTG_NAME	equ 31
;WINOLEAPI
FmtIdToPropStgName proto _CType \
		pfmtid: ptr FMTID,
	       oszName: LPOLESTR

PropStgNameToFmtId proto _CType \
	       oszName: LPOLESTR,
		pfmtid: ptr FMTID

endif
if  (_WIN32_WINNT GE 0x0400 ) OR defined(_WIN32_DCOM)
;; This interface is only valid on Windows NT 4.0


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

	QueryBlanket@CT typedef proto \
		 pThis: ptr IClientSecurity,
		pProxy: ptr IUnknown,
	     pAuthnSvc: LPDWORD,
	     pAuthzSvc: LPDWORD,
      pServerPrincName: ptr OLECHAR,
	   pAuthnLevel: LPDWORD,
	     pImpLevel: LPDWORD,
	     pAuthInfo: PVOID,
	  pCapabilites: LPDWORD
	QueryBlanket@MP typedef ptr QueryBlanket@CT
	   QueryBlanket QueryBlanket@MP ?

	  SetBlanket@CT typedef proto \
		 pThis: ptr IClientSecurity,
		pProxy: ptr IUnknown,
	      AuthnSvc: DWORD,
	      AuthzSvc: DWORD,
      pServerPrincName: ptr OLECHAR,
	    AuthnLevel: DWORD,
	      ImpLevel: DWORD,
	     pAuthInfo: PVOID,
	  Capabilities: DWORD
	  SetBlanket@MP typedef ptr SetBlanket@CT
	     SetBlanket SetBlanket@MP ?

	   CopyProxy@CT typedef proto \
		 pThis: ptr IClientSecurity,
		pProxy: ptr IUnknown,
		ppCopy: ptr IUnknown
	   CopyProxy@MP typedef ptr CopyProxy@CT
	      CopyProxy CopyProxy@MP ?

	END_INTERFACE

IClientSecurityVtbl	ENDS

LPIClientSecurityVtbl	typedef ptr IClientSecurityVtbl
IClientSecurity		STRUC
lpVtbl			LPIClientSecurityVtbl ?
IClientSecurity		ENDS


;HRESULT
IClientSecurity_QueryBlanket_Proxy proto _CType \
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
IClientSecurity_QueryBlanket_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClientSecurity_SetBlanket_Proxy proto _CType \
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
IClientSecurity_SetBlanket_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClientSecurity_CopyProxy_Proxy proto _CType \
		 pThis: ptr IClientSecurity,
		pProxy: ptr IUnknown,
		ppCopy: ptr IUnknown


;void
IClientSecurity_CopyProxy_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IClientSecurity_INTERFACE_DEFINED__


ifndef __IServerSecurity_INTERFACE_DEFINED__
__IServerSecurity_INTERFACE_DEFINED__ equ 1

externdef		IID_IServerSecurity:IID

IServerSecurityVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

       QueryBlanket2@CT typedef proto \
		 pThis: ptr IServerSecurity,
	     pAuthnSvc: LPDWORD,
	     pAuthzSvc: LPDWORD,
      pServerPrincName: ptr OLECHAR,
	   pAuthnLevel: LPDWORD,
	     pImpLevel: LPDWORD,
		pPrivs: PVOID,
	 pCapabilities: LPDWORD
       QueryBlanket2@MP typedef ptr QueryBlanket2@CT
	   QueryBlanket QueryBlanket2@MP ?

   ImpersonateClient@CT typedef proto \
		 pThis: ptr IServerSecurity
   ImpersonateClient@MP typedef ptr ImpersonateClient@CT
      ImpersonateClient ImpersonateClient@MP ?

	RevertToSelf@CT typedef proto \
		 pThis: ptr IServerSecurity
	RevertToSelf@MP typedef ptr RevertToSelf@CT
	   RevertToSelf RevertToSelf@MP ?

     IsImpersonating@CT typedef proto \
		 pThis: ptr IServerSecurity
     IsImpersonating@MP typedef ptr IsImpersonating@CT
	IsImpersonating IsImpersonating@MP ?

	END_INTERFACE

IServerSecurityVtbl	ENDS

LPIServerSecurityVtbl	typedef ptr IServerSecurityVtbl
IServerSecurity		STRUC
lpVtbl			LPIServerSecurityVtbl ?
IServerSecurity		ENDS


;HRESULT
IServerSecurity_QueryBlanket_Proxy proto _CType \
		 pThis: ptr IServerSecurity,
	     pAuthnSvc: LPDWORD,
	     pAuthzSvc: LPDWORD,
      pServerPrincName: ptr OLECHAR,
	   pAuthnLevel: LPDWORD,
	     pImpLevel: LPDWORD,
		pPrivs: PVOID,
	 pCapabilities: LPDWORD


;void
IServerSecurity_QueryBlanket_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IServerSecurity_ImpersonateClient_Proxy proto _CType \
		 pThis: ptr IServerSecurity


;void
IServerSecurity_ImpersonateClient_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IServerSecurity_RevertToSelf_Proxy proto _CType \
		 pThis: ptr IServerSecurity


;void
IServerSecurity_RevertToSelf_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;BOOL
IServerSecurity_IsImpersonating_Proxy proto _CType \
		 pThis: ptr IServerSecurity


;void
IServerSecurity_IsImpersonating_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IServerSecurity_INTERFACE_DEFINED__


ifndef __IClassActivator_INTERFACE_DEFINED__
__IClassActivator_INTERFACE_DEFINED__ equ 1


externdef		IID_IClassActivator:IID

IClassActivatorVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

      GetClassObject@CT typedef proto \
		 pThis: ptr IClassActivator,
		rclsid: REFCLSID,
	dwClassContext: DWORD,
		locale: LCID,
		  riid: REFIID,
		   ppv: PVOID
      GetClassObject@MP typedef ptr GetClassObject@CT
	 GetClassObject GetClassObject@MP ?

	END_INTERFACE

IClassActivatorVtbl	ENDS

LPIClassActivatorVtbl	typedef ptr IClassActivatorVtbl
IClassActivator		STRUC
lpVtbl			LPIClassActivatorVtbl ?
IClassActivator		ENDS



;HRESULT
IClassActivator_GetClassObject_Proxy proto _CType \
		 pThis: ptr IClassActivator,
		rclsid: REFCLSID,
	dwClassContext: DWORD,
		locale: LCID,
		  riid: REFIID,
		   ppv: PVOID


;void
IClassActivator_GetClassObject_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IClassActivator_INTERFACE_DEFINED__


ifndef __IRpcOptions_INTERFACE_DEFINED__
__IRpcOptions_INTERFACE_DEFINED__ equ 1




externdef		IID_IRpcOptions:IID

IRpcOptionsVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

		 Set@CT typedef proto \
		 pThis: ptr IRpcOptions,
		  pPrx: ptr IUnknown,
	    dwProperty: DWORD,
	       dwValue: DWORD
		 Set@MP typedef ptr Set@CT
		    Set Set@MP ?

	       Query@CT typedef proto \
		 pThis: ptr IRpcOptions,
		  pPrx: ptr IUnknown,
	    dwProperty: DWORD,
	      pdwValue: LPDWORD
	       Query@MP typedef ptr Query@CT
		  Query Query@MP ?

	  CopyProxy2@CT typedef proto \
		 pThis: ptr IRpcOptions,
	     punkProxy: ptr IUnknown,
	     ppunkCopy: ptr IUnknown
	  CopyProxy2@MP typedef ptr CopyProxy2@CT
	      CopyProxy CopyProxy2@MP ?

	END_INTERFACE

IRpcOptionsVtbl		ENDS

LPIRpcOptionsVtbl	typedef ptr IRpcOptionsVtbl
IRpcOptions		STRUC
lpVtbl			LPIRpcOptionsVtbl ?
IRpcOptions		ENDS


;HRESULT
IRpcOptions_Set_Proxy proto _CType \
		 pThis: ptr IRpcOptions,
		  pPrx: ptr IUnknown,
	    dwProperty: DWORD,
	       dwValue: DWORD


;void
IRpcOptions_Set_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcOptions_Query_Proxy proto _CType \
		 pThis: ptr IRpcOptions,
		  pPrx: ptr IUnknown,
	    dwProperty: DWORD,
	      pdwValue: LPDWORD


;void
IRpcOptions_Query_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IRpcOptions_CopyProxy_Proxy proto _CType \
		 pThis: ptr IRpcOptions,
	     punkProxy: ptr IUnknown,
	     ppunkCopy: ptr IUnknown


;void
IRpcOptions_CopyProxy_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IRpcOptions_INTERFACE_DEFINED__






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

	 InitBinding@CT typedef proto \
		 pThis: ptr IComBinding,
       dwEndpointFlags: DWORD,
	    dwNICFlags: DWORD,
	  mbzReserved1: DWORD,
	  mbzReserved2: DWORD,
	    pszBinding: LPOLESTR
	 InitBinding@MP typedef ptr InitBinding@CT
	    InitBinding InitBinding@MP ?

	QueryBinding@CT typedef proto \
		 pThis: ptr IComBinding,
      pdwEndpointFlags: LPDWORD,
	   pdwNICFlags: LPDWORD,
	  mbzReserved1: LPDWORD,
	  mbzReserved2: LPDWORD,
	   ppszBinding: ptr LPOLESTR
	QueryBinding@MP typedef ptr QueryBinding@CT
	   QueryBinding QueryBinding@MP ?

	END_INTERFACE

IComBindingVtbl		ENDS

LPIComBindingVtbl	typedef ptr IComBindingVtbl
IComBinding		STRUC
lpVtbl			LPIComBindingVtbl ?
IComBinding		ENDS



;HRESULT
IComBinding_InitBinding_Proxy proto _CType \
		 pThis: ptr IComBinding,
       dwEndpointFlags: DWORD,
	    dwNICFlags: DWORD,
	  mbzReserved1: DWORD,
	  mbzReserved2: DWORD,
	    pszBinding: LPOLESTR


;void
IComBinding_InitBinding_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IComBinding_QueryBinding_Proxy proto _CType \
		 pThis: ptr IComBinding,
      pdwEndpointFlags: LPDWORD,
	   pdwNICFlags: LPDWORD,
	  mbzReserved1: LPDWORD,
	  mbzReserved2: LPDWORD,
	   ppszBinding: ptr LPOLESTR


;void
IComBinding_QueryBinding_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IComBinding_INTERFACE_DEFINED__





endif ;;DCOM


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

	  FillAppend@CT typedef proto \
		 pThis: ptr IFillLockBytes,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD
	  FillAppend@MP typedef ptr FillAppend@CT
	     FillAppend FillAppend@MP ?

	      FillAt@CT typedef proto \
		 pThis: ptr IFillLockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD
	      FillAt@MP typedef ptr FillAt@CT
		 FillAt FillAt@MP ?

	 SetFillSize@CT typedef proto \
		 pThis: ptr IFillLockBytes,
		ulSize: ULARGE_INTEGER
	 SetFillSize@MP typedef ptr SetFillSize@CT
	    SetFillSize SetFillSize@MP ?

	   Terminate@CT typedef proto \
		 pThis: ptr IFillLockBytes,
	     bCanceled: BOOL
	   Terminate@MP typedef ptr Terminate@CT
	      Terminate Terminate@MP ?

	END_INTERFACE

IFillLockBytesVtbl	ENDS

LPIFillLockBytesVtbl	typedef ptr IFillLockBytesVtbl
IFillLockBytes		STRUC
lpVtbl			LPIFillLockBytesVtbl ?
IFillLockBytes		ENDS

;HRESULT
IFillLockBytes_RemoteFillAppend_Proxy proto _CType \
		 pThis: ptr IFillLockBytes,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;void
IFillLockBytes_RemoteFillAppend_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IFillLockBytes_RemoteFillAt_Proxy proto _CType \
		 pThis: ptr IFillLockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;void
IFillLockBytes_RemoteFillAt_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IFillLockBytes_SetFillSize_Proxy proto _CType \
		 pThis: ptr IFillLockBytes,
		ulSize: ULARGE_INTEGER


;void
IFillLockBytes_SetFillSize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IFillLockBytes_Terminate_Proxy proto _CType \
		 pThis: ptr IFillLockBytes,
	     bCanceled: BOOL


;void
IFillLockBytes_Terminate_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IFillLockBytes_INTERFACE_DEFINED__


ifndef __IProgressNotify_INTERFACE_DEFINED__
__IProgressNotify_INTERFACE_DEFINED__ equ 1




externdef		IID_IProgressNotify:IID

IProgressNotifyVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	  OnProgress@CT typedef proto \
		 pThis: ptr IProgressNotify,
     dwProgressCurrent: DWORD,
     dwProgressMaximum: DWORD,
	     fAccurate: BOOL,
		fOwner: BOOL
	  OnProgress@MP typedef ptr OnProgress@CT
	     OnProgress OnProgress@MP ?

	END_INTERFACE

IProgressNotifyVtbl	ENDS

LPIProgressNotifyVtbl	typedef ptr IProgressNotifyVtbl
IProgressNotify		STRUC
lpVtbl			LPIProgressNotifyVtbl ?
IProgressNotify		ENDS



;HRESULT
IProgressNotify_OnProgress_Proxy proto _CType \
		 pThis: ptr IProgressNotify,
     dwProgressCurrent: DWORD,
     dwProgressMaximum: DWORD,
	     fAccurate: BOOL,
		fOwner: BOOL


;void
IProgressNotify_OnProgress_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IProgressNotify_INTERFACE_DEFINED__


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

	LayoutScript@CT typedef proto \
		 pThis: ptr ILayoutStorage,
	pStorageLayout: ptr StorageLayout,
	      nEntries: DWORD,
    glfInterleavedFlag: DWORD
	LayoutScript@MP typedef ptr LayoutScript@CT
	   LayoutScript LayoutScript@MP ?

	BeginMonitor@CT typedef proto \
		 pThis: ptr ILayoutStorage
	BeginMonitor@MP typedef ptr BeginMonitor@CT
	   BeginMonitor BeginMonitor@MP ?

	  EndMonitor@CT typedef proto \
		 pThis: ptr ILayoutStorage
	  EndMonitor@MP typedef ptr EndMonitor@CT
	     EndMonitor EndMonitor@MP ?

     ReLayoutDocfile@CT typedef proto \
		 pThis: ptr ILayoutStorage,
	 pwcsNewDfName: ptr OLECHAR
     ReLayoutDocfile@MP typedef ptr ReLayoutDocfile@CT
	ReLayoutDocfile ReLayoutDocfile@MP ?

ReLayoutDocfileOnILockBytes@CT typedef proto \
		 pThis: ptr ILayoutStorage,
	   pILockBytes: ptr ILockBytes
ReLayoutDocfileOnILockBytes@MP typedef ptr ReLayoutDocfileOnILockBytes@CT
ReLayoutDocfileOnILockBytes ReLayoutDocfileOnILockBytes@MP ?

	END_INTERFACE

ILayoutStorageVtbl	ENDS

LPILayoutStorageVtbl	typedef ptr ILayoutStorageVtbl
ILayoutStorage		STRUC
lpVtbl			LPILayoutStorageVtbl ?
ILayoutStorage		ENDS



;HRESULT
ILayoutStorage_LayoutScript_Proxy proto _CType \
		 pThis: ptr ILayoutStorage,
	pStorageLayout: ptr StorageLayout,
	      nEntries: DWORD,
    glfInterleavedFlag: DWORD


;void
ILayoutStorage_LayoutScript_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ILayoutStorage_BeginMonitor_Proxy proto _CType \
		 pThis: ptr ILayoutStorage


;void
ILayoutStorage_BeginMonitor_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ILayoutStorage_EndMonitor_Proxy proto _CType \
		 pThis: ptr ILayoutStorage


;void
ILayoutStorage_EndMonitor_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ILayoutStorage_ReLayoutDocfile_Proxy proto _CType \
		 pThis: ptr ILayoutStorage,
	 pwcsNewDfName: ptr OLECHAR


;void
ILayoutStorage_ReLayoutDocfile_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ILayoutStorage_ReLayoutDocfileOnILockBytes_Proxy proto _CType \
		 pThis: ptr ILayoutStorage,
	   pILockBytes: ptr ILockBytes


;void
ILayoutStorage_ReLayoutDocfileOnILockBytes_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __ILayoutStorage_INTERFACE_DEFINED__


ifndef __ISurrogate_INTERFACE_DEFINED__
__ISurrogate_INTERFACE_DEFINED__ equ 1



LPSURROGATE		typedef ptr ISurrogate


externdef		IID_ISurrogate:IID

ISurrogateVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

       LoadDllServer@CT typedef proto \
		 pThis: ptr ISurrogate,
		 Clsid: REFCLSID
       LoadDllServer@MP typedef ptr LoadDllServer@CT
	  LoadDllServer LoadDllServer@MP ?

       FreeSurrogate@CT typedef proto \
		 pThis: ptr ISurrogate
       FreeSurrogate@MP typedef ptr FreeSurrogate@CT
	  FreeSurrogate FreeSurrogate@MP ?

	END_INTERFACE

ISurrogateVtbl		ENDS

LPISurrogateVtbl	typedef ptr ISurrogateVtbl
ISurrogate		STRUC
lpVtbl			LPISurrogateVtbl ?
ISurrogate		ENDS



;HRESULT
ISurrogate_LoadDllServer_Proxy proto _CType \
		 pThis: ptr ISurrogate,
		 Clsid: REFCLSID


;void
ISurrogate_LoadDllServer_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ISurrogate_FreeSurrogate_Proxy proto _CType \
		 pThis: ptr ISurrogate


;void
ISurrogate_FreeSurrogate_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __ISurrogate_INTERFACE_DEFINED__


ifndef __IGlobalInterfaceTable_INTERFACE_DEFINED__
__IGlobalInterfaceTable_INTERFACE_DEFINED__ equ 1



LPGLOBALINTERFACETABLE	typedef ptr IGlobalInterfaceTable


externdef		IID_IGlobalInterfaceTable:IID


IGlobalInterfaceTableVtbl STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

RegisterInterfaceInGlobal@CT typedef proto \
		 pThis: ptr IGlobalInterfaceTable,
		  pUnk: ptr IUnknown,
		  riid: REFIID,
	     pdwCookie: LPDWORD
RegisterInterfaceInGlobal@MP typedef ptr RegisterInterfaceInGlobal@CT
RegisterInterfaceInGlobal RegisterInterfaceInGlobal@MP ?

RevokeInterfaceFromGlobal@CT typedef proto \
		 pThis: ptr IGlobalInterfaceTable,
	      dwCookie: DWORD
RevokeInterfaceFromGlobal@MP typedef ptr RevokeInterfaceFromGlobal@CT
RevokeInterfaceFromGlobal RevokeInterfaceFromGlobal@MP ?

GetInterfaceFromGlobal@CT typedef proto \
		 pThis: ptr IGlobalInterfaceTable,
	      dwCookie: DWORD,
		  riid: REFIID,
		   ppv: PVOID
GetInterfaceFromGlobal@MP typedef ptr GetInterfaceFromGlobal@CT
 GetInterfaceFromGlobal GetInterfaceFromGlobal@MP ?

	END_INTERFACE

IGlobalInterfaceTableVtbl ENDS

LPIGlobalInterfaceTableVtbl typedef ptr IGlobalInterfaceTableVtbl
IGlobalInterfaceTable	STRUC
lpVtbl			LPIGlobalInterfaceTableVtbl ?
IGlobalInterfaceTable	ENDS

;HRESULT
IGlobalInterfaceTable_RegisterInterfaceInGlobal_Proxy proto _CType \
		 pThis: ptr IGlobalInterfaceTable,
		  pUnk: ptr IUnknown,
		  riid: REFIID,
	     pdwCookie: LPDWORD


;void
IGlobalInterfaceTable_RegisterInterfaceInGlobal_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IGlobalInterfaceTable_RevokeInterfaceFromGlobal_Proxy proto _CType \
		 pThis: ptr IGlobalInterfaceTable,
	      dwCookie: DWORD


;void
IGlobalInterfaceTable_RevokeInterfaceFromGlobal_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IGlobalInterfaceTable_GetInterfaceFromGlobal_Proxy proto _CType \
		 pThis: ptr IGlobalInterfaceTable,
	      dwCookie: DWORD,
		  riid: REFIID,
		   ppv: PVOID


;void
IGlobalInterfaceTable_GetInterfaceFromGlobal_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IGlobalInterfaceTable_INTERFACE_DEFINED__


ifndef __IDirectWriterLock_INTERFACE_DEFINED__
__IDirectWriterLock_INTERFACE_DEFINED__ equ 1




externdef		IID_IDirectWriterLock:IID

IDirectWriterLockVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

  WaitForWriteAccess@CT typedef proto \
		 pThis: ptr IDirectWriterLock,
	     dwTimeout: DWORD
  WaitForWriteAccess@MP typedef ptr WaitForWriteAccess@CT
     WaitForWriteAccess WaitForWriteAccess@MP ?

  ReleaseWriteAccess@CT typedef proto \
		 pThis: ptr IDirectWriterLock
  ReleaseWriteAccess@MP typedef ptr ReleaseWriteAccess@CT
     ReleaseWriteAccess ReleaseWriteAccess@MP ?

     HaveWriteAccess@CT typedef proto \
		 pThis: ptr IDirectWriterLock
     HaveWriteAccess@MP typedef ptr HaveWriteAccess@CT
	HaveWriteAccess HaveWriteAccess@MP ?

	END_INTERFACE

IDirectWriterLockVtbl	ENDS

LPIDirectWriterLockVtbl typedef ptr IDirectWriterLockVtbl
IDirectWriterLock	STRUC
lpVtbl			LPIDirectWriterLockVtbl ?
IDirectWriterLock	ENDS

;HRESULT
IDirectWriterLock_WaitForWriteAccess_Proxy proto _CType \
		 pThis: ptr IDirectWriterLock,
	     dwTimeout: DWORD


;void
IDirectWriterLock_WaitForWriteAccess_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDirectWriterLock_ReleaseWriteAccess_Proxy proto _CType \
		 pThis: ptr IDirectWriterLock


;void
IDirectWriterLock_ReleaseWriteAccess_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IDirectWriterLock_HaveWriteAccess_Proxy proto _CType \
		 pThis: ptr IDirectWriterLock


;void
IDirectWriterLock_HaveWriteAccess_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IDirectWriterLock_INTERFACE_DEFINED__


ifndef __ISynchronize_INTERFACE_DEFINED__
__ISynchronize_INTERFACE_DEFINED__ equ 1




externdef		IID_ISynchronize:IID

ISynchronizeVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	       _Wait@CT typedef proto \
		 pThis: ptr ISynchronize,
	dwMilliseconds: DWORD
	       _Wait@MP typedef ptr _Wait@CT
		  _Wait _Wait@MP ?

	      Signal@CT typedef proto \
		 pThis: ptr ISynchronize
	      Signal@MP typedef ptr Signal@CT
		 Signal Signal@MP ?

		  Reset Reset@MP ?

	END_INTERFACE

ISynchronizeVtbl	ENDS

LPISynchronizeVtbl	typedef ptr ISynchronizeVtbl
ISynchronize		STRUC
lpVtbl			LPISynchronizeVtbl ?
ISynchronize		ENDS


;HRESULT
ISynchronize_Wait_Proxy proto _CType \
		 pThis: ptr ISynchronize,
	dwMilliseconds: DWORD


;void
ISynchronize_Wait_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ISynchronize_Signal_Proxy proto _CType \
		 pThis: ptr ISynchronize


;void
ISynchronize_Signal_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ISynchronize_Reset_Proxy proto _CType \
		 pThis: ptr ISynchronize


;void
ISynchronize_Reset_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __ISynchronize_INTERFACE_DEFINED__


ifndef __ISynchronizeMutex_INTERFACE_DEFINED__
__ISynchronizeMutex_INTERFACE_DEFINED__ equ 1




externdef		IID_ISynchronizeMutex:IID

ISynchronizeMutexVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	       Wait2@CT typedef proto \
		 pThis: ptr ISynchronizeMutex,
	dwMilliseconds: DWORD
	       Wait2@MP typedef ptr Wait2@CT
		  _Wait Wait2@MP ?

	     Signal2@CT typedef proto \
		 pThis: ptr ISynchronizeMutex
	     Signal2@MP typedef ptr Signal2@CT
		 Signal Signal2@MP ?

		  Reset Reset@MP ?

	ReleaseMutex@CT typedef proto \
		 pThis: ptr ISynchronizeMutex
	ReleaseMutex@MP typedef ptr ReleaseMutex@CT
	   ReleaseMutex ReleaseMutex@MP ?

	END_INTERFACE

ISynchronizeMutexVtbl	ENDS

LPISynchronizeMutexVtbl typedef ptr ISynchronizeMutexVtbl
ISynchronizeMutex	STRUC
lpVtbl			LPISynchronizeMutexVtbl ?
ISynchronizeMutex	ENDS


;HRESULT
ISynchronizeMutex_ReleaseMutex_Proxy proto _CType \
		 pThis: ptr ISynchronizeMutex


;void
ISynchronizeMutex_ReleaseMutex_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __ISynchronizeMutex_INTERFACE_DEFINED__


ifndef __IAsyncSetup_INTERFACE_DEFINED__
__IAsyncSetup_INTERFACE_DEFINED__ equ 1




externdef		IID_IAsyncSetup:IID

IAsyncSetupVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

     GetAsyncManager@CT typedef proto \
		 pThis: ptr IAsyncSetup,
		  riid: REFIID,
		pOuter: ptr IUnknown,
	       dwFlags: DWORD,
	       ppInner: ptr IUnknown,
	    ppAsyncMgr: ptr IAsyncManager
     GetAsyncManager@MP typedef ptr GetAsyncManager@CT
	GetAsyncManager GetAsyncManager@MP ?

	END_INTERFACE

IAsyncSetupVtbl		ENDS

LPIAsyncSetupVtbl	typedef ptr IAsyncSetupVtbl
IAsyncSetup		STRUC
lpVtbl			LPIAsyncSetupVtbl ?
IAsyncSetup		ENDS



;HRESULT
IAsyncSetup_GetAsyncManager_Proxy proto _CType \
		 pThis: ptr IAsyncSetup,
		  riid: REFIID,
		pOuter: ptr IUnknown,
	       dwFlags: DWORD,
	       ppInner: ptr IUnknown,
	    ppAsyncMgr: ptr IAsyncManager


;void
IAsyncSetup_GetAsyncManager_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IAsyncSetup_INTERFACE_DEFINED__


ifndef __ICancelMethodCalls_INTERFACE_DEFINED__
__ICancelMethodCalls_INTERFACE_DEFINED__ equ 1



LPCANCELMETHODCALLS	typedef ptr ICancelMethodCalls


externdef		IID_ICancelMethodCalls:IID


ICancelMethodCallsVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	     Cancel2@CT typedef proto \
		 pThis: ptr ICancelMethodCalls
	     Cancel2@MP typedef ptr Cancel2@CT
		 Cancel Cancel2@MP ?

	  TestCancel@CT typedef proto \
		 pThis: ptr ICancelMethodCalls
	  TestCancel@MP typedef ptr TestCancel@CT
	     TestCancel TestCancel@MP ?

    SetCancelTimeout@CT typedef proto \
		 pThis: ptr ICancelMethodCalls,
	     ulSeconds: ULONG
    SetCancelTimeout@MP typedef ptr SetCancelTimeout@CT
       SetCancelTimeout SetCancelTimeout@MP ?

	END_INTERFACE

ICancelMethodCallsVtbl	ENDS

LPICancelMethodCallsVtbl typedef ptr ICancelMethodCallsVtbl
ICancelMethodCalls	STRUC
lpVtbl			LPICancelMethodCallsVtbl ?
ICancelMethodCalls	ENDS



;HRESULT
ICancelMethodCalls_Cancel_Proxy proto _CType \
		 pThis: ptr ICancelMethodCalls


;void
ICancelMethodCalls_Cancel_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ICancelMethodCalls_TestCancel_Proxy proto _CType \
		 pThis: ptr ICancelMethodCalls


;void
ICancelMethodCalls_TestCancel_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
ICancelMethodCalls_SetCancelTimeout_Proxy proto _CType \
		 pThis: ptr ICancelMethodCalls,
	     ulSeconds: ULONG


;void
ICancelMethodCalls_SetCancelTimeout_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __ICancelMethodCalls_INTERFACE_DEFINED__


ifndef __IAsyncManager_INTERFACE_DEFINED__
__IAsyncManager_INTERFACE_DEFINED__ equ 1



;;typedef
;;enum tagDCOM_CALL_STATE
DCOM_NONE		equ 0
DCOM_CALL_COMPLETE	equ 0x1
DCOM_CALL_CANCELED	equ 0x2

externdef		IID_IAsyncManager:IID

IAsyncManagerVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	CompleteCall@CT typedef proto \
		 pThis: ptr IAsyncManager,
		Result: HRESULT
	CompleteCall@MP typedef ptr CompleteCall@CT
	   CompleteCall CompleteCall@MP ?

     GetCallContext2@CT typedef proto \
		 pThis: ptr IAsyncManager,
		  riid: REFIID,
	    pInterface: PVOID
     GetCallContext2@MP typedef ptr GetCallContext2@CT
	 GetCallContext GetCallContext2@MP ?

	   GetState2@CT typedef proto \
		 pThis: ptr IAsyncManager,
	 pulStateFlags: LPDWORD
	   GetState2@MP typedef ptr GetState2@CT
	       GetState GetState2@MP ?

	END_INTERFACE

IAsyncManagerVtbl	ENDS

LPIAsyncManagerVtbl	typedef ptr IAsyncManagerVtbl
IAsyncManager		STRUC
lpVtbl			LPIAsyncManagerVtbl ?
IAsyncManager		ENDS



;HRESULT
IAsyncManager_CompleteCall_Proxy proto _CType \
		 pThis: ptr IAsyncManager,
		Result: HRESULT


;void
IAsyncManager_CompleteCall_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IAsyncManager_GetCallContext_Proxy proto _CType \
		 pThis: ptr IAsyncManager,
		  riid: REFIID,
	    pInterface: PVOID


;void
IAsyncManager_GetCallContext_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IAsyncManager_GetState_Proxy proto _CType \
		 pThis: ptr IAsyncManager,
	 pulStateFlags: LPDWORD


;void
IAsyncManager_GetState_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IAsyncManager_INTERFACE_DEFINED__


ifndef __IWaitMultiple_INTERFACE_DEFINED__
__IWaitMultiple_INTERFACE_DEFINED__ equ 1




externdef		IID_IWaitMultiple:IID

IWaitMultipleVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	WaitMultiple@CT typedef proto \
		 pThis: ptr IWaitMultiple,
	       timeout: DWORD,
		 pSync: ptr ISynchronize
	WaitMultiple@MP typedef ptr WaitMultiple@CT
	   WaitMultiple WaitMultiple@MP ?

      AddSynchronize@CT typedef proto \
		 pThis: ptr IWaitMultiple,
		 pSync: ptr ISynchronize
      AddSynchronize@MP typedef ptr AddSynchronize@CT
	 AddSynchronize AddSynchronize@MP ?

	END_INTERFACE

IWaitMultipleVtbl	ENDS

LPIWaitMultipleVtbl	typedef ptr IWaitMultipleVtbl
IWaitMultiple		STRUC
lpVtbl			LPIWaitMultipleVtbl ?
IWaitMultiple		ENDS



;HRESULT
IWaitMultiple_WaitMultiple_Proxy proto _CType \
		 pThis: ptr IWaitMultiple,
	       timeout: DWORD,
		 pSync: ptr ISynchronize


;void
IWaitMultiple_WaitMultiple_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IWaitMultiple_AddSynchronize_Proxy proto _CType \
		 pThis: ptr IWaitMultiple,
		 pSync: ptr ISynchronize


;void
IWaitMultiple_AddSynchronize_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IWaitMultiple_INTERFACE_DEFINED__


ifndef __ISynchronizeEvent_INTERFACE_DEFINED__
__ISynchronizeEvent_INTERFACE_DEFINED__ equ 1




externdef		IID_ISynchronizeEvent:IID

ISynchronizeEventVtbl	STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

	    GetEvent@CT typedef proto \
		 pThis: ptr ISynchronizeEvent,
		pEvent: ptr HANDLE
	    GetEvent@MP typedef ptr GetEvent@CT
	       GetEvent GetEvent@MP ?

	END_INTERFACE

ISynchronizeEventVtbl	ENDS

LPISynchronizeEventVtbl typedef ptr ISynchronizeEventVtbl
ISynchronizeEvent	STRUC
lpVtbl			LPISynchronizeEventVtbl ?
ISynchronizeEvent	ENDS



;HRESULT
ISynchronizeEvent_GetEvent_Proxy proto _CType \
		 pThis: ptr ISynchronizeEvent,
		pEvent: ptr HANDLE


;void
ISynchronizeEvent_GetEvent_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __ISynchronizeEvent_INTERFACE_DEFINED__


ifndef __IUrlMon_INTERFACE_DEFINED__
__IUrlMon_INTERFACE_DEFINED__ equ 1




externdef		IID_IUrlMon:IID

IUrlMonVtbl		STRUC

	BEGIN_INTERFACE

	 QueryInterface QueryInterface@MP ?
		 AddRef AddRef@MP ?
		Release Release@MP ?

   AsyncGetClassBits@CT typedef proto \
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
   AsyncGetClassBits@MP typedef ptr AsyncGetClassBits@CT
      AsyncGetClassBits AsyncGetClassBits@MP ?

	END_INTERFACE

IUrlMonVtbl		ENDS

LPIUrlMonVtbl		typedef ptr IUrlMonVtbl
IUrlMon			STRUC
lpVtbl			LPIUrlMonVtbl ?
IUrlMon			ENDS



;HRESULT
IUrlMon_AsyncGetClassBits_Proxy proto _CType \
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
IUrlMon_AsyncGetClassBits_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IUrlMon_INTERFACE_DEFINED__


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

	GetClassInfo@CT typedef proto \
		 pThis: ptr IClassAccess,
		 clsid: REFCLSID,
	    QryContext: QUERYCONTEXT,
	  pPackageInfo: ptr PACKAGEINFO
	GetClassInfo@MP typedef ptr GetClassInfo@CT
	   GetClassInfo GetClassInfo@MP ?

    GetClassSpecInfo@CT typedef proto \
		 pThis: ptr IClassAccess,
	    pClassSpec: ptr uCLSSPEC,
	    QryContext: QUERYCONTEXT,
	  pPackageInfo: ptr PACKAGEINFO
    GetClassSpecInfo@MP typedef ptr GetClassSpecInfo@CT
       GetClassSpecInfo GetClassSpecInfo@MP ?

GetInstallablePackages@CT typedef proto \
		 pThis: ptr IClassAccess,
		 Count: DWORD,
	     pInfoList: ptr PUBLISHEDINFOLIST
GetInstallablePackages@MP typedef ptr GetInstallablePackages@CT
 GetInstallablePackages GetInstallablePackages@MP ?

	END_INTERFACE

IClassAccessVtbl	ENDS

LPIClassAccessVtbl	typedef ptr IClassAccessVtbl
IClassAccess		STRUC
lpVtbl			LPIClassAccessVtbl ?
IClassAccess		ENDS



;HRESULT
IClassAccess_GetClassInfo_Proxy proto _CType \
		 pThis: ptr IClassAccess,
		 clsid: REFCLSID,
	    QryContext: QUERYCONTEXT,
	  pPackageInfo: ptr PACKAGEINFO


;void
IClassAccess_GetClassInfo_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAccess_GetClassSpecInfo_Proxy proto _CType \
		 pThis: ptr IClassAccess,
	    pClassSpec: ptr uCLSSPEC,
	    QryContext: QUERYCONTEXT,
	  pPackageInfo: ptr PACKAGEINFO


;void
IClassAccess_GetClassSpecInfo_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAccess_GetInstallablePackages_Proxy proto _CType \
		 pThis: ptr IClassAccess,
		 Count: DWORD,
	     pInfoList: ptr PUBLISHEDINFOLIST


;void
IClassAccess_GetInstallablePackages_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IClassAccess_INTERFACE_DEFINED__


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

	 GetUpgrades@CT typedef proto \
		 pThis: ptr IClassRefresh,
	      cClasses: ULONG,
	    pClassList: ptr CLSID,
	      Platform: CSPLATFORM,
		Locale: LCID,
      pPackageInfoList: ptr PACKAGEINFOLIST
	 GetUpgrades@MP typedef ptr GetUpgrades@CT
	    GetUpgrades GetUpgrades@MP ?

      CommitUpgrades@CT typedef proto \
		 pThis: ptr IClassRefresh
      CommitUpgrades@MP typedef ptr CommitUpgrades@CT
	 CommitUpgrades CommitUpgrades@MP ?

	END_INTERFACE

IClassRefreshVtbl	ENDS

LPIClassRefreshVtbl	typedef ptr IClassRefreshVtbl
IClassRefresh		STRUC
lpVtbl			LPIClassRefreshVtbl ?
IClassRefresh		ENDS



;HRESULT
IClassRefresh_GetUpgrades_Proxy proto _CType \
		 pThis: ptr IClassRefresh,
	      cClasses: ULONG,
	    pClassList: ptr CLSID,
	      Platform: CSPLATFORM,
		Locale: LCID,
      pPackageInfoList: ptr PACKAGEINFOLIST


;void
IClassRefresh_GetUpgrades_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassRefresh_CommitUpgrades_Proxy proto _CType \
		 pThis: ptr IClassRefresh


;void
IClassRefresh_CommitUpgrades_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IClassRefresh_INTERFACE_DEFINED__





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
IEnumPackage_Next_Proxy proto _CType \
		 pThis: ptr IEnumPackage,
		  celt: ULONG,
		 rgelt: ptr PACKAGEDETAIL,
	  pceltFetched: LPDWORD


;void
IEnumPackage_Next_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumPackage_Skip_Proxy proto _CType \
		 pThis: ptr IEnumPackage,
		  celt: ULONG


;void
IEnumPackage_Skip_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumPackage_Reset_Proxy proto _CType \
		 pThis: ptr IEnumPackage


;void
IEnumPackage_Reset_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumPackage_Clone_Proxy proto _CType \
		 pThis: ptr IEnumPackage,
		ppenum: ptr IEnumPackage


;void
IEnumPackage_Clone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IEnumPackage_INTERFACE_DEFINED__


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
IEnumClass_Next_Proxy proto _CType \
		 pThis: ptr IEnumClass,
		  celt: ULONG,
		 rgelt: ptr CLASSDETAIL,
	  pceltFetched: LPDWORD


;void
IEnumClass_Next_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumClass_Skip_Proxy proto _CType \
		 pThis: ptr IEnumClass,
		  celt: ULONG


;void
IEnumClass_Skip_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumClass_Reset_Proxy proto _CType \
		 pThis: ptr IEnumClass


;void
IEnumClass_Reset_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IEnumClass_Clone_Proxy proto _CType \
		 pThis: ptr IEnumClass,
		ppenum: ptr IEnumClass


;void
IEnumClass_Clone_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IEnumClass_INTERFACE_DEFINED__





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

	    NewClass@CT typedef proto \
		 pThis: ptr IClassAdmin,
	  pClassDetail: ptr CLASSDETAIL
	    NewClass@MP typedef ptr NewClass@CT
	       NewClass NewClass@MP ?

	 DeleteClass@CT typedef proto \
		 pThis: ptr IClassAdmin,
	     guidClsId: REFCLSID
	 DeleteClass@MP typedef ptr DeleteClass@CT
	    DeleteClass DeleteClass@MP ?

	NewInterface@CT typedef proto \
		 pThis: ptr IClassAdmin,
		   iid: REFIID,
	       pszDesc: LPOLESTR,
	       psclsid: REFCLSID,
	     typelibid: REFCLSID
	NewInterface@MP typedef ptr NewInterface@CT
	   NewInterface NewInterface@MP ?

     DeleteInterface@CT typedef proto \
		 pThis: ptr IClassAdmin,
		   iid: REFIID
     DeleteInterface@MP typedef ptr DeleteInterface@CT
	DeleteInterface DeleteInterface@MP ?

	  NewPackage@CT typedef proto \
		 pThis: ptr IClassAdmin,
	pPackageDetail: ptr PACKAGEDETAIL
	  NewPackage@MP typedef ptr NewPackage@CT
	     NewPackage NewPackage@MP ?

       DeletePackage@CT typedef proto \
		 pThis: ptr IClassAdmin,
	pszPackageName: LPOLESTR
       DeletePackage@MP typedef ptr DeletePackage@CT
	  DeletePackage DeletePackage@MP ?

      GetClassesEnum@CT typedef proto \
		 pThis: ptr IClassAdmin,
	  ppIEnumClass: ptr IEnumClass
      GetClassesEnum@MP typedef ptr GetClassesEnum@CT
	 GetClassesEnum GetClassesEnum@MP ?

     GetPackagesEnum@CT typedef proto \
		 pThis: ptr IClassAdmin,
	     guidClsid: REFCLSID,
	     pszVendor: LPOLESTR,
	      Platform: CSPLATFORM,
	     dwContext: DWORD,
		Locale: LCID,
	ppIEnumPackage: ptr IEnumPackage
     GetPackagesEnum@MP typedef ptr GetPackagesEnum@CT
	GetPackagesEnum GetPackagesEnum@MP ?

     GetClassDetails@CT typedef proto \
		 pThis: ptr IClassAdmin,
	     guidClsId: REFCLSID,
	  pClassDetail: ptr CLASSDETAIL
     GetClassDetails@MP typedef ptr GetClassDetails@CT
	GetClassDetails GetClassDetails@MP ?

       GetIidDetails@CT typedef proto \
		 pThis: ptr IClassAdmin,
		   iid: REFIID,
	      ppszDesc: ptr LPOLESTR,
	       psClsid: ptr CLSID,
	    pTypeLibId: ptr CLSID
       GetIidDetails@MP typedef ptr GetIidDetails@CT
	  GetIidDetails GetIidDetails@MP ?

   GetPackageDetails@CT typedef proto \
		 pThis: ptr IClassAdmin,
	pszPackageName: LPOLESTR,
	pPackageDetail: ptr PACKAGEDETAIL
   GetPackageDetails@MP typedef ptr GetPackageDetails@CT
      GetPackageDetails GetPackageDetails@MP ?

	END_INTERFACE

IClassAdminVtbl		ENDS

LPIClassAdminVtbl	typedef ptr IClassAdminVtbl
IClassAdmin		STRUC
lpVtbl			LPIClassAdminVtbl ?
IClassAdmin		ENDS

;HRESULT
IClassAdmin_NewClass_Proxy proto _CType \
		 pThis: ptr IClassAdmin,
	  pClassDetail: ptr CLASSDETAIL


;void
IClassAdmin_NewClass_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAdmin_DeleteClass_Proxy proto _CType \
		 pThis: ptr IClassAdmin,
	     guidClsId: REFCLSID


;void
IClassAdmin_DeleteClass_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAdmin_NewInterface_Proxy proto _CType \
		 pThis: ptr IClassAdmin,
		   iid: REFIID,
	       pszDesc: LPOLESTR,
	       psclsid: REFCLSID,
	     typelibid: REFCLSID


;void
IClassAdmin_NewInterface_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAdmin_DeleteInterface_Proxy proto _CType \
		 pThis: ptr IClassAdmin,
		   iid: REFIID


;void
IClassAdmin_DeleteInterface_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAdmin_NewPackage_Proxy proto _CType \
		 pThis: ptr IClassAdmin,
	pPackageDetail: ptr PACKAGEDETAIL


;void
IClassAdmin_NewPackage_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAdmin_DeletePackage_Proxy proto _CType \
		 pThis: ptr IClassAdmin,
	pszPackageName: LPOLESTR


;void
IClassAdmin_DeletePackage_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAdmin_GetClassesEnum_Proxy proto _CType \
		 pThis: ptr IClassAdmin,
	  ppIEnumClass: ptr IEnumClass


;void
IClassAdmin_GetClassesEnum_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAdmin_GetPackagesEnum_Proxy proto _CType \
		 pThis: ptr IClassAdmin,
	     guidClsid: REFCLSID,
	     pszVendor: LPOLESTR,
	      Platform: CSPLATFORM,
	     dwContext: DWORD,
		Locale: LCID,
	ppIEnumPackage: ptr IEnumPackage


;void
IClassAdmin_GetPackagesEnum_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAdmin_GetClassDetails_Proxy proto _CType \
		 pThis: ptr IClassAdmin,
	     guidClsId: REFCLSID,
	  pClassDetail: ptr CLASSDETAIL


;void
IClassAdmin_GetClassDetails_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAdmin_GetIidDetails_Proxy proto _CType \
		 pThis: ptr IClassAdmin,
		   iid: REFIID,
	      ppszDesc: ptr LPOLESTR,
	       psClsid: ptr CLSID,
	    pTypeLibId: ptr CLSID


;void
IClassAdmin_GetIidDetails_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD


;HRESULT
IClassAdmin_GetPackageDetails_Proxy proto _CType \
		 pThis: ptr IClassAdmin,
	pszPackageName: LPOLESTR,
	pPackageDetail: ptr PACKAGEDETAIL


;void
IClassAdmin_GetPackageDetails_Stub proto _CType \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: LPDWORD



endif	;; __IClassAdmin_INTERFACE_DEFINED__





if ( _MSC_VER GE 800 )
;pragma warning(default:4201)
endif


externdef		__MIDL_itf_objidl_0072_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_objidl_0072_v0_0_s_ifspec:RPC_IF_HANDLE

;; Additional Prototypes for ALL interfaces

;DWORD
ASYNC_STGMEDIUM_UserSize proto _CType \
		      : LPDWORD,
		      : DWORD,
		      : ptr ASYNC_STGMEDIUM
;LPSTR
ASYNC_STGMEDIUM_UserMarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr ASYNC_STGMEDIUM
;LPSTR
ASYNC_STGMEDIUM_UserUnmarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr ASYNC_STGMEDIUM
;void
ASYNC_STGMEDIUM_UserFree proto _CType \
		      : LPDWORD,
		      : ptr ASYNC_STGMEDIUM

;DWORD
BSTR_UserSize proto _CType \
		      : LPDWORD,
		      : DWORD,
		      : ptr BSTR
;LPSTR
BSTR_UserMarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr BSTR
;LPSTR
BSTR_UserUnmarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr BSTR
;void
BSTR_UserFree proto _CType \
		      : LPDWORD,
		      : ptr BSTR

;DWORD
CLIPFORMAT_UserSize proto _CType \
		      : LPDWORD,
		      : DWORD,
		      : ptr CLIPFORMAT
;LPSTR
CLIPFORMAT_UserMarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT
;LPSTR
CLIPFORMAT_UserUnmarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT
;void
CLIPFORMAT_UserFree proto _CType \
		      : LPDWORD,
		      : ptr CLIPFORMAT

;DWORD
FLAG_STGMEDIUM_UserSize proto _CType \
		      : LPDWORD,
		      : DWORD,
		      : ptr FLAG_STGMEDIUM
;LPSTR
FLAG_STGMEDIUM_UserMarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr FLAG_STGMEDIUM
;LPSTR
FLAG_STGMEDIUM_UserUnmarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr FLAG_STGMEDIUM
;void
FLAG_STGMEDIUM_UserFree proto _CType \
		      : LPDWORD,
		      : ptr FLAG_STGMEDIUM

;DWORD
SNB_UserSize proto _CType \
		      : LPDWORD,
		      : DWORD,
		      : ptr SNB
;LPSTR
SNB_UserMarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr SNB
;LPSTR
SNB_UserUnmarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr SNB
;void
SNB_UserFree proto _CType \
		      : LPDWORD,
		      : ptr SNB

;DWORD
STGMEDIUM_UserSize proto _CType \
		      : LPDWORD,
		      : DWORD,
		      : ptr STGMEDIUM
;LPSTR
STGMEDIUM_UserMarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr STGMEDIUM
;LPSTR
STGMEDIUM_UserUnmarshal proto _CType \
		      : LPDWORD,
		      : LPSTR,
		      : ptr STGMEDIUM
;void
STGMEDIUM_UserFree proto _CType \
		      : LPDWORD,
		      : ptr STGMEDIUM

;HRESULT
IEnumUnknown_Next_Proxy proto _CType \
		 pThis: ptr IEnumUnknown,
		  celt: ULONG,
		 rgelt: ptr IUnknown,
	  pceltFetched: LPDWORD


;HRESULT
IEnumUnknown_Next_Stub proto _CType \
		 pThis: ptr IEnumUnknown,
		  celt: ULONG,
		 rgelt: ptr IUnknown,
	  pceltFetched: LPDWORD

;HRESULT
IBindCtx_SetBindOptions_Proxy proto _CType \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS


;HRESULT
IBindCtx_SetBindOptions_Stub proto _CType \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS2

;HRESULT
IBindCtx_GetBindOptions_Proxy proto _CType \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS


;HRESULT
IBindCtx_GetBindOptions_Stub proto _CType \
		 pThis: ptr IBindCtx,
	     pbindopts: ptr BIND_OPTS2

;HRESULT
IEnumMoniker_Next_Proxy proto _CType \
		 pThis: ptr IEnumMoniker,
		  celt: ULONG,
		 rgelt: ptr IMoniker,
	  pceltFetched: LPDWORD


;HRESULT
IEnumMoniker_Next_Stub proto _CType \
		 pThis: ptr IEnumMoniker,
		  celt: ULONG,
		 rgelt: ptr IMoniker,
	  pceltFetched: LPDWORD

;BOOL
IRunnableObject_IsRunning_Proxy proto _CType \
		 pThis: ptr IRunnableObject


;HRESULT
IRunnableObject_IsRunning_Stub proto _CType \
		 pThis: ptr IRunnableObject

;HRESULT
IMoniker_BindToObject_Proxy proto _CType \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	    riidResult: REFIID,
	     ppvResult: PVOID


;HRESULT
IMoniker_BindToObject_Stub proto _CType \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
	    riidResult: REFIID,
	     ppvResult: ptr IUnknown

;HRESULT
IMoniker_BindToStorage_Proxy proto _CType \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
		  riid: REFIID,
		ppvObj: PVOID


;HRESULT
IMoniker_BindToStorage_Stub proto _CType \
		 pThis: ptr IMoniker,
		   pbc: ptr IBindCtx,
	     pmkToLeft: ptr IMoniker,
		  riid: REFIID,
		ppvObj: ptr IUnknown

;HRESULT
IEnumString_Next_Proxy proto _CType \
		 pThis: ptr IEnumString,
		  celt: ULONG,
		 rgelt: ptr LPOLESTR,
	  pceltFetched: LPDWORD


;HRESULT
IEnumString_Next_Stub proto _CType \
		 pThis: ptr IEnumString,
		  celt: ULONG,
		 rgelt: ptr LPOLESTR,
	  pceltFetched: LPDWORD

;HRESULT
ISequentialStream_Read_Proxy proto _CType \
		 pThis: ptr ISequentialStream,
		    pv: PVOID,
		    cb: ULONG,
	       pcbRead: LPDWORD


;HRESULT
ISequentialStream_Read_Stub proto _CType \
		 pThis: ptr ISequentialStream,
		    pv: LPBYTE,
		    cb: ULONG,
	       pcbRead: LPDWORD

;HRESULT
ISequentialStream_Write_Proxy proto _CType \
		 pThis: ptr ISequentialStream,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;HRESULT
ISequentialStream_Write_Stub proto _CType \
		 pThis: ptr ISequentialStream,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD

;HRESULT
IStream_Seek_Proxy proto _CType \
		 pThis: ptr IStream,
	      dlibMove: LARGE_INTEGER,
	      dwOrigin: DWORD,
       plibNewPosition: ptr ULARGE_INTEGER


;HRESULT
IStream_Seek_Stub proto _CType \
		 pThis: ptr IStream,
	      dlibMove: LARGE_INTEGER,
	      dwOrigin: DWORD,
       plibNewPosition: ptr ULARGE_INTEGER

;HRESULT
IStream_CopyTo_Proxy proto _CType \
		 pThis: ptr IStream,
		  pstm: ptr IStream,
		    cb: ULARGE_INTEGER,
	       pcbRead: ptr ULARGE_INTEGER,
	    pcbWritten: ptr ULARGE_INTEGER


;HRESULT
IStream_CopyTo_Stub proto _CType \
		 pThis: ptr IStream,
		  pstm: ptr IStream,
		    cb: ULARGE_INTEGER,
	       pcbRead: ptr ULARGE_INTEGER,
	    pcbWritten: ptr ULARGE_INTEGER

;HRESULT
IEnumSTATSTG_Next_Proxy proto _CType \
		 pThis: ptr IEnumSTATSTG,
		  celt: ULONG,
		 rgelt: ptr STATSTG,
	  pceltFetched: LPDWORD


;HRESULT
IEnumSTATSTG_Next_Stub proto _CType \
		 pThis: ptr IEnumSTATSTG,
		  celt: ULONG,
		 rgelt: ptr STATSTG,
	  pceltFetched: LPDWORD

;HRESULT
IStorage_OpenStream_Proxy proto _CType \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	     reserved1: PVOID,
	       grfMode: DWORD,
	     reserved2: DWORD,
		 ppstm: ptr IStream


;HRESULT
IStorage_OpenStream_Stub proto _CType \
		 pThis: ptr IStorage,
	      pwcsName: ptr OLECHAR,
	   cbReserved1: DWORD,
	     reserved1: LPBYTE,
	       grfMode: DWORD,
	     reserved2: DWORD,
		 ppstm: ptr IStream

;HRESULT
IStorage_EnumElements_Proxy proto _CType \
		 pThis: ptr IStorage,
	     reserved1: DWORD,
	     reserved2: PVOID,
	     reserved3: DWORD,
		ppenum: ptr IEnumSTATSTG


;HRESULT
IStorage_EnumElements_Stub proto _CType \
		 pThis: ptr IStorage,
	     reserved1: DWORD,
	   cbReserved2: DWORD,
	     reserved2: LPBYTE,
	     reserved3: DWORD,
		ppenum: ptr IEnumSTATSTG

;HRESULT
ILockBytes_ReadAt_Proxy proto _CType \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: PVOID,
		    cb: ULONG,
	       pcbRead: LPDWORD


;HRESULT
ILockBytes_ReadAt_Stub proto _CType \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	       pcbRead: LPDWORD

;HRESULT
ILockBytes_WriteAt_Proxy proto _CType \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;HRESULT
ILockBytes_WriteAt_Stub proto _CType \
		 pThis: ptr ILockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD

;HRESULT
IEnumFORMATETC_Next_Proxy proto _CType \
		 pThis: ptr IEnumFORMATETC,
		  celt: ULONG,
		 rgelt: ptr FORMATETC,
	  pceltFetched: LPDWORD


;HRESULT
IEnumFORMATETC_Next_Stub proto _CType \
		 pThis: ptr IEnumFORMATETC,
		  celt: ULONG,
		 rgelt: ptr FORMATETC,
	  pceltFetched: LPDWORD

;HRESULT
IEnumSTATDATA_Next_Proxy proto _CType \
		 pThis: ptr IEnumSTATDATA,
		  celt: ULONG,
		 rgelt: ptr STATDATA,
	  pceltFetched: LPDWORD


;HRESULT
IEnumSTATDATA_Next_Stub proto _CType \
		 pThis: ptr IEnumSTATDATA,
		  celt: ULONG,
		 rgelt: ptr STATDATA,
	  pceltFetched: LPDWORD

;void
IAdviseSink_OnDataChange_Proxy proto _CType \
		 pThis: ptr IAdviseSink,
	    pFormatetc: ptr FORMATETC,
	       pStgmed: ptr STGMEDIUM


;HRESULT
IAdviseSink_OnDataChange_Stub proto _CType \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
	    pFormatetc: ptr FORMATETC,
	       pStgmed: ptr ASYNC_STGMEDIUM

;void
IAdviseSink_OnViewChange_Proxy proto _CType \
		 pThis: ptr IAdviseSink,
	      dwAspect: DWORD,
		lindex: LONG


;HRESULT
IAdviseSink_OnViewChange_Stub proto _CType \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
	      dwAspect: DWORD,
		lindex: LONG

;void
IAdviseSink_OnRename_Proxy proto _CType \
		 pThis: ptr IAdviseSink,
		   pmk: ptr IMoniker


;HRESULT
IAdviseSink_OnRename_Stub proto _CType \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager,
		   pmk: ptr IMoniker

;void
IAdviseSink_OnSave_Proxy proto _CType \
		 pThis: ptr IAdviseSink


;HRESULT
IAdviseSink_OnSave_Stub proto _CType \
		 pThis: ptr IAdviseSink,
		 ppIAM: ptr IAsyncManager

;void
IAdviseSink_OnClose_Proxy proto _CType \
		 pThis: ptr IAdviseSink


;HRESULT
IAdviseSink_OnClose_Stub proto _CType \
		 pThis: ptr IAdviseSink

;void
IAdviseSink2_OnLinkSrcChange_Proxy proto _CType \
		 pThis: ptr IAdviseSink2,
		   pmk: ptr IMoniker


;HRESULT
IAdviseSink2_OnLinkSrcChange_Stub proto _CType \
		 pThis: ptr IAdviseSink2,
		 ppIAM: ptr IAsyncManager,
		   pmk: ptr IMoniker

;HRESULT
IDataObject_GetData_Proxy proto _CType \
		 pThis: ptr IDataObject,
	  pformatetcIn: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM


;HRESULT
IDataObject_GetData_Stub proto _CType \
		 pThis: ptr IDataObject,
	  pformatetcIn: ptr FORMATETC,
	 pRemoteMedium: ptr STGMEDIUM

;HRESULT
IDataObject_GetDataHere_Proxy proto _CType \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM


;HRESULT
IDataObject_GetDataHere_Stub proto _CType \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	 pRemoteMedium: ptr STGMEDIUM

;HRESULT
IDataObject_SetData_Proxy proto _CType \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM,
	      fRelease: BOOL


;HRESULT
IDataObject_SetData_Stub proto _CType \
		 pThis: ptr IDataObject,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr FLAG_STGMEDIUM,
	      fRelease: BOOL

;HRESULT
IEnumSTATPROPSTG_Next_Proxy proto _CType \
		 pThis: ptr IEnumSTATPROPSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSTG,
	  pceltFetched: LPDWORD


;HRESULT
IEnumSTATPROPSTG_Next_Stub proto _CType \
		 pThis: ptr IEnumSTATPROPSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSTG,
	  pceltFetched: LPDWORD

;HRESULT
IEnumSTATPROPSETSTG_Next_Proxy proto _CType \
		 pThis: ptr IEnumSTATPROPSETSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSETSTG,
	  pceltFetched: LPDWORD


;HRESULT
IEnumSTATPROPSETSTG_Next_Stub proto _CType \
		 pThis: ptr IEnumSTATPROPSETSTG,
		  celt: ULONG,
		 rgelt: ptr STATPROPSETSTG,
	  pceltFetched: LPDWORD

;HRESULT
IFillLockBytes_FillAppend_Proxy proto _CType \
		 pThis: ptr IFillLockBytes,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;HRESULT
IFillLockBytes_FillAppend_Stub proto _CType \
		 pThis: ptr IFillLockBytes,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD

;HRESULT
IFillLockBytes_FillAt_Proxy proto _CType \
		 pThis: ptr IFillLockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: PVOID,
		    cb: ULONG,
	    pcbWritten: LPDWORD


;HRESULT
IFillLockBytes_FillAt_Stub proto _CType \
		 pThis: ptr IFillLockBytes,
	      ulOffset: ULARGE_INTEGER,
		    pv: LPBYTE,
		    cb: ULONG,
	    pcbWritten: LPDWORD



;; end of Additional Prototypes
.list

endif
