include stdio.inc
include io.inc
include winbase.inc

    .code

    assume rsi:LPFILE

_flswbuf proc uses rsi rdi rbx char:SINT, fp:LPFILE

    mov	 rsi,rdx
    mov	 edi,[rsi]._flag
    test edi,_IOREAD or _IOWRT or _IORW
    jz	 error
    test edi,_IOSTRG
    jnz error
    mov ebx,[rsi]._file
    .if edi & _IOREAD

	xor eax,eax
	mov [rsi]._cnt,eax
	test edi,_IOEOF
	jz error

	mov rax,[rsi]._base
	mov [rsi]._ptr,rax
	and edi,not _IOREAD
    .endif

    or	edi,_IOWRT
    and edi,not _IOEOF
    mov [rsi]._flag,edi
    xor eax,eax
    mov [rsi]._cnt,eax

    .if !(edi & _IOMYBUF or _IONBF or _IOYOURBUF)

	_isatty(ebx)
	lea r8,stdout
	lea r9,stderr
	.if !((rsi == r8 || rsi == r9) && rax)
	    _getbuf(rsi)
	.endif
    .endif

    mov eax,[rsi]._flag
    xor edi,edi
    mov [rsi]._cnt,edi

    .if eax & _IOMYBUF or _IOYOURBUF

	mov rax,[rsi]._base
	mov rdi,[rsi]._ptr
	sub rdi,rax
	add rax,2
	mov [rsi]._ptr,rax
	mov eax,[rsi]._bufsiz
	sub eax,2
	mov [rsi]._cnt,eax
	xor eax,eax

	.ifs rdi > rax
	    _write(ebx, [rsi]._base, rdi)
	.else
	    lea r8,_osfile
	    mov dl,[r8+rbx]
	    .ifs ebx > eax && dl & FH_APPEND

		lea rcx,_osfhnd
		mov rcx,[rcx+rbx*8]
		SetFilePointer(rcx, eax, rax, SEEK_END)
		xor eax,eax
	    .endif
	.endif

	mov edx,char
	mov rbx,[rsi]._base
	mov [rbx],dx
    .else
	add edi,2
	_write(ebx, &char, rdi)
    .endif
    cmp eax,edi
    jne error
    movzx eax,word ptr char
toend:
    ret
error:
    or	edi,_IOERR
    mov [rsi]._flag,edi
    mov rax,-1
    jmp toend
_flswbuf endp

    END
