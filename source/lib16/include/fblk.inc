ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_A_FATTRIB	equ 003Fh
_A_SELECTED	equ 0040h
_A_UPDIR	equ 0080h
;_A_CDROOM	equ 0100h	; _A_TEMPORARY
_A_ZENCRYPTED	equ 0200h	; _A_SPARSE_FILE
_A_ZEXTLOCHD	equ 0400h	; _A_REPARSEPOINT
;_A_COMPRESSED	equ 0800h	; _A_COMPRESSED
;_A_OFFLINE	equ 1000h	; _A_OFFLINE
_A_ROOTDIR	equ 2000h	; _A_NOT_INDEXED
_A_ARCHEXT	equ 4000h	; _A_ENCRYPTED
_A_ARCHZIP	equ 8000h
_A_ARCHIVE	equ 0C000h

S_FBLK		STRUC
fb_flag		dw ?
fb_time		dd ?
fb_size		dd ?
fb_name		db 4 dup(?)
S_FBLK		ENDS

externdef	cp_dotdot:  BYTE	; ".."
externdef	cp_datefrm: BYTE	; "%2u.%02u.%02u"
externdef	cp_timefrm: BYTE	; "%2u:%02u"

fballoc		PROTO _CType :PTR BYTE, :DWORD, :DWORD, :WORD
fballocwf	PROTO _CType :DWORD, :WORD
fbupdir		PROTO _CType :WORD
fbinvert	PROTO _CType :DWORD
fbselect	PROTO _CType :DWORD
fbffirst	PROTO _CType :DWORD, :WORD
fballocff	PROTO _CType :DWORD, :WORD

fbcolor PROTO _CType
fbputsl PROTO pascal :DWORD, :WORD, :WORD
fbputsd PROTO pascal :DWORD, :WORD, :WORD
ifdef __LFN__
fbputll PROTO pascal :DWORD, :WORD, :WORD
fbputld PROTO pascal :DWORD, :WORD, :WORD
endif
fbputfile PROTO pascal :DWORD, :WORD, :WORD

.list
