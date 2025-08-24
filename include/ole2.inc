ifndef _OLE2_H_
define _OLE2_H_

include winapifamily.inc

;ifndef WIN32
;define WIN32	 100
;endif

include winerror.inc
include objbase.inc
include oleauto.inc
include coml2api.inc

.pragma comment(lib, ole32)

define E_DRAW		       VIEW_E_DRAW
define DATA_E_FORMATETC	       DV_E_FORMATETC

define OLEIVERB_PRIMARY		   (0)
define OLEIVERB_SHOW		   (-1)
define OLEIVERB_OPEN		   (-2)
define OLEIVERB_HIDE		   (-3)
define OLEIVERB_UIACTIVATE	   (-4)
define OLEIVERB_INPLACEACTIVATE	   (-5)
define OLEIVERB_DISCARDUNDOSTATE   (-6)

define EMBDHLP_INPROC_HANDLER	0x0000
define EMBDHLP_INPROC_SERVER	0x0001
define EMBDHLP_CREATENOW    0x00000000
define EMBDHLP_DELAYCREATE  0x00010000

define OLECREATE_LEAVERUNNING	0x00000001

include oleidl.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

if not defined(ISOLATION_AWARE_ENABLED) or not ISOLATION_AWARE_ENABLED or not defined(_OBJBASE_H_) or not defined(CreateDataAdviseHolder)
CreateDataAdviseHolder proto WINAPI :ptr
endif

OleBuildVersion proto WINAPI

WriteFmtUserTypeStg proto WINAPI :LPSTORAGE, :CLIPFORMAT, :LPOLESTR
ReadFmtUserTypeStg proto WINAPI :LPSTORAGE, :ptr, :ptr

OleInitialize proto WINAPI :LPVOID
OleUninitialize proto WINAPI
OleQueryLinkFromData proto WINAPI :LPDATAOBJECT
OleQueryCreateFromData proto WINAPI :LPDATAOBJECT

OleCreate proto WINAPI :REFCLSID, :REFIID, :DWORD, :LPFORMATETC, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateEx proto WINAPI :REFCLSID, :REFIID, :DWORD, :DWORD, :ULONG, :ptr, :LPFORMATETC, :ptr, :ptr, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateFromData proto WINAPI :LPDATAOBJECT, :REFIID, :DWORD, :LPFORMATETC, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateFromDataEx proto WINAPI :LPDATAOBJECT, :REFIID, :DWORD, :DWORD, :ULONG, :ptr, :LPFORMATETC, :ptr, :ptr, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateLinkFromData proto WINAPI :LPDATAOBJECT, :REFIID, :DWORD, :LPFORMATETC, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateLinkFromDataEx proto WINAPI :LPDATAOBJECT, :REFIID, :DWORD, :DWORD, :ULONG, :ptr, :LPFORMATETC, :ptr, :ptr, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateStaticFromData proto WINAPI :LPDATAOBJECT, :REFIID, :DWORD, :LPFORMATETC, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateLink proto WINAPI :LPMONIKER, :REFIID, :DWORD, :LPFORMATETC, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateLinkEx proto WINAPI :LPMONIKER, :REFIID, :DWORD, :DWORD, :ULONG, :ptr, :LPFORMATETC, :ptr, :ptr, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateLinkToFile proto WINAPI :LPCOLESTR, :REFIID, :DWORD, :LPFORMATETC, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateLinkToFileEx proto WINAPI :LPCOLESTR, :REFIID, :DWORD, :DWORD, :ULONG, :ptr, :LPFORMATETC, :ptr, :ptr, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateFromFile proto WINAPI :REFCLSID, :LPCOLESTR, :REFIID, :DWORD, :LPFORMATETC, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleCreateFromFileEx proto WINAPI :REFCLSID, :LPCOLESTR, :REFIID, :DWORD, :DWORD, :ULONG, :ptr, :LPFORMATETC, :ptr, :ptr, :LPOLECLIENTSITE, :LPSTORAGE, :ptr
OleLoad proto WINAPI :LPSTORAGE, :REFIID, :LPOLECLIENTSITE, :ptr
OleSave proto WINAPI :LPPERSISTSTORAGE, :LPSTORAGE, :BOOL

OleLoadFromStream proto WINAPI :LPSTREAM, :REFIID, :ptr
OleSaveToStream proto WINAPI :LPPERSISTSTREAM, :LPSTREAM

OleSetContainedObject proto WINAPI :LPUNKNOWN, :BOOL
OleNoteObjectVisible proto WINAPI :LPUNKNOWN, :BOOL

RegisterDragDrop proto WINAPI :HWND, :LPDROPTARGET
RevokeDragDrop proto WINAPI :HWND
DoDragDrop proto WINAPI :LPDATAOBJECT, :LPDROPSOURCE, :DWORD, :LPDWORD

OleSetClipboard proto WINAPI :LPDATAOBJECT
OleGetClipboard proto WINAPI :ptr
if (NTDDI_VERSION ge NTDDI_WIN10_RS1)
OleGetClipboardWithEnterpriseInfo proto WINAPI :ptr ptr, :ptr, :ptr, :ptr, :ptr
endif
OleFlushClipboard proto WINAPI
OleIsCurrentClipboard proto WINAPI :LPDATAOBJECT

OleCreateMenuDescriptor proto WINAPI :HMENU, :LPOLEMENUGROUPWIDTHS
OleSetMenuDescriptor proto WINAPI :HOLEMENU, :HWND, :HWND, :LPOLEINPLACEFRAME, :LPOLEINPLACEACTIVEOBJECT
OleDestroyMenuDescriptor proto WINAPI :HOLEMENU

OleTranslateAccelerator proto WINAPI :LPOLEINPLACEFRAME, :LPOLEINPLACEFRAMEINFO, :LPMSG
OleDuplicateData proto WINAPI :HANDLE, :CLIPFORMAT, :UINT
OleDraw proto WINAPI :LPUNKNOWN, :DWORD, :HDC, :LPCRECT

OleRun proto WINAPI :LPUNKNOWN
OleIsRunning proto WINAPI :LPOLEOBJECT
OleLockRunning proto WINAPI :LPUNKNOWN, :BOOL, :BOOL

ReleaseStgMedium proto WINAPI :LPSTGMEDIUM

CreateOleAdviseHolder proto WINAPI :ptr
OleCreateDefaultHandler proto WINAPI :REFCLSID, :LPUNKNOWN, :REFIID, :ptr
OleCreateEmbeddingHelper proto WINAPI :REFCLSID, :LPUNKNOWN, :DWORD, :LPCLASSFACTORY, :REFIID, :ptr

IsAccelerator proto WINAPI :HACCEL, :sdword, :LPMSG, :ptr

OleGetIconOfFile proto WINAPI :LPOLESTR, :BOOL
OleGetIconOfClass proto WINAPI :REFCLSID, :LPOLESTR, :BOOL
OleMetafilePictFromIconAndLabel proto WINAPI :HICON, :LPOLESTR, :LPOLESTR, :UINT
OleRegGetUserType proto WINAPI :REFCLSID, :DWORD, :ptr
OleRegGetMiscStatus proto WINAPI :REFCLSID, :DWORD, :ptr
OleRegEnumFormatEtc proto WINAPI :REFCLSID, :DWORD, :ptr
OleRegEnumVerbs proto WINAPI :REFCLSID, :ptr

.pragma pack(push, size_t)

LPOLESTREAM		typedef ptr

OLESTREAMVTBL		struct
Get			proc :LPOLESTREAM, :ptr, :DWORD
Put			proc :LPOLESTREAM, :ptr, :DWORD
OLESTREAMVTBL		ends
LPOLESTREAMVTBL		typedef ptr OLESTREAMVTBL

OLESTREAM		struct
lpstbl			LPOLESTREAMVTBL ?
OLESTREAM		ends

.pragma pack(pop)

OleConvertOLESTREAMToIStorage proto WINAPI :LPOLESTREAM, :LPSTORAGE, :ptr
OleConvertIStorageToOLESTREAM proto WINAPI :LPSTORAGE, :LPOLESTREAM
OleDoAutoConvert proto WINAPI :LPSTORAGE, :LPCLSID
OleGetAutoConvert proto WINAPI :REFCLSID, :LPCLSID
OleSetAutoConvert proto WINAPI :REFCLSID, :REFCLSID

SetConvertStg proto WINAPI :LPSTORAGE, :BOOL

OleConvertIStorageToOLESTREAMEx proto WINAPI :LPSTORAGE, :CLIPFORMAT, :LONG, :LONG, :DWORD, :LPSTGMEDIUM, :LPOLESTREAM
OleConvertOLESTREAMToIStorageEx proto WINAPI :LPOLESTREAM, :LPSTORAGE, :ptr, :ptr, :ptr, :ptr, :LPSTGMEDIUM

endif

endif
