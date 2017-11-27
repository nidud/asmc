ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_A_NORMAL	equ 80h
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

IO_RETURNLF	equ 0040h	; return line index on search
IO_GLMEM	equ 0080h	; save pointer in ios_line (ios_bp aligned xxxx0000h)
IO_CRYPT	equ 0100h	; Crypted file
IO_USEUPD	equ 0200h	; Progress
IO_UPDTOTAL	equ 0400h	; Add Read/Write size to total
IO_USECRC	equ 0800h	; Update CRC on read/write
IO_MEMBUF	equ 4000h	; File in buffer or memory addr
IO_ERROR	equ 8000h	; Write fault

OO_MEM64K	equ 00010000h	; malloc(segment) aligned xxxx0000h
OO_MEMBUF	equ 00000000h	; read, set ios_fsize and IO_MEMBUF

S_IOST		STRUC
ios_bp		SIZE_T ?
ios_i		SIZE_T ?
ios_c		SIZE_T ?
ios_size	SIZE_T ?
ios_flag	DWORD ?
ios_file	DWORD ?
ios_crc		SIZE_T ?
ios_line	SIZE_T ?	; line offset
ios_offset	QWORD ?		; seek offset
ios_total	QWORD ?		; count read/write
ios_fsize	QWORD ?
S_IOST		ENDS

externdef	STDI:S_IOST
externdef	STDO:S_IOST
externdef	crctab:DWORD
externdef	oupdate:SIZE_T

ioinit		PROTO :PTR S_IOST, :SIZE_T
ioopen		PROTO :PTR S_IOST, :LPSTR, :DWORD, :SIZE_T
ioseek		PROTO :PTR S_IOST, :QWORD, :DWORD
iocopy		PROTO :PTR S_IOST, :PTR S_IOST, :QWORD
ioflush		PROTO :PTR S_IOST
ioread		PROTO :PTR S_IOST
ioclose		PROTO :PTR S_IOST
iofree		PROTO :PTR S_IOST
ioputc		PROTO ; edx, eax
ifdef _WIN64
iogetc		PROTO :PTR S_IOST
else
iogetc		PROTO
endif
iowrite		PROTO :PTR S_IOST, :PVOID, :SIZE_T
iotell		PROTO :PTR S_IOST

oputc		PROTO ; STDO, eax
ogetc		PROTO ; STDI

oupdcrc		PROTO
osearch		PROTO
notfoundmsg	PROTO

oreadb		PROTO :LPSTR, :DWORD
oungetc		PROTO

oread		PROTO
oprintf		PROTO _CDecl :LPSTR, :VARARG
ogetl		PROTO :LPSTR, :LPSTR, :DWORD
ogets		PROTO
oputs		PROTO :LPSTR
_close		PROTO :SINT
ogetouth	PROTO :LPSTR, :DWORD
openfile	PROTO :LPSTR, :DWORD, :DWORD
oseek		PROTO :SIZE_T, :DWORD

eropen		PROTO :LPSTR

.list
