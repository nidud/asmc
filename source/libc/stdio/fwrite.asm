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
   .new count:size_t

    ldr rbx,fp
    ldr eax,rsize
    mul num
    mov count,rax
    mov total,eax

    mov bufsize,_MAXIOBUF
    .if ( [rbx]._flag & _IOMYBUF or _IONBF or _IOYOURBUF )
	mov bufsize,[rbx]._bufsiz
    .endif

    .while count

	mov rax,count
	mov ecx,[rbx]._cnt

	.if ( ecx && [rbx]._flag & _IOMYBUF or _IOYOURBUF )

	    .if ( count < rcx )
		mov rcx,count
	    .endif
	    sub count,rcx
	    sub [rbx]._cnt,ecx
	    mov rdi,[rbx]._ptr
	    mov rsi,buf
	    rep movsb
	    mov [rbx]._ptr,rdi
	    mov buf,rsi

	.elseif ( eax >= bufsize )

	    .if ( [rbx]._flag & _IOMYBUF or _IOYOURBUF )

		fflush( rbx )
		test eax,eax
		jnz break
	    .endif

	    mov rax,count
	    mov ecx,bufsize

	    .if ecx

		xor edx,edx
		div ecx
		mov rax,count
		sub eax,edx
	    .endif
	    mov nbytes,eax
ifdef STDZIP
	    .if ( [rbx]._flag & _IOCRC32 )

		_crc32( [rbx]._crc32, [rbx]._base, eax )
		mov [rbx]._crc32,eax
		mov eax,nbytes
	    .endif
endif
	    _write( [rbx]._file, buf, eax )
	    cmp eax,-1
	    je	error

	    sub count,rax
	    add buf,rax
	    cmp eax,nbytes
	    jb	error

	.else

	    mov rcx,buf
	    movzx eax,byte ptr [rcx]
	    _flsbuf( eax, rbx )
	    cmp eax,-1
	    je	break

	    inc buf
	    dec count
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
    sub rax,count
    xor edx,edx
    div dword ptr rsize
    jmp toend

fwrite	endp

    end
