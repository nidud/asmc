ifndef _TIMEZONEAPI_H_
define _TIMEZONEAPI_H_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

define TIME_ZONE_ID_INVALID (0xFFFFFFFF)

_TIME_ZONE_INFORMATION  struct
Bias                    LONG ?
StandardName            WCHAR 32 dup(?)
StandardDate            SYSTEMTIME <>
StandardBias            LONG ?
DaylightName            WCHAR 32 dup(?)
DaylightDate            SYSTEMTIME <>
DaylightBias            LONG ?
_TIME_ZONE_INFORMATION  ends
TIME_ZONE_INFORMATION   typedef _TIME_ZONE_INFORMATION
PTIME_ZONE_INFORMATION  typedef ptr _TIME_ZONE_INFORMATION
LPTIME_ZONE_INFORMATION typedef ptr _TIME_ZONE_INFORMATION

_TIME_DYNAMIC_ZONE_INFORMATION struct
Bias                    LONG ?
StandardName            WCHAR 32 dup(?)
StandardDate            SYSTEMTIME <>
StandardBias            LONG ?
DaylightName            WCHAR 32 dup(?)
DaylightDate            SYSTEMTIME <>
DaylightBias            LONG ?
TimeZoneKeyName         WCHAR 128 dup(?)
DynamicDaylightTimeDisabled BOOLEAN ?
_TIME_DYNAMIC_ZONE_INFORMATION ends
DYNAMIC_TIME_ZONE_INFORMATION typedef _TIME_DYNAMIC_ZONE_INFORMATION
PDYNAMIC_TIME_ZONE_INFORMATION typedef ptr _TIME_DYNAMIC_ZONE_INFORMATION

SystemTimeToTzSpecificLocalTime proto WINAPI :ptr, :ptr, :LPSYSTEMTIME
TzSpecificLocalTimeToSystemTime proto WINAPI :ptr, :ptr, :LPSYSTEMTIME
FileTimeToSystemTime proto WINAPI :ptr, :LPSYSTEMTIME
SystemTimeToFileTime proto WINAPI :ptr, :LPFILETIME
GetTimeZoneInformation proto WINAPI :LPTIME_ZONE_INFORMATION
SetTimeZoneInformation proto WINAPI :ptr

if (_WIN32_WINNT ge 0x0600)
SetDynamicTimeZoneInformation proto WINAPI :ptr
endif

if (_WIN32_WINNT ge 0x0600)
GetDynamicTimeZoneInformation proto WINAPI :PDYNAMIC_TIME_ZONE_INFORMATION
endif

if (_WIN32_WINNT ge 0x0601)
GetTimeZoneInformationForYear proto WINAPI :USHORT, :PDYNAMIC_TIME_ZONE_INFORMATION, :LPTIME_ZONE_INFORMATION
endif

if (_WIN32_WINNT ge _WIN32_WINNT_WIN8)

EnumDynamicTimeZoneInformation proto WINAPI :DWORD, :PDYNAMIC_TIME_ZONE_INFORMATION
GetDynamicTimeZoneInformationEffectiveYears proto WINAPI :PDYNAMIC_TIME_ZONE_INFORMATION, :LPDWORD, :LPDWORD
SystemTimeToTzSpecificLocalTimeEx proto WINAPI :ptr, :ptr, :LPSYSTEMTIME
TzSpecificLocalTimeToSystemTimeEx proto WINAPI :ptr, :ptr, :LPSYSTEMTIME

endif

if (NTDDI_VERSION ge NTDDI_WIN10_RS5)

LocalFileTimeToLocalSystemTime proto WINAPI :ptr, :ptr, :ptr
LocalSystemTimeToLocalFileTime proto WINAPI :ptr, :ptr, :ptr

endif

endif

endif
