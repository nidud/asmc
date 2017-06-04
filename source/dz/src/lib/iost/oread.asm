include iost.inc

	.code

oread	PROC
	mov	ecx,STDI.ios_c
	sub	ecx,STDI.ios_i
	cmp	ecx,eax
	jb	read
done:
	mov	eax,STDI.ios_bp
	add	eax,STDI.ios_i
toend:
	ret
read:
	push	eax
	ioread( addr STDI )
	pop	eax
	jz	error
	mov	ecx,STDI.ios_c
	sub	ecx,STDI.ios_i
	cmp	ecx,eax
	jae	done
error:
	xor	eax,eax
	jmp	toend
oread	ENDP

	END
