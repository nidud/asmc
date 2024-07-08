ifndef __WTYPES_INC
define __WTYPES_INC

ifndef __REQUIRED_RPCNDR_H_VERSION__
define __REQUIRED_RPCNDR_H_VERSION__ 500
endif

ifndef __REQUIRED_RPCSAL_H_VERSION__
define __REQUIRED_RPCSAL_H_VERSION__ 100
endif

include rpc.inc
include rpcndr.inc

ifndef __RPCNDR_H_VERSION__
.err <this stub requires an updated version of rpcndr.h>
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

if 0
REFFMTID		typedef ptr FMTID
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
    STGC_DEFAULT	= 0,
    STGC_OVERWRITE	= 1,
    STGC_ONLYIFCURRENT	= 2,
    STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE = 4,
    STGC_CONSOLIDATE	= 8
    }

.enum STGMOVE {
    STGMOVE_MOVE	= 0,
    STGMOVE_COPY	= 1,
    STGMOVE_SHALLOWCOPY = 2
    }

.enum STATFLAG {
    STATFLAG_DEFAULT	= 0,
    STATFLAG_NONAME	= 1,
    STATFLAG_NOOPEN	= 2
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

define	WDT_INPROC_CALL ( 0x48746457 )
define	WDT_REMOTE_CALL ( 0x52746457 )
define	WDT_INPROC64_CALL ( 0x50746457 )

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
bmPlanes		WORD ?
bmBitsPixel		WORD ?
cbSize			ULONG ?
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

if 0
HWND			typedef ptr
HMENU			typedef ptr
HACCEL			typedef ptr
HBRUSH			typedef ptr
HFONT			typedef ptr
HDC			typedef ptr
HICON			typedef ptr
HRGN			typedef ptr
HMONITOR		typedef ptr
ifndef _HCURSOR_DEFINED
define _HCURSOR_DEFINED
HCURSOR			typedef HICON
endif
endif

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
tmFirstChar		WCHAR ?
tmLastChar		WCHAR ?
tmDefaultChar		WCHAR ?
tmBreakChar		WCHAR ?
tmItalic		BYTE ?
tmUnderlined		BYTE ?
tmStruckOut		BYTE ?
tmPitchAndFamily	BYTE ?
tmCharSet		BYTE ?
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

if 0
HGLOBAL			typedef ptr
HLOCAL			typedef HGLOBAL
HBITMAP			typedef ptr
HPALETTE		typedef ptr
HENHMETAFILE		typedef ptr
HMETAFILE		typedef ptr
endif

HMETAFILEPICT		typedef ptr

endif ; __IWinTypes_INTERFACE_DEFINED__

DATE			typedef real8
LPDATE			typedef ptr real8

ifndef _tagCY_DEFINED
define _tagCY_DEFINED
define _CY_DEFINED

if 0
tagCY			struct
int64			SQWORD ?
tagCY			ends
CY			typedef tagCY
else
tagCY			union
struct
 Lo			DWORD ?
 Hi			SDWORD ?
ends
int64			SQWORD ?
tagCY			ends
CY			typedef tagCY
endif
endif
LPCY			typedef ptr CY

if 0
tagDEC			struct
wReserved		WORD ?
scale			BYTE ?
sign			BYTE ?
Hi32			DWORD ?
Lo64			QWORD ?
tagDEC			ends
DECIMAL			typedef tagDEC
else
tagDEC			struct
wReserved		WORD ?
union
 struct
  scale			BYTE ?
  sign			BYTE ?
 ends
 signscale		WORD ?
ends
Hi32			DWORD ?
union
 struct
  Lo32			DWORD ?
  Mid32			DWORD ?
 ends
 Lo64			QWORD ?
ends
tagDEC			ends
DECIMAL			typedef tagDEC
define DECIMAL_NEG (0x80)
endif

LPDECIMAL		typedef ptr DECIMAL
wireBSTR		typedef ptr FLAGGED_WORD_BLOB
BSTR			typedef ptr OLECHAR
LPBSTR			typedef ptr BSTR
VARIANT_BOOL		typedef sword

ifndef _tagBSTRBLOB_DEFINED
define _tagBSTRBLOB_DEFINED
BSTRBLOB		struct
cbSize			ULONG ?
pData			LPBYTE ?
BSTRBLOB		ends
LPBSTRBLOB		typedef ptr BSTRBLOB
endif

define VARIANT_TRUE	(-1)
define VARIANT_FALSE	(0)

tagCLIPDATA		struct
cbSize			ULONG ?
ulClipFmt		LONG ?
pClipData		LPBYTE ?
tagCLIPDATA		ends
CLIPDATA		typedef tagCLIPDATA
LPCLIPDATA		typedef ptr CLIPDATA

VARTYPE			typedef word

.enum VARENUM {
    VT_EMPTY		= 0,
    VT_NULL		= 1,
    VT_I2		= 2,
    VT_I4		= 3,
    VT_R4		= 4,
    VT_R8		= 5,
    VT_CY		= 6,
    VT_DATE		= 7,
    VT_BSTR		= 8,
    VT_DISPATCH		= 9,
    VT_ERROR		= 10,
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
    TYSPEC_CLSID	= 0,
    TYSPEC_FILEEXT	= ( TYSPEC_CLSID + 1 ) ,
    TYSPEC_MIMETYPE	= ( TYSPEC_FILEEXT + 1 ) ,
    TYSPEC_FILENAME	= ( TYSPEC_MIMETYPE + 1 ) ,
    TYSPEC_PROGID	= ( TYSPEC_FILENAME + 1 ) ,
    TYSPEC_PACKAGENAME	= ( TYSPEC_PROGID + 1 ) ,
    TYSPEC_OBJECTID	= ( TYSPEC_PACKAGENAME + 1 )
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
