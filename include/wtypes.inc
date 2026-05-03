ifndef _WTYPES_
define _WTYPES_
ifndef _RPC500_
include rpc500.inc
endif
ifndef __wtypes_h__
define __wtypes_h__

include wtypesbase.inc

ifndef __IWinTypes_INTERFACE_DEFINED__
define __IWinTypes_INTERFACE_DEFINED__

RemHGLOBAL		struct
fNullHGlobal		LONG ?
cbData			ULONG ?
data			byte 1 dup(?)
RemHGLOBAL		ends

RemHMETAFILEPICT	struct
_mm			LONG ?
xExt			LONG ?
yExt			LONG ?
cbData			ULONG ?
data			byte 1 dup(?)
RemHMETAFILEPICT	ends

RemHENHMETAFILE		struct
cbData			ULONG ?
data			byte 1 dup(?)
RemHENHMETAFILE		ends

RemHBITMAP		struct
cbData			ULONG ?
data			byte 1 dup(?)
RemHBITMAP		ends

RemHPALETTE		struct
cbData			ULONG ?
data			byte 1 dup(?)
RemHPALETTE		ends

RemBRUSH		struct
cbData			ULONG ?
data			byte 1 dup(?)
RemBRUSH		ends

ifndef _PALETTEENTRY_DEFINED
define _PALETTEENTRY_DEFINED
PALETTEENTRY		struct
peRed			BYTE ?
peGreen			BYTE ?
peBlue			BYTE ?
peFlags			BYTE ?
PALETTEENTRY		ends
PPALETTEENTRY		typedef ptr PALETTEENTRY
LPPALETTEENTRY		typedef ptr PALETTEENTRY
endif

ifndef _LOGPALETTE_DEFINED
define _LOGPALETTE_DEFINED
LOGPALETTE		struct
palVersion		WORD ?
palNumEntries		WORD ?
palPalEntry		PALETTEENTRY 1 dup(<>)
LOGPALETTE		ends
PLOGPALETTE		typedef ptr LOGPALETTE
LPLOGPALETTE		typedef ptr LOGPALETTE
endif

ifndef _WINDEF_
LPCRECTL		typedef ptr RECTL
RECT			struct
left			LONG ?
top			LONG ?
right			LONG ?
bottom			LONG ?
RECT			ends
PRECT			typedef ptr RECT
LPRECT			typedef ptr RECT
LPCRECT			typedef ptr RECT
endif

ifndef _ROTFLAGS_DEFINED
define _ROTFLAGS_DEFINED
define ROTFLAGS_REGISTRATIONKEEPSALIVE 0x1
define ROTFLAGS_ALLOWANYCLIENT 0x2
endif

ifndef _ROT_COMPARE_MAX_DEFINED
define _ROT_COMPARE_MAX_DEFINED
define ROT_COMPARE_MAX 2048
endif

.enum DVASPECT {
    DVASPECT_CONTENT	= 1,
    DVASPECT_THUMBNAIL	= 2,
    DVASPECT_ICON	= 4,
    DVASPECT_DOCPRINT	= 8
    }

.enum STGC {
    STGC_DEFAULT,
    STGC_OVERWRITE,
    STGC_ONLYIFCURRENT,
    STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE = 4,
    STGC_CONSOLIDATE	= 8
    }

.enum STGMOVE {
    STGMOVE_MOVE,
    STGMOVE_COPY,
    STGMOVE_SHALLOWCOPY
    }

.enum STATFLAG {
    STATFLAG_DEFAULT,
    STATFLAG_NONAME,
    STATFLAG_NOOPEN
    }

HCONTEXT	typedef ptr

ifndef _LCID_DEFINED
define _LCID_DEFINED
LCID		typedef DWORD
endif

ifndef _LANGID_DEFINED
define _LANGID_DEFINED
LANGID		typedef WORD
endif

define WDT_INPROC_CALL	0x48746457
define WDT_REMOTE_CALL	0x52746457
define WDT_INPROC64_CALL 0x50746457

userCLIPFORMAT		struct
fContext		LONG ?
union u
 dwValue		dd ?
 pwszName		LPWSTR ?
ends
userCLIPFORMAT		ends
wireCLIPFORMAT		typedef ptr userCLIPFORMAT

CLIPFORMAT		typedef WORD

GDI_NONREMOTE		struct
fContext		LONG ?
union u
 hInproc		LONG ?
 hRemote		UP_DWORD_BLOB ?
ends
GDI_NONREMOTE		ends

userHGLOBAL		struct
fContext		LONG ?
union u
 hInproc		LONG ?
 hRemote		UP_FLAGGED_BYTE_BLOB ?
 hGlobal		LONG ?
ends
userHGLOBAL		ends

wireHGLOBAL		typedef ptr userHGLOBAL

userHMETAFILE		struct
fContext		LONG ?
union u
 hInproc		LONG ?
 hRemote		UP_BYTE_BLOB ?
 hInproc64		sqword ?
ends
userHMETAFILE		ends

remoteMETAFILEPICT	struct
mm			LONG ?
xExt			LONG ?
yExt			LONG ?
hMF			ptr userHMETAFILE ?
remoteMETAFILEPICT	ends
PremoteMETAFILEPICT	typedef ptr remoteMETAFILEPICT

userHMETAFILEPICT	struct
fContext		LONG ?
union u
 hInproc		LONG ?
 hRemote		PremoteMETAFILEPICT ?
 hInproc64		sqword ?
ends
userHMETAFILEPICT	ends

userHENHMETAFILE	struct
fContext		LONG ?
union u
 hInproc		LONG ?
 hRemote		UP_BYTE_BLOB ?
 hInproc64		sqword ?
ends
userHENHMETAFILE	ends

userBITMAP		struct
bmType			LONG ?
bmWidth			LONG ?
bmHeight		LONG ?
bmWidthBytes		LONG ?
bmPlanes		dw ?
bmBitsPixel		dw ?
cbSize			dd ?
pBuffer			byte 1 dup(?)
userBITMAP		ends

userHBITMAP		struct
fContext		LONG ?
union u
 hInproc		LONG ?
 hRemote		ptr userBITMAP ?
 hInproc64		sqword ?
ends
userHBITMAP		ends

userHPALETTE		struct
fContext		LONG ?
union u
 hInproc		LONG ?
 hRemote		LPLOGPALETTE ?
 hInproc64		sqword ?
ends
userHPALETTE		ends

RemotableHandle		struct
fContext		LONG ?
union u
 hInproc		LONG ?
 hRemote		LONG ?
ends
RemotableHandle		ends

wireHWND		typedef ptr RemotableHandle
wireHMENU		typedef ptr RemotableHandle
wireHACCEL		typedef ptr RemotableHandle
wireHBRUSH		typedef ptr RemotableHandle
wireHFONT		typedef ptr RemotableHandle
wireHDC			typedef ptr RemotableHandle
wireHICON		typedef ptr RemotableHandle
wireHRGN		typedef ptr RemotableHandle
wireHMONITOR		typedef ptr RemotableHandle

ifndef _TEXTMETRIC_DEFINED
define _TEXTMETRIC_DEFINED
TEXTMETRICW		struct
tmHeight		LONG ?
tmAscent		LONG ?
tmDescent		LONG ?
tmInternalLeading	LONG ?
tmExternalLeading	LONG ?
tmAveCharWidth		LONG ?
tmMaxCharWidth		LONG ?
tmWeight		LONG ?
tmOverhang		LONG ?
tmDigitizedAspectX	LONG ?
tmDigitizedAspectY	LONG ?
tmFirstChar		dw ?
tmLastChar		dw ?
tmDefaultChar		dw ?
tmBreakChar		dw ?
tmItalic		db ?
tmUnderlined		db ?
tmStruckOut		db ?
tmPitchAndFamily	db ?
tmCharSet		db ?
TEXTMETRICW		ends
PTEXTMETRICW		typedef ptr TEXTMETRICW
LPTEXTMETRICW		typedef ptr TEXTMETRICW
endif

ifndef _WIN32
ifndef WINAPI
MSG			struct
hwnd			HWND ?
message			UINT ?
wParam			WPARAM ?
lParam			LPARAM ?
time			DWORD ?
pt			POINT <>
MSG			ends
PMSG			typedef ptr MSG
NPMSG			typedef ptr MSG
LPMSG			typedef ptr MSG
endif
endif

wireHBITMAP		typedef ptr userHBITMAP
wireHPALETTE		typedef ptr userHPALETTE
wireHENHMETAFILE	typedef ptr userHENHMETAFILE
wireHMETAFILE		typedef ptr userHMETAFILE
wireHMETAFILEPICT	typedef ptr userHMETAFILEPICT

HMETAFILEPICT		typedef ptr

endif

DATE			typedef real8
LPDATE			typedef ptr real8

ifndef _CY_DEFINED
define _CY_DEFINED
CY			union
struct
 Lo			DWORD ?
 Hi			SDWORD ?
ends
int64			SQWORD ?
CY			ends
endif
LPCY			typedef ptr CY

DECIMAL			struct
wReserved		dw ?
union
 struct
  scale			db ?
  sign			db ?
 ends
 signscale		dw ?
ends
Hi32			dd ?
union
 struct
  Lo32			dd ?
  Mid32			dd ?
 ends
 Lo64			dq ?
ends
DECIMAL			ends
define DECIMAL_NEG (0x80)

LPDECIMAL		typedef ptr DECIMAL
wireBSTR		typedef ptr FLAGGED_WORD_BLOB
BSTR			typedef ptr OLECHAR
LPBSTR			typedef ptr BSTR
VARIANT_BOOL		typedef sword

ifndef _BSTRBLOB_DEFINED
define _BSTRBLOB_DEFINED
BSTRBLOB		struct
cbSize			ULONG ?
pData			LPBYTE ?
BSTRBLOB		ends
LPBSTRBLOB		typedef ptr BSTRBLOB
endif

define VARIANT_TRUE	(-1)
define VARIANT_FALSE	(0)

CLIPDATA		struct
cbSize			ULONG ?
ulClipFmt		LONG ?
pClipData		LPBYTE ?
CLIPDATA		ends
LPCLIPDATA		typedef ptr CLIPDATA

VARTYPE			typedef word

.enum VARENUM {
    VT_EMPTY,
    VT_NULL,
    VT_I2,
    VT_I4,
    VT_R4,
    VT_R8,
    VT_CY,
    VT_DATE,
    VT_BSTR,
    VT_DISPATCH,
    VT_ERROR,
    VT_BOOL		= 11,
    VT_VARIANT		= 12,
    VT_UNKNOWN		= 13,
    VT_DECIMAL		= 14,
    VT_I1		= 16,
    VT_UI1		= 17,
    VT_UI2		= 18,
    VT_UI4		= 19,
    VT_I8		= 20,
    VT_UI8		= 21,
    VT_INT		= 22,
    VT_UINT		= 23,
    VT_VOID		= 24,
    VT_HRESULT		= 25,
    VT_PTR		= 26,
    VT_SAFEARRAY	= 27,
    VT_CARRAY		= 28,
    VT_USERDEFINED	= 29,
    VT_LPSTR		= 30,
    VT_LPWSTR		= 31,
    VT_RECORD		= 36,
    VT_INT_PTR		= 37,
    VT_UINT_PTR		= 38,
    VT_FILETIME		= 64,
    VT_BLOB		= 65,
    VT_STREAM		= 66,
    VT_STORAGE		= 67,
    VT_STREAMED_OBJECT	= 68,
    VT_STORED_OBJECT	= 69,
    VT_BLOB_OBJECT	= 70,
    VT_CF		= 71,
    VT_CLSID		= 72,
    VT_VERSIONED_STREAM = 73,
    VT_BSTR_BLOB	= 0xfff,
    VT_VECTOR		= 0x1000,
    VT_ARRAY		= 0x2000,
    VT_BYREF		= 0x4000,
    VT_RESERVED		= 0x8000,
    VT_ILLEGAL		= 0xffff,
    VT_ILLEGALMASKED	= 0xfff,
    VT_TYPEMASK		= 0xfff
    }
PROPID			typedef DWORD

ifndef PROPERTYKEY_DEFINED
define PROPERTYKEY_DEFINED
PROPERTYKEY		struct
fmtid			GUID <>
pid			DWORD ?
PROPERTYKEY		ends
endif

CSPLATFORM		struct
dwPlatformId		DWORD ?
dwVersionHi		DWORD ?
dwVersionLo		DWORD ?
dwProcessorArch		DWORD ?
CSPLATFORM		ends

QUERYCONTEXT		struct
dwContext		DWORD ?
Platform		CSPLATFORM <>
Locale			LCID ?
dwVersionHi		DWORD ?
dwVersionLo		DWORD ?
QUERYCONTEXT		ends

.enum TYSPEC {
    TYSPEC_CLSID,
    TYSPEC_FILEEXT,
    TYSPEC_MIMETYPE,
    TYSPEC_FILENAME,
    TYSPEC_PROGID,
    TYSPEC_PACKAGENAME,
    TYSPEC_OBJECTID
    }

uCLSSPEC		struct
tyspec			DWORD ?
union tagged_union
 pFileExt		LPOLESTR ?
 pMimeType		LPOLESTR ?
 pProgId		LPOLESTR ?
 pFileName		LPOLESTR ?
 struct ByName
  pPackageName		LPOLESTR ?
  PolicyId		GUID <>
 ends
 struct ByObjectId
  ObjectId		GUID <>
  PolicyId		GUID <>
 ends
ends
uCLSSPEC		ends

endif

endif
