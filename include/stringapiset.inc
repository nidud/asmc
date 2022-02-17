ifndef _APISETSTRING_
define _APISETSTRING_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include winnls.inc

ifndef _APISET_STRING_VER
ifdef _APISET_MINWIN_VERSION
if _APISET_MINWIN_VERSION GE 0x0100
define _APISET_STRING_VER 0x0100
endif
endif
endif

if (WINVER GE 0x0600)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;int
CompareStringEx proto WINAPI \
          lpLocaleName: LPCWSTR,
            dwCmpFlags: DWORD,
             lpString1: LPCWCH,
             cchCount1: SINT,
             lpString2: LPCWCH,
             cchCount2: SINT,
  lpVersionInformation: LPNLSVERSIONINFO,
            lpReserved: LPVOID,
                lParam: LPARAM


;int
CompareStringOrdinal proto WINAPI \
             lpString1: LPCWCH,
             cchCount1: SINT,
             lpString2: LPCWCH,
             cchCount2: SINT,
           bIgnoreCase: BOOL

endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)

;int
CompareStringW proto WINAPI \
                Locale: LCID,
            dwCmpFlags: DWORD,
             lpString1: PCNZWCH,
             cchCount1: SINT,
             lpString2: PCNZWCH,
             cchCount2: SINT

ifdef _UNICODE
define CompareString  <CompareStringW>
endif

;int
FoldStringW proto WINAPI \
            dwMapFlags: DWORD,
              lpSrcStr: LPCWCH,
                cchSrc: SINT,
             lpDestStr: LPWSTR,
               cchDest: SINT

ifdef _UNICODE
define FoldString  <FoldStringW>
endif

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;BOOL
GetStringTypeExW proto WINAPI \
                Locale: LCID,
            dwInfoType: DWORD,
              lpSrcStr: LPCWCH,
                cchSrc: SINT,
            lpCharType: LPWORD

ifdef _UNICODE
define GetStringTypeEx  <GetStringTypeExW>
endif

;BOOL
GetStringTypeW proto WINAPI \
            dwInfoType: DWORD,
              lpSrcStr: LPCWCH,
                cchSrc: SINT,
            lpCharType: LPWORD

;int
MultiByteToWideChar proto WINAPI \
              CodePage: UINT,
               dwFlags: DWORD,
        lpMultiByteStr: LPCCH,
           cbMultiByte: SINT,
         lpWideCharStr: LPWSTR,
           cchWideChar: SINT

;int
WideCharToMultiByte proto WINAPI \
              CodePage: UINT,
               dwFlags: DWORD,
         lpWideCharStr: LPCWCH,
           cchWideChar: SINT,
        lpMultiByteStr: LPSTR,
           cbMultiByte: SINT,
         lpDefaultChar: LPCCH,
     lpUsedDefaultChar: LPBOOL


endif
endif ;; _APISETSTRING_
