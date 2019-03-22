ifndef _INC_SHLWAPI
_INC_SHLWAPI equ <>
.pragma list(push, 0)

ifndef __LIBC_INC
 include libc.inc
endif
ifndef NOSHLWAPI
include SpecStrings.inc
include objbase.inc
include shtypes.inc

ifndef WINSHLWAPI
ifndef _SHLWAPI_
.pragma comment(lib, shlwapi)
endif
endif

ifdef _WIN32
.pragma pack(push, 8)
endif

ifndef __IBindCtx_FWD_DEFINED__
__IBindCtx_FWD_DEFINED__ equ 1
;typedef interface IBindCtx IBindCtx;
endif

if defined(__cplusplus) AND defined(STRICT_CONST)
USE_STRICT_CONST equ 1
endif

ifndef NO_SHLWAPI_STRFCNS

ifdef USE_STRICT_CONST
if (_WIN32_IE GE _WIN32_IE_IE60)
endif
else
;LWSTDAPI
StrChrA proto WINAPI \
	       lpStart: LPCSTR,
		wMatch: WORD
StrChrW proto WINAPI \
	       lpStart: LPCWSTR,
		wMatch: WCHAR
StrChrIA proto WINAPI \
	       lpStart: LPCSTR,
		wMatch: WORD
StrChrIW proto WINAPI \
	       lpStart: LPCWSTR,
		wMatch: WCHAR
if (_WIN32_IE GT _WIN32_IE_IE60)
;LWSTDAPI
StrChrNW proto WINAPI \
	       lpStart: LPCWSTR,
		wMatch: WCHAR,
		cchMax: UINT
StrChrNIW proto WINAPI \
	       lpStart: LPCWSTR,
		wMatch: WCHAR,
		cchMax: UINT
endif
endif ;; USE_STRICT_CONST

;LWSTDAPI
StrCmpNA proto WINAPI \
		lpStr1: LPCSTR,
		lpStr2: LPCSTR,
		 nChar: SINT

;LWSTDAPI
StrCmpNW proto WINAPI \
		lpStr1: LPCWSTR,
		lpStr2: LPCWSTR,
		 nChar: SINT

;LWSTDAPI
StrCmpNIA proto WINAPI \
		lpStr1: LPCSTR,
		lpStr2: LPCSTR,
		 nChar: SINT

;LWSTDAPI
StrCmpNIW proto WINAPI \
		lpStr1: LPCWSTR,
		lpStr2: LPCWSTR,
		 nChar: SINT

;LWSTDAPI
StrCSpnA proto WINAPI \
		 lpStr: LPCSTR,
		 lpSet: LPCSTR

;LWSTDAPI
StrCSpnW proto WINAPI \
		 lpStr: LPCWSTR,
		 lpSet: LPCWSTR

;LWSTDAPI
StrCSpnIA proto WINAPI \
		 lpStr: LPCSTR,
		 lpSet: LPCSTR

;LWSTDAPI
StrCSpnIW proto WINAPI \
		 lpStr: LPCWSTR,
		 lpSet: LPCWSTR

;LWSTDAPI
StrDupA proto WINAPI \
		lpSrch: LPCSTR

;LWSTDAPI
StrDupW proto WINAPI \
		lpSrch: LPCWSTR



tagSFBS_FLAGS		typedef SDWORD
SFBS_FLAGS_ROUND_TO_NEAREST_DISPLAYED_DIGIT equ 0x0001
SFBS_FLAGS_TRUNCATE_UNDISPLAYED_DECIMAL_DIGITS equ 0x0002
SFBS_FLAGS		typedef SINT

;LWSTDAPI
StrFormatByteSizeEx proto WINAPI \
		   ull: ULONGLONG,
		 flags: SFBS_FLAGS,
		pszBuf: LPWSTR,
		cchBuf: UINT


;LWSTDAPI
StrFormatByteSizeA proto WINAPI \
		   _dw: DWORD,
		pszBuf: LPSTR,
		cchBuf: UINT

;LWSTDAPI
StrFormatByteSize64A proto WINAPI \
		   qdw: LONGLONG,
		pszBuf: LPSTR,
		cchBuf: UINT

;LWSTDAPI
StrFormatByteSizeW proto WINAPI \
		   qdw: LONGLONG,
		pszBuf: LPWSTR,
		cchBuf: UINT

;LWSTDAPI
StrFormatKBSizeW proto WINAPI \
		   qdw: LONGLONG,
		pszBuf: LPWSTR,
		cchBuf: UINT

;LWSTDAPI
StrFormatKBSizeA proto WINAPI \
		   qdw: LONGLONG,
		pszBuf: LPSTR,
		cchBuf: UINT

;LWSTDAPI
StrFromTimeIntervalA proto WINAPI \
		pszOut: LPSTR,
		cchMax: UINT,
	      dwTimeMS: DWORD,
		digits: SINT

;LWSTDAPI
StrFromTimeIntervalW proto WINAPI \
	       pwszOut: LPWSTR,
		cchMax: UINT,
	      dwTimeMS: DWORD,
		digits: SINT

;LWSTDAPI
StrIsIntlEqualA proto WINAPI \
	     fCaseSens: BOOL,
	     lpString1: LPCSTR,
	     lpString2: LPCSTR,
		 nChar: SINT

;LWSTDAPI
StrIsIntlEqualW proto WINAPI \
	     fCaseSens: BOOL,
	     lpString1: LPCWSTR,
	     lpString2: LPCWSTR,
		 nChar: SINT

;LWSTDAPI
StrNCatA proto WINAPI \
		  psz1: LPSTR,
		  psz2: LPCSTR,
		cchMax: SINT

;LWSTDAPI
StrNCatW proto WINAPI \
		  psz1: LPWSTR,
		  psz2: LPCWSTR,
		cchMax: SINT

ifdef USE_STRICT_CONST
else
;LWSTDAPI
StrPBrkA proto WINAPI \
		   psz: LPCSTR,
		pszSet: LPCSTR

;LWSTDAPI
StrPBrkW proto WINAPI \
		   psz: LPCWSTR,
		pszSet: LPCWSTR

;LWSTDAPI
StrRChrA proto WINAPI \
	       lpStart: LPCSTR,
		 lpEnd: LPCSTR,
		wMatch: WORD

;LWSTDAPI
StrRChrW proto WINAPI \
	       lpStart: LPCWSTR,
		 lpEnd: LPCWSTR,
		wMatch: WCHAR

;LWSTDAPI
StrRChrIA proto WINAPI \
	       lpStart: LPCSTR,
		 lpEnd: LPCSTR,
		wMatch: WORD

;LWSTDAPI
StrRChrIW proto WINAPI \
	       lpStart: LPCWSTR,
		 lpEnd: LPCWSTR,
		wMatch: WCHAR

;LWSTDAPI
StrRStrIA proto WINAPI \
	      lpSource: LPCSTR,
		lpLast: LPCSTR,
		lpSrch: LPCSTR

;LWSTDAPI
StrRStrIW proto WINAPI \
	      lpSource: LPCWSTR,
		lpLast: LPCWSTR,
		lpSrch: LPCWSTR
endif

;LWSTDAPI
StrSpnA proto WINAPI \
		   psz: LPCSTR,
		pszSet: LPCSTR

;LWSTDAPI
StrSpnW proto WINAPI \
		   psz: LPCWSTR,
		pszSet: LPCWSTR

ifdef USE_STRICT_CONST
if (_WIN32_IE GE _WIN32_IE_IE6)
endif
else
;LWSTDAPI
StrStrA proto WINAPI \
	       lpFirst: LPCSTR,
		lpSrch: LPCSTR

;LWSTDAPI
StrStrW proto WINAPI \
	       lpFirst: LPCWSTR,
		lpSrch: LPCWSTR

;LWSTDAPI
StrStrIA proto WINAPI \
	       lpFirst: LPCSTR,
		lpSrch: LPCSTR

;LWSTDAPI
StrStrIW proto WINAPI \
	       lpFirst: LPCWSTR,
		lpSrch: LPCWSTR

if (_WIN32_IE GE _WIN32_IE_IE60)
;LWSTDAPI
StrStrNW proto WINAPI \
	       lpFirst: LPCWSTR,
		lpSrch: LPCWSTR,
		cchMax: UINT

;LWSTDAPI
StrStrNIW proto WINAPI \
	       lpFirst: LPCWSTR,
		lpSrch: LPCWSTR,
		cchMax: UINT

endif
endif

STIF_DEFAULT		equ 0x00000000
STIF_SUPPORT_HEX	equ 0x00000001
STIF_FLAGS		typedef SINT

;LWSTDAPI
StrToIntA proto WINAPI \
		 lpSrc: LPCSTR

;LWSTDAPI
StrToIntW proto WINAPI \
		 lpSrc: LPCWSTR

;LWSTDAPI
StrToIntExA proto WINAPI \
	     pszString: LPCSTR,
	       dwFlags: STIF_FLAGS,
		 piRet: ptr SINT

;LWSTDAPI
StrToIntExW proto WINAPI \
	     pszString: LPCWSTR,
	       dwFlags: STIF_FLAGS,
		 piRet: ptr SINT

if (_WIN32_IE GE _WIN32_IE_IE60)
;LWSTDAPI
StrToInt64ExA proto WINAPI \
	     pszString: LPCSTR,
	       dwFlags: STIF_FLAGS,
		pllRet: ptr LONGLONG

;LWSTDAPI
StrToInt64ExW proto WINAPI \
	     pszString: LPCWSTR,
	       dwFlags: STIF_FLAGS,
		pllRet: ptr LONGLONG

endif

;LWSTDAPI
StrTrimA proto WINAPI \
		   psz: LPSTR,
	  pszTrimChars: LPCSTR

;LWSTDAPI
StrTrimW proto WINAPI \
		   psz: LPWSTR,
	  pszTrimChars: LPCWSTR



;LWSTDAPI
StrCatW proto WINAPI \
		  psz1: LPWSTR,
		  psz2: LPCWSTR

;LWSTDAPI
StrCmpW proto WINAPI \
		  psz1: LPCWSTR,
		  psz2: LPCWSTR

;LWSTDAPI
StrCmpIW proto WINAPI \
		  psz1: LPCWSTR,
		  psz2: LPCWSTR

;LWSTDAPI
StrCpyW proto WINAPI \
		  psz1: LPWSTR,
		  psz2: LPCWSTR

;LWSTDAPI
StrCpyNW proto WINAPI \
		  psz1: LPWSTR,
		  psz2: LPCWSTR,
		cchMax: SINT


;LWSTDAPI
StrCatBuffW proto WINAPI \
	       pszDest: LPWSTR,
		pszSrc: LPCWSTR,
       cchDestBuffSize: SINT

;LWSTDAPI
StrCatBuffA proto WINAPI \
	       pszDest: LPSTR,
		pszSrc: LPCSTR,
       cchDestBuffSize: SINT

;LWSTDAPI
ChrCmpIA proto WINAPI \
		    w1: WORD,
		    w2: WORD

;LWSTDAPI
ChrCmpIW proto WINAPI \
		    w1: WCHAR,
		    w2: WCHAR


;LWSTDAPI
wvnsprintfA proto WINAPI \
	       pszDest: LPSTR,
	       cchDest: SINT,
		pszFmt: LPCSTR,
	       arglist: va_list

;LWSTDAPI
wvnsprintfW proto WINAPI \
	       pszDest: LPWSTR,
	       cchDest: SINT,
		pszFmt: LPCWSTR,
	       arglist: va_list

;LWSTDAPIV
wnsprintfA proto _CDecl \
	       pszDest: LPSTR,
	       cchDest: SINT,
		pszFmt: LPCSTR,
		      : VARARG

;LWSTDAPIV
wnsprintfW proto _CDecl \
	       pszDest: LPWSTR,
	       cchDest: SINT,
		pszFmt: LPCWSTR,
		      : VARARG


StrIntlEqNA macro s1, s2, nChar
	exitm<StrIsIntlEqualA( TRUE, s1, s2, nChar)>
	endm
StrIntlEqNW macro s1, s2, nChar
	exitm<StrIsIntlEqualW( TRUE, s1, s2, nChar)>
	endm
StrIntlEqNIA macro s1, s2, nChar
	exitm<StrIsIntlEqualA(FALSE, s1, s2, nChar)>
	endm
StrIntlEqNIW macro s1, s2, nChar
	exitm<StrIsIntlEqualW(FALSE, s1, s2, nChar)>
	endm

;LWSTDAPI
StrRetToStrA proto WINAPI \
		  pstr: ptr STRRET,
		  pidl: PCUITEMID_CHILD,
		  ppsz: ptr LPSTR

;LWSTDAPI
StrRetToStrW proto WINAPI \
		  pstr: ptr STRRET,
		  pidl: PCUITEMID_CHILD,
		  ppsz: ptr LPWSTR

ifdef _UNICODE
StrRetToStr		equ <StrRetToStrW>
else
StrRetToStr		equ <StrRetToStrA>
endif

;LWSTDAPI
StrRetToBufA proto WINAPI \
		  pstr: ptr STRRET,
		  pidl: PCUITEMID_CHILD,
		pszBuf: LPSTR,
		cchBuf: UINT

;LWSTDAPI
StrRetToBufW proto WINAPI \
		  pstr: ptr STRRET,
		  pidl: PCUITEMID_CHILD,
		pszBuf: LPWSTR,
		cchBuf: UINT

ifdef _UNICODE
StrRetToBuf		equ <StrRetToBufW>
else
StrRetToBuf		equ <StrRetToBufA>
endif


;LWSTDAPI
SHStrDupA proto WINAPI \
		   psz: LPCSTR,
		 ppwsz: ptr LPWSTR

;LWSTDAPI
SHStrDupW proto WINAPI \
		   psz: LPCWSTR,
		 ppwsz: ptr LPWSTR

ifdef _UNICODE
SHStrDup		equ <SHStrDupW>
else
SHStrDup		equ <SHStrDupA>
endif

if (_WIN32_IE GE _WIN32_IE_IE55)
;LWSTDAPI
StrCmpLogicalW proto WINAPI \
		  psz1: LPCWSTR,
		  psz2: LPCWSTR

;LWSTDAPI
StrCatChainW proto WINAPI \
		pszDst: LPWSTR,
		cchDst: DWORD,
		 ichAt: DWORD,
		pszSrc: LPCWSTR

;LWSTDAPI
StrRetToBSTR proto WINAPI \
		  pstr: ptr STRRET,
		  pidl: PCUITEMID_CHILD,
		 pbstr: ptr BSTR

;LWSTDAPI
SHLoadIndirectString proto WINAPI \
	     pszSource: LPCWSTR,
	     pszOutBuf: LPWSTR,
	     cchOutBuf: UINT,
	   ppvReserved: PVOID

endif


if (_WIN32_IE GE _WIN32_IE_IE60SP2)
;LWSTDAPI
IsCharSpaceA proto WINAPI \
		   wch: CHAR

;LWSTDAPI
IsCharSpaceW proto WINAPI \
		   wch: WCHAR

ifdef _UNICODE
IsCharSpace		equ <IsCharSpaceW>
else
IsCharSpace		equ <IsCharSpaceA>
endif

;LWSTDAPI
StrCmpCA proto WINAPI \
	       pszStr1: LPCSTR,
	       pszStr2: LPCSTR

;LWSTDAPI
StrCmpCW proto WINAPI \
	       pszStr1: LPCWSTR,
	       pszStr2: LPCWSTR

ifdef _UNICODE
StrCmpC			equ <StrCmpCW>
else
StrCmpC			equ <StrCmpCA>
endif

;LWSTDAPI
StrCmpICA proto WINAPI \
	       pszStr1: LPCSTR,
	       pszStr2: LPCSTR

;LWSTDAPI
StrCmpICW proto WINAPI \
	       pszStr1: LPCWSTR,
	       pszStr2: LPCWSTR

ifdef _UNICODE
StrCmpIC		equ <StrCmpICW>
else
StrCmpIC		equ <StrCmpICA>
endif
endif

ifdef _UNICODE
StrChr			equ <StrChrW>
StrRChr			equ <StrRChrW>
StrChrI			equ <StrChrIW>
StrRChrI		equ <StrRChrIW>
StrCmpN			equ <StrCmpNW>
StrCmpNI		equ <StrCmpNIW>
StrStr			equ <StrStrW>
StrStrI			equ <StrStrIW>
StrDup			equ <StrDupW>
StrRStrI		equ <StrRStrIW>
StrCSpn			equ <StrCSpnW>
StrCSpnI		equ <StrCSpnIW>
StrSpn			equ <StrSpnW>
StrToInt		equ <StrToIntW>
StrPBrk			equ <StrPBrkW>
StrToIntEx		equ <StrToIntExW>
if (_WIN32_IE GE 0x0600)
StrToInt64Ex		equ <StrToInt64ExW>
endif
StrFromTimeInterval	equ <StrFromTimeIntervalW>
StrIntlEqN		equ <StrIntlEqNW>
StrIntlEqNI		equ <StrIntlEqNIW>
StrFormatByteSize	equ <StrFormatByteSizeW>
StrFormatByteSize64	equ <StrFormatByteSizeW>
StrFormatKBSize		equ <StrFormatKBSizeW>
StrNCat			equ <StrNCatW>
StrTrim			equ <StrTrimW>
StrCatBuff		equ <StrCatBuffW>
ChrCmpI			equ <ChrCmpIW>
wvnsprintf		equ <wvnsprintfW>
wnsprintf		equ <wnsprintfW>
StrIsIntlEqual		equ <StrIsIntlEqualW>

else

StrChr			equ <StrChrA>
StrRChr			equ <StrRChrA>
StrChrI			equ <StrChrIA>
StrRChrI		equ <StrRChrIA>
StrCmpN			equ <StrCmpNA>
StrCmpNI		equ <StrCmpNIA>
StrStr			equ <StrStrA>
StrStrI			equ <StrStrIA>
StrDup			equ <StrDupA>
StrRStrI		equ <StrRStrIA>
StrCSpn			equ <StrCSpnA>
StrCSpnI		equ <StrCSpnIA>
StrSpn			equ <StrSpnA>
StrToInt		equ <StrToIntA>
StrPBrk			equ <StrPBrkA>
StrToIntEx		equ <StrToIntExA>
if (_WIN32_IE GE 0x0600)
StrToInt64Ex		equ <StrToInt64ExA>
endif
StrFromTimeInterval	equ <StrFromTimeIntervalA>
StrIntlEqN		equ <StrIntlEqNA>
StrIntlEqNI		equ <StrIntlEqNIA>
StrFormatByteSize	equ <StrFormatByteSizeA>
StrFormatByteSize64	equ <StrFormatByteSize64A>
StrFormatKBSize		equ <StrFormatKBSizeA>
StrNCat			equ <StrNCatA>
StrTrim			equ <StrTrimA>
StrCatBuff		equ <StrCatBuffA>
ChrCmpI			equ <ChrCmpIA>
wvnsprintf		equ <wvnsprintfA>
wnsprintf		equ <wnsprintfA>
StrIsIntlEqual		equ <StrIsIntlEqualA>
endif

if (_WIN32_IE GE _WIN32_IE_IE50)
;LWSTDAPI
StrCmpNCA proto WINAPI \
		lpStr1: LPCSTR,
		lpStr2: LPCSTR,
		 nChar: SINT

;LWSTDAPI
StrCmpNCW proto WINAPI \
		lpStr1: LPCWSTR,
		lpStr2: LPCWSTR,
		 nChar: SINT

ifdef _UNICODE
StrCmpNC		equ <StrCmpNCW>
else
StrCmpNC		equ <StrCmpNCA>
endif
;LWSTDAPI
StrCmpNICA proto WINAPI \
		lpStr1: LPCSTR,
		lpStr2: LPCSTR,
		 nChar: SINT

;LWSTDAPI
StrCmpNICW proto WINAPI \
		lpStr1: LPCWSTR,
		lpStr2: LPCWSTR,
		 nChar: SINT

ifdef _UNICODE
StrCmpNIC		equ <StrCmpNICW>
else
StrCmpNIC		equ <StrCmpNICA>
endif
endif


;LWSTDAPI
IntlStrEqWorkerA proto WINAPI \
	     fCaseSens: BOOL,
	     lpString1: LPCSTR,
	     lpString2: LPCSTR,
		 nChar: SINT

;LWSTDAPI
IntlStrEqWorkerW proto WINAPI \
	     fCaseSens: BOOL,
	     lpString1: LPCWSTR,
	     lpString2: LPCWSTR,
		 nChar: SINT


IntlStrEqNA macro s1, s2, nChar
	exitm<IntlStrEqWorkerA( TRUE, s1, s2, nChar)>
	endm
IntlStrEqNW macro s1, s2, nChar
	exitm<IntlStrEqWorkerW( TRUE, s1, s2, nChar)>
	endm
IntlStrEqNIA macro s1, s2, nChar
	exitm<IntlStrEqWorkerA(FALSE, s1, s2, nChar)>
	endm
IntlStrEqNIW macro s1, s2, nChar
	exitm<IntlStrEqWorkerW(FALSE, s1, s2, nChar)>
	endm

ifdef _UNICODE
IntlStrEqN		equ <IntlStrEqNW>
IntlStrEqNI		equ <IntlStrEqNIW>
else
IntlStrEqN		equ <IntlStrEqNA>
IntlStrEqNI		equ <IntlStrEqNIA>
endif

SZ_CONTENTTYPE_HTMLA	equ <"text/html">
SZ_CONTENTTYPE_HTMLW	equ <L"text/html">
SZ_CONTENTTYPE_CDFA	equ <"application/x-cdf">
SZ_CONTENTTYPE_CDFW	equ <L"application/x-cdf">

ifdef _UNICODE
SZ_CONTENTTYPE_HTML	equ <SZ_CONTENTTYPE_HTMLW>
SZ_CONTENTTYPE_CDF	equ <SZ_CONTENTTYPE_CDFW>
else
SZ_CONTENTTYPE_HTML	equ <SZ_CONTENTTYPE_HTMLA>
SZ_CONTENTTYPE_CDF	equ <SZ_CONTENTTYPE_CDFA>
endif

PathIsHTMLFileA macro pszPath
	exitm<PathIsContentTypeA(pszPath, SZ_CONTENTTYPE_HTMLA)>
	endm
PathIsHTMLFileW macro pszPath
	exitm<PathIsContentTypeW(pszPath, SZ_CONTENTTYPE_HTMLW)>
	endm


StrCatA			equ <lstrcatA>
StrCmpA			equ <lstrcmpA>
StrCmpIA		equ <lstrcmpiA>
StrCpyA			equ <lstrcpyA>
StrCpyNA		equ <lstrcpynA>


StrToLong		equ <StrToInt>
StrNCmp			equ <StrCmpN>
StrNCmpI		equ <StrCmpNI>
StrNCpy			equ <StrCpyN>
StrCatN			equ <StrNCat>

ifdef _UNICODE
StrCat			equ <StrCatW>
StrCmp			equ <StrCmpW>
StrCmpI			equ <StrCmpIW>
StrCpy			equ <StrCpyW>
StrCpyN			equ <StrCpyNW>
StrCatBuff		equ <StrCatBuffW>
else
StrCat			equ <lstrcatA>
StrCmp			equ <lstrcmpA>
StrCmpI			equ <lstrcmpiA>
StrCpy			equ <lstrcpyA>
StrCpyN			equ <lstrcpynA>
StrCatBuff		equ <StrCatBuffA>
endif

endif ;;  NO_SHLWAPI_STRFCNS

ifndef NO_SHLWAPI_PATH

;LWSTDAPI
PathAddBackslashA proto WINAPI \
	       pszPath: LPSTR

;LWSTDAPI
PathAddBackslashW proto WINAPI \
	       pszPath: LPWSTR

ifdef _UNICODE
PathAddBackslash	equ <PathAddBackslashW>
else
PathAddBackslash	equ <PathAddBackslashA>
endif
;LWSTDAPI
PathAddExtensionA proto WINAPI \
	       pszPath: LPSTR,
		pszExt: LPCSTR
PathAddExtensionW proto WINAPI \
	       pszPath: LPWSTR,
		pszExt: LPCWSTR
ifdef _UNICODE
PathAddExtension	equ <PathAddExtensionW>
else
PathAddExtension	equ <PathAddExtensionA>
endif

;LWSTDAPI
PathAppendA proto WINAPI \
	       pszPath: LPSTR,
		 pMore: LPCSTR

;LWSTDAPI
PathAppendW proto WINAPI \
	       pszPath: LPWSTR,
		 pMore: LPCWSTR

;LWSTDAPI
PathBuildRootA proto WINAPI \
	       pszRoot: LPSTR,
		iDrive: SINT

;LWSTDAPI
PathBuildRootW proto WINAPI \
	       pszRoot: LPWSTR,
		iDrive: SINT

ifdef _UNICODE
PathBuildRoot		equ <PathBuildRootW>
else
PathBuildRoot		equ <PathBuildRootA>
endif
;LWSTDAPI
PathCanonicalizeA proto WINAPI \
		pszBuf: LPSTR,
	       pszPath: LPCSTR

;LWSTDAPI
PathCanonicalizeW proto WINAPI \
		pszBuf: LPWSTR,
	       pszPath: LPCWSTR

;LWSTDAPI
PathCombineA proto WINAPI \
	       pszDest: LPSTR,
		pszDir: LPCSTR,
	       pszFile: LPCSTR

;LWSTDAPI
PathCombineW proto WINAPI \
	       pszDest: LPWSTR,
		pszDir: LPCWSTR,
	       pszFile: LPCWSTR

ifdef _UNICODE
PathCombine		equ <PathCombineW>
else
PathCombine		equ <PathCombineA>
endif
;LWSTDAPI
PathCompactPathA proto WINAPI \
		   hDC: HDC,
	       pszPath: LPSTR,
		   _dx: UINT

;LWSTDAPI
PathCompactPathW proto WINAPI \
		   hDC: HDC,
	       pszPath: LPWSTR,
		   _dx: UINT

;LWSTDAPI
PathCompactPathExA proto WINAPI \
		pszOut: LPSTR,
		pszSrc: LPCSTR,
		cchMax: UINT,
	       dwFlags: DWORD

;LWSTDAPI
PathCompactPathExW proto WINAPI \
		pszOut: LPWSTR,
		pszSrc: LPCWSTR,
		cchMax: UINT,
	       dwFlags: DWORD

;LWSTDAPI
PathCommonPrefixA proto WINAPI \
	      pszFile1: LPCSTR,
	      pszFile2: LPCSTR,
	       achPath: LPSTR

;LWSTDAPI
PathCommonPrefixW proto WINAPI \
	      pszFile1: LPCWSTR,
	      pszFile2: LPCWSTR,
	       achPath: LPWSTR

;LWSTDAPI
PathFileExistsA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathFileExistsW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathFileExists		equ <PathFileExistsW>
else
PathFileExists		equ <PathFileExistsA>
endif
ifdef USE_STRICT_CONST
;LWSTDAPI
PathFindExtensionA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathFindExtensionW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathFindExtension	equ <PathFindExtensionW>
else
PathFindExtension	equ <PathFindExtensionA>
endif
;LWSTDAPI
PathFindFileNameA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathFindFileNameW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathFindFileName	equ <PathFindFileNameW>
else
PathFindFileName	equ <PathFindFileNameA>
endif
;LWSTDAPI
PathFindNextComponentA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathFindNextComponentW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathFindNextComponent	equ <PathFindNextComponentW>
else
PathFindNextComponent	equ <PathFindNextComponentA>
endif
else
;LWSTDAPI
PathFindExtensionA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathFindExtensionW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathFindExtension	equ <PathFindExtensionW>
else
PathFindExtension	equ <PathFindExtensionA>
endif
;LWSTDAPI
PathFindFileNameA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathFindFileNameW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathFindFileName	equ <PathFindFileNameW>
else
PathFindFileName	equ <PathFindFileNameA>
endif
;LWSTDAPI
PathFindNextComponentA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathFindNextComponentW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathFindNextComponent	equ <PathFindNextComponentW>
else
PathFindNextComponent	equ <PathFindNextComponentA>
endif
endif ;; USE_STRICT_CONST

;LWSTDAPI
PathFindOnPathA proto WINAPI \
	       pszPath: LPSTR,
	 ppszOtherDirs: PZPCSTR

;LWSTDAPI
PathFindOnPathW proto WINAPI \
	       pszPath: LPWSTR,
	 ppszOtherDirs: PZPCWSTR

;LWSTDAPI
PathFindSuffixArrayA proto WINAPI \
	       pszPath: LPCSTR,
	    apszSuffix: ptr LPCSTR,
	    iArraySize: SINT

;LWSTDAPI
PathFindSuffixArrayW proto WINAPI \
	       pszPath: LPCWSTR,
	    apszSuffix: ptr LPCWSTR,
	    iArraySize: SINT

ifdef _UNICODE
PathFindSuffixArray	equ <PathFindSuffixArrayW>
else
PathFindSuffixArray	equ <PathFindSuffixArrayA>
endif
ifdef USE_STRICT_CONST
;LWSTDAPI
PathGetArgsA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathGetArgsW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathGetArgs		equ <PathGetArgsW>
else
PathGetArgs		equ <PathGetArgsA>
endif
else
;LWSTDAPI
PathGetArgsA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathGetArgsW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathGetArgs		equ <PathGetArgsW>
else
PathGetArgs		equ <PathGetArgsA>
endif
endif ;; USE_STRICT_CONST

;LWSTDAPI
PathIsLFNFileSpecA proto WINAPI \
		lpName: LPCSTR

;LWSTDAPI
PathIsLFNFileSpecW proto WINAPI \
		lpName: LPCWSTR

ifdef _UNICODE
PathIsLFNFileSpec	equ <PathIsLFNFileSpecW>
else
PathIsLFNFileSpec	equ <PathIsLFNFileSpecA>
endif
;LWSTDAPI
PathGetCharTypeA proto WINAPI \
		   _ch: UCHAR

;LWSTDAPI
PathGetCharTypeW proto WINAPI \
		   _ch: WCHAR


GCT_INVALID		equ 0x0000
GCT_LFNCHAR		equ 0x0001
GCT_SHORTCHAR		equ 0x0002
GCT_WILD		equ 0x0004
GCT_SEPARATOR		equ 0x0008

;LWSTDAPI
PathGetDriveNumberA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathGetDriveNumberW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathGetDriveNumber	equ <PathGetDriveNumberW>
else
PathGetDriveNumber	equ <PathGetDriveNumberA>
endif
;LWSTDAPI
PathIsDirectoryA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathIsDirectoryW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathIsDirectory		equ <PathIsDirectoryW>
else
PathIsDirectory		equ <PathIsDirectoryA>
endif
;LWSTDAPI
PathIsDirectoryEmptyA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathIsDirectoryEmptyW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathIsDirectoryEmpty	equ <PathIsDirectoryEmptyW>
else
PathIsDirectoryEmpty	equ <PathIsDirectoryEmptyA>
endif
;LWSTDAPI
PathIsFileSpecA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathIsFileSpecW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathIsFileSpec		equ <PathIsFileSpecW>
else
PathIsFileSpec		equ <PathIsFileSpecA>
endif
;LWSTDAPI
PathIsPrefixA proto WINAPI \
	     pszPrefix: LPCSTR,
	       pszPath: LPCSTR

;LWSTDAPI
PathIsPrefixW proto WINAPI \
	     pszPrefix: LPCWSTR,
	       pszPath: LPCWSTR

ifdef _UNICODE
PathIsPrefix		equ <PathIsPrefixW>
else
PathIsPrefix		equ <PathIsPrefixA>
endif
;LWSTDAPI
PathIsRelativeA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathIsRelativeW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathIsRelative		equ <PathIsRelativeW>
else
PathIsRelative		equ <PathIsRelativeA>
endif
;LWSTDAPI
PathIsRootA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathIsRootW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathIsRoot		equ <PathIsRootW>
else
PathIsRoot		equ <PathIsRootA>
endif
;LWSTDAPI
PathIsSameRootA proto WINAPI \
	      pszPath1: LPCSTR,
	      pszPath2: LPCSTR

;LWSTDAPI
PathIsSameRootW proto WINAPI \
	      pszPath1: LPCWSTR,
	      pszPath2: LPCWSTR

ifdef _UNICODE
PathIsSameRoot		equ <PathIsSameRootW>
else
PathIsSameRoot		equ <PathIsSameRootA>
endif
;LWSTDAPI
PathIsUNCA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathIsUNCW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathIsUNC		equ <PathIsUNCW>
else
PathIsUNC		equ <PathIsUNCA>
endif
;LWSTDAPI
PathIsNetworkPathA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathIsNetworkPathW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathIsNetworkPath	equ <PathIsNetworkPathW>
else
PathIsNetworkPath	equ <PathIsNetworkPathA>
endif
;LWSTDAPI
PathIsUNCServerA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathIsUNCServerW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathIsUNCServer		equ <PathIsUNCServerW>
else
PathIsUNCServer		equ <PathIsUNCServerA>
endif
;LWSTDAPI
PathIsUNCServerShareA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathIsUNCServerShareW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathIsUNCServerShare	equ <PathIsUNCServerShareW>
else
PathIsUNCServerShare	equ <PathIsUNCServerShareA>
endif
;LWSTDAPI
PathIsContentTypeA proto WINAPI \
	       pszPath: LPCSTR,
	pszContentType: LPCSTR

;LWSTDAPI
PathIsContentTypeW proto WINAPI \
	       pszPath: LPCWSTR,
	pszContentType: LPCWSTR

;LWSTDAPI
PathIsURLA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathIsURLW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathIsURL		equ <PathIsURLW>
else
PathIsURL		equ <PathIsURLA>
endif
;LWSTDAPI
PathMakePrettyA proto WINAPI \
	       pszPath: LPSTR

;LWSTDAPI
PathMakePrettyW proto WINAPI \
	       pszPath: LPWSTR

;LWSTDAPI
PathMatchSpecA proto WINAPI \
	       pszFile: LPCSTR,
	       pszSpec: LPCSTR

;LWSTDAPI
PathMatchSpecW proto WINAPI \
	       pszFile: LPCWSTR,
	       pszSpec: LPCWSTR


if (_WIN32_IE GE _WIN32_IE_IE70)
PMSF_NORMAL		equ 0x00000000
PMSF_MULTIPLE		equ 0x00000001
PMSF_DONT_STRIP_SPACES	equ 0x00010000

;LWSTDAPI
PathMatchSpecExA proto WINAPI \
	       pszFile: LPCSTR,
	       pszSpec: LPCSTR,
	       dwFlags: DWORD

;LWSTDAPI
PathMatchSpecExW proto WINAPI \
	       pszFile: LPCWSTR,
	       pszSpec: LPCWSTR,
	       dwFlags: DWORD

endif

;LWSTDAPI
PathParseIconLocationA proto WINAPI \
	   pszIconFile: LPSTR

;LWSTDAPI
PathParseIconLocationW proto WINAPI \
	   pszIconFile: LPWSTR

;LWSTDAPI
PathQuoteSpacesA proto WINAPI \
		  lpsz: LPSTR

;LWSTDAPI
PathQuoteSpacesW proto WINAPI \
		  lpsz: LPWSTR

;LWSTDAPI
PathRelativePathToA proto WINAPI \
	       pszPath: LPSTR,
	       pszFrom: LPCSTR,
	    dwAttrFrom: DWORD,
		 pszTo: LPCSTR,
	      dwAttrTo: DWORD

;LWSTDAPI
PathRelativePathToW proto WINAPI \
	       pszPath: LPWSTR,
	       pszFrom: LPCWSTR,
	    dwAttrFrom: DWORD,
		 pszTo: LPCWSTR,
	      dwAttrTo: DWORD

;LWSTDAPI
PathRemoveArgsA proto WINAPI \
	       pszPath: LPSTR

;LWSTDAPI
PathRemoveArgsW proto WINAPI \
	       pszPath: LPWSTR

;LWSTDAPI
PathRemoveBackslashA proto WINAPI \
	       pszPath: LPSTR

;LWSTDAPI
PathRemoveBackslashW proto WINAPI \
	       pszPath: LPWSTR

ifdef _UNICODE
PathRemoveBackslash	equ <PathRemoveBackslashW>
else
PathRemoveBackslash	equ <PathRemoveBackslashA>
endif
;LWSTDAPI
PathRemoveBlanksA proto WINAPI \
	       pszPath: LPSTR

;LWSTDAPI
PathRemoveBlanksW proto WINAPI \
	       pszPath: LPWSTR

;LWSTDAPI
PathRemoveExtensionA proto WINAPI \
	       pszPath: LPSTR

;LWSTDAPI
PathRemoveExtensionW proto WINAPI \
	       pszPath: LPWSTR

;LWSTDAPI
PathRemoveFileSpecA proto WINAPI \
	       pszPath: LPSTR

;LWSTDAPI
PathRemoveFileSpecW proto WINAPI \
	       pszPath: LPWSTR

;LWSTDAPI
PathRenameExtensionA proto WINAPI \
	       pszPath: LPSTR,
		pszExt: LPCSTR

;LWSTDAPI
PathRenameExtensionW proto WINAPI \
	       pszPath: LPWSTR,
		pszExt: LPCWSTR

;LWSTDAPI
PathSearchAndQualifyA proto WINAPI \
	       pszPath: LPCSTR,
		pszBuf: LPSTR,
		cchBuf: UINT

;LWSTDAPI
PathSearchAndQualifyW proto WINAPI \
	       pszPath: LPCWSTR,
		pszBuf: LPWSTR,
		cchBuf: UINT

;LWSTDAPI
PathSetDlgItemPathA proto WINAPI \
		  hDlg: HWND,
		    id: SINT,
	       pszPath: LPCSTR

;LWSTDAPI
PathSetDlgItemPathW proto WINAPI \
		  hDlg: HWND,
		    id: SINT,
	       pszPath: LPCWSTR

ifdef USE_STRICT_CONST
;LWSTDAPI
PathSkipRootA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathSkipRootW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathSkipRoot		equ <PathSkipRootW>
else
PathSkipRoot		equ <PathSkipRootA>
endif
else
;LWSTDAPI
PathSkipRootA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathSkipRootW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathSkipRoot		equ <PathSkipRootW>
else
PathSkipRoot		equ <PathSkipRootA>
endif
endif
;LWSTDAPI
PathStripPathA proto WINAPI \
	       pszPath: LPSTR

;LWSTDAPI
PathStripPathW proto WINAPI \
	       pszPath: LPWSTR

ifdef _UNICODE
PathStripPath		equ <PathStripPathW>
else
PathStripPath		equ <PathStripPathA>
endif
;LWSTDAPI
PathStripToRootA proto WINAPI \
	       pszPath: LPSTR

;LWSTDAPI
PathStripToRootW proto WINAPI \
	       pszPath: LPWSTR

ifdef _UNICODE
PathStripToRoot		equ <PathStripToRootW>
else
PathStripToRoot		equ <PathStripToRootA>
endif
;LWSTDAPI
PathUnquoteSpacesA proto WINAPI \
		  lpsz: LPSTR

;LWSTDAPI
PathUnquoteSpacesW proto WINAPI \
		  lpsz: LPWSTR

;LWSTDAPI
PathMakeSystemFolderA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathMakeSystemFolderW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathMakeSystemFolder	equ <PathMakeSystemFolderW>
else
PathMakeSystemFolder	equ <PathMakeSystemFolderA>
endif
;LWSTDAPI
PathUnmakeSystemFolderA proto WINAPI \
	       pszPath: LPCSTR

;LWSTDAPI
PathUnmakeSystemFolderW proto WINAPI \
	       pszPath: LPCWSTR

ifdef _UNICODE
PathUnmakeSystemFolder	equ <PathUnmakeSystemFolderW>
else
PathUnmakeSystemFolder	equ <PathUnmakeSystemFolderA>
endif
;LWSTDAPI
PathIsSystemFolderA proto WINAPI \
	       pszPath: LPCSTR,
	       dwAttrb: DWORD

;LWSTDAPI
PathIsSystemFolderW proto WINAPI \
	       pszPath: LPCWSTR,
	       dwAttrb: DWORD

ifdef _UNICODE
PathIsSystemFolder	equ <PathIsSystemFolderW>
else
PathIsSystemFolder	equ <PathIsSystemFolderA>
endif
;LWSTDAPI
PathUndecorateA proto WINAPI \
	       pszPath: LPSTR

;LWSTDAPI
PathUndecorateW proto WINAPI \
	       pszPath: LPWSTR

ifdef _UNICODE
PathUndecorate		equ <PathUndecorateW>
else
PathUndecorate		equ <PathUndecorateA>
endif
;LWSTDAPI
PathUnExpandEnvStringsA proto WINAPI \
	       pszPath: LPCSTR,
		pszBuf: LPSTR,
		cchBuf: UINT

;LWSTDAPI
PathUnExpandEnvStringsW proto WINAPI \
	       pszPath: LPCWSTR,
		pszBuf: LPWSTR,
		cchBuf: UINT

ifdef _UNICODE
PathUnExpandEnvStrings	equ <PathUnExpandEnvStringsW>
else
PathUnExpandEnvStrings	equ <PathUnExpandEnvStringsA>
endif


ifdef _UNICODE
PathAppend		equ <PathAppendW>
PathCanonicalize	equ <PathCanonicalizeW>
PathCompactPath		equ <PathCompactPathW>
PathCompactPathEx	equ <PathCompactPathExW>
PathCommonPrefix	equ <PathCommonPrefixW>
PathFindOnPath		equ <PathFindOnPathW>
PathGetCharType		equ <PathGetCharTypeW>
PathIsContentType	equ <PathIsContentTypeW>
PathIsHTMLFile		equ <PathIsHTMLFileW>
PathMakePretty		equ <PathMakePrettyW>
PathMatchSpec		equ <PathMatchSpecW>
if (_WIN32_IE GE _WIN32_IE_IE70)
PathMatchSpecEx		equ <PathMatchSpecExW>
endif
PathParseIconLocation	equ <PathParseIconLocationW>
PathQuoteSpaces		equ <PathQuoteSpacesW>
PathRelativePathTo	equ <PathRelativePathToW>
PathRemoveArgs		equ <PathRemoveArgsW>
PathRemoveBlanks	equ <PathRemoveBlanksW>
PathRemoveExtension	equ <PathRemoveExtensionW>
PathRemoveFileSpec	equ <PathRemoveFileSpecW>
PathRenameExtension	equ <PathRenameExtensionW>
PathSearchAndQualify	equ <PathSearchAndQualifyW>
PathSetDlgItemPath	equ <PathSetDlgItemPathW>
PathUnquoteSpaces	equ <PathUnquoteSpacesW>
else
PathAppend		equ <PathAppendA>
PathCanonicalize	equ <PathCanonicalizeA>
PathCompactPath		equ <PathCompactPathA>
PathCompactPathEx	equ <PathCompactPathExA>
PathCommonPrefix	equ <PathCommonPrefixA>
PathFindOnPath		equ <PathFindOnPathA>
PathGetCharType		equ <PathGetCharTypeA>
PathIsContentType	equ <PathIsContentTypeA>
PathIsHTMLFile		equ <PathIsHTMLFileA>
PathMakePretty		equ <PathMakePrettyA>
PathMatchSpec		equ <PathMatchSpecA>
if (_WIN32_IE GE _WIN32_IE_IE70)
PathMatchSpecEx		equ <PathMatchSpecExA>
endif
PathParseIconLocation	equ <PathParseIconLocationA>
PathQuoteSpaces		equ <PathQuoteSpacesA>
PathRelativePathTo	equ <PathRelativePathToA>
PathRemoveArgs		equ <PathRemoveArgsA>
PathRemoveBlanks	equ <PathRemoveBlanksA>
PathRemoveExtension	equ <PathRemoveExtensionA>
PathRemoveFileSpec	equ <PathRemoveFileSpecA>
PathRenameExtension	equ <PathRenameExtensionA>
PathSearchAndQualify	equ <PathSearchAndQualifyA>
PathSetDlgItemPath	equ <PathSetDlgItemPathA>
PathUnquoteSpaces	equ <PathUnquoteSpacesA>
endif

URL_SCHEME_INVALID	equ -1
URL_SCHEME_UNKNOWN	equ 0
URL_SCHEME_FTP		equ 2
URL_SCHEME_HTTP		equ 3
URL_SCHEME_GOPHER	equ 4
URL_SCHEME_MAILTO	equ 5
URL_SCHEME_NEWS		equ 6
URL_SCHEME_NNTP		equ 7
URL_SCHEME_TELNET	equ 8
URL_SCHEME_WAIS		equ 9
URL_SCHEME_FILE		equ 10
URL_SCHEME_MK		equ 11
URL_SCHEME_HTTPS	equ 12
URL_SCHEME_SHELL	equ 13
URL_SCHEME_SNEWS	equ 14
URL_SCHEME_LOCAL	equ 15
URL_SCHEME_JAVASCRIPT	equ 16
URL_SCHEME_VBSCRIPT	equ 17
URL_SCHEME_ABOUT	equ 18
URL_SCHEME_RES		equ 19
if (_WIN32_IE GE _WIN32_IE_IE60)
URL_SCHEME_MSSHELLROOTED equ 20
URL_SCHEME_MSSHELLIDLIST equ 21
URL_SCHEME_MSHELP	equ 22
endif
if (_WIN32_IE GE _WIN32_IE_IE70)
URL_SCHEME_MSSHELLDEVICE equ 23
URL_SCHEME_WILDCARD	equ 24
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
URL_SCHEME_SEARCH_MS	equ 25
endif
if (NTDDI_VERSION GE NTDDI_VISTASP1)
URL_SCHEME_SEARCH	equ 26
endif
if (NTDDI_VERSION GE NTDDI_WIN7)
URL_SCHEME_KNOWNFOLDER	equ 27
endif
URL_SCHEME_MAXVALUE	equ 28

URL_PART		typedef SDWORD
URL_PART_NONE		equ 0
URL_PART_SCHEME		equ 1
URL_PART_HOSTNAME	equ 2
URL_PART_USERNAME	equ 3
URL_PART_PASSWORD	equ 4
URL_PART_PORT		equ 5
URL_PART_QUERY		equ 6

URLIS			typedef SDWORD
URLIS_URL		equ 0
URLIS_OPAQUE		equ 1
URLIS_NOHISTORY		equ 2
URLIS_FILEURL		equ 3
URLIS_APPLIABLE		equ 4
URLIS_DIRECTORY		equ 5
URLIS_HASQUERY		equ 6

URL_UNESCAPE		equ 0x10000000
URL_ESCAPE_UNSAFE	equ 0x20000000
URL_PLUGGABLE_PROTOCOL	equ 0x40000000
URL_WININET_COMPATIBILITY equ 0x80000000
URL_DONT_ESCAPE_EXTRA_INFO equ 0x02000000
URL_DONT_UNESCAPE_EXTRA_INFO equ URL_DONT_ESCAPE_EXTRA_INFO
URL_BROWSER_MODE	equ URL_DONT_ESCAPE_EXTRA_INFO
URL_ESCAPE_SPACES_ONLY	equ 0x04000000
URL_DONT_SIMPLIFY	equ 0x08000000
URL_NO_META		equ URL_DONT_SIMPLIFY
URL_UNESCAPE_INPLACE	equ 0x00100000
URL_CONVERT_IF_DOSPATH	equ 0x00200000
URL_UNESCAPE_HIGH_ANSI_ONLY equ 0x00400000
URL_INTERNAL_PATH	equ 0x00800000
URL_FILE_USE_PATHURL	equ 0x00010000
if (_WIN32_IE GE _WIN32_IE_IE60SP2)
URL_DONT_UNESCAPE	equ 0x00020000
endif
if (NTDDI_VERSION GE NTDDI_WIN7)
URL_ESCAPE_AS_UTF8	equ 0x00040000
endif
URL_ESCAPE_PERCENT	equ 0x00001000
URL_ESCAPE_SEGMENT_ONLY equ 0x00002000

URL_PARTFLAG_KEEPSCHEME equ 0x00000001

URL_APPLY_DEFAULT	equ 0x00000001
URL_APPLY_GUESSSCHEME	equ 0x00000002
URL_APPLY_GUESSFILE	equ 0x00000004
URL_APPLY_FORCEAPPLY	equ 0x00000008


;LWSTDAPI
UrlCompareA proto WINAPI \
		  psz1: LPCSTR,
		  psz2: LPCSTR,
	  fIgnoreSlash: BOOL

;LWSTDAPI
UrlCompareW proto WINAPI \
		  psz1: LPCWSTR,
		  psz2: LPCWSTR,
	  fIgnoreSlash: BOOL

;LWSTDAPI
UrlCombineA proto WINAPI \
	       pszBase: LPCSTR,
	   pszRelative: LPCSTR,
	   pszCombined: LPSTR,
	  pcchCombined: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlCombineW proto WINAPI \
	       pszBase: LPCWSTR,
	   pszRelative: LPCWSTR,
	   pszCombined: LPWSTR,
	  pcchCombined: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlCanonicalizeA proto WINAPI \
		pszUrl: LPCSTR,
      pszCanonicalized: LPSTR,
     pcchCanonicalized: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlCanonicalizeW proto WINAPI \
		pszUrl: LPCWSTR,
      pszCanonicalized: LPWSTR,
     pcchCanonicalized: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlIsOpaqueA proto WINAPI \
		pszURL: LPCSTR

;LWSTDAPI
UrlIsOpaqueW proto WINAPI \
		pszURL: LPCWSTR

;LWSTDAPI
UrlIsNoHistoryA proto WINAPI \
		pszURL: LPCSTR

;LWSTDAPI
UrlIsNoHistoryW proto WINAPI \
		pszURL: LPCWSTR

UrlIsFileUrlA macro pszURL
	exitm<UrlIsA(pszURL, URLIS_FILEURL)>
	endm
UrlIsFileUrlW macro pszURL
	exitm<UrlIsW(pszURL, URLIS_FILEURL)>
	endm
;LWSTDAPI
UrlIsA proto WINAPI \
		pszUrl: LPCSTR,
		 UrlIs: URLIS

;LWSTDAPI
UrlIsW proto WINAPI \
		pszUrl: LPCWSTR,
		 UrlIs: URLIS

;LWSTDAPI
UrlGetLocationA proto WINAPI \
		  psz1: LPCSTR

;LWSTDAPI
UrlGetLocationW proto WINAPI \
		  psz1: LPCWSTR

;LWSTDAPI
UrlUnescapeA proto WINAPI \
		pszUrl: LPSTR,
	  pszUnescaped: LPSTR,
	 pcchUnescaped: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlUnescapeW proto WINAPI \
		pszUrl: LPWSTR,
	  pszUnescaped: LPWSTR,
	 pcchUnescaped: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlEscapeA proto WINAPI \
		pszUrl: LPCSTR,
	    pszEscaped: LPSTR,
	   pcchEscaped: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlEscapeW proto WINAPI \
		pszUrl: LPCWSTR,
	    pszEscaped: LPWSTR,
	   pcchEscaped: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlCreateFromPathA proto WINAPI \
	       pszPath: LPCSTR,
		pszUrl: LPSTR,
	       pcchUrl: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlCreateFromPathW proto WINAPI \
	       pszPath: LPCWSTR,
		pszUrl: LPWSTR,
	       pcchUrl: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
PathCreateFromUrlA proto WINAPI \
		pszUrl: LPCSTR,
	       pszPath: LPSTR,
	      pcchPath: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
PathCreateFromUrlW proto WINAPI \
		pszUrl: LPCWSTR,
	       pszPath: LPWSTR,
	      pcchPath: LPDWORD,
	       dwFlags: DWORD

if (_WIN32_IE GE _WIN32_IE_IE70)
;LWSTDAPI
PathCreateFromUrlAlloc proto WINAPI \
		 pszIn: LPCWSTR,
	       ppszOut: ptr LPWSTR,
	       dwFlags: DWORD

endif
;LWSTDAPI
UrlHashA proto WINAPI \
		pszUrl: LPCSTR,
		pbHash: LPBYTE,
		cbHash: DWORD

;LWSTDAPI
UrlHashW proto WINAPI \
		pszUrl: LPCWSTR,
		pbHash: LPBYTE,
		cbHash: DWORD

;LWSTDAPI
UrlGetPartW proto WINAPI \
		 pszIn: LPCWSTR,
		pszOut: LPWSTR,
	       pcchOut: LPDWORD,
		dwPart: DWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlGetPartA proto WINAPI \
		 pszIn: LPCSTR,
		pszOut: LPSTR,
	       pcchOut: LPDWORD,
		dwPart: DWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlApplySchemeA proto WINAPI \
		 pszIn: LPCSTR,
		pszOut: LPSTR,
	       pcchOut: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
UrlApplySchemeW proto WINAPI \
		 pszIn: LPCWSTR,
		pszOut: LPWSTR,
	       pcchOut: LPDWORD,
	       dwFlags: DWORD

;LWSTDAPI
HashData proto WINAPI \
		pbData: LPBYTE,
		cbData: DWORD,
		pbHash: LPBYTE,
		cbHash: DWORD

;LWSTDAPI
UrlFixupW proto WINAPI \
		 pszIn: LPCWSTR,
		pszOut: LPWSTR,
		cchOut: DWORD


ifdef _UNICODE
UrlCompare		equ <UrlCompareW>
UrlCombine		equ <UrlCombineW>
UrlCanonicalize		equ <UrlCanonicalizeW>
UrlIsOpaque		equ <UrlIsOpaqueW>
UrlIsFileUrl		equ <UrlIsFileUrlW>
UrlGetLocation		equ <UrlGetLocationW>
UrlUnescape		equ <UrlUnescapeW>
UrlEscape		equ <UrlEscapeW>
UrlCreateFromPath	equ <UrlCreateFromPathW>
PathCreateFromUrl	equ <PathCreateFromUrlW>
UrlHash			equ <UrlHashW>
UrlGetPart		equ <UrlGetPartW>
UrlApplyScheme		equ <UrlApplySchemeW>
UrlIs			equ <UrlIsW>
UrlFixup		equ <UrlFixupW>
else
UrlCompare		equ <UrlCompareA>
UrlCombine		equ <UrlCombineA>
UrlCanonicalize		equ <UrlCanonicalizeA>
UrlIsOpaque		equ <UrlIsOpaqueA>
UrlIsFileUrl		equ <UrlIsFileUrlA>
UrlGetLocation		equ <UrlGetLocationA>
UrlUnescape		equ <UrlUnescapeA>
UrlEscape		equ <UrlEscapeA>
UrlCreateFromPath	equ <UrlCreateFromPathA>
PathCreateFromUrl	equ <PathCreateFromUrlA>
UrlHash			equ <UrlHashA>
UrlGetPart		equ <UrlGetPartA>
UrlApplyScheme		equ <UrlApplySchemeA>
UrlIs			equ <UrlIsA>
endif

UrlEscapeSpaces macro pszUrl, pszEscaped, pcchEscaped
	exitm<UrlCanonicalize(pszUrl, pszEscaped, pcchEscaped, URL_ESCAPE_SPACES_ONLY OR URL_DONT_ESCAPE_EXTRA_INFO )>
	endm
UrlUnescapeInPlace macro pszUrl, dwFlags
	exitm<UrlUnescape(pszUrl, NULL, NULL, dwFlags OR URL_UNESCAPE_INPLACE)>
	endm


if (_WIN32_IE GE _WIN32_IE_IE50)

PARSEDURLA		STRUC
cbSize			dd ?
pszProtocol		LPCSTR ?
cchProtocol		UINT ?
pszSuffix		LPCSTR ?
cchSuffix		UINT ?
nScheme			UINT ?
PARSEDURLA		ENDS
PPARSEDURLA		typedef ptr PARSEDURLA
PARSEDURLW		STRUC
cbSize			dd ?
pszProtocol		LPCWSTR ?
cchProtocol		UINT ?
pszSuffix		LPCWSTR ?
cchSuffix		UINT ?
nScheme			UINT ?
PARSEDURLW		ENDS
PPARSEDURLW		typedef ptr PARSEDURLW
ifdef _UNICODE
PARSEDURL		typedef PARSEDURLW
PPARSEDURL		typedef PPARSEDURLW
else
PARSEDURL		typedef PARSEDURLA
PPARSEDURL		typedef PPARSEDURLA
endif

;LWSTDAPI
ParseURLA proto WINAPI \
	       pcszURL: LPCSTR,
		   ppu: ptr PARSEDURLA

;LWSTDAPI
ParseURLW proto WINAPI \
	       pcszURL: LPCWSTR,
		   ppu: ptr PARSEDURLW

ifdef _UNICODE
ParseURL		equ <ParseURLW>
else
ParseURL		equ <ParseURLA>
endif

endif ;; _WIN32_IE_IE50
endif ;; NO_SHLWAPI_PATH

ifndef NO_SHLWAPI_REG

;LWSTDAPI
SHDeleteEmptyKeyA proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCSTR

;LWSTDAPI
SHDeleteEmptyKeyW proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCWSTR

ifdef _UNICODE
SHDeleteEmptyKey	equ <SHDeleteEmptyKeyW>
else
SHDeleteEmptyKey	equ <SHDeleteEmptyKeyA>
endif
;LWSTDAPI
SHDeleteKeyA proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCSTR

;LWSTDAPI
SHDeleteKeyW proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCWSTR

ifdef _UNICODE
SHDeleteKey		equ <SHDeleteKeyW>
else
SHDeleteKey		equ <SHDeleteKeyA>
endif
;LWSTDAPI
SHRegDuplicateHKey proto WINAPI \
		  hkey: HKEY

;LWSTDAPI
SHDeleteValueA proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCSTR,
	      pszValue: LPCSTR

;LWSTDAPI
SHDeleteValueW proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCWSTR,
	      pszValue: LPCWSTR

ifdef _UNICODE
SHDeleteValue		equ <SHDeleteValueW>
else
SHDeleteValue		equ <SHDeleteValueA>
endif
;LWSTDAPI
SHGetValueA proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCSTR,
	      pszValue: LPCSTR,
	       pdwType: ptr DWORD,
		pvData: ptr void,
	       pcbData: ptr DWORD

;LWSTDAPI
SHGetValueW proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCWSTR,
	      pszValue: LPCWSTR,
	       pdwType: ptr DWORD,
		pvData: ptr void,
	       pcbData: ptr DWORD

ifdef _UNICODE
SHGetValue		equ <SHGetValueW>
else
SHGetValue		equ <SHGetValueA>
endif
;LWSTDAPI
SHSetValueA proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCSTR,
	      pszValue: LPCSTR,
		dwType: DWORD,
		pvData: LPCVOID,
		cbData: DWORD

;LWSTDAPI
SHSetValueW proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCWSTR,
	      pszValue: LPCWSTR,
		dwType: DWORD,
		pvData: LPCVOID,
		cbData: DWORD

ifdef _UNICODE
SHSetValue		equ <SHSetValueW>
else
SHSetValue		equ <SHSetValueA>
endif

if (_WIN32_IE GE 0x0602)

SRRF			typedef SINT

SRRF_RT_REG_NONE	equ 0x00000001
SRRF_RT_REG_SZ		equ 0x00000002
SRRF_RT_REG_EXPAND_SZ	equ 0x00000004
SRRF_RT_REG_BINARY	equ 0x00000008
SRRF_RT_REG_DWORD	equ 0x00000010
SRRF_RT_REG_MULTI_SZ	equ 0x00000020
SRRF_RT_REG_QWORD	equ 0x00000040

SRRF_RT_DWORD		equ (SRRF_RT_REG_BINARY OR SRRF_RT_REG_DWORD)
SRRF_RT_QWORD		equ (SRRF_RT_REG_BINARY OR SRRF_RT_REG_QWORD)
SRRF_RT_ANY		equ 0x0000ffff

SRRF_RM_ANY		equ 0x00000000
SRRF_RM_NORMAL		equ 0x00010000
SRRF_RM_SAFE		equ 0x00020000
SRRF_RM_SAFENETWORK	equ 0x00040000

SRRF_NOEXPAND		equ 0x10000000
SRRF_ZEROONFAILURE	equ 0x20000000
SRRF_NOVIRT		equ 0x40000000



;LWSTDAPI
SHRegGetValueA proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCSTR,
	      pszValue: LPCSTR,
	     srrfFlags: SRRF,
	       pdwType: ptr DWORD,
		pvData: PVOID,
	       pcbData: ptr DWORD

;LWSTDAPI
SHRegGetValueW proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCWSTR,
	      pszValue: LPCWSTR,
	     srrfFlags: SRRF,
	       pdwType: ptr DWORD,
		pvData: PVOID,
	       pcbData: ptr DWORD

ifdef _UNICODE
SHRegGetValue		equ <SHRegGetValueW>
else
SHRegGetValue		equ <SHRegGetValueA>
endif

;LWSTDAPI
SHRegSetValue proto WINAPI \
		  hkey: HKEY,
	     pszSubKey: LPCWSTR,
	      pszValue: LPCWSTR,
	     srrfFlags: SRRF,
		dwType: DWORD,
		pvData: LPCVOID,
		cbData: DWORD


;LWSTDAPI
SHRegGetValueFromHKCUHKLM proto WINAPI \
	       pwszKey: PCWSTR,
	     pwszValue: PCWSTR,
	     srrfFlags: SRRF,
	       pdwType: ptr DWORD,
		pvData: PVOID,
	       pcbData: ptr DWORD

;STDAPI
SHRegGetBoolValueFromHKCUHKLM proto WINAPI \
		pszKey: PCWSTR,
	      pszValue: PCWSTR,
	      fDefault: BOOL

endif

;LWSTDAPI
SHQueryValueExA proto WINAPI \
		  hkey: HKEY,
	      pszValue: LPCSTR,
	   pdwReserved: ptr DWORD,
	       pdwType: ptr DWORD,
		pvData: ptr void,
	       pcbData: ptr DWORD

;LWSTDAPI
SHQueryValueExW proto WINAPI \
		  hkey: HKEY,
	      pszValue: LPCWSTR,
	   pdwReserved: ptr DWORD,
	       pdwType: ptr DWORD,
		pvData: ptr void,
	       pcbData: ptr DWORD

ifdef _UNICODE
SHQueryValueEx		equ <SHQueryValueExW>
else
SHQueryValueEx		equ <SHQueryValueExA>
endif


;LWSTDAPI
SHEnumKeyExA proto WINAPI \
		  hkey: HKEY,
	       dwIndex: DWORD,
	       pszName: LPSTR,
	      pcchName: LPDWORD

;LWSTDAPI
SHEnumKeyExW proto WINAPI \
		  hkey: HKEY,
	       dwIndex: DWORD,
	       pszName: LPWSTR,
	      pcchName: LPDWORD

;LWSTDAPI
SHEnumValueA proto WINAPI \
		  hkey: HKEY,
	       dwIndex: DWORD,
	  pszValueName: PSTR,
	 pcchValueName: LPDWORD,
	       pdwType: LPDWORD,
		pvData: PVOID,
	       pcbData: LPDWORD

;LWSTDAPI
SHEnumValueW proto WINAPI \
		  hkey: HKEY,
	       dwIndex: DWORD,
	  pszValueName: PWSTR,
	 pcchValueName: LPDWORD,
	       pdwType: LPDWORD,
		pvData: PVOID,
	       pcbData: LPDWORD

;LWSTDAPI
SHQueryInfoKeyA proto WINAPI \
		  hkey: HKEY,
	     pcSubKeys: LPDWORD,
      pcchMaxSubKeyLen: LPDWORD,
	      pcValues: LPDWORD,
   pcchMaxValueNameLen: LPDWORD

;LWSTDAPI
SHQueryInfoKeyW proto WINAPI \
		  hkey: HKEY,
	     pcSubKeys: LPDWORD,
      pcchMaxSubKeyLen: LPDWORD,
	      pcValues: LPDWORD,
   pcchMaxValueNameLen: LPDWORD


;LWSTDAPI
SHCopyKeyA proto WINAPI \
	       hkeySrc: HKEY,
	   szSrcSubKey: LPCSTR,
	      hkeyDest: HKEY,
	     fReserved: DWORD

;LWSTDAPI
SHCopyKeyW proto WINAPI \
	       hkeySrc: HKEY,
	  wszSrcSubKey: LPCWSTR,
	      hkeyDest: HKEY,
	     fReserved: DWORD

;LWSTDAPI
SHRegGetPathA proto WINAPI \
		  hKey: HKEY,
	    pcszSubKey: LPCSTR,
	     pcszValue: LPCSTR,
	       pszPath: LPSTR,
	       dwFlags: DWORD

;LWSTDAPI
SHRegGetPathW proto WINAPI \
		  hKey: HKEY,
	    pcszSubKey: LPCWSTR,
	     pcszValue: LPCWSTR,
	       pszPath: LPWSTR,
	       dwFlags: DWORD

;LWSTDAPI
SHRegSetPathA proto WINAPI \
		  hKey: HKEY,
	    pcszSubKey: LPCSTR,
	     pcszValue: LPCSTR,
	      pcszPath: LPCSTR,
	       dwFlags: DWORD

;LWSTDAPI
SHRegSetPathW proto WINAPI \
		  hKey: HKEY,
	    pcszSubKey: LPCWSTR,
	     pcszValue: LPCWSTR,
	      pcszPath: LPCWSTR,
	       dwFlags: DWORD


ifdef _UNICODE
SHEnumKeyEx		equ <SHEnumKeyExW>
SHEnumValue		equ <SHEnumValueW>
SHQueryInfoKey		equ <SHQueryInfoKeyW>
SHCopyKey		equ <SHCopyKeyW>
SHRegGetPath		equ <SHRegGetPathW>
SHRegSetPath		equ <SHRegSetPathW>
else
SHEnumKeyEx		equ <SHEnumKeyExA>
SHEnumValue		equ <SHEnumValueA>
SHQueryInfoKey		equ <SHQueryInfoKeyA>
SHCopyKey		equ <SHCopyKeyA>
SHRegGetPath		equ <SHRegGetPathA>
SHRegSetPath		equ <SHRegSetPathA>
endif


SHREGDEL_FLAGS		typedef SDWORD
SHREGDEL_DEFAULT	equ 0x00000000
SHREGDEL_HKCU		equ 0x00000001
SHREGDEL_HKLM		equ 0x00000010
SHREGDEL_BOTH		equ 0x00000011

SHREGENUM_FLAGS		typedef SDWORD
SHREGENUM_DEFAULT	equ 0x00000000
SHREGENUM_HKCU		equ 0x00000001
SHREGENUM_HKLM		equ 0x00000010
SHREGENUM_BOTH		equ 0x00000011

SHREGSET_HKCU		equ 0x00000001
SHREGSET_FORCE_HKCU	equ 0x00000002
SHREGSET_HKLM		equ 0x00000004
SHREGSET_FORCE_HKLM	equ 0x00000008
SHREGSET_DEFAULT	equ (SHREGSET_FORCE_HKCU OR SHREGSET_HKLM)

PHUSKEY			typedef ptr HUSKEY
ifndef REGSAM
REGSAM			typedef ACCESS_MASK
endif

;LWSTDAPI
SHRegCreateUSKeyA proto WINAPI \
	       pszPath: LPCSTR,
	    samDesired: REGSAM,
	hRelativeUSKey: HUSKEY,
	    phNewUSKey: PHUSKEY,
	       dwFlags: DWORD

;LWSTDAPI
SHRegCreateUSKeyW proto WINAPI \
	       pwzPath: LPCWSTR,
	    samDesired: REGSAM,
	hRelativeUSKey: HUSKEY,
	    phNewUSKey: PHUSKEY,
	       dwFlags: DWORD

;LWSTDAPI
SHRegOpenUSKeyA proto WINAPI \
	       pszPath: LPCSTR,
	    samDesired: REGSAM,
	hRelativeUSKey: HUSKEY,
	    phNewUSKey: PHUSKEY,
	   fIgnoreHKCU: BOOL

;LWSTDAPI
SHRegOpenUSKeyW proto WINAPI \
	       pwzPath: LPCWSTR,
	    samDesired: REGSAM,
	hRelativeUSKey: HUSKEY,
	    phNewUSKey: PHUSKEY,
	   fIgnoreHKCU: BOOL

;LWSTDAPI
SHRegQueryUSValueA proto WINAPI \
		hUSKey: HUSKEY,
	      pszValue: LPCSTR,
	       pdwType: ptr DWORD,
		pvData: PVOID,
	       pcbData: ptr DWORD,
	   fIgnoreHKCU: BOOL,
	 pvDefaultData: PVOID,
     dwDefaultDataSize: DWORD

;LWSTDAPI
SHRegQueryUSValueW proto WINAPI \
		hUSKey: HUSKEY,
	      pszValue: LPCWSTR,
	       pdwType: ptr DWORD,
		pvData: PVOID,
	       pcbData: ptr DWORD,
	   fIgnoreHKCU: BOOL,
	 pvDefaultData: PVOID,
     dwDefaultDataSize: DWORD

;LWSTDAPI
SHRegWriteUSValueA proto WINAPI \
		hUSKey: HUSKEY,
	      pszValue: LPCSTR,
		dwType: DWORD,
		pvData: PVOID,
		cbData: DWORD,
	       dwFlags: DWORD

;LWSTDAPI
SHRegWriteUSValueW proto WINAPI \
		hUSKey: HUSKEY,
	      pwzValue: LPCWSTR,
		dwType: DWORD,
		pvData: PVOID,
		cbData: DWORD,
	       dwFlags: DWORD

;LWSTDAPI
SHRegDeleteUSValueA proto WINAPI \
		hUSKey: HUSKEY,
	      pszValue: LPCSTR,
	   delRegFlags: SHREGDEL_FLAGS

;LWSTDAPI
SHRegDeleteUSValueW proto WINAPI \
		hUSKey: HUSKEY,
	      pwzValue: LPCWSTR,
	   delRegFlags: SHREGDEL_FLAGS

;LWSTDAPI
SHRegDeleteEmptyUSKeyW proto WINAPI \
		hUSKey: HUSKEY,
	     pwzSubKey: LPCWSTR,
	   delRegFlags: SHREGDEL_FLAGS

;LWSTDAPI
SHRegDeleteEmptyUSKeyA proto WINAPI \
		hUSKey: HUSKEY,
	     pszSubKey: LPCSTR,
	   delRegFlags: SHREGDEL_FLAGS

;LWSTDAPI
SHRegEnumUSKeyA proto WINAPI \
		hUSKey: HUSKEY,
	       dwIndex: DWORD,
	       pszName: LPSTR,
	      pcchName: LPDWORD,
	  enumRegFlags: SHREGENUM_FLAGS

;LWSTDAPI
SHRegEnumUSKeyW proto WINAPI \
		hUSKey: HUSKEY,
	       dwIndex: DWORD,
	       pwzName: LPWSTR,
	      pcchName: LPDWORD,
	  enumRegFlags: SHREGENUM_FLAGS

;LWSTDAPI
SHRegEnumUSValueA proto WINAPI \
		hUSkey: HUSKEY,
	       dwIndex: DWORD,
	  pszValueName: LPSTR,
	 pcchValueName: LPDWORD,
	       pdwType: LPDWORD,
		pvData: PVOID,
	       pcbData: LPDWORD,
	  enumRegFlags: SHREGENUM_FLAGS

;LWSTDAPI
SHRegEnumUSValueW proto WINAPI \
		hUSkey: HUSKEY,
	       dwIndex: DWORD,
	  pszValueName: LPWSTR,
	 pcchValueName: LPDWORD,
	       pdwType: LPDWORD,
		pvData: PVOID,
	       pcbData: LPDWORD,
	  enumRegFlags: SHREGENUM_FLAGS

;LWSTDAPI
SHRegQueryInfoUSKeyA proto WINAPI \
		hUSKey: HUSKEY,
	     pcSubKeys: LPDWORD,
      pcchMaxSubKeyLen: LPDWORD,
	      pcValues: LPDWORD,
   pcchMaxValueNameLen: LPDWORD,
	  enumRegFlags: SHREGENUM_FLAGS

;LWSTDAPI
SHRegQueryInfoUSKeyW proto WINAPI \
		hUSKey: HUSKEY,
	     pcSubKeys: LPDWORD,
      pcchMaxSubKeyLen: LPDWORD,
	      pcValues: LPDWORD,
   pcchMaxValueNameLen: LPDWORD,
	  enumRegFlags: SHREGENUM_FLAGS

;LWSTDAPI
SHRegCloseUSKey proto WINAPI \
		hUSKey: HUSKEY

;STDAPI
SHRegGetUSValueA proto WINAPI \
	     pszSubKey: LPCSTR,
	      pszValue: LPCSTR,
	       pdwType: ptr DWORD,
		pvData: ptr void,
	       pcbData: ptr DWORD,
	   fIgnoreHKCU: BOOL,
	 pvDefaultData: ptr void,
     dwDefaultDataSize: DWORD

;STDAPI
SHRegGetUSValueW proto WINAPI \
	     pszSubKey: LPCWSTR,
	      pszValue: LPCWSTR,
	       pdwType: ptr DWORD,
		pvData: ptr void,
	       pcbData: ptr DWORD,
	   fIgnoreHKCU: BOOL,
	 pvDefaultData: ptr void,
     dwDefaultDataSize: DWORD

;LWSTDAPI
SHRegSetUSValueA proto WINAPI \
	     pszSubKey: LPCSTR,
	      pszValue: LPCSTR,
		dwType: DWORD,
		pvData: PVOID,
		cbData: DWORD,
	       dwFlags: DWORD

;LWSTDAPI
SHRegSetUSValueW proto WINAPI \
	     pwzSubKey: LPCWSTR,
	      pwzValue: LPCWSTR,
		dwType: DWORD,
		pvData: PVOID,
		cbData: DWORD,
	       dwFlags: DWORD

;LWSTDAPI
SHRegGetIntW proto WINAPI \
		    hk: HKEY,
		pwzKey: PCWSTR,
	      iDefault: SINT


ifdef _UNICODE
SHRegCreateUSKey	equ <SHRegCreateUSKeyW>
SHRegOpenUSKey		equ <SHRegOpenUSKeyW>
SHRegQueryUSValue	equ <SHRegQueryUSValueW>
SHRegWriteUSValue	equ <SHRegWriteUSValueW>
SHRegDeleteUSValue	equ <SHRegDeleteUSValueW>
SHRegDeleteEmptyUSKey	equ <SHRegDeleteEmptyUSKeyW>
SHRegEnumUSKey		equ <SHRegEnumUSKeyW>
SHRegEnumUSValue	equ <SHRegEnumUSValueW>
SHRegQueryInfoUSKey	equ <SHRegQueryInfoUSKeyW>
SHRegGetUSValue		equ <SHRegGetUSValueW>
SHRegSetUSValue		equ <SHRegSetUSValueW>
SHRegGetInt		equ <SHRegGetIntW>
else
SHRegCreateUSKey	equ <SHRegCreateUSKeyA>
SHRegOpenUSKey		equ <SHRegOpenUSKeyA>
SHRegQueryUSValue	equ <SHRegQueryUSValueA>
SHRegWriteUSValue	equ <SHRegWriteUSValueA>
SHRegDeleteUSValue	equ <SHRegDeleteUSValueA>
SHRegDeleteEmptyUSKey	equ <SHRegDeleteEmptyUSKeyA>
SHRegEnumUSKey		equ <SHRegEnumUSKeyA>
SHRegEnumUSValue	equ <SHRegEnumUSValueA>
SHRegQueryInfoUSKey	equ <SHRegQueryInfoUSKeyA>
SHRegGetUSValue		equ <SHRegGetUSValueA>
SHRegSetUSValue		equ <SHRegSetUSValueA>
endif

;LWSTDAPI
SHRegGetBoolUSValueA proto WINAPI \
	     pszSubKey: LPCSTR,
	      pszValue: LPCSTR,
	   fIgnoreHKCU: BOOL,
	      fDefault: BOOL

;LWSTDAPI
SHRegGetBoolUSValueW proto WINAPI \
	     pszSubKey: LPCWSTR,
	      pszValue: LPCWSTR,
	   fIgnoreHKCU: BOOL,
	      fDefault: BOOL

ifdef _UNICODE
SHRegGetBoolUSValue	equ <SHRegGetBoolUSValueW>
else
SHRegGetBoolUSValue	equ <SHRegGetBoolUSValueA>
endif


ASSOCF_INIT_NOREMAPCLSID equ 0x00000001
ASSOCF_INIT_BYEXENAME	equ 0x00000002
ASSOCF_OPEN_BYEXENAME	equ 0x00000002
ASSOCF_INIT_DEFAULTTOSTAR equ 0x00000004
ASSOCF_INIT_DEFAULTTOFOLDER equ 0x00000008
ASSOCF_NOUSERSETTINGS	equ 0x00000010
ASSOCF_NOTRUNCATE	equ 0x00000020
ASSOCF_VERIFY		equ 0x00000040
ASSOCF_REMAPRUNDLL	equ 0x00000080
ASSOCF_NOFIXUPS		equ 0x00000100
ASSOCF_IGNOREBASECLASS	equ 0x00000200
ASSOCF_INIT_IGNOREUNKNOWN equ 0x00000400
ASSOCF			typedef DWORD

ASSOCSTR		typedef DWORD
ASSOCSTR_COMMAND	equ 1
ASSOCSTR_EXECUTABLE	equ 1
ASSOCSTR_FRIENDLYDOCNAME equ 2
ASSOCSTR_FRIENDLYAPPNAME equ 3
ASSOCSTR_NOOPEN		equ 4
ASSOCSTR_SHELLNEWVALUE	equ 5
ASSOCSTR_DDECOMMAND	equ 6
ASSOCSTR_DDEIFEXEC	equ 7
ASSOCSTR_DDEAPPLICATION equ 8
ASSOCSTR_DDETOPIC	equ 9
ASSOCSTR_INFOTIP	equ 10
if (_WIN32_IE GE _WIN32_IE_IE60)
ASSOCSTR_QUICKTIP	equ 11
ASSOCSTR_TILEINFO	equ 12
ASSOCSTR_CONTENTTYPE	equ 13
ASSOCSTR_DEFAULTICON	equ 14
ASSOCSTR_SHELLEXTENSION equ 15
endif
if (_WIN32_IE GE _WIN32_IE_IE80)
ASSOCSTR_DROPTARGET	equ 16
ASSOCSTR_DELEGATEEXECUTE equ 17
endif
ASSOCSTR_MAX		equ 18

ASSOCKEY		typedef DWORD
ASSOCKEY_SHELLEXECCLASS equ 1
ASSOCKEY_APP		equ 1
ASSOCKEY_CLASS		equ 2
ASSOCKEY_BASECLASS	equ 3
ASSOCKEY_MAX		equ 4

ASSOCDATA		typedef DWORD
ASSOCDATA_MSIDESCRIPTOR equ 1
ASSOCDATA_NOACTIVATEHANDLER equ 1
ASSOCDATA_QUERYCLASSSTORE equ 2
ASSOCDATA_HASPERUSERASSOC equ 3
if (_WIN32_IE GE _WIN32_IE_IE60)
ASSOCDATA_EDITFLAGS	equ 4
ASSOCDATA_VALUE		equ 5
endif
ASSOCDATA_MAX		equ 6

ASSOCENUM		typedef DWORD
ASSOCENUM_NONE		equ 0

DEFINE_IIDX(IQueryAssociations, "c46ca590-3c3f-11d2-bee6-0000f805ca57")
.comdef IQueryAssociations
    QueryInterface	proc :REFIID, :PVOID
    AddRef		proc
    Release		proc
    Init		proc :ASSOCF, :LPCWSTR, :HKEY, :HWND
    GetString		proc :ASSOCF, :ASSOCSTR, :LPCWSTR, :LPWSTR, :ptr DWORD
    GetKey		proc :ASSOCF, :ASSOCKEY, :LPCWSTR, :ptr HKEY
    GetData		proc :ASSOCF, :ASSOCDATA, :LPCWSTR, :PVOID, :ptr DWORD
    GetEnum		proc :ASSOCF, :ASSOCENUM, :LPCWSTR, :REFIID, :PVOID
    .ends

;LWSTDAPI
AssocCreate proto WINAPI \
		 clsid: CLSID,
		  riid: REFIID,
		   ppv: PVOID

;LWSTDAPI
AssocQueryStringA proto WINAPI \
		 flags: ASSOCF,
		  _str: ASSOCSTR,
	      pszAssoc: LPCSTR,
	      pszExtra: LPCSTR,
		pszOut: LPSTR,
	       pcchOut: ptr DWORD

;LWSTDAPI
AssocQueryStringW proto WINAPI \
		 flags: ASSOCF,
		  _str: ASSOCSTR,
	      pszAssoc: LPCWSTR,
	      pszExtra: LPCWSTR,
		pszOut: LPWSTR,
	       pcchOut: ptr DWORD

ifdef _UNICODE
AssocQueryString	equ <AssocQueryStringW>
else
AssocQueryString	equ <AssocQueryStringA>
endif
;LWSTDAPI
AssocQueryStringByKeyA proto WINAPI \
		 flags: ASSOCF,
		  _str: ASSOCSTR,
	       hkAssoc: HKEY,
	      pszExtra: LPCSTR,
		pszOut: LPSTR,
	       pcchOut: ptr DWORD

;LWSTDAPI
AssocQueryStringByKeyW proto WINAPI \
		 flags: ASSOCF,
		  _str: ASSOCSTR,
	       hkAssoc: HKEY,
	      pszExtra: LPCWSTR,
		pszOut: LPWSTR,
	       pcchOut: ptr DWORD

ifdef _UNICODE
AssocQueryStringByKey	equ <AssocQueryStringByKeyW>
else
AssocQueryStringByKey	equ <AssocQueryStringByKeyA>
endif
;LWSTDAPI
AssocQueryKeyA proto WINAPI \
		 flags: ASSOCF,
		   key: ASSOCKEY,
	      pszAssoc: LPCSTR,
	      pszExtra: LPCSTR,
	      phkeyOut: ptr HKEY

;LWSTDAPI
AssocQueryKeyW proto WINAPI \
		 flags: ASSOCF,
		   key: ASSOCKEY,
	      pszAssoc: LPCWSTR,
	      pszExtra: LPCWSTR,
	      phkeyOut: ptr HKEY

ifdef _UNICODE
AssocQueryKey		equ <AssocQueryKeyW>
else
AssocQueryKey		equ <AssocQueryKeyA>
endif

if (_WIN32_IE GE 0x0601)
;LWSTDAPI
AssocIsDangerous proto WINAPI \
	      pszAssoc: LPCWSTR
endif

if (_WIN32_IE GE _WIN32_IE_IE60SP2)
;LWSTDAPI
AssocGetPerceivedType proto WINAPI \
		pszExt: LPCWSTR,
		 ptype: ptr PERCEIVED,
		 pflag: ptr PERCEIVEDFLAG,
	      ppszType: ptr LPWSTR
endif

endif ;; NO_SHLWAPI_REG

ifndef NO_SHLWAPI_STREAM

ifndef __IStream_FWD_DEFINED__
__IStream_FWD_DEFINED__ equ 1
endif

;LWSTDAPI
SHOpenRegStreamA proto WINAPI \
		  hkey: HKEY,
	     pszSubkey: LPCSTR,
	      pszValue: LPCSTR,
	       grfMode: DWORD

;LWSTDAPI
SHOpenRegStreamW proto WINAPI \
		  hkey: HKEY,
	     pszSubkey: LPCWSTR,
	      pszValue: LPCWSTR,
	       grfMode: DWORD

ifdef _UNICODE
SHOpenRegStream		equ <SHOpenRegStreamW>
else
SHOpenRegStream		equ <SHOpenRegStreamA>
endif
;LWSTDAPI
SHOpenRegStream2A proto WINAPI \
		  hkey: HKEY,
	     pszSubkey: LPCSTR,
	      pszValue: LPCSTR,
	       grfMode: DWORD

;LWSTDAPI
SHOpenRegStream2W proto WINAPI \
		  hkey: HKEY,
	     pszSubkey: LPCWSTR,
	      pszValue: LPCWSTR,
	       grfMode: DWORD

ifdef _UNICODE
SHOpenRegStream2	equ <SHOpenRegStream2W>
else
SHOpenRegStream2	equ <SHOpenRegStream2A>
endif
SHOpenRegStream		equ <SHOpenRegStream2>

;LWSTDAPI
SHCreateStreamOnFileA proto WINAPI \
	       pszFile: LPCSTR,
	       grfMode: DWORD,
		 ppstm: ptr IStream

;LWSTDAPI
SHCreateStreamOnFileW proto WINAPI \
	       pszFile: LPCWSTR,
	       grfMode: DWORD,
		 ppstm: ptr IStream

ifdef _UNICODE
SHCreateStreamOnFile	equ <SHCreateStreamOnFileW>
else
SHCreateStreamOnFile	equ <SHCreateStreamOnFileA>
endif


if (_WIN32_IE GE 0x0600)

;LWSTDAPI
SHCreateStreamOnFileEx proto WINAPI \
	       pszFile: LPCWSTR,
	       grfMode: DWORD,
	  dwAttributes: DWORD,
	       fCreate: BOOL,
	  pstmTemplate: ptr IStream,
		 ppstm: ptr IStream

endif

if (_WIN32_IE GE _WIN32_IE_IE501)

;LWSTDAPI
SHCreateMemStream proto WINAPI \
		 pInit: ptr BYTE,
		cbInit: UINT

endif
endif ;; NO_SHLWAPI_STREAM

ifndef NO_SHLWAPI_HTTP
if (_WIN32_IE GE 0x0603)
;LWSTDAPI
GetAcceptLanguagesA proto WINAPI \
		   psz: LPSTR,
		  pcch: ptr DWORD
GetAcceptLanguagesW proto WINAPI \
		   psz: LPWSTR,
		  pcch: ptr DWORD
ifdef _UNICODE
GetAcceptLanguages	equ <GetAcceptLanguagesW>
else
GetAcceptLanguages	equ <GetAcceptLanguagesA>
endif
endif ;; (_WIN32_IE >= 0x0603)
endif ;; NO_SHLWAPI_HTTP


if (_WIN32_IE LT _WIN32_IE_IE70) AND NOT defined(NO_SHLWAPI_STOPWATCH)

SPMODE_SHELL		equ 0x00000001
SPMODE_DEBUGOUT		equ 0x00000002
SPMODE_TEST		equ 0x00000004
SPMODE_BROWSER		equ 0x00000008
SPMODE_FLUSH		equ 0x00000010
SPMODE_EVENT		equ 0x00000020
SPMODE_MSVM		equ 0x00000040
SPMODE_FORMATTEXT	equ 0x00000080
SPMODE_PROFILE		equ 0x00000100
SPMODE_DEBUGBREAK	equ 0x00000200
SPMODE_MSGTRACE		equ 0x00000400
SPMODE_PERFTAGS		equ 0x00000800
SPMODE_MEMWATCH		equ 0x00001000
SPMODE_DBMON		equ 0x00002000
SPMODE_MULTISTOP	equ 0x00004000
ifndef NO_ETW_TRACING
SPMODE_EVENTTRACE	equ 0x00008000
endif

;DWORD
StopWatchMode proto WINAPI
;DWORD
StopWatchFlush proto WINAPI

endif


if (_WIN32_IE GE _WIN32_IE_IE501)

;LWSTDAPI
IUnknown_Set proto WINAPI \
		 ppunk: ptr IUnknown,
		  punk: ptr IUnknown

;LWSTDAPI
IUnknown_AtomicRelease proto WINAPI \
		 ppunk: PVOID

;LWSTDAPI
IUnknown_GetWindow proto WINAPI \
		  punk: ptr IUnknown,
		 phwnd: ptr HWND

;LWSTDAPI
IUnknown_SetSite proto WINAPI \
		  punk: ptr IUnknown,
	      punkSite: ptr IUnknown

;LWSTDAPI
IUnknown_GetSite proto WINAPI \
		  punk: ptr IUnknown,
		  riid: REFIID,
		   ppv: PVOID

;LWSTDAPI
IUnknown_QueryService proto WINAPI \
		  punk: ptr IUnknown,
	   guidService: REFGUID,
		  riid: REFIID,
		ppvOut: PVOID

endif

if (_WIN32_IE GE _WIN32_IE_IE501)

;LWSTDAPI
IStream_Read proto WINAPI \
		  pstm: ptr IStream,
		    pv: PVOID,
		    cb: ULONG

;LWSTDAPI
IStream_Write proto WINAPI \
		  pstm: ptr IStream,
		    pv: PVOID,
		    cb: ULONG

;LWSTDAPI
IStream_Reset proto WINAPI \
		  pstm: ptr IStream

;LWSTDAPI
IStream_Size proto WINAPI \
		  pstm: ptr IStream,
		   pui: ptr ULARGE_INTEGER


ifndef __IConnectionPoint_FWD_DEFINED__
__IConnectionPoint_FWD_DEFINED__ equ 1
endif

;LWSTDAPI
ConnectToConnectionPoint proto WINAPI \
		  punk: ptr IUnknown,
	     riidEvent: REFIID,
	      fConnect: BOOL,
	    punkTarget: ptr IUnknown,
	     pdwCookie: ptr DWORD,
	       ppcpOut: ptr IConnectionPoint


endif ;; (_WIN32_IE >= _WIN32_IE_IE501)

if (_WIN32_IE GE _WIN32_IE_IE60)

;LWSTDAPI
IStream_ReadPidl proto WINAPI \
		  pstm: ptr IStream,
	      ppidlOut: ptr PIDLIST_RELATIVE

;LWSTDAPI
IStream_WritePidl proto WINAPI \
		  pstm: ptr IStream,
	     pidlWrite: PCUIDLIST_RELATIVE


endif

if (_WIN32_IE GE _WIN32_IE_IE70)

;LWSTDAPI
IStream_ReadStr proto WINAPI \
		  pstm: ptr IStream,
		  ppsz: ptr PWSTR

;LWSTDAPI
IStream_WriteStr proto WINAPI \
		  pstm: ptr IStream,
		   psz: PCWSTR


;LWSTDAPI
IStream_Copy proto WINAPI \
	      pstmFrom: ptr IStream,
		pstmTo: ptr IStream,
		    cb: DWORD

endif

if (_WIN32_IE GE 0x0600)
SHGVSPB_PERUSER		equ 0x00000001
SHGVSPB_ALLUSERS	equ 0x00000002
SHGVSPB_PERFOLDER	equ 0x00000004
SHGVSPB_ALLFOLDERS	equ 0x00000008
SHGVSPB_INHERIT		equ 0x00000010
SHGVSPB_ROAM		equ 0x00000020
SHGVSPB_NOAUTODEFAULTS	equ 0x80000000

SHGVSPB_FOLDER		equ (SHGVSPB_PERUSER OR SHGVSPB_PERFOLDER)
SHGVSPB_FOLDERNODEFAULTS equ (SHGVSPB_PERUSER OR SHGVSPB_PERFOLDER OR SHGVSPB_NOAUTODEFAULTS)
SHGVSPB_USERDEFAULTS	equ (SHGVSPB_PERUSER OR SHGVSPB_ALLFOLDERS)
SHGVSPB_GLOBALDEFAULTS	equ (SHGVSPB_ALLUSERS OR SHGVSPB_ALLFOLDERS)

;LWSTDAPI
SHGetViewStatePropertyBag proto WINAPI \
		  pidl: PCIDLIST_ABSOLUTE,
	    pszBagName: LPCWSTR,
	       dwFlags: DWORD,
		  riid: REFIID,
		   ppv: ptr PVOID

endif

FDTF_SHORTTIME		equ 0x00000001
FDTF_SHORTDATE		equ 0x00000002
FDTF_DEFAULT		equ (FDTF_SHORTDATE OR FDTF_SHORTTIME)
FDTF_LONGDATE		equ 0x00000004
FDTF_LONGTIME		equ 0x00000008
FDTF_RELATIVE		equ 0x00000010
FDTF_LTRDATE		equ 0x00000100
FDTF_RTLDATE		equ 0x00000200
FDTF_NOAUTOREADINGORDER equ 0x00000400

;LWSTDAPI
SHFormatDateTimeA proto WINAPI \
		   pft: ptr FILETIME,
	      pdwFlags: ptr DWORD,
		pszBuf: LPSTR,
		cchBuf: UINT

;LWSTDAPI
SHFormatDateTimeW proto WINAPI \
		   pft: ptr FILETIME,
	      pdwFlags: ptr DWORD,
		pszBuf: LPWSTR,
		cchBuf: UINT

ifdef _UNICODE
SHFormatDateTime	equ <SHFormatDateTimeW>
else
SHFormatDateTime	equ <SHFormatDateTimeA>
endif

if (_WIN32_IE GE _WIN32_IE_IE501)


;LWSTDAPI
SHAnsiToUnicode proto WINAPI \
		pszSrc: LPCSTR,
	       pwszDst: LPWSTR,
	       cwchBuf: SINT


;LWSTDAPI
SHAnsiToAnsi proto WINAPI \
		pszSrc: LPCSTR,
		pszDst: LPSTR,
		cchBuf: SINT


;LWSTDAPI
SHUnicodeToAnsi proto WINAPI \
	       pwszSrc: LPCWSTR,
		pszDst: LPSTR,
		cchBuf: SINT


;LWSTDAPI
SHUnicodeToUnicode proto WINAPI \
		pwzSrc: LPCWSTR,
		pwzDst: LPWSTR,
	       cwchBuf: SINT


ifdef _UNICODE
SHTCharToUnicode macro wzSrc, wzDest, cchSize
	exitm<SHUnicodeToUnicode(wzSrc, wzDest, cchSize)>
	endm
SHTCharToAnsi macro wzSrc, szDest, cchSize
	exitm<SHUnicodeToAnsi(wzSrc, szDest, cchSize)>
	endm
SHUnicodeToTChar macro wzSrc, wzDest, cchSize
	exitm<SHUnicodeToUnicode(wzSrc, wzDest, cchSize)>
	endm
SHAnsiToTChar macro szSrc, wzDest, cchSize
	exitm<SHAnsiToUnicode(szSrc, wzDest, cchSize)>
	endm
else
SHTCharToUnicode macro szSrc, wzDest, cchSize
	exitm<SHAnsiToUnicode(szSrc, wzDest, cchSize)>
	endm
SHTCharToAnsi macro szSrc, szDest, cchSize
	exitm<SHAnsiToAnsi(szSrc, szDest, cchSize)>
	endm
SHUnicodeToTChar macro wzSrc, szDest, cchSize
	exitm<SHUnicodeToAnsi(wzSrc, szDest, cchSize)>
	endm
SHAnsiToTChar macro szSrc, szDest, cchSize
	exitm<SHAnsiToAnsi(szSrc, szDest, cchSize)>
	endm
endif

endif ;; (_WIN32_IE >= _WIN32_IE_IE501)


if (_WIN32_IE GE _WIN32_IE_IE501)

;LWSTDAPI
SHMessageBoxCheckA proto WINAPI \
		  hwnd: HWND,
	       pszText: LPCSTR,
	    pszCaption: LPCSTR,
		 uType: UINT,
	      iDefault: SINT,
	     pszRegVal: LPCSTR

;LWSTDAPI
SHMessageBoxCheckW proto WINAPI \
		  hwnd: HWND,
	       pszText: LPCWSTR,
	    pszCaption: LPCWSTR,
		 uType: UINT,
	      iDefault: SINT,
	     pszRegVal: LPCWSTR

ifdef _UNICODE
SHMessageBoxCheck	equ <SHMessageBoxCheckW>
else
SHMessageBoxCheck	equ <SHMessageBoxCheckA>
endif

endif


if (_WIN32_IE GE _WIN32_IE_IE501)

;LWSTDAPI
SHSendMessageBroadcastA proto WINAPI \
		  uMsg: UINT,
		wParam: WPARAM,
		lParam: LPARAM

;LWSTDAPI
SHSendMessageBroadcastW proto WINAPI \
		  uMsg: UINT,
		wParam: WPARAM,
		lParam: LPARAM

ifdef _UNICODE
SHSendMessageBroadcast	equ <SHSendMessageBroadcastW>
else
SHSendMessageBroadcast	equ <SHSendMessageBroadcastA>
endif

;LWSTDAPI
SHStripMneumonicA proto WINAPI \
	       pszMenu: LPSTR

;LWSTDAPI
SHStripMneumonicW proto WINAPI \
	       pszMenu: LPWSTR

ifdef _UNICODE
SHStripMneumonic	equ <SHStripMneumonicW>
else
SHStripMneumonic	equ <SHStripMneumonicA>
endif

ifndef NO_SHLWAPI_ISOS

OS_WINDOWS		equ 0
OS_NT			equ 1
OS_WIN95ORGREATER	equ 2
OS_NT4ORGREATER		equ 3
OS_WIN98ORGREATER	equ 5
OS_WIN98_GOLD		equ 6
OS_WIN2000ORGREATER	equ 7

OS_WIN2000PRO		equ 8
OS_WIN2000SERVER	equ 9
OS_WIN2000ADVSERVER	equ 10
OS_WIN2000DATACENTER	equ 11
OS_WIN2000TERMINAL	equ 12

OS_EMBEDDED		equ 13
OS_TERMINALCLIENT	equ 14
OS_TERMINALREMOTEADMIN	equ 15
OS_WIN95_GOLD		equ 16
OS_MEORGREATER		equ 17
OS_XPORGREATER		equ 18
OS_HOME			equ 19
OS_PROFESSIONAL		equ 20
OS_DATACENTER		equ 21
OS_ADVSERVER		equ 22
OS_SERVER		equ 23
OS_TERMINALSERVER	equ 24
OS_PERSONALTERMINALSERVER equ 25
OS_FASTUSERSWITCHING	equ 26
OS_WELCOMELOGONUI	equ 27
OS_DOMAINMEMBER		equ 28
OS_ANYSERVER		equ 29
OS_WOW6432		equ 30
OS_WEBSERVER		equ 31
OS_SMALLBUSINESSSERVER	equ 32
OS_TABLETPC		equ 33
OS_SERVERADMINUI	equ 34
OS_MEDIACENTER		equ 35
OS_APPLIANCE		equ 36

;LWSTDAPI
IsOS proto WINAPI \
		  dwOS: DWORD

endif ;; NO_SHLWAPI_ISOS
endif ;; (_WIN32_IE >= _WIN32_IE_IE501)


GLOBALCOUNTER_SEARCHMANAGER equ 0
GLOBALCOUNTER_SEARCHOPTIONS equ 1
GLOBALCOUNTER_FOLDERSETTINGSCHANGE equ 2
GLOBALCOUNTER_RATINGS	equ 3
GLOBALCOUNTER_APPROVEDSITES equ 4
GLOBALCOUNTER_RESTRICTIONS equ 5
GLOBALCOUNTER_SHELLSETTINGSCHANGED equ 6
GLOBALCOUNTER_SYSTEMPIDLCHANGE equ 7
GLOBALCOUNTER_OVERLAYMANAGER equ 8
GLOBALCOUNTER_QUERYASSOCIATIONS equ 9
GLOBALCOUNTER_IESESSIONS equ 10
GLOBALCOUNTER_IEONLY_SESSIONS equ 11
GLOBALCOUNTER_APPLICATION_DESTINATIONS equ 12
__UNUSED_RECYCLE_WAS_GLOBALCOUNTER_CSCSYNCINPROGRESS equ 13
GLOBALCOUNTER_BITBUCKETNUMDELETERS equ 14
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_SHARES equ 15
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_A equ 16
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_B equ 17
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_C equ 18
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_D equ 19
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_E equ 20
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_F equ 21
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_G equ 22
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_H equ 23
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_I equ 24
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_J equ 25
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_K equ 26
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_L equ 27
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_M equ 28
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_N equ 29
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_O equ 30
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_P equ 31
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_Q equ 32
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_R equ 33
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_S equ 34
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_T equ 35
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_U equ 36
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_V equ 37
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_W equ 38
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_X equ 39
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_Y equ 40
GLOBALCOUNTER_RECYCLEDIRTYCOUNT_DRIVE_Z equ 41
__UNUSED_RECYCLE_WAS_GLOBALCOUNTER_RECYCLEDIRTYCOUNT_SERVERDRIVE equ 42
__UNUSED_RECYCLE_WAS_GLOBALCOUNTER_RECYCLEGLOBALDIRTYCOUNT equ 43
GLOBALCOUNTER_RECYCLEBINENUM equ 44
GLOBALCOUNTER_RECYCLEBINCORRUPTED equ 45
GLOBALCOUNTER_RATINGS_STATECOUNTER equ 46
GLOBALCOUNTER_PRIVATE_PROFILE_CACHE equ 47
GLOBALCOUNTER_INTERNETTOOLBAR_LAYOUT equ 48
GLOBALCOUNTER_FOLDERDEFINITION_CACHE equ 49
GLOBALCOUNTER_COMMONPLACES_LIST_CACHE equ 50
GLOBALCOUNTER_PRIVATE_PROFILE_CACHE_MACHINEWIDE equ 51
GLOBALCOUNTER_ASSOCCHANGED equ 52
GLOBALCOUNTER_MAXIMUMVALUE equ 53

SHGLOBALCOUNTER		typedef SDWORD

;LWSTDAPI
SHGlobalCounterGetValue proto WINAPI \
		    id: SHGLOBALCOUNTER

;LWSTDAPI
SHGlobalCounterIncrement proto WINAPI \
		    id: SHGLOBALCOUNTER

;LWSTDAPI
SHGlobalCounterDecrement proto WINAPI \
		    id: SHGLOBALCOUNTER

if (_WIN32_IE GE 0x0603)
;LWSTDAPI
SHAllocShared proto WINAPI \
		pvData: PVOID,
		dwSize: DWORD,
	   dwProcessId: DWORD

;LWSTDAPI
SHFreeShared proto WINAPI \
		 hData: HANDLE,
	   dwProcessId: DWORD

;LWSTDAPI
SHLockShared proto WINAPI \
		 hData: HANDLE,
	   dwProcessId: DWORD

;LWSTDAPI
SHUnlockShared proto WINAPI \
		pvData: PVOID

endif


if (_WIN32_IE GE _WIN32_IE_IE501)

;LWSTDAPI
WhichPlatform proto WINAPI

PLATFORM_UNKNOWN	equ 0
PLATFORM_IE3		equ 1
PLATFORM_BROWSERONLY	equ 1
PLATFORM_INTEGRATED	equ 2


QITAB			STRUC
piid			LPIID ?
dwOffset		SINT ?
QITAB			ENDS
LPQITAB			typedef ptr QITAB
LPCQITAB		typedef ptr QITAB

QITABENTMULTI macro Cthis, Ifoo, Iimpl
	exitm<{IID_&Ifoo&, OFFSETOFCLASS(Iimpl, Cthis)}>
	endm


QITABENTMULTI2 macro Cthis, Ifoo, Iimpl
	exitm<{Ifoo, OFFSETOFCLASS(Iimpl, Cthis)}>
	endm

QITABENT macro Cthis, Ifoo
	exitm<QITABENTMULTI(Cthis, Ifoo, Ifoo)>
	endm

;STDAPI
QISearch proto WINAPI \
		  that: PVOID,
		  pqit: LPCQITAB,
		  riid: REFIID,
		   ppv: PVOID


endif ;; (_WIN32_IE >= _WIN32_IE_IE501)

ifndef STATIC_CAST
STATIC_CAST macro typ
	exitm<typ>
	endm
ifndef _X86_
STATIC_CAST macro typ
	exitm<(typ)>
	endm
endif
endif

ifndef OFFSETOFCLASS

OFFSETOFCLASS macro base, derived
	exitm<0>
	endm
endif


ILMM_IE4		equ 0
;LWSTDAPI
SHIsLowMemoryMachine proto WINAPI \
		dwType: DWORD


;LWSTDAPI
GetMenuPosFromID proto WINAPI \
		 hmenu: HMENU,
		    id: UINT


;LWSTDAPI
SHGetInverseCMAP proto WINAPI \
		 pbMap: ptr BYTE,
		 cbMap: ULONG



if (_WIN32_IE GE 0x0500)

SHACF_DEFAULT		equ 0x00000000
SHACF_FILESYSTEM	equ 0x00000001
SHACF_URLALL		equ (SHACF_URLHISTORY OR SHACF_URLMRU)
SHACF_URLHISTORY	equ 0x00000002
SHACF_URLMRU		equ 0x00000004
SHACF_USETAB		equ 0x00000008
SHACF_FILESYS_ONLY	equ 0x00000010
if (_WIN32_IE GE 0x0600)
SHACF_FILESYS_DIRS	equ 0x00000020
endif
if (_WIN32_IE GE _WIN32_IE_IE70)
SHACF_VIRTUAL_NAMESPACE equ 0x00000040
endif
SHACF_AUTOSUGGEST_FORCE_ON equ 0x10000000
SHACF_AUTOSUGGEST_FORCE_OFF equ 0x20000000
SHACF_AUTOAPPEND_FORCE_ON equ 0x40000000
SHACF_AUTOAPPEND_FORCE_OFF equ 0x80000000

;LWSTDAPI
SHAutoComplete proto WINAPI \
	      hwndEdit: HWND,
	       dwFlags: DWORD


if (_WIN32_IE GE _WIN32_IE_IE60SP2)
;LWSTDAPI
SHCreateThreadRef proto WINAPI \
		 pcRef: ptr LONG,
		 ppunk: ptr IUnknown
endif

;LWSTDAPI
SHSetThreadRef proto WINAPI \
		  punk: ptr IUnknown
SHGetThreadRef proto WINAPI \
		 ppunk: ptr IUnknown
SHSkipJunction proto WINAPI \
		   pbc: ptr IBindCtx,
		pclsid: ptr CLSID

endif ;; (_WIN32_IE >= 0x0500)

CTF_INSIST		equ 0x00000001
CTF_THREAD_REF		equ 0x00000002
CTF_PROCESS_REF		equ 0x00000004
CTF_COINIT_STA		equ 0x00000008
CTF_COINIT		equ 0x00000008
if (_WIN32_IE GE _WIN32_IE_IE60)
CTF_FREELIBANDEXIT	equ 0x00000010
CTF_REF_COUNTED		equ 0x00000020
CTF_WAIT_ALLOWCOM	equ 0x00000040
endif
if (_WIN32_IE GE _WIN32_IE_IE70)
CTF_UNUSED		equ 0x00000080
CTF_INHERITWOW64	equ 0x00000100
endif
if (NTDDI_VERSION GE NTDDI_VISTA)
CTF_WAIT_NO_REENTRANCY	equ 0x00000200
endif
if (NTDDI_VERSION GE NTDDI_WIN7)
CTF_KEYBOARD_LOCALE	equ 0x00000400
CTF_OLEINITIALIZE	equ 0x00000800
CTF_COINIT_MTA		equ 0x00001000
CTF_NOADDREFLIB		equ 0x00002000
endif

SHCT_FLAGS		typedef DWORD

;LWSTDAPI
SHCreateThread proto WINAPI \
	 pfnThreadProc: LPTHREAD_START_ROUTINE,
		 pData: PVOID,
		 flags: SHCT_FLAGS,
	   pfnCallback: LPTHREAD_START_ROUTINE

;LWSTDAPI
SHCreateThreadWithHandle proto WINAPI \
	 pfnThreadProc: LPTHREAD_START_ROUTINE,
		 pData: PVOID,
		 flags: SHCT_FLAGS,
	   pfnCallback: LPTHREAD_START_ROUTINE,
	       pHandle: ptr HANDLE


if (_WIN32_IE GE _WIN32_IE_IE60)
;LWSTDAPI
SHReleaseThreadRef proto WINAPI
endif

ifndef NO_SHLWAPI_GDI

;LWSTDAPI_(HPALETTE)
SHCreateShellPalette proto WINAPI \
		   hdc: HDC


if (_WIN32_IE GE 0x0500)

;LWSTDAPI
ColorRGBToHLS proto WINAPI \
		clrRGB: COLORREF,
		 pwHue: ptr WORD,
	   pwLuminance: ptr WORD,
	  pwSaturation: ptr WORD

;LWSTDAPI_(COLORREF)
ColorHLSToRGB proto WINAPI \
		  wHue: WORD,
	    wLuminance: WORD,
	   wSaturation: WORD

;LWSTDAPI_(COLORREF)
ColorAdjustLuma proto WINAPI \
		clrRGB: COLORREF,
		     n: SINT,
	       _fScale: BOOL

endif
endif

DLLVERSIONINFO		STRUC
cbSize			dd ?
dwMajorVersion		dd ?
dwMinorVersion		dd ?
dwBuildNumber		dd ?
dwPlatformID		dd ?
DLLVERSIONINFO		ENDS

DLLVER_PLATFORM_WINDOWS equ 0x00000001
DLLVER_PLATFORM_NT	equ 0x00000002

if (_WIN32_IE GE 0x0501)

DLLVERSIONINFO2		STRUC
info1			DLLVERSIONINFO <>
dwFlags			dd ?
ullVersion		ULONGLONG ?
DLLVERSIONINFO2		ENDS

DLLVER_MAJOR_MASK	equ 0xFFFF000000000000
DLLVER_MINOR_MASK	equ 0x0000FFFF00000000
DLLVER_BUILD_MASK	equ 0x00000000FFFF0000
DLLVER_QFE_MASK		equ 0x000000000000FFFF

endif

MAKEDLLVERULL macro major, minor, build, qfe
	exitm<(major shl 48) or (minor shl 32) or (build shl 16) or (qfe)>
	endm

CALLBACK(DLLGETVERSIONPROC, :ptr DLLVERSIONINFO)

;STDAPI
DllInstall proto WINAPI \
	      bInstall: BOOL,
	    pszCmdLine: LPCWSTR

if (_WIN32_IE GE 0x0602)
;LWSTDAPI
IsInternetESCEnabled proto WINAPI
endif

ifdef _WIN32
.pragma pack(pop)
endif

endif

.pragma list(pop)
endif

