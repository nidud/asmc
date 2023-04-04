ifndef __TIME_INC
define __TIME_INC
.pragma list(push, 0)

ifndef __LIBC_INC
 include libc.inc
endif

.pragma comment(lib, libc, msvcrt)
.pragma pack(push, size_t)

ifndef _WCHAR_T_DEFINED
define _WCHAR_T_DEFINED
wchar_t typedef ushort_t
endif

ifndef _TIME32_T_DEFINED
define _TIME32_T_DEFINED
__time32_t typedef long_t	;; 32-bit time value
endif

ifndef _TIME64_T_DEFINED
define _TIME64_T_DEFINED
__time64_t typedef int64_t	;; 64-bit time value
endif

ifndef _TIME_T_DEFINED
define _TIME_T_DEFINED		;; avoid multiple def's of time_t
ifdef _WIN64
time_t typedef int64_t
else
time_t typedef long_t
endif
endif

ifndef _CLOCK_T_DEFINED
define _CLOCK_T_DEFINED
clock_t typedef long_t
endif

ifndef _SIZE_T_DEFINED
define _SIZE_T_DEFINED
ifdef _WIN64
size_t typedef uint64_t
else
size_t typedef uint_t
endif
endif

;
; ISO 8601:	YYYY-MM-DD hh:mm:ss
; Short form:	YY-MM-DD hh:mm
;
; input accept: MM/DD/YY[YY] | DD.MM.YY[YY] | [YY]YY-MM-DD
;
DT_BASEYEAR		equ 1980

_DAY_SEC		equ 24 * 60 * 60	; secs in a day
_YEAR_SEC		equ 365 * _DAY_SEC	; secs in a year
_FOUR_YEAR_SEC		equ 1461 * _DAY_SEC	; secs in a 4 year interval
_DEC_SEC		equ 315532800		; secs in 1970-1979
_BASE_YEAR		equ 70			; 1970 is the base year
_BASE_DOW		equ 4			; 01-01-70 was a Thursday
_LEAP_YEAR_ADJUST	equ 17			; Leap years 1900 - 1970
_MAX_YEAR		equ 138			; 2038 is the max year


ifndef LPFILETIME
FILETIME	STRUC
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ENDS
LPFILETIME	typedef ptr FILETIME
endif

ifndef LPSYSTEMTIME
SYSTEMTIME	STRUC
wYear		dw ?
wMonth		dw ?
wDayOfWeek	dw ?
wDay		dw ?
wHour		dw ?
wMinute		dw ?
wSecond		dw ?
wMilliseconds	dw ?
SYSTEMTIME	ENDS
LPSYSTEMTIME	typedef ptr SYSTEMTIME
endif

ifndef _TM_DEFINED
define _TM_DEFINED
tm		STRUC
tm_sec		SINT ?	;; seconds after the minute - [0,59]
tm_min		SINT ?	;; minutes after the hour - [0,59]
tm_hour		SINT ?	;; hours since midnight - [0,23]
tm_mday		SINT ?	;; day of the month - [1,31]
tm_mon		SINT ?	;; months since January - [0,11]
tm_year		SINT ?	;; years since 1900
tm_wday		SINT ?	;; days since Sunday - [0,6]
tm_yday		SINT ?	;; days since January 1 - [0,365]
tm_isdst	SINT ?	;; daylight savings time flag
tm		ENDS
endif

define CLOCKS_PER_SEC 1000

LPTIME		typedef ptr time_t

asctime		proto __cdecl :ptr tm
ctime		proto __cdecl :ptr time_t
clock		proto __cdecl
csftime		proto __cdecl :ptr sbyte, :size_t, :ptr sbyte, :ptr tm
strdate		proto __cdecl :ptr sbyte
strtime		proto __cdecl :ptr sbyte
difftime	proto __cdecl :time_t, :time_t

gmtime		proto __cdecl :ptr time_t
ifdef __LIBASMC__
define localtime <gmtime>
else
localtime	proto __cdecl :ptr time_t
endif
mktime		proto __cdecl :ptr tm
_mkgmtime	proto __cdecl :ptr tm
strftime	proto __cdecl :ptr sbyte, :size_t, :ptr sbyte, :ptr tm
strdate		proto __cdecl :ptr sbyte
strtime		proto __cdecl :ptr sbyte
_tzset		proto __cdecl
time		proto __cdecl :ptr time_t
_isindst	proto __cdecl :ptr tm
_loctotime_t	proto __cdecl y:SINT, m:SINT, d:SINT, h:SINT, m:SINT, s:SINT

_time		equ <time>
_strdate	equ <strdate>
_strtime	equ <strtime>

ifndef _WTIME_DEFINED
define _WTIME_DEFINED
_wasctime	proto __cdecl :ptr tm
_wctime		proto __cdecl :ptr time_t
wcsftime	proto __cdecl :ptr wchar_t, :size_t, :ptr wchar_t, :ptr tm
_wstrdate	proto __cdecl :ptr wchar_t
_wstrtime	proto __cdecl :ptr wchar_t
endif

ifdef __UNIX__

timeval		struct
tv_sec		size_t ? ; Seconds
tv_usec		size_t ? ; Microseconds
timeval		ends

itimerval	struct
it_interval	timeval <>
it_value	timeval <>
itimerval	ends

timezone	struct
tz_minuteswest	int_t ? ; Minutes west of GMT.
tz_dsttime	int_t ? ; Nonzero if DST is ever in effect.
timezone	ends

gettimeofday	proto __cdecl :ptr timeval, :ptr timezone
settimeofday	proto __cdecl :ptr timeval, :ptr timezone

endif

if not defined(_MSVCRT) or defined(_CRTBLD)

externdef	_days:DWORD
externdef	_lpdays:DWORD
externdef	_timezone:DWORD
externdef	_daylight:DWORD
externdef	_tzname:LPSTR
externdef	__dnames:BYTE
externdef	__mnames:BYTE

DaysInFebruary		proto __cdecl :uint_t
DaysInMonth		proto __cdecl :uint_t, :uint_t
GetDayCount		proto __cdecl :uint_t, :uint_t, :uint_t
GetWeekDay		proto __cdecl :uint_t, :uint_t, :uint_t

FileTimeToTime		proto __cdecl :ptr FILETIME
SystemTimeToTime	proto __cdecl :ptr SYSTEMTIME
TimeToFileTime		proto __cdecl :time_t, :ptr FILETIME
TimeToSystemTime	proto __cdecl :time_t, :ptr SYSTEMTIME

StringToSystemTimeA	proto __cdecl :ptr char_t,  :ptr SYSTEMTIME
StringToSystemTimeW	proto __cdecl :ptr wchar_t, :ptr SYSTEMTIME
StringToSystemDateA	proto __cdecl :ptr char_t,  :ptr SYSTEMTIME
StringToSystemDateW	proto __cdecl :ptr wchar_t, :ptr SYSTEMTIME

SystemTimeToStringA	proto __cdecl :ptr char_t,  :ptr SYSTEMTIME
SystemTimeToStringW	proto __cdecl :ptr wchar_t, :ptr SYSTEMTIME
SystemDateToStringA	proto __cdecl :ptr char_t,  :ptr SYSTEMTIME
SystemDateToStringW	proto __cdecl :ptr wchar_t, :ptr SYSTEMTIME

FileTimeToStringA	proto __cdecl :ptr char_t,  :ptr FILETIME
FileTimeToStringW	proto __cdecl :ptr wchar_t, :ptr FILETIME
FileDateToStringA	proto __cdecl :ptr char_t,  :ptr FILETIME
FileDateToStringW	proto __cdecl :ptr wchar_t, :ptr FILETIME

ifdef _UNICODE
define StringToSystemTime <StringToSystemTimeW>
define StringToSystemDate <StringToSystemDateW>
define SystemDateToString <SystemDateToStringW>
define SystemTimeToString <SystemTimeToStringW>
define FileTimeToString	  <FileTimeToStringW>
define FileDateToString	  <FileDateToStringW>
else
define StringToSystemTime <StringToSystemTimeA>
define StringToSystemDate <StringToSystemDateA>
define SystemDateToString <SystemDateToStringA>
define SystemTimeToString <SystemTimeToStringA>
define FileTimeToString	  <FileTimeToStringA>
define FileDateToString	  <FileDateToStringA>
endif

endif

.pragma pack(pop)
.pragma list(pop)
endif
