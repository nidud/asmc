include errno.inc
include winbase.inc

	.code

_getdrive PROC
	local	b[512]:BYTE
	GetCurrentDirectory( 512, addr b )
	test	eax,eax
	jz	error
ifdef _UNICODE
	mov	al,b
	mov	ah,b[2]
else
	mov	ax,WORD PTR b
endif
	cmp	ah,':'
	jne	nodrv
	movzx	eax,al
	or	al,20h
	sub	al,'a' - 1	; A: == 1
toend:
	ret
error:
	call	osmaperr
nodrv:
	xor	eax,eax
	jmp	toend
_getdrive ENDP

	END
