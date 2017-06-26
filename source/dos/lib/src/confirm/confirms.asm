; CONFIRMS.ASM--
; Copyright (C) 2015 Doszip Developers
include libc.inc
include confirm.inc

ID_DELETE	equ 1	; return 1
ID_DELETEALL	equ 2	; return 1 + update confirmflag
ID_SKIPFILE	equ 3	; return 0
ID_CANCEL	equ 0	; return -1

	.code

confirm_delete_sub PROC _CType PUBLIC path:PTR BYTE
	mov ax,1
	.if confirmflag & CFDIRECTORY
	    .if confirm_delete(path,1) == ID_DELETEALL
		and confirmflag,not (CFDIRECTORY or CFDELETEALL)
		mov ax,1
	    .elseif ax == ID_SKIPFILE
		mov ax,-1
	    .elseif ax != ID_DELETE
		xor ax,ax
	    .endif
	.endif
	ret
confirm_delete_sub ENDP

	END
