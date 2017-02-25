ifndef __LIBC_INC
 include libc.inc
endif

.xlist
ifdef __PE__
option	dllimport:<msvcrt>
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


FILETIME	STRUC
dwLowDateTime	dd ?
dwHighDateTime	dd ?
FILETIME	ENDS
LPFILETIME	typedef ptr FILETIME

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
_TM_DEFINED	equ 1
endif

time_t		typedef sdword
LPTIME		typedef ptr time_t

asctime		proto :ptr tm
ctime		proto :ptr time_t
clock		proto
csftime		proto :ptr sbyte, :size_t, :ptr sbyte, :ptr tm
strdate		proto :ptr sbyte
strtime		proto :ptr sbyte
difftime	proto :time_t, :time_t

gmtime		proto :ptr time_t
localtime	proto :ptr time_t
mktime		proto :ptr tm
strftime	proto :ptr sbyte, :size_t, :ptr sbyte, :ptr tm
_strdate	proto :ptr sbyte
_strtime	proto :ptr sbyte
_tzset		proto
_time		proto :ptr time_t
_isindst	proto :ptr tm
_loctotime_t	proto y:SINT, m:SINT, d:SINT, h:SINT, m:SINT, s:SINT

ifndef _WTIME_DEFINED

_wasctime	proto :ptr tm
_wctime		proto :ptr time_t
wcsftime	proto :ptr wchar_t, :size_t, :ptr wchar_t, :ptr tm
_wstrdate	proto :ptr wchar_t
_wstrtime	proto :ptr wchar_t

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

__FTToTime	proto :LPFILETIME
__STToTime	proto :LPSYSTEMTIME
__TimeToFT	proto :time_t, :LPFILETIME
__TimeToST	proto :time_t, :LPSYSTEMTIME

DaysInFebruary	proto :dword
DaysInMonth	proto :dword, :dword
GetDayCount	proto :dword, :dword, :dword
GetWeekDay	proto :dword, :dword, :dword

atotime		proto :LPSTR
atodate		proto :LPSTR
fdatetostr	proto :LPSTR, :LPFILETIME
ftimetostr	proto :LPSTR, :LPFILETIME

TDateToString		proto :ptr sbyte, :time_t
SystemTimeToString	proto :ptr sbyte, :LPSYSTEMTIME
SystemDateToString	proto :ptr sbyte, :LPSYSTEMTIME

endif	;; __PE__

.list
