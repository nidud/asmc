ifndef __LIBC_INC
 include libc.inc
endif

.xlist

_NFILE_		equ 20
_A_NORMAL	equ 00h
_A_RDONLY	equ 01h
_A_HIDDEN	equ 02h
_A_SYSTEM	equ 04h
_A_SUBDIR	equ 10h
_A_ARCH		equ 20h

_A_TEMPORARY	equ 0100h
_A_DELETE	equ 0400h
_A_SEQSCAN	equ 0800h
_A_RANDOM	equ 1000h

FH_OPEN		equ 01h
FH_EOF		equ 02h
FH_CRLF		equ 04h
FH_PIPE		equ 08h
FH_APPEND	equ 20h
FH_DEVICE	equ 40h
FH_TEXT		equ 80h

SEEK_SET	equ 0
SEEK_CUR	equ 1
SEEK_END	equ 2

DEV_UNKNOWN	equ 0000h
DEV_DISK	equ 0001h
DEV_CHAR	equ 0002h
DEV_PIPE	equ 0003h
DEV_REMOTE	equ 8000h

externdef _osfile:BYTE
externdef _nfile:WORD

A_OPEN		equ 0001h
A_TRUNC		equ 0002h
A_CREATE	equ 0010h
A_CREATETRUNC	equ A_CREATE or A_TRUNC
A_OPENCREATE	equ A_OPEN or A_CREATE
M_RDONLY	equ 0000h
M_WRONLY	equ 0001h
M_RDWR		equ 0002h

close		PROTO _CType :WORD
lseek		PROTO _CType :WORD, :DWORD, :WORD
write		PROTO _CType :WORD, :DWORD, :WORD
access		PROTO _CType :DWORD, :WORD
readword	PROTO _CType :DWORD
osopen		PROTO _CType :DWORD, :WORD, :WORD, :WORD
osread		PROTO _CType :WORD, :DWORD, :WORD
oswrite		PROTO _CType :WORD, :DWORD, :WORD
removefile	PROTO _CType :DWORD
isatty		PROTO _CType :WORD
osmaperr	PROTO
remove		PROTO _CType :DWORD
rename		PROTO _CType :DWORD, :DWORD
_dos_setfileattr PROTO _CType :DWORD, :WORD
dosmaperr	PROTO _CType :WORD

open		PROTO _CDecl :DWORD, :WORD, :VARARG
sopen		PROTO _CDecl :DWORD, :WORD, :WORD, :VARARG
read		PROTO _CType :WORD, :DWORD, :WORD
creat		PROTO _CType :DWORD, :WORD
osfiletype	PROTO _CType :WORD
chsize		PROTO _CType :WORD, :DWORD
filelength	PROTO _CType :WORD
tell		PROTO _CType :WORD

.list
