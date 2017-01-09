include stdio.inc

	.code

	ASSUME	ebx:ptr S_FILE

fgets PROC USES ebx buf:LPSTR, count:SIZE_T, fp:LPFILE
	mov	edx,buf
	mov	ecx,count
	mov	ebx,fp
	cmp	ecx,0
	jle	error
	dec	ecx
	jz	done
lupe:
	dec	[ebx].iob_cnt
	jl	fbuf
	mov	eax,[ebx].iob_ptr
	inc	[ebx].iob_ptr
	mov	al,[eax]
next:
	mov	[edx],al
	inc	edx
	cmp	al,10
	je	done
	dec	ecx
	jnz	lupe
done:
	mov	byte ptr [edx],0
	mov	eax,buf
	test	eax,eax
toend:
	ret
fbuf:
	push	edx
	push	ecx
	_filbuf(ebx)
	pop	ecx
	pop	edx
	cmp	eax,-1
	jne	next
	cmp	edx,buf
	jne	done
error:
	xor	eax,eax
	jmp	toend
fgets	ENDP

	END
