ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 440
endif
include rpc.inc
include rpcndr.inc
ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.inc>
endif 

ifndef COM_NO_WINDOWS_H
include windows.inc
include ole2.inc
endif 
ifndef __oleidl_h__
.xlist
__oleidl_h__ equ 1


ifndef __IOleAdviseHolder_FWD_DEFINED__
__IOleAdviseHolder_FWD_DEFINED__ equ 1
endif	


ifndef __IOleCache_FWD_DEFINED__
__IOleCache_FWD_DEFINED__ equ 1
endif	


ifndef __IOleCache2_FWD_DEFINED__
__IOleCache2_FWD_DEFINED__ equ 1
endif	


ifndef __IOleCacheControl_FWD_DEFINED__
__IOleCacheControl_FWD_DEFINED__ equ 1
endif	


ifndef __IParseDisplayName_FWD_DEFINED__
__IParseDisplayName_FWD_DEFINED__ equ 1
endif	


ifndef __IOleContainer_FWD_DEFINED__
__IOleContainer_FWD_DEFINED__ equ 1
endif	


ifndef __IOleClientSite_FWD_DEFINED__
__IOleClientSite_FWD_DEFINED__ equ 1
endif	


ifndef __IOleObject_FWD_DEFINED__
__IOleObject_FWD_DEFINED__ equ 1
endif	


ifndef __IOleWindow_FWD_DEFINED__
__IOleWindow_FWD_DEFINED__ equ 1
endif	


ifndef __IOleLink_FWD_DEFINED__
__IOleLink_FWD_DEFINED__ equ 1
endif	


ifndef __IOleItemContainer_FWD_DEFINED__
__IOleItemContainer_FWD_DEFINED__ equ 1
endif	


ifndef __IOleInPlaceUIWindow_FWD_DEFINED__
__IOleInPlaceUIWindow_FWD_DEFINED__ equ 1
endif	


ifndef __IOleInPlaceActiveObject_FWD_DEFINED__
__IOleInPlaceActiveObject_FWD_DEFINED__ equ 1
endif	


ifndef __IOleInPlaceFrame_FWD_DEFINED__
__IOleInPlaceFrame_FWD_DEFINED__ equ 1
endif	


ifndef __IOleInPlaceObject_FWD_DEFINED__
__IOleInPlaceObject_FWD_DEFINED__ equ 1
endif	


ifndef __IOleInPlaceSite_FWD_DEFINED__
__IOleInPlaceSite_FWD_DEFINED__ equ 1
endif	


ifndef __IContinue_FWD_DEFINED__
__IContinue_FWD_DEFINED__ equ 1
endif	


ifndef __IViewObject_FWD_DEFINED__
__IViewObject_FWD_DEFINED__ equ 1
endif	


ifndef __IViewObject2_FWD_DEFINED__
__IViewObject2_FWD_DEFINED__ equ 1
endif	


ifndef __IDropSource_FWD_DEFINED__
__IDropSource_FWD_DEFINED__ equ 1
endif	


ifndef __IDropTarget_FWD_DEFINED__
__IDropTarget_FWD_DEFINED__ equ 1
endif	


ifndef __IEnumOLEVERB_FWD_DEFINED__
__IEnumOLEVERB_FWD_DEFINED__ equ 1
endif	


include objidl.inc
.xlist

;PVOID
;void
MIDL_user_free proto WINAPI \
		      : PVOID



externdef		__MIDL_itf_oleidl_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_oleidl_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IOleAdviseHolder_INTERFACE_DEFINED__
__IOleAdviseHolder_INTERFACE_DEFINED__ equ 1



LPOLEADVISEHOLDER	typedef ptr IOleAdviseHolder


externdef		IID_IOleAdviseHolder:IID


IOleAdviseHolderVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface30@CT typedef proto \
		 pThis: ptr IOleAdviseHolder,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface30@MP typedef ptr QueryInterface30@CT
	 QueryInterface QueryInterface30@MP ?

	    AddRef30@CT typedef proto \
		 pThis: ptr IOleAdviseHolder

	    AddRef30@MP typedef ptr AddRef30@CT
		 AddRef AddRef30@MP ?

	   Release30@CT typedef proto \
		 pThis: ptr IOleAdviseHolder

	   Release30@MP typedef ptr Release30@CT
		Release Release30@MP ?

	    Advise30@CT typedef proto \
		 pThis: ptr IOleAdviseHolder,
	       pAdvise: ptr IAdviseSink,
	 pdwConnection: ptr DWORD

	    Advise30@MP typedef ptr Advise30@CT
		 Advise Advise30@MP ?

	  Unadvise30@CT typedef proto \
		 pThis: ptr IOleAdviseHolder,
	  dwConnection: DWORD

	  Unadvise30@MP typedef ptr Unadvise30@CT
	       Unadvise Unadvise30@MP ?

	EnumAdvise30@CT typedef proto \
		 pThis: ptr IOleAdviseHolder,
	  ppenumAdvise: ptr IEnumSTATDATA

	EnumAdvise30@MP typedef ptr EnumAdvise30@CT
	     EnumAdvise EnumAdvise30@MP ?

      SendOnRename30@CT typedef proto \
		 pThis: ptr IOleAdviseHolder,
		   pmk: ptr IMoniker

      SendOnRename30@MP typedef ptr SendOnRename30@CT
	   SendOnRename SendOnRename30@MP ?

	SendOnSave30@CT typedef proto \
		 pThis: ptr IOleAdviseHolder

	SendOnSave30@MP typedef ptr SendOnSave30@CT
	     SendOnSave SendOnSave30@MP ?

       SendOnClose30@CT typedef proto \
		 pThis: ptr IOleAdviseHolder

       SendOnClose30@MP typedef ptr SendOnClose30@CT
	    SendOnClose SendOnClose30@MP ?

	END_INTERFACE

IOleAdviseHolderVtbl	ENDS

LPIOleAdviseHolderVtbl	typedef ptr IOleAdviseHolderVtbl
IOleAdviseHolder	STRUC
lpVtbl			LPIOleAdviseHolderVtbl ?
IOleAdviseHolder	ENDS






;HRESULT
IOleAdviseHolder_Advise_Proxy proto WINAPI \
		 pThis: ptr IOleAdviseHolder,
	       pAdvise: ptr IAdviseSink,
	 pdwConnection: ptr DWORD



;void
IOleAdviseHolder_Advise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleAdviseHolder_Unadvise_Proxy proto WINAPI \
		 pThis: ptr IOleAdviseHolder,
	  dwConnection: DWORD



;void
IOleAdviseHolder_Unadvise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleAdviseHolder_EnumAdvise_Proxy proto WINAPI \
		 pThis: ptr IOleAdviseHolder,
	  ppenumAdvise: ptr IEnumSTATDATA



;void
IOleAdviseHolder_EnumAdvise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleAdviseHolder_SendOnRename_Proxy proto WINAPI \
		 pThis: ptr IOleAdviseHolder,
		   pmk: ptr IMoniker



;void
IOleAdviseHolder_SendOnRename_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleAdviseHolder_SendOnSave_Proxy proto WINAPI \
		 pThis: ptr IOleAdviseHolder



;void
IOleAdviseHolder_SendOnSave_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleAdviseHolder_SendOnClose_Proxy proto WINAPI \
		 pThis: ptr IOleAdviseHolder



;void
IOleAdviseHolder_SendOnClose_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleCache_INTERFACE_DEFINED__
__IOleCache_INTERFACE_DEFINED__ equ 1



LPOLECACHE		typedef ptr IOleCache


externdef		IID_IOleCache:IID


IOleCacheVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface31@CT typedef proto \
		 pThis: ptr IOleCache,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface31@MP typedef ptr QueryInterface31@CT
	 QueryInterface QueryInterface31@MP ?

	    AddRef31@CT typedef proto \
		 pThis: ptr IOleCache

	    AddRef31@MP typedef ptr AddRef31@CT
		 AddRef AddRef31@MP ?

	   Release31@CT typedef proto \
		 pThis: ptr IOleCache

	   Release31@MP typedef ptr Release31@CT
		Release Release31@MP ?

	     Cache31@CT typedef proto \
		 pThis: ptr IOleCache,
	    pformatetc: ptr FORMATETC,
		  advf: DWORD,
	 pdwConnection: ptr DWORD

	     Cache31@MP typedef ptr Cache31@CT
		  Cache Cache31@MP ?

	   Uncache31@CT typedef proto \
		 pThis: ptr IOleCache,
	  dwConnection: DWORD

	   Uncache31@MP typedef ptr Uncache31@CT
		Uncache Uncache31@MP ?

	 EnumCache31@CT typedef proto \
		 pThis: ptr IOleCache,
	ppenumSTATDATA: ptr IEnumSTATDATA

	 EnumCache31@MP typedef ptr EnumCache31@CT
	      EnumCache EnumCache31@MP ?

	 InitCache31@CT typedef proto \
		 pThis: ptr IOleCache,
	   pDataObject: ptr IDataObject

	 InitCache31@MP typedef ptr InitCache31@CT
	      InitCache InitCache31@MP ?

	   SetData31@CT typedef proto \
		 pThis: ptr IOleCache,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM,
	      fRelease: BOOL

	   SetData31@MP typedef ptr SetData31@CT
		SetData SetData31@MP ?

	END_INTERFACE

IOleCacheVtbl		ENDS

LPIOleCacheVtbl		typedef ptr IOleCacheVtbl
IOleCache		STRUC
lpVtbl			LPIOleCacheVtbl ?
IOleCache		ENDS






;HRESULT
IOleCache_Cache_Proxy proto WINAPI \
		 pThis: ptr IOleCache,
	    pformatetc: ptr FORMATETC,
		  advf: DWORD,
	 pdwConnection: ptr DWORD



;void
IOleCache_Cache_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleCache_Uncache_Proxy proto WINAPI \
		 pThis: ptr IOleCache,
	  dwConnection: DWORD



;void
IOleCache_Uncache_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleCache_EnumCache_Proxy proto WINAPI \
		 pThis: ptr IOleCache,
	ppenumSTATDATA: ptr IEnumSTATDATA



;void
IOleCache_EnumCache_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleCache_InitCache_Proxy proto WINAPI \
		 pThis: ptr IOleCache,
	   pDataObject: ptr IDataObject



;void
IOleCache_InitCache_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleCache_SetData_Proxy proto WINAPI \
		 pThis: ptr IOleCache,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM,
	      fRelease: BOOL



;void
IOleCache_SetData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleCache2_INTERFACE_DEFINED__
__IOleCache2_INTERFACE_DEFINED__ equ 1



LPOLECACHE2		typedef ptr IOleCache2

UPDFCACHE_NODATACACHE	equ ( 0x1 )

UPDFCACHE_ONSAVECACHE	equ ( 0x2 )

UPDFCACHE_ONSTOPCACHE	equ ( 0x4 )

UPDFCACHE_NORMALCACHE	equ ( 0x8 )

UPDFCACHE_IFBLANK	equ ( 0x10 )

UPDFCACHE_ONLYIFBLANK	equ ( 0x80000000 )

UPDFCACHE_IFBLANKORONSAVECACHE equ ( UPDFCACHE_IFBANK OR UPDFCACHE_ONSAVECACHE )

UPDFCACHE_ALL		equ ( ( DWORD  ) NOT UPDFCACHE_ONLYIFBANK )

UPDFCACHE_ALLBUTNODATACACHE equ ( UPDFCACHE_ALL AND ( DWORD  ) NOT UPDFCACHE_NODATACACHE )

;typedef /* [v1_enum] */ enum tagDISCARDCACHE

DISCARDCACHE_SAVEIFDIRTY equ 0
DISCARDCACHE_NOSAVE	equ 1


externdef		IID_IOleCache2:IID


IOleCache2Vtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface32@CT typedef proto \
		 pThis: ptr IOleCache2,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface32@MP typedef ptr QueryInterface32@CT
	 QueryInterface QueryInterface32@MP ?

	    AddRef32@CT typedef proto \
		 pThis: ptr IOleCache2

	    AddRef32@MP typedef ptr AddRef32@CT
		 AddRef AddRef32@MP ?

	   Release32@CT typedef proto \
		 pThis: ptr IOleCache2

	   Release32@MP typedef ptr Release32@CT
		Release Release32@MP ?

	     Cache32@CT typedef proto \
		 pThis: ptr IOleCache2,
	    pformatetc: ptr FORMATETC,
		  advf: DWORD,
	 pdwConnection: ptr DWORD

	     Cache32@MP typedef ptr Cache32@CT
		  Cache Cache32@MP ?

	   Uncache32@CT typedef proto \
		 pThis: ptr IOleCache2,
	  dwConnection: DWORD

	   Uncache32@MP typedef ptr Uncache32@CT
		Uncache Uncache32@MP ?

	 EnumCache32@CT typedef proto \
		 pThis: ptr IOleCache2,
	ppenumSTATDATA: ptr IEnumSTATDATA

	 EnumCache32@MP typedef ptr EnumCache32@CT
	      EnumCache EnumCache32@MP ?

	 InitCache32@CT typedef proto \
		 pThis: ptr IOleCache2,
	   pDataObject: ptr IDataObject

	 InitCache32@MP typedef ptr InitCache32@CT
	      InitCache InitCache32@MP ?

	   SetData32@CT typedef proto \
		 pThis: ptr IOleCache2,
	    pformatetc: ptr FORMATETC,
	       pmedium: ptr STGMEDIUM,
	      fRelease: BOOL

	   SetData32@MP typedef ptr SetData32@CT
		SetData SetData32@MP ?

       UpdateCache32@CT typedef proto \
		 pThis: ptr IOleCache2,
	   pDataObject: LPDATAOBJECT,
	       grfUpdf: DWORD,
	     pReserved: LPVOID

       UpdateCache32@MP typedef ptr UpdateCache32@CT
	    UpdateCache UpdateCache32@MP ?

      DiscardCache32@CT typedef proto \
		 pThis: ptr IOleCache2,
      dwDiscardOptions: DWORD

      DiscardCache32@MP typedef ptr DiscardCache32@CT
	   DiscardCache DiscardCache32@MP ?

	END_INTERFACE

IOleCache2Vtbl		ENDS

LPIOleCache2Vtbl	typedef ptr IOleCache2Vtbl
IOleCache2		STRUC
lpVtbl			LPIOleCache2Vtbl ?
IOleCache2		ENDS






;HRESULT
IOleCache2_RemoteUpdateCache_Proxy proto WINAPI \
		 pThis: ptr IOleCache2,
	   pDataObject: LPDATAOBJECT,
	       grfUpdf: DWORD,
	     pReserved: DWORD



;void
IOleCache2_RemoteUpdateCache_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleCache2_DiscardCache_Proxy proto WINAPI \
		 pThis: ptr IOleCache2,
      dwDiscardOptions: DWORD



;void
IOleCache2_DiscardCache_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleCacheControl_INTERFACE_DEFINED__
__IOleCacheControl_INTERFACE_DEFINED__ equ 1



LPOLECACHECONTROL	typedef ptr IOleCacheControl


externdef		IID_IOleCacheControl:IID


IOleCacheControlVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface33@CT typedef proto \
		 pThis: ptr IOleCacheControl,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface33@MP typedef ptr QueryInterface33@CT
	 QueryInterface QueryInterface33@MP ?

	    AddRef33@CT typedef proto \
		 pThis: ptr IOleCacheControl

	    AddRef33@MP typedef ptr AddRef33@CT
		 AddRef AddRef33@MP ?

	   Release33@CT typedef proto \
		 pThis: ptr IOleCacheControl

	   Release33@MP typedef ptr Release33@CT
		Release Release33@MP ?

	     OnRun33@CT typedef proto \
		 pThis: ptr IOleCacheControl,
	   pDataObject: LPDATAOBJECT

	     OnRun33@MP typedef ptr OnRun33@CT
		  OnRun OnRun33@MP ?

	    OnStop33@CT typedef proto \
		 pThis: ptr IOleCacheControl

	    OnStop33@MP typedef ptr OnStop33@CT
		 OnStop OnStop33@MP ?

	END_INTERFACE

IOleCacheControlVtbl	ENDS

LPIOleCacheControlVtbl	typedef ptr IOleCacheControlVtbl
IOleCacheControl	STRUC
lpVtbl			LPIOleCacheControlVtbl ?
IOleCacheControl	ENDS






;HRESULT
IOleCacheControl_OnRun_Proxy proto WINAPI \
		 pThis: ptr IOleCacheControl,
	   pDataObject: LPDATAOBJECT



;void
IOleCacheControl_OnRun_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleCacheControl_OnStop_Proxy proto WINAPI \
		 pThis: ptr IOleCacheControl



;void
IOleCacheControl_OnStop_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IParseDisplayName_INTERFACE_DEFINED__
__IParseDisplayName_INTERFACE_DEFINED__ equ 1



LPPARSEDISPLAYNAME	typedef ptr IParseDisplayName


externdef		IID_IParseDisplayName:IID


IParseDisplayNameVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface34@CT typedef proto \
		 pThis: ptr IParseDisplayName,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface34@MP typedef ptr QueryInterface34@CT
	 QueryInterface QueryInterface34@MP ?

	    AddRef34@CT typedef proto \
		 pThis: ptr IParseDisplayName

	    AddRef34@MP typedef ptr AddRef34@CT
		 AddRef AddRef34@MP ?

	   Release34@CT typedef proto \
		 pThis: ptr IParseDisplayName

	   Release34@MP typedef ptr Release34@CT
		Release Release34@MP ?

  ParseDisplayName34@CT typedef proto \
		 pThis: ptr IParseDisplayName,
		   pbc: ptr IBindCtx,
	pszDisplayName: LPOLESTR,
	      pchEaten: ptr ULONG,
	       ppmkOut: ptr IMoniker

  ParseDisplayName34@MP typedef ptr ParseDisplayName34@CT
       ParseDisplayName ParseDisplayName34@MP ?

	END_INTERFACE

IParseDisplayNameVtbl	ENDS

LPIParseDisplayNameVtbl typedef ptr IParseDisplayNameVtbl
IParseDisplayName	STRUC
lpVtbl			LPIParseDisplayNameVtbl ?
IParseDisplayName	ENDS






;HRESULT
IParseDisplayName_ParseDisplayName_Proxy proto WINAPI \
		 pThis: ptr IParseDisplayName,
		   pbc: ptr IBindCtx,
	pszDisplayName: LPOLESTR,
	      pchEaten: ptr ULONG,
	       ppmkOut: ptr IMoniker



;void
IParseDisplayName_ParseDisplayName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleContainer_INTERFACE_DEFINED__
__IOleContainer_INTERFACE_DEFINED__ equ 1



LPOLECONTAINER		typedef ptr IOleContainer


externdef		IID_IOleContainer:IID


IOleContainerVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface35@CT typedef proto \
		 pThis: ptr IOleContainer,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface35@MP typedef ptr QueryInterface35@CT
	 QueryInterface QueryInterface35@MP ?

	    AddRef35@CT typedef proto \
		 pThis: ptr IOleContainer

	    AddRef35@MP typedef ptr AddRef35@CT
		 AddRef AddRef35@MP ?

	   Release35@CT typedef proto \
		 pThis: ptr IOleContainer

	   Release35@MP typedef ptr Release35@CT
		Release Release35@MP ?

  ParseDisplayName35@CT typedef proto \
		 pThis: ptr IOleContainer,
		   pbc: ptr IBindCtx,
	pszDisplayName: LPOLESTR,
	      pchEaten: ptr ULONG,
	       ppmkOut: ptr IMoniker

  ParseDisplayName35@MP typedef ptr ParseDisplayName35@CT
       ParseDisplayName ParseDisplayName35@MP ?

       EnumObjects35@CT typedef proto \
		 pThis: ptr IOleContainer,
	      grfFlags: DWORD,
		ppenum: ptr IEnumUnknown

       EnumObjects35@MP typedef ptr EnumObjects35@CT
	    EnumObjects EnumObjects35@MP ?

     LockContainer35@CT typedef proto \
		 pThis: ptr IOleContainer,
		 fLock: BOOL

     LockContainer35@MP typedef ptr LockContainer35@CT
	  LockContainer LockContainer35@MP ?

	END_INTERFACE

IOleContainerVtbl	ENDS

LPIOleContainerVtbl	typedef ptr IOleContainerVtbl
IOleContainer		STRUC
lpVtbl			LPIOleContainerVtbl ?
IOleContainer		ENDS






;HRESULT
IOleContainer_EnumObjects_Proxy proto WINAPI \
		 pThis: ptr IOleContainer,
	      grfFlags: DWORD,
		ppenum: ptr IEnumUnknown



;void
IOleContainer_EnumObjects_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleContainer_LockContainer_Proxy proto WINAPI \
		 pThis: ptr IOleContainer,
		 fLock: BOOL



;void
IOleContainer_LockContainer_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleClientSite_INTERFACE_DEFINED__
__IOleClientSite_INTERFACE_DEFINED__ equ 1



LPOLECLIENTSITE		typedef ptr IOleClientSite


externdef		IID_IOleClientSite:IID


IOleClientSiteVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface36@CT typedef proto \
		 pThis: ptr IOleClientSite,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface36@MP typedef ptr QueryInterface36@CT
	 QueryInterface QueryInterface36@MP ?

	    AddRef36@CT typedef proto \
		 pThis: ptr IOleClientSite

	    AddRef36@MP typedef ptr AddRef36@CT
		 AddRef AddRef36@MP ?

	   Release36@CT typedef proto \
		 pThis: ptr IOleClientSite

	   Release36@MP typedef ptr Release36@CT
		Release Release36@MP ?

	SaveObject36@CT typedef proto \
		 pThis: ptr IOleClientSite

	SaveObject36@MP typedef ptr SaveObject36@CT
	     SaveObject SaveObject36@MP ?

	GetMoniker36@CT typedef proto \
		 pThis: ptr IOleClientSite,
	      dwAssign: DWORD,
	dwWhichMoniker: DWORD,
		  ppmk: ptr IMoniker

	GetMoniker36@MP typedef ptr GetMoniker36@CT
	     GetMoniker GetMoniker36@MP ?

      GetContainer36@CT typedef proto \
		 pThis: ptr IOleClientSite,
	   ppContainer: ptr IOleContainer

      GetContainer36@MP typedef ptr GetContainer36@CT
	   GetContainer GetContainer36@MP ?

	ShowObject36@CT typedef proto \
		 pThis: ptr IOleClientSite

	ShowObject36@MP typedef ptr ShowObject36@CT
	     ShowObject ShowObject36@MP ?

      OnShowWindow36@CT typedef proto \
		 pThis: ptr IOleClientSite,
		 fShow: BOOL

      OnShowWindow36@MP typedef ptr OnShowWindow36@CT
	   OnShowWindow OnShowWindow36@MP ?

RequestNewObjectLayout36@CT typedef proto \
		 pThis: ptr IOleClientSite

RequestNewObjectLayout36@MP typedef ptr RequestNewObjectLayout36@CT
 RequestNewObjectLayout RequestNewObjectLayout36@MP ?

	END_INTERFACE

IOleClientSiteVtbl	ENDS

LPIOleClientSiteVtbl	typedef ptr IOleClientSiteVtbl
IOleClientSite		STRUC
lpVtbl			LPIOleClientSiteVtbl ?
IOleClientSite		ENDS






;HRESULT
IOleClientSite_SaveObject_Proxy proto WINAPI \
		 pThis: ptr IOleClientSite



;void
IOleClientSite_SaveObject_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleClientSite_GetMoniker_Proxy proto WINAPI \
		 pThis: ptr IOleClientSite,
	      dwAssign: DWORD,
	dwWhichMoniker: DWORD,
		  ppmk: ptr IMoniker



;void
IOleClientSite_GetMoniker_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleClientSite_GetContainer_Proxy proto WINAPI \
		 pThis: ptr IOleClientSite,
	   ppContainer: ptr IOleContainer



;void
IOleClientSite_GetContainer_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleClientSite_ShowObject_Proxy proto WINAPI \
		 pThis: ptr IOleClientSite



;void
IOleClientSite_ShowObject_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleClientSite_OnShowWindow_Proxy proto WINAPI \
		 pThis: ptr IOleClientSite,
		 fShow: BOOL



;void
IOleClientSite_OnShowWindow_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleClientSite_RequestNewObjectLayout_Proxy proto WINAPI \
		 pThis: ptr IOleClientSite



;void
IOleClientSite_RequestNewObjectLayout_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleObject_INTERFACE_DEFINED__
__IOleObject_INTERFACE_DEFINED__ equ 1



LPOLEOBJECT		typedef ptr IOleObject

;typedef enum tagOLEGETMONIKER

OLEGETMONIKER_ONLYIFTHERE equ 1
OLEGETMONIKER_FORCEASSIGN equ 2
OLEGETMONIKER_UNASSIGN	equ 3
OLEGETMONIKER_TEMPFORUSER equ 4

;typedef enum tagOLEWHICHMK

OLEWHICHMK_CONTAINER	equ 1
OLEWHICHMK_OBJREL	equ 2
OLEWHICHMK_OBJFULL	equ 3

;typedef enum tagUSERCLASSTYPE

USERCLASSTYPE_FULL	equ 1
USERCLASSTYPE_SHORT	equ 2
USERCLASSTYPE_APPNAME	equ 3

;typedef enum tagOLEMISC

OLEMISC_RECOMPOSEONRESIZE equ 0x1
OLEMISC_ONLYICONIC	equ 0x2
OLEMISC_INSERTNOTREPLACE equ 0x4
OLEMISC_STATIC		equ 0x8
OLEMISC_CANTLINKINSIDE	equ 0x10
OLEMISC_CANLINKBYOLE1	equ 0x20
OLEMISC_ISLINKOBJECT	equ 0x40
OLEMISC_INSIDEOUT	equ 0x80
OLEMISC_ACTIVATEWHENVISIBLE equ 0x100
OLEMISC_RENDERINGISDEVICEINDEPENDENT equ 0x200
OLEMISC_INVISIBLEATRUNTIME equ 0x400
OLEMISC_ALWAYSRUN	equ 0x800
OLEMISC_ACTSLIKEBUTTON	equ 0x1000
OLEMISC_ACTSLIKELABEL	equ 0x2000
OLEMISC_NOUIACTIVATE	equ 0x4000
OLEMISC_ALIGNABLE	equ 0x8000
OLEMISC_SIMPLEFRAME	equ 0x10000
OLEMISC_SETCLIENTSITEFIRST equ 0x20000
OLEMISC_IMEMODE		equ 0x40000
OLEMISC_IGNOREACTIVATEWHENVISIBLE equ 0x80000
OLEMISC_WANTSTOMENUMERGE equ 0x100000
OLEMISC_SUPPORTSMULTILEVELUNDO equ 0x200000

;typedef enum tagOLECLOSE

OLECLOSE_SAVEIFDIRTY	equ 0
OLECLOSE_NOSAVE		equ 1
OLECLOSE_PROMPTSAVE	equ 2


externdef		IID_IOleObject:IID


IOleObjectVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface37@CT typedef proto \
		 pThis: ptr IOleObject,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface37@MP typedef ptr QueryInterface37@CT
	 QueryInterface QueryInterface37@MP ?

	    AddRef37@CT typedef proto \
		 pThis: ptr IOleObject

	    AddRef37@MP typedef ptr AddRef37@CT
		 AddRef AddRef37@MP ?

	   Release37@CT typedef proto \
		 pThis: ptr IOleObject

	   Release37@MP typedef ptr Release37@CT
		Release Release37@MP ?

     SetClientSite37@CT typedef proto \
		 pThis: ptr IOleObject,
	   pClientSite: ptr IOleClientSite

     SetClientSite37@MP typedef ptr SetClientSite37@CT
	  SetClientSite SetClientSite37@MP ?

     GetClientSite37@CT typedef proto \
		 pThis: ptr IOleObject,
	  ppClientSite: ptr IOleClientSite

     GetClientSite37@MP typedef ptr GetClientSite37@CT
	  GetClientSite GetClientSite37@MP ?

      SetHostNames37@CT typedef proto \
		 pThis: ptr IOleObject,
	szContainerApp: LPCOLESTR,
	szContainerObj: LPCOLESTR

      SetHostNames37@MP typedef ptr SetHostNames37@CT
	   SetHostNames SetHostNames37@MP ?

	     Close37@CT typedef proto \
		 pThis: ptr IOleObject,
	  dwSaveOption: DWORD

	     Close37@MP typedef ptr Close37@CT
		  Close Close37@MP ?

	SetMoniker37@CT typedef proto \
		 pThis: ptr IOleObject,
	dwWhichMoniker: DWORD,
		   pmk: ptr IMoniker

	SetMoniker37@MP typedef ptr SetMoniker37@CT
	     SetMoniker SetMoniker37@MP ?

	GetMoniker37@CT typedef proto \
		 pThis: ptr IOleObject,
	      dwAssign: DWORD,
	dwWhichMoniker: DWORD,
		  ppmk: ptr IMoniker

	GetMoniker37@MP typedef ptr GetMoniker37@CT
	     GetMoniker GetMoniker37@MP ?

      InitFromData37@CT typedef proto \
		 pThis: ptr IOleObject,
	   pDataObject: ptr IDataObject,
	     fCreation: BOOL,
	    dwReserved: DWORD

      InitFromData37@MP typedef ptr InitFromData37@CT
	   InitFromData InitFromData37@MP ?

  GetClipboardData37@CT typedef proto \
		 pThis: ptr IOleObject,
	    dwReserved: DWORD,
	  ppDataObject: ptr IDataObject

  GetClipboardData37@MP typedef ptr GetClipboardData37@CT
       GetClipboardData GetClipboardData37@MP ?

	    DoVerb37@CT typedef proto \
		 pThis: ptr IOleObject,
		 iVerb: LONG,
		 lpmsg: LPMSG,
	   pActiveSite: ptr IOleClientSite,
		lindex: LONG,
	    hwndParent: HWND,
	   lprcPosRect: LPCRECT

	    DoVerb37@MP typedef ptr DoVerb37@CT
		 DoVerb DoVerb37@MP ?

	 EnumVerbs37@CT typedef proto \
		 pThis: ptr IOleObject,
	 ppEnumOleVerb: ptr IEnumOLEVERB

	 EnumVerbs37@MP typedef ptr EnumVerbs37@CT
	      EnumVerbs EnumVerbs37@MP ?

	    Update37@CT typedef proto \
		 pThis: ptr IOleObject

	    Update37@MP typedef ptr Update37@CT
		 Update Update37@MP ?

	IsUpToDate37@CT typedef proto \
		 pThis: ptr IOleObject

	IsUpToDate37@MP typedef ptr IsUpToDate37@CT
	     IsUpToDate IsUpToDate37@MP ?

    GetUserClassID37@CT typedef proto \
		 pThis: ptr IOleObject,
		pClsid: ptr CLSID

    GetUserClassID37@MP typedef ptr GetUserClassID37@CT
	 GetUserClassID GetUserClassID37@MP ?

       GetUserType37@CT typedef proto \
		 pThis: ptr IOleObject,
	  dwFormOfType: DWORD,
	   pszUserType: ptr LPOLESTR

       GetUserType37@MP typedef ptr GetUserType37@CT
	    GetUserType GetUserType37@MP ?

	 SetExtent37@CT typedef proto \
		 pThis: ptr IOleObject,
	  dwDrawAspect: DWORD,
		psizel: ptr SIZEL

	 SetExtent37@MP typedef ptr SetExtent37@CT
	      SetExtent SetExtent37@MP ?

	 GetExtent37@CT typedef proto \
		 pThis: ptr IOleObject,
	  dwDrawAspect: DWORD,
		psizel: ptr SIZEL

	 GetExtent37@MP typedef ptr GetExtent37@CT
	      GetExtent GetExtent37@MP ?

	    Advise37@CT typedef proto \
		 pThis: ptr IOleObject,
	      pAdvSink: ptr IAdviseSink,
	 pdwConnection: ptr DWORD

	    Advise37@MP typedef ptr Advise37@CT
		 Advise Advise37@MP ?

	  Unadvise37@CT typedef proto \
		 pThis: ptr IOleObject,
	  dwConnection: DWORD

	  Unadvise37@MP typedef ptr Unadvise37@CT
	       Unadvise Unadvise37@MP ?

	EnumAdvise37@CT typedef proto \
		 pThis: ptr IOleObject,
	  ppenumAdvise: ptr IEnumSTATDATA

	EnumAdvise37@MP typedef ptr EnumAdvise37@CT
	     EnumAdvise EnumAdvise37@MP ?

     GetMiscStatus37@CT typedef proto \
		 pThis: ptr IOleObject,
	      dwAspect: DWORD,
	     pdwStatus: ptr DWORD

     GetMiscStatus37@MP typedef ptr GetMiscStatus37@CT
	  GetMiscStatus GetMiscStatus37@MP ?

    SetColorScheme37@CT typedef proto \
		 pThis: ptr IOleObject,
	       pLogpal: ptr LOGPALETTE

    SetColorScheme37@MP typedef ptr SetColorScheme37@CT
	 SetColorScheme SetColorScheme37@MP ?

	END_INTERFACE

IOleObjectVtbl		ENDS

LPIOleObjectVtbl	typedef ptr IOleObjectVtbl
IOleObject		STRUC
lpVtbl			LPIOleObjectVtbl ?
IOleObject		ENDS






;HRESULT
IOleObject_SetClientSite_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	   pClientSite: ptr IOleClientSite



;void
IOleObject_SetClientSite_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_GetClientSite_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	  ppClientSite: ptr IOleClientSite



;void
IOleObject_GetClientSite_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_SetHostNames_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	szContainerApp: LPCOLESTR,
	szContainerObj: LPCOLESTR



;void
IOleObject_SetHostNames_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_Close_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	  dwSaveOption: DWORD



;void
IOleObject_Close_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_SetMoniker_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	dwWhichMoniker: DWORD,
		   pmk: ptr IMoniker



;void
IOleObject_SetMoniker_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_GetMoniker_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	      dwAssign: DWORD,
	dwWhichMoniker: DWORD,
		  ppmk: ptr IMoniker



;void
IOleObject_GetMoniker_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_InitFromData_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	   pDataObject: ptr IDataObject,
	     fCreation: BOOL,
	    dwReserved: DWORD



;void
IOleObject_InitFromData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_GetClipboardData_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	    dwReserved: DWORD,
	  ppDataObject: ptr IDataObject



;void
IOleObject_GetClipboardData_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_DoVerb_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
		 iVerb: LONG,
		 lpmsg: LPMSG,
	   pActiveSite: ptr IOleClientSite,
		lindex: LONG,
	    hwndParent: HWND,
	   lprcPosRect: LPCRECT



;void
IOleObject_DoVerb_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_EnumVerbs_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	 ppEnumOleVerb: ptr IEnumOLEVERB



;void
IOleObject_EnumVerbs_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_Update_Proxy proto WINAPI \
		 pThis: ptr IOleObject



;void
IOleObject_Update_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_IsUpToDate_Proxy proto WINAPI \
		 pThis: ptr IOleObject



;void
IOleObject_IsUpToDate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_GetUserClassID_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
		pClsid: ptr CLSID



;void
IOleObject_GetUserClassID_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_GetUserType_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	  dwFormOfType: DWORD,
	   pszUserType: ptr LPOLESTR



;void
IOleObject_GetUserType_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_SetExtent_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	  dwDrawAspect: DWORD,
		psizel: ptr SIZEL



;void
IOleObject_SetExtent_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_GetExtent_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	  dwDrawAspect: DWORD,
		psizel: ptr SIZEL



;void
IOleObject_GetExtent_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_Advise_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	      pAdvSink: ptr IAdviseSink,
	 pdwConnection: ptr DWORD



;void
IOleObject_Advise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_Unadvise_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	  dwConnection: DWORD



;void
IOleObject_Unadvise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_EnumAdvise_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	  ppenumAdvise: ptr IEnumSTATDATA



;void
IOleObject_EnumAdvise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_GetMiscStatus_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	      dwAspect: DWORD,
	     pdwStatus: ptr DWORD



;void
IOleObject_GetMiscStatus_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleObject_SetColorScheme_Proxy proto WINAPI \
		 pThis: ptr IOleObject,
	       pLogpal: ptr LOGPALETTE



;void
IOleObject_SetColorScheme_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOLETypes_INTERFACE_DEFINED__
__IOLETypes_INTERFACE_DEFINED__ equ 1



;typedef enum tagOLERENDER

OLERENDER_NONE		equ 0
OLERENDER_DRAW		equ 1
OLERENDER_FORMAT	equ 2
OLERENDER_ASIS		equ 3

LPOLERENDER		typedef ptr OLERENDER

OBJECTDESCRIPTOR	STRUC
cbSize			ULONG ?
clsid			CLSID <>
dwDrawAspect		dd ?
sizel			SIZEL <>
pointl			POINTL <>
dwStatus		dd ?
dwFullUserTypeName	dd ?
dwSrcOfCopy		dd ?
OBJECTDESCRIPTOR	ENDS
POBJECTDESCRIPTOR	typedef ptr OBJECTDESCRIPTOR
LPOBJECTDESCRIPTOR	typedef ptr OBJECTDESCRIPTOR
LINKSRCDESCRIPTOR	typedef OBJECTDESCRIPTOR
PLINKSRCDESCRIPTOR	typedef ptr OBJECTDESCRIPTOR
LPLINKSRCDESCRIPTOR	typedef ptr OBJECTDESCRIPTOR


externdef		IOLETypes_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		IOLETypes_v0_0_s_ifspec:RPC_IF_HANDLE
endif 

ifndef __IOleWindow_INTERFACE_DEFINED__
__IOleWindow_INTERFACE_DEFINED__ equ 1



LPOLEWINDOW		typedef ptr IOleWindow


externdef		IID_IOleWindow:IID


IOleWindowVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface38@CT typedef proto \
		 pThis: ptr IOleWindow,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface38@MP typedef ptr QueryInterface38@CT
	 QueryInterface QueryInterface38@MP ?

	    AddRef38@CT typedef proto \
		 pThis: ptr IOleWindow

	    AddRef38@MP typedef ptr AddRef38@CT
		 AddRef AddRef38@MP ?

	   Release38@CT typedef proto \
		 pThis: ptr IOleWindow

	   Release38@MP typedef ptr Release38@CT
		Release Release38@MP ?

	 GetWindow38@CT typedef proto \
		 pThis: ptr IOleWindow,
		 phwnd: ptr HWND

	 GetWindow38@MP typedef ptr GetWindow38@CT
	      GetWindow GetWindow38@MP ?

ContextSensitiveHelp38@CT typedef proto \
		 pThis: ptr IOleWindow,
	    fEnterMode: BOOL

ContextSensitiveHelp38@MP typedef ptr ContextSensitiveHelp38@CT
   ContextSensitiveHelp ContextSensitiveHelp38@MP ?

	END_INTERFACE

IOleWindowVtbl		ENDS

LPIOleWindowVtbl	typedef ptr IOleWindowVtbl
IOleWindow		STRUC
lpVtbl			LPIOleWindowVtbl ?
IOleWindow		ENDS






;HRESULT
IOleWindow_GetWindow_Proxy proto WINAPI \
		 pThis: ptr IOleWindow,
		 phwnd: ptr HWND



;void
IOleWindow_GetWindow_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleWindow_ContextSensitiveHelp_Proxy proto WINAPI \
		 pThis: ptr IOleWindow,
	    fEnterMode: BOOL



;void
IOleWindow_ContextSensitiveHelp_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleLink_INTERFACE_DEFINED__
__IOleLink_INTERFACE_DEFINED__ equ 1



LPOLELINK		typedef ptr IOleLink

;typedef enum tagOLEUPDATE

OLEUPDATE_ALWAYS	equ 1
OLEUPDATE_ONCALL	equ 3

LPOLEUPDATE		typedef ptr OLEUPDATE

POLEUPDATE		typedef ptr OLEUPDATE

;typedef enum tagOLELINKBIND

OLELINKBIND_EVENIFCLASSDIFF equ 1


externdef		IID_IOleLink:IID


IOleLinkVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface39@CT typedef proto \
		 pThis: ptr IOleLink,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface39@MP typedef ptr QueryInterface39@CT
	 QueryInterface QueryInterface39@MP ?

	    AddRef39@CT typedef proto \
		 pThis: ptr IOleLink

	    AddRef39@MP typedef ptr AddRef39@CT
		 AddRef AddRef39@MP ?

	   Release39@CT typedef proto \
		 pThis: ptr IOleLink

	   Release39@MP typedef ptr Release39@CT
		Release Release39@MP ?

  SetUpdateOptions39@CT typedef proto \
		 pThis: ptr IOleLink,
	   dwUpdateOpt: DWORD

  SetUpdateOptions39@MP typedef ptr SetUpdateOptions39@CT
       SetUpdateOptions SetUpdateOptions39@MP ?

  GetUpdateOptions39@CT typedef proto \
		 pThis: ptr IOleLink,
	  pdwUpdateOpt: ptr DWORD

  GetUpdateOptions39@MP typedef ptr GetUpdateOptions39@CT
       GetUpdateOptions GetUpdateOptions39@MP ?

  SetSourceMoniker39@CT typedef proto \
		 pThis: ptr IOleLink,
		   pmk: ptr IMoniker,
		rclsid: REFCLSID

  SetSourceMoniker39@MP typedef ptr SetSourceMoniker39@CT
       SetSourceMoniker SetSourceMoniker39@MP ?

  GetSourceMoniker39@CT typedef proto \
		 pThis: ptr IOleLink,
		  ppmk: ptr IMoniker

  GetSourceMoniker39@MP typedef ptr GetSourceMoniker39@CT
       GetSourceMoniker GetSourceMoniker39@MP ?

SetSourceDisplayName39@CT typedef proto \
		 pThis: ptr IOleLink,
	 pszStatusText: LPCOLESTR

SetSourceDisplayName39@MP typedef ptr SetSourceDisplayName39@CT
   SetSourceDisplayName SetSourceDisplayName39@MP ?

GetSourceDisplayName39@CT typedef proto \
		 pThis: ptr IOleLink,
       ppszDisplayName: ptr LPOLESTR

GetSourceDisplayName39@MP typedef ptr GetSourceDisplayName39@CT
   GetSourceDisplayName GetSourceDisplayName39@MP ?

      BindToSource39@CT typedef proto \
		 pThis: ptr IOleLink,
	     bindflags: DWORD,
		   pbc: ptr IBindCtx

      BindToSource39@MP typedef ptr BindToSource39@CT
	   BindToSource BindToSource39@MP ?

     BindIfRunning39@CT typedef proto \
		 pThis: ptr IOleLink

     BindIfRunning39@MP typedef ptr BindIfRunning39@CT
	  BindIfRunning BindIfRunning39@MP ?

    GetBoundSource39@CT typedef proto \
		 pThis: ptr IOleLink,
		 ppunk: ptr IUnknown

    GetBoundSource39@MP typedef ptr GetBoundSource39@CT
	 GetBoundSource GetBoundSource39@MP ?

      UnbindSource39@CT typedef proto \
		 pThis: ptr IOleLink

      UnbindSource39@MP typedef ptr UnbindSource39@CT
	   UnbindSource UnbindSource39@MP ?

	    Update39@CT typedef proto \
		 pThis: ptr IOleLink,
		   pbc: ptr IBindCtx

	    Update39@MP typedef ptr Update39@CT
		 Update Update39@MP ?

	END_INTERFACE

IOleLinkVtbl		ENDS

LPIOleLinkVtbl		typedef ptr IOleLinkVtbl
IOleLink		STRUC
lpVtbl			LPIOleLinkVtbl ?
IOleLink		ENDS






;HRESULT
IOleLink_SetUpdateOptions_Proxy proto WINAPI \
		 pThis: ptr IOleLink,
	   dwUpdateOpt: DWORD



;void
IOleLink_SetUpdateOptions_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleLink_GetUpdateOptions_Proxy proto WINAPI \
		 pThis: ptr IOleLink,
	  pdwUpdateOpt: ptr DWORD



;void
IOleLink_GetUpdateOptions_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleLink_SetSourceMoniker_Proxy proto WINAPI \
		 pThis: ptr IOleLink,
		   pmk: ptr IMoniker,
		rclsid: REFCLSID



;void
IOleLink_SetSourceMoniker_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleLink_GetSourceMoniker_Proxy proto WINAPI \
		 pThis: ptr IOleLink,
		  ppmk: ptr IMoniker



;void
IOleLink_GetSourceMoniker_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleLink_SetSourceDisplayName_Proxy proto WINAPI \
		 pThis: ptr IOleLink,
	 pszStatusText: LPCOLESTR



;void
IOleLink_SetSourceDisplayName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleLink_GetSourceDisplayName_Proxy proto WINAPI \
		 pThis: ptr IOleLink,
       ppszDisplayName: ptr LPOLESTR



;void
IOleLink_GetSourceDisplayName_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleLink_BindToSource_Proxy proto WINAPI \
		 pThis: ptr IOleLink,
	     bindflags: DWORD,
		   pbc: ptr IBindCtx



;void
IOleLink_BindToSource_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleLink_BindIfRunning_Proxy proto WINAPI \
		 pThis: ptr IOleLink



;void
IOleLink_BindIfRunning_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleLink_GetBoundSource_Proxy proto WINAPI \
		 pThis: ptr IOleLink,
		 ppunk: ptr IUnknown



;void
IOleLink_GetBoundSource_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleLink_UnbindSource_Proxy proto WINAPI \
		 pThis: ptr IOleLink



;void
IOleLink_UnbindSource_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleLink_Update_Proxy proto WINAPI \
		 pThis: ptr IOleLink,
		   pbc: ptr IBindCtx



;void
IOleLink_Update_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleItemContainer_INTERFACE_DEFINED__
__IOleItemContainer_INTERFACE_DEFINED__ equ 1



LPOLEITEMCONTAINER	typedef ptr IOleItemContainer

;typedef enum tagBINDSPEED

BINDSPEED_INDEFINITE	equ 1
BINDSPEED_MODERATE	equ 2
BINDSPEED_IMMEDIATE	equ 3

;typedef /* [v1_enum] */ enum tagOLECONTF

OLECONTF_EMBEDDINGS	equ 1
OLECONTF_LINKS		equ 2
OLECONTF_OTHERS		equ 4
OLECONTF_ONLYUSER	equ 8
OLECONTF_ONLYIFRUNNING	equ 16


externdef		IID_IOleItemContainer:IID


IOleItemContainerVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface40@CT typedef proto \
		 pThis: ptr IOleItemContainer,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface40@MP typedef ptr QueryInterface40@CT
	 QueryInterface QueryInterface40@MP ?

	    AddRef40@CT typedef proto \
		 pThis: ptr IOleItemContainer

	    AddRef40@MP typedef ptr AddRef40@CT
		 AddRef AddRef40@MP ?

	   Release40@CT typedef proto \
		 pThis: ptr IOleItemContainer

	   Release40@MP typedef ptr Release40@CT
		Release Release40@MP ?

  ParseDisplayName40@CT typedef proto \
		 pThis: ptr IOleItemContainer,
		   pbc: ptr IBindCtx,
	pszDisplayName: LPOLESTR,
	      pchEaten: ptr ULONG,
	       ppmkOut: ptr IMoniker

  ParseDisplayName40@MP typedef ptr ParseDisplayName40@CT
       ParseDisplayName ParseDisplayName40@MP ?

       EnumObjects40@CT typedef proto \
		 pThis: ptr IOleItemContainer,
	      grfFlags: DWORD,
		ppenum: ptr IEnumUnknown

       EnumObjects40@MP typedef ptr EnumObjects40@CT
	    EnumObjects EnumObjects40@MP ?

     LockContainer40@CT typedef proto \
		 pThis: ptr IOleItemContainer,
		 fLock: BOOL

     LockContainer40@MP typedef ptr LockContainer40@CT
	  LockContainer LockContainer40@MP ?

	 GetObject40@CT typedef proto \
		 pThis: ptr IOleItemContainer,
	       pszItem: LPOLESTR,
	 dwSpeedNeeded: DWORD,
		   pbc: ptr IBindCtx,
		  riid: REFIID,
	     ppvObject: PVOID

	 GetObject40@MP typedef ptr GetObject40@CT
	      GetObject GetObject40@MP ?

  GetObjectStorage40@CT typedef proto \
		 pThis: ptr IOleItemContainer,
	       pszItem: LPOLESTR,
		   pbc: ptr IBindCtx,
		  riid: REFIID,
	     ppvObject: PVOID

  GetObjectStorage40@MP typedef ptr GetObjectStorage40@CT
       GetObjectStorage GetObjectStorage40@MP ?

	 IsRunning40@CT typedef proto \
		 pThis: ptr IOleItemContainer,
	       pszItem: LPOLESTR

	 IsRunning40@MP typedef ptr IsRunning40@CT
	      IsRunning IsRunning40@MP ?

	END_INTERFACE

IOleItemContainerVtbl	ENDS

LPIOleItemContainerVtbl typedef ptr IOleItemContainerVtbl
IOleItemContainer	STRUC
lpVtbl			LPIOleItemContainerVtbl ?
IOleItemContainer	ENDS






;HRESULT
IOleItemContainer_GetObject_Proxy proto WINAPI \
		 pThis: ptr IOleItemContainer,
	       pszItem: LPOLESTR,
	 dwSpeedNeeded: DWORD,
		   pbc: ptr IBindCtx,
		  riid: REFIID,
	     ppvObject: PVOID



;void
IOleItemContainer_GetObject_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleItemContainer_GetObjectStorage_Proxy proto WINAPI \
		 pThis: ptr IOleItemContainer,
	       pszItem: LPOLESTR,
		   pbc: ptr IBindCtx,
		  riid: REFIID,
	     ppvObject: PVOID



;void
IOleItemContainer_GetObjectStorage_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleItemContainer_IsRunning_Proxy proto WINAPI \
		 pThis: ptr IOleItemContainer,
	       pszItem: LPOLESTR



;void
IOleItemContainer_IsRunning_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleInPlaceUIWindow_INTERFACE_DEFINED__
__IOleInPlaceUIWindow_INTERFACE_DEFINED__ equ 1



LPOLEINPLACEUIWINDOW	typedef ptr IOleInPlaceUIWindow

BORDERWIDTHS		typedef RECT

LPBORDERWIDTHS		typedef LPRECT

LPCBORDERWIDTHS		typedef LPCRECT


externdef		IID_IOleInPlaceUIWindow:IID


IOleInPlaceUIWindowVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface41@CT typedef proto \
		 pThis: ptr IOleInPlaceUIWindow,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface41@MP typedef ptr QueryInterface41@CT
	 QueryInterface QueryInterface41@MP ?

	    AddRef41@CT typedef proto \
		 pThis: ptr IOleInPlaceUIWindow

	    AddRef41@MP typedef ptr AddRef41@CT
		 AddRef AddRef41@MP ?

	   Release41@CT typedef proto \
		 pThis: ptr IOleInPlaceUIWindow

	   Release41@MP typedef ptr Release41@CT
		Release Release41@MP ?

	 GetWindow41@CT typedef proto \
		 pThis: ptr IOleInPlaceUIWindow,
		 phwnd: ptr HWND

	 GetWindow41@MP typedef ptr GetWindow41@CT
	      GetWindow GetWindow41@MP ?

ContextSensitiveHelp41@CT typedef proto \
		 pThis: ptr IOleInPlaceUIWindow,
	    fEnterMode: BOOL

ContextSensitiveHelp41@MP typedef ptr ContextSensitiveHelp41@CT
   ContextSensitiveHelp ContextSensitiveHelp41@MP ?

	 GetBorder41@CT typedef proto \
		 pThis: ptr IOleInPlaceUIWindow,
	  lprectBorder: LPRECT

	 GetBorder41@MP typedef ptr GetBorder41@CT
	      GetBorder GetBorder41@MP ?

RequestBorderSpace41@CT typedef proto \
		 pThis: ptr IOleInPlaceUIWindow,
	 pborderwidths: LPCBORDERWIDTHS

RequestBorderSpace41@MP typedef ptr RequestBorderSpace41@CT
     RequestBorderSpace RequestBorderSpace41@MP ?

    SetBorderSpace41@CT typedef proto \
		 pThis: ptr IOleInPlaceUIWindow,
	 pborderwidths: LPCBORDERWIDTHS

    SetBorderSpace41@MP typedef ptr SetBorderSpace41@CT
	 SetBorderSpace SetBorderSpace41@MP ?

   SetActiveObject41@CT typedef proto \
		 pThis: ptr IOleInPlaceUIWindow,
	 pActiveObject: ptr IOleInPlaceActiveObject,
	    pszObjName: LPCOLESTR

   SetActiveObject41@MP typedef ptr SetActiveObject41@CT
	SetActiveObject SetActiveObject41@MP ?

	END_INTERFACE

IOleInPlaceUIWindowVtbl ENDS

LPIOleInPlaceUIWindowVtbl typedef ptr IOleInPlaceUIWindowVtbl
IOleInPlaceUIWindow	STRUC
lpVtbl			LPIOleInPlaceUIWindowVtbl ?
IOleInPlaceUIWindow	ENDS






;HRESULT
IOleInPlaceUIWindow_GetBorder_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceUIWindow,
	  lprectBorder: LPRECT



;void
IOleInPlaceUIWindow_GetBorder_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceUIWindow_RequestBorderSpace_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceUIWindow,
	 pborderwidths: LPCBORDERWIDTHS



;void
IOleInPlaceUIWindow_RequestBorderSpace_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceUIWindow_SetBorderSpace_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceUIWindow,
	 pborderwidths: LPCBORDERWIDTHS



;void
IOleInPlaceUIWindow_SetBorderSpace_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceUIWindow_SetActiveObject_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceUIWindow,
	 pActiveObject: ptr IOleInPlaceActiveObject,
	    pszObjName: LPCOLESTR



;void
IOleInPlaceUIWindow_SetActiveObject_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleInPlaceActiveObject_INTERFACE_DEFINED__
__IOleInPlaceActiveObject_INTERFACE_DEFINED__ equ 1



LPOLEINPLACEACTIVEOBJECT typedef ptr IOleInPlaceActiveObject


externdef		IID_IOleInPlaceActiveObject:IID


IOleInPlaceActiveObjectVtbl STRUC

	BEGIN_INTERFACE

    QueryInterface42@CT typedef proto \
		 pThis: ptr IOleInPlaceActiveObject,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface42@MP typedef ptr QueryInterface42@CT
	 QueryInterface QueryInterface42@MP ?

	    AddRef42@CT typedef proto \
		 pThis: ptr IOleInPlaceActiveObject

	    AddRef42@MP typedef ptr AddRef42@CT
		 AddRef AddRef42@MP ?

	   Release42@CT typedef proto \
		 pThis: ptr IOleInPlaceActiveObject

	   Release42@MP typedef ptr Release42@CT
		Release Release42@MP ?

	 GetWindow42@CT typedef proto \
		 pThis: ptr IOleInPlaceActiveObject,
		 phwnd: ptr HWND

	 GetWindow42@MP typedef ptr GetWindow42@CT
	      GetWindow GetWindow42@MP ?

ContextSensitiveHelp42@CT typedef proto \
		 pThis: ptr IOleInPlaceActiveObject,
	    fEnterMode: BOOL

ContextSensitiveHelp42@MP typedef ptr ContextSensitiveHelp42@CT
   ContextSensitiveHelp ContextSensitiveHelp42@MP ?

TranslateAccelerator42@CT typedef proto \
		 pThis: ptr IOleInPlaceActiveObject,
		 lpmsg: LPMSG

TranslateAccelerator42@MP typedef ptr TranslateAccelerator42@CT
   TranslateAccelerator TranslateAccelerator42@MP ?

OnFrameWindowActivate42@CT typedef proto \
		 pThis: ptr IOleInPlaceActiveObject,
	     fActivate: BOOL

OnFrameWindowActivate42@MP typedef ptr OnFrameWindowActivate42@CT
  OnFrameWindowActivate OnFrameWindowActivate42@MP ?

OnDocWindowActivate42@CT typedef proto \
		 pThis: ptr IOleInPlaceActiveObject,
	     fActivate: BOOL

OnDocWindowActivate42@MP typedef ptr OnDocWindowActivate42@CT
    OnDocWindowActivate OnDocWindowActivate42@MP ?

      ResizeBorder42@CT typedef proto \
		 pThis: ptr IOleInPlaceActiveObject,
	     prcBorder: LPCRECT,
	     pUIWindow: ptr IOleInPlaceUIWindow,
	  fFrameWindow: BOOL

      ResizeBorder42@MP typedef ptr ResizeBorder42@CT
	   ResizeBorder ResizeBorder42@MP ?

    EnableModeless42@CT typedef proto \
		 pThis: ptr IOleInPlaceActiveObject,
	       fEnable: BOOL

    EnableModeless42@MP typedef ptr EnableModeless42@CT
	 EnableModeless EnableModeless42@MP ?

	END_INTERFACE

IOleInPlaceActiveObjectVtbl ENDS

LPIOleInPlaceActiveObjectVtbl typedef ptr IOleInPlaceActiveObjectVtbl
IOleInPlaceActiveObject STRUC
lpVtbl			LPIOleInPlaceActiveObjectVtbl ?
IOleInPlaceActiveObject ENDS






;HRESULT
IOleInPlaceActiveObject_RemoteTranslateAccelerator_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceActiveObject



;void
IOleInPlaceActiveObject_RemoteTranslateAccelerator_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceActiveObject_OnFrameWindowActivate_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceActiveObject,
	     fActivate: BOOL



;void
IOleInPlaceActiveObject_OnFrameWindowActivate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceActiveObject_OnDocWindowActivate_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceActiveObject,
	     fActivate: BOOL



;void
IOleInPlaceActiveObject_OnDocWindowActivate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceActiveObject_RemoteResizeBorder_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceActiveObject,
	     prcBorder: LPCRECT,
		  riid: REFIID,
	     pUIWindow: ptr IOleInPlaceUIWindow,
	  fFrameWindow: BOOL



;void
IOleInPlaceActiveObject_RemoteResizeBorder_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceActiveObject_EnableModeless_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceActiveObject,
	       fEnable: BOOL



;void
IOleInPlaceActiveObject_EnableModeless_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleInPlaceFrame_INTERFACE_DEFINED__
__IOleInPlaceFrame_INTERFACE_DEFINED__ equ 1



LPOLEINPLACEFRAME	typedef ptr IOleInPlaceFrame

OLEINPLACEFRAMEINFO	STRUC
cb			UINT ?
fMDIApp			BOOL ?
hwndFrame		HWND ?
haccel			HACCEL ?
cAccelEntries		UINT ?
OLEINPLACEFRAMEINFO	ENDS
LPOLEINPLACEFRAMEINFO	typedef ptr OLEINPLACEFRAMEINFO

OLEMENUGROUPWIDTHS	STRUC
_width			LONG 6 dup(?)
OLEMENUGROUPWIDTHS	ENDS

LPOLEMENUGROUPWIDTHS	typedef ptr OLEMENUGROUPWIDTHS

HOLEMENU		typedef HGLOBAL

externdef		IID_IOleInPlaceFrame:IID

IOleInPlaceFrameVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface43@MP typedef ptr QueryInterface43@CT
	 QueryInterface QueryInterface43@MP ?

	    AddRef43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame

	    AddRef43@MP typedef ptr AddRef43@CT
		 AddRef AddRef43@MP ?

	   Release43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame

	   Release43@MP typedef ptr Release43@CT
		Release Release43@MP ?

	 GetWindow43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
		 phwnd: ptr HWND

	 GetWindow43@MP typedef ptr GetWindow43@CT
	      GetWindow GetWindow43@MP ?

ContextSensitiveHelp43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
	    fEnterMode: BOOL

ContextSensitiveHelp43@MP typedef ptr ContextSensitiveHelp43@CT
   ContextSensitiveHelp ContextSensitiveHelp43@MP ?

	 GetBorder43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
	  lprectBorder: LPRECT

	 GetBorder43@MP typedef ptr GetBorder43@CT
	      GetBorder GetBorder43@MP ?

RequestBorderSpace43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
	 pborderwidths: LPCBORDERWIDTHS

RequestBorderSpace43@MP typedef ptr RequestBorderSpace43@CT
     RequestBorderSpace RequestBorderSpace43@MP ?

    SetBorderSpace43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
	 pborderwidths: LPCBORDERWIDTHS

    SetBorderSpace43@MP typedef ptr SetBorderSpace43@CT
	 SetBorderSpace SetBorderSpace43@MP ?

   SetActiveObject43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
	 pActiveObject: ptr IOleInPlaceActiveObject,
	    pszObjName: LPCOLESTR

   SetActiveObject43@MP typedef ptr SetActiveObject43@CT
	SetActiveObject SetActiveObject43@MP ?

       InsertMenus43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
	   hmenuShared: HMENU,
	  lpMenuWidths: LPOLEMENUGROUPWIDTHS

       InsertMenus43@MP typedef ptr InsertMenus43@CT
	    InsertMenus InsertMenus43@MP ?

	   SetMenu43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
	   hmenuShared: HMENU,
	      holemenu: HOLEMENU,
      hwndActiveObject: HWND

	   SetMenu43@MP typedef ptr SetMenu43@CT
		SetMenu SetMenu43@MP ?

       RemoveMenus43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
	   hmenuShared: HMENU

       RemoveMenus43@MP typedef ptr RemoveMenus43@CT
	    RemoveMenus RemoveMenus43@MP ?

     SetStatusText43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
	 pszStatusText: LPCOLESTR

     SetStatusText43@MP typedef ptr SetStatusText43@CT
	  SetStatusText SetStatusText43@MP ?

    EnableModeless43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
	       fEnable: BOOL

    EnableModeless43@MP typedef ptr EnableModeless43@CT
	 EnableModeless EnableModeless43@MP ?

TranslateAccelerator43@CT typedef proto \
		 pThis: ptr IOleInPlaceFrame,
		 lpmsg: LPMSG,
		   wID: WORD

TranslateAccelerator43@MP typedef ptr TranslateAccelerator43@CT
   TranslateAccelerator TranslateAccelerator43@MP ?

	END_INTERFACE

IOleInPlaceFrameVtbl	ENDS

LPIOleInPlaceFrameVtbl	typedef ptr IOleInPlaceFrameVtbl
IOleInPlaceFrame	STRUC
lpVtbl			LPIOleInPlaceFrameVtbl ?
IOleInPlaceFrame	ENDS

;HRESULT
IOleInPlaceFrame_InsertMenus_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceFrame,
	   hmenuShared: HMENU,
	  lpMenuWidths: LPOLEMENUGROUPWIDTHS

;void
IOleInPlaceFrame_InsertMenus_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IOleInPlaceFrame_SetMenu_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceFrame,
	   hmenuShared: HMENU,
	      holemenu: HOLEMENU,
      hwndActiveObject: HWND

;void
IOleInPlaceFrame_SetMenu_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IOleInPlaceFrame_RemoveMenus_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceFrame,
	   hmenuShared: HMENU

;void
IOleInPlaceFrame_RemoveMenus_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceFrame_SetStatusText_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceFrame,
	 pszStatusText: LPCOLESTR



;void
IOleInPlaceFrame_SetStatusText_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceFrame_EnableModeless_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceFrame,
	       fEnable: BOOL



;void
IOleInPlaceFrame_EnableModeless_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceFrame_TranslateAccelerator_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceFrame,
		 lpmsg: LPMSG,
		   wID: WORD



;void
IOleInPlaceFrame_TranslateAccelerator_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleInPlaceObject_INTERFACE_DEFINED__
__IOleInPlaceObject_INTERFACE_DEFINED__ equ 1



LPOLEINPLACEOBJECT	typedef ptr IOleInPlaceObject


externdef		IID_IOleInPlaceObject:IID


IOleInPlaceObjectVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface44@CT typedef proto \
		 pThis: ptr IOleInPlaceObject,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface44@MP typedef ptr QueryInterface44@CT
	 QueryInterface QueryInterface44@MP ?

	    AddRef44@CT typedef proto \
		 pThis: ptr IOleInPlaceObject

	    AddRef44@MP typedef ptr AddRef44@CT
		 AddRef AddRef44@MP ?

	   Release44@CT typedef proto \
		 pThis: ptr IOleInPlaceObject

	   Release44@MP typedef ptr Release44@CT
		Release Release44@MP ?

	 GetWindow44@CT typedef proto \
		 pThis: ptr IOleInPlaceObject,
		 phwnd: ptr HWND

	 GetWindow44@MP typedef ptr GetWindow44@CT
	      GetWindow GetWindow44@MP ?

ContextSensitiveHelp44@CT typedef proto \
		 pThis: ptr IOleInPlaceObject,
	    fEnterMode: BOOL

ContextSensitiveHelp44@MP typedef ptr ContextSensitiveHelp44@CT
   ContextSensitiveHelp ContextSensitiveHelp44@MP ?

 InPlaceDeactivate44@CT typedef proto \
		 pThis: ptr IOleInPlaceObject

 InPlaceDeactivate44@MP typedef ptr InPlaceDeactivate44@CT
      InPlaceDeactivate InPlaceDeactivate44@MP ?

      UIDeactivate44@CT typedef proto \
		 pThis: ptr IOleInPlaceObject

      UIDeactivate44@MP typedef ptr UIDeactivate44@CT
	   UIDeactivate UIDeactivate44@MP ?

    SetObjectRects44@CT typedef proto \
		 pThis: ptr IOleInPlaceObject,
	   lprcPosRect: LPCRECT,
	  lprcClipRect: LPCRECT

    SetObjectRects44@MP typedef ptr SetObjectRects44@CT
	 SetObjectRects SetObjectRects44@MP ?

 ReactivateAndUndo44@CT typedef proto \
		 pThis: ptr IOleInPlaceObject

 ReactivateAndUndo44@MP typedef ptr ReactivateAndUndo44@CT
      ReactivateAndUndo ReactivateAndUndo44@MP ?

	END_INTERFACE

IOleInPlaceObjectVtbl	ENDS

LPIOleInPlaceObjectVtbl typedef ptr IOleInPlaceObjectVtbl
IOleInPlaceObject	STRUC
lpVtbl			LPIOleInPlaceObjectVtbl ?
IOleInPlaceObject	ENDS






;HRESULT
IOleInPlaceObject_InPlaceDeactivate_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceObject



;void
IOleInPlaceObject_InPlaceDeactivate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceObject_UIDeactivate_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceObject



;void
IOleInPlaceObject_UIDeactivate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceObject_SetObjectRects_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceObject,
	   lprcPosRect: LPCRECT,
	  lprcClipRect: LPCRECT



;void
IOleInPlaceObject_SetObjectRects_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceObject_ReactivateAndUndo_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceObject



;void
IOleInPlaceObject_ReactivateAndUndo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IOleInPlaceSite_INTERFACE_DEFINED__
__IOleInPlaceSite_INTERFACE_DEFINED__ equ 1



LPOLEINPLACESITE	typedef ptr IOleInPlaceSite


externdef		IID_IOleInPlaceSite:IID


IOleInPlaceSiteVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface45@MP typedef ptr QueryInterface45@CT
	 QueryInterface QueryInterface45@MP ?

	    AddRef45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite

	    AddRef45@MP typedef ptr AddRef45@CT
		 AddRef AddRef45@MP ?

	   Release45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite

	   Release45@MP typedef ptr Release45@CT
		Release Release45@MP ?

	 GetWindow45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite,
		 phwnd: ptr HWND

	 GetWindow45@MP typedef ptr GetWindow45@CT
	      GetWindow GetWindow45@MP ?

ContextSensitiveHelp45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite,
	    fEnterMode: BOOL

ContextSensitiveHelp45@MP typedef ptr ContextSensitiveHelp45@CT
   ContextSensitiveHelp ContextSensitiveHelp45@MP ?

CanInPlaceActivate45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite

CanInPlaceActivate45@MP typedef ptr CanInPlaceActivate45@CT
     CanInPlaceActivate CanInPlaceActivate45@MP ?

 OnInPlaceActivate45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite

 OnInPlaceActivate45@MP typedef ptr OnInPlaceActivate45@CT
      OnInPlaceActivate OnInPlaceActivate45@MP ?

      OnUIActivate45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite

      OnUIActivate45@MP typedef ptr OnUIActivate45@CT
	   OnUIActivate OnUIActivate45@MP ?

  GetWindowContext45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite,
	       ppFrame: ptr IOleInPlaceFrame,
		 ppDoc: ptr IOleInPlaceUIWindow,
	   lprcPosRect: LPRECT,
	  lprcClipRect: LPRECT,
	   lpFrameInfo: LPOLEINPLACEFRAMEINFO

  GetWindowContext45@MP typedef ptr GetWindowContext45@CT
       GetWindowContext GetWindowContext45@MP ?

	    Scroll45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite,
	  scrollExtant: DWORD;SIZE

	    Scroll45@MP typedef ptr Scroll45@CT
		 Scroll Scroll45@MP ?

    OnUIDeactivate45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite,
	     fUndoable: BOOL

    OnUIDeactivate45@MP typedef ptr OnUIDeactivate45@CT
	 OnUIDeactivate OnUIDeactivate45@MP ?

OnInPlaceDeactivate45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite

OnInPlaceDeactivate45@MP typedef ptr OnInPlaceDeactivate45@CT
    OnInPlaceDeactivate OnInPlaceDeactivate45@MP ?

  DiscardUndoState45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite

  DiscardUndoState45@MP typedef ptr DiscardUndoState45@CT
       DiscardUndoState DiscardUndoState45@MP ?

 DeactivateAndUndo45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite

 DeactivateAndUndo45@MP typedef ptr DeactivateAndUndo45@CT
      DeactivateAndUndo DeactivateAndUndo45@MP ?

   OnPosRectChange45@CT typedef proto \
		 pThis: ptr IOleInPlaceSite,
	   lprcPosRect: LPCRECT

   OnPosRectChange45@MP typedef ptr OnPosRectChange45@CT
	OnPosRectChange OnPosRectChange45@MP ?

	END_INTERFACE

IOleInPlaceSiteVtbl	ENDS

LPIOleInPlaceSiteVtbl	typedef ptr IOleInPlaceSiteVtbl
IOleInPlaceSite		STRUC
lpVtbl			LPIOleInPlaceSiteVtbl ?
IOleInPlaceSite		ENDS






;HRESULT
IOleInPlaceSite_CanInPlaceActivate_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceSite



;void
IOleInPlaceSite_CanInPlaceActivate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceSite_OnInPlaceActivate_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceSite



;void
IOleInPlaceSite_OnInPlaceActivate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceSite_OnUIActivate_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceSite



;void
IOleInPlaceSite_OnUIActivate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceSite_GetWindowContext_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceSite,
	       ppFrame: ptr IOleInPlaceFrame,
		 ppDoc: ptr IOleInPlaceUIWindow,
	   lprcPosRect: LPRECT,
	  lprcClipRect: LPRECT,
	   lpFrameInfo: LPOLEINPLACEFRAMEINFO



;void
IOleInPlaceSite_GetWindowContext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD


;HRESULT
IOleInPlaceSite_Scroll_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceSite,
	  scrollExtant: tagSIZE



;void
IOleInPlaceSite_Scroll_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceSite_OnUIDeactivate_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceSite,
	     fUndoable: BOOL



;void
IOleInPlaceSite_OnUIDeactivate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceSite_OnInPlaceDeactivate_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceSite



;void
IOleInPlaceSite_OnInPlaceDeactivate_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceSite_DiscardUndoState_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceSite



;void
IOleInPlaceSite_DiscardUndoState_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceSite_DeactivateAndUndo_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceSite



;void
IOleInPlaceSite_DeactivateAndUndo_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IOleInPlaceSite_OnPosRectChange_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceSite,
	   lprcPosRect: LPCRECT



;void
IOleInPlaceSite_OnPosRectChange_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IContinue_INTERFACE_DEFINED__
__IContinue_INTERFACE_DEFINED__ equ 1




externdef		IID_IContinue:IID


IContinueVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface46@CT typedef proto \
		 pThis: ptr IContinue,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface46@MP typedef ptr QueryInterface46@CT
	 QueryInterface QueryInterface46@MP ?

	    AddRef46@CT typedef proto \
		 pThis: ptr IContinue

	    AddRef46@MP typedef ptr AddRef46@CT
		 AddRef AddRef46@MP ?

	   Release46@CT typedef proto \
		 pThis: ptr IContinue

	   Release46@MP typedef ptr Release46@CT
		Release Release46@MP ?

	 FContinue46@CT typedef proto \
		 pThis: ptr IContinue

	 FContinue46@MP typedef ptr FContinue46@CT
	      FContinue FContinue46@MP ?

	END_INTERFACE

IContinueVtbl		ENDS

LPIContinueVtbl		typedef ptr IContinueVtbl
IContinue		STRUC
lpVtbl			LPIContinueVtbl ?
IContinue		ENDS






;HRESULT
IContinue_FContinue_Proxy proto WINAPI \
		 pThis: ptr IContinue



;void
IContinue_FContinue_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IViewObject_INTERFACE_DEFINED__
__IViewObject_INTERFACE_DEFINED__ equ 1



LPVIEWOBJECT		typedef ptr IViewObject


externdef		IID_IViewObject:IID


IViewObjectVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface47@CT typedef proto \
		 pThis: ptr IViewObject,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface47@MP typedef ptr QueryInterface47@CT
	 QueryInterface QueryInterface47@MP ?

	    AddRef47@CT typedef proto \
		 pThis: ptr IViewObject

	    AddRef47@MP typedef ptr AddRef47@CT
		 AddRef AddRef47@MP ?

	   Release47@CT typedef proto \
		 pThis: ptr IViewObject

	   Release47@MP typedef ptr Release47@CT
		Release Release47@MP ?

	      Draw47@CT typedef proto \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: ptr void,
		   ptd: ptr DVTARGETDEVICE,
	  hdcTargetDev: HDC,
	       hdcDraw: HDC,
	    lprcBounds: LPCRECTL,
	   lprcWBounds: LPCRECTL,
;BOOL ( STDMETHODCALLTYPE *pfnContinue )( DWORD dwContinue);
	   pfnContinue: PVOID,
	    dwContinue: DWORD

	      Draw47@MP typedef ptr Draw47@CT
		   Draw Draw47@MP ?

       GetColorSet47@CT typedef proto \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: ptr void,
		   ptd: ptr DVTARGETDEVICE,
	  hicTargetDev: HDC,
	    ppColorSet: ptr LOGPALETTE

       GetColorSet47@MP typedef ptr GetColorSet47@CT
	    GetColorSet GetColorSet47@MP ?

	    Freeze47@CT typedef proto \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: ptr void,
	     pdwFreeze: ptr DWORD

	    Freeze47@MP typedef ptr Freeze47@CT
		 Freeze Freeze47@MP ?

	  Unfreeze47@CT typedef proto \
		 pThis: ptr IViewObject,
	      dwFreeze: DWORD

	  Unfreeze47@MP typedef ptr Unfreeze47@CT
	       Unfreeze Unfreeze47@MP ?

	 SetAdvise47@CT typedef proto \
		 pThis: ptr IViewObject,
	       aspects: DWORD,
		  advf: DWORD,
	      pAdvSink: ptr IAdviseSink

	 SetAdvise47@MP typedef ptr SetAdvise47@CT
	      SetAdvise SetAdvise47@MP ?

	 GetAdvise47@CT typedef proto \
		 pThis: ptr IViewObject,
	      pAspects: ptr DWORD,
		 pAdvf: ptr DWORD,
	     ppAdvSink: ptr IAdviseSink

	 GetAdvise47@MP typedef ptr GetAdvise47@CT
	      GetAdvise GetAdvise47@MP ?

	END_INTERFACE

IViewObjectVtbl		ENDS

LPIViewObjectVtbl	typedef ptr IViewObjectVtbl
IViewObject		STRUC
lpVtbl			LPIViewObjectVtbl ?
IViewObject		ENDS






;HRESULT
IViewObject_RemoteDraw_Proxy proto WINAPI \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: DWORD,
		   ptd: ptr DVTARGETDEVICE,
	  hdcTargetDev: DWORD,
	       hdcDraw: DWORD,
	    lprcBounds: LPCRECTL,
	   lprcWBounds: LPCRECTL,
	     pContinue: ptr IContinue



;void
IViewObject_RemoteDraw_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IViewObject_RemoteGetColorSet_Proxy proto WINAPI \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: DWORD,
		   ptd: ptr DVTARGETDEVICE,
	  hicTargetDev: DWORD,
	    ppColorSet: ptr LOGPALETTE



;void
IViewObject_RemoteGetColorSet_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IViewObject_RemoteFreeze_Proxy proto WINAPI \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: DWORD,
	     pdwFreeze: ptr DWORD



;void
IViewObject_RemoteFreeze_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IViewObject_Unfreeze_Proxy proto WINAPI \
		 pThis: ptr IViewObject,
	      dwFreeze: DWORD



;void
IViewObject_Unfreeze_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IViewObject_SetAdvise_Proxy proto WINAPI \
		 pThis: ptr IViewObject,
	       aspects: DWORD,
		  advf: DWORD,
	      pAdvSink: ptr IAdviseSink



;void
IViewObject_SetAdvise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IViewObject_RemoteGetAdvise_Proxy proto WINAPI \
		 pThis: ptr IViewObject,
	      pAspects: ptr DWORD,
		 pAdvf: ptr DWORD,
	     ppAdvSink: ptr IAdviseSink



;void
IViewObject_RemoteGetAdvise_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IViewObject2_INTERFACE_DEFINED__
__IViewObject2_INTERFACE_DEFINED__ equ 1



LPVIEWOBJECT2		typedef ptr IViewObject2


externdef		IID_IViewObject2:IID


IViewObject2Vtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface48@CT typedef proto \
		 pThis: ptr IViewObject2,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface48@MP typedef ptr QueryInterface48@CT
	 QueryInterface QueryInterface48@MP ?

	    AddRef48@CT typedef proto \
		 pThis: ptr IViewObject2

	    AddRef48@MP typedef ptr AddRef48@CT
		 AddRef AddRef48@MP ?

	   Release48@CT typedef proto \
		 pThis: ptr IViewObject2

	   Release48@MP typedef ptr Release48@CT
		Release Release48@MP ?

	      Draw48@CT typedef proto \
		 pThis: ptr IViewObject2,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: ptr void,
		   ptd: ptr DVTARGETDEVICE,
	  hdcTargetDev: HDC,
	       hdcDraw: HDC,
	    lprcBounds: LPCRECTL,
	   lprcWBounds: LPCRECTL,
;BOOL ( STDMETHODCALLTYPE *pfnContinue )( DWORD dwContinue);
	   pfnContinue: PVOID,
	    dwContinue: DWORD

	      Draw48@MP typedef ptr Draw48@CT
		   Draw Draw48@MP ?

       GetColorSet48@CT typedef proto \
		 pThis: ptr IViewObject2,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: ptr void,
		   ptd: ptr DVTARGETDEVICE,
	  hicTargetDev: HDC,
	    ppColorSet: ptr LOGPALETTE

       GetColorSet48@MP typedef ptr GetColorSet48@CT
	    GetColorSet GetColorSet48@MP ?

	    Freeze48@CT typedef proto \
		 pThis: ptr IViewObject2,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: ptr void,
	     pdwFreeze: ptr DWORD

	    Freeze48@MP typedef ptr Freeze48@CT
		 Freeze Freeze48@MP ?

	  Unfreeze48@CT typedef proto \
		 pThis: ptr IViewObject2,
	      dwFreeze: DWORD

	  Unfreeze48@MP typedef ptr Unfreeze48@CT
	       Unfreeze Unfreeze48@MP ?

	 SetAdvise48@CT typedef proto \
		 pThis: ptr IViewObject2,
	       aspects: DWORD,
		  advf: DWORD,
	      pAdvSink: ptr IAdviseSink

	 SetAdvise48@MP typedef ptr SetAdvise48@CT
	      SetAdvise SetAdvise48@MP ?

	 GetAdvise48@CT typedef proto \
		 pThis: ptr IViewObject2,
	      pAspects: ptr DWORD,
		 pAdvf: ptr DWORD,
	     ppAdvSink: ptr IAdviseSink

	 GetAdvise48@MP typedef ptr GetAdvise48@CT
	      GetAdvise GetAdvise48@MP ?

	 GetExtent48@CT typedef proto \
		 pThis: ptr IViewObject2,
	  dwDrawAspect: DWORD,
		lindex: LONG,
		   ptd: ptr DVTARGETDEVICE,
	       lpsizel: LPSIZEL

	 GetExtent48@MP typedef ptr GetExtent48@CT
	      GetExtent GetExtent48@MP ?

	END_INTERFACE

IViewObject2Vtbl	ENDS

LPIViewObject2Vtbl	typedef ptr IViewObject2Vtbl
IViewObject2		STRUC
lpVtbl			LPIViewObject2Vtbl ?
IViewObject2		ENDS






;HRESULT
IViewObject2_GetExtent_Proxy proto WINAPI \
		 pThis: ptr IViewObject2,
	  dwDrawAspect: DWORD,
		lindex: LONG,
		   ptd: ptr DVTARGETDEVICE,
	       lpsizel: LPSIZEL



;void
IViewObject2_GetExtent_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IDropSource_INTERFACE_DEFINED__
__IDropSource_INTERFACE_DEFINED__ equ 1



LPDROPSOURCE		typedef ptr IDropSource


externdef		IID_IDropSource:IID


IDropSourceVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface49@CT typedef proto \
		 pThis: ptr IDropSource,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface49@MP typedef ptr QueryInterface49@CT
	 QueryInterface QueryInterface49@MP ?

	    AddRef49@CT typedef proto \
		 pThis: ptr IDropSource

	    AddRef49@MP typedef ptr AddRef49@CT
		 AddRef AddRef49@MP ?

	   Release49@CT typedef proto \
		 pThis: ptr IDropSource

	   Release49@MP typedef ptr Release49@CT
		Release Release49@MP ?

 QueryContinueDrag49@CT typedef proto \
		 pThis: ptr IDropSource,
	fEscapePressed: BOOL,
	   grfKeyState: DWORD

 QueryContinueDrag49@MP typedef ptr QueryContinueDrag49@CT
      QueryContinueDrag QueryContinueDrag49@MP ?

      GiveFeedback49@CT typedef proto \
		 pThis: ptr IDropSource,
	      dwEffect: DWORD

      GiveFeedback49@MP typedef ptr GiveFeedback49@CT
	   GiveFeedback GiveFeedback49@MP ?

	END_INTERFACE

IDropSourceVtbl		ENDS

LPIDropSourceVtbl	typedef ptr IDropSourceVtbl
IDropSource		STRUC
lpVtbl			LPIDropSourceVtbl ?
IDropSource		ENDS






;HRESULT
IDropSource_QueryContinueDrag_Proxy proto WINAPI \
		 pThis: ptr IDropSource,
	fEscapePressed: BOOL,
	   grfKeyState: DWORD



;void
IDropSource_QueryContinueDrag_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IDropSource_GiveFeedback_Proxy proto WINAPI \
		 pThis: ptr IDropSource,
	      dwEffect: DWORD



;void
IDropSource_GiveFeedback_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IDropTarget_INTERFACE_DEFINED__
__IDropTarget_INTERFACE_DEFINED__ equ 1



LPDROPTARGET		typedef ptr IDropTarget

MK_ALT			equ ( 0x20 )

DROPEFFECT_NONE		equ ( 0 )

DROPEFFECT_COPY		equ ( 1 )

DROPEFFECT_MOVE		equ ( 2 )

DROPEFFECT_LINK		equ ( 4 )

DROPEFFECT_SCROLL	equ ( 0x80000000 )

DD_DEFSCROLLINSET	equ ( 11 )

DD_DEFSCROLLDELAY	equ ( 50 )

DD_DEFSCROLLINTERVAL	equ ( 50 )

DD_DEFDRAGDELAY		equ ( 200 )

DD_DEFDRAGMINDIST	equ ( 2 )


externdef		IID_IDropTarget:IID


IDropTargetVtbl		STRUC

	BEGIN_INTERFACE

    QueryInterface50@CT typedef proto \
		 pThis: ptr IDropTarget,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface50@MP typedef ptr QueryInterface50@CT
	 QueryInterface QueryInterface50@MP ?

	    AddRef50@CT typedef proto \
		 pThis: ptr IDropTarget

	    AddRef50@MP typedef ptr AddRef50@CT
		 AddRef AddRef50@MP ?

	   Release50@CT typedef proto \
		 pThis: ptr IDropTarget

	   Release50@MP typedef ptr Release50@CT
		Release Release50@MP ?

	 DragEnter50@CT typedef proto \
		 pThis: ptr IDropTarget,
	      pDataObj: ptr IDataObject,
	   grfKeyState: DWORD,
		    pt: POINTL,
	     pdwEffect: ptr DWORD

	 DragEnter50@MP typedef ptr DragEnter50@CT
	      DragEnter DragEnter50@MP ?

	  DragOver50@CT typedef proto \
		 pThis: ptr IDropTarget,
	   grfKeyState: DWORD,
		    pt: POINTL,
	     pdwEffect: ptr DWORD

	  DragOver50@MP typedef ptr DragOver50@CT
	       DragOver DragOver50@MP ?

	 DragLeave50@CT typedef proto \
		 pThis: ptr IDropTarget

	 DragLeave50@MP typedef ptr DragLeave50@CT
	      DragLeave DragLeave50@MP ?

	      Drop50@CT typedef proto \
		 pThis: ptr IDropTarget,
	      pDataObj: ptr IDataObject,
	   grfKeyState: DWORD,
		    pt: POINTL,
	     pdwEffect: ptr DWORD

	      Drop50@MP typedef ptr Drop50@CT
		   Drop Drop50@MP ?

	END_INTERFACE

IDropTargetVtbl		ENDS

LPIDropTargetVtbl	typedef ptr IDropTargetVtbl
IDropTarget		STRUC
lpVtbl			LPIDropTargetVtbl ?
IDropTarget		ENDS






;HRESULT
IDropTarget_DragEnter_Proxy proto WINAPI \
		 pThis: ptr IDropTarget,
	      pDataObj: ptr IDataObject,
	   grfKeyState: DWORD,
		    pt: POINTL,
	     pdwEffect: ptr DWORD



;void
IDropTarget_DragEnter_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IDropTarget_DragOver_Proxy proto WINAPI \
		 pThis: ptr IDropTarget,
	   grfKeyState: DWORD,
		    pt: POINTL,
	     pdwEffect: ptr DWORD



;void
IDropTarget_DragOver_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IDropTarget_DragLeave_Proxy proto WINAPI \
		 pThis: ptr IDropTarget



;void
IDropTarget_DragLeave_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IDropTarget_Drop_Proxy proto WINAPI \
		 pThis: ptr IDropTarget,
	      pDataObj: ptr IDataObject,
	   grfKeyState: DWORD,
		    pt: POINTL,
	     pdwEffect: ptr DWORD



;void
IDropTarget_Drop_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	


ifndef __IEnumOLEVERB_INTERFACE_DEFINED__
__IEnumOLEVERB_INTERFACE_DEFINED__ equ 1



LPENUMOLEVERB		typedef ptr IEnumOLEVERB

OLEVERB			STRUC
lVerb			LONG ?
lpszVerbName		LPOLESTR ?
fuFlags			dd ?
grfAttribs		dd ?
OLEVERB			ENDS
LPOLEVERB		typedef ptr OLEVERB

;typedef /* [v1_enum] */ enum tagOLEVERBATTRIB

OLEVERBATTRIB_NEVERDIRTIES equ 1
OLEVERBATTRIB_ONCONTAINERMENU equ 2


externdef		IID_IEnumOLEVERB:IID


IEnumOLEVERBVtbl	STRUC

	BEGIN_INTERFACE

    QueryInterface51@CT typedef proto \
		 pThis: ptr IEnumOLEVERB,
		  riid: REFIID,
	     ppvObject: PVOID

    QueryInterface51@MP typedef ptr QueryInterface51@CT
	 QueryInterface QueryInterface51@MP ?

	    AddRef51@CT typedef proto \
		 pThis: ptr IEnumOLEVERB

	    AddRef51@MP typedef ptr AddRef51@CT
		 AddRef AddRef51@MP ?

	   Release51@CT typedef proto \
		 pThis: ptr IEnumOLEVERB

	   Release51@MP typedef ptr Release51@CT
		Release Release51@MP ?

	      Next51@CT typedef proto \
		 pThis: ptr IEnumOLEVERB,
		  celt: ULONG,
		 rgelt: LPOLEVERB,
	  pceltFetched: ptr ULONG

	      Next51@MP typedef ptr Next51@CT
		   Next Next51@MP ?

	      Skip51@CT typedef proto \
		 pThis: ptr IEnumOLEVERB,
		  celt: ULONG

	      Skip51@MP typedef ptr Skip51@CT
		   Skip Skip51@MP ?

	     Reset51@CT typedef proto \
		 pThis: ptr IEnumOLEVERB

	     Reset51@MP typedef ptr Reset51@CT
		  Reset Reset51@MP ?

	     Clone51@CT typedef proto \
		 pThis: ptr IEnumOLEVERB,
		ppenum: ptr IEnumOLEVERB

	     Clone51@MP typedef ptr Clone51@CT
		  Clone Clone51@MP ?

	END_INTERFACE

IEnumOLEVERBVtbl	ENDS

LPIEnumOLEVERBVtbl	typedef ptr IEnumOLEVERBVtbl
IEnumOLEVERB		STRUC
lpVtbl			LPIEnumOLEVERBVtbl ?
IEnumOLEVERB		ENDS






;HRESULT
IEnumOLEVERB_RemoteNext_Proxy proto WINAPI \
		 pThis: ptr IEnumOLEVERB,
		  celt: ULONG,
		 rgelt: LPOLEVERB,
	  pceltFetched: ptr ULONG



;void
IEnumOLEVERB_RemoteNext_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IEnumOLEVERB_Skip_Proxy proto WINAPI \
		 pThis: ptr IEnumOLEVERB,
		  celt: ULONG



;void
IEnumOLEVERB_Skip_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IEnumOLEVERB_Reset_Proxy proto WINAPI \
		 pThis: ptr IEnumOLEVERB



;void
IEnumOLEVERB_Reset_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD



;HRESULT
IEnumOLEVERB_Clone_Proxy proto WINAPI \
		 pThis: ptr IEnumOLEVERB,
		ppenum: ptr IEnumOLEVERB



;void
IEnumOLEVERB_Clone_Stub proto WINAPI \
		 pThis: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD




endif	



;DWORD
CLIPFORMAT_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr CLIPFORMAT

;LPBYTE
CLIPFORMAT_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT

;LPBYTE
CLIPFORMAT_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT

;void
CLIPFORMAT_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr CLIPFORMAT


;DWORD
HACCEL_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HACCEL

;LPBYTE
HACCEL_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HACCEL

;LPBYTE
HACCEL_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HACCEL

;void
HACCEL_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr HACCEL

;DWORD
HGLOBAL_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HGLOBAL

;LPBYTE
HGLOBAL_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HGLOBAL

;LPBYTE
HGLOBAL_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HGLOBAL

;void
HGLOBAL_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr HGLOBAL


;DWORD
HMENU_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HMENU

;LPBYTE
HMENU_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HMENU

;LPBYTE
HMENU_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HMENU

;void
HMENU_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr HMENU


;DWORD
HWND_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HWND

;LPBYTE
HWND_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HWND

;LPBYTE
HWND_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HWND

;void
HWND_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr HWND


;DWORD
STGMEDIUM_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr STGMEDIUM
;LPBYTE
STGMEDIUM_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr STGMEDIUM
;LPBYTE
STGMEDIUM_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr STGMEDIUM

;void
STGMEDIUM_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr STGMEDIUM


;HRESULT
IOleInPlaceActiveObject_TranslateAccelerator_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceActiveObject,
		 lpmsg: LPMSG



;HRESULT
IOleInPlaceActiveObject_TranslateAccelerator_Stub proto WINAPI \
		 pThis: ptr IOleInPlaceActiveObject


;HRESULT
IOleInPlaceActiveObject_ResizeBorder_Proxy proto WINAPI \
		 pThis: ptr IOleInPlaceActiveObject,
	     prcBorder: LPCRECT,
	     pUIWindow: ptr IOleInPlaceUIWindow,
	  fFrameWindow: BOOL



;HRESULT
IOleInPlaceActiveObject_ResizeBorder_Stub proto WINAPI \
		 pThis: ptr IOleInPlaceActiveObject,
	     prcBorder: LPCRECT,
		  riid: REFIID,
	     pUIWindow: ptr IOleInPlaceUIWindow,
	  fFrameWindow: BOOL


       pfnContinue52@CT typedef proto \
	    dwContinue: DWORD
       pfnContinue52@MP typedef ptr pfnContinue52@CT

;HRESULT
IViewObject_Draw_Proxy proto WINAPI \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: ptr void,
		   ptd: ptr DVTARGETDEVICE,
	  hdcTargetDev: HDC,
	       hdcDraw: HDC,
	    lprcBounds: LPCRECTL,
	   lprcWBounds: LPCRECTL,
	   pfnContinue: pfnContinue52@MP,
	    dwContinue: DWORD



;HRESULT
IViewObject_Draw_Stub proto WINAPI \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: DWORD,
		   ptd: ptr DVTARGETDEVICE,
	  hdcTargetDev: DWORD,
	       hdcDraw: DWORD,
	    lprcBounds: LPCRECTL,
	   lprcWBounds: LPCRECTL,
	     pContinue: ptr IContinue


;HRESULT
IViewObject_GetColorSet_Proxy proto WINAPI \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: ptr void,
		   ptd: ptr DVTARGETDEVICE,
	  hicTargetDev: HDC,
	    ppColorSet: ptr LOGPALETTE



;HRESULT
IViewObject_GetColorSet_Stub proto WINAPI \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: DWORD,
		   ptd: ptr DVTARGETDEVICE,
	  hicTargetDev: DWORD,
	    ppColorSet: ptr LOGPALETTE


;HRESULT
IViewObject_Freeze_Proxy proto WINAPI \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: PVOID,
	     pdwFreeze: LPDWORD



;HRESULT
IViewObject_Freeze_Stub proto WINAPI \
		 pThis: ptr IViewObject,
	  dwDrawAspect: DWORD,
		lindex: LONG,
	      pvAspect: DWORD,
	     pdwFreeze: LPDWORD


;HRESULT
IViewObject_GetAdvise_Proxy proto WINAPI \
		 pThis: ptr IViewObject,
	      pAspects: LPDWORD,
		 pAdvf: LPDWORD,
	     ppAdvSink: ptr IAdviseSink



;HRESULT
IViewObject_GetAdvise_Stub proto WINAPI \
		 pThis: ptr IViewObject,
	      pAspects: LPDWORD,
		 pAdvf: LPDWORD,
	     ppAdvSink: ptr IAdviseSink


;HRESULT
IEnumOLEVERB_Next_Proxy proto WINAPI \
		 pThis: ptr IEnumOLEVERB,
		  celt: ULONG,
		 rgelt: LPOLEVERB,
	  pceltFetched: ptr ULONG



;HRESULT
IEnumOLEVERB_Next_Stub proto WINAPI \
		 pThis: ptr IEnumOLEVERB,
		  celt: ULONG,
		 rgelt: LPOLEVERB,
	  pceltFetched: ptr ULONG


;HRESULT
IOleCache2_UpdateCache_Proxy proto WINAPI \
		 pThis: ptr IOleCache2,
	   pDataObject: LPDATAOBJECT,
	       grfUpdf: DWORD,
	     pReserved: LPVOID



;HRESULT
IOleCache2_UpdateCache_Stub proto WINAPI \
		 pThis: ptr IOleCache2,
	   pDataObject: LPDATAOBJECT,
	       grfUpdf: DWORD,
	     pReserved: DWORD



.list

endif
