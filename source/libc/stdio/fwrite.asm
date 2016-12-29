include stdio.inc
include io.inc
include errno.inc
include string.inc

	.code

	ASSUME	ebx: LPFILE

fwrite PROC USES esi edi ebx,
	buf:	LPSTR,
	rsize:	SINT,
	num:	SINT,
	fp:	LPFILE
local	total:	SINT,
	bufsize:SINT,
	nbytes: SINT

	mov	esi,buf
	mov	ebx,fp
	mov	eax,rsize
	mul	num
	mov	edi,eax
	mov	total,eax
	mov	edx,_MAXIOBUF
	.if	[ebx].iob_flag & _IOMYBUF or _IONBF or _IOYOURBUF
		mov edx,[ebx].S_FILE.iob_bufsize
	.endif
	mov	bufsize,edx
	.while	edi
		mov	edx,[ebx].iob_cnt
		.if	[ebx].iob_flag & _IOMYBUF or _IOYOURBUF && edx
			.if	edi < edx
				mov edx,edi
			.endif
			memcpy( [ebx].iob_ptr, esi, edx )
			sub	edi,edx
			sub	[ebx].iob_cnt,edx
			add	[ebx].iob_ptr,edx
			add	esi,edx
		.elseif edi >= bufsize
			.if	[ebx].iob_flag & _IOMYBUF or _IOYOURBUF
				fflush( ebx )
				test	eax,eax
				jnz	break
			.endif
			mov	eax,edi
			mov	ecx,bufsize
			.if	ecx
				xor	edx,edx
				div	ecx
				mov	eax,edi
				sub	eax,edx
			.endif
			mov	nbytes,eax
			_write( [ebx].iob_file, esi, eax )
			cmp	eax,-1
			je	error
			sub	edi,eax
			add	esi,eax
			cmp	eax,nbytes
			jb	error
		.else
			movzx	eax,BYTE PTR [esi]
			_flsbuf( eax, ebx )
			cmp	eax,-1
			je	break
			inc	esi
			dec	edi
			mov	eax,[ebx].iob_bufsize
			.if	!eax
				mov eax,1
			.endif
			mov	bufsize,eax
		.endif
	.endw
	mov	eax,num
toend:
	ret
error:
	or	[ebx].iob_flag,_IOERR
break:
	mov	eax,total
	sub	eax,edi
	xor	edx,edx
	div	rsize
	jmp	toend
fwrite	ENDP

	END
