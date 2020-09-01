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

fwrite proc uses rsi rdi rbx r12 r13 r14 buf:LPSTR, rsize:SINT, num:SINT, fp:LPFILE

    mov rsi,rcx ; buf
    mov rbx,r9	; fp
    mov eax,edx ; rsize
    mul r8d	; num
    mov edi,eax
    mov r12d,eax

    mov r13d,_MAXIOBUF
    .if [rbx]._flag & _IOMYBUF or _IONBF or _IOYOURBUF
	mov r13d,[rbx]._bufsiz
    .endif

    .while edi

	mov ecx,[rbx]._cnt
	.if ecx && [rbx]._flag & _IOMYBUF or _IOYOURBUF

	    .if edi < ecx
		mov ecx,edi
	    .endif
	    sub edi,ecx
	    sub [rbx]._cnt,ecx
	    mov edx,edi
	    mov rdi,[rbx]._ptr
	    rep movsb
	    mov [rbx]._ptr,rdi
	    mov edi,edx

	.elseif edi >= r13d

	    .if [rbx]._flag & _IOMYBUF or _IOYOURBUF
		fflush(rbx)
		test rax,rax
		jnz break
	    .endif

	    mov eax,edi
	    mov ecx,r13d

	    .if ecx
		xor edx,edx
		div ecx
		mov eax,edi
		sub eax,edx
	    .endif
	    mov r14d,eax

	    _write([rbx]._file, rsi, eax)
	    cmp rax,-1
	    je	error

	    sub rdi,rax
	    add rsi,rax
	    cmp eax,r14d
	    jb	error
	.else
	    movzx eax,byte ptr [rsi]
	    _flsbuf(eax, rbx)
	    cmp eax,-1
	    je	break
	    inc rsi
	    dec rdi
	    mov eax,[rbx]._bufsiz
	    .if !eax
		mov eax,1
	    .endif
	    mov r13,rax
	.endif
    .endw
    mov eax,num
toend:
    ret
error:
    or	[rbx]._flag,_IOERR
break:
    mov rax,r12
    sub rax,rdi
    xor rdx,rdx
    div rsize
    jmp toend
fwrite	endp

    END
