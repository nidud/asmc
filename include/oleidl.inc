ifndef _RPCNDR500_
include rpcndr500.inc
endif
ifndef __oleidl_h__
define __oleidl_h__
ifndef __objidl_h__
include objidl.inc
endif

ifndef __IOleAdviseHolder_INTERFACE_DEFINED__
define __IOleAdviseHolder_INTERFACE_DEFINED__

DEFINE_IIDX(IOleAdviseHolder, "00000111-0000-0000-C000-000000000046")

.comdef IOleAdviseHolder : public IUnknown

    Advise		proc :ptr, :ptr
    Unadvise		proc :DWORD
    EnumAdvise		proc :ptr
    SendOnRename	proc :ptr
    SendOnSave		proc
    SendOnClose		proc
   .ends

LPOLEADVISEHOLDER	typedef ptr IOleAdviseHolder

endif

ifndef __IOleCache_INTERFACE_DEFINED__
define __IOleCache_INTERFACE_DEFINED__

DEFINE_IIDX(IOleCache, "0000011e-0000-0000-C000-000000000046")

.comdef IOleCache : public IUnknown

    Cache		proc :ptr, :DWORD, :ptr
    Uncache		proc :DWORD
    EnumCache		proc :ptr
    InitCache		proc :ptr
    SetData		proc :ptr, :ptr, :BOOL
   .ends

LPOLECACHE		typedef ptr IOleCache

endif

ifndef __IOleCache2_INTERFACE_DEFINED__
define __IOleCache2_INTERFACE_DEFINED__

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

DEFINE_IIDX(IOleCache2, "00000128-0000-0000-C000-000000000046")

.comdef IOleCache2 : public IOleCache

    UpdateCache		proc :LPDATAOBJECT, :DWORD, :LPVOID
    DiscardCache	proc :DWORD
   .ends

LPOLECACHE2		typedef ptr IOleCache2

endif

ifndef __IOleCacheControl_INTERFACE_DEFINED__
define __IOleCacheControl_INTERFACE_DEFINED__

DEFINE_IIDX(IOleCacheControl, "00000129-0000-0000-C000-000000000046")

.comdef IOleCacheControl : public IUnknown

    OnRun		proc :LPDATAOBJECT
    OnStop		proc
   .ends

PPOLECACHECONTROL	typedef ptr IOleCacheControl

endif

ifndef __IParseDisplayName_INTERFACE_DEFINED__
define __IParseDisplayName_INTERFACE_DEFINED__

DEFINE_IIDX(IParseDisplayName, "0000011a-0000-0000-C000-000000000046")

.comdef IParseDisplayName : public IUnknown

    ParseDisplayName	proc :ptr, :LPOLESTR, :ptr, :ptr
   .ends

LPPARSEDISPLAYNAME	typedef ptr IParseDisplayName

endif

ifndef __IOleContainer_INTERFACE_DEFINED__
define __IOleContainer_INTERFACE_DEFINED__

DEFINE_IIDX(IOleContainer, "0000011b-0000-0000-C000-000000000046")

.comdef IOleContainer : public IParseDisplayName

    EnumObjects		proc :DWORD, :ptr
    LockContainer	proc :BOOL
   .ends

LPOLECONTAINER		typedef ptr IOleContainer

endif

ifndef __IOleClientSite_INTERFACE_DEFINED__
define __IOleClientSite_INTERFACE_DEFINED__

DEFINE_IIDX(IOleClientSite, "00000118-0000-0000-C000-000000000046")

.comdef IOleClientSite : public IUnknown

    SaveObject		proc
    GetMoniker		proc :DWORD, :DWORD, :ptr
    GetContainer	proc :ptr
    ShowObject		proc
    OnShowWindow	proc :BOOL
    RequestNewObjectLayout proc
   .ends

LPOLECLIENTSITE		typedef ptr IOleClientSite

endif

ifndef __IOleObject_INTERFACE_DEFINED__
define __IOleObject_INTERFACE_DEFINED__

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

DEFINE_IIDX(IOleObject, "00000112-0000-0000-C000-000000000046")

.comdef IOleObject : public IUnknown

    SetClientSite	proc :ptr
    GetClientSite	proc :ptr
    SetHostNames	proc :LPCOLESTR, :LPCOLESTR
    Close		proc :DWORD
    SetMoniker		proc :DWORD, :ptr
    GetMoniker		proc :DWORD, :DWORD, :ptr
    InitFromData	proc :ptr, :BOOL, :DWORD
    GetClipboardData	proc :DWORD ,:ptr
    DoVerb		proc :SDWORD,: LPMSG, :ptr, :SDWORD, :HWND, :LPCRECT
    EnumVerbs		proc :ptr
    Update		proc
    IsUpToDate		proc
    GetUserClassID	proc :ptr
    GetUserType		proc :DWORD, :ptr
    SetExtent		proc :DWORD, :ptr
    GetExtent		proc :DWORD, :ptr
    Advise		proc :ptr, :ptr
    Unadvise		proc :DWORD
    EnumAdvise		proc :ptr
    GetMiscStatus	proc :DWORD, :ptr
    SetColorScheme	proc :ptr
   .ends

LPOLEOBJECT		typedef ptr IOleObject

endif

ifndef __IOLETypes_INTERFACE_DEFINED__
define __IOLETypes_INTERFACE_DEFINED__

.enum OLERENDER {
    OLERENDER_NONE,
    OLERENDER_DRAW,
    OLERENDER_FORMAT,
    OLERENDER_ASIS,
    }
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

endif

ifndef __IOleWindow_INTERFACE_DEFINED__
define __IOleWindow_INTERFACE_DEFINED__

DEFINE_IIDX(IOleWindow, "00000114-0000-0000-C000-000000000046")

.comdef IOleWindow : public IUnknown

    GetWindow		proc :ptr
    ContextSensitiveHelp proc :BOOL
   .ends

LPOLEWINDOW		typedef ptr IOleWindow

endif

ifndef __IOleLink_INTERFACE_DEFINED__
define __IOleLink_INTERFACE_DEFINED__

.enum OLEUPDATE {
    OLEUPDATE_ALWAYS = 1,
    OLEUPDATE_ONCALL = 3,
    }

LPOLEUPDATE		typedef ptr OLEUPDATE
POLEUPDATE		typedef ptr OLEUPDATE

;typedef enum tagOLELINKBIND

OLELINKBIND_EVENIFCLASSDIFF equ 1

DEFINE_IIDX(IOleLink, "0000011d-0000-0000-C000-000000000046")

.comdef IOleLink : public IUnknown

    SetUpdateOptions	proc :DWORD
    GetUpdateOptions	proc :ptr
    SetSourceMoniker	proc :ptr, :REFCLSID
    GetSourceMoniker	proc :ptr
    SetSourceDisplayName proc :LPCOLESTR
    GetSourceDisplayName proc :ptr
    BindToSource	proc :DWORD, :ptr
    BindIfRunning	proc
    GetBoundSource	proc :ptr
    UnbindSource	proc
    Update		proc :ptr
   .ends

LPOLELINK		typedef ptr IOleLink

endif

ifndef __IOleItemContainer_INTERFACE_DEFINED__
define __IOleItemContainer_INTERFACE_DEFINED__

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

DEFINE_IIDX(IOleItemContainer, "0000011c-0000-0000-C000-000000000046")

.comdef IOleItemContainer : public IOleContainer

    GetObject		proc :LPOLESTR, :DWORD, :ptr, :REFIID, :ptr
    GetObjectStorage	proc :LPOLESTR, :ptr, :REFIID, :ptr
    IsRunning		proc :LPOLESTR
   .ends

LPOLEITEMCONTAINER	typedef ptr IOleItemContainer

endif

ifndef __IOleInPlaceUIWindow_INTERFACE_DEFINED__
define __IOleInPlaceUIWindow_INTERFACE_DEFINED__

BORDERWIDTHS		typedef RECT
LPBORDERWIDTHS		typedef LPRECT
LPCBORDERWIDTHS		typedef LPCRECT

DEFINE_IIDX(IOleInPlaceUIWindow, "00000115-0000-0000-C000-000000000046")

.comdef IOleInPlaceUIWindow : public IOleWindow

    GetBorder		proc :LPRECT
    RequestBorderSpace	proc :LPCBORDERWIDTHS
    SetBorderSpace	proc :LPCBORDERWIDTHS
    SetActiveObject	proc :ptr, :LPCOLESTR
   .ends

LPOLEINPLACEUIWINDOW	typedef ptr IOleInPlaceUIWindow

endif

ifndef __IOleInPlaceActiveObject_INTERFACE_DEFINED__
define __IOleInPlaceActiveObject_INTERFACE_DEFINED__

DEFINE_IIDX(IOleInPlaceActiveObject, "00000117-0000-0000-C000-000000000046")

.comdef IOleInPlaceActiveObject : public IOleWindow

    TranslateAccelerator proc :LPMSG
    OnFrameWindowActivate proc :BOOL
    OnDocWindowActivate proc :BOOL
    ResizeBorder	proc :LPCRECT, :ptr, :BOOL
    EnableModeless	proc :BOOL
   .ends

LPOLEINPLACEACTIVEOBJECT typedef ptr IOleInPlaceActiveObject

endif

ifndef __IOleInPlaceFrame_INTERFACE_DEFINED__
define __IOleInPlaceFrame_INTERFACE_DEFINED__

OLEINPLACEFRAMEINFO	STRUC
cb			UINT ?
fMDIApp			BOOL ?
hwndFrame		HWND ?
haccel			HACCEL ?
cAccelEntries		UINT ?
OLEINPLACEFRAMEINFO	ENDS
LPOLEINPLACEFRAMEINFO	typedef ptr OLEINPLACEFRAMEINFO

OLEMENUGROUPWIDTHS	STRUC
width			LONG 6 dup(?)
OLEMENUGROUPWIDTHS	ENDS

LPOLEMENUGROUPWIDTHS	typedef ptr OLEMENUGROUPWIDTHS
HOLEMENU		typedef HGLOBAL

DEFINE_IIDX(IOleInPlaceFrame, "00000116-0000-0000-C000-000000000046")

.comdef IOleInPlaceFrame : public IOleInPlaceUIWindow

    InsertMenus		proc :HMENU, :LPOLEMENUGROUPWIDTHS
    SetMenu		proc :HMENU, :HOLEMENU, :HWND
    RemoveMenus		proc :HMENU
    SetStatusText	proc :LPCOLESTR
    EnableModeless	proc :BOOL
    TranslateAccelerator proc :LPMSG, :WORD
   .ends

LPOLEINPLACEFRAME	typedef ptr IOleInPlaceFrame

endif

ifndef __IOleInPlaceObject_INTERFACE_DEFINED__
define __IOleInPlaceObject_INTERFACE_DEFINED__

DEFINE_IIDX(IOleInPlaceObject, "00000113-0000-0000-C000-000000000046")

.comdef IOleInPlaceObject : public IOleWindow

    InPlaceDeactivate	proc
    UIDeactivate	proc
    SetObjectRects	proc :LPCRECT, :LPCRECT
    ReactivateAndUndo	proc
   .ends

LPOLEINPLACEOBJECT	typedef ptr IOleInPlaceObject

endif

ifndef __IOleInPlaceSite_INTERFACE_DEFINED__
define __IOleInPlaceSite_INTERFACE_DEFINED__

DEFINE_IIDX(IOleInPlaceSite, "00000119-0000-0000-C000-000000000046")

.comdef IOleInPlaceSite : public IOleWindow

    CanInPlaceActivate	proc
    OnInPlaceActivate	proc
    OnUIActivate	proc
    GetWindowContext	proc :ptr, :ptr, :LPRECT, :LPRECT, :LPOLEINPLACEFRAMEINFO
    Scroll		proc :size_t
    OnUIDeactivate	proc :BOOL
    OnInPlaceDeactivate proc
    DiscardUndoState	proc
    DeactivateAndUndo	proc
    OnPosRectChange	proc :LPCRECT
   .ends

LPOLEINPLACESITE	typedef ptr IOleInPlaceSite

endif

ifndef __IContinue_INTERFACE_DEFINED__
define __IContinue_INTERFACE_DEFINED__

DEFINE_IIDX(IContinue, "0000012a-0000-0000-C000-000000000046")

.comdef IContinue : public IUnknown

    FContinue		proc
   .ends

endif

ifndef __IViewObject_INTERFACE_DEFINED__
define __IViewObject_INTERFACE_DEFINED__

DEFINE_IIDX(IViewObject, "0000010d-0000-0000-C000-000000000046")

.comdef IViewObject : public IUnknown

    Draw		proc :DWORD, :SDWORD, :ptr,:ptr, :HDC, :HDC, :LPCRECTL, :LPCRECTL, :ptr, :DWORD
    GetColorSet		proc :DWORD, :SDWORD, :ptr,:ptr, :HDC, :ptr
    Freeze		proc :DWORD, :SDWORD, :ptr,:ptr
    Unfreeze		proc :DWORD
    SetAdvise		proc :DWORD, :DWORD, :ptr
    GetAdvise		proc :ptr, :ptr, :ptr
   .ends

LPVIEWOBJECT		typedef ptr IViewObject

endif

ifndef __IViewObject2_INTERFACE_DEFINED__
define __IViewObject2_INTERFACE_DEFINED__

DEFINE_IIDX(IViewObject2, "00000127-0000-0000-C000-000000000046")

.comdef IViewObject2 : public IViewObject

    GetExtent		proc :DWORD, :SDWORD, :ptr, :LPSIZEL
   .ends

LPVIEWOBJECT2		typedef ptr IViewObject2

endif

ifndef __IDropSource_INTERFACE_DEFINED__
define __IDropSource_INTERFACE_DEFINED__

DEFINE_IIDX(IDropSource, "00000121-0000-0000-C000-000000000046")

.comdef IDropSource : public IUnknown

    QueryContinueDrag	proc :BOOL, :DWORD
    GiveFeedback	proc :DWORD
   .ends

LPDROPSOURCE		typedef ptr IDropSource

endif

ifndef __IDropTarget_INTERFACE_DEFINED__
define __IDropTarget_INTERFACE_DEFINED__

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

DEFINE_IIDX(IDropTarget, "00000122-0000-0000-C000-000000000046")

.comdef IDropTarget : public IUnknown

    DragEnter		proc :ptr, :DWORD, :POINTL, :ptr
    DragOver		proc :DWORD, :POINTL, :ptr
    DragLeave		proc
    Drop		proc :ptr, :DWORD, :POINTL, :ptr
   .ends

LPDROPTARGET		typedef ptr IDropTarget

endif

ifndef __IEnumOLEVERB_INTERFACE_DEFINED__
define __IEnumOLEVERB_INTERFACE_DEFINED__

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

DEFINE_IIDX(IEnumOLEVERB, "0000012B-0000-0000-C000-000000000046")

.comdef IEnumOLEVERB : public IUnknown

    Next		proc :DWORD, :LPOLEVERB, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr
   .ends

LPENUMOLEVERB		typedef ptr IEnumOLEVERB

endif

endif
