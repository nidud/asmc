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
__oleidl_h__ equ <>

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

;void
MIDL_user_free proto WINAPI :PVOID

ifndef __IOleAdviseHolder_INTERFACE_DEFINED__
__IOleAdviseHolder_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IOleAdviseHolder, "00000111-0000-0000-C000-000000000046")

.comdef IOleAdviseHolder
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Advise		proc :ptr, :ptr
    Unadvise		proc :DWORD
    EnumAdvise		proc :ptr ptr
    SendOnRename	proc :ptr
    SendOnSave		proc
    SendOnClose		proc
    .ends

LPOLEADVISEHOLDER	typedef ptr IOleAdviseHolder

endif

ifndef __IOleCache_INTERFACE_DEFINED__
__IOleCache_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IOleCache, "0000011e-0000-0000-C000-000000000046")

.comdef IOleCache
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Cache		proc :ptr, :DWORD, :ptr
    Uncache		proc :DWORD
    EnumCache		proc :ptr
    InitCache		proc :ptr
    SetData		proc :ptr, :ptr, :BOOL
    .ends

LPOLECACHE		typedef ptr IOleCache

endif

ifndef __IOleCache2_INTERFACE_DEFINED__
__IOleCache2_INTERFACE_DEFINED__ equ 1

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

.comdef IOleCache2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Cache		proc :ptr, :DWORD, :ptr
    Uncache		proc :DWORD
    EnumCache		proc :ptr
    InitCache		proc :ptr
    SetData		proc :ptr, :ptr, :BOOL
    UpdateCache		proc :LPDATAOBJECT, :DWORD, :LPVOID
    DiscardCache	proc :DWORD
    .ends

LPOLECACHE2		typedef ptr IOleCache2

endif

ifndef __IOleCacheControl_INTERFACE_DEFINED__
__IOleCacheControl_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IOleCacheControl, "00000129-0000-0000-C000-000000000046")

.comdef IOleCacheControl
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    OnRun		proc :LPDATAOBJECT
    OnStop		proc
    .ends

PPOLECACHECONTROL	typedef ptr IOleCacheControl

endif

ifndef __IParseDisplayName_INTERFACE_DEFINED__
__IParseDisplayName_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IParseDisplayName, "0000011a-0000-0000-C000-000000000046")

.comdef IParseDisplayName
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ParseDisplayName	proc :ptr, :LPOLESTR, :ptr, :ptr
    .ends

LPPARSEDISPLAYNAME	typedef ptr IParseDisplayName

endif

ifndef __IOleContainer_INTERFACE_DEFINED__
__IOleContainer_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IOleContainer, "0000011b-0000-0000-C000-000000000046")

.comdef IOleContainer
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ParseDisplayName	proc :ptr, :LPOLESTR, :ptr, :ptr
    EnumObjects_	proc :DWORD, :ptr
    LockContainer	proc :BOOL
    .ends

LPOLECONTAINER		typedef ptr IOleContainer

endif

ifndef __IOleClientSite_INTERFACE_DEFINED__
__IOleClientSite_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IOleClientSite, "00000118-0000-0000-C000-000000000046")

.comdef IOleClientSite
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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

DEFINE_IIDX(IOleObject, "00000112-0000-0000-C000-000000000046")

.comdef IOleObject
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    SetClientSite	proc :ptr
    GetClientSite	proc :ptr
    SetHostNames	proc :LPCOLESTR, :LPCOLESTR
    Close		proc :DWORD
    SetMoniker		proc :DWORD, :ptr
    GetMoniker		proc :DWORD, :DWORD, :ptr
    InitFromData	proc :ptr, :BOOL, :DWORD
    GetClipboardData_	proc :DWORD ,:ptr
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

endif

ifndef __IOleWindow_INTERFACE_DEFINED__
__IOleWindow_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IOleWindow, "00000114-0000-0000-C000-000000000046")

.comdef IOleWindow
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetWindow_		proc :ptr
    ContextSensitiveHelp proc :BOOL
    .ends

LPOLEWINDOW		typedef ptr IOleWindow

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

DEFINE_IIDX(IOleLink, "0000011d-0000-0000-C000-000000000046")

.comdef IOleLink
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
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

DEFINE_IIDX(IOleItemContainer, "0000011c-0000-0000-C000-000000000046")

.comdef IOleItemContainer
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    ParseDisplayName	proc :ptr, :LPOLESTR, :ptr, :ptr
    EnumObjects_	proc :DWORD, :ptr
    LockContainer	proc :BOOL
    GetObject_		proc :LPOLESTR, :DWORD, :ptr, :REFIID, :ptr
    GetObjectStorage	proc :LPOLESTR, :ptr, :REFIID, :ptr
    IsRunning		proc :LPOLESTR
    .ends

LPOLEITEMCONTAINER	typedef ptr IOleItemContainer

endif

ifndef __IOleInPlaceUIWindow_INTERFACE_DEFINED__
__IOleInPlaceUIWindow_INTERFACE_DEFINED__ equ 1

BORDERWIDTHS		typedef RECT
LPBORDERWIDTHS		typedef LPRECT
LPCBORDERWIDTHS		typedef LPCRECT

DEFINE_IIDX(IOleInPlaceUIWindow, "00000115-0000-0000-C000-000000000046")

.comdef IOleInPlaceUIWindow
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetWindow_		proc :ptr
    ContextSensitiveHelp proc :BOOL
    GetBorder		proc :LPRECT
    RequestBorderSpace	proc :LPCBORDERWIDTHS
    SetBorderSpace	proc :LPCBORDERWIDTHS
    SetActiveObject	proc :ptr, :LPCOLESTR
    .ends

LPOLEINPLACEUIWINDOW	typedef ptr IOleInPlaceUIWindow

endif

ifndef __IOleInPlaceActiveObject_INTERFACE_DEFINED__
__IOleInPlaceActiveObject_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IOleInPlaceActiveObject, "00000117-0000-0000-C000-000000000046")

.comdef IOleInPlaceActiveObject
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetWindow_		proc :ptr
    ContextSensitiveHelp proc :BOOL
    TranslateAccelerator_ proc :LPMSG
    OnFrameWindowActivate proc :BOOL
    OnDocWindowActivate proc :BOOL
    ResizeBorder	proc :LPCRECT, :ptr, :BOOL
    EnableModeless	proc :BOOL
    .ends

LPOLEINPLACEACTIVEOBJECT typedef ptr IOleInPlaceActiveObject

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
width			LONG 6 dup(?)
OLEMENUGROUPWIDTHS	ENDS

LPOLEMENUGROUPWIDTHS	typedef ptr OLEMENUGROUPWIDTHS
HOLEMENU		typedef HGLOBAL

DEFINE_IIDX(IOleInPlaceFrame, "00000116-0000-0000-C000-000000000046")

.comdef IOleInPlaceFrame
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetWindow_		proc :ptr
    ContextSensitiveHelp proc :BOOL
    GetBorder		proc :LPRECT
    RequestBorderSpace	proc :LPCBORDERWIDTHS
    SetBorderSpace	proc :LPCBORDERWIDTHS
    SetActiveObject	proc :ptr, :LPCOLESTR
    InsertMenus		proc :HMENU, :LPOLEMENUGROUPWIDTHS
    SetMenu_		proc :HMENU, :HOLEMENU, :HWND
    RemoveMenus		proc :HMENU
    SetStatusText	proc :LPCOLESTR
    EnableModeless	proc :BOOL
    TranslateAccelerator_ proc :LPMSG, :WORD
    .ends

LPOLEINPLACEFRAME	typedef ptr IOleInPlaceFrame

endif

ifndef __IOleInPlaceObject_INTERFACE_DEFINED__
__IOleInPlaceObject_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IOleInPlaceObject, "00000113-0000-0000-C000-000000000046")

.comdef IOleInPlaceObject
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetWindow_		proc :ptr
    ContextSensitiveHelp proc :BOOL
    InPlaceDeactivate	proc
    UIDeactivate	proc
    SetObjectRects	proc :LPCRECT, :LPCRECT
    ReactivateAndUndo	proc
    .ends

LPOLEINPLACEOBJECT	typedef ptr IOleInPlaceObject

endif

ifndef __IOleInPlaceSite_INTERFACE_DEFINED__
__IOleInPlaceSite_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IOleInPlaceSite, "00000119-0000-0000-C000-000000000046")

.comdef IOleInPlaceSite
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    GetWindow_		proc :ptr
    ContextSensitiveHelp proc :BOOL
    CanInPlaceActivate	proc
    OnInPlaceActivate	proc
    OnUIActivate	proc
    GetWindowContext	proc :ptr, :ptr, :LPRECT, :LPRECT, :LPOLEINPLACEFRAMEINFO
    Scroll		proc :SIZE_T
    OnUIDeactivate	proc :BOOL
    OnInPlaceDeactivate proc
    DiscardUndoState	proc
    DeactivateAndUndo	proc
    OnPosRectChange	proc :LPCRECT
    .ends

LPOLEINPLACESITE	typedef ptr IOleInPlaceSite

endif

ifndef __IContinue_INTERFACE_DEFINED__
__IContinue_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IContinue, "0000012a-0000-0000-C000-000000000046")

.comdef IContinue
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    FContinue		proc
    .ends

endif

ifndef __IViewObject_INTERFACE_DEFINED__
__IViewObject_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IViewObject, "0000010d-0000-0000-C000-000000000046")

.comdef IViewObject
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Draw		proc :DWORD, :SDWORD, :ptr ,:ptr, :HDC, :HDC, :LPCRECTL, :LPCRECTL, :ptr, :DWORD
    GetColorSet		proc :DWORD, :SDWORD, :ptr ,:ptr, :HDC, :ptr
    Freeze		proc :DWORD, :SDWORD, :ptr ,:ptr
    Unfreeze		proc :DWORD
    SetAdvise		proc :DWORD, :DWORD, :ptr
    GetAdvise		proc :ptr, :ptr, :ptr
    .ends

LPVIEWOBJECT		typedef ptr IViewObject

endif

ifndef __IViewObject2_INTERFACE_DEFINED__
__IViewObject2_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IViewObject2, "00000127-0000-0000-C000-000000000046")

.comdef IViewObject2
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Draw		proc :DWORD, :SDWORD, :ptr ,:ptr, :HDC, :HDC, :LPCRECTL, :LPCRECTL, :ptr, :DWORD
    GetColorSet		proc :DWORD, :SDWORD, :ptr, :ptr, :HDC, :ptr
    Freeze		proc :DWORD, :SDWORD, :ptr, :ptr
    Unfreeze		proc :DWORD
    SetAdvise		proc :DWORD, :DWORD, :ptr
    GetAdvise		proc :ptr, :ptr, :ptr
    GetExtent		proc :DWORD, :SDWORD, :ptr, :LPSIZEL
    .ends

LPVIEWOBJECT2		typedef ptr IViewObject2

endif

ifndef __IDropSource_INTERFACE_DEFINED__
__IDropSource_INTERFACE_DEFINED__ equ 1

DEFINE_IIDX(IDropSource, "00000121-0000-0000-C000-000000000046")

.comdef IDropSource
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    QueryContinueDrag	proc :BOOL, :DWORD
    GiveFeedback	proc :DWORD
    .ends

LPDROPSOURCE		typedef ptr IDropSource

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

DEFINE_IIDX(IDropTarget, "00000122-0000-0000-C000-000000000046")

.comdef IDropTarget
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    DragEnter		proc :ptr, :DWORD, :POINTL, :ptr
    DragOver		proc :DWORD, :POINTL, :ptr
    DragLeave		proc
    Drop		proc :ptr, :DWORD, :POINTL, :ptr
    .ends

LPDROPTARGET		typedef ptr IDropTarget

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

DEFINE_IIDX(IEnumOLEVERB, "0000012B-0000-0000-C000-000000000046")

.comdef IEnumOLEVERB
    QueryInterface	proc :REFIID, :ptr
    AddRef		proc
    Release		proc
    Next		proc :DWORD, :LPOLEVERB, :ptr
    Skip		proc :DWORD
    Reset		proc
    Clone		proc :ptr
    .ends

LPENUMOLEVERB		typedef ptr IEnumOLEVERB

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

endif
