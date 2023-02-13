ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif
ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
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
define __ocidl_h__

include oleidl.inc
include oaidl.inc
include servprov.inc
include urlmon.inc

ifndef __IOleControlTypes_INTERFACE_DEFINED__
define __IOleControlTypes_INTERFACE_DEFINED__

.enum UASFLAGS {
	UAS_NORMAL,
	UAS_BLOCKED,
	UAS_NOPARENTENABLE,
	UAS_MASK
	}

.enum READYSTATE {
	READYSTATE_UNINITIALIZED,
	READYSTATE_LOADING,
	READYSTATE_LOADED,
	READYSTATE_INTERACTIVE,
	READYSTATE_COMPLETE
	}

endif

ifndef __IEnumConnections_INTERFACE_DEFINED__
define __IEnumConnections_INTERFACE_DEFINED__

PENUMCONNECTIONS	typedef ptr IEnumConnections
LPENUMCONNECTIONS	typedef ptr IEnumConnections
CONNECTDATA		STRUC
pUnk			LPUNKNOWN ?
dwCookie		dd ?
CONNECTDATA		ENDS
PCONNECTDATA		typedef ptr CONNECTDATA
LPCONNECTDATA		typedef ptr CONNECTDATA

DEFINE_IIDX(IEnumConnections, "B196B287-BAB4-101A-B69C-00AA00341D07")

.comdef IEnumConnections : public IUnknown

    Next		proc :DWORD, :LPCONNECTDATA, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr
   .ends

endif

ifndef __IConnectionPoint_INTERFACE_DEFINED__
define __IConnectionPoint_INTERFACE_DEFINED__

DEFINE_IIDX(IConnectionPoint, "B196B286-BAB4-101A-B69C-00AA00341D07")

.comdef IConnectionPoint : public IUnknown

    GetConnectionInterface proc :ptr
    GetConnectionPointContainer proc :ptr
    Advise		proc :ptr, :ptr
    Unadvise		proc :DWORD
    EnumConnections	proc :ptr
   .ends

PCONNECTIONPOINT	typedef ptr IConnectionPoint
LPCONNECTIONPOINT	typedef ptr IConnectionPoint

endif

ifndef __IEnumConnectionPoints_INTERFACE_DEFINED__
define __IEnumConnectionPoints_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumConnectionPoints, "B196B285-BAB4-101A-B69C-00AA00341D07")

.comdef IEnumConnectionPoints : public IUnknown

    Next		proc :DWORD, :ptr, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr
   .ends

PENUMCONNECTIONPOINTS	typedef ptr IEnumConnectionPoints
LPENUMCONNECTIONPOINTS	typedef ptr IEnumConnectionPoints

endif

ifndef __IConnectionPointContainer_INTERFACE_DEFINED__
define __IConnectionPointContainer_INTERFACE_DEFINED__

DEFINE_IIDX(IConnectionPointContainer, "B196B284-BAB4-101A-B69C-00AA00341D07")

.comdef IConnectionPointContainer : public IUnknown

    EnumConnectionPoints proc :ptr
    FindConnectionPoint proc :REFIID, :ptr
   .ends

PCONNECTIONPOINTCONTAINER typedef ptr IConnectionPointContainer
LPCONNECTIONPOINTCONTAINER typedef ptr IConnectionPointContainer

endif

ifndef __IClassFactory2_INTERFACE_DEFINED__
define __IClassFactory2_INTERFACE_DEFINED__


LICINFO			STRUC
cbLicInfo		LONG ?
fRuntimeKeyAvail	BOOL ?
fLicVerified		BOOL ?
LICINFO			ENDS
LPLICINFO		typedef ptr LICINFO

DEFINE_IIDX(IClassFactory2, "B196B28F-BAB4-101A-B69C-00AA00341D07")

.comdef IClassFactory2 : public IClassFactory

    GetLicInfo		proc :ptr
    RequestLicKey	proc :DWORD, :ptr
    CreateInstanceLic	proc :ptr, :ptr, :REFIID, :BSTR, :ptr
   .ends

LPCLASSFACTORY2		typedef ptr IClassFactory2

endif

ifndef __IProvideClassInfo_INTERFACE_DEFINED__
define __IProvideClassInfo_INTERFACE_DEFINED__

DEFINE_IIDX(IProvideClassInfo, "B196B283-BAB4-101A-B69C-00AA00341D07")

.comdef IProvideClassInfo : public IUnknown

    GetClassInfo	proc :ptr
   .ends

LPPROVIDECLASSINFO	typedef ptr IProvideClassInfo

endif


ifndef __IProvideClassInfo2_INTERFACE_DEFINED__
define __IProvideClassInfo2_INTERFACE_DEFINED__

GUIDKIND		typedef sdword
GUIDKIND_DEFAULT_SOURCE_DISP_IID equ 1

DEFINE_IIDX(IProvideClassInfo2, "A6BC3AC0-DBAA-11CE-9DE3-00AA004BB851")

.comdef IProvideClassInfo2 : public IProvideClassInfo

    GetGUID		proc :DWORD, :ptr
   .ends

LPPROVIDECLASSINFO2	typedef ptr IProvideClassInfo2

endif


ifndef __IProvideMultipleClassInfo_INTERFACE_DEFINED__
define __IProvideMultipleClassInfo_INTERFACE_DEFINED__


MULTICLASSINFO_GETTYPEINFO equ 0x00000001
MULTICLASSINFO_GETNUMRESERVEDDISPIDS equ 0x00000002
MULTICLASSINFO_GETIIDPRIMARY equ 0x00000004
MULTICLASSINFO_GETIIDSOURCE equ 0x00000008
TIFLAGS_EXTENDDISPATCHONLY equ 0x00000001

DEFINE_IIDX(IProvideMultipleClassInfo, "A7ABA9C1-8983-11cf-8F20-00805F2CD064")

.comdef IProvideMultipleClassInfo : public IProvideClassInfo2

    GetMultiTypeInfoCount proc :ptr
    GetInfoOfIndex	proc :ULONG, :DWORD, :ptr, :ptr, :ptr, :ptr, :ptr
   .ends

LPPROVIDEMULTIPLECLASSINFO typedef ptr IProvideMultipleClassInfo

endif

ifndef __IOleControl_INTERFACE_DEFINED__
define __IOleControl_INTERFACE_DEFINED__

CONTROLINFO		STRUC
cb			ULONG ?
hAccel			HACCEL ?
cAccel			USHORT ?
dwFlags			dd ?
CONTROLINFO		ENDS
LPCONTROLINFO		typedef ptr CONTROLINFO

CTRLINFO		typedef sdword
CTRLINFO_EATS_RETURN	equ 1
CTRLINFO_EATS_ESCAPE	equ 2

DEFINE_IIDX(IOleControl, "B196B288-BAB4-101A-B69C-00AA00341D07")

.comdef IOleControl : public IUnknown

    GetControlInfo	proc :ptr
    OnMnemonic		proc :ptr
    OnAmbientPropertyChange proc :DISPID
    FreezeEvents	proc :BOOL
   .ends

LPOLECONTROL		typedef ptr IOleControl

endif

ifndef __IOleControlSite_INTERFACE_DEFINED__
define __IOleControlSite_INTERFACE_DEFINED__

POINTF			STRUC
x			FLOAT ?
y			FLOAT ?
POINTF			ENDS
LPPOINTF		typedef ptr POINTF

.enum XFORMCOORDS {
	XFORMCOORDS_POSITION		= 0x1,
	XFORMCOORDS_SIZE		= 0x2,
	XFORMCOORDS_HIMETRICTOCONTAINER = 0x4,
	XFORMCOORDS_CONTAINERTOHIMETRIC = 0x8,
	XFORMCOORDS_EVENTCOMPAT		= 0x10
	}

DEFINE_IIDX(IOleControlSite, "B196B289-BAB4-101A-B69C-00AA00341D07")

.comdef IOleControlSite : public IUnknown

    OnControlInfoChanged proc
    LockInPlaceActive	proc :BOOL
    GetExtendedControl	proc :ptr
    TransformCoords	proc :ptr, :ptr, :DWORD
    TranslateAccelerator proc :ptr, :DWORD
    OnFocus		proc :BOOL
    ShowPropertyFrame	proc
   .ends

LPOLECONTROLSITE	typedef ptr IOleControlSite

endif

ifndef __IPropertyPage_INTERFACE_DEFINED__
define __IPropertyPage_INTERFACE_DEFINED__

PROPPAGEINFO		STRUC
cb			ULONG ?
pszTitle		LPOLESTR ?
size			tagSIZE <>
pszDocString		LPOLESTR ?
pszHelpFile		LPOLESTR ?
dwHelpContext		dd ?
PROPPAGEINFO		ENDS
LPPROPPAGEINFO		typedef ptr PROPPAGEINFO

DEFINE_IIDX(IPropertyPage, "B196B28D-BAB4-101A-B69C-00AA00341D07")

.comdef IPropertyPage : public IUnknown

    SetPageSite		proc :ptr
    Activate		proc :HWND, :LPCRECT, :BOOL
    Deactivate		proc
    GetPageInfo		proc :ptr
    SetObjects		proc :DWORD, :ptr
    Show		proc :DWORD
    Move		proc :LPCRECT
    IsPageDirty		proc
    Apply		proc
    Help		proc :LPCOLESTR
    TranslateAccelerator proc :ptr
   .ends

LPPROPERTYPAGE		typedef ptr IPropertyPage

endif


ifndef __IPropertyPage2_INTERFACE_DEFINED__
define __IPropertyPage2_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyPage2, "01E44665-24AC-101B-84ED-08002B2EC713")

.comdef IPropertyPage2 : public IPropertyPage

    EditProperty	proc :DISPID
   .ends

LPPROPERTYPAGE2		typedef ptr IPropertyPage2

endif


ifndef __IPropertyPageSite_INTERFACE_DEFINED__
define __IPropertyPageSite_INTERFACE_DEFINED__

.enum PROPPAGESTATUS {
	PROPPAGESTATUS_DIRTY	= 0x1,
	PROPPAGESTATUS_VALIDATE = 0x2,
	PROPPAGESTATUS_CLEAN	= 0x4
	}

DEFINE_IIDX(IPropertyPageSite, "B196B28C-BAB4-101A-B69C-00AA00341D07")

.comdef IPropertyPageSite : public IUnknown

    OnStatusChange	proc :DWORD
    GetLocaleID		proc :ptr
    GetPageContainer	proc :ptr
    TranslateAccelerator proc :ptr
   .ends

LPPROPERTYPAGESITE	typedef ptr IPropertyPageSite

endif


ifndef __IPropertyNotifySink_INTERFACE_DEFINED__
define __IPropertyNotifySink_INTERFACE_DEFINED__

DEFINE_IIDX(IPropertyNotifySink, "9BFBBC02-EFF1-101A-84ED-00AA00341D07")

.comdef IPropertyNotifySink : public IUnknown

    OnChanged		proc :DISPID
    OnRequestEdit	proc :DISPID
   .ends

LPPROPERTYNOTIFYSINK	typedef ptr IPropertyNotifySink

endif


ifndef __ISpecifyPropertyPages_INTERFACE_DEFINED__
define __ISpecifyPropertyPages_INTERFACE_DEFINED__

DEFINE_IIDX(ISpecifyPropertyPages, "B196B28B-BAB4-101A-B69C-00AA00341D07")

CAUUID			STRUC
cElems			ULONG ?
pElems			LPGUID ?
CAUUID			ENDS
LPCAUUID		typedef ptr CAUUID

.comdef ISpecifyPropertyPages : public IUnknown

    GetPages		proc :ptr
   .ends

LPSPECIFYPROPERTYPAGES	typedef ptr ISpecifyPropertyPages

endif

ifndef __IPersistMemory_INTERFACE_DEFINED__
define __IPersistMemory_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistMemory, "BD1AE5E0-A6AE-11CE-BD37-504200C10000")

.comdef IPersistMemory : public IPersist

    IsDirty		proc
    Load		proc :LPVOID, :ULONG
    Save		proc :LPVOID, :BOOL, :ULONG
    GetSizeMax		proc :ptr
    InitNew		proc
   .ends

LPPERSISTMEMORY		typedef ptr IPersistMemory

endif

ifndef __IPersistStreamInit_INTERFACE_DEFINED__
define __IPersistStreamInit_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistStreamInit, "7FD52380-4E07-101B-AE2D-08002B2EC713")

.comdef IPersistStreamInit : public IPersist

    IsDirty		proc
    Load		proc :LPSTREAM
    Save		proc :LPSTREAM, :BOOL
    GetSizeMax		proc :ptr
    InitNew		proc
   .ends

LPPERSISTSTREAMINIT	typedef ptr IPersistStreamInit

endif


ifndef __IPersistPropertyBag_INTERFACE_DEFINED__
define __IPersistPropertyBag_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistPropertyBag, "37D84F60-42CB-11CE-8135-00AA004BB851")

.comdef IPersistPropertyBag : public IPersist

    InitNew		proc
    Load		proc :ptr, :ptr
    Save		proc :ptr, :BOOL, :BOOL
   .ends

LPPERSISTPROPERTYBAG	typedef ptr IPersistPropertyBag

endif

ifndef __ISimpleFrameSite_INTERFACE_DEFINED__
define __ISimpleFrameSite_INTERFACE_DEFINED__

DEFINE_IIDX(ISimpleFrameSite, "742B0E01-14E6-101B-914E-00AA00300CAB")

.comdef ISimpleFrameSite : public IUnknown

    PreMessageFilter	proc :HWND, :DWORD, :WPARAM, :LPARAM, :ptr, :ptr
    PostMessageFilter	proc :HWND, :DWORD, :WPARAM, :LPARAM, :ptr, :DWORD
   .ends

LPSIMPLEFRAMESITE	typedef ptr ISimpleFrameSite

endif

ifndef __IFont_INTERFACE_DEFINED__
define __IFont_INTERFACE_DEFINED__

if (defined(_WIN32) OR defined (_WIN64)) AND NOT defined(OLE2ANSI)
TEXTMETRICOLE		typedef TEXTMETRICW
else
TEXTMETRICOLE		typedef TEXTMETRIC
endif
LPTEXTMETRICOLE		typedef ptr TEXTMETRICOLE

DEFINE_IIDX(IFont, "BEF6E002-A874-101A-8BBA-00AA00300CAB")

.comdef IFont : public IUnknown

    get_Name		proc :ptr
    put_Name		proc :BSTR
    get_Size		proc :ptr
    put_Size		proc :CY
    get_Bold		proc :ptr
    put_Bold		proc :BOOL
    get_Italic		proc :ptr
    put_Italic		proc :BOOL
    get_Underline	proc :ptr
    put_Underline	proc :BOOL
    get_Strikethrough	proc :ptr
    put_Strikethrough	proc :BOOL
    get_Weight		proc :ptr
    put_Weight		proc :SWORD
    get_Charset		proc :ptr
    put_Charset		proc :SWORD
    get_hFont		proc :ptr
    Clone		proc :ptr
    IsEqual		proc :ptr
    SetRatio		proc :SDWORD, :SDWORD
    QueryTextMetrics	proc :ptr
    AddRefHfont		proc :HFONT
    ReleaseHfont	proc :HFONT
    SetHdc		proc :HDC
   .ends

LPFONT			typedef ptr IFont

endif

ifndef __IPicture_INTERFACE_DEFINED__
define __IPicture_INTERFACE_DEFINED__


.enum PICTUREATTRIBUTES {
	PICTURE_SCALABLE	= 0x1,
	PICTURE_TRANSPARENT	= 0x2
	}

OLE_HANDLE		typedef UINT ; DECLSPEC_UUID("66504313-BE0F-101A-8BBB-00AA00300CAB")
OLE_XPOS_HIMETRIC	typedef LONG ; DECLSPEC_UUID("66504306-BE0F-101A-8BBB-00AA00300CAB")
OLE_YPOS_HIMETRIC	typedef LONG ; DECLSPEC_UUID("66504307-BE0F-101A-8BBB-00AA00300CAB")
OLE_XSIZE_HIMETRIC	typedef LONG ; DECLSPEC_UUID("66504308-BE0F-101A-8BBB-00AA00300CAB")
OLE_YSIZE_HIMETRIC	typedef LONG ; DECLSPEC_UUID("66504309-BE0F-101A-8BBB-00AA00300CAB")

DEFINE_IIDX(IPicture, "7BF80980-BF32-101A-8BBB-00AA00300CAB")

.comdef IPicture : public IUnknown

    get_Handle		proc :ptr
    get_hPal		proc :ptr
    get_Type		proc :ptr
    get_Width		proc :ptr
    get_Height		proc :ptr
    Render		proc :HDC, :SDWORD, :SDWORD, :SDWORD, :SDWORD, :OLE_XPOS_HIMETRIC, :OLE_YPOS_HIMETRIC, :OLE_XSIZE_HIMETRIC, :OLE_YSIZE_HIMETRIC, :LPCRECT
    set_hPal		proc :OLE_HANDLE
    get_CurDC		proc :ptr
    SelectPicture	proc :HDC, :ptr, :ptr
    get_KeepOriginalFormat proc :ptr
    put_KeepOriginalFormat proc :BOOL
    PictureChanged	proc
    SaveAsFile		proc :LPSTREAM, :BOOL, :ptr
    get_Attributes	proc :ptr
   .ends

LPPICTURE		typedef ptr IPicture

endif

ifndef __IPicture2_INTERFACE_DEFINED__
define __IPicture2_INTERFACE_DEFINED__

HHANDLE			typedef UINT_PTR

DEFINE_IIDX(IPicture2, "F5185DD8-2012-4b0b-AAD9-F052C6BD482B")

.comdef IPicture2 : public IUnknown

    get_Handle		proc :ptr
    get_hPal		proc :ptr
    get_Type		proc :ptr
    get_Width		proc :ptr
    get_Height		proc :ptr
    Render		proc :HDC, :LONG, :LONG, :LONG, :LONG, :OLE_XPOS_HIMETRIC, :OLE_YPOS_HIMETRIC, :OLE_XSIZE_HIMETRIC, :OLE_YSIZE_HIMETRIC, :LPCRECT
    set_hPal		proc :HHANDLE
    get_CurDC		proc :ptr
    SelectPicture	proc :HDC, :ptr, :ptr
    get_KeepOriginalFormat proc :ptr
    put_KeepOriginalFormat proc :BOOL
    PictureChanged	proc
    SaveAsFile		proc :LPSTREAM, :BOOL, :ptr
    get_Attributes	proc :ptr
   .ends

LPPICTURE2		typedef ptr IPicture2

endif


ifndef __IFontEventsDisp_INTERFACE_DEFINED__
define __IFontEventsDisp_INTERFACE_DEFINED__

DEFINE_IIDX(IFontEventsDisp, "4EF6100A-AF88-11D0-9846-00C04FC29993")

.comdef IFontEventsDisp : public IDispatch

    .ends

LPFONTEVENTS		typedef ptr IFontEventsDisp

endif

ifndef __IFontDisp_INTERFACE_DEFINED__
define __IFontDisp_INTERFACE_DEFINED__

DEFINE_IIDX(IFontDisp, "BEF6E003-A874-101A-8BBA-00AA00300CAB")

.comdef IFontDisp : public IDispatch

    .ends

LPFONTDISP		typedef ptr IFontDisp

endif

ifndef __IPictureDisp_INTERFACE_DEFINED__
define __IPictureDisp_INTERFACE_DEFINED__

DEFINE_IIDX(IPictureDisp, "7BF80981-BF32-101A-8BBB-00AA00300CAB")

.comdef IPictureDisp : public IDispatch

    .ends

LPPICTUREDISP		typedef ptr IPictureDisp

endif

ifndef __IOleInPlaceObjectWindowless_INTERFACE_DEFINED__
define __IOleInPlaceObjectWindowless_INTERFACE_DEFINED__

DEFINE_IIDX(IOleInPlaceObjectWindowless, "1C2056CC-5EF4-101B-8BC8-00AA003E3B29")

.comdef IOleInPlaceObjectWindowless : public IOleInPlaceObject

    OnWindowMessage	proc :DWORD, :WPARAM, :LPARAM, :ptr
    GetDropTarget	proc :ptr
   .ends

LPOLEINPLACEOBJECTWINDOWLESS typedef ptr IOleInPlaceObjectWindowless

endif


ifndef __IOleInPlaceSiteEx_INTERFACE_DEFINED__
define __IOleInPlaceSiteEx_INTERFACE_DEFINED__


.enum ACTIVATEFLAGS {
	ACTIVATE_WINDOWLESS = 1
	}

DEFINE_IIDX(IOleInPlaceSiteEx, "9C2CAD80-3424-11CF-B670-00AA004CD6D8")

.comdef IOleInPlaceSiteEx : public IOleInPlaceSite

    OnInPlaceActivateEx proc :ptr, :DWORD
    OnInPlaceDeactivateEx proc :BOOL
    RequestUIActivate	proc
   .ends

LPOLEINPLACESITEEX	typedef ptr IOleInPlaceSiteEx

endif


ifndef __IOleInPlaceSiteWindowless_INTERFACE_DEFINED__
define __IOleInPlaceSiteWindowless_INTERFACE_DEFINED__


.enum OLEDCFLAGS {
	OLEDC_NODRAW	 = 0x1,
	OLEDC_PAINTBKGND = 0x2,
	OLEDC_OFFSCREEN	 = 0x4
	}

DEFINE_IIDX(IOleInPlaceSiteWindowless, "922EADA0-3424-11CF-B670-00AA004CD6D8")

.comdef IOleInPlaceSiteWindowless : public IOleInPlaceSiteEx

    CanWindowlessActivate proc
    GetCapture		proc
    SetCapture		proc :BOOL
    GetFocus		proc
    SetFocus		proc :BOOL
    GetDC		proc :LPCRECT, :DWORD, :ptr
    ReleaseDC		proc :HDC
    InvalidateRect	proc :LPCRECT, :BOOL
    InvalidateRgn	proc :HRGN, :BOOL
    ScrollRect		proc :DWORD, :DWORD, :LPCRECT, :LPCRECT
    AdjustRect		proc :LPRECT
    OnDefWindowMessage	proc :DWORD, :WPARAM, :LPARAM, :ptr
   .ends

LPOLEINPLACESITEWINDOWLESS typedef ptr IOleInPlaceSiteWindowless

endif

ifndef __IViewObjectEx_INTERFACE_DEFINED__
define __IViewObjectEx_INTERFACE_DEFINED__


.enum VIEWSTATUS {
	VIEWSTATUS_OPAQUE		= 1,
	VIEWSTATUS_SOLIDBKGND		= 2,
	VIEWSTATUS_DVASPECTOPAQUE	= 4,
	VIEWSTATUS_DVASPECTTRANSPARENT	= 8,
	VIEWSTATUS_SURFACE		= 16,
	VIEWSTATUS_3DSURFACE		= 32
	}

.enum HITRESULT {
	HITRESULT_OUTSIDE,
	HITRESULT_TRANSPARENT,
	HITRESULT_CLOSE,
	HITRESULT_HIT
	}

.enum DVASPECT2 {
	DVASPECT_OPAQUE		= 16,
	DVASPECT_TRANSPARENT	= 32
	}

DVEXTENTINFO		STRUC
cb			ULONG ?
dwExtentMode		dd ?
sizelProposed		SIZEL <>
DVEXTENTINFO		ENDS

.enum DVEXTENTMODE {
	DVEXTENT_CONTENT,
	DVEXTENT_INTEGRAL
	}

.enum DVASPECTINFOFLAG {
	DVASPECTINFOFLAG_CANOPTIMIZE = 1
	}

DVASPECTINFO		STRUC
cb			ULONG ?
dwFlags			dd ?
DVASPECTINFO		ENDS

CALLBACK(pDraw_pfnContinue, :DWORD)

DEFINE_IIDX(IViewObjectEx, "3AF24292-0C96-11CE-A0CF-00AA00600AB8")

.comdef IViewObjectEx : public IViewObject2

    GetRect		proc :DWORD, :LPRECTL
    GetViewStatus	proc :ptr
    QueryHitPoint	proc :DWORD, :LPCRECT, :POINT, :SDWORD, :ptr
    QueryHitRect	proc :DWORD, :LPCRECT, :LPCRECT, :SDWORD, :ptr
    GetNaturalExtent	proc :DWORD, :SDWORD, :ptr, :HDC, :ptr, :LPSIZEL
   .ends

endif

ifndef __IOleUndoUnit_INTERFACE_DEFINED__
define __IOleUndoUnit_INTERFACE_DEFINED__

DEFINE_IIDX(IOleUndoUnit, "894AD3B0-EF97-11CE-9BC9-00AA00608E01")

.comdef IOleUndoUnit : public IUnknown

    Do			proc :ptr
    GetDescription	proc :ptr
    GetUnitType		proc :ptr, :ptr
    OnNextAdd		proc
   .ends

LPOLEUNDOUNIT		typedef ptr IOleUndoUnit

endif

ifndef __IOleParentUndoUnit_INTERFACE_DEFINED__
define __IOleParentUndoUnit_INTERFACE_DEFINED__

DEFINE_IIDX(IOleParentUndoUnit, "A1FAF330-EF97-11CE-9BC9-00AA00608E01")

.comdef IOleParentUndoUnit : public IOleUndoUnit

    Open		proc :ptr
    Close		proc :ptr, :BOOL
    _Add		proc :ptr
    FindUnit		proc :ptr
    GetParentState	proc :ptr
   .ends

endif


ifndef __IEnumOleUndoUnits_INTERFACE_DEFINED__
define __IEnumOleUndoUnits_INTERFACE_DEFINED__

DEFINE_IIDX(IEnumOleUndoUnits, "B3E7C340-EF97-11CE-9BC9-00AA00608E01")

.comdef IEnumOleUndoUnits : public IUnknown

    Next		proc :ULONG, :ptr, :ptr
    Skip		proc :ULONG
    Reset		proc
    Clone		proc :ptr
   .ends

LPENUMOLEUNDOUNITS	typedef ptr IEnumOleUndoUnits

endif

ifndef __IOleUndoManager_INTERFACE_DEFINED__
define __IOleUndoManager_INTERFACE_DEFINED__


DEFINE_IIDX(IOleUndoManager, "D001F200-EF97-11CE-9BC9-00AA00608E01")
SID_SOleUndoManager	equ <IID_IOleUndoManager>

.comdef IOleUndoManager : public IUnknown

    Open		proc :ptr
    Close		proc :ptr, :BOOL
    _Add		proc :ptr
    GetOpenParentState	proc :ptr
    DiscardFrom		proc :ptr
    UndoTo		proc :ptr
    RedoTo		proc :ptr
    EnumUndoable	proc :ptr
    EnumRedoable	proc :ptr
    GetLastUndoDescription proc :ptr
    GetLastRedoDescription proc :ptr
    Enable		proc :BOOL
   .ends

LPOLEUNDOMANAGER	typedef ptr IOleUndoManager

endif

ifndef __IPointerInactive_INTERFACE_DEFINED__
define __IPointerInactive_INTERFACE_DEFINED__

.enum POINTERINACTIVE {
	POINTERINACTIVE_ACTIVATEONENTRY	  = 1,
	POINTERINACTIVE_DEACTIVATEONLEAVE = 2,
	POINTERINACTIVE_ACTIVATEONDRAG	  = 4
	}

DEFINE_IIDX(IPointerInactive, "55980BA0-35AA-11CF-B671-00AA004CD6D8")

.comdef IPointerInactive : public IUnknown

    GetActivationPolicy proc :ptr
    OnInactiveMouseMove proc :LPCRECT, :LONG, :LONG, :DWORD
    OnInactiveSetCursor proc :LPCRECT, :LONG, :LONG, :DWORD, :BOOL
   .ends

LPPOINTERINACTIVE	typedef ptr IPointerInactive

endif

ifndef __IObjectWithSite_INTERFACE_DEFINED__
define __IObjectWithSite_INTERFACE_DEFINED__

DEFINE_IIDX(IObjectWithSite, "FC4801A3-2BA9-11CF-A229-00AA003D7352")

.comdef IObjectWithSite : public IUnknown

    SetSite		proc :ptr
    GetSite		proc :REFIID, :ptr
   .ends

LPOBJECTWITHSITE	typedef ptr IObjectWithSite

endif


ifndef __IPerPropertyBrowsing_INTERFACE_DEFINED__
define __IPerPropertyBrowsing_INTERFACE_DEFINED__

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

DEFINE_IIDX(IPerPropertyBrowsing, "376BD3AA-3845-101B-84ED-08002B2EC713")

.comdef IPerPropertyBrowsing : public IUnknown

    GetDisplayString	proc :DISPID, :ptr
    MapPropertyToPage	proc :DISPID, :ptr
    GetPredefinedStrings proc :DISPID, :ptr, :ptr
    GetPredefinedValue	proc :DISPID, :DWORD, :ptr
   .ends

LPPERPROPERTYBROWSING	typedef ptr IPerPropertyBrowsing

endif


ifndef __IPropertyBag2_INTERFACE_DEFINED__
define __IPropertyBag2_INTERFACE_DEFINED__

PROPBAG2_TYPE		typedef SDWORD

PROPBAG2		STRUC
dwType			dd ?
vt			VARTYPE ?
cfType			CLIPFORMAT ?
dwHint			dd ?
pstrName		LPOLESTR ?
clsid			CLSID <>
PROPBAG2		ENDS

DEFINE_IIDX(IPropertyBag2, "22F55882-280B-11d0-A8A9-00A0C90C2004")

.comdef IPropertyBag2 : public IUnknown

    Read		proc :DWORD,:ptr, :ptr, :ptr, :ptr
    Write		proc :DWORD, :ptr, :ptr
    CountProperties	proc :ptr
    GetPropertyInfo	proc :DWORD, :DWORD, :ptr, :ptr
    LoadObject		proc :LPCOLESTR, :DWORD, :ptr, :ptr
   .ends

LPPROPERTYBAG2		typedef ptr IPropertyBag2

endif


ifndef __IPersistPropertyBag2_INTERFACE_DEFINED__
define __IPersistPropertyBag2_INTERFACE_DEFINED__

DEFINE_IIDX(IPersistPropertyBag2, "22F55881-280B-11d0-A8A9-00A0C90C2004")

.comdef IPersistPropertyBag2 : public IPersist

    InitNew		proc
    Load		proc :ptr, :ptr
    Save		proc :ptr, :BOOL, :BOOL
    IsDirty		proc
   .ends

LPPERSISTPROPERTYBAG2	typedef ptr IPersistPropertyBag2

endif


ifndef __IAdviseSinkEx_INTERFACE_DEFINED__
define __IAdviseSinkEx_INTERFACE_DEFINED__

DEFINE_IIDX(IAdviseSinkEx, "3AF24290-0C96-11CE-A0CF-00AA00600AB8")

.comdef IAdviseSinkEx : public IAdviseSink

    OnViewStatusChange	proc :DWORD
   .ends

LPADVISESINKEX		typedef ptr IAdviseSinkEx

endif

ifndef __IQuickActivate_INTERFACE_DEFINED__
define __IQuickActivate_INTERFACE_DEFINED__


.enum QACONTAINERFLAGS {
	QACONTAINER_SHOWHATCHING	= 0x1,
	QACONTAINER_SHOWGRABHANDLES	= 0x2,
	QACONTAINER_USERMODE		= 0x4,
	QACONTAINER_DISPLAYASDEFAULT	= 0x8,
	QACONTAINER_UIDEAD		= 0x10,
	QACONTAINER_AUTOCLIP		= 0x20,
	QACONTAINER_MESSAGEREFLECT	= 0x40,
	QACONTAINER_SUPPORTSMNEMONICS	= 0x80
	}

OLE_COLOR		typedef DWORD

QACONTAINER		STRUC
cbSize			ULONG ?
pClientSite		LPOLECLIENTSITE ?
pAdviseSink		LPADVISESINKEX ?
pPropertyNotifySink	LPPROPERTYNOTIFYSINK ?
pUnkEventSink		LPUNKNOWN ?
dwAmbientFlags		dd ?
colorFore		OLE_COLOR ?
colorBack		OLE_COLOR ?
pFont			LPFONT ?
pUndoMgr		LPOLEUNDOMANAGER ?
dwAppearance		dd ?
lcid			LONG ?
hpal			HPALETTE ?
pBindHost		LPBINDHOST ?
pOleControlSite		LPOLECONTROLSITE ?
pServiceProvider	LPSERVICEPROVIDER ?
QACONTAINER		ENDS

QACONTROL		STRUC
cbSize			ULONG ?
dwMiscStatus		dd ?
dwViewStatus		dd ?
dwEventCookie		dd ?
dwPropNotifyCookie	dd ?
dwPointerActivationPolicy dd ?
QACONTROL		ENDS

DEFINE_IIDX(IQuickActivate, "CF51ED10-62FE-11CF-BF86-00A0C9034836")

.comdef IQuickActivate : public IUnknown

    QuickActivate	proc :ptr, :ptr
    SetContentExtent	proc :LPSIZEL
    GetContentExtent	proc :LPSIZEL
   .ends

LPQUICKACTIVATE		typedef ptr IQuickActivate

endif

BSTR_UserSize proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree proto WINAPI :ptr, :ptr

CLIPFORMAT_UserSize proto WINAPI :ptr, :dword, :ptr
CLIPFORMAT_UserMarshal proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserFree proto WINAPI :ptr, :ptr

HACCEL_UserSize proto WINAPI :ptr, :dword, :ptr
HACCEL_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HACCEL_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HACCEL_UserFree proto WINAPI :ptr, :ptr

HDC_UserSize proto WINAPI :ptr, :dword, :ptr
HDC_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HDC_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HDC_UserFree proto WINAPI :ptr, :ptr


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


HWND_UserSize proto WINAPI :ptr, :dword, :ptr
HWND_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HWND_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HWND_UserFree proto WINAPI :ptr, :ptr

VARIANT_UserSize proto WINAPI :ptr, :dword, :ptr
VARIANT_UserMarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserFree proto WINAPI :ptr, :ptr

BSTR_UserSize64 proto WINAPI :ptr, :dword, :ptr
BSTR_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
BSTR_UserFree64 proto WINAPI :ptr, :ptr

CLIPFORMAT_UserSize64 proto WINAPI :ptr, :dword, :ptr
CLIPFORMAT_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
CLIPFORMAT_UserFree64 proto WINAPI :ptr, :ptr

HACCEL_UserSize proto WINAPI :ptr, :dword, :ptr
HACCEL_UserMarshal proto WINAPI :ptr, :ptr, :ptr
HACCEL_UserUnmarshal proto WINAPI :ptr, :ptr, :ptr
HACCEL_UserFree proto WINAPI :ptr, :ptr

HDC_UserSize64 proto WINAPI :ptr, :dword, :ptr
HDC_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HDC_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HDC_UserFree64 proto WINAPI :ptr, :ptr


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

HWND_UserSize64 proto WINAPI :ptr, :dword, :ptr
HWND_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
HWND_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
HWND_UserFree64 proto WINAPI :ptr, :ptr

VARIANT_UserSize64 proto WINAPI :ptr, :dword, :ptr
VARIANT_UserMarshal64 proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserUnmarshal64 proto WINAPI :ptr, :ptr, :ptr
VARIANT_UserFree64 proto WINAPI :ptr, :ptr

endif
