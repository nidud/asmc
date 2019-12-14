ifndef _RICHOLE_
_RICHOLE_ equ <>

REOBJECT		STRUC
cbStruct		dd ?
cp			LONG ?
clsid			CLSID <>
poleobj			LPOLEOBJECT ?
pstg			LPSTORAGE ?
polesite		LPOLECLIENTSITE ?
sizel			SIZEL <>
dvaspect		dd ?
dwFlags			dd ?
dwUser			dd ?
REOBJECT		ENDS

REO_GETOBJ_NO_INTERFACES equ 0x00000000
REO_GETOBJ_POLEOBJ	equ 0x00000001
REO_GETOBJ_PSTG		equ 0x00000002
REO_GETOBJ_POLESITE	equ 0x00000004
REO_GETOBJ_ALL_INTERFACES equ 0x00000007

REO_CP_SELECTION	equ -1

REO_IOB_SELECTION	equ -1
REO_IOB_USE_CP		equ -2

REO_NULL		equ 0x00000000
REO_READWRITEMASK	equ 0x000007FF
REO_CANROTATE		equ 0x00000080
REO_OWNERDRAWSELECT	equ 0x00000040
REO_DONTNEEDPALETTE	equ 0x00000020
REO_BLANK		equ 0x00000010
REO_DYNAMICSIZE		equ 0x00000008
REO_INVERTEDSELECT	equ 0x00000004
REO_BELOWBASELINE	equ 0x00000002
REO_RESIZABLE		equ 0x00000001
REO_USEASBACKGROUND	equ 0x00000400
REO_WRAPTEXTAROUND	equ 0x00000200
REO_ALIGNTORIGHT	equ 0x00000100

REO_LINK		equ 0x80000000
REO_STATIC		equ 0x40000000
REO_SELECTED		equ 0x08000000
REO_OPEN		equ 0x04000000
REO_INPLACEACTIVE	equ 0x02000000
REO_HILITED		equ 0x01000000
REO_LINKAVAILABLE	equ 0x00800000
REO_GETMETAFILE		equ 0x00400000

RECO_PASTE		equ 0x00000000
RECO_DROP		equ 0x00000001
RECO_COPY		equ 0x00000002
RECO_CUT		equ 0x00000003
RECO_DRAG		equ 0x00000004

.comdef IRichEditOle : public IUnknown

    GetClientSite	proc :ptr LPOLECLIENTSITE
    GetObjectCount	proc
    GetLinkCount	proc
    GetObject		proc :LONG, :ptr REOBJECT, :DWORD
    InsertObject	proc :ptr REOBJECT
    ConvertObject	proc :LONG, :REFCLSID, :LPCSTR
    ActivateAs		proc :REFCLSID, :REFCLSID
    SetHostNames	proc :LPCSTR, :LPCSTR
    SetLinkAvailable	proc :LONG, :BOOL
    SetDvaspect		proc :LONG, :DWORD
    HandsOffStorage	proc :LONG
    SaveCompleted	proc :LONG, :LPSTORAGE
    InPlaceDeactivate	proc
    ContextSensitiveHelp proc :BOOL
    GetClipboardData	proc :ptr CHARRANGE, :DWORD, :ptr LPDATAOBJECT
    ImportDataObject	proc :LPDATAOBJECT, :CLIPFORMAT, :HGLOBAL

    .ends
    LPRICHEDITOLE	typedef ptr IRichEditOle

.comdef IRichEditOleCallback : public IUnknown

    GetNewStorage	proc :ptr LPSTORAGE
    GetInPlaceContext	proc :ptr LPOLEINPLACEFRAME, :ptr LPOLEINPLACEUIWINDOW, :LPOLEINPLACEFRAMEINFO
    ShowContainerUI	proc :BOOL
    QueryInsertObject	proc :LPCLSID, :LPSTORAGE, :LONG
    DeleteObject	proc :LPOLEOBJECT
    QueryAcceptData	proc :LPDATAOBJECT, :ptr CLIPFORMAT, :DWORD, :BOOL, :HGLOBAL
    ContextSensitiveHelp proc :BOOL
    GetClipboardData	proc :ptr CHARRANGE, :DWORD, :ptr LPDATAOBJECT
    GetDragDropEffect	proc :BOOL, :DWORD, :LPDWORD
    GetContextMenu	proc :WORD, :LPOLEOBJECT, :ptr CHARRANGE, :ptr HMENU

    .ends
    LPRICHEDITOLECALLBACK typedef ptr IRichEditOleCallback

ifndef MAC
DEFINE_GUID(IID_IRichEditOle,	      0x00020D00, 0, 0, 0xC0,0,0,0,0,0,0,0x46)
DEFINE_GUID(IID_IRichEditOleCallback, 0x00020D03, 0, 0, 0xC0,0,0,0,0,0,0,0x46)
endif
endif ;; _RICHOLE_
