include stdio.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

fgets PROC USES rsi rdi,
	buf:	LPSTR,
	count:	SIZE_T,
	fp:	LPFILE

	cmp	rdx,0
	jle	error
	mov	rdi,rcx
	dec	rdx
	jz	done
	mov	rsi,r8
lup:
	fgetc ( rsi )
	cmp	rax,-1
	je	@F
	mov	[rdi],al
	inc	rdi
	cmp	al,10
	jne	lup
	jmp	done
@@:
	cmp	rdi,buf
	je	error
done:
	mov	byte ptr [rdi],0
	mov	rax,buf
	test	rax,rax
toend:
	ret
error:
	xor	rax,rax
	jmp	toend
fgets	ENDP

	END
