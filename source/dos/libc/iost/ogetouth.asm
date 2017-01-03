; OGETOUTH.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc
include io.inc
include dos.inc
include errno.inc
include confirm.inc

	.code

ogetouth PROC _CType PUBLIC filename:DWORD
	invoke	osopen,filename,_A_NORMAL,M_WRONLY,A_CREATE
	cmp	ax,-1
	jne	ogetouth_end
	cmp	errno,EEXIST
	jne	ogetouth_err
	test	confirmflag,CFDELETEALL
	jnz	ogetouth_confirm
    ogetouth_trunc:
	invoke	_dos_setfileattr,filename,0
	invoke	openfile,filename,M_WRONLY,A_TRUNC
	jmp	ogetouth_end
    ogetouth_confirm:
	invoke	confirm_delete,filename,0
	cmp	ax,1
	je	ogetouth_trunc	; delete --> trunc
	cmp	ax,2
	je	ogetouth_del	; delete all --> clear flag, trunc
	cmp	ax,3
	je	ogetouth_nul	; jump --> return 0
	mov	ax,-1		; Cancel --> return -1
	jmp	ogetouth_end
    ogetouth_del:
	and	confirmflag,not CFDELETEALL
	jmp	ogetouth_trunc
    ogetouth_nul:
	xor	ax,ax
    ogetouth_end:
	ret
    ogetouth_err:
	invoke	eropen,filename ; -1
	jmp	ogetouth_end
ogetouth ENDP

	END
