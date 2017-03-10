ifndef __LIBC_INC
 include libc.inc
endif
ifndef _OLE2_H_
.xlist
_OLE2_H_ equ 1

;; Set packing to 8
;#include <pshpack8.h>

;; Make 100% sure WIN32 is defined
;ifndef WIN32
;WIN32 equ 100	;; 100 EQ NT version 1.0
;endif

;; SET to remove _export from interface definitions

include winerror.inc
include objbase.inc
include oleauto.inc
.xlist

;; View OBJECT Error Codes

E_DRAW			equ VIEW_E_DRAW

;; IDataObject Error Codes
DATA_E_FORMATETC	equ DV_E_FORMATETC

;; Common stuff gleamed from OLE.2,

;; verbs
OLEIVERB_PRIMARY	equ (0)
OLEIVERB_SHOW		equ (-1)
OLEIVERB_OPEN		equ (-2)
OLEIVERB_HIDE		equ (-3)
OLEIVERB_UIACTIVATE	equ (-4)
OLEIVERB_INPLACEACTIVATE equ (-5)
OLEIVERB_DISCARDUNDOSTATE equ (-6)

;; for OleCreateEmbeddingHelper flags; roles in low word; options in high word
EMBDHLP_INPROC_HANDLER	equ 0x0000
EMBDHLP_INPROC_SERVER	equ 0x0001
EMBDHLP_CREATENOW	equ 0x00000000
EMBDHLP_DELAYCREATE	equ 0x00010000

;; extended create function flags
OLECREATE_LEAVERUNNING	equ 0x00000001

;; pull in the MIDL generated header

include oleidl.inc
.xlist

;;***** DV APIs **********************************************************


CreateDataAdviseHolder proto _CType \
	    ppDAHolder: LPDATAADVISEHOLDER

;;***** OLE API Prototypes ***********************************************

;DWORD
OleBuildVersion proto _CType

;; helper functions

ReadClassStg proto _CType \
		  pStg: LPSTORAGE,
		pclsid: ptr CLSID

WriteClassStg proto _CType \
		  pStg: LPSTORAGE,
		rclsid: REFCLSID

ReadClassStm proto _CType \
		  pStm: LPSTREAM,
		pclsid: ptr CLSID

WriteClassStm proto _CType \
		  pStm: LPSTREAM,
		rclsid: REFCLSID

WriteFmtUserTypeStg proto _CType \
		  pstg: LPSTORAGE,
		    cf: CLIPFORMAT,
	  lpszUserType: LPOLESTR

ReadFmtUserTypeStg proto _CType \
		  pstg: LPSTORAGE,
		   pcf: ptr CLIPFORMAT,
	lplpszUserType: LPOLESTR

;; init/term


OleInitialize proto _CType \
	    pvReserved: LPVOID
;void


;; the APIs to query whether (Embedded/Linked) object can be created from data object

OleQueryLinkFromData proto _CType \
	pSrcDataObject: LPDATAOBJECT

OleQueryCreateFromData proto _CType \
	pSrcDataObject: LPDATAOBJECT


;; Object creation APIs


OleCreate proto _CType \
		rclsid: REFCLSID,
		  riid: REFIID,
	     renderopt: DWORD,
	    pFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateEx proto _CType \
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


OleCreateFromData proto _CType \
	   pSrcDataObj: LPDATAOBJECT,
		  riid: REFIID,
	     renderopt: DWORD,
	    pFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateFromDataEx proto _CType \
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


OleCreateLinkFromData proto _CType \
	   pSrcDataObj: LPDATAOBJECT,
		  riid: REFIID,
	     renderopt: DWORD,
	    pFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateLinkFromDataEx proto _CType \
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


OleCreateStaticFromData proto _CType \
	   pSrcDataObj: LPDATAOBJECT,
		   iid: REFIID,
	     renderopt: DWORD,
	    pFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID



OleCreateLink proto _CType \
	    pmkLinkSrc: LPMONIKER,
		  riid: REFIID,
	     renderopt: DWORD,
	   lpFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateLinkEx proto _CType \
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


OleCreateLinkToFile proto _CType \
	  lpszFileName: LPCOLESTR,
		  riid: REFIID,
	     renderopt: DWORD,
	   lpFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateLinkToFileEx proto _CType \
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


OleCreateFromFile proto _CType \
		rclsid: REFCLSID,
	  lpszFileName: LPCOLESTR,
		  riid: REFIID,
	     renderopt: DWORD,
	   lpFormatEtc: LPFORMATETC,
	   pClientSite: LPOLECLIENTSITE,
		  pStg: LPSTORAGE,
		ppvObj: LPVOID


OleCreateFromFileEx proto _CType \
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


OleLoad proto _CType \
		  pStg: LPSTORAGE,
		  riid: REFIID,
	   pClientSite: LPOLECLIENTSITE,
		ppvObj: LPVOID


OleSave proto _CType \
		   pPS: LPPERSISTSTORAGE,
		  pStg: LPSTORAGE,
	   fSameAsLoad: BOOL


OleLoadFromStream proto _CType \
		  pStm: LPSTREAM,
	  iidInterface: REFIID,
		ppvObj: LPVOID

OleSaveToStream proto _CType \
		 pPStm: LPPERSISTSTREAM,
		  pStm: LPSTREAM



OleSetContainedObject proto _CType \
	      pUnknown: LPUNKNOWN,
	    fContained: BOOL

OleNoteObjectVisible proto _CType \
	      pUnknown: LPUNKNOWN,
	      fVisible: BOOL


;; Drag/Drop APIs


RegisterDragDrop proto _CType \
		  hwnd: HWND,
	   pDropTarget: LPDROPTARGET

RevokeDragDrop proto _CType \
		  hwnd: HWND

DoDragDrop proto _CType \
	      pDataObj: LPDATAOBJECT,
	   pDropSource: LPDROPSOURCE,
	   dwOKEffects: DWORD,
	     pdwEffect: LPDWORD

;; Clipboard APIs


OleSetClipboard proto _CType \
	      pDataObj: LPDATAOBJECT

OleGetClipboard proto _CType \
	     ppDataObj: LPDATAOBJECT


OleIsCurrentClipboard proto _CType \
	      pDataObj: LPDATAOBJECT


;; InPlace Editing APIs

;HOLEMENU
OleCreateMenuDescriptor proto _CType \
	 hmenuCombined: HMENU,
	  lpMenuWidths: LPOLEMENUGROUPWIDTHS

OleSetMenuDescriptor proto _CType \
	      holemenu: HOLEMENU,
	     hwndFrame: HWND,
      hwndActiveObject: HWND,
	       lpFrame: LPOLEINPLACEFRAME,
	   lpActiveObj: LPOLEINPLACEACTIVEOBJECT

OleDestroyMenuDescriptor proto _CType \
	      holemenu: HOLEMENU


OleTranslateAccelerator proto _CType \
	       lpFrame: LPOLEINPLACEFRAME,
	   lpFrameInfo: LPOLEINPLACEFRAMEINFO,
		 lpmsg: LPMSG


;; Helper APIs
;HANDLE
OleDuplicateData proto _CType \
		  hSrc: HANDLE,
	      cfFormat: CLIPFORMAT,
	       uiFlags: UINT


OleDraw proto _CType \
	      pUnknown: LPUNKNOWN,
	      dwAspect: DWORD,
	       hdcDraw: HDC,
	    lprcBounds: LPCRECT


OleRun proto _CType \
	      pUnknown: LPUNKNOWN
;BOOL
OleIsRunning proto _CType \
	       pObject: LPOLEOBJECT

OleLockRunning proto _CType \
	      pUnknown: LPUNKNOWN,
		 fLock: BOOL,
     fLastUnlockCloses: BOOL

;void
CreateOleAdviseHolder proto _CType \
	    ppOAHolder: LPOLEADVISEHOLDER

OleCreateDefaultHandler proto _CType \
		 clsid: REFCLSID,
	     pUnkOuter: LPUNKNOWN,
		  riid: REFIID,
	       lplpObj: LPVOID


OleCreateEmbeddingHelper proto _CType \
		 clsid: REFCLSID,
	     pUnkOuter: LPUNKNOWN,
		 flags: DWORD,
		   pCF: LPCLASSFACTORY,
		  riid: REFIID,
	       lplpObj: LPVOID

;BOOL
IsAccelerator proto _CType \
		hAccel: HACCEL,
	 cAccelEntries: SINT,
		 lpMsg: LPMSG,
		lpwCmd: LPWORD
;; Icon extraction Helper APIs

;HGLOBAL
OleGetIconOfFile proto _CType \
	      lpszPath: LPOLESTR,
       fUseFileAsLabel: BOOL

;HGLOBAL
OleGetIconOfClass proto _CType \
		rclsid: REFCLSID,
	     lpszLabel: LPOLESTR,
       fUseTypeAsLabel: BOOL

;HGLOBAL
OleMetafilePictFromIconAndLabel proto _CType \
		 hIcon: HICON,
	     lpszLabel: LPOLESTR,
	lpszSourceFile: LPOLESTR,
	    iIconIndex: UINT



;; Registration Database Helper APIs


OleRegGetUserType proto _CType \
		 clsid: REFCLSID,
	  dwFormOfType: DWORD,
	   pszUserType: LPOLESTR


OleRegGetMiscStatus proto _CType \
		 clsid: REFCLSID,
	      dwAspect: DWORD,
	     pdwStatus: LPDWORD


OleRegEnumFormatEtc proto _CType \
		 clsid: REFCLSID,
	   dwDirection: DWORD,
		ppenum: LPENUMFORMATETC


OleRegEnumVerbs proto _CType \
		 clsid: REFCLSID,
		ppenum: LPENUMOLEVERB

;; OLE 1.0 conversion APIS

;;**** OLE 1.0 OLESTREAM declarations ************************************

LPOLESTREAM	typedef ptr OLESTREAM

OLESTREAMVTBL_PT typedef proto _CType \
			: LPOLESTREAM,
			: PVOID,
			: DWORD
OLESTREAMVTBL_P typedef ptr OLESTREAMVTBL_PT

OLESTREAMVTBL		STRUC
Get			OLESTREAMVTBL_P ?
Put			OLESTREAMVTBL_P ?
OLESTREAMVTBL		ENDS
LPOLESTREAMVTBL		typedef	 ptr OLESTREAMVTBL

OLESTREAM		STRUC
lpstbl			LPOLESTREAMVTBL ?
OLESTREAM		ENDS



OleConvertOLESTREAMToIStorage proto _CType \
	   lpolestream: LPOLESTREAM,
		  pstg: LPSTORAGE,
		   ptd: ptr DVTARGETDEVICE


OleConvertIStorageToOLESTREAM proto _CType \
		  pstg: LPSTORAGE,
	   lpolestream: LPOLESTREAM


;; Storage Utility APIs

GetHGlobalFromILockBytes proto _CType \
		plkbyt: LPLOCKBYTES,
	      phglobal: ptr HGLOBAL

CreateILockBytesOnHGlobal proto _CType \
	       hGlobal: HGLOBAL,
      fDeleteOnRelease: BOOL,
	       pplkbyt: ptr LPLOCKBYTES


GetHGlobalFromStream proto _CType \
		  pstm: LPSTREAM,
	      phglobal: ptr HGLOBAL

CreateStreamOnHGlobal proto _CType \
	       hGlobal: HGLOBAL,
      fDeleteOnRelease: BOOL,
		 ppstm: ptr LPSTREAM


;; ConvertTo APIS


OleDoAutoConvert proto _CType \
		  pStg: LPSTORAGE,
	     pClsidNew: LPCLSID

OleGetAutoConvert proto _CType \
	      clsidOld: REFCLSID,
	     pClsidNew: LPCLSID

OleSetAutoConvert proto _CType \
	      clsidOld: REFCLSID,
	      clsidNew: REFCLSID

GetConvertStg proto _CType \
		  pStg: LPSTORAGE

SetConvertStg proto _CType \
		  pStg: LPSTORAGE,
	      fConvert: BOOL


OleConvertIStorageToOLESTREAMEx proto _CType \
		  pstg: LPSTORAGE,
	      cfFormat: CLIPFORMAT,
		lWidth: LONG,
	       lHeight: LONG,
		dwSize: DWORD,
	       pmedium: LPSTGMEDIUM,
	       polestm: LPOLESTREAM

OleConvertOLESTREAMToIStorageEx proto _CType \
	       polestm: LPOLESTREAM,
		  pstg: LPSTORAGE,
	     pcfFormat: ptr CLIPFORMAT,
	      plwWidth: ptr LONG,
	      plHeight: ptr LONG,
	       pdwSize: LPDWORD,
	       pmedium: LPSTGMEDIUM

.list

endif	   ;; __OLE2_H__

