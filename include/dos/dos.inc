ifndef __LIBC_INC
 include libc.inc
endif

.xlist

SEEK_CUR	equ 1
SEEK_END	equ 2
SEEK_SET	equ 0

_A_NORMAL	equ 00h
_A_RDONLY	equ 01h
_A_HIDDEN	equ 02h
_A_SYSTEM	equ 04h
_A_VOLID	equ 08h
_A_SUBDIR	equ 10h
_A_ARCH		equ 20h
_A_STDFILES	equ _A_ARCH or _A_RDONLY or _A_SYSTEM or _A_SUBDIR
_A_ALLFILES	equ _A_STDFILES or _A_HIDDEN

S_DISKFREE	STRUC
df_size		dw ?
df_version	dw ?
df_sclus	dd ?
df_bsec		dd ?
df_avail	dd ?
df_total	dd ?
df_phavail	dd ?
df_phtotal	dd ?
df_alavail	dd ?
df_altotal	dd ?
df_reserved	db 8 dup(?)
S_DISKFREE	ENDS

S_FFBLK		STRUC
ff_reserved	db 21 dup(?)
ff_attrib	db ?
ff_ftime	dw ?
ff_fdate	dw ?
ff_fsize	dd ?
ff_name		db 13 dup(?)
S_FFBLK		ENDS

ifdef __LFN__
externdef	_ifsmgr:BYTE
endif
externdef	_osversion:WORD
externdef	_osminor:BYTE
externdef	_osmajor:BYTE
externdef	_psp:WORD
externdef	envseg:WORD

findfirst	PROTO _CType :DWORD, :DWORD, :WORD
findnext	PROTO _CType :DWORD
beep		PROTO _CType :WORD, :WORD

externdef	_argc:WORD
externdef	_argv:DWORD

osmaperr	PROTO
externdef	errno:WORD
externdef	doserrno:WORD

S_FTIME		STRUC
ft_time		dw ?
ft_date		dw ?
ft_high		dd ?
S_FTIME		ENDS

S_WFBLK		STRUC
wf_attrib	dd ?		; DWORD File attributes
wf_timecreate	S_FTIME <>	; QWORD File creation time
wf_timeaccess	S_FTIME <>	; QWORD Last access time
wf_time		S_FTIME <>	; QWORD Last modification time
wf_sizedx	dd ?		; QWORD File size
wf_sizeax	dd ?		; - low DWORD
wf_reserved	db 8 dup(?)
wf_name		db 260 dup(?)
wf_shortname	db 14 dup(?)
S_WFBLK		ENDS	;  318 byte

delay		PROTO _CType :WORD
dosdate		PROTO _CType
dostime		PROTO _CType
getday		PROTO _CType
getsec		PROTO _CType
getmin		PROTO _CType
gethour		PROTO _CType
getmnd		PROTO _CType
getyear		PROTO _CType
getdatew	PROTO _CType

remove		PROTO _CType :DWORD
rename		PROTO _CType :DWORD, :DWORD

setftime	PROTO _CType :WORD, :PTR S_FTIME
_dos_setftime	PROTO _CType :WORD, :WORD, :WORD
setftime_create PROTO _CType :WORD, :PTR S_FTIME
_dos_setftime_create PROTO _CType :WORD, :WORD, :WORD

getftime	PROTO _CType :WORD, :PTR S_FTIME
getftime_access PROTO _CType :WORD, :PTR S_FTIME
getftime_create PROTO _CType :WORD, :PTR S_FTIME
_dos_getftime	PROTO _CType :WORD, :DWORD, :DWORD
_dos_getftime_access PROTO _CType :WORD, :DWORD, :DWORD
_dos_getftime_create PROTO _CType :WORD, :DWORD, :DWORD

_dos_setfileattr PROTO _CType :DWORD, :WORD
_dos_getfileattr PROTO _CType :DWORD, :DWORD

getfattr	PROTO _CType :DWORD
filexist	PROTO _CType :DWORD
wfindfirst	PROTO _CType :DWORD, :DWORD, attrib:WORD
wfindnext	PROTO _CType :DWORD, :WORD
wcloseff	PROTO _CType :WORD

ifdef __LFN__
wsetfattr	PROTO _CType :DWORD, :WORD
wgetfattr	PROTO _CType :DWORD
wsetacdate	PROTO _CType :DWORD, :WORD
wsetwrdate	PROTO _CType :DWORD, :WORD, :WORD
wsetcrdate	PROTO _CType :DWORD, :WORD, :WORD
wgetacdate	PROTO _CType :DWORD
wgetwrdate	PROTO _CType :DWORD
wgetcrdate	PROTO _CType :DWORD
wfullpath	PROTO _CType :DWORD, :WORD
wvolinfo	PROTO _CType :PTR BYTE, :PTR BYTE
endif

wgetcwd		PROTO _CType :DWORD, :WORD
wlongname	PROTO _CType :DWORD, :DWORD
wlongpath	PROTO _CType :DWORD, :DWORD
wshortname	PROTO _CType :DWORD
removefile	PROTO _CType :DWORD
removetemp	PROTO _CType :DWORD

GetTickCount	PROTO _CType

.list
