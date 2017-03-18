ifndef __WSUB_INC
__WSUB_INC equ <>

ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_MAX_PATH	equ 260
WMAXPATH	equ 2048	; the max length is 8000h..
MAXFBLOCK	equ 5000
WMAXFBLOCK	equ 300000

_A_READONLY	equ 0001h
_A_HIDDEN	equ 0002h
_A_SYSTEM	equ 0004h
_A_VOLID	equ 0008h
_A_DIRECTORY	equ 0010h
;_A_ARCHIVE	equ 0020h
_A_NORMAL	equ 0080h
_A_TEMPORARY	equ 0100h
_A_COMPRESSED	equ 0800h
_A_OFFLINE	equ 1000h
_A_NOT_INDEXED	equ 2000h
_A_ENCRYPTED	equ 4000h
_A_FATTRIB	equ 0000FFFFh

_FB_SELECTED	equ 00010000h
_FB_ROOTDIR	equ 00020000h
_FB_UPDIR	equ 00040000h
_FB_CDROOM	equ 00080000h
_FB_ARCHZIP	equ 00100000h
_FB_ARCHEXT	equ 00200000h
_FB_ZENCRYPTED	equ 00400000h	; if _FB_ARCHZIP
_FB_ZEXTLOCHD	equ 00800000h	; if _FB_ARCHZIP
_FB_ARCHIVE	equ _FB_ARCHEXT or _FB_ARCHZIP

_W_PANELID	equ 00000001h	; _P_PANELID
_W_VISIBLE	equ 00000002h	; _P_VISIBLE
_W_MINISTATUS	equ 00000004h	; _P_MINISTATUS
_W_WIDEVIEW	equ 00000008h	; _P_WIDEVIEW
_W_DETAIL	equ 00000010h	; _P_DETAIL
_W_DRVINFO	equ 00000020h	; _P_DRVINFO
_W_WHIDDEN	equ 00000040h	; _P_WHIDDEN - Hidden Panel
_P_FLAGMASK	equ 0000007Fh

_W_HIDDEN	equ 00000080h	; Hidden files
_W_LONGNAME	equ 00000100h
_W_SORTNAME	equ 00000000h
_W_SORTTYPE	equ 00000200h
_W_SORTDATE	equ 00000400h
_W_SORTSIZE	equ 00000600h
_W_NOSORT	equ 00000800h
_W_SORTSUB	equ 00001000h
_W_ROOTDIR	equ 00002000h
_W_CDROOM	equ 00004000h
_W_NETWORK	equ 00008000h
_W_REMOVABLE	equ 00010000h
_W_TEDIT	equ 00020000h
_W_ARCHZIP	equ 00100000h
_W_ARCHEXT	equ 00200000h
_W_MALLOC	equ 01000000h

_W_ARCHIVE	equ _W_ARCHZIP or _W_ARCHEXT
_W_DEFAULT	equ _W_SORTTYPE or _W_HIDDEN or _W_VISIBLE or _W_MINISTATUS or _W_LONGNAME

S_FBLK		STRUC
fb_flag		dd ?	; _FB_:_A_
fb_time		dd ?	; date:time
;fb_timecreate	dd ?	; File creation time
;fb_timeaccess	dd ?	; Last access time
fb_size		dq ?
fb_name		db 4 dup(?)
S_FBLK		ENDS
LPFBLK		TYPEDEF PTR S_FBLK

S_WSUB		STRUC
ws_flag		SIZE_T ?
ws_count	SIZE_T ?
ws_maxfb	SIZE_T ?
ws_mask		SIZE_T ?
ws_file		SIZE_T ?
ws_arch		SIZE_T ?
ws_path		SIZE_T ?
ws_fcb		SIZE_T ?
S_WSUB		ENDS	; 32 byte
LPWSUB		TYPEDEF PTR S_WSUB

externdef	cp_stdmask: SBYTE
externdef	cp_warning: SBYTE
externdef	cp_einitsub:SBYTE
externdef	cp_dotdot:  SBYTE	; ".."
externdef	cp_datefrm: SBYTE	; "%2u.%02u.%02u"
externdef	cp_timefrm: SBYTE	; "%2u:%02u"

externdef	__srcpath:SIZE_T
externdef	__outpath:SIZE_T
externdef	__srcfile:SIZE_T
externdef	__outfile:SIZE_T
externdef	_pgmpath:SIZE_T

fballoc		PROTO :LPSTR, :DWORD, :QWORD, :DWORD
fballocwf	PROTO :PVOID, :DWORD
fbupdir		PROTO :DWORD
fbinvert	PROTO :LPFBLK
fbselect	PROTO :LPFBLK
fbffirst	PROTO :PVOID, :DWORD
fballocff	PROTO :DWORD, :DWORD
fbcolor		PROTO :LPFBLK

wsalloc		PROTO :DWORD, :DWORD
wsopen		PROTO :LPWSUB
wsclose		PROTO :LPWSUB
wsinit		PROTO :LPWSUB
wsfree		PROTO :LPWSUB
wsread		PROTO :LPWSUB
wssort		PROTO :LPWSUB
wssetflag	PROTO :LPWSUB
wslocal		PROTO :LPWSUB
wschdrv		PROTO :LPWSUB, :DWORD
wsearch		PROTO :LPWSUB, :LPSTR
wsfblk		PROTO :LPWSUB, :DWORD
wsffirst	PROTO :LPWSUB
wsmkdir		PROTO :LPSTR
wscopy_open	PROTO ; eax, edx (__srcfile, __outfile)
wscopy_remove	PROTO ; eax (__outfile)

_WOPEN		equ 0x01
_WSAVE		equ 0x02
_WLOCAL		equ 0x04 ; use program or current directory
_WLOCK		equ 0x08 ; lock to this directory
_WNEWFILE	equ 0x10

wdlgopen	PROTO :LPSTR, :LPSTR, :DWORD
wgetfile	PROTO :LPSTR, :LPSTR, :DWORD

;;;;;;;;;;;;;;;;; __ZIP__

ER_ZIP		equ 2
ER_BADERR	equ 3
ER_MEM		equ 4
ER_CRCERR	equ 5
ER_NOZIP	equ 9
ER_FIND		equ 11
ER_OPEN		equ 12
ER_DISK		equ 50
ER_USERABORT	equ 66
ER_READARCH	equ -2

externdef	entryname:SIZE_T

wsopenarch	PROTO :LPWSUB
wzipread	PROTO :DWORD
wzipopen	PROTO
wzipclose	PROTO
wsdecomp	PROTO :DWORD, :DWORD, :DWORD
wzipadd		PROTO :QWORD, :DWORD, :DWORD
wzipdel		PROTO
wzipcopy	PROTO :DWORD, :DWORD, :DWORD
wsmkzipdir	PROTO :DWORD, :DWORD

dostounix	PROTO :LPSTR
unixtodos	PROTO :LPSTR

eropen		PROTO :LPSTR
ermkdir		PROTO :LPSTR
erdelete	PROTO :LPSTR
errnomsg	PROTO :LPSTR, :LPSTR, :LPSTR

S_WFBLK		STRUC
wf_attrib	dd ?	; DWORD File attributes
wf_timecreate	dq ?	; QWORD File creation time
wf_timeaccess	dq ?	; QWORD Last access time
wf_time		dq ?	; QWORD Last modification time
wf_size		dq ?	; QWORD File size
wf_reserved	dq ?
wf_name		db 260 dup(?)
wf_shortname	db 14 dup(?)
S_WFBLK		ENDS	;  318 byte

S_WFBLKW	STRUC
wf_attrib	dd ?	; DWORD File attributes
wf_timecreate	dq ?	; QWORD File creation time
wf_timeaccess	dq ?	; QWORD Last access time
wf_time		dq ?	; QWORD Last modification time
wf_size		dq ?	; QWORD File size
wf_reserved	dq ?
wf_name		dw 260 dup(?)
wf_shortname	dw 14 dup(?)
S_WFBLKW	ENDS

wfindfirst	PROTO :LPSTR, :PTR S_WFBLK, :SIZE_T
wfindnext	PROTO :PTR S_WFBLK, :HANDLE
wcloseff	PROTO :HANDLE

removefile	PROTO :LPSTR
removetemp	PROTO :LPSTR

filexist	PROTO :LPSTR
notsup		PROTO

.list
endif
