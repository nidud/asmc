ifndef __LIBC_INC
 include libc.inc
endif
ifndef _OLE2_H_
.xlist
_OLE2_H_ equ 1

;#include <pshpack8.h>

;ifndef WIN32
;WIN32 equ 100
;endif


include winerror.inc
include objbase.inc
include oleauto.inc
.xlist


E_DRAW			equ VIEW_E_DRAW

DATA_E_FORMATETC	equ DV_E_FORMATETC


OLEIVERB_PRIMARY	equ (0)
OLEIVERB_SHOW		equ (-1)
OLEIVERB_OPEN		equ (-2)
OLEIVERB_HIDE		equ (-3)
OLEIVERB_UIACTIVATE	equ (-4)
OLEIVERB_INPLACEACTIVATE equ (-5)
OLEIVERB_DISCARDUNDOSTATE equ (-6)

EMBDHLP_INPROC_HANDLER	equ 0x0000
EMBDHLP_INPROC_SERVER	equ 0x0001
EMBDHLP_CREATENOW	equ 0x00000000
EMBDHLP_DELAYCREATE	equ 0x00010000

OLECREATE_LEAVERUNNING	equ 0x00000001


include oleidl.inc
.xlist



CreateDataAdviseHolder proto WINAPI \
	    ppDAHolder: LPDATAADVISEHOLDER


;DWORD
OleBuildVersion proto WINAPI


ReadClassStg proto WINAPI \
		  pStg: LPSTORAGE,
		pclsid: ptr CLSID

WriteClassStg proto WINAPI \
		  pStg: LPSTORAGE,
		rclsid: REFCLSID

ReadClassStm proto WINAPI \
		  pStm: LPSTREAM,
		pclsid: ptr CLSID

WriteClassStm proto WINAPI \
		  pStm: LPSTREAM,
		rclsid: REFCLSID

WriteFmtUserTypeStg proto WINAPI \
		  pstg: LPSTORAGE,
		    cf: CLIPFORMAT,
	  lpszUserType: LPOLESTR

ReadFmtUserTypeStg proto WINAPI \
		  pstg: LPSTORAGE,
		   pcf: ptr CLIPFORMAT,
	lplpszUserType: LPOLESTR



OleInitialize proto WINAPI \
	    pvReserved: LPVOID
;void



OleQueryLinkFromData proto WINAPI \
	pSrcDataObject: LPDATAOBJECT

OleQueryCreateFromData proto WINAPI \
	pSrcDataObject: LPDATAOBJECT




OleCreate proto WINAPI \
		rclsid: REFCLSID,
		  riid: REFIID,
	     renderopt: DWORD,
	    pFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateEx proto WINAPI \
		rclsid: REFCLSID,
		  riid: REFIID,
	       dwFlags: DWORD,
	     renderopt: DWORD,
	      cFormats: ULONG,
		rgAdvf: LPDWORD,
	   rgFormatEtc: LPFORMATETC,
	  lpAdviseSink: ptr IAdviseSink,
	rgdwConnection: LPDWORD,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateFromData proto WINAPI \
	   pSrcDataObj: LPDATAOBJECT,
		  riid: REFIID,
	     renderopt: DWORD,
	    pFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateFromDataEx proto WINAPI \
	   pSrcDataObj: LPDATAOBJECT,
		  riid: REFIID,
	       dwFlags: DWORD,
	     renderopt: DWORD,
	      cFormats: ULONG,
		rgAdvf: LPDWORD,
	   rgFormatEtc: LPFORMATETC,
	  lpAdviseSink: ptr IAdviseSink,
	rgdwConnection: LPDWORD,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateLinkFromData proto WINAPI \
	   pSrcDataObj: LPDATAOBJECT,
		  riid: REFIID,
	     renderopt: DWORD,
	    pFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateLinkFromDataEx proto WINAPI \
	   pSrcDataObj: LPDATAOBJECT,
		  riid: REFIID,
	       dwFlags: DWORD,
	     renderopt: DWORD,
	      cFormats: ULONG,
		rgAdvf: LPDWORD,
	   rgFormatEtc: LPFORMATETC,
	  lpAdviseSink: ptr IAdviseSink,
	rgdwConnection: LPDWORD,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateStaticFromData proto WINAPI \
	   pSrcDataObj: LPDATAOBJECT,
		   iid: REFIID,
	     renderopt: DWORD,
	    pFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID



OleCreateLink proto WINAPI \
	    pmkLinkSrc: LPMONIKER,
		  riid: REFIID,
	     renderopt: DWORD,
	   lpFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateLinkEx proto WINAPI \
	    pmkLinkSrc: LPMONIKER,
		  riid: REFIID,
	       dwFlags: DWORD,
	     renderopt: DWORD,
	      cFormats: ULONG,
		rgAdvf: LPDWORD,
	   rgFormatEtc: LPFORMATETC,
	  lpAdviseSink: ptr IAdviseSink,
	rgdwConnection: LPDWORD,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateLinkToFile proto WINAPI \
	  lpszFileName: LPCOLESTR,
		  riid: REFIID,
	     renderopt: DWORD,
	   lpFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateLinkToFileEx proto WINAPI \
	  lpszFileName: LPCOLESTR,
		  riid: REFIID,
	       dwFlags: DWORD,
	     renderopt: DWORD,
	      cFormats: ULONG,
		rgAdvf: LPDWORD,
	   rgFormatEtc: LPFORMATETC,
	  lpAdviseSink: ptr IAdviseSink,
	rgdwConnection: LPDWORD,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateFromFile proto WINAPI \
		rclsid: REFCLSID,
	  lpszFileName: LPCOLESTR,
		  riid: REFIID,
	     renderopt: DWORD,
	   lpFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateFromFileEx proto WINAPI \
		rclsid: REFCLSID,
	  lpszFileName: LPCOLESTR,
		  riid: REFIID,
	       dwFlags: DWORD,
	     renderopt: DWORD,
	      cFormats: ULONG,
		rgAdvf: LPDWORD,
	   rgFormatEtc: LPFORMATETC,
	  lpAdviseSink: ptr IAdviseSink,
	rgdwConnection: LPDWORD,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleLoad proto WINAPI \
		  pStg: LPSTORAGE,
		  riid: REFIID,
	   pClientSite: LPOLECLIENTSITE,
		ppvObj: LPVOID


OleSave proto WINAPI \
		   pPS: LPPERSISTSTORAGE,
		  pStg: LPSTORAGE,
	   fSameAsLoad: BOOL


OleLoadFromStream proto WINAPI \
		  pStm: LPSTREAM,
	  iidInterface: REFIID,
		ppvObj: LPVOID

OleSaveToStream proto WINAPI \
		 pPStm: LPPERSISTSTREAM,
		  pStm: LPSTREAM



OleSetContainedObject proto WINAPI \
	      pUnknown: LPUNKNOWN,
	    fContained: BOOL

OleNoteObjectVisible proto WINAPI \
	      pUnknown: LPUNKNOWN,
	      fVisible: BOOL




RegisterDragDrop proto WINAPI \
		  hwnd: HWND,
	   pDropTarget: LPDROPTARGET

RevokeDragDrop proto WINAPI \
		  hwnd: HWND

DoDragDrop proto WINAPI \
	      pDataObj: LPDATAOBJECT,
	   pDropSource: LPDROPSOURCE,
	   dwOKEffects: DWORD,
	     pdwEffect: LPDWORD



OleSetClipboard proto WINAPI \
	      pDataObj: LPDATAOBJECT

OleGetClipboard proto WINAPI \
	     ppDataObj: LPDATAOBJECT


OleIsCurrentClipboard proto WINAPI \
	      pDataObj: LPDATAOBJECT



;HOLEMENU
OleCreateMenuDescriptor proto WINAPI \
	 hmenuCombined: HMENU,
	  lpMenuWidths: LPOLEMENUGROUPWIDTHS

OleSetMenuDescriptor proto WINAPI \
	      holemenu: HOLEMENU,
	     hwndFrame: HWND,
      hwndActiveObject: HWND,
	       lpFrame: LPOLEINPLACEFRAME,
	   lpActiveObj: LPOLEINPLACEACTIVEOBJECT

OleDestroyMenuDescriptor proto WINAPI \
	      holemenu: HOLEMENU


OleTranslateAccelerator proto WINAPI \
	       lpFrame: LPOLEINPLACEFRAME,
	   lpFrameInfo: LPOLEINPLACEFRAMEINFO,
		 lpmsg: LPMSG


;HANDLE
OleDuplicateData proto WINAPI \
		  hSrc: HANDLE,
	      cfFormat: CLIPFORMAT,
	       uiFlags: UINT


OleDraw proto WINAPI \
	      pUnknown: LPUNKNOWN,
	      dwAspect: DWORD,
	       hdcDraw: HDC,
	    lprcBounds: LPCRECT


OleRun proto WINAPI \
	      pUnknown: LPUNKNOWN
;BOOL
OleIsRunning proto WINAPI \
	       pObject: LPOLEOBJECT

OleLockRunning proto WINAPI \
	      pUnknown: LPUNKNOWN,
		 fLock: BOOL,
     fLastUnlockCloses: BOOL

;void
CreateOleAdviseHolder proto WINAPI \
	    ppOAHolder: LPOLEADVISEHOLDER

OleCreateDefaultHandler proto WINAPI \
		 clsid: REFCLSID,
	     pUnkOuter: LPUNKNOWN,
		  riid: REFIID,
	       lplpObj: LPVOID


OleCreateEmbeddingHelper proto WINAPI \
		 clsid: REFCLSID,
	     pUnkOuter: LPUNKNOWN,
		 flags: DWORD,
		   pCF: LPCLASSFACTORY,
		  riid: REFIID,
	       lplpObj: LPVOID

;BOOL
IsAccelerator proto WINAPI \
		hAccel: HACCEL,
	 cAccelEntries: SINT,
		 lpMsg: LPMSG,
		lpwCmd: LPWORD

;HGLOBAL
OleGetIconOfFile proto WINAPI \
	      lpszPath: LPOLESTR,
       fUseFileAsLabel: BOOL

;HGLOBAL
OleGetIconOfClass proto WINAPI \
		rclsid: REFCLSID,
	     lpszLabel: LPOLESTR,
       fUseTypeAsLabel: BOOL

;HGLOBAL
OleMetafilePictFromIconAndLabel proto WINAPI \
		 hIcon: HICON,
	     lpszLabel: LPOLESTR,
	lpszSourceFile: LPOLESTR,
	    iIconIndex: UINT





OleRegGetUserType proto WINAPI \
		 clsid: REFCLSID,
	  dwFormOfType: DWORD,
	   pszUserType: LPOLESTR


OleRegGetMiscStatus proto WINAPI \
		 clsid: REFCLSID,
	      dwAspect: DWORD,
	     pdwStatus: LPDWORD


OleRegEnumFormatEtc proto WINAPI \
		 clsid: REFCLSID,
	   dwDirection: DWORD,
		ppenum: LPENUMFORMATETC


OleRegEnumVerbs proto WINAPI \
		 clsid: REFCLSID,
		ppenum: LPENUMOLEVERB



LPOLESTREAM	typedef ptr OLESTREAM

CALLBACK(OLESTREAMVTBL_P, :LPOLESTREAM, :PVOID, :DWORD)

OLESTREAMVTBL		STRUC
Get			OLESTREAMVTBL_P ?
Put			OLESTREAMVTBL_P ?
OLESTREAMVTBL		ENDS
LPOLESTREAMVTBL		typedef	 ptr OLESTREAMVTBL

OLESTREAM		STRUC
lpstbl			LPOLESTREAMVTBL ?
OLESTREAM		ENDS

OleConvertOLESTREAMToIStorage proto WINAPI \
	   lpolestream: LPOLESTREAM,
		  pstg: LPSTORAGE,
		   ptd: ptr DVTARGETDEVICE


OleConvertIStorageToOLESTREAM proto WINAPI \
		  pstg: LPSTORAGE,
	   lpolestream: LPOLESTREAM



GetHGlobalFromILockBytes proto WINAPI \
		plkbyt: LPLOCKBYTES,
	      phglobal: ptr HGLOBAL

CreateILockBytesOnHGlobal proto WINAPI \
	       hGlobal: HGLOBAL,
      fDeleteOnRelease: BOOL,
	       pplkbyt: ptr LPLOCKBYTES


GetHGlobalFromStream proto WINAPI \
		  pstm: LPSTREAM,
	      phglobal: ptr HGLOBAL

CreateStreamOnHGlobal proto WINAPI \
	       hGlobal: HGLOBAL,
      fDeleteOnRelease: BOOL,
		 ppstm: ptr LPSTREAM




OleDoAutoConvert proto WINAPI \
		  pStg: LPSTORAGE,
	     pClsidNew: LPCLSID

OleGetAutoConvert proto WINAPI \
	      clsidOld: REFCLSID,
	     pClsidNew: LPCLSID

OleSetAutoConvert proto WINAPI \
	      clsidOld: REFCLSID,
	      clsidNew: REFCLSID

GetConvertStg proto WINAPI \
		  pStg: LPSTORAGE

SetConvertStg proto WINAPI \
		  pStg: LPSTORAGE,
	      fConvert: BOOL


OleConvertIStorageToOLESTREAMEx proto WINAPI \
		  pstg: LPSTORAGE,
	      cfFormat: CLIPFORMAT,
		lWidth: LONG,
	       lHeight: LONG,
		dwSize: DWORD,
	       pmedium: LPSTGMEDIUM,
	       polestm: LPOLESTREAM

OleConvertOLESTREAMToIStorageEx proto WINAPI \
	       polestm: LPOLESTREAM,
		  pstg: LPSTORAGE,
	     pcfFormat: ptr CLIPFORMAT,
	      plwWidth: ptr LONG,
	      plHeight: ptr LONG,
	       pdwSize: LPDWORD,
	       pmedium: LPSTGMEDIUM

.list

endif

