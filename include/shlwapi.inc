.pragma list(push, 0)
ifndef _INC_SHLWAPI
define _INC_SHLWAPI

ifndef __LIBC_INC
 include libc.inc
endif
ifndef NOSHLWAPI
include specstrings.inc
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

if defined(__cplusplus) AND defined(STRICT_CONST)
USE_STRICT_CONST equ 1
endif

ifndef NO_SHLWAPI_STRFCNS

ifdef USE_STRICT_CONST
if (_WIN32_IE GE _WIN32_IE_IE60)
endif
else
StrChrA proto WINAPI :LPCSTR, :WORD
StrChrW proto WINAPI :LPCWSTR, :WCHAR
StrChrIA proto WINAPI :LPCSTR, :WORD
StrChrIW proto WINAPI :LPCWSTR, :WCHAR
if (_WIN32_IE GT _WIN32_IE_IE60)
StrChrNW proto WINAPI :LPCWSTR, :WCHAR, :UINT
StrChrNIW proto WINAPI :LPCWSTR, :WCHAR, :UINT
endif
endif

StrCmpNA proto WINAPI :LPCSTR, :LPCSTR, :SINT
StrCmpNW proto WINAPI :LPCWSTR, :LPCWSTR, :SINT
StrCmpNIA proto WINAPI :LPCSTR, :LPCSTR, :SINT
StrCmpNIW proto WINAPI :LPCWSTR, :LPCWSTR, :SINT
StrCSpnA proto WINAPI :LPCSTR, :LPCSTR
StrCSpnW proto WINAPI :LPCWSTR, :LPCWSTR
StrCSpnIA proto WINAPI :LPCSTR, :LPCSTR
StrCSpnIW proto WINAPI :LPCWSTR, :LPCWSTR
StrDupA proto WINAPI :LPCSTR
StrDupW proto WINAPI :LPCWSTR

tagSFBS_FLAGS		typedef SDWORD
SFBS_FLAGS_ROUND_TO_NEAREST_DISPLAYED_DIGIT equ 0x0001
SFBS_FLAGS_TRUNCATE_UNDISPLAYED_DECIMAL_DIGITS equ 0x0002
SFBS_FLAGS		typedef SINT

StrFormatByteSizeEx proto WINAPI :ULONGLONG, :SFBS_FLAGS, :LPWSTR, :UINT
StrFormatByteSizeA proto WINAPI :DWORD, :LPSTR, :UINT
StrFormatByteSize64A proto WINAPI :LONGLONG, :LPSTR, :UINT
StrFormatByteSizeW proto WINAPI :LONGLONG, :LPWSTR, :UINT
StrFormatKBSizeW proto WINAPI :LONGLONG, :LPWSTR, :UINT
StrFormatKBSizeA proto WINAPI :LONGLONG, :LPSTR, :UINT
StrFromTimeIntervalA proto WINAPI :LPSTR, :UINT, :DWORD, :SINT
StrFromTimeIntervalW proto WINAPI :LPWSTR, :UINT, :DWORD, :SINT
StrIsIntlEqualA proto WINAPI :BOOL, :LPCSTR, :LPCSTR, :SINT
StrIsIntlEqualW proto WINAPI :BOOL, :LPCWSTR, :LPCWSTR, :SINT
StrNCatA proto WINAPI :LPSTR, :LPCSTR, :SINT
StrNCatW proto WINAPI :LPWSTR, :LPCWSTR, :SINT

ifdef USE_STRICT_CONST
else
StrPBrkA proto WINAPI :LPCSTR, :LPCSTR
StrPBrkW proto WINAPI :LPCWSTR, :LPCWSTR
StrRChrA proto WINAPI :LPCSTR, :LPCSTR, :WORD
StrRChrW proto WINAPI :LPCWSTR, :LPCWSTR, :WCHAR
StrRChrIA proto WINAPI :LPCSTR, :LPCSTR, :WORD
StrRChrIW proto WINAPI :LPCWSTR, :LPCWSTR, :WCHAR
StrRStrIA proto WINAPI :LPCSTR, :LPCSTR, :LPCSTR
StrRStrIW proto WINAPI :LPCWSTR, :LPCWSTR, :LPCWSTR
endif

StrSpnA proto WINAPI :LPCSTR, :LPCSTR
StrSpnW proto WINAPI :LPCWSTR, :LPCWSTR

ifdef USE_STRICT_CONST
else
StrStrA proto WINAPI :LPCSTR, :LPCSTR
StrStrW proto WINAPI :LPCWSTR, :LPCWSTR
StrStrIA proto WINAPI :LPCSTR, :LPCSTR
StrStrIW proto WINAPI :LPCWSTR, :LPCWSTR

if (_WIN32_IE GE _WIN32_IE_IE60)
StrStrNW proto WINAPI :LPCWSTR, :LPCWSTR, :UINT
StrStrNIW proto WINAPI :LPCWSTR, :LPCWSTR, :UINT
endif
endif

STIF_DEFAULT		equ 0x00000000
STIF_SUPPORT_HEX	equ 0x00000001
STIF_FLAGS		typedef SINT

StrToIntA proto WINAPI :LPCSTR
StrToIntW proto WINAPI :LPCWSTR
StrToIntExA proto WINAPI :LPCSTR, :STIF_FLAGS, :ptr
StrToIntExW proto WINAPI :LPCWSTR, :STIF_FLAGS, :ptr

if (_WIN32_IE GE _WIN32_IE_IE60)
StrToInt64ExA proto WINAPI :LPCSTR, :STIF_FLAGS, :ptr
StrToInt64ExW proto WINAPI :LPCWSTR, :STIF_FLAGS, :ptr
endif
StrTrimA proto WINAPI :LPSTR, :LPCSTR
StrTrimW proto WINAPI :LPWSTR, :LPCWSTR
StrCatW proto WINAPI :LPWSTR, :LPCWSTR
StrCmpW proto WINAPI :LPCWSTR, :LPCWSTR
StrCmpIW proto WINAPI :LPCWSTR, :LPCWSTR
StrCpyW proto WINAPI :LPWSTR, :LPCWSTR
StrCpyNW proto WINAPI :LPWSTR, :LPCWSTR, :SINT
StrCatBuffW proto WINAPI :LPWSTR, :LPCWSTR, :SINT
StrCatBuffA proto WINAPI :LPSTR, :LPCSTR, :SINT
ChrCmpIA proto WINAPI :WORD, :WORD
ChrCmpIW proto WINAPI :WCHAR, :WCHAR
wvnsprintfA proto WINAPI :LPSTR, :SINT, :LPCSTR, :va_list
wvnsprintfW proto WINAPI :LPWSTR, :SINT, :LPCWSTR, :va_list
wnsprintfA proto __Cdecl :LPSTR, :SINT, :LPCSTR, :VARARG
wnsprintfW proto __Cdecl :LPWSTR, :SINT, :LPCWSTR, :VARARG

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

StrRetToStrA proto WINAPI :ptr, :PCUITEMID_CHILD, :ptr
StrRetToStrW proto WINAPI :ptr, :PCUITEMID_CHILD, :ptr
ifdef _UNICODE
StrRetToStr		equ <StrRetToStrW>
else
StrRetToStr		equ <StrRetToStrA>
endif

StrRetToBufA proto WINAPI :ptr, :PCUITEMID_CHILD, :LPSTR, :UINT
StrRetToBufW proto WINAPI :ptr, :PCUITEMID_CHILD, :LPWSTR, :UINT
ifdef _UNICODE
StrRetToBuf		equ <StrRetToBufW>
else
StrRetToBuf		equ <StrRetToBufA>
endif
SHStrDupA proto WINAPI :LPCSTR, :ptr
SHStrDupW proto WINAPI :LPCWSTR, :ptr
ifdef _UNICODE
SHStrDup		equ <SHStrDupW>
else
SHStrDup		equ <SHStrDupA>
endif

if (_WIN32_IE GE _WIN32_IE_IE55)
StrCmpLogicalW proto WINAPI :LPCWSTR, :LPCWSTR
StrCatChainW proto WINAPI :LPWSTR, :DWORD, :DWORD, :LPCWSTR
StrRetToBSTR proto WINAPI :ptr, :PCUITEMID_CHILD, :ptr
SHLoadIndirectString proto WINAPI :LPCWSTR, :LPWSTR, :UINT, :ptr
endif

if (_WIN32_IE GE _WIN32_IE_IE60SP2)
IsCharSpaceA proto WINAPI :CHAR
IsCharSpaceW proto WINAPI :WCHAR
ifdef _UNICODE
IsCharSpace		equ <IsCharSpaceW>
else
IsCharSpace		equ <IsCharSpaceA>
endif
StrCmpCA proto WINAPI :LPCSTR, :LPCSTR
StrCmpCW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
StrCmpC			equ <StrCmpCW>
else
StrCmpC			equ <StrCmpCA>
endif

StrCmpICA proto WINAPI :LPCSTR, :LPCSTR
StrCmpICW proto WINAPI :LPCWSTR, :LPCWSTR
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
StrCmpNCA proto WINAPI :LPCSTR, :LPCSTR, :SINT
StrCmpNCW proto WINAPI :LPCWSTR, :LPCWSTR, :SINT
ifdef _UNICODE
StrCmpNC		equ <StrCmpNCW>
else
StrCmpNC		equ <StrCmpNCA>
endif
StrCmpNICA proto WINAPI :LPCSTR, :LPCSTR, :SINT
StrCmpNICW proto WINAPI :LPCWSTR, :LPCWSTR, :SINT
ifdef _UNICODE
StrCmpNIC		equ <StrCmpNICW>
else
StrCmpNIC		equ <StrCmpNICA>
endif
endif
IntlStrEqWorkerA proto WINAPI :BOOL, :LPCSTR, :LPCSTR, :SINT
IntlStrEqWorkerW proto WINAPI :BOOL, :LPCWSTR, :LPCWSTR, :SINT
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

PathAddBackslashA proto WINAPI :LPSTR
PathAddBackslashW proto WINAPI :LPWSTR
ifdef _UNICODE
PathAddBackslash	equ <PathAddBackslashW>
else
PathAddBackslash	equ <PathAddBackslashA>
endif
PathAddExtensionA proto WINAPI :LPSTR, :LPCSTR
PathAddExtensionW proto WINAPI :LPWSTR, :LPCWSTR
ifdef _UNICODE
PathAddExtension	equ <PathAddExtensionW>
else
PathAddExtension	equ <PathAddExtensionA>
endif

PathAppendA proto WINAPI :LPSTR, :LPCSTR
PathAppendW proto WINAPI :LPWSTR, :LPCWSTR
PathBuildRootA proto WINAPI :LPSTR, :SINT
PathBuildRootW proto WINAPI :LPWSTR, :SINT
ifdef _UNICODE
PathBuildRoot		equ <PathBuildRootW>
else
PathBuildRoot		equ <PathBuildRootA>
endif
PathCanonicalizeA proto WINAPI :LPSTR, :LPCSTR
PathCanonicalizeW proto WINAPI :LPWSTR, :LPCWSTR
PathCombineA proto WINAPI :LPSTR, :LPCSTR, :LPCSTR
PathCombineW proto WINAPI :LPWSTR, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
PathCombine		equ <PathCombineW>
else
PathCombine		equ <PathCombineA>
endif
PathCompactPathA proto WINAPI :HDC, :LPSTR, :UINT
PathCompactPathW proto WINAPI :HDC, :LPWSTR, :UINT
PathCompactPathExA proto WINAPI :LPSTR, :LPCSTR, :UINT, :DWORD
PathCompactPathExW proto WINAPI :LPWSTR, :LPCWSTR, :UINT, :DWORD
PathCommonPrefixA proto WINAPI :LPCSTR, :LPCSTR, :LPSTR
PathCommonPrefixW proto WINAPI :LPCWSTR, :LPCWSTR, :LPWSTR
PathFileExistsA proto WINAPI :LPCSTR
PathFileExistsW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathFileExists		equ <PathFileExistsW>
else
PathFileExists		equ <PathFileExistsA>
endif
ifdef USE_STRICT_CONST
PathFindExtensionA proto WINAPI :LPCSTR
PathFindExtensionW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathFindExtension	equ <PathFindExtensionW>
else
PathFindExtension	equ <PathFindExtensionA>
endif
PathFindFileNameA proto WINAPI :LPCSTR
PathFindFileNameW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathFindFileName	equ <PathFindFileNameW>
else
PathFindFileName	equ <PathFindFileNameA>
endif
PathFindNextComponentA proto WINAPI :LPCSTR
PathFindNextComponentW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathFindNextComponent	equ <PathFindNextComponentW>
else
PathFindNextComponent	equ <PathFindNextComponentA>
endif
else
PathFindExtensionA proto WINAPI :LPCSTR
PathFindExtensionW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathFindExtension	equ <PathFindExtensionW>
else
PathFindExtension	equ <PathFindExtensionA>
endif
PathFindFileNameA proto WINAPI :LPCSTR
PathFindFileNameW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathFindFileName	equ <PathFindFileNameW>
else
PathFindFileName	equ <PathFindFileNameA>
endif
PathFindNextComponentA proto WINAPI :LPCSTR
PathFindNextComponentW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathFindNextComponent	equ <PathFindNextComponentW>
else
PathFindNextComponent	equ <PathFindNextComponentA>
endif
endif ;; USE_STRICT_CONST

PathFindOnPathA proto WINAPI :LPSTR, :PZPCSTR
PathFindOnPathW proto WINAPI :LPWSTR, :PZPCWSTR
PathFindSuffixArrayA proto WINAPI :LPCSTR, :ptr, :SINT
PathFindSuffixArrayW proto WINAPI :LPCWSTR, :ptr, :SINT
ifdef _UNICODE
PathFindSuffixArray	equ <PathFindSuffixArrayW>
else
PathFindSuffixArray	equ <PathFindSuffixArrayA>
endif
ifdef USE_STRICT_CONST
PathGetArgsA proto WINAPI :LPCSTR
PathGetArgsW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathGetArgs		equ <PathGetArgsW>
else
PathGetArgs		equ <PathGetArgsA>
endif
else
PathGetArgsA proto WINAPI :LPCSTR
PathGetArgsW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathGetArgs		equ <PathGetArgsW>
else
PathGetArgs		equ <PathGetArgsA>
endif
endif ;; USE_STRICT_CONST

PathIsLFNFileSpecA proto WINAPI :LPCSTR
PathIsLFNFileSpecW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathIsLFNFileSpec	equ <PathIsLFNFileSpecW>
else
PathIsLFNFileSpec	equ <PathIsLFNFileSpecA>
endif
PathGetCharTypeA proto WINAPI :UCHAR
PathGetCharTypeW proto WINAPI :WCHAR

GCT_INVALID		equ 0x0000
GCT_LFNCHAR		equ 0x0001
GCT_SHORTCHAR		equ 0x0002
GCT_WILD		equ 0x0004
GCT_SEPARATOR		equ 0x0008

PathGetDriveNumberA proto WINAPI :LPCSTR
PathGetDriveNumberW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathGetDriveNumber	equ <PathGetDriveNumberW>
else
PathGetDriveNumber	equ <PathGetDriveNumberA>
endif
PathIsDirectoryA proto WINAPI :LPCSTR
PathIsDirectoryW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathIsDirectory		equ <PathIsDirectoryW>
else
PathIsDirectory		equ <PathIsDirectoryA>
endif
PathIsDirectoryEmptyA proto WINAPI :LPCSTR
PathIsDirectoryEmptyW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathIsDirectoryEmpty	equ <PathIsDirectoryEmptyW>
else
PathIsDirectoryEmpty	equ <PathIsDirectoryEmptyA>
endif
PathIsFileSpecA proto WINAPI :LPCSTR
PathIsFileSpecW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathIsFileSpec		equ <PathIsFileSpecW>
else
PathIsFileSpec		equ <PathIsFileSpecA>
endif
PathIsPrefixA proto WINAPI :LPCSTR, :LPCSTR
PathIsPrefixW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
PathIsPrefix		equ <PathIsPrefixW>
else
PathIsPrefix		equ <PathIsPrefixA>
endif
PathIsRelativeA proto WINAPI :LPCSTR
PathIsRelativeW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathIsRelative		equ <PathIsRelativeW>
else
PathIsRelative		equ <PathIsRelativeA>
endif
PathIsRootA proto WINAPI :LPCSTR
PathIsRootW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathIsRoot		equ <PathIsRootW>
else
PathIsRoot		equ <PathIsRootA>
endif
PathIsSameRootA proto WINAPI :LPCSTR, :LPCSTR
PathIsSameRootW proto WINAPI :LPCWSTR, :LPCWSTR
ifdef _UNICODE
PathIsSameRoot		equ <PathIsSameRootW>
else
PathIsSameRoot		equ <PathIsSameRootA>
endif
PathIsUNCA proto WINAPI :LPCSTR
PathIsUNCW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathIsUNC		equ <PathIsUNCW>
else
PathIsUNC		equ <PathIsUNCA>
endif
PathIsNetworkPathA proto WINAPI :LPCSTR
PathIsNetworkPathW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathIsNetworkPath	equ <PathIsNetworkPathW>
else
PathIsNetworkPath	equ <PathIsNetworkPathA>
endif
PathIsUNCServerA proto WINAPI :LPCSTR
PathIsUNCServerW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathIsUNCServer		equ <PathIsUNCServerW>
else
PathIsUNCServer		equ <PathIsUNCServerA>
endif
PathIsUNCServerShareA proto WINAPI :LPCSTR
PathIsUNCServerShareW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathIsUNCServerShare	equ <PathIsUNCServerShareW>
else
PathIsUNCServerShare	equ <PathIsUNCServerShareA>
endif
PathIsContentTypeA proto WINAPI :LPCSTR, :LPCSTR
PathIsContentTypeW proto WINAPI :LPCWSTR, :LPCWSTR
PathIsURLA proto WINAPI :LPCSTR
PathIsURLW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathIsURL		equ <PathIsURLW>
else
PathIsURL		equ <PathIsURLA>
endif
PathMakePrettyA proto WINAPI :LPSTR
PathMakePrettyW proto WINAPI :LPWSTR
PathMatchSpecA proto WINAPI :LPCSTR, :LPCSTR
PathMatchSpecW proto WINAPI :LPCWSTR, :LPCWSTR
if (_WIN32_IE GE _WIN32_IE_IE70)
PMSF_NORMAL		equ 0x00000000
PMSF_MULTIPLE		equ 0x00000001
PMSF_DONT_STRIP_SPACES	equ 0x00010000

PathMatchSpecExA proto WINAPI :LPCSTR, :LPCSTR, :DWORD
PathMatchSpecExW proto WINAPI :LPCWSTR, :LPCWSTR, :DWORD
endif

PathParseIconLocationA proto WINAPI :LPSTR
PathParseIconLocationW proto WINAPI :LPWSTR
PathQuoteSpacesA proto WINAPI :LPSTR
PathQuoteSpacesW proto WINAPI :LPWSTR
PathRelativePathToA proto WINAPI :LPSTR, :LPCSTR, :DWORD, :LPCSTR, :DWORD
PathRelativePathToW proto WINAPI :LPWSTR, :LPCWSTR, :DWORD, :LPCWSTR, :DWORD
PathRemoveArgsA proto WINAPI :LPSTR
PathRemoveArgsW proto WINAPI :LPWSTR
PathRemoveBackslashA proto WINAPI :LPSTR
PathRemoveBackslashW proto WINAPI :LPWSTR
ifdef _UNICODE
PathRemoveBackslash	equ <PathRemoveBackslashW>
else
PathRemoveBackslash	equ <PathRemoveBackslashA>
endif
PathRemoveBlanksA proto WINAPI :LPSTR
PathRemoveBlanksW proto WINAPI :LPWSTR
PathRemoveExtensionA proto WINAPI :LPSTR
PathRemoveExtensionW proto WINAPI :LPWSTR
PathRemoveFileSpecA proto WINAPI :LPSTR
PathRemoveFileSpecW proto WINAPI :LPWSTR
PathRenameExtensionA proto WINAPI :LPSTR, :LPCSTR
PathRenameExtensionW proto WINAPI :LPWSTR, :LPCWSTR
PathSearchAndQualifyA proto WINAPI :LPCSTR, :LPSTR, :UINT
PathSearchAndQualifyW proto WINAPI :LPCWSTR, :LPWSTR, :UINT
PathSetDlgItemPathA proto WINAPI :HWND, :SINT, :LPCSTR
PathSetDlgItemPathW proto WINAPI :HWND, :SINT, :LPCWSTR

ifdef USE_STRICT_CONST
PathSkipRootA proto WINAPI :LPCSTR
PathSkipRootW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathSkipRoot		equ <PathSkipRootW>
else
PathSkipRoot		equ <PathSkipRootA>
endif
else
PathSkipRootA proto WINAPI :LPCSTR
PathSkipRootW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathSkipRoot		equ <PathSkipRootW>
else
PathSkipRoot		equ <PathSkipRootA>
endif
endif
PathStripPathA proto WINAPI :LPSTR
PathStripPathW proto WINAPI :LPWSTR
ifdef _UNICODE
PathStripPath		equ <PathStripPathW>
else
PathStripPath		equ <PathStripPathA>
endif
PathStripToRootA proto WINAPI :LPSTR
PathStripToRootW proto WINAPI :LPWSTR
ifdef _UNICODE
PathStripToRoot		equ <PathStripToRootW>
else
PathStripToRoot		equ <PathStripToRootA>
endif
PathUnquoteSpacesA proto WINAPI :LPSTR
PathUnquoteSpacesW proto WINAPI :LPWSTR
PathMakeSystemFolderA proto WINAPI :LPCSTR
PathMakeSystemFolderW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathMakeSystemFolder	equ <PathMakeSystemFolderW>
else
PathMakeSystemFolder	equ <PathMakeSystemFolderA>
endif
PathUnmakeSystemFolderA proto WINAPI :LPCSTR
PathUnmakeSystemFolderW proto WINAPI :LPCWSTR
ifdef _UNICODE
PathUnmakeSystemFolder	equ <PathUnmakeSystemFolderW>
else
PathUnmakeSystemFolder	equ <PathUnmakeSystemFolderA>
endif
PathIsSystemFolderA proto WINAPI :LPCSTR, :DWORD
PathIsSystemFolderW proto WINAPI :LPCWSTR, :DWORD
ifdef _UNICODE
PathIsSystemFolder	equ <PathIsSystemFolderW>
else
PathIsSystemFolder	equ <PathIsSystemFolderA>
endif
PathUndecorateA proto WINAPI :LPSTR
PathUndecorateW proto WINAPI :LPWSTR
ifdef _UNICODE
PathUndecorate		equ <PathUndecorateW>
else
PathUndecorate		equ <PathUndecorateA>
endif
PathUnExpandEnvStringsA proto WINAPI :LPCSTR, :LPSTR, :UINT
PathUnExpandEnvStringsW proto WINAPI :LPCWSTR, :LPWSTR, :UINT
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


UrlCompareA proto WINAPI :LPCSTR, :LPCSTR, :BOOL
UrlCompareW proto WINAPI :LPCWSTR, :LPCWSTR, :BOOL
UrlCombineA proto WINAPI :LPCSTR, :LPCSTR, :LPSTR, :LPDWORD, :DWORD
UrlCombineW proto WINAPI :LPCWSTR, :LPCWSTR, :LPWSTR, :LPDWORD, :DWORD
UrlCanonicalizeA proto WINAPI :LPCSTR, :LPSTR, :LPDWORD, :DWORD
UrlCanonicalizeW proto WINAPI :LPCWSTR, :LPWSTR, :LPDWORD, :DWORD
UrlIsOpaqueA proto WINAPI :LPCSTR
UrlIsOpaqueW proto WINAPI :LPCWSTR
UrlIsNoHistoryA proto WINAPI :LPCSTR
UrlIsNoHistoryW proto WINAPI :LPCWSTR
UrlIsFileUrlA macro pszURL
	exitm<UrlIsA(pszURL, URLIS_FILEURL)>
	endm
UrlIsFileUrlW macro pszURL
	exitm<UrlIsW(pszURL, URLIS_FILEURL)>
	endm
UrlIsA proto WINAPI :LPCSTR, :URLIS
UrlIsW proto WINAPI :LPCWSTR, :URLIS
UrlGetLocationA proto WINAPI :LPCSTR
UrlGetLocationW proto WINAPI :LPCWSTR
UrlUnescapeA proto WINAPI :LPSTR, :LPSTR, :LPDWORD, :DWORD
UrlUnescapeW proto WINAPI :LPWSTR, :LPWSTR, :LPDWORD, :DWORD
UrlEscapeA proto WINAPI :LPCSTR, :LPSTR, :LPDWORD, :DWORD
UrlEscapeW proto WINAPI :LPCWSTR, :LPWSTR, :LPDWORD, :DWORD
UrlCreateFromPathA proto WINAPI :LPCSTR, :LPSTR, :LPDWORD, :DWORD
UrlCreateFromPathW proto WINAPI :LPCWSTR, :LPWSTR, :LPDWORD, :DWORD
PathCreateFromUrlA proto WINAPI :LPCSTR, :LPSTR, :LPDWORD, :DWORD
PathCreateFromUrlW proto WINAPI :LPCWSTR, :LPWSTR, :LPDWORD, :DWORD

if (_WIN32_IE GE _WIN32_IE_IE70)
PathCreateFromUrlAlloc proto WINAPI :LPCWSTR, :ptr LPWSTR, :DWORD
endif
UrlHashA proto WINAPI :LPCSTR, :LPBYTE, :DWORD
UrlHashW proto WINAPI :LPCWSTR, :LPBYTE, :DWORD
UrlGetPartW proto WINAPI :LPCWSTR, :PWSTR, :LPDWORD, :DWORD, :DWORD
UrlGetPartA proto WINAPI :LPCSTR, :LPSTR, :LPDWORD, :DWORD, :DWORD
UrlApplySchemeA proto WINAPI :LPCSTR, :LPSTR, :LPDWORD, :DWORD
UrlApplySchemeW proto WINAPI :LPCWSTR, :LPWSTR, :LPDWORD, :DWORD
HashData proto WINAPI :LPBYTE, :DWORD, :LPBYTE, :DWORD
UrlFixupW proto WINAPI :LPCWSTR, :LPWSTR, :DWORD

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

ParseURLA proto WINAPI :LPCSTR, :ptr PARSEDURLA
ParseURLW proto WINAPI :LPCWSTR, :ptr PARSEDURLW
ifdef _UNICODE
ParseURL		equ <ParseURLW>
else
ParseURL		equ <ParseURLA>
endif

endif ;; _WIN32_IE_IE50
endif ;; NO_SHLWAPI_PATH

ifndef NO_SHLWAPI_REG

SHDeleteEmptyKeyA proto WINAPI :HKEY, :LPCSTR
SHDeleteEmptyKeyW proto WINAPI :HKEY, :LPCWSTR
ifdef _UNICODE
SHDeleteEmptyKey	equ <SHDeleteEmptyKeyW>
else
SHDeleteEmptyKey	equ <SHDeleteEmptyKeyA>
endif
SHDeleteKeyA proto WINAPI :HKEY, :LPCSTR
SHDeleteKeyW proto WINAPI :HKEY, :LPCWSTR
ifdef _UNICODE
SHDeleteKey		equ <SHDeleteKeyW>
else
SHDeleteKey		equ <SHDeleteKeyA>
endif
SHRegDuplicateHKey proto WINAPI :HKEY
SHDeleteValueA proto WINAPI :HKEY, :LPCSTR, :LPCSTR
SHDeleteValueW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR
ifdef _UNICODE
SHDeleteValue		equ <SHDeleteValueW>
else
SHDeleteValue		equ <SHDeleteValueA>
endif
SHGetValueA proto WINAPI :HKEY, :LPCSTR, :LPCSTR, :ptr, :ptr, :ptr
SHGetValueW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR, :ptr, :ptr, :ptr
ifdef _UNICODE
SHGetValue		equ <SHGetValueW>
else
SHGetValue		equ <SHGetValueA>
endif
SHSetValueA proto WINAPI :HKEY, :LPCSTR, :LPCSTR, :DWORD, :ptr, :DWORD
SHSetValueW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR, :DWORD, :ptr, :DWORD
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

SHRegGetValueA proto WINAPI :HKEY, :LPCSTR, :LPCSTR, :SRRF, :ptr, :ptr, :ptr
SHRegGetValueW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR, :SRRF, :ptr, :ptr, :ptr
ifdef _UNICODE
SHRegGetValue		equ <SHRegGetValueW>
else
SHRegGetValue		equ <SHRegGetValueA>
endif
SHRegSetValue proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR, :SRRF, :DWORD, :ptr, :DWORD
SHRegGetValueFromHKCUHKLM proto WINAPI :PCWSTR, :PCWSTR, :SRRF, :ptr, :ptr, :ptr
SHRegGetBoolValueFromHKCUHKLM proto WINAPI :PCWSTR, :PCWSTR, :BOOL
endif
SHQueryValueExA proto WINAPI :HKEY, :LPCSTR, :ptr, :ptr, :ptr, :ptr
SHQueryValueExW proto WINAPI :HKEY, :LPCWSTR, :ptr, :ptr, :ptr, :ptr
ifdef _UNICODE
SHQueryValueEx		equ <SHQueryValueExW>
else
SHQueryValueEx		equ <SHQueryValueExA>
endif
SHEnumKeyExA proto WINAPI :HKEY, :DWORD, :LPSTR, :LPDWORD
SHEnumKeyExW proto WINAPI :HKEY, :DWORD, :LPWSTR, :LPDWORD
SHEnumValueA proto WINAPI :HKEY, :DWORD, :PSTR, :LPDWORD, :LPDWORD, :ptr, :LPDWORD
SHEnumValueW proto WINAPI :HKEY, :DWORD, :PWSTR, :LPDWORD, :LPDWORD, :ptr, :LPDWORD
SHQueryInfoKeyA proto WINAPI :HKEY, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD
SHQueryInfoKeyW proto WINAPI :HKEY, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD
SHCopyKeyA proto WINAPI :HKEY, :LPCSTR, :HKEY, :DWORD
SHCopyKeyW proto WINAPI :HKEY, :LPCWSTR, :HKEY, :DWORD
SHRegGetPathA proto WINAPI :HKEY, :LPCSTR, :LPCSTR, :LPSTR, :DWORD
SHRegGetPathW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR, :LPWSTR, :DWORD
SHRegSetPathA proto WINAPI :HKEY, :LPCSTR, :LPCSTR, :LPCSTR, :DWORD
SHRegSetPathW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR, :LPCWSTR, :DWORD

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

HUSKEY			typedef HANDLE
PHUSKEY			typedef ptr HUSKEY
ifndef REGSAM
REGSAM			typedef ACCESS_MASK
endif

SHRegCreateUSKeyA proto WINAPI :LPCSTR, :REGSAM, :HUSKEY, :PHUSKEY, :DWORD
SHRegCreateUSKeyW proto WINAPI :LPCWSTR, :REGSAM, :HUSKEY, :PHUSKEY, :DWORD
SHRegOpenUSKeyA proto WINAPI :LPCSTR, :REGSAM, :HUSKEY, :PHUSKEY, :BOOL
SHRegOpenUSKeyW proto WINAPI :LPCWSTR, :REGSAM, :HUSKEY, :PHUSKEY, :BOOL
SHRegQueryUSValueA proto WINAPI :HUSKEY, :LPCSTR, :ptr, :ptr, :ptr, :BOOL, :ptr, :DWORD
SHRegQueryUSValueW proto WINAPI :HUSKEY, :LPCWSTR, :ptr, :ptr, :ptr, :BOOL, :ptr, :DWORD
SHRegWriteUSValueA proto WINAPI :HUSKEY, :LPCSTR, :DWORD, :ptr, :DWORD, :DWORD
SHRegWriteUSValueW proto WINAPI :HUSKEY, :LPCWSTR, :DWORD, :ptr, :DWORD, :DWORD
SHRegDeleteUSValueA proto WINAPI :HUSKEY, :LPCSTR, :SHREGDEL_FLAGS
SHRegDeleteUSValueW proto WINAPI :HUSKEY, :LPCWSTR, :SHREGDEL_FLAGS
SHRegDeleteEmptyUSKeyW proto WINAPI :HUSKEY, :LPCWSTR, :SHREGDEL_FLAGS
SHRegDeleteEmptyUSKeyA proto WINAPI :HUSKEY, :LPCSTR, :SHREGDEL_FLAGS
SHRegEnumUSKeyA proto WINAPI :HUSKEY, :DWORD, :LPSTR, :LPDWORD, :SHREGENUM_FLAGS
SHRegEnumUSKeyW proto WINAPI :HUSKEY, :DWORD, :LPWSTR, :LPDWORD, :SHREGENUM_FLAGS
SHRegEnumUSValueA proto WINAPI :HUSKEY, :DWORD, :LPSTR, :LPDWORD, :LPDWORD, :ptr, :LPDWORD, :SHREGENUM_FLAGS
SHRegEnumUSValueW proto WINAPI :HUSKEY, :DWORD, :LPWSTR, :LPDWORD, :LPDWORD, :ptr, :LPDWORD, :SHREGENUM_FLAGS
SHRegQueryInfoUSKeyA proto WINAPI :HUSKEY, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :SHREGENUM_FLAGS
SHRegQueryInfoUSKeyW proto WINAPI :HUSKEY, :LPDWORD, :LPDWORD, :LPDWORD, :LPDWORD, :SHREGENUM_FLAGS
SHRegCloseUSKey proto WINAPI :HUSKEY
SHRegGetUSValueA proto WINAPI :LPCSTR, :LPCSTR, :ptr, :ptr, :ptr, :BOOL, :ptr, :DWORD
SHRegGetUSValueW proto WINAPI :LPCWSTR, :LPCWSTR, :ptr, :ptr, :ptr, :BOOL, :ptr, :DWORD
SHRegSetUSValueA proto WINAPI :LPCSTR, :LPCSTR, :DWORD, :ptr, :DWORD, :DWORD
SHRegSetUSValueW proto WINAPI :LPCWSTR, :LPCWSTR, :DWORD, :ptr, :DWORD, :DWORD
SHRegGetIntW proto WINAPI :HKEY, :PCWSTR, :SINT

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

SHRegGetBoolUSValueA proto WINAPI :LPCSTR, :LPCSTR, :BOOL, :BOOL
SHRegGetBoolUSValueW proto WINAPI :LPCWSTR, :LPCWSTR, :BOOL, :BOOL
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

.comdef IQueryAssociations : public IUnknown

    Init		proc :ASSOCF, :LPCWSTR, :HKEY, :HWND
    GetString		proc :ASSOCF, :ASSOCSTR, :LPCWSTR, :LPWSTR, :ptr
    GetKey		proc :ASSOCF, :ASSOCKEY, :LPCWSTR, :ptr
    GetData		proc :ASSOCF, :ASSOCDATA, :LPCWSTR, :PVOID, :ptr
    GetEnum		proc :ASSOCF, :ASSOCENUM, :LPCWSTR, :REFIID, :PVOID
   .ends

AssocCreate proto WINAPI :CLSID, :REFIID, :ptr
AssocQueryStringA proto WINAPI :ASSOCF, :ASSOCSTR, :LPCSTR, :LPCSTR, :LPSTR, :ptr
AssocQueryStringW proto WINAPI :ASSOCF, :ASSOCSTR, :LPCWSTR, :LPCWSTR, :LPWSTR, :ptr
ifdef _UNICODE
AssocQueryString	equ <AssocQueryStringW>
else
AssocQueryString	equ <AssocQueryStringA>
endif
AssocQueryStringByKeyA proto WINAPI :ASSOCF, :ASSOCSTR, :HKEY, :LPCSTR, :LPSTR, :ptr
AssocQueryStringByKeyW proto WINAPI :ASSOCF, :ASSOCSTR, :HKEY, :LPCWSTR, :LPWSTR, :ptr
ifdef _UNICODE
AssocQueryStringByKey	equ <AssocQueryStringByKeyW>
else
AssocQueryStringByKey	equ <AssocQueryStringByKeyA>
endif
AssocQueryKeyA proto WINAPI :ASSOCF, :ASSOCKEY, :LPCSTR, :LPCSTR, :ptr
AssocQueryKeyW proto WINAPI :ASSOCF, :ASSOCKEY, :LPCWSTR, :LPCWSTR, :ptr
ifdef _UNICODE
AssocQueryKey		equ <AssocQueryKeyW>
else
AssocQueryKey		equ <AssocQueryKeyA>
endif
if (_WIN32_IE GE 0x0601)
AssocIsDangerous proto WINAPI :LPCWSTR
endif
if (_WIN32_IE GE _WIN32_IE_IE60SP2)
AssocGetPerceivedType proto WINAPI :LPCWSTR, :ptr, :ptr, :ptr
endif
endif ;; NO_SHLWAPI_REG

ifndef NO_SHLWAPI_STREAM

SHOpenRegStreamA proto WINAPI :HKEY, :LPCSTR, :LPCSTR, :DWORD
SHOpenRegStreamW proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR, :DWORD
ifdef _UNICODE
SHOpenRegStream		equ <SHOpenRegStreamW>
else
SHOpenRegStream		equ <SHOpenRegStreamA>
endif
SHOpenRegStream2A proto WINAPI :HKEY, :LPCSTR, :LPCSTR, :DWORD
SHOpenRegStream2W proto WINAPI :HKEY, :LPCWSTR, :LPCWSTR, :DWORD
ifdef _UNICODE
SHOpenRegStream2	equ <SHOpenRegStream2W>
else
SHOpenRegStream2	equ <SHOpenRegStream2A>
endif
SHOpenRegStream		equ <SHOpenRegStream2>

SHCreateStreamOnFileA proto WINAPI :LPCSTR, :DWORD, :ptr
SHCreateStreamOnFileW proto WINAPI :LPCWSTR, :DWORD, :ptr
ifdef _UNICODE
SHCreateStreamOnFile	equ <SHCreateStreamOnFileW>
else
SHCreateStreamOnFile	equ <SHCreateStreamOnFileA>
endif

if (_WIN32_IE GE 0x0600)
SHCreateStreamOnFileEx proto WINAPI :LPCWSTR, :DWORD, :DWORD, :BOOL, :ptr, :ptr
endif

if (_WIN32_IE GE _WIN32_IE_IE501)
SHCreateMemStream proto WINAPI :ptr, :UINT
endif
endif ;; NO_SHLWAPI_STREAM

ifndef NO_SHLWAPI_HTTP
if (_WIN32_IE GE 0x0603)
GetAcceptLanguagesA proto WINAPI :LPSTR, :ptr
GetAcceptLanguagesW proto WINAPI :LPWSTR, :ptr
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

StopWatchMode proto WINAPI
StopWatchFlush proto WINAPI
endif

if (_WIN32_IE GE _WIN32_IE_IE501)
IUnknown_Set proto WINAPI :ptr, :ptr
IUnknown_AtomicRelease proto WINAPI :ptr
IUnknown_GetWindow proto WINAPI :ptr, :ptr
IUnknown_SetSite proto WINAPI :ptr, :ptr
IUnknown_GetSite proto WINAPI :ptr, :REFIID, :ptr
IUnknown_QueryService proto WINAPI :ptr, :REFGUID, :REFIID, :ptr
endif

if (_WIN32_IE GE _WIN32_IE_IE501)
IStream_Read proto WINAPI :ptr, :ptr, :ULONG
IStream_Write proto WINAPI :ptr, :ptr, :ULONG
IStream_Reset proto WINAPI :ptr
IStream_Size proto WINAPI :ptr, :ptr
ConnectToConnectionPoint proto WINAPI :ptr, :REFIID, :BOOL, :ptr, :ptr, :ptr
endif

if (_WIN32_IE GE _WIN32_IE_IE60)
IStream_ReadPidl proto WINAPI :ptr, :ptr
IStream_WritePidl proto WINAPI :ptr, :PCUIDLIST_RELATIVE
endif

if (_WIN32_IE GE _WIN32_IE_IE70)
IStream_ReadStr proto WINAPI :ptr, :ptr
IStream_WriteStr proto WINAPI :ptr, :PCWSTR
IStream_Copy proto WINAPI :ptr, :ptr, :DWORD
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

SHGetViewStatePropertyBag proto WINAPI :PCIDLIST_ABSOLUTE, :LPCWSTR, :DWORD, :REFIID, :ptr
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

SHFormatDateTimeA proto WINAPI :ptr, :ptr, :LPSTR, :UINT
SHFormatDateTimeW proto WINAPI :ptr, :ptr, :LPWSTR, :UINT
ifdef _UNICODE
SHFormatDateTime	equ <SHFormatDateTimeW>
else
SHFormatDateTime	equ <SHFormatDateTimeA>
endif

if (_WIN32_IE GE _WIN32_IE_IE501)
SHAnsiToUnicode proto WINAPI :LPCSTR, :LPWSTR, :SINT
SHAnsiToAnsi proto WINAPI :LPCSTR, :LPSTR, :SINT
SHUnicodeToAnsi proto WINAPI :LPCWSTR, :LPSTR, :SINT
SHUnicodeToUnicode proto WINAPI :LPCWSTR, :LPWSTR, :SINT

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
SHMessageBoxCheckA proto WINAPI :HWND, :LPCSTR, :LPCSTR, :UINT, :SINT, :LPCSTR
SHMessageBoxCheckW proto WINAPI :HWND, :LPCWSTR, :LPCWSTR, :UINT, :SINT, :LPCWSTR
ifdef _UNICODE
SHMessageBoxCheck	equ <SHMessageBoxCheckW>
else
SHMessageBoxCheck	equ <SHMessageBoxCheckA>
endif

endif

if (_WIN32_IE GE _WIN32_IE_IE501)
SHSendMessageBroadcastA proto WINAPI :UINT, :WPARAM, :LPARAM
SHSendMessageBroadcastW proto WINAPI :UINT, :WPARAM, :LPARAM
ifdef _UNICODE
SHSendMessageBroadcast	equ <SHSendMessageBroadcastW>
else
SHSendMessageBroadcast	equ <SHSendMessageBroadcastA>
endif
SHStripMneumonicA proto WINAPI :LPSTR
SHStripMneumonicW proto WINAPI :LPWSTR
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

IsOS proto WINAPI :DWORD

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

SHGlobalCounterGetValue proto WINAPI :SHGLOBALCOUNTER
SHGlobalCounterIncrement proto WINAPI :SHGLOBALCOUNTER
SHGlobalCounterDecrement proto WINAPI :SHGLOBALCOUNTER
if (_WIN32_IE GE 0x0603)
SHAllocShared proto WINAPI :ptr, :DWORD, :DWORD
SHFreeShared proto WINAPI :HANDLE, :DWORD
SHLockShared proto WINAPI :HANDLE, :DWORD
SHUnlockShared proto WINAPI :ptr
endif

if (_WIN32_IE GE _WIN32_IE_IE501)

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

QISearch proto WINAPI :ptr, :LPCQITAB, :REFIID, :ptr

endif

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
SHIsLowMemoryMachine proto WINAPI :DWORD
GetMenuPosFromID proto WINAPI :HMENU, :UINT
SHGetInverseCMAP proto WINAPI :ptr, :ULONG

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

SHAutoComplete proto WINAPI :HWND, :DWORD

if (_WIN32_IE GE _WIN32_IE_IE60SP2)
SHCreateThreadRef proto WINAPI :ptr, :ptr
endif

SHSetThreadRef proto WINAPI :ptr
SHGetThreadRef proto WINAPI :ptr
SHSkipJunction proto WINAPI :ptr, :ptr

endif

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

SHCreateThread proto WINAPI :LPTHREAD_START_ROUTINE, :ptr, :SHCT_FLAGS, :LPTHREAD_START_ROUTINE
SHCreateThreadWithHandle proto WINAPI :LPTHREAD_START_ROUTINE, :ptr, :SHCT_FLAGS, :LPTHREAD_START_ROUTINE, :ptr
if (_WIN32_IE GE _WIN32_IE_IE60)
SHReleaseThreadRef proto WINAPI
endif
ifndef NO_SHLWAPI_GDI
SHCreateShellPalette proto WINAPI :HDC
if (_WIN32_IE GE 0x0500)
ColorRGBToHLS proto WINAPI :COLORREF, :ptr, :ptr, :ptr
ColorHLSToRGB proto WINAPI :WORD, :WORD, :WORD
ColorAdjustLuma proto WINAPI :COLORREF, :SINT, :BOOL
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

DllInstall proto WINAPI :BOOL, :LPCWSTR

if (_WIN32_IE GE 0x0602)
IsInternetESCEnabled proto WINAPI
endif

ifdef _WIN32
.pragma pack(pop)
endif
endif
endif
.pragma list(pop)
