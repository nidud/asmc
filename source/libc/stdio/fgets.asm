include stdio.inc

	.code

fgets PROC USES edi,
	buf:	LPSTR,
	count:	SIZE_T,
	fp:	LPFILE

	mov	eax,count
	cmp	eax,0
	jle	error
	mov	edi,buf
	dec	eax
	jz	done
lup:
	fgetc ( fp )
	cmp	eax,-1
	je	@F
	mov	[edi],al
	inc	edi
	cmp	al,10
	jne	lup
	jmp	done
@@:
	cmp	edi,buf
	je	error
done:
	mov	byte ptr [edi],0
	mov	eax,buf
	test	eax,eax
toend:
	ret
error:
	xor	eax,eax
	jmp	toend
fgets	ENDP

	END
