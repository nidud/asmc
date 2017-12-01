include stdio.inc
include io.inc
include errno.inc
include winbase.inc

    .code

    option win64:rsp nosave
    assume rbx:LPFILE

fseek proc uses rsi rdi rbx fp:LPFILE, off:SIZE_T, whence:SIZE_T

    mov rbx,rcx ; fp
    mov rsi,rdx ; offset
    mov rdi,r8	; whence

    .if r8b != SEEK_SET && r8b != SEEK_CUR && r8b != SEEK_END
	jmp error
    .endif
    mov eax,[rbx]._flag
    .if !(eax & _IOREAD or _IOWRT or _IORW)
	jmp error
    .endif
    and eax,not _IOEOF
    mov [rbx]._flag,eax

    .if r8b == SEEK_CUR
	ftell (rbx)
	add rsi,rax
	mov rdi,SEEK_SET
    .endif
    fflush(rbx)

    mov eax,[rbx]._flag
    .if eax & _IORW
	and eax,not (_IOWRT or _IOREAD)
	mov [rbx]._flag,eax
    .elseif eax & _IOREAD && eax & _IOMYBUF && !(eax & _IOSETVBUF)
	mov [rbx]._bufsiz,_MINIOBUF
    .endif

    mov eax,[rbx]._file
    lea r8,_osfhnd
    mov rax,[r8+rax*8]
    .if SetFilePointer(rax, esi, 0, edi) == -1
	call	osmaperr
	jmp toend
    .endif
    xor rax,rax
toend:
    ret
error:
    mov errno,EINVAL
    mov rax,-1
    jmp toend
fseek endp

    END
