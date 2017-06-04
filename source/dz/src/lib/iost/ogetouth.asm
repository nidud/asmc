include iost.inc
include io.inc
include errno.inc
include confirm.inc
include dzlib.inc

	.code

ogetouth PROC filename:LPSTR, mode
	osopen( filename, _A_NORMAL, mode, A_CREATE )
	cmp	eax,-1
	jne	toend
	cmp	errno,EEXIST
	jne	error
	test	confirmflag,CFDELETEALL
	jnz	confirm
trunc:
	setfattr( filename, 0 )
	openfile( filename, mode, A_TRUNC )
	jmp	toend
confirm:
	confirm_delete( filename, 0 )
	cmp	eax,1
	je	trunc		; delete --> trunc
	cmp	eax,2
	je	delete		; delete all --> clear flag, trunc
	cmp	eax,3
	je	skip		; jump --> return 0
	mov	eax,-1		; Cancel --> return -1
	jmp	toend
delete:
	and	confirmflag,not CFDELETEALL
	jmp	trunc
skip:
	xor	eax,eax
toend:
	ret
error:
	eropen( filename ) ; -1
	jmp	toend
ogetouth ENDP

	END
