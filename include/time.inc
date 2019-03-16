.pragma list(push, 0)
ifndef __LIBC_INC
 include libc.inc
endif

ifdef __PE__
option dllimport:<msvcrt>
endif

include crtdefs.inc

.pragma pack(push, _CRT_PACKING)

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
_TM_DEFINED equ <>
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

ifndef _TIME_T_DEFINED
_TIME_T_DEFINED equ <>
ifdef _WIN64
time_t		typedef sqword
else
time_t		typedef sdword
endif
endif
LPTIME		typedef ptr time_t

asctime		proto __cdecl :ptr tm
ctime		proto __cdecl :ptr time_t
clock		proto __cdecl
csftime		proto __cdecl :ptr sbyte, :size_t, :ptr sbyte, :ptr tm
strdate		proto __cdecl :ptr sbyte
strtime		proto __cdecl :ptr sbyte
difftime	proto __cdecl :time_t, :time_t

gmtime		proto __cdecl :ptr time_t
localtime	proto __cdecl :ptr time_t
mktime		proto __cdecl :ptr tm
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

_wasctime	proto __cdecl :ptr tm
_wctime		proto __cdecl :ptr time_t
wcsftime	proto __cdecl :ptr wchar_t, :size_t, :ptr wchar_t, :ptr tm
_wstrdate	proto __cdecl :ptr wchar_t
_wstrtime	proto __cdecl :ptr wchar_t

_WTIME_DEFINED	equ 1
endif

ifndef __PE__

externdef	_days:DWORD
externdef	_lpdays:DWORD
externdef	_timezone:DWORD
externdef	_daylight:DWORD
externdef	_tzname:LPSTR
externdef	__dnames:BYTE
externdef	__mnames:BYTE

__FTToTime	proto __cdecl :LPFILETIME
__STToTime	proto __cdecl :LPSYSTEMTIME
__TimeToFT	proto __cdecl :time_t, :LPFILETIME
__TimeToST	proto __cdecl :time_t, :LPSYSTEMTIME

DaysInFebruary	proto __cdecl :dword
DaysInMonth	proto __cdecl :dword, :dword
GetDayCount	proto __cdecl :dword, :dword, :dword
GetWeekDay	proto __cdecl :dword, :dword, :dword

atotime		proto __cdecl :LPSTR
atodate		proto __cdecl :LPSTR
fdatetostr	proto __cdecl :LPSTR, :LPFILETIME
ftimetostr	proto __cdecl :LPSTR, :LPFILETIME

TDateToString	proto __cdecl :ptr sbyte, :time_t
SystemTimeToString proto __cdecl :ptr sbyte, :LPSYSTEMTIME
SystemDateToString proto __cdecl :ptr sbyte, :LPSYSTEMTIME

.pragma pack(pop)
endif
.pragma list(pop)
