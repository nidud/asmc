include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

strcmp	PROC s1:LPSTR, s2:LPSTR

	push	edx
	mov	edx,4[esp+4]
	mov	ecx,4[esp+8]
	xor	eax,eax
	ALIGN	4
@@:
	xor	al,[edx]
	jz	zero_0
	sub	al,[ecx]
	jnz	done
	xor	al,[edx+1]
	jz	zero_1
	sub	al,[ecx+1]
	jnz	done
	xor	al,[edx+2]
	jz	zero_2
	sub	al,[ecx+2]
	jnz	done
	xor	al,[edx+3]
	jz	zero_3
	sub	al,[ecx+3]
	jnz	done
	lea	edx,[edx+4]
	lea	ecx,[ecx+4]
	jmp	@B
	ALIGN	4
done:
	sbb	eax,eax
	sbb	eax,-1
	pop	edx
	ret
zero_3:
	add	ecx,1
zero_2:
	add	ecx,1
zero_1:
	add	ecx,1
zero_0:
	sub	al,[ecx]
	jnz	done
	pop	edx
	ret
strcmp	endp

	END
