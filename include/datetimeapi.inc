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

;int
GetDateFormatA proto WINAPI \
                Locale: LCID,
               dwFlags: DWORD,
                lpDate: ptr SYSTEMTIME,
              lpFormat: LPCSTR,
             lpDateStr: LPSTR,
               cchDate: SINT

;int
GetDateFormatW proto WINAPI \
                Locale: LCID,
               dwFlags: DWORD,
                lpDate: ptr SYSTEMTIME,
              lpFormat: LPCWSTR,
             lpDateStr: LPWSTR,
               cchDate: SINT

ifdef _UNICODE
define GetDateFormat  <GetDateFormatW>
else
define GetDateFormat  <GetDateFormatA>
endif

;int
GetTimeFormatA proto WINAPI \
                Locale: LCID,
               dwFlags: DWORD,
                lpTime: ptr SYSTEMTIME,
              lpFormat: LPCSTR,
             lpTimeStr: LPSTR,
               cchTime: SINT

;int
GetTimeFormatW proto WINAPI \
                Locale: LCID,
               dwFlags: DWORD,
                lpTime: ptr SYSTEMTIME,
              lpFormat: LPCWSTR,
             lpTimeStr: LPWSTR,
               cchTime: SINT

ifdef _UNICODE
define GetTimeFormat  <GetTimeFormatW>
else
define GetTimeFormat  <GetTimeFormatA>
endif

endif

if NOT defined(_CONTRACT_GEN) OR (_APISET_DATETIME_VER GT 0x0100)
if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)

;int
GetTimeFormatEx proto WINAPI \
          lpLocaleName: LPCWSTR,
               dwFlags: DWORD,
                lpTime: ptr SYSTEMTIME,
              lpFormat: LPCWSTR,
             lpTimeStr: LPWSTR,
               cchTime: SINT

;int
GetDateFormatEx proto WINAPI \
          lpLocaleName: LPCWSTR,
               dwFlags: DWORD,
                lpDate: ptr SYSTEMTIME,
              lpFormat: LPCWSTR,
             lpDateStr: LPWSTR,
               cchDate: SINT,
            lpCalendar: LPCWSTR

endif
endif
endif
