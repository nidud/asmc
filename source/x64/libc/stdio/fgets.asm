include stdio.inc

	.code

	OPTION	STACKBASE:rsp
	ASSUME	rbx:ptr S_FILE

fgets PROC USES rsi rdi rbx buf:LPSTR, count:SIZE_T, fp:LPFILE

	mov	rdi,rcx
	mov	rsi,rdx
	mov	rbx,r8

	cmp	rsi,0
	jle	error
	dec	rsi
	jz	done
lupe:
	dec	[rbx].iob_cnt
	jl	fbuf
	mov	rcx,[rbx].iob_ptr
	inc	[rbx].iob_ptr
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
