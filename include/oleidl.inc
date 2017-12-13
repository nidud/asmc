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

;void
MIDL_user_free proto WINAPI :PVOID

externdef		__MIDL_itf_oleidl_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_oleidl_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IOleAdviseHolder_INTERFACE_DEFINED__
__IOleAdviseHolder_INTERFACE_DEFINED__ equ 1

IOleAdviseHolder	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Advise, :ptr, :ptr
	STDMETHOD	Unadvise, :DWORD
	STDMETHOD	EnumAdvise, :ptr ptr
	STDMETHOD	SendOnRename, :ptr
	STDMETHOD	SendOnSave
	STDMETHOD	SendOnClose
IOleAdviseHolder	ENDS
LPOLEADVISEHOLDER	typedef ptr IOleAdviseHolder
externdef		IID_IOleAdviseHolder:IID

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

IOleCache		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Cache, :ptr, :DWORD, :ptr
	STDMETHOD	Uncache, :DWORD
	STDMETHOD	EnumCache, :ptr
	STDMETHOD	InitCache, :ptr
	STDMETHOD	SetData, :ptr, :ptr, :BOOL
IOleCache		ENDS
LPOLECACHE		typedef ptr IOleCache
externdef		IID_IOleCache:IID

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

tagDISCARDCACHE		typedef SDWORD
DISCARDCACHE_SAVEIFDIRTY equ 0
DISCARDCACHE_NOSAVE	equ 1

externdef		IID_IOleCache2:IID

IOleCache2		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Cache, :ptr, :DWORD, :ptr
	STDMETHOD	Uncache, :DWORD
	STDMETHOD	EnumCache, :ptr
	STDMETHOD	InitCache, :ptr
	STDMETHOD	SetData, :ptr, :ptr, :BOOL
	STDMETHOD	UpdateCache, :LPDATAOBJECT, :DWORD, :LPVOID
	STDMETHOD	DiscardCache, :DWORD
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

IOleCacheControl	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	OnRun, :LPDATAOBJECT
	STDMETHOD	OnStop
IOleCacheControl	ENDS
PPOLECACHECONTROL	typedef ptr IOleCacheControl
externdef		IID_IOleCacheControl:IID

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

IParseDisplayName	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ParseDisplayName, :ptr, :LPOLESTR, :ptr, :ptr
IParseDisplayName	ENDS
LPPARSEDISPLAYNAME	typedef ptr IParseDisplayName
externdef		IID_IParseDisplayName:IID

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

IOleContainerVtbl	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ParseDisplayName, :ptr, :LPOLESTR, :ptr, :ptr
	STDMETHOD	EnumObjects_, :DWORD, :ptr
	STDMETHOD	LockContainer, :BOOL
IOleContainerVtbl	ENDS
LPOLECONTAINER		typedef ptr IOleContainer
externdef		IID_IOleContainer:IID

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

IOleClientSite		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SaveObject
	STDMETHOD	GetMoniker, :DWORD, :DWORD, :ptr
	STDMETHOD	GetContainer, :ptr
	STDMETHOD	ShowObject
	STDMETHOD	OnShowWindow, :BOOL
	STDMETHOD	RequestNewObjectLayout
IOleClientSite		ENDS
LPOLECLIENTSITE		typedef ptr IOleClientSite
externdef		IID_IOleClientSite:IID

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


IOleObject		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetClientSite, :ptr
	STDMETHOD	GetClientSite, :ptr
	STDMETHOD	SetHostNames, :LPCOLESTR, :LPCOLESTR
	STDMETHOD	Close, :DWORD
	STDMETHOD	SetMoniker, :DWORD, :ptr
	STDMETHOD	GetMoniker, :DWORD, :DWORD, :ptr
	STDMETHOD	InitFromData, :ptr, :BOOL, :DWORD
	STDMETHOD	GetClipboardData_, :DWORD ,:ptr
	STDMETHOD	DoVerb, :SDWORD,: LPMSG, :ptr, :SDWORD, :HWND, :LPCRECT
	STDMETHOD	EnumVerbs, :ptr
	STDMETHOD	Update
	STDMETHOD	IsUpToDate
	STDMETHOD	GetUserClassID, :ptr
	STDMETHOD	GetUserType, :DWORD, :ptr
	STDMETHOD	SetExtent, :DWORD, :ptr
	STDMETHOD	GetExtent, :DWORD, :ptr
	STDMETHOD	Advise, :ptr, :ptr
	STDMETHOD	Unadvise, :DWORD
	STDMETHOD	EnumAdvise, :ptr
	STDMETHOD	GetMiscStatus, :DWORD, :ptr
	STDMETHOD	SetColorScheme, :ptr
IOleObject		ENDS
LPOLEOBJECT		typedef ptr IOleObject
externdef		IID_IOleObject:IID

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

IOleWindow		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow_, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
IOleWindow		ENDS
LPOLEWINDOW		typedef ptr IOleWindow
externdef		IID_IOleWindow:IID

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

;typedef enum tagOLEUPDATE

OLEUPDATE_ALWAYS	equ 1
OLEUPDATE_ONCALL	equ 3

LPOLEUPDATE		typedef ptr OLEUPDATE
POLEUPDATE		typedef ptr OLEUPDATE

;typedef enum tagOLELINKBIND

OLELINKBIND_EVENIFCLASSDIFF equ 1

IOleLink		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	SetUpdateOptions, :DWORD
	STDMETHOD	GetUpdateOptions, :ptr
	STDMETHOD	SetSourceMoniker, :ptr, :REFCLSID
	STDMETHOD	GetSourceMoniker, :ptr
	STDMETHOD	SetSourceDisplayName, :LPCOLESTR
	STDMETHOD	GetSourceDisplayName, :ptr
	STDMETHOD	BindToSource, :DWORD, :ptr
	STDMETHOD	BindIfRunning
	STDMETHOD	GetBoundSource, :ptr
	STDMETHOD	UnbindSource
	STDMETHOD	Update, :ptr
IOleLink		ENDS
LPOLELINK		typedef ptr IOleLink
externdef		IID_IOleLink:IID

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

IOleItemContainer	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	ParseDisplayName, :ptr, :LPOLESTR, :ptr, :ptr
	STDMETHOD	EnumObjects_, :DWORD, :ptr
	STDMETHOD	LockContainer, :BOOL
	STDMETHOD	GetObject_, :LPOLESTR, :DWORD, :ptr, :REFIID, :ptr
	STDMETHOD	GetObjectStorage, :LPOLESTR, :ptr, :REFIID, :ptr
	STDMETHOD	IsRunning, :LPOLESTR
IOleItemContainer	ENDS
LPOLEITEMCONTAINER	typedef ptr IOleItemContainer
externdef		IID_IOleItemContainer:IID

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

BORDERWIDTHS		typedef RECT
LPBORDERWIDTHS		typedef LPRECT
LPCBORDERWIDTHS		typedef LPCRECT

IOleInPlaceUIWindow	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow_, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	GetBorder, :LPRECT
	STDMETHOD	RequestBorderSpace, :LPCBORDERWIDTHS
	STDMETHOD	SetBorderSpace, :LPCBORDERWIDTHS
	STDMETHOD	SetActiveObject, :ptr, :LPCOLESTR
IOleInPlaceUIWindow	ENDS
LPOLEINPLACEUIWINDOW	typedef ptr IOleInPlaceUIWindow
externdef		IID_IOleInPlaceUIWindow:IID

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

IOleInPlaceActiveObject STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow_, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	TranslateAccelerator_, :LPMSG
	STDMETHOD	OnFrameWindowActivate, :BOOL
	STDMETHOD	OnDocWindowActivate, :BOOL
	STDMETHOD	ResizeBorder, :LPCRECT, :ptr, :BOOL
	STDMETHOD	EnableModeless, :BOOL
IOleInPlaceActiveObject ENDS
LPOLEINPLACEACTIVEOBJECT typedef ptr IOleInPlaceActiveObject
externdef		IID_IOleInPlaceActiveObject:IID

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

IOleInPlaceFrame	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow_, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	GetBorder, :LPRECT
	STDMETHOD	RequestBorderSpace, :LPCBORDERWIDTHS
	STDMETHOD	SetBorderSpace, :LPCBORDERWIDTHS
	STDMETHOD	SetActiveObject, :ptr, :LPCOLESTR
	STDMETHOD	InsertMenus, :HMENU, :LPOLEMENUGROUPWIDTHS
	STDMETHOD	SetMenu_, :HMENU, :HOLEMENU, :HWND
	STDMETHOD	RemoveMenus, :HMENU
	STDMETHOD	SetStatusText, :LPCOLESTR
	STDMETHOD	EnableModeless, :BOOL
	STDMETHOD	TranslateAccelerator_, :LPMSG, :WORD
IOleInPlaceFrame	ENDS
LPOLEINPLACEFRAME	typedef ptr IOleInPlaceFrame

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

IOleInPlaceObject	STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow_, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	InPlaceDeactivate
	STDMETHOD	UIDeactivate
	STDMETHOD	SetObjectRects, :LPCRECT, :LPCRECT
	STDMETHOD	ReactivateAndUndo
IOleInPlaceObject	ENDS
LPOLEINPLACEOBJECT	typedef ptr IOleInPlaceObject
externdef		IID_IOleInPlaceObject:IID

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

IOleInPlaceSite		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	GetWindow_, :ptr
	STDMETHOD	ContextSensitiveHelp, :BOOL
	STDMETHOD	CanInPlaceActivate
	STDMETHOD	OnInPlaceActivate
	STDMETHOD	OnUIActivate
	STDMETHOD	GetWindowContext, :ptr, :ptr, :LPRECT, :LPRECT, :LPOLEINPLACEFRAMEINFO
	STDMETHOD	Scroll, :SIZE_T
	STDMETHOD	OnUIDeactivate, :BOOL
	STDMETHOD	OnInPlaceDeactivate
	STDMETHOD	DiscardUndoState
	STDMETHOD	DeactivateAndUndo,
	STDMETHOD	OnPosRectChange, :LPCRECT
IOleInPlaceSite		ENDS
LPOLEINPLACESITE	typedef ptr IOleInPlaceSite
externdef		IID_IOleInPlaceSite:IID

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

IContinue		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	FContinue
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

IViewObject		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Draw, :DWORD, :SDWORD, :ptr ,:ptr, :HDC, :HDC, :LPCRECTL, :LPCRECTL, :ptr, :DWORD
	STDMETHOD	GetColorSet, :DWORD, :SDWORD, :ptr ,:ptr, :HDC, :ptr
	STDMETHOD	Freeze, :DWORD, :SDWORD, :ptr ,:ptr
	STDMETHOD	Unfreeze, :DWORD
	STDMETHOD	SetAdvise, :DWORD, :DWORD, :ptr
	STDMETHOD	GetAdvise, :ptr, :ptr, :ptr
IViewObject		ENDS
LPVIEWOBJECT		typedef ptr IViewObject
externdef		IID_IViewObject:IID

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

IViewObject2		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Draw, :DWORD, :SDWORD, :ptr ,:ptr, :HDC, :HDC, :LPCRECTL, :LPCRECTL, :ptr, :DWORD
	STDMETHOD	GetColorSet, :DWORD, :SDWORD, :ptr, :ptr, :HDC, :ptr
	STDMETHOD	Freeze, :DWORD, :SDWORD, :ptr, :ptr
	STDMETHOD	Unfreeze, :DWORD
	STDMETHOD	SetAdvise, :DWORD, :DWORD, :ptr
	STDMETHOD	GetAdvise, :ptr, :ptr, :ptr
	STDMETHOD	GetExtent, :DWORD, :SDWORD, :ptr, :LPSIZEL
IViewObject2		ENDS
LPVIEWOBJECT2		typedef ptr IViewObject2
externdef		IID_IViewObject2:IID

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

IDropSource		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	QueryContinueDrag, :BOOL, :DWORD
	STDMETHOD	GiveFeedback, :DWORD
IDropSource		ENDS
LPDROPSOURCE		typedef ptr IDropSource
externdef		IID_IDropSource:IID

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

IDropTarget		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	DragEnter, :ptr, :DWORD, :POINTL, :ptr
	STDMETHOD	DragOver, :DWORD, :POINTL, :ptr
	STDMETHOD	DragLeave
	STDMETHOD	Drop, :ptr, :DWORD, :POINTL, :ptr
IDropTarget		ENDS
LPDROPTARGET		typedef ptr IDropTarget
externdef		IID_IDropTarget:IID

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

IEnumOLEVERB		STRUC
	STDMETHOD	QueryInterface, :REFIID, :ptr
	STDMETHOD	AddRef
	STDMETHOD	Release
	STDMETHOD	Next, :DWORD, :LPOLEVERB, :ptr
	STDMETHOD	Skip, :DWORD
	STDMETHOD	Reset
	STDMETHOD	Clone, :ptr
IEnumOLEVERB		ENDS
LPENUMOLEVERB		typedef ptr IEnumOLEVERB
externdef		IID_IEnumOLEVERB:IID

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
