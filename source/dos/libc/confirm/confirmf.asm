; CONFIRMF.ASM--
; Copyright (C) 2015 Doszip Developers
include dos.inc
include confirm.inc

ID_DELETE	equ 1	; return 1
ID_DELETEALL	equ 2	; return 1 + update confirmflag
ID_SKIPFILE	equ 3	; return 0
ID_CANCEL	equ 0	; return -1

	.code

confirm_delete_file PROC _CType PUBLIC USES si fname:PTR BYTE, flag:size_t
	mov ax,flag
	mov dx,confirmflag
	.if al & _A_RDONLY && dl & CFREADONY
	    mov ax,-1
	    mov si,not (CFREADONY or CFDELETEALL)
	.elseif al & _A_SYSTEM && dl & CFSYSTEM
	    mov ax,-2
	    mov si,not (CFSYSTEM or CFDELETEALL)
	.elseif dl & CFDELETEALL
	    xor ax,ax
	    mov si,not CFDELETEALL
	.else
	    mov ax,1
	    jmp @F
	.endif
	.if confirm_delete(fname,ax) == ID_DELETEALL
	    and confirmflag,si
	    mov ax,1
	.elseif ax == ID_SKIPFILE
	    xor ax,ax
	.elseif ax != ID_DELETE
	    mov ax,-1
	.endif
      @@:
	ret
confirm_delete_file ENDP

	END
