ifndef _WINDEF_
 include windef.inc
endif

.xlist
;
; declarations for wide character functions
;
ifndef __WCHAR_INC
__WCHAR_INC equ 1

ifndef _INTEGRAL_MAX_BITS
_INTEGRAL_MAX_BITS equ 64
endif

ifndef _WIN32
ifndef _WIN64
.err <ERROR: Only Win64 or Win32 targets supported>
endif
endif

;; Define _CRTIMP

ifdef __PE__
option	dllimport:<msvcrt>
endif

ifndef _TIME_T_DEFINED
time_t			typedef SDWORD
_TIME_T_DEFINED equ 1
endif

ifndef _WCHAR_T_DEFINED
wchar_t			typedef WORD
_WCHAR_T_DEFINED	equ 1
endif

WCHAR_MIN		equ 0
WCHAR_MAX		equ 0xFFFF

ifndef _WCTYPE_T_DEFINED
wint_t			typedef wchar_t
wctype_t		typedef wchar_t
_WCTYPE_T_DEFINED	equ 1
endif


ifndef _VA_LIST_DEFINED
ifdef  _M_ALPHA
va_list			STRUC
a0			LPSTR ? ;; pointer to first homed integer argument
offset			SINT ?	;; byte offset of next parameter
va_list			ENDS
else
va_list			typedef LPSTR
endif
_VA_LIST_DEFINED	equ 1
endif

ifndef WEOF
WEOF			equ 0xFFFF
endif

ifndef _FILE_DEFINED
_iobuf			STRUC
_ptr			LPSTR ?
_cnt			SINT ?
_base			LPSTR ?
_flag			SINT ?
_file			SINT ?
_charbuf		SINT ?
_bufsiz			SINT ?
_tmpfname		LPSTR ?
_iobuf			ENDS
FILE			typedef _iobuf
_FILE_DEFINED		equ 1
endif

;; Declare _iob[] array

ifndef _STDIO_DEFINED
externdef		_iob:FILE
endif  ;; _STDIO_DEFINED

ifndef _FSIZE_T_DEFINED
_fsize_t		typedef size_t	;; Could be 64 bits for Win32
_FSIZE_T_DEFINED	equ 1
endif

ifndef _WFINDDATA_T_DEFINED

_wfinddata_t		STRUC
attrib			dd ?
time_create		time_t ?	;; -1 for FAT file systems
time_access		time_t ?	;; -1 for FAT file systems
time_write		time_t ?
_size			dq ?
_name			wchar_t 260 dup(?)
_wfinddata_t		ENDS

if     _INTEGRAL_MAX_BITS GE 64
_wfinddatai64_t		STRUC
attrib			dd ?
time_create		time_t ?	;; -1 for FAT file systems
time_access		time_t ?	;; -1 for FAT file systems
time_write		time_t ?
_size			dq ?
_name			wchar_t 260 dup(?)
_wfinddatai64_t		ENDS
endif

_WFINDDATA_T_DEFINED	equ 1
endif

;; define NULL pointer value

ifndef NULL
NULL			equ 0
endif


ifndef _CTYPE_DISABLE_MACROS
externdef		_ctype:word
externdef		_pctype:ptr word
externdef		_pwctype:ptr wctype_t
endif  ;; _CTYPE_DISABLE_MACROS


;; set bit masks for the possible character types

_UPPER			equ 0x1	    ;; upper case letter
_LOWER			equ 0x2	    ;; lower case letter
_DIGIT			equ 0x4	    ;; digit[0-9]
_SPACE			equ 0x8	    ;; tab, carriage return, newline,
;; vertical tab or form feed
_PUNCT			equ 0x10    ;; punctuation character
_CONTROL		equ 0x20    ;; control character
_BLANK			equ 0x40    ;; space char
_HEX			equ 0x80    ;; hexadecimal digit

_LEADBYTE		equ 0x8000  ;; multibyte leadbyte
_ALPHA			equ 0x0100 OR _UPPER OR _LOWER	;; alphabetic character


;; Function prototypes

ifndef _WCTYPE_DEFINED

;; Character classification function prototypes
;; also declared in ctype.h

iswalpha	proto :wint_t
iswupper	proto :wint_t
iswlower	proto :wint_t
iswdigit	proto :wint_t
iswxdigit	proto :wint_t
iswspace	proto :wint_t
iswpunct	proto :wint_t
iswalnum	proto :wint_t
iswprint	proto :wint_t
iswgraph	proto :wint_t
iswcntrl	proto :wint_t
iswascii	proto :wint_t
isleadbyte	proto :SINT

towupper	proto :wchar_t
towlower	proto :wchar_t

iswctype	proto :wint_t, :wctype_t

_WCTYPE_DEFINED equ 1
endif

ifndef _WDIRECT_DEFINED

;; also declared in direct.h

_wchdir		proto :ptr wchar_t
_wgetcwd	proto :ptr wchar_t, :SINT
_wgetdcwd	proto :SINT, :ptr wchar_t, :SINT
_wmkdir		proto :ptr wchar_t
_wrmdir		proto :ptr wchar_t

_WDIRECT_DEFINED equ 1
endif

ifndef _WIO_DEFINED

;; also declared in io.h

_waccess	proto :ptr wchar_t, :SINT
_wchmod		proto :ptr wchar_t, :SINT
_wcreat		proto :ptr wchar_t, :SINT
_wfindfirst	proto :ptr wchar_t, :ptr _wfinddata_t
_wfindnext	proto :LONG, :ptr _wfinddata_t
_wunlink	proto :ptr wchar_t
_wrename	proto :ptr wchar_t, :ptr wchar_t
_wopen		proto _CDecl :ptr wchar_t, :SINT, :VARARG
_wsopen		proto _CDecl :ptr wchar_t, :SINT, :SINT, :VARARG
_wmktemp	proto :ptr wchar_t

if     _INTEGRAL_MAX_BITS GE 64
_wfindfirsti64	proto :ptr wchar_t, :ptr _wfinddatai64_t
_wfindnexti64	proto :LONG, :ptr _wfinddatai64_t
endif

_WIO_DEFINED	equ 1
endif

ifndef _WLOCALE_DEFINED

;; wide function prototypes, also declared in wchar.h

_wsetlocale	proto :SINT, :ptr wchar_t

_WLOCALE_DEFINED equ 1
endif

ifndef _WPROCESS_DEFINED

;; also declared in process.h

_wexecl		proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
_wexecle	proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
_wexeclp	proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
_wexeclpe	proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
_wexecv		proto :ptr wchar_t, :ptr wchar_t
_wexecve	proto :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wexecvp	proto :ptr wchar_t, :ptr wchar_t
_wexecvpe	proto :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wspawnl	proto _CDecl :SINT, :ptr wchar_t, :ptr wchar_t, :VARARG
_wspawnle	proto _CDecl :SINT, :ptr wchar_t, :ptr wchar_t, :VARARG
_wspawnlp	proto _CDecl :SINT, :ptr wchar_t, :ptr wchar_t, :VARARG
_wspawnlpe	proto _CDecl :SINT, :ptr wchar_t, :ptr wchar_t, :VARARG
_wspawnv	proto :SINT, :ptr wchar_t, :ptr wchar_t
_wspawnve	proto :SINT, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wspawnvp	proto :SINT, :ptr wchar_t, :ptr wchar_t
_wspawnvpe	proto :SINT, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wsystem	proto :ptr wchar_t

_WPROCESS_DEFINED equ 1
endif

ifndef _WCTYPE_DEFINED
ifndef _WCTYPE_INLINE_DEFINED

iswalpha macro _c
	exitm<iswctype(_c,_APHA)>
	endm
iswupper macro _c
	exitm<iswctype(_c,_UPPER)>
	endm
iswlower macro _c
	exitm<iswctype(_c,_LOWER)>
	endm
iswdigit macro _c
	exitm<iswctype(_c,_DIGIT)>
	endm
iswxdigit macro _c
	exitm<iswctype(_c,_HEX)>
	endm
iswspace macro _c
	exitm<iswctype(_c,_SPACE)>
	endm
iswpunct macro _c
	exitm<iswctype(_c,_PUNCT)>
	endm
iswalnum macro _c
	exitm<iswctype(_c,_APHA OR _DIGIT)>
	endm
iswprint macro _c
	exitm<iswctype(_c,_BLANK OR _PUNCT OR _APHA OR _DIGIT)>
	endm
iswgraph macro _c
	exitm<iswctype(_c,_PUNCT OR _APHA OR _DIGIT)>
	endm
iswcntrl macro _c
	exitm<iswctype(_c,_CONTROL)>
	endm
iswascii macro _c
	exitm<_c LT 0x80>
	endm

ifndef _CTYPE_DISABLE_MACROS
isleadbyte macro _c
	exitm<_pctype[_c] AND _LEADBYTE>
	endm
endif  ;; _CTYPE_DISABLE_MACROS

_WCTYPE_INLINE_DEFINED equ 1
endif  ;; _WCTYPE_INLINE_DEFINED
endif  ;; _WCTYPE_DEFINED


ifndef _POSIX_

;; define structure for returning status information

ifndef _INO_T_DEFINED
_ino_t			typedef WORD	;; i-node number (not used on DOS)
if NOT __STDC__
;; Non-ANSI name for compatibility
ino_t			typedef WORD
endif
_INO_T_DEFINED		equ 1
endif

ifndef _DEV_T_DEFINED
_dev_t			typedef UINT	  ;; device code
if NOT __STDC__
;; Non-ANSI name for compatibility
dev_t			typedef UINT
endif
_DEV_T_DEFINED		equ 1
endif

ifndef _OFF_T_DEFINED
ifdef _WIN64
_off_t			typedef QWORD	;; file offset value
else
_off_t			typedef SDWORD
endif
if NOT __STDC__
;; Non-ANSI name for compatibility
off_t			typedef _off_t
endif
_OFF_T_DEFINED		equ 1
endif

ifndef _STAT_DEFINED

_stat			STRUC
st_dev			_dev_t ?
st_ino			_ino_t ?
st_mode			dw ?
st_nlink		dw ?
st_uid			dw ?
st_gid			dw ?
st_rdev			_dev_t ?
st_size			_off_t ?
st_atime		time_t ?
st_mtime		time_t ?
st_ctime		time_t ?
_stat			ENDS

if NOT __STDC__
;; Non-ANSI names for compatibility
stat			STRUC
st_dev			_dev_t ?
st_ino			_ino_t ?
st_mode			dw ?
st_nlink		dw ?
st_uid			dw ?
st_gid			dw ?
st_rdev			_dev_t ?
st_size			_off_t ?
st_atime		time_t ?
st_mtime		time_t ?
st_ctime		time_t ?
stat			ENDS
endif  ;; __STDC__

if     _INTEGRAL_MAX_BITS GE 64
_stati64		STRUC
st_dev			_dev_t ?
st_ino			_ino_t ?
st_mode			dw ?
st_nlink		dw ?
st_uid			dw ?
st_gid			dw ?
st_rdev			_dev_t ?
st_size			dq ?
st_atime		time_t ?
st_mtime		time_t ?
st_ctime		time_t ?
_stati64		ENDS
endif

_STAT_DEFINED equ 1
endif


ifndef _WSTAT_DEFINED

;; also declared in stat.h

_wstatproto	proto :ptr wchar_t, :ptr _stat

if     _INTEGRAL_MAX_BITS GE 64
_wstati64	proto :ptr wchar_t, :ptr _stati64
endif

_WSTAT_DEFINED	equ 1
endif

endif  ;; NOT _POSIX_


ifndef _WSTDIO_DEFINED

;; also declared in stdio.h

ifdef  _POSIX_
_wfsopenproto	proto :ptr wchar_t, :ptr wchar_t
else
_wfsopenproto	proto :ptr wchar_t, :ptr wchar_t, :SINT
endif

fgetwc		proto :ptr FILE
_fgetwchar	proto
fputwc		proto :wint_t, :ptr FILE
_fputwchar	proto :wint_t
getwc		proto :ptr FILE
getwchar	proto
putwc		proto :wint_t, :ptr FILE
putwchar	proto :wint_t
ungetwc		proto :wint_t, :ptr FILE
fgetws		proto :ptr wchar_t, :SINT, :ptr FILE
fputws		proto :ptr wchar_t, :ptr FILE
_getws		proto :ptr wchar_t
_putws		proto :ptr wchar_t
fwprintf	proto _CDecl :ptr FILE, :ptr wchar_t, :VARARG
wprintf		proto _CDecl :ptr wchar_t, :VARARG
_snwprintf	proto _CDecl :ptr wchar_t, :size_t, :ptr wchar_t, :VARARG
swprintf	proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
vfwprintf	proto :ptr FILE, :ptr wchar_t, :PVOID
vwprintf	proto :ptr wchar_t, :PVOID
_vsnwprintf	proto :ptr wchar_t, :size_t, :ptr wchar_t, :PVOID
vswprintf	proto :ptr wchar_t, :ptr wchar_t, :PVOID
fwscanf		proto _CDecl :ptr FILE, :ptr wchar_t, :VARARG
swscanf		proto _CDecl :ptr wchar_t, :ptr wchar_t, :VARARG
wscanf		proto _CDecl :ptr wchar_t, :VARARG
if 0
getwchar macro
	exitm<fgetwc(stdin)>
	endm
putwchar macro _c
	exitm<fputwc(_c,stdout)>
	endm

getwc	macro _stm
	exitm<fgetwc(_stm)>
	endm
putwc	macro _c,_stm
	exitm<fputwc(_c,_stm)>
	endm
endif
_wfdopen	proto :SINT, :ptr wchar_t
_wfopen		proto :ptr wchar_t, :ptr wchar_t
_wfreopen	proto :ptr wchar_t, :ptr wchar_t, :ptr FILE
_wperror	proto :ptr wchar_t
_wpopen		proto :ptr wchar_t, :ptr wchar_t
_wremove	proto :ptr wchar_t
_wtempnam	proto :ptr wchar_t, :ptr wchar_t
_wtmpnam	proto :ptr wchar_t

_WSTDIO_DEFINED equ 1
endif


ifndef _WSTDLIB_DEFINED

;; also declared in stdlib.h

_itow		proto :SINT, :ptr wchar_t, :SINT
_ltow		proto :LONG, :ptr wchar_t, :SINT
_ultow		proto :DWORD, :ptr wchar_t, :SINT
wcstod		proto :ptr wchar_t, :ptr wchar_t
wcstol		proto :ptr wchar_t, :ptr wchar_t, :SINT
wcstoul		proto :ptr wchar_t, :ptr wchar_t, :SINT
_wgetenv	proto :ptr wchar_t
_wsystem	proto :ptr wchar_t
_wtoi		proto :ptr wchar_t
_wtol		proto :ptr wchar_t

if     _INTEGRAL_MAX_BITS GE 64
_i64tow		proto :qword, :ptr wchar_t, :SINT
_ui64tow	proto :sqword, :ptr wchar_t, :SINT
_wtoi64		proto :ptr wchar_t
endif

_WSTDLIB_DEFINED equ 1
endif

ifndef _POSIX_

ifndef _WSTDLIBP_DEFINED

;; also declared in stdlib.h

_wfullpath	proto :ptr wchar_t, :ptr wchar_t, :size_t
_wmakepath	proto :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wperror	proto :ptr wchar_t
_wputenv	proto :ptr wchar_t
_wsearchenv	proto :ptr wchar_t, :ptr wchar_t, :ptr wchar_t
_wsplitpath	proto :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t, :ptr wchar_t

_WSTDLIBP_DEFINED equ 1
endif

endif  ;; _POSIX_


ifndef _WSTRING_DEFINED

;; also declared in string.h

wcscat		proto :ptr wchar_t, :ptr wchar_t
wcschr		proto :ptr wchar_t, :wchar_t
wcscmp		proto :ptr wchar_t, :ptr wchar_t
wcscpy		proto :ptr wchar_t, :ptr wchar_t
wcscspn		proto :ptr wchar_t, :ptr wchar_t
wcslen		proto :ptr wchar_t
wcsncat		proto :ptr wchar_t, :ptr wchar_t, :size_t
wcsncmp		proto :ptr wchar_t, :ptr wchar_t, :size_t
wcsncpy		proto :ptr wchar_t, :ptr wchar_t, :size_t
wcspbrk		proto :ptr wchar_t, :ptr wchar_t
wcsrchr		proto :ptr wchar_t, :wchar_t
wcsspn		proto :ptr wchar_t, :ptr wchar_t
wcsstr		proto :ptr wchar_t, :ptr wchar_t
wcstok		proto :ptr wchar_t, :ptr wchar_t
_wcsdup		proto :ptr wchar_t
_wcsicmp	proto :ptr wchar_t, :ptr wchar_t
_wcsnicmp	proto :ptr wchar_t, :ptr wchar_t, :size_t
_wcsnset	proto :ptr wchar_t, :wchar_t, :size_t
_wcsrev		proto :ptr wchar_t
_wcsset		proto :ptr wchar_t, :wchar_t
_wcslwr		proto :ptr wchar_t
_wcsupr		proto :ptr wchar_t
wcsxfrm		proto :ptr wchar_t, :ptr wchar_t, :size_t
wcscoll		proto :ptr wchar_t, :ptr wchar_t
_wcsicoll	proto :ptr wchar_t, :ptr wchar_t
_wcsncoll	proto :ptr wchar_t, :ptr wchar_t, :size_t
_wcsnicoll	proto :ptr wchar_t, :ptr wchar_t, :size_t

;; Old names
wcswcs		equ <wcsstr>

if NOT __STDC__

;; prototypes for oldnames.lib functions
wcsdup		proto :ptr wchar_t
wcsicmp		proto :ptr wchar_t, :ptr wchar_t
wcsnicmp	proto :ptr wchar_t, :ptr wchar_t, :size_t
wcsnset		proto :ptr wchar_t, :wchar_t, :size_t
wcsrev		proto :ptr wchar_t
wcsset		proto :ptr wchar_t, :wchar_t
wcslwr		proto :ptr wchar_t
wcsupr		proto :ptr wchar_t
wcsicoll	proto :ptr wchar_t, :ptr wchar_t

endif  ;; NOT __STDC__

_WSTRING_DEFINED equ 1
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

ifndef _WTIME_DEFINED

;; also declared in time.h

_wasctime	proto :ptr tm
_wctime		proto :ptr time_t
wcsftime	proto :ptr wchar_t, :size_t, :ptr wchar_t, :ptr tm
_wstrdate	proto :ptr wchar_t
_wstrtime	proto :ptr wchar_t

_WTIME_DEFINED	equ 1
endif



mbstate_t	typedef SINT
_Wint_t		typedef wchar_t

btowc		proto :SINT
mbrlen		proto :LPSTR, :size_t, :ptr mbstate_t
mbrtowc		proto :ptr wchar_t, :LPSTR, :size_t, :ptr mbstate_t
mbsrtowcs	proto :ptr wchar_t, :LPSTR, :size_t, :ptr mbstate_t

wcrtomb		proto :LPSTR, :wchar_t, :ptr mbstate_t
wcsrtombs	proto :LPSTR, :ptr wchar_t, :size_t, :ptr mbstate_t
wctob		proto :wint_t

endif  ;; __WCHAR_INC

.list
