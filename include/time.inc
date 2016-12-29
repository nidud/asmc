ifndef __LIBC_INC
 include libc.inc
endif

.xlist
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

S_TM		STRUC
tm_sec		dd ?	; seconds after the minute - [0,59]
tm_min		dd ?	; minutes after the hour - [0,59]
tm_hour		dd ?	; hours since midnight - [0,23]
tm_mday		dd ?	; day of the month - [1,31]
tm_mon		dd ?	; months since January - [0,11]
tm_year		dd ?	; years since 1900
tm_wday		dd ?	; days since Sunday - [0,6]
tm_yday		dd ?	; days since January 1 - [0,365]
tm_isdst	dd ?	; daylight savings time flag
S_TM		ENDS

TIME_T		TYPEDEF SDWORD
LPTIME		TYPEDEF PTR TIME_T
LPFILETIME	TYPEDEF PTR FILETIME
LPSYSTEMTIME	TYPEDEF PTR SYSTEMTIME

localtime	PROTO :LPTIME
gmtime		PROTO :LPTIME
_time		PROTO :LPTIME
_tzset		PROTO
_isindst	PROTO :PTR S_TM
_loctotime_t	PROTO y:SINT, m:SINT, d:SINT, h:SINT, m:SINT, s:SINT
clock		PROTO

externdef	_days:DWORD
externdef	_lpdays:DWORD
externdef	_timezone:DWORD
externdef	_daylight:DWORD
externdef	_tzname:LPSTR
externdef	__dnames:BYTE
externdef	__mnames:BYTE

__FTToTime	PROTO :LPFILETIME
__STToTime	PROTO :LPSYSTEMTIME
__TimeToFT	PROTO :TIME_T, :LPFILETIME
__TimeToST	PROTO :TIME_T, :LPSYSTEMTIME

;;;;;;;;;;;;;;;;;;;;;;; kernel32.dll

TIME_ZONE_INFORMATION	STRUC
Bias			DD ?
StandardName		DW 32 dup(?)
StandardDate		SYSTEMTIME <>
StandardBias		DD ?
DaylightName		DW 32 dup(?)
DaylightDate		SYSTEMTIME <>
DaylightBias		DD ?
TIME_ZONE_INFORMATION	ENDS

;VOID
Sleep proto \
	dwMilliseconds: DWORD	; sleep time in milliseconds
;DWORD
GetTickCount proto
;VOID
GetLocalTime proto \
	lpSystemTime:	LPSYSTEMTIME	; address of system time structure
;BOOL
FileTimeToSystemTime proto \
	lpFileTime:	LPFILETIME,	; pointer to file time to convert
	lpSystemTime:	LPSYSTEMTIME	; pointer to structure to receive system time
;BOOL
SystemTimeToFileTime proto \
	lpSystemTime:	LPSYSTEMTIME,	; address of system time to convert
	lpFileTime:	LPFILETIME	; address of buffer for converted file time
;BOOL
FileTimeToLocalFileTime proto \
	lpFileTime:	LPFILETIME,	; pointer to UTC file time to convert
	lpLocalFileTime:LPFILETIME	; pointer to converted file time
;BOOL
LocalFileTimeToFileTime proto \
	lpLocalFileTime:LPFILETIME,	; address of local file time to convert
	lpFileTime:	LPFILETIME	; address of converted file time
;int
GetTimeFormatA proto \
	Locale:		DWORD,		; (LCID) locale for which time is to be formatted
	dwFlags:	DWORD,		; flags specifying function options
	lpTime:		LPSYSTEMTIME,	; time to be formatted
	lpFormat:	LPSTR,		; time format string
	lpTimeStr:	LPSTR,		; buffer for storing formatted string
	cchTime:	DWORD		; size, in bytes or characters, of the buffer
GetTimeFormatW proto \
	Locale:		DWORD,
	dwFlags:	DWORD,
	lpTime:		LPSYSTEMTIME,
	lpFormat:	LPWSTR,
	lpTimeStr:	LPWSTR,
	cchTime:	DWORD
;int
GetDateFormatA proto \
	Locale:		DWORD,		; (LCID) locale for which date is to be formatted
	dwFlags:	DWORD,		; flags specifying function options
	lpDate:		LPSYSTEMTIME,	; date to be formatted
	lpFormat:	LPSTR,		; date format string
	lpDateStr:	LPSTR,		; buffer for storing formatted string
	cchDate:	DWORD		; size of buffer
GetDateFormatW proto \
	Locale:		DWORD,
	dwFlags:	DWORD,
	lpDate:		LPSYSTEMTIME,
	lpFormat:	LPWSTR,
	lpDateStr:	LPWSTR,
	cchDate:	DWORD
;LCID
GetUserDefaultLCID proto
;DWORD
GetTimeZoneInformation proto \
	lpTimeZoneInformation:	PTR TIME_ZONE_INFORMATION ; address of time-zone settings

IFDEF _UNICODE
GetTimeFormat	equ	<GetTimeFormatW>
GetDateFormat	equ	<GetDateFormatW>
ELSE
GetTimeFormat	equ	<GetTimeFormatA>
GetDateFormat	equ	<GetDateFormatA>
ENDIF

delay		equ	<Sleep>

; BOOL - 16-bit date and time
DosDateTimeToFileTime proto \
	wFatDate:	DWORD,		; (WORD) 16-bit MS-DOS date
	wFatTime:	DWORD,		; (WORD) 16-bit MS-DOS time
	lpFileTime:	LPFILETIME	; pointer to buffer for 64-bit file time
; BOOL
FileTimeToDosDateTime proto \
	lpFileTime:	LPFILETIME,	; pointer to 64-bit file time
	lpFatDate:	LPWORD,		; pointer to variable for MS-DOS date
	lpFatTime:	LPWORD		; pointer to variable for MS-DOS time

.list
