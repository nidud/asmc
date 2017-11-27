ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_A_NORMAL	equ 00h
_A_RDONLY	equ 01h
_A_HIDDEN	equ 02h
_A_SYSTEM	equ 04h
_A_SUBDIR	equ 10h
_A_ARCH		equ 20h

SEEK_SET	equ 0
SEEK_CUR	equ 1
SEEK_END	equ 2

IO_SEARCHCASE	equ 0001h
IO_SEARCHHEX	equ 0002h
IO_SEARCHSET	equ 0004h
IO_SEARCHCUR	equ 0008h
IO_SEARCHMASK	equ 000Fh
IO_SEARCHSUB	equ 0020h

IO_LINEBUF	equ 0040h	; Line buffer
IO_STRINGB	equ 0080h	; String buffer
IO_CRYPT	equ 0100h	; Crypted file
IO_USEUPD	equ 0200h	; Progress
IO_UPDTOTAL	equ 0400h	; Add Read/Write size to total
IO_USECRC	equ 0800h	; Update CRC on read/write
IO_USEBITS	equ 1000h	; Align bits on read/write
IO_CLIPBOARD	equ 2000h	; Flush to clipboard
IO_MEMREAD	equ 4000h	; View memory area
IO_ERROR	equ 8000h	; Write fault

S_IOST		STRUC
ios_bp		dd ?
ios_i		dw ?
ios_c		dw ?
ios_size	dw ?
ios_flag	dw ?
ios_file	dw ?
ios_l		dw ?
ios_bb		dd ?
ios_total	dd ?
ios_offset	dd ?
S_IOST		ENDS

externdef	STDI:S_IOST
externdef	STDO:S_IOST
externdef	crctab:DWORD
externdef	oupdate:size_p
externdef	tinfo:WORD

OSTDI		equ offset STDI
OSTDO		equ offset STDO

oupdcrc		PROTO
otell		PROTO
owrite		PROTO
oopenst		PROTO
oopencl		PROTO

oread		PROTO
oputc		PROTO
ogetc		PROTO

oclose		PROTO _CType :DWORD
oinitst		PROTO _CType :DWORD, :WORD
ofreest		PROTO _CType :DWORD
continuesearch	PROTO _CType
oflush		PROTO _CType
ofread		PROTO _CType
oungetc		PROTO _CType

ogetl		PROTO _CType :DWORD, :DWORD, :WORD
ogets		PROTO _CType
oopen		PROTO _CType :DWORD, :WORD
oopens		PROTO _CType :DWORD, :WORD
iopens		PROTO _CType :DWORD, :WORD
close		PROTO _CType :WORD
ogetouth	PROTO _CType :DWORD
openfile	PROTO _CType :DWORD, :WORD, :WORD
ogetouth	PROTO _CType :DWORD
oseek		PROTO _CType :DWORD, :WORD
oseekl		PROTO _CType :DWORD, :WORD
ocopy		PROTO _CType :DWORD
osearch		PROTO _CType :WORD, :DWORD, :DWORD, :WORD, :WORD
cmdsearch	PROTO _CType :DWORD
oprintf		PROTO _CDecl :DWORD, :VARARG

ugetc		PROTO _CType
uputc		PROTO _CType :WORD

.list
