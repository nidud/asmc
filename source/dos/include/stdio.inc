ifndef __LIBC_INC
 include libc.inc
endif

.xlist

SEEK_CUR	equ 1
SEEK_END	equ 2
SEEK_SET	equ 0

INT_MAX		equ 7FFFh

_NSTREAM_	equ 10
_MAXIOBUF	equ 4000h
_INTIOBUF	equ 1000h
_MINIOBUF	equ 0200h

_IOFBF		equ 0000h
_IOREAD		equ 0001h
_IOWRT		equ 0002h
_IONBF		equ 0004h
_IOMYBUF	equ 0008h
_IOEOF		equ 0010h
_IOERR		equ 0020h
_IOSTRG		equ 0040h
_IOLBF		equ 0040h
_IORW		equ 0080h
_IOYOURBUF	equ 0100h
_IOSETVBUF	equ 0400h
_IOFEOF		equ 0800h
_IOFLRTN	equ 1000h
_IOCTRLZ	equ 2000h
_IOCOMMIT	equ 4000h

S_FILE		STRUC
iob_bp		dd ?
iob_cnt		dw ?
iob_base	dd ?
iob_flag	dw ?
iob_file	dw ?
iob_bufsize	dw ?
iob_charbuf	dw ?
S_FILE		ENDS

externdef	_bufin: BYTE
externdef	_iob:	S_FILE
externdef	stdout: S_FILE
externdef	stderr: S_FILE

_print		PROTO _CDecl :DWORD, :VARARG
sprintf		PROTO _CDecl :DWORD, :DWORD, :VARARG
_output		PROTO _CType :DWORD, :DWORD, :DWORD
ftobufin	PROTO _CDecl :DWORD, :VARARG

printf		PROTO _CDecl :DWORD, :VARARG
fprintf		PROTO _CDecl :DWORD, :DWORD, :VARARG
puts		PROTO _CType :DWORD
fopen		PROTO _CType :DWORD, :DWORD
fclose		PROTO _CType :DWORD
fgetc		PROTO _CType :DWORD
vsprintf	PROTO _CType :DWORD, :DWORD, :DWORD
fread		PROTO _CType :DWORD, :WORD, :WORD, :DWORD
fwrite		PROTO _CType :DWORD, :WORD, :WORD, :DWORD
fseek		PROTO _CType :DWORD, :DWORD, :WORD
fgets		PROTO _CType :DWORD, :WORD, :DWORD
fputs		PROTO _CType :DWORD, :DWORD
ftell		PROTO _CType :DWORD
perror		PROTO _CType :DWORD
fflush		PROTO _CType :DWORD
_flush		PROTO _CType :DWORD
_flsbuf		PROTO _CType :WORD, :DWORD
_freebuf	PROTO _CType :DWORD
_filebuf	PROTO _CType :DWORD
_openfile	PROTO _CType :DWORD
_getst		PROTO _CType
_ftbuf		PROTO _CType :WORD, :DWORD
_stbuf		PROTO _CType :DWORD
_getbuf		PROTO _CType :DWORD
setvbuf		PROTO _CType :DWORD, :DWORD, :WORD, :WORD
setbuf		PROTO _CType :DWORD, :DWORD

.list
