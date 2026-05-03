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
CompareStringEx proto WINAPI :LPCWSTR, :DWORD, :LPCWCH, :SINT, :LPCWCH, :SINT, :LPNLSVERSIONINFO, :ptr, :LPARAM
CompareStringOrdinal proto WINAPI :LPCWCH, :SINT, :LPCWCH, :SINT, :BOOL
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
CompareStringW proto WINAPI :LCID, :DWORD, :PCNZWCH, :SINT, :PCNZWCH, :SINT
ifdef _UNICODE
define CompareString  <CompareStringW>
endif
FoldStringW proto WINAPI :DWORD, :LPCWCH, :SINT, :LPWSTR, :SINT
ifdef _UNICODE
define FoldString  <FoldStringW>
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
GetStringTypeExW proto WINAPI :LCID, :DWORD, :LPCWCH, :SINT, :LPWORD
ifdef _UNICODE
define GetStringTypeEx  <GetStringTypeExW>
endif
GetStringTypeW proto WINAPI :DWORD, :LPCWCH, :SINT, :LPWORD
MultiByteToWideChar proto WINAPI :UINT, :DWORD, :LPCCH, :SINT, :LPWSTR, :SINT
WideCharToMultiByte proto WINAPI :UINT, :DWORD, :LPCWCH, :SINT, :LPSTR, :SINT, :LPCCH, :LPBOOL
endif
endif ;; _APISETSTRING_
