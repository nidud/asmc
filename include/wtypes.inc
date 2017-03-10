ifndef __wtypes_h__
.xlist
__wtypes_h__ equ 1

ifndef __REQUIRED_RPCNDR_H_VERSION__
__REQUIRED_RPCNDR_H_VERSION__ equ 440
endif

include rpc.inc
include rpcndr.inc
.xlist
;; Forward Declarations

;PVOID
MIDL_user_allocate proto _CType :size_t
;void
MIDL_user_free proto _CType :PVOID

externdef __MIDL_itf_wtypes_0000_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_wtypes_0000_v0_0_s_ifspec:RPC_IF_HANDLE

ifndef __IWinTypes_INTERFACE_DEFINED__
__IWinTypes_INTERFACE_DEFINED__ equ 1

RemHGLOBAL		STRUC
fNullHGlobal		LONG ?
cbData			ULONG ?
data			db ?
RemHGLOBAL		ENDS

RemHMETAFILEPICT	STRUC
mm			LONG ?
xExt			LONG ?
yExt			LONG ?
cbData			ULONG ?
data			db ?
RemHMETAFILEPICT	ENDS

RemHENHMETAFILE		STRUC
cbData			ULONG ?
data			db ?
RemHENHMETAFILE		ENDS

RemHBITMAP		STRUC
cbData			ULONG ?
data			db ?
RemHBITMAP		ENDS

RemHPALETTE		STRUC
cbData			ULONG ?
data			db ?
RemHPALETTE		ENDS

RemHBRUSH		STRUC
cbData			ULONG ?
data			db ?
RemHBRUSH		ENDS

if defined(_WIN32) AND NOT defined(OLE2ANSI)
OLECHAR			typedef WCHAR
LPOLESTR		typedef ptr OLECHAR
LPCOLESTR		typedef ptr OLECHAR
OLESTR macro str
	exitm<str>
	endm

else

OLECHAR			typedef SBYTE
LPOLESTR		typedef LPSTR
LPCOLESTR		typedef LPCSTR
OLESTR macro str
	exitm<str>
	endm
endif
ifndef _WINDEF_
LPCRECTL		typedef ptr RECTL
;;typedef void *PVOID;
;;typedef void *LPVOID;
;;typedef float FLOAT;

RECT			STRUC
left			LONG ?
top			LONG ?
right			LONG ?
bottom			LONG ?
RECT			ENDS
PRECT			typedef ptr RECT
LPRECT			typedef ptr RECT
LPCRECT			typedef ptr RECT

endif	;;_WINDEF_
UCHAR			typedef BYTE
USHORT			typedef WORD
DOUBLE			typedef REAL8

ifndef _DWORDLONG_
DWORDLONG		typedef MIDL_uhyper
PDWORDLONG		typedef ptr DWORDLONG

endif ;; NOT _DWORDLONG_

ifndef _ULONGLONG_
LONGLONG		typedef hyper
ULONGLONG		typedef MIDL_uhyper
PLONGLONG		typedef ptr LONGLONG
PULONGLONG		typedef ptr ULONGLONG

endif ;; _ULONGLONG_

ifndef _WINBASE_
ifndef _FILETIME_
_FILETIME_		equ 1
FILETIME		STRUC
dwLowDateTime		dd ?
dwHighDateTime		dd ?
FILETIME		ENDS
PFILETIME		typedef ptr FILETIME
LPFILETIME		typedef ptr FILETIME
endif ;; NOT _FILETIME

ifndef _SYSTEMTIME_
_SYSTEMTIME_		equ 1
SYSTEMTIME		STRUC
wYear			dw ?
wMonth			dw ?
wDayOfWeek		dw ?
wDay			dw ?
wHour			dw ?
wMinute			dw ?
wSecond			dw ?
wMilliseconds		dw ?
SYSTEMTIME		ENDS
PSYSTEMTIME		typedef ptr SYSTEMTIME
LPSYSTEMTIME		typedef ptr SYSTEMTIME
endif ;; NOT _SYSTEMTIME

ifndef _SECURITY_ATTRIBUTES_
_SECURITY_ATTRIBUTES_	equ 1
SECURITY_ATTRIBUTES	STRUC
nLength			dd ?
lpSecurityDescriptor	LPVOID ?
bInheritHandle		BOOL ?
SECURITY_ATTRIBUTES	ENDS
PSECURITY_ATTRIBUTES	typedef ptr SECURITY_ATTRIBUTES
LPSECURITY_ATTRIBUTES	typedef ptr SECURITY_ATTRIBUTES
endif ;; NOT _SECURITY_ATTRIBUTES_

ifndef SECURITY_DESCRIPTOR_REVISION
SECURITY_DESCRIPTOR_CONTROL	typedef USHORT
PSECURITY_DESCRIPTOR_CONTROL	typedef ptr USHORT
PSID				typedef PVOID

ACL			STRUC
AclRevision		UCHAR ?
Sbz1			UCHAR ?
AclSize			USHORT ?
AceCount		USHORT ?
Sbz2			USHORT ?
ACL			ENDS
PACL			typedef ptr ACL

SECURITY_DESCRIPTOR	STRUC
Revision		UCHAR ?
Sbz1			UCHAR ?
Control			SECURITY_DESCRIPTOR_CONTROL ?
Owner			PSID ?
Group			PSID ?
Sacl			PACL ?
Dacl			PACL ?
SECURITY_DESCRIPTOR	ENDS
PISECURITY_DESCRIPTOR	typedef ptr SECURITY_DESCRIPTOR

endif ;; NOT SECURITY_DESCRIPTOR_REVISION

endif ;;_WINBASE_
COAUTHIDENTITY		STRUC
User			LPWORD ?
UserLength		ULONG ?
Domain			LPWORD ?
DomainLength		ULONG ?
Password		LPWORD ?
PasswordLength		ULONG ?
Flags			ULONG ?
COAUTHIDENTITY		ENDS
PCOAUTHIDENTITY		typedef ptr COAUTHIDENTITY

COAUTHINFO		STRUC
dwAuthnSvc		dd ?
dwAuthzSvc		dd ?
pwszServerPrincName	LPWSTR ?
dwAuthnLevel		dd ?
dwImpersonationLevel	dd ?
pAuthIdentityData	PCOAUTHIDENTITY ?
dwCapabilities		dd ?
COAUTHINFO		ENDS

SCODE			typedef LONG

ifndef _HRESULT_DEFINED
_HRESULT_DEFINED equ 1
HRESULT			typedef LONG
endif ;; NOT _HRESULT_DEFINED

PSCODE			typedef ptr SCODE

ifndef GUID_DEFINED
GUID_DEFINED		equ 1
GUID			STRUC
Data1			dd ?
Data2			dw ?
Data3			dw ?
Data4			db 8 dup(?)
GUID			ENDS
endif ;; NOT GUID_DEFINED

if NOT defined( __LPGUID_DEFINED__ )
__LPGUID_DEFINED__	equ 1
LPGUID			typedef ptr GUID
endif ;; NOT __LPGUID_DEFINED__

ifndef __OBJECTID_DEFINED
__OBJECTID_DEFINED	equ 1
_OBJECTID_DEFINED	equ 1
OBJECTID		STRUC
Lineage			GUID <>
Uniquifier		dd ?
OBJECTID		ENDS
endif ;; NOT _OBJECTID_DEFINED

ifndef __IID_DEFINED__
__IID_DEFINED__		equ 1
IID			typedef GUID
LPIID			typedef ptr IID
IID_NULL		equ <GUID_NULL>

IsEqualIID macro riid1, riid2
	exitm<IsEqualGUID(riid1, riid2)>
	endm
CLSID			typedef GUID
LPCLSID			typedef ptr CLSID
CLSID_NULL		equ <GUID_NULL>
IsEqualCLSID macro rclsid1, rclsid2
	exitm<IsEqualGUID(rclsid1, rclsid2)>
	endm
FMTID			typedef GUID
LPFMTID			typedef ptr FMTID
FMTID_NULL		equ <GUID_NULL>
IsEqualFMTID macro rfmtid1, rfmtid2
	exitm<IsEqualGUID(rfmtid1, rfmtid2)>
	endm

REFGUID			typedef ptr GUID
REFIID			typedef ptr IID
REFCLSID		typedef ptr CLSID
REFFMTID		typedef ptr FMTID
endif ;; NOT __IID_DEFINED__

MEMCTX			typedef SDWORD
MEMCTX_TASK		equ 1
MEMCTX_SHARED		equ 2
MEMCTX_MACSYSTEM	equ 3
MEMCTX_UNKNOWN		equ -1
MEMCTX_SAME		equ -2

ifndef _ROTFLAGS_DEFINED
_ROTFLAGS_DEFINED	equ 1
ROTFLAGS_REGISTRATIONKEEPSALIVE equ 0x1
ROTFLAGS_ALLOWANYCLIENT equ 0x2
endif ;; NOT _ROTFLAGS_DEFINED

ifndef _ROT_COMPARE_MAX_DEFINED
_ROT_COMPARE_MAX_DEFINED equ 1
ROT_COMPARE_MAX		equ 2048
endif ;; NOT _ROT_COMPARE_MAX_DEFINED

CLSCTX			typedef SDWORD

CLSCTX_INPROC_SERVER	equ 0x1
CLSCTX_INPROC_HANDLER	equ 0x2
CLSCTX_LOCAL_SERVER	equ 0x4
CLSCTX_INPROC_SERVER16	equ 0x8
CLSCTX_REMOTE_SERVER	equ 0x10
CLSCTX_INPROC_HANDLER16 equ 0x20
CLSCTX_INPROC_SERVERX86 equ 0x40
CLSCTX_INPROC_HANDLERX86 equ 0x80
CLSCTX_ESERVER_HANDLER	equ 0x100

MSHLFLAGS		typedef SDWORD
MSHLFLAGS_NORMAL	equ 0
MSHLFLAGS_TABLESTRONG	equ 1
MSHLFLAGS_TABLEWEAK	equ 2
MSHLFLAGS_NOPING	equ 4

MSHCTX			typedef SDWORD
MSHCTX_LOCAL		equ 0
MSHCTX_NOSHAREDMEM	equ 1
MSHCTX_DIFFERENTMACHINE equ 2
MSHCTX_INPROC		equ 3

DVASPECT		typedef SDWORD
DVASPECT_CONTENT	equ 1
DVASPECT_THUMBNAIL	equ 2
DVASPECT_ICON		equ 4
DVASPECT_DOCPRINT	equ 8

STGC			typedef SDWORD
STGC_DEFAULT		equ 0
STGC_OVERWRITE		equ 1
STGC_ONLYIFCURRENT	equ 2
STGC_DANGEROUSLYCOMMITMERELYTODISKCACHE equ 4
STGC_CONSOLIDATE	equ 8

STGMOVE			typedef SDWORD
STGMOVE_MOVE		equ 0
STGMOVE_COPY		equ 1
STGMOVE_SHALLOWCOPY	equ 2

STATFLAG		typedef SDWORD
STATFLAG_DEFAULT	equ 0
STATFLAG_NONAME		equ 1
STATFLAG_NOOPEN		equ 2

HCONTEXT		typedef PVOID

ifndef _LCID_DEFINED
_LCID_DEFINED equ 1
LCID			typedef DWORD

endif ;; NOT _LCID_DEFINED
BYTE_BLOB		STRUC
clSize			dd ?
abData			db ?
BYTE_BLOB		ENDS

UP_BYTE_BLOB		typedef ptr BYTE_BLOB

WORD_BLOB		STRUC
clSize			dd ?
asData			db ?
WORD_BLOB		ENDS

UP_WORD_BLOB		typedef ptr WORD_BLOB

DWORD_BLOB		STRUC
clSize			dd ?
alData			db ?
DWORD_BLOB		ENDS

UP_DWORD_BLOB		typedef ptr DWORD_BLOB

FLAGGED_BYTE_BLOB	STRUC
fFlags			dd ?
clSize			dd ?
abData			db ?
FLAGGED_BYTE_BLOB	ENDS

UP_FLAGGED_BYTE_BLOB	typedef ptr FLAGGED_BYTE_BLOB

FLAGGED_WORD_BLOB	STRUC
fFlags			dd ?
clSize			dd ?
asData			dw ?
FLAGGED_WORD_BLOB	ENDS

UP_FLAGGED_WORD_BLOB	typedef ptr FLAGGED_WORD_BLOB

BYTE_SIZEDARR		STRUC
clSize			dd ?
pData			LPBYTE ?
BYTE_SIZEDARR		ENDS

WORD_SIZEDARR		STRUC
clSize			dd ?
pData			LPWORD ?
WORD_SIZEDARR		ENDS

DWORD_SIZEDARR		STRUC
clSize			dd ?
pData			LPDWORD ?
DWORD_SIZEDARR		ENDS

HYPER_SIZEDARR		STRUC
clSize			dd ?
pData			PVOID ?;* hyper
HYPER_SIZEDARR		ENDS

WDT_INPROC_CALL		equ 0x48746457
WDT_REMOTE_CALL		equ 0x52746457

userCLIPFORMAT		STRUC
fContext		LONG ?
UNION u
 dwValue		dd ?
 pwszName		LPWORD ?
ENDS
userCLIPFORMAT		ENDS

wireCLIPFORMAT		typedef ptr userCLIPFORMAT
CLIPFORMAT		typedef WORD

GDI_NONREMOTE		STRUC
fContext		LONG ?
UNION u
 hInproc		LONG ?
 hRemote		LPDWORD ?
ENDS
GDI_NONREMOTE		ENDS

userHGLOBAL		STRUC
fContext		LONG ?
UNION u
 hInproc		LONG ?
 hRemote		UP_FLAGGED_BYTE_BLOB ?
 hGlobal		LONG ?
ENDS
userHGLOBAL		ENDS

wireHGLOBAL		typedef ptr userHGLOBAL

userHMETAFILE		STRUC
fContext		LONG ?
UNION u
 hInproc		LONG ?
 hRemote		LPSTR ?
 hGlobal		LONG ?
ENDS
userHMETAFILE		ENDS
PuserHMETAFILE		typedef ptr userHMETAFILE

remoteMETAFILEPICT	STRUC
mm			LONG ?
xExt			LONG ?
yExt			LONG ?
hMF			PuserHMETAFILE ?
remoteMETAFILEPICT	ENDS
PremoteMETAFILEPICT	typedef ptr remoteMETAFILEPICT

userHMETAFILEPICT	STRUC
fContext		LONG ?
UNION u
 hInproc		LONG ?
 hRemote		PremoteMETAFILEPICT ?
 hGlobal		LONG ?
ENDS
userHMETAFILEPICT	ENDS

userHENHMETAFILE	STRUC
fContext		LONG ?
UNION u
 hInproc		LONG ?
 hRemote		LPSTR ?
 hGlobal		LONG ?
ENDS
userHENHMETAFILE	ENDS

userBITMAP		STRUC
bmType			LONG ?
bmWidth			LONG ?
bmHeight		LONG ?
bmWidthBytes		LONG ?
bmPlanes		dw ?
bmBitsPixel		dw ?
cbSize			ULONG ?
pBuffer			db ?
userBITMAP		ENDS
PuserBITMAP		typedef ptr PuserBITMAP

userHBITMAP		STRUC
fContext		LONG ?
UNION u
hInproc			LONG ?
hRemote			PuserBITMAP ?
hGlobal			LONG ?
ENDS
userHBITMAP		ENDS

rpcLOGPALETTE		STRUC
palVersion		dw ?
palNumEntries		dw ?
palPalEntry		PALETTEENTRY <>
rpcLOGPALETTE		ENDS
PrpcLOGPALETTE		typedef ptr rpcLOGPALETTE

userHPALETTE		STRUC
fContext		LONG ?
UNION u
hInproc			LONG ?
hRemote			PrpcLOGPALETTE ?
ENDS
userHPALETTE		ENDS

RemotableHandle		STRUC
fContext		LONG ?
UNION u
 hInproc		LONG ?
 hRemote		LONG ?
ENDS
RemotableHandle		ENDS

wireHWND		typedef ptr RemotableHandle
wireHMENU		typedef ptr RemotableHandle
wireHACCEL		typedef ptr RemotableHandle
wireHBRUSH		typedef ptr RemotableHandle
wireHFONT		typedef ptr RemotableHandle
wireHDC			typedef ptr RemotableHandle
wireHICON		typedef ptr RemotableHandle

ifndef _WIN32		 ;; The following code is for Win16 only
ifndef WINAPI		;; If not included with 3.1 headers...
MSG			STRUC
hwnd			HWND ?
message			UINT ?
wParam			WPARAM ?
lParam			LPARAM ?
time			dd ?
pt			POINT <>
MSG			ENDS
PMSG			typedef ptr MSG
NPMSG			typedef ptr MSG
LPMSG			typedef ptr MSG

endif ;; _WIN32
endif ;; WINAPI

wireHBITMAP		typedef ptr userHBITMAP
wireHPALETTE		typedef ptr userHPALETTE
wireHENHMETAFILE	typedef ptr userHENHMETAFILE
wireHMETAFILE		typedef ptr userHMETAFILE
wireHMETAFILEPICT	typedef ptr userHMETAFILEPICT
HMETAFILEPICT		typedef PVOID


externdef IWinTypes_v0_1_c_ifspec:RPC_IF_HANDLE
externdef IWinTypes_v0_1_s_ifspec:RPC_IF_HANDLE
endif ;; __IWinTypes_INTERFACE_DEFINED__

if ( _MSC_VER GE 800 )
;#pragma warning(disable:4201)
endif
DATE			typedef REAL8

ifndef _tagCY_DEFINED
_tagCY_DEFINED		equ 1
_CY_DEFINED		equ 1
if 0
;; the following isn't the real definition of CY, but it is
;; what RPC knows how to remote
CY			STRUC
int64			LONGLONG <>
CY			ENDS

else ;; 0
;; real definition that makes the C++ compiler happy
CY			UNION
STRUC
	Lo		dd ?
	Hi		LONG ?
ENDS
int64			dq ?
CY			ENDS
endif ;; 0
endif ;; _tagCY_DEFINED
LPCY			typedef ptr CY

if 0 ;; _tagDEC_DEFINED
;; The following isn't the real definition of Decimal type,
;; but it is what RPC knows how to remote
DECIMAL			STRUC
wReserved		dw ?
scale			db ?
sign			db ?
Hi32			dd ?
Lo64			dq ?
DECIMAL			ENDS

else ;; _tagDEC_DEFINED
;; real definition that makes the C++ compiler happy

DECIMAL			STRUC
wReserved		dw ?
UNION
 STRUC
  scale			db ?
  sign			db ?
 ENDS
 signscale		dw ?
ENDS
Hi32			dd ?
UNION
 STRUC
  Lo32			dd ?
  Mid32			dd ?
 ENDS
 Lo64			dq ?
ENDS
DECIMAL			ENDS
DECIMAL_NEG		equ 0x80
DECIMAL_SETZERO macro val
	mov val.Lo64,0
	mov val.Hi32,0
	mov val.signscale,0
	endm
endif ;; _tagDEC_DEFINED
LPDECIMAL		typedef ptr DECIMAL

if ( _MSC_VER GE 800 )
;#pragma warning(default:4201)
endif
wireBSTR		typedef ptr FLAGGED_WORD_BLOB
BSTR			typedef ptr OLECHAR
LPBSTR			typedef ptr BSTR
;; 0 == FALSE, -1 == TRUE
VARIANT_BOOL		typedef sword

if NOT __STDC__ AND (_MSC_VER LE 1000)
;; For backward compatibility
_VARIANT_BOOL		typedef VARIANT_BOOL

else
;; ANSI C/C++ reserve bool as keyword
_VARIANT_BOOL		equ <>;/##/
endif
BOOLEAN			typedef boolean

;; The BSTRBLOB structure is used by some implementations
;; of the IPropertyStorage interface when marshaling BSTRs
;; on systems which don't support BSTR marshaling.
ifndef _tagBSTRBLOB_DEFINED
_tagBSTRBLOB_DEFINED	equ 1
BSTRBLOB		STRUC
cbSize			ULONG ?
pData			LPBYTE ?
BSTRBLOB		ENDS
LPBSTRBLOB		typedef ptr BSTRBLOB
endif

VARIANT_TRUE		equ 0xffff
VARIANT_FALSE		equ 0

ifndef _tagBLOB_DEFINED
_tagBLOB_DEFINED	equ 1
_BLOB_DEFINED		equ 1
_LPBLOB_DEFINED		equ 1
BLOB			STRUC
cbSize			ULONG ?
pBlobData		LPBYTE ?	;; [size_is]
BLOB			ENDS
LPBLOB			typedef ptr BLOB
endif

CLIPDATA		STRUC
cbSize			ULONG ?
ulClipFmt		LONG ?
pClipData		LPBYTE ?
CLIPDATA		ENDS

;; Macro to calculate the size of the above pClipData
CBPCLIPDATA macro clipdata
	exitm<( (clipdata).cbSize - sizeof((clipdata).ulClipFmt) )>
	endm
VARTYPE			typedef WORD

;;
;; VARENUM usage key,
;;
;; * [V] - may appear in a VARIANT
;; * [T] - may appear in a TYPEDESC
;; * [P] - may appear in an OLE property set
;; * [S] - may appear in a Safe Array
;;
;;
;;  VT_EMPTY		[V]   [P]     nothing
;;  VT_NULL		[V]   [P]     SQL style Null
;;  VT_I2		[V][T][P][S]  2 byte signed int
;;  VT_I4		[V][T][P][S]  4 byte signed int
;;  VT_R4		[V][T][P][S]  4 byte real
;;  VT_R8		[V][T][P][S]  8 byte real
;;  VT_CY		[V][T][P][S]  currency
;;  VT_DATE		[V][T][P][S]  date
;;  VT_BSTR		[V][T][P][S]  OLE Automation string
;;  VT_DISPATCH		[V][T][P][S]  IDispatch *
;;  VT_ERROR		[V][T][P][S]  SCODE
;;  VT_BOOL		[V][T][P][S]  True=-1, False=0
;;  VT_VARIANT		[V][T][P][S]  VARIANT *
;;  VT_UNKNOWN		[V][T]	 [S]  IUnknown *
;;  VT_DECIMAL		[V][T]	 [S]  16 byte fixed point
;;  VT_RECORD		[V]   [P][S]  user defined type
;;  VT_I1		[V][T][P][s]  signed char
;;  VT_UI1		[V][T][P][S]  unsigned char
;;  VT_UI2		[V][T][P][S]  unsigned short
;;  VT_UI4		[V][T][P][S]  unsigned short
;;  VT_I8		   [T][P]     signed 64-bit int
;;  VT_UI8		   [T][P]     unsigned 64-bit int
;;  VT_INT		[V][T][P][S]  signed machine int
;;  VT_UINT		[V][T]	 [S]  unsigned machine int
;;  VT_VOID		   [T]	      C style void
;;  VT_HRESULT		   [T]	      Standard return type
;;  VT_PTR		   [T]	      pointer type
;;  VT_SAFEARRAY	   [T]	      (use VT_ARRAY in VARIANT)
;;  VT_CARRAY		   [T]	      C style array
;;  VT_USERDEFINED	   [T]	      user defined type
;;  VT_LPSTR		   [T][P]     null terminated string
;;  VT_LPWSTR		   [T][P]     wide null terminated string
;;  VT_FILETIME		      [P]     FILETIME
;;  VT_BLOB		      [P]     Length prefixed bytes
;;  VT_STREAM		      [P]     Name of the stream follows
;;  VT_STORAGE		      [P]     Name of the storage follows
;;  VT_STREAMED_OBJECT	      [P]     Stream contains an object
;;  VT_STORED_OBJECT	      [P]     Storage contains an object
;;  VT_BLOB_OBJECT	      [P]     Blob contains an object
;;  VT_CF		      [P]     Clipboard format
;;  VT_CLSID		      [P]     A Class ID
;;  VT_VECTOR		      [P]     simple counted array
;;  VT_ARRAY		[V]	      SAFEARRAY*
;;  VT_BYREF		[V]	      void* for local use
;;  VT_BSTR_BLOB		      Reserved for system use
;;

;;enum VARENUM
VT_EMPTY		equ 0
VT_NULL			equ 1
VT_I2			equ 2
VT_I4			equ 3
VT_R4			equ 4
VT_R8			equ 5
VT_CY			equ 6
VT_DATE			equ 7
VT_BSTR			equ 8
VT_DISPATCH		equ 9
VT_ERROR		equ 10
VT_BOOL			equ 11
VT_VARIANT		equ 12
VT_UNKNOWN		equ 13
VT_DECIMAL		equ 14
VT_I1			equ 16
VT_UI1			equ 17
VT_UI2			equ 18
VT_UI4			equ 19
VT_I8			equ 20
VT_UI8			equ 21
VT_INT			equ 22
VT_UINT			equ 23
VT_VOID			equ 24
VT_HRESULT		equ 25
VT_PTR			equ 26
VT_SAFEARRAY		equ 27
VT_CARRAY		equ 28
VT_USERDEFINED		equ 29
VT_LPSTR		equ 30
VT_LPWSTR		equ 31
VT_RECORD		equ 36
VT_FILETIME		equ 64
VT_BLOB			equ 65
VT_STREAM		equ 66
VT_STORAGE		equ 67
VT_STREAMED_OBJECT	equ 68
VT_STORED_OBJECT	equ 69
VT_BLOB_OBJECT		equ 70
VT_CF			equ 71
VT_CLSID		equ 72
VT_BSTR_BLOB		equ 0xfff
VT_VECTOR		equ 0x1000
VT_ARRAY		equ 0x2000
VT_BYREF		equ 0x4000
VT_RESERVED		equ 0x8000
VT_ILLEGAL		equ 0xffff
VT_ILLEGALMASKED	equ 0xfff
VT_TYPEMASK		equ 0xfff

PROPID			typedef ULONG

ifndef SID_IDENTIFIER_AUTHORITY_DEFINED
SID_IDENTIFIER_AUTHORITY_DEFINED equ 1
SID_IDENTIFIER_AUTHORITY STRUC
Value			db 6 dup(?)
SID_IDENTIFIER_AUTHORITY ENDS
PSID_IDENTIFIER_AUTHORITY typedef ptr SID_IDENTIFIER_AUTHORITY
endif

ifndef SID_DEFINED
SID_DEFINED		equ 1
SID			STRUC
Revision		dw ?
SubAuthorityCount	dw ?
IdentifierAuthority	SID_IDENTIFIER_AUTHORITY <>
SubAuthority		dd ?
SID			ENDS
PISID			typedef ptr SID
endif

APPID			typedef GUID

CSPLATFORM		STRUC
dwPlatformId		dd ?
dwVersionHi		dd ?
dwVersionLo		dd ?
dwProcessorArch		dd ?
CSPLATFORM		ENDS

QUERYCONTEXT		STRUC
dwContext		dd ?
Platform		CSPLATFORM <>
Locale			LCID ?
dwVersionHi		dd ?
dwVersionLo		dd ?
QUERYCONTEXT		ENDS


;;enum tagTYSPEC
TYSPEC_CLSID		equ 0
TYSPEC_FILEEXT		equ TYSPEC_CSID + 1
TYSPEC_MIMETYPE		equ TYSPEC_FILEEXT + 1
TYSPEC_PROGID		equ TYSPEC_MIMETYPE + 1
TYSPEC_IID		equ TYSPEC_PROGID + 1
TYSPEC_TYPELIB		equ TYSPEC_IID + 1
TYSPEC_FILENAME		equ TYSPEC_TYPEIB + 1
TYSPEC_JAVACLASS	equ TYSPEC_FILENAME + 1
TYSPEC_PACKAGENAME	equ TYSPEC_JAVACASS + 1


uCLSSPEC		STRUC
tyspec			dd ?
UNION	tagged_union
 clsid			CLSID <>
 iid			IID <>
 typelibID		GUID <>
 pFileExt		LPOLESTR ?
 pMimeType		LPOLESTR ?
 pProgId		LPOLESTR ?
 pFileName		LPOLESTR ?
 pJavaClassName		LPOLESTR ?
 pPackageName		LPOLESTR ?
ENDS
uCLSSPEC		ENDS

PUBLISHEDAPPINFO	STRUC
pwszFileExtension	LPOLESTR ?
pwszDisplayName		LPOLESTR ?
pwszPackagePath		LPOLESTR ?
PUBLISHEDAPPINFO	ENDS

APPINFOTYPE		typedef SDWORD
APPINFO_PUBLISHED	equ 1
APPINFO_SHELLNEW	equ APPINFO_PUBISHED + 1
APPINFO_INSERTABLE	equ APPINFO_SHELLNEW + 1


ACTFLG_RunLocally	equ 1
ACTFLG_RunOnce		equ 2
ACTFLG_SystemWide	equ 4
ACTFLG_Published	equ 8
ACTFLG_Assigned		equ 16
ACTFLG_UserInstall	equ 32

;;typedef enum _CLASSPATHTYPE
CLASSPATHTYPE		typedef SDWORD
ExeNamePath		equ 0
DllNamePath		equ ExeNamePath + 1
TlbNamePath		equ DllNamePath + 1
CabFilePath		equ TlbNamePath + 1
InfFilePath		equ CabFilePath + 1
DrwFilePath		equ InfFilePath + 1
SetupNamePath		equ DrwFilePath + 1


APPDETAIL		STRUC
AppID			GUID <>
cClasses		dd ?
prgClsIdList		LPCLSID ?
cTypeLibIds		dd ?
prgTypeLibIdList	LPCLSID ?
cServers		dd ?
prgServerNames		LPOLESTR ?
APPDETAIL		ENDS
LPAPPDETAIL		typedef ptr APPDETAIL

PACKAGEDETAIL		STRUC
PathType		CLASSPATHTYPE ?
pszPath			LPOLESTR ?
pszIconPath		LPOLESTR ?
pszSetupCommand		LPOLESTR ?
dwActFlags		dd ?
pszVendor		LPOLESTR ?
pszPackageName		LPOLESTR ?
pszProductName		LPOLESTR ?
dwContext		dd ?
Platform		CSPLATFORM <>
Locale			LCID ?
dwVersionHi		dd ?
dwVersionLo		dd ?
Usn			dq ?;ULONGLONG ?
cApps			dd ?
pAppDetail		LPAPPDETAIL ?
PACKAGEDETAIL		ENDS
LPPACKAGEDETAIL		typedef ptr PACKAGEDETAIL

PACKAGEINFO		STRUC
pszClassIconPath	LPOLESTR ?
pTreatAsClsid		LPCLSID ?
cPackages		dd ?
pPackageDetail		LPPACKAGEDETAIL ?
PACKAGEINFO		ENDS


externdef __MIDL_itf_wtypes_0001_v0_0_c_ifspec:RPC_IF_HANDLE
externdef __MIDL_itf_wtypes_0001_v0_0_s_ifspec:RPC_IF_HANDLE

;; Additional Prototypes for ALL interfaces

;; end of Additional Prototypes

.list

endif	;; __wtypes_h__

