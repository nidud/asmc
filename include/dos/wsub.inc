ifndef __LIBC_INC
 include libc.inc
endif

.xlist

WMAXPATH	equ 260
MAXFBLOCK	equ 3000
WMAXFBLOCK	equ 3FFFh

_W_ROOTDIR	equ 0001h
_W_LONGNAME	equ 0010h
_W_HIDDEN	equ 0040h
_W_FLOPPY	equ 0080h	; wsetflag -- not used
_W_CDROOM	equ 0100h
_W_NETWORK	equ 0180h
_W_SORTNAME	equ 0000h
_W_SORTTYPE	equ 0200h
_W_SORTDATE	equ 0400h
_W_SORTSIZE	equ 0600h
_W_NOSORT	equ 0800h
_W_SORTSUB	equ 1000h
_W_ARCHEXT	equ 4000h
_W_ARCHZIP	equ 8000h
_W_ARCHIVE	equ _W_ARCHZIP or _W_ARCHEXT

S_PATH		STRUC
wp_flag		dw ?
wp_mask		db  32 dup(?)
wp_file		db 260 dup(?)
wp_arch		db 260 dup(?)
wp_path		db 260 dup(?)
S_PATH		ENDS	;  816 byte

S_WSUB		STRUC
ws_count	dw ?
ws_maxfb	dw ?
ws_flag		dd ?
ws_mask		dd ?
ws_file		dd ?
ws_arch		dd ?
ws_path		dd ?
ws_fcb		dd ?
S_WSUB		ENDS	; 28 byte

S_DISK		STRUC
di_flag		dw ?	; align FBLK
di_time		dd ?
di_sizeax	dd ?
di_sizedx	dd ?
di_name		db 16 dup(?)
S_DISK		ENDS

externdef	drvinfo:S_DISK
externdef	cp_stdmask:BYTE
externdef	cp_warning:BYTE
externdef	cp_emaxfb:BYTE
externdef	cp_einitsub:BYTE
externdef	__srcpath:BYTE
externdef	__outpath:BYTE
externdef	__srcfile:BYTE
externdef	__outfile:BYTE

wsopen		PROTO _CType :DWORD
wsclose		PROTO _CType :DWORD
wsinit		PROTO _CType :DWORD
wsfree		PROTO _CType :DWORD
wsread		PROTO _CType :DWORD
wssort		PROTO _CType :DWORD
wssetflag	PROTO _CType :DWORD
wslocal		PROTO _CType :DWORD
wschdrv		PROTO _CType :DWORD, :WORD
wsearch		PROTO _CType :DWORD, :PTR BYTE
wsfblk		PROTO _CType :DWORD, :WORD
wsffirst	PROTO _CType :DWORD
wsmkdir		PROTO _CType :PTR BYTE
wsetprogress	PROTO _CType
wdlgopen	PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
wgetfile	PROTO _CType :PTR BYTE, :WORD
wscopy_open	PROTO _CType ; eax, edx (__srcfile, __outfile)
wscopy_remove	PROTO _CType ; eax (__outfile)

ifdef __ZIP__
 externdef	entryname: BYTE
 wsopenarch	PROTO _CType :DWORD
 wzipread	PROTO _CType :DWORD
 wzipopen	PROTO _CType
 wzipclose	PROTO _CType
 wsdecomp	PROTO _CType :DWORD, :DWORD, :DWORD
 wzipadd	PROTO _CType :DWORD, :DWORD, :WORD
 wzipcopy	PROTO _CType :DWORD, :DWORD, :DWORD
 wzipcopypath	PROTO _CType :DWORD, :DWORD, :DWORD
 wzipcopyfile	PROTO _CType :DWORD, :DWORD, :DWORD
 wzipfindentry	PROTO _CType :DWORD, :WORD
endif

.list
