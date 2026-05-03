ifndef _DATETIMEAPI_H_
define _DATETIMEAPI_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

ifndef _APISET_DATETIME_VER
ifdef _APISET_MINWIN_VERSION
if _APISET_MINWIN_VERSION GE 0x0101
define _APISET_DATETIME_VER 0x0101
elseif _APISET_MINWIN_VERSION EQ 0x0100
define _APISET_DATETIME_VER 0x0100
endif
endif
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
GetDateFormatA proto WINAPI :LCID, :DWORD, :ptr SYSTEMTIME, :LPCSTR, :LPSTR, :SINT
GetDateFormatW proto WINAPI :LCID, :DWORD, :ptr SYSTEMTIME, :LPCWSTR, :LPWSTR, :SINT
GetTimeFormatA proto WINAPI :LCID, :DWORD, :ptr SYSTEMTIME, :LPCSTR, :LPSTR, :SINT
GetTimeFormatW proto WINAPI :LCID, :DWORD, :ptr SYSTEMTIME, :LPCWSTR, :LPWSTR, :SINT
ifdef _UNICODE
define GetDateFormat  <GetDateFormatW>
define GetTimeFormat  <GetTimeFormatW>
else
define GetDateFormat  <GetDateFormatA>
define GetTimeFormat  <GetTimeFormatA>
endif
endif
if NOT defined(_CONTRACT_GEN) OR (_APISET_DATETIME_VER GT 0x0100)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
GetTimeFormatEx proto WINAPI :LPCWSTR, :DWORD, :ptr SYSTEMTIME, :LPCWSTR, :LPWSTR, :SINT
GetDateFormatEx proto WINAPI :LPCWSTR, :DWORD, :ptr SYSTEMTIME, :LPCWSTR, :LPWSTR, :SINT, :LPCWSTR
endif
endif
endif
