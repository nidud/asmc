include stdio.inc

	.code

	OPTION	STACKBASE:rsp
	ASSUME	rbx:ptr _iobuf

fgets PROC USES rsi rdi rbx buf:LPSTR, count:SINT, fp:LPFILE

	mov	rdi,rcx
	mov	rsi,rdx
	mov	rbx,r8

	cmp	rsi,0
	jle	error
	dec	rsi
	jz	done
lupe:
	dec	[rbx]._cnt
	jl	fbuf
	mov	rcx,[rbx]._ptr
	inc	[rbx]._ptr
	mov	al,[rcx]
next:
	mov	[rdi],al
	inc	rdi
	cmp	al,10
	je	done
	dec	rsi
	jnz	lupe
done:
	mov	byte ptr [rdi],0
	mov	rax,buf
	test	rax,rax
toend:
	ret
fbuf:
	_filbuf(rbx)
	cmp	eax,-1
	jne	next
	cmp	rdi,buf
	jne	done
error:
	xor	eax,eax
	jmp	toend
fgets	ENDP

	END
