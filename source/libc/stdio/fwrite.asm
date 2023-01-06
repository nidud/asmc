; FWRITE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include errno.inc
include string.inc

    .code

    assume rbx:LPFILE

fwrite proc uses rsi rdi rbx buf:LPSTR, rsize:int_t, num:int_t, fp:LPFILE

   .new total:int_t
   .new bufsize:int_t
   .new nbytes:int_t

    mov rsi,buf
    mov rbx,fp
    mov eax,rsize
    mul num
    mov edi,eax
    mov total,eax

    mov bufsize,_MAXIOBUF
    .if ( [rbx]._flag & _IOMYBUF or _IONBF or _IOYOURBUF )
	mov bufsize,[rbx]._bufsiz
    .endif

    .while edi

	mov ecx,[rbx]._cnt
	.if ( ecx && [rbx]._flag & _IOMYBUF or _IOYOURBUF )

	    .if ( edi < ecx )
		mov ecx,edi
	    .endif
	    sub edi,ecx
	    sub [rbx]._cnt,ecx
	    mov edx,edi
	    mov rdi,[rbx]._ptr
	    rep movsb
	    mov [rbx]._ptr,rdi
	    mov edi,edx

	.elseif ( edi >= bufsize )

	    .if ( [rbx]._flag & _IOMYBUF or _IOYOURBUF )

		fflush( rbx )
		test eax,eax
		jnz break
	    .endif

	    mov eax,edi
	    mov ecx,bufsize

	    .if ecx

		xor edx,edx
		div ecx
		mov eax,edi
		sub eax,edx
	    .endif
	    mov nbytes,eax

	    _write( [rbx]._file, rsi, eax )
	    cmp eax,-1
	    je	error

	    sub edi,eax
	    add rsi,rax
	    cmp eax,nbytes
	    jb	error

	.else

	    movzx eax,byte ptr [rsi]
	    _flsbuf( eax, rbx )
	    cmp eax,-1
	    je	break

	    inc rsi
	    dec rdi
	    mov eax,[rbx]._bufsiz
	    .if ( !eax )
		mov eax,1
	    .endif
	    mov bufsize,eax
	.endif
    .endw
    .return( num )

toend:
    ret

error:
    or	[rbx]._flag,_IOERR

break:
    mov eax,total
    sub eax,edi
    xor edx,edx
    div dword ptr rsize
    jmp toend

fwrite	endp

    end
