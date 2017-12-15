ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
__REQUIRED_RPCSAL_H_VERSION__ equ 100
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
ifndef __ocidl_h__
__ocidl_h__ equ 1
.xlist

ifndef __IEnumConnections_FWD_DEFINED__
__IEnumConnections_FWD_DEFINED__ equ 1
endif

ifndef __IConnectionPoint_FWD_DEFINED__
__IConnectionPoint_FWD_DEFINED__ equ 1
endif

ifndef __IEnumConnectionPoints_FWD_DEFINED__
__IEnumConnectionPoints_FWD_DEFINED__ equ 1
endif

ifndef __IConnectionPointContainer_FWD_DEFINED__
__IConnectionPointContainer_FWD_DEFINED__ equ 1
endif

ifndef __IClassFactory2_FWD_DEFINED__
__IClassFactory2_FWD_DEFINED__ equ 1
endif

ifndef __IProvideClassInfo_FWD_DEFINED__
__IProvideClassInfo_FWD_DEFINED__ equ 1
endif

ifndef __IProvideClassInfo2_FWD_DEFINED__
__IProvideClassInfo2_FWD_DEFINED__ equ 1
endif

ifndef __IProvideMultipleClassInfo_FWD_DEFINED__
__IProvideMultipleClassInfo_FWD_DEFINED__ equ 1
endif

ifndef __IOleControl_FWD_DEFINED__
__IOleControl_FWD_DEFINED__ equ 1
endif

ifndef __IOleControlSite_FWD_DEFINED__
__IOleControlSite_FWD_DEFINED__ equ 1
endif

ifndef __IPropertyPage_FWD_DEFINED__
__IPropertyPage_FWD_DEFINED__ equ 1
endif

ifndef __IPropertyPage2_FWD_DEFINED__
__IPropertyPage2_FWD_DEFINED__ equ 1
endif

ifndef __IPropertyPageSite_FWD_DEFINED__
__IPropertyPageSite_FWD_DEFINED__ equ 1
endif

ifndef __IPropertyNotifySink_FWD_DEFINED__
__IPropertyNotifySink_FWD_DEFINED__ equ 1
endif

ifndef __ISpecifyPropertyPages_FWD_DEFINED__
__ISpecifyPropertyPages_FWD_DEFINED__ equ 1
endif

ifndef __IPersistMemory_FWD_DEFINED__
__IPersistMemory_FWD_DEFINED__ equ 1
endif

ifndef __IPersistStreamInit_FWD_DEFINED__
__IPersistStreamInit_FWD_DEFINED__ equ 1
endif

ifndef __IPersistPropertyBag_FWD_DEFINED__
__IPersistPropertyBag_FWD_DEFINED__ equ 1
endif

ifndef __ISimpleFrameSite_FWD_DEFINED__
__ISimpleFrameSite_FWD_DEFINED__ equ 1
endif

ifndef __IFont_FWD_DEFINED__
__IFont_FWD_DEFINED__ equ 1
endif

ifndef __IPicture_FWD_DEFINED__
__IPicture_FWD_DEFINED__ equ 1
endif

ifndef __IPicture2_FWD_DEFINED__
__IPicture2_FWD_DEFINED__ equ 1
endif

ifndef __IFontEventsDisp_FWD_DEFINED__
__IFontEventsDisp_FWD_DEFINED__ equ 1
endif

ifndef __IFontDisp_FWD_DEFINED__
__IFontDisp_FWD_DEFINED__ equ 1
endif

ifndef __IPictureDisp_FWD_DEFINED__
__IPictureDisp_FWD_DEFINED__ equ 1
endif

ifndef __IOleInPlaceObjectWindowless_FWD_DEFINED__
__IOleInPlaceObjectWindowless_FWD_DEFINED__ equ 1
endif

ifndef __IOleInPlaceSiteEx_FWD_DEFINED__
__IOleInPlaceSiteEx_FWD_DEFINED__ equ 1
endif

ifndef __IOleInPlaceSiteWindowless_FWD_DEFINED__
__IOleInPlaceSiteWindowless_FWD_DEFINED__ equ 1
endif

ifndef __IViewObjectEx_FWD_DEFINED__
__IViewObjectEx_FWD_DEFINED__ equ 1
endif

ifndef __IOleUndoUnit_FWD_DEFINED__
__IOleUndoUnit_FWD_DEFINED__ equ 1
endif

ifndef __IOleParentUndoUnit_FWD_DEFINED__
__IOleParentUndoUnit_FWD_DEFINED__ equ 1
endif

ifndef __IEnumOleUndoUnits_FWD_DEFINED__
__IEnumOleUndoUnits_FWD_DEFINED__ equ 1
endif

ifndef __IOleUndoManager_FWD_DEFINED__
__IOleUndoManager_FWD_DEFINED__ equ 1
endif

ifndef __IPointerInactive_FWD_DEFINED__
__IPointerInactive_FWD_DEFINED__ equ 1
endif

ifndef __IObjectWithSite_FWD_DEFINED__
__IObjectWithSite_FWD_DEFINED__ equ 1
endif

ifndef __IPerPropertyBrowsing_FWD_DEFINED__
__IPerPropertyBrowsing_FWD_DEFINED__ equ 1
endif

ifndef __IPropertyBag2_FWD_DEFINED__
__IPropertyBag2_FWD_DEFINED__ equ 1
endif

ifndef __IPersistPropertyBag2_FWD_DEFINED__
__IPersistPropertyBag2_FWD_DEFINED__ equ 1
endif

ifndef __IAdviseSinkEx_FWD_DEFINED__
__IAdviseSinkEx_FWD_DEFINED__ equ 1
endif

ifndef __IQuickActivate_FWD_DEFINED__
__IQuickActivate_FWD_DEFINED__ equ 1
endif

include oleidl.inc
include oaidl.inc
include servprov.inc
include urlmon.inc
.xlist

externdef		__MIDL_itf_ocidl_0000_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef		__MIDL_itf_ocidl_0000_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IOleControlTypes_INTERFACE_DEFINED__
__IOleControlTypes_INTERFACE_DEFINED__ equ 1

tagUASFLAGS		typedef SDWORD
UAS_NORMAL		equ 0
UAS_BLOCKED		equ 0x1
UAS_NOPARENTENABLE	equ 0x2
UAS_MASK		equ 0x3

tagREADYSTATE		typedef SDWORD
READYSTATE_UNINITIALIZED equ 0
READYSTATE_LOADING	equ 1
READYSTATE_LOADED	equ 2
READYSTATE_INTERACTIVE	equ 3
READYSTATE_COMPLETE	equ 4

externdef		IOleControlTypes_v1_0_c_ifspec:RPC_IF_HANDLE
externdef		IOleControlTypes_v1_0_s_ifspec:RPC_IF_HANDLE
endif

ifndef __IEnumConnections_INTERFACE_DEFINED__
__IEnumConnections_INTERFACE_DEFINED__ equ 1

PENUMCONNECTIONS	typedef ptr IEnumConnections
LPENUMCONNECTIONS	typedef ptr IEnumConnections
CONNECTDATA		STRUC
pUnk			LPIUnknown ?
dwCookie		dd ?
CONNECTDATA		ENDS
PCONNECTDATA		typedef ptr CONNECTDATA
LPCONNECTDATA		typedef ptr CONNECTDATA

externdef		IID_IEnumConnections:IID
IEnumConnections	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		Next, :DWORD, :LPCONNECTDATA, :ptr
STDMETHOD		Skip, :DWORD
STDMETHOD		Reset
STDMETHOD		Clone, :ptr
IEnumConnections	ENDS

;HRESULT
IEnumConnections_RemoteNext_Proxy proto WINAPI \
		 _This: ptr IEnumConnections,
	  cConnections: ULONG,
		  rgcd: LPCONNECTDATA,
	     pcFetched: ptr ULONG

;void
IEnumConnections_RemoteNext_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IConnectionPoint_INTERFACE_DEFINED__
__IConnectionPoint_INTERFACE_DEFINED__ equ 1


IConnectionPoint	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetConnectionInterface, :ptr
STDMETHOD		GetConnectionPointContainer, :ptr
STDMETHOD		Advise, :ptr, :ptr
STDMETHOD		Unadvise, :DWORD
STDMETHOD		EnumConnections, :ptr
IConnectionPoint	ENDS
PCONNECTIONPOINT	typedef ptr IConnectionPoint
LPCONNECTIONPOINT	typedef ptr IConnectionPoint
externdef		IID_IConnectionPoint:IID

endif

ifndef __IEnumConnectionPoints_INTERFACE_DEFINED__
__IEnumConnectionPoints_INTERFACE_DEFINED__ equ 1


IEnumConnectionPoints	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		Next, :DWORD, :ptr, :ptr
STDMETHOD		Skip, :DWORD
STDMETHOD		Reset
STDMETHOD		Clone, :ptr
IEnumConnectionPoints	ENDS
PENUMCONNECTIONPOINTS	typedef ptr IEnumConnectionPoints
LPENUMCONNECTIONPOINTS	typedef ptr IEnumConnectionPoints
externdef		IID_IEnumConnectionPoints:IID

;HRESULT
IEnumConnectionPoints_RemoteNext_Proxy proto WINAPI \
		 _This: ptr IEnumConnectionPoints,
	  cConnections: ULONG,
		  ppCP: ptr LPCONNECTIONPOINT,
	     pcFetched: ptr ULONG

;void
IEnumConnectionPoints_RemoteNext_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IConnectionPointContainer_INTERFACE_DEFINED__
__IConnectionPointContainer_INTERFACE_DEFINED__ equ 1


IConnectionPointContainer STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		EnumConnectionPoints, :ptr
STDMETHOD		FindConnectionPoint, :REFIID, :ptr
IConnectionPointContainer ENDS
PCONNECTIONPOINTCONTAINER typedef ptr IConnectionPointContainer
LPCONNECTIONPOINTCONTAINER typedef ptr IConnectionPointContainer
externdef		IID_IConnectionPointContainer:IID

endif

ifndef __IClassFactory2_INTERFACE_DEFINED__
__IClassFactory2_INTERFACE_DEFINED__ equ 1


LICINFO			STRUC
cbLicInfo		LONG ?
fRuntimeKeyAvail	BOOL ?
fLicVerified		BOOL ?
LICINFO			ENDS
LPLICINFO		typedef ptr LICINFO

IClassFactory2		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		CreateInstance, :ptr, :REFIID, :ptr
STDMETHOD		LockServer, :BOOL
STDMETHOD		GetLicInfo, :ptr
STDMETHOD		RequestLicKey, :DWORD, :ptr
STDMETHOD		CreateInstanceLic, :ptr, :ptr, :REFIID, :BSTR, :ptr
IClassFactory2		ENDS
LPCLASSFACTORY2		typedef ptr IClassFactory2
externdef		IID_IClassFactory2:IID

;HRESULT
IClassFactory2_RemoteCreateInstanceLic_Proxy proto WINAPI \
		 _This: ptr IClassFactory2,
		  riid: REFIID,
	       bstrKey: BSTR,
		ppvObj: ptr IUnknown

;void
IClassFactory2_RemoteCreateInstanceLic_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IProvideClassInfo_INTERFACE_DEFINED__
__IProvideClassInfo_INTERFACE_DEFINED__ equ 1


IProvideClassInfo	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetClassInfo, :ptr
IProvideClassInfo	ENDS
LPPROVIDECLASSINFO	typedef ptr IProvideClassInfo
externdef		IID_IProvideClassInfo:IID

endif


ifndef __IProvideClassInfo2_INTERFACE_DEFINED__
__IProvideClassInfo2_INTERFACE_DEFINED__ equ 1

;GUIDKIND		typedef enum tagGUIDKIND {
GUIDKIND_DEFAULT_SOURCE_DISP_IID	equ 1

IProvideClassInfo2	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetClassInfo, :ptr
STDMETHOD		GetGUID, :DWORD, :ptr
IProvideClassInfo2	ENDS
LPPROVIDECLASSINFO2	typedef ptr IProvideClassInfo2
externdef		IID_IProvideClassInfo2:IID

endif


ifndef __IProvideMultipleClassInfo_INTERFACE_DEFINED__
__IProvideMultipleClassInfo_INTERFACE_DEFINED__ equ 1


MULTICLASSINFO_GETTYPEINFO equ 0x00000001
MULTICLASSINFO_GETNUMRESERVEDDISPIDS equ 0x00000002
MULTICLASSINFO_GETIIDPRIMARY equ 0x00000004
MULTICLASSINFO_GETIIDSOURCE equ 0x00000008
TIFLAGS_EXTENDDISPATCHONLY equ 0x00000001

externdef		IID_IProvideMultipleClassInfo:IID
IProvideMultipleClassInfo STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetClassInfo, :ptr
STDMETHOD		GetGUID, :DWORD, :ptr
STDMETHOD		GetMultiTypeInfoCount, :ptr
STDMETHOD		GetInfoOfIndex, :ULONG, :DWORD, :ptr, :ptr, :ptr, :ptr, :ptr
IProvideMultipleClassInfo ENDS
LPPROVIDEMULTIPLECLASSINFO typedef ptr IProvideMultipleClassInfo

endif

ifndef __IOleControl_INTERFACE_DEFINED__
__IOleControl_INTERFACE_DEFINED__ equ 1


CONTROLINFO		STRUC
cb			ULONG ?
hAccel			HACCEL ?
cAccel			USHORT ?
dwFlags			dd ?
CONTROLINFO		ENDS
LPCONTROLINFO		typedef ptr CONTROLINFO

;CTRLINFO		 typedef enum tagCTRLINFO {
CTRLINFO_EATS_RETURN	equ 1
CTRLINFO_EATS_ESCAPE	equ 2

externdef		IID_IOleControl:IID
IOleControl		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetControlInfo, :ptr
STDMETHOD		OnMnemonic, :ptr
STDMETHOD		OnAmbientPropertyChange, :DISPID
STDMETHOD		FreezeEvents, :BOOL
IOleControl		ENDS
LPOLECONTROL		typedef ptr IOleControl

endif

ifndef __IOleControlSite_INTERFACE_DEFINED__
__IOleControlSite_INTERFACE_DEFINED__ equ 1


POINTF			STRUC
x			FLOAT ?
y			FLOAT ?
POINTF			ENDS
LPPOINTF		typedef ptr POINTF

XFORMCOORDS		typedef SDWORD
XFORMCOORDS_POSITION	equ 0x1
XFORMCOORDS_SIZE	equ 0x2
XFORMCOORDS_HIMETRICTOCONTAINER equ 0x4
XFORMCOORDS_CONTAINERTOHIMETRIC equ 0x8
XFORMCOORDS_EVENTCOMPAT equ 0x10

IOleControlSite		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		OnControlInfoChanged
STDMETHOD		LockInPlaceActive, :BOOL
STDMETHOD		GetExtendedControl, :ptr
STDMETHOD		TransformCoords, :ptr, :ptr, :DWORD
STDMETHOD		TranslateAccelerator_, :ptr, :DWORD
STDMETHOD		OnFocus, :BOOL
STDMETHOD		ShowPropertyFrame
IOleControlSite		ENDS
LPOLECONTROLSITE	typedef ptr IOleControlSite
LPIOleControlSite	typedef ptr IOleControlSite
externdef		IID_IOleControlSite:IID

endif

ifndef __IPropertyPage_INTERFACE_DEFINED__
__IPropertyPage_INTERFACE_DEFINED__ equ 1


PROPPAGEINFO		STRUC
cb			ULONG ?
pszTitle		LPOLESTR ?
_size			tagSIZE <>
pszDocString		LPOLESTR ?
pszHelpFile		LPOLESTR ?
dwHelpContext		dd ?
PROPPAGEINFO		ENDS
LPPROPPAGEINFO		typedef ptr PROPPAGEINFO

IPropertyPage		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		SetPageSite, :ptr
STDMETHOD		Activate, :HWND, :LPCRECT, :BOOL
STDMETHOD		Deactivate,
STDMETHOD		GetPageInfo, :ptr
STDMETHOD		SetObjects, :DWORD, :ptr
STDMETHOD		Show, :DWORD
STDMETHOD		Move, :LPCRECT
STDMETHOD		IsPageDirty
STDMETHOD		Apply
STDMETHOD		Help, :LPCOLESTR
STDMETHOD		TranslateAccelerator_, :ptr
IPropertyPage		ENDS
LPPROPERTYPAGE		typedef ptr IPropertyPage
externdef		IID_IPropertyPage:IID

endif


ifndef __IPropertyPage2_INTERFACE_DEFINED__
__IPropertyPage2_INTERFACE_DEFINED__ equ 1


IPropertyPage2		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		SetPageSite, :ptr
STDMETHOD		Activate, :HWND, :LPCRECT, :BOOL
STDMETHOD		Deactivate
STDMETHOD		GetPageInfo, :ptr
STDMETHOD		SetObjects, :DWORD, :ptr
STDMETHOD		Show, :DWORD
STDMETHOD		Move, :LPCRECT
STDMETHOD		IsPageDirty
STDMETHOD		Apply
STDMETHOD		Help, :LPCOLESTR
STDMETHOD		TranslateAccelerator_, :ptr
STDMETHOD		EditProperty, :DISPID
IPropertyPage2		ENDS
LPPROPERTYPAGE2		typedef ptr IPropertyPage2
externdef		IID_IPropertyPage2:IID

endif


ifndef __IPropertyPageSite_INTERFACE_DEFINED__
__IPropertyPageSite_INTERFACE_DEFINED__ equ 1


PROPPAGESTATUS		typedef SDWORD
PROPPAGESTATUS_DIRTY	equ 0x1
PROPPAGESTATUS_VALIDATE equ 0x2
PROPPAGESTATUS_CLEAN	equ 0x4

IPropertyPageSite	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		OnStatusChange, :DWORD
STDMETHOD		GetLocaleID, :ptr
STDMETHOD		GetPageContainer, :ptr
STDMETHOD		TranslateAccelerator_, :ptr
IPropertyPageSite	ENDS
LPPROPERTYPAGESITE	typedef ptr IPropertyPageSite
externdef		IID_IPropertyPageSite:IID

endif


ifndef __IPropertyNotifySink_INTERFACE_DEFINED__
__IPropertyNotifySink_INTERFACE_DEFINED__ equ 1


IPropertyNotifySink	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		OnChanged, :DISPID
STDMETHOD		OnRequestEdit, :DISPID
IPropertyNotifySink	ENDS
LPPROPERTYNOTIFYSINK	typedef ptr IPropertyNotifySink
externdef		IID_IPropertyNotifySink:IID

endif


ifndef __ISpecifyPropertyPages_INTERFACE_DEFINED__
__ISpecifyPropertyPages_INTERFACE_DEFINED__ equ 1


CAUUID			STRUC
cElems			ULONG ?
pElems			LPGUID ?
CAUUID			ENDS
LPCAUUID		typedef ptr CAUUID

ISpecifyPropertyPages	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetPages, :ptr
ISpecifyPropertyPages	ENDS
LPSPECIFYPROPERTYPAGES	typedef ptr ISpecifyPropertyPages
externdef		IID_ISpecifyPropertyPages:IID

endif

ifndef __IPersistMemory_INTERFACE_DEFINED__
__IPersistMemory_INTERFACE_DEFINED__ equ 1


IPersistMemory		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetClassID, :ptr
STDMETHOD		IsDirty
STDMETHOD		Load, :LPVOID, :ULONG
STDMETHOD		Save, :LPVOID, :BOOL, :ULONG
STDMETHOD		GetSizeMax, :ptr
STDMETHOD		InitNew
IPersistMemory		ENDS
LPPERSISTMEMORY		typedef ptr IPersistMemory
externdef		IID_IPersistMemory:IID

;HRESULT
IPersistMemory_RemoteLoad_Proxy proto WINAPI \
		 _This: ptr IPersistMemory,
		  pMem: ptr BYTE,
		cbSize: ULONG

;void
IPersistMemory_RemoteLoad_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

;HRESULT
IPersistMemory_RemoteSave_Proxy proto WINAPI \
		 _This: ptr IPersistMemory,
		  pMem: ptr BYTE,
	   fClearDirty: BOOL,
		cbSize: ULONG

;void
IPersistMemory_RemoteSave_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IPersistStreamInit_INTERFACE_DEFINED__
__IPersistStreamInit_INTERFACE_DEFINED__ equ 1


IPersistStreamInit	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetClassID, :ptr
STDMETHOD		IsDirty
STDMETHOD		Load, :LPSTREAM
STDMETHOD		Save, :LPSTREAM, :BOOL
STDMETHOD		GetSizeMax, :ptr
STDMETHOD		InitNew
IPersistStreamInit	ENDS
LPPERSISTSTREAMINIT	typedef ptr IPersistStreamInit
externdef		IID_IPersistStreamInit:IID

endif


ifndef __IPersistPropertyBag_INTERFACE_DEFINED__
__IPersistPropertyBag_INTERFACE_DEFINED__ equ 1


IPersistPropertyBag	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetClassID, :ptr
STDMETHOD		InitNew
STDMETHOD		Load, :ptr, :ptr
STDMETHOD		Save, :ptr, :BOOL, :BOOL
IPersistPropertyBag	ENDS
LPPERSISTPROPERTYBAG	typedef ptr IPersistPropertyBag
externdef		IID_IPersistPropertyBag:IID

endif

ifndef __ISimpleFrameSite_INTERFACE_DEFINED__
__ISimpleFrameSite_INTERFACE_DEFINED__ equ 1


ISimpleFrameSite	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		PreMessageFilter, :HWND, :DWORD, :WPARAM, :LPARAM, :ptr, :ptr
STDMETHOD		PostMessageFilter, :HWND, :DWORD, :WPARAM, :LPARAM, :ptr, :DWORD
ISimpleFrameSite	ENDS
LPSIMPLEFRAMESITE	typedef ptr ISimpleFrameSite
externdef		IID_ISimpleFrameSite:IID

endif

ifndef __IFont_INTERFACE_DEFINED__
__IFont_INTERFACE_DEFINED__ equ 1


if (defined(_WIN32) OR defined (_WIN64)) AND NOT defined(OLE2ANSI)
TEXTMETRICOLE		typedef TEXTMETRICW
else
TEXTMETRICOLE		typedef TEXTMETRIC
endif
LPTEXTMETRICOLE		typedef ptr TEXTMETRICOLE

IFont			STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		get_Name, :ptr
STDMETHOD		put_Name, :BSTR
STDMETHOD		get_Size, :ptr
STDMETHOD		put_Size, :CY
STDMETHOD		get_Bold, :ptr
STDMETHOD		put_Bold, :BOOL
STDMETHOD		get_Italic, :ptr
STDMETHOD		put_Italic, :BOOL
STDMETHOD		get_Underline, :ptr
STDMETHOD		put_Underline, :BOOL
STDMETHOD		get_Strikethrough, :ptr
STDMETHOD		put_Strikethrough, :BOOL
STDMETHOD		get_Weight, :ptr
STDMETHOD		put_Weight, :SWORD
STDMETHOD		get_Charset, :ptr
STDMETHOD		put_Charset, :SWORD
STDMETHOD		get_hFont, :ptr
STDMETHOD		Clone, :ptr
STDMETHOD		IsEqual, :ptr
STDMETHOD		SetRatio, :SDWORD, :SDWORD
STDMETHOD		QueryTextMetrics, :ptr
STDMETHOD		AddRefHfont, :HFONT
STDMETHOD		ReleaseHfont, :HFONT
STDMETHOD		SetHdc, :HDC
IFont			ENDS
LPFONT			typedef ptr IFont
LPIFont			typedef ptr IFont
externdef		IID_IFont:IID

endif

ifndef __IPicture_INTERFACE_DEFINED__
__IPicture_INTERFACE_DEFINED__ equ 1


PICTUREATTRIBUTES	typedef SDWORD
PICTURE_SCALABLE	equ 0x1
PICTURE_TRANSPARENT	equ 0x2

OLE_HANDLE		typedef ptr GUID ; DECLSPEC_UUID("66504313-BE0F-101A-8BBB-00AA00300CAB")
OLE_XPOS_HIMETRIC	typedef ptr GUID ; DECLSPEC_UUID("66504306-BE0F-101A-8BBB-00AA00300CAB")
OLE_YPOS_HIMETRIC	typedef ptr GUID ; DECLSPEC_UUID("66504307-BE0F-101A-8BBB-00AA00300CAB")
OLE_XSIZE_HIMETRIC	typedef ptr GUID ; DECLSPEC_UUID("66504308-BE0F-101A-8BBB-00AA00300CAB")
OLE_YSIZE_HIMETRIC	typedef ptr GUID ; DECLSPEC_UUID("66504309-BE0F-101A-8BBB-00AA00300CAB")

DEFINE_IIDX(IPicture, "7BF80980-BF32-101A-8BBB-00AA00300CAB")

IPicture		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		get_Handle, :ptr
STDMETHOD		get_hPal, :ptr
STDMETHOD		get_Type, :ptr
STDMETHOD		get_Width, :ptr
STDMETHOD		get_Height, :ptr
STDMETHOD		Render, :HDC, :SDWORD, :SDWORD, :SDWORD, :SDWORD, :OLE_XPOS_HIMETRIC, :OLE_YPOS_HIMETRIC, :OLE_XSIZE_HIMETRIC, :OLE_YSIZE_HIMETRIC, :LPCRECT
STDMETHOD		set_hPal, :OLE_HANDLE
STDMETHOD		get_CurDC, :ptr
STDMETHOD		SelectPicture, :HDC, :ptr, :ptr
STDMETHOD		get_KeepOriginalFormat, :ptr
STDMETHOD		put_KeepOriginalFormat, :BOOL
STDMETHOD		PictureChanged,
STDMETHOD		SaveAsFile, :LPSTREAM, :BOOL, :ptr
STDMETHOD		get_Attributes, :ptr
IPicture		ENDS
LPPICTURE		typedef ptr IPicture
externdef		IID_IPicture:IID

endif

ifndef __IPicture2_INTERFACE_DEFINED__
__IPicture2_INTERFACE_DEFINED__ equ 1


HHANDLE			typedef UINT_PTR

IPicture2		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		get_Handle, :ptr
STDMETHOD		get_hPal, :ptr
STDMETHOD		get_Type, :ptr
STDMETHOD		get_Width, :ptr
STDMETHOD		get_Height, :ptr
STDMETHOD		Render, :HDC, :LONG, :LONG, :LONG, :LONG, :OLE_XPOS_HIMETRIC, :OLE_YPOS_HIMETRIC, :OLE_XSIZE_HIMETRIC, :OLE_YSIZE_HIMETRIC, :LPCRECT
STDMETHOD		set_hPal, :HHANDLE
STDMETHOD		get_CurDC, :ptr
STDMETHOD		SelectPicture, :HDC, :ptr, :ptr
STDMETHOD		get_KeepOriginalFormat, :ptr
STDMETHOD		put_KeepOriginalFormat, :BOOL
STDMETHOD		PictureChanged
STDMETHOD		SaveAsFile, :LPSTREAM, :BOOL, :ptr
STDMETHOD		get_Attributes, :ptr
IPicture2		ENDS
LPPICTURE2		typedef ptr IPicture2
externdef		IID_IPicture2:IID

endif


ifndef __IFontEventsDisp_INTERFACE_DEFINED__
__IFontEventsDisp_INTERFACE_DEFINED__ equ 1


IFontEventsDisp		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetTypeInfoCount, :ptr
STDMETHOD		GetTypeInfo, :DWORD, :LCID, :ptr
STDMETHOD		GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
STDMETHOD		_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
IFontEventsDisp		ENDS
LPFONTEVENTS		typedef ptr IFontEventsDisp
externdef		IID_IFontEventsDisp:IID

endif

ifndef __IFontDisp_INTERFACE_DEFINED__
__IFontDisp_INTERFACE_DEFINED__ equ 1


IFontDisp		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetTypeInfoCount, :ptr
STDMETHOD		GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD		GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
STDMETHOD		_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
IFontDisp		ENDS
LPFONTDISP		typedef ptr IFontDisp
externdef		IID_IFontDisp:IID

endif

ifndef __IPictureDisp_INTERFACE_DEFINED__
__IPictureDisp_INTERFACE_DEFINED__ equ 1


IPictureDisp		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetTypeInfoCount, :ptr
STDMETHOD		GetTypeInfo, :UINT, :LCID, :ptr
STDMETHOD		GetIDsOfNames, :REFIID, :ptr, :DWORD, :LCID, :ptr
STDMETHOD		_Invoke, :DISPID, :REFIID, :LCID, :WORD, :ptr, :ptr, :ptr, :ptr
IPictureDisp		ENDS
LPPICTUREDISP		typedef ptr IPictureDisp
externdef		IID_IPictureDisp:IID

endif

ifndef __IOleInPlaceObjectWindowless_INTERFACE_DEFINED__
__IOleInPlaceObjectWindowless_INTERFACE_DEFINED__ equ 1


IOleInPlaceObjectWindowless STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetWindow, :ptr
STDMETHOD		ContextSensitiveHelp, :BOOL
STDMETHOD		InPlaceDeactivate
STDMETHOD		UIDeactivate
STDMETHOD		SetObjectRects, :LPCRECT, :LPCRECT
STDMETHOD		ReactivateAndUndo,
STDMETHOD		OnWindowMessage, :DWORD, :WPARAM, :LPARAM, :ptr
STDMETHOD		GetDropTarget, :ptr
IOleInPlaceObjectWindowless ENDS
LPOLEINPLACEOBJECTWINDOWLESS typedef ptr IOleInPlaceObjectWindowless
externdef		IID_IOleInPlaceObjectWindowless:IID

endif


ifndef __IOleInPlaceSiteEx_INTERFACE_DEFINED__
__IOleInPlaceSiteEx_INTERFACE_DEFINED__ equ 1


ACTIVATEFLAGS		typedef SDWORD
ACTIVATE_WINDOWLESS	equ 1

IOleInPlaceSiteEx	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetWindow, :ptr
STDMETHOD		ContextSensitiveHelp, :BOOL
STDMETHOD		CanInPlaceActivate
STDMETHOD		OnInPlaceActivate
STDMETHOD		OnUIActivate
STDMETHOD		GetWindowContext, :ptr, :ptr, :LPRECT, :LPRECT, :LPOLEINPLACEFRAMEINFO
STDMETHOD		Scroll, :tagSIZE
STDMETHOD		OnUIDeactivate, :BOOL
STDMETHOD		OnInPlaceDeactivate
STDMETHOD		DiscardUndoState
STDMETHOD		DeactivateAndUndo
STDMETHOD		OnPosRectChange, :LPCRECT
STDMETHOD		OnInPlaceActivateEx, :ptr, :DWORD
STDMETHOD		OnInPlaceDeactivateEx, :BOOL
STDMETHOD		RequestUIActivate
IOleInPlaceSiteEx	ENDS
LPOLEINPLACESITEEX	typedef ptr IOleInPlaceSiteEx
externdef		IID_IOleInPlaceSiteEx:IID

endif


ifndef __IOleInPlaceSiteWindowless_INTERFACE_DEFINED__
__IOleInPlaceSiteWindowless_INTERFACE_DEFINED__ equ 1


OLEDCFLAGS		typedef SDWORD
OLEDC_NODRAW		equ 0x1
OLEDC_PAINTBKGND	equ 0x2
OLEDC_OFFSCREEN		equ 0x4

IOleInPlaceSiteWindowless STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetWindow, :ptr
STDMETHOD		ContextSensitiveHelp, :BOOL
STDMETHOD		CanInPlaceActivate
STDMETHOD		OnInPlaceActivate
STDMETHOD		OnUIActivate
STDMETHOD		GetWindowContext, :ptr, :ptr, :LPRECT, :LPRECT, :LPOLEINPLACEFRAMEINFO
STDMETHOD		Scroll, :tagSIZE
STDMETHOD		OnUIDeactivate, :BOOL
STDMETHOD		OnInPlaceDeactivate
STDMETHOD		DiscardUndoState
STDMETHOD		DeactivateAndUndo
STDMETHOD		OnPosRectChange, :LPCRECT
STDMETHOD		OnInPlaceActivateEx, :ptr, :DWORD
STDMETHOD		OnInPlaceDeactivateEx, :BOOL
STDMETHOD		RequestUIActivate
STDMETHOD		CanWindowlessActivate
STDMETHOD		GetCapture_
STDMETHOD		SetCapture_, :BOOL
STDMETHOD		GetFocus_
STDMETHOD		SetFocus_, :BOOL
STDMETHOD		GetDC_, :LPCRECT, :DWORD, :ptr
STDMETHOD		ReleaseDC_, :HDC
STDMETHOD		InvalidateRect, :LPCRECT, :BOOL
STDMETHOD		InvalidateRgn, :HRGN, :BOOL
STDMETHOD		ScrollRect, :DWORD, :DWORD, :LPCRECT, :LPCRECT
STDMETHOD		AdjustRect, :LPRECT
STDMETHOD		OnDefWindowMessage, :DWORD, :WPARAM, :LPARAM, :ptr
IOleInPlaceSiteWindowless ENDS
LPOLEINPLACESITEWINDOWLESS typedef ptr IOleInPlaceSiteWindowless
externdef		IID_IOleInPlaceSiteWindowless:IID

endif

ifndef	__IViewObjectEx_INTERFACE_DEFINED__
__IViewObjectEx_INTERFACE_DEFINED__ equ 1


VIEWSTATUS		typedef SDWORD
VIEWSTATUS_OPAQUE		equ 1
VIEWSTATUS_SOLIDBKGND		equ 2
VIEWSTATUS_DVASPECTOPAQUE	equ 4
VIEWSTATUS_DVASPECTTRANSPARENT	equ 8
VIEWSTATUS_SURFACE		equ 16
VIEWSTATUS_3DSURFACE		equ 32

HITRESULT		typedef SDWORD
HITRESULT_OUTSIDE	equ 0
HITRESULT_TRANSPARENT	equ 1
HITRESULT_CLOSE		equ 2
HITRESULT_HIT		equ 3

DVASPECT2		typedef SDWORD
DVASPECT_OPAQUE		equ 16
DVASPECT_TRANSPARENT	equ 32

DVEXTENTINFO		STRUC
cb			ULONG ?
dwExtentMode		dd ?
sizelProposed		SIZEL <>
DVEXTENTINFO		ENDS

DVEXTENTMODE		typedef SDWORD
DVEXTENT_CONTENT	equ 0
DVEXTENT_INTEGRAL	equ ( DVEXTENT_CONTENT + 1 )

DVASPECTINFOFLAG	typedef SDWORD
DVASPECTINFOFLAG_CANOPTIMIZE equ 1

DVASPECTINFO		STRUC
cb			ULONG ?
dwFlags			dd ?
DVASPECTINFO		ENDS

CALLBACK(pDraw_pfnContinue, :DWORD)

IViewObjectEx		STRUC
STDMETHOD		Draw, :DWORD, :SDWORD, :ptr, :ptr, :HDC, :HDC, :LPCRECTL, :LPCRECTL, :pDraw_pfnContinue, :DWORD
STDMETHOD		GetColorSet, :DWORD, :SDWORD, :ptr, :ptr, :HDC, :ptr
STDMETHOD		Freeze, :DWORD, :SDWORD, :ptr, :ptr
STDMETHOD		Unfreeze, :DWORD
STDMETHOD		SetAdvise, :DWORD, :DWORD, :ptr
STDMETHOD		GetAdvise, :ptr, :ptr, :ptr
STDMETHOD		GetExtent, :DWORD, :SDWORD, :ptr, :LPSIZEL
STDMETHOD		GetRect, :DWORD, :LPRECTL
STDMETHOD		GetViewStatus, :ptr
STDMETHOD		QueryHitPoint, :DWORD, :LPCRECT, :POINT, :SDWORD, :ptr
STDMETHOD		QueryHitRect, :DWORD, :LPCRECT, :LPCRECT, :SDWORD, :ptr
STDMETHOD		GetNaturalExtent, :DWORD, :SDWORD, :ptr, :HDC, :ptr, :LPSIZEL
IViewObjectEx		ends

endif ; __IViewObjectEx_INTERFACE_DEFINED__

ifndef __IOleUndoUnit_INTERFACE_DEFINED__
__IOleUndoUnit_INTERFACE_DEFINED__ equ 1


IOleUndoUnit		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		Do, :ptr
STDMETHOD		GetDescription, :ptr
STDMETHOD		GetUnitType, :ptr, :ptr
STDMETHOD		OnNextAdd
IOleUndoUnit		ENDS
LPOLEUNDOUNIT		typedef ptr IOleUndoUnit
externdef		IID_IOleUndoUnit:IID

endif

ifndef __IOleParentUndoUnit_INTERFACE_DEFINED__
__IOleParentUndoUnit_INTERFACE_DEFINED__ equ 1


IOleParentUndoUnit	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		Do, :ptr
STDMETHOD		GetDescription, :ptr
STDMETHOD		GetUnitType, :ptr, :ptr
STDMETHOD		OnNextAdd
STDMETHOD		Open, :ptr
STDMETHOD		Close, :ptr, :BOOL
STDMETHOD		_Add, :ptr
STDMETHOD		FindUnit, :ptr
STDMETHOD		GetParentState, :ptr
IOleParentUndoUnit	ENDS

endif


ifndef __IEnumOleUndoUnits_INTERFACE_DEFINED__
__IEnumOleUndoUnits_INTERFACE_DEFINED__ equ 1


IEnumOleUndoUnits	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		Next, :ULONG, :ptr, :ptr
STDMETHOD		Skip, :ULONG
STDMETHOD		Reset
STDMETHOD		Clone, :ptr
IEnumOleUndoUnits	ENDS
LPENUMOLEUNDOUNITS	typedef ptr IEnumOleUndoUnits
externdef		IID_IEnumOleUndoUnits:IID

;HRESULT
IEnumOleUndoUnits_RemoteNext_Proxy proto WINAPI \
		 _This: ptr IEnumOleUndoUnits,
		  cElt: ULONG,
		 rgElt: ptr IOleUndoUnit,
	  pcEltFetched: ptr ULONG

;void
IEnumOleUndoUnits_RemoteNext_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IOleUndoManager_INTERFACE_DEFINED__
__IOleUndoManager_INTERFACE_DEFINED__ equ 1


SID_SOleUndoManager	equ IID_IOleUndoManager

IOleUndoManager		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		Open, :ptr
STDMETHOD		Close, :ptr, :BOOL
STDMETHOD		_Add, :ptr
STDMETHOD		GetOpenParentState, :ptr
STDMETHOD		DiscardFrom, :ptr
STDMETHOD		UndoTo, :ptr
STDMETHOD		RedoTo, :ptr
STDMETHOD		EnumUndoable, :ptr
STDMETHOD		EnumRedoable, :ptr
STDMETHOD		GetLastUndoDescription, :ptr
STDMETHOD		GetLastRedoDescription, :ptr
STDMETHOD		Enable, :BOOL
IOleUndoManager		ENDS
LPOLEUNDOMANAGER	typedef ptr IOleUndoManager
LPIOleUndoManager	typedef ptr IOleUndoManager
externdef		IID_IOleUndoManager:IID

endif

ifndef __IPointerInactive_INTERFACE_DEFINED__
__IPointerInactive_INTERFACE_DEFINED__ equ 1


POINTERINACTIVE		typedef dword
POINTERINACTIVE_ACTIVATEONENTRY	  equ 1
POINTERINACTIVE_DEACTIVATEONLEAVE equ 2
POINTERINACTIVE_ACTIVATEONDRAG	  equ 4

IPointerInactive	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetActivationPolicy, :ptr
STDMETHOD		OnInactiveMouseMove, :LPCRECT, :LONG, :LONG, :DWORD
STDMETHOD		OnInactiveSetCursor, :LPCRECT, :LONG, :LONG, :DWORD, :BOOL
IPointerInactive	ENDS
LPPOINTERINACTIVE	typedef ptr IPointerInactive
externdef		IID_IPointerInactive:IID

endif

ifndef __IObjectWithSite_INTERFACE_DEFINED__
__IObjectWithSite_INTERFACE_DEFINED__ equ 1


IObjectWithSite		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		SetSite, :ptr
STDMETHOD		GetSite, :REFIID, :ptr
IObjectWithSite		ENDS
LPOBJECTWITHSITE	typedef ptr IObjectWithSite
externdef		IID_IObjectWithSite:IID

endif


ifndef __IPerPropertyBrowsing_INTERFACE_DEFINED__
__IPerPropertyBrowsing_INTERFACE_DEFINED__ equ 1


CALPOLESTR		STRUC
cElems			ULONG ?
pElems			LPOLESTR ?
CALPOLESTR		ENDS
LPCALPOLESTR		typedef ptr CALPOLESTR

CADWORD			STRUC
cElems			ULONG ?
pElems			LPDWORD ?
CADWORD			ENDS
LPCADWORD		typedef ptr CADWORD

IPerPropertyBrowsing	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetDisplayString, :DISPID, :ptr
STDMETHOD		MapPropertyToPage, :DISPID, :ptr
STDMETHOD		GetPredefinedStrings, :DISPID, :ptr, :ptr
STDMETHOD		GetPredefinedValue, :DISPID, :DWORD, :ptr
IPerPropertyBrowsing	ENDS
LPPERPROPERTYBROWSING	typedef ptr IPerPropertyBrowsing
externdef		IID_IPerPropertyBrowsing:IID

endif


ifndef __IPropertyBag2_INTERFACE_DEFINED__
__IPropertyBag2_INTERFACE_DEFINED__ equ 1


PROPBAG2_TYPE		typedef SDWORD

PROPBAG2		STRUC
dwType			dd ?
vt			VARTYPE ?
cfType			CLIPFORMAT ?
dwHint			dd ?
pstrName		LPOLESTR ?
clsid			CLSID <>
PROPBAG2		ENDS

IPropertyBag2		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		Read, :DWORD,:ptr, :ptr, :ptr, :ptr
STDMETHOD		Write, :DWORD, :ptr, :ptr
STDMETHOD		CountProperties, :ptr
STDMETHOD		GetPropertyInfo, :DWORD, :DWORD, :ptr, :ptr
STDMETHOD		LoadObject, :LPCOLESTR, :DWORD, :ptr, :ptr
IPropertyBag2		ENDS
LPPROPERTYBAG2		typedef ptr IPropertyBag2
externdef		IID_IPropertyBag2:IID

endif


ifndef __IPersistPropertyBag2_INTERFACE_DEFINED__
__IPersistPropertyBag2_INTERFACE_DEFINED__ equ 1


IPersistPropertyBag2	STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		GetClassID, :ptr
STDMETHOD		InitNew
STDMETHOD		Load, :ptr, :ptr
STDMETHOD		Save, :ptr, :BOOL, :BOOL
STDMETHOD		IsDirty
IPersistPropertyBag2	ENDS
LPPERSISTPROPERTYBAG2	typedef ptr IPersistPropertyBag2
externdef		IID_IPersistPropertyBag2:IID

endif


ifndef __IAdviseSinkEx_INTERFACE_DEFINED__
__IAdviseSinkEx_INTERFACE_DEFINED__ equ 1


IAdviseSinkEx		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		OnDataChange, :ptr, :ptr
STDMETHOD		OnViewChange, :DWORD, :SDWORD
STDMETHOD		OnRename, :ptr
STDMETHOD		OnSave
STDMETHOD		OnClose
STDMETHOD		OnViewStatusChange, :DWORD
IAdviseSinkEx		ENDS
LPADVISESINKEX		typedef ptr IAdviseSinkEx
externdef		IID_IAdviseSinkEx:IID

;HRESULT
IAdviseSinkEx_RemoteOnViewStatusChange_Proxy proto WINAPI \
		 _This: ptr IAdviseSinkEx,
	  dwViewStatus: DWORD

;void
IAdviseSinkEx_RemoteOnViewStatusChange_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif

ifndef __IQuickActivate_INTERFACE_DEFINED__
__IQuickActivate_INTERFACE_DEFINED__ equ 1


tagQACONTAINERFLAGS	typedef SDWORD
QACONTAINER_SHOWHATCHING equ 0x1
QACONTAINER_SHOWGRABHANDLES equ 0x2
QACONTAINER_USERMODE	equ 0x4
QACONTAINER_DISPLAYASDEFAULT equ 0x8
QACONTAINER_UIDEAD	equ 0x10
QACONTAINER_AUTOCLIP	equ 0x20
QACONTAINER_MESSAGEREFLECT equ 0x40
QACONTAINER_SUPPORTSMNEMONICS equ 0x80

DECLSPEC_UUID("66504301-BE0F-101A-8BBB-00AA00300CAB")

OLE_COLOR		typedef DWORD

QACONTAINER		STRUC
cbSize			ULONG ?
pClientSite		LPOLECLIENTSITE ?
pAdviseSink		LPADVISESINKEX ?
pPropertyNotifySink	LPPROPERTYNOTIFYSINK ?
pUnkEventSink		LPIUnknown ?
dwAmbientFlags		dd ?
colorFore		OLE_COLOR ?
colorBack		OLE_COLOR ?
pFont			LPIFont ?
pUndoMgr		LPIOleUndoManager ?
dwAppearance		dd ?
lcid			LONG ?
hpal			HPALETTE ?
pBindHost		LPIBindHost ?
pOleControlSite		LPIOleControlSite ?
pServiceProvider	LPIServiceProvider ?
QACONTAINER		ENDS

QACONTROL		STRUC
cbSize			ULONG ?
dwMiscStatus		dd ?
dwViewStatus		dd ?
dwEventCookie		dd ?
dwPropNotifyCookie	dd ?
dwPointerActivationPolicy dd ?
QACONTROL		ENDS

IQuickActivate		STRUC
STDMETHOD		QueryInterface, :REFIID, :ptr
STDMETHOD		AddRef
STDMETHOD		Release
STDMETHOD		QuickActivate, :ptr, :ptr
STDMETHOD		SetContentExtent, :LPSIZEL
STDMETHOD		GetContentExtent, :LPSIZEL
IQuickActivate		ENDS
LPQUICKACTIVATE		typedef ptr IQuickActivate
externdef		IID_IQuickActivate:IID

;HRESULT
IQuickActivate_RemoteQuickActivate_Proxy proto WINAPI \
		 _This: ptr IQuickActivate,
	  pQaContainer: ptr QACONTAINER,
	    pQaControl: ptr QACONTROL

;void
IQuickActivate_RemoteQuickActivate_Stub proto WINAPI \
		 _This: ptr IRpcStubBuffer,
    _pRpcChannelBuffer: ptr IRpcChannelBuffer,
	  _pRpcMessage: PRPC_MESSAGE,
	 _pdwStubPhase: ptr DWORD

endif


;unsigned
BSTR_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr BSTR

;unsigned
BSTR_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr BSTR

;unsigned
BSTR_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr BSTR


;unsigned
CLIPFORMAT_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr CLIPFORMAT

;unsigned
CLIPFORMAT_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT

;unsigned
CLIPFORMAT_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT

;void
CLIPFORMAT_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr CLIPFORMAT


;unsigned
HACCEL_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HACCEL

;unsigned
HACCEL_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HACCEL

;unsigned
HACCEL_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HACCEL

;void
HACCEL_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr HACCEL


;unsigned
HDC_UserSize proto WINAPI \
		      : LPDWORD,
		      : dword,
		      : ptr HDC

;unsigned
HDC_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HDC

;unsigned
HDC_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HDC

;void
HDC_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr HDC


;unsigned
HFONT_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HFONT

;unsigned
HFONT_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HFONT

;unsigned
HFONT_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HFONT

;void
HFONT_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr HFONT


;unsigned
HPALETTE_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HPALETTE

;unsigned
HPALETTE_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HPALETTE

;unsigned
HPALETTE_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HPALETTE

;void
HPALETTE_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr HPALETTE


;unsigned
HRGN_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HRGN

;unsigned
HRGN_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HRGN

;unsigned
HRGN_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HRGN

;void
HRGN_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr HRGN


;unsigned
HWND_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HWND

;unsigned
HWND_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HWND

;unsigned
HWND_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HWND

;void
HWND_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr HWND


;unsigned
VARIANT_UserSize proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr VARIANT

;unsigned
VARIANT_UserMarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr VARIANT

;unsigned
VARIANT_UserUnmarshal proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr VARIANT

;void
VARIANT_UserFree proto WINAPI \
		      : LPDWORD,
		      : ptr VARIANT


;unsigned
BSTR_UserSize64 proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr BSTR

;unsigned
BSTR_UserMarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr BSTR

;unsigned
BSTR_UserUnmarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr BSTR

;void
BSTR_UserFree64 proto WINAPI \
		      : LPDWORD,
		      : ptr BSTR


;unsigned
CLIPFORMAT_UserSize64 proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr CLIPFORMAT

;unsigned
CLIPFORMAT_UserMarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT

;unsigned
CLIPFORMAT_UserUnmarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr CLIPFORMAT

;void
CLIPFORMAT_UserFree64 proto WINAPI \
		      : LPDWORD,
		      : ptr CLIPFORMAT


;unsigned
HACCEL_UserSize64 proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HACCEL

;unsigned
HACCEL_UserMarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HACCEL

;unsigned
HACCEL_UserUnmarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HACCEL

;void
HACCEL_UserFree64 proto WINAPI \
		      : LPDWORD,
		      : ptr HACCEL


;unsigned
HDC_UserSize64 proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HDC

;unsigned
HDC_UserMarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HDC

;unsigned
HDC_UserUnmarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HDC

;void
HDC_UserFree64 proto WINAPI \
		      : LPDWORD,
		      : ptr HDC


;unsigned
HFONT_UserSize64 proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HFONT

;unsigned
HFONT_UserMarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HFONT

;unsigned
HFONT_UserUnmarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HFONT

;void
HFONT_UserFree64 proto WINAPI \
		      : LPDWORD,
		      : ptr HFONT


;unsigned
HPALETTE_UserSize64 proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HPALETTE

;unsigned
HPALETTE_UserMarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HPALETTE

;unsigned
HPALETTE_UserUnmarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HPALETTE

;void
HPALETTE_UserFree64 proto WINAPI \
		      : LPDWORD,
		      : ptr HPALETTE

;unsigned
HRGN_UserSize64 proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HRGN

;unsigned
HRGN_UserMarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HRGN

;unsigned
HRGN_UserUnmarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HRGN
;void
HRGN_UserFree64 proto WINAPI \
		      : LPDWORD,
		      : ptr HRGN

;unsigned
HWND_UserSize64 proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr HWND

;unsigned
HWND_UserMarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HWND

;unsigned
HWND_UserUnmarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr HWND

;void
HWND_UserFree64 proto WINAPI \
		      : LPDWORD,
		      : ptr HWND


;unsigned
VARIANT_UserSize64 proto WINAPI \
		      : LPDWORD,
		      : DWORD,
		      : ptr VARIANT

;unsigned
VARIANT_UserMarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr VARIANT

;unsigned
VARIANT_UserUnmarshal64 proto WINAPI \
		      : LPDWORD,
		      : LPSTR,
		      : ptr VARIANT

;void
VARIANT_UserFree64 proto WINAPI \
		      : LPDWORD,
		      : ptr VARIANT

;HRESULT
IEnumConnections_Next_Proxy proto WINAPI \
		 _This: ptr IEnumConnections,
	  cConnections: ULONG,
		  rgcd: LPCONNECTDATA,
	     pcFetched: ptr ULONG

;HRESULT
IEnumConnections_Next_Stub proto WINAPI \
		 _This: ptr IEnumConnections,
	  cConnections: ULONG,
		  rgcd: LPCONNECTDATA,
	     pcFetched: ptr ULONG

;HRESULT
IEnumConnectionPoints_Next_Proxy proto WINAPI \
		 _This: ptr IEnumConnectionPoints,
	  cConnections: ULONG,
		  ppCP: ptr LPCONNECTIONPOINT,
	     pcFetched: ptr ULONG

;HRESULT
IEnumConnectionPoints_Next_Stub proto WINAPI \
		 _This: ptr IEnumConnectionPoints,
	  cConnections: ULONG,
		  ppCP: ptr LPCONNECTIONPOINT,
	     pcFetched: ptr ULONG

;HRESULT
IClassFactory2_CreateInstanceLic_Proxy proto WINAPI \
		 _This: ptr IClassFactory2,
	     pUnkOuter: ptr IUnknown,
	  pUnkReserved: ptr IUnknown,
		  riid: REFIID,
	       bstrKey: BSTR,
		ppvObj: ptr PVOID

;HRESULT
IClassFactory2_CreateInstanceLic_Stub proto WINAPI \
		 _This: ptr IClassFactory2,
		  riid: REFIID,
	       bstrKey: BSTR,
		ppvObj: ptr IUnknown

;HRESULT
IPersistMemory_Load_Proxy proto WINAPI \
		 _This: ptr IPersistMemory,
		  pMem: LPVOID,
		cbSize: ULONG

;HRESULT
IPersistMemory_Load_Stub proto WINAPI \
		 _This: ptr IPersistMemory,
		  pMem: ptr BYTE,
		cbSize: ULONG

;HRESULT
IPersistMemory_Save_Proxy proto WINAPI \
		 _This: ptr IPersistMemory,
		  pMem: LPVOID,
	   fClearDirty: BOOL,
		cbSize: ULONG

;HRESULT
IPersistMemory_Save_Stub proto WINAPI \
		 _This: ptr IPersistMemory,
		  pMem: ptr BYTE,
	   fClearDirty: BOOL,
		cbSize: ULONG
;HRESULT
IEnumOleUndoUnits_Next_Proxy proto WINAPI \
		 _This: ptr IEnumOleUndoUnits,
		  cElt: ULONG,
		 rgElt: ptr IOleUndoUnit,
	  pcEltFetched: ptr ULONG

;HRESULT
IEnumOleUndoUnits_Next_Stub proto WINAPI \
		 _This: ptr IEnumOleUndoUnits,
		  cElt: ULONG,
		 rgElt: ptr IOleUndoUnit,
	  pcEltFetched: ptr ULONG

;void
IAdviseSinkEx_OnViewStatusChange_Proxy proto WINAPI \
		 _This: ptr IAdviseSinkEx,
	  dwViewStatus: DWORD

;HRESULT
IAdviseSinkEx_OnViewStatusChange_Stub proto WINAPI \
		 _This: ptr IAdviseSinkEx,
	  dwViewStatus: DWORD

;HRESULT
IQuickActivate_QuickActivate_Proxy proto WINAPI \
		 _This: ptr IQuickActivate,
	  pQaContainer: ptr QACONTAINER,
	    pQaControl: ptr QACONTROL

;HRESULT
IQuickActivate_QuickActivate_Stub proto WINAPI \
		 _This: ptr IQuickActivate,
	  pQaContainer: ptr QACONTAINER,
	    pQaControl: ptr QACONTROL


.list
endif ; __ocidl_h__
