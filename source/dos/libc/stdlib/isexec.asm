; ISEXEC.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc
include string.inc

	.code	; Test if <ext> == bat | com | exe

isexec	PROC _CType PUBLIC	; (char *filename);
ifdef __3__
	.if strrchr(dx::ax,'.')
	    mov bx,ax
	    mov eax,es:[bx+1]
	    or	eax,'   '
	    .if eax == 'tab'
		mov ax,1
	    .elseif eax == 'moc'
		mov ax,2
	    .elseif eax == 'exe'
		mov ax,3
	    .else
		sub ax,ax
	    .endif
	.endif
	ret
else
	invoke	strrchr,dx::ax,'.'
	jz	isexec_NOT
	mov	es,dx
	inc	ax
	mov	bx,ax
	mov	dx,'  '
	mov	ax,es:[bx]
	mov	bx,es:[bx+2]
	or	ax,dx
	or	bx,dx
	cmp	ax,'ab'
	je	isexec_BAT
	cmp	ax,'oc'
	je	isexec_COM
	cmp	ax,'xe'
	je	isexec_EXE
    isexec_NOT:
	xor	ax,ax
    isexec_END:
	ret
    isexec_EXE:
	cmp	bx,' e'
	jne	isexec_NOT
	mov	ax,3	; 3 = EXE
	jmp	isexec_END
    isexec_COM:
	cmp	bx,' m'
	jne	isexec_NOT
	mov	ax,2	; 2 = COM
	jmp	isexec_END
    isexec_BAT:
	cmp	bx,' t'
	jne	isexec_NOT
	mov	ax,1	; 1 = BAT
	jmp	isexec_END
endif
isexec	ENDP

	END
