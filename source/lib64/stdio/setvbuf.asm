; SETVBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc
include limits.inc

    .code

    assume rcx:LPFILE

setvbuf proc fp:LPFILE, buf:LPSTR, tp:SIZE_T, bsize:SIZE_T

    mov eax,-1
    .return .if r8d != _IONBF && (r9d < 2 || r9d > INT_MAX || (r8d != _IOFBF && r8d != _IOLBF))

    fflush(rcx)
    _freebuf(fp)

    mov edx,_IOYOURBUF or _IOSETVBUF
    mov rax,buf
    mov r8,tp
    mov r9,bsize
    mov rcx,fp

    .if r8d & _IONBF

        mov edx,_IONBF
        lea rax,[rcx]._charbuf
        mov r9d,4

    .elseif !rax

        .if !malloc(r9)

            dec eax
            .return
        .endif
        mov r9,bsize
        mov edx,_IOMYBUF or _IOSETVBUF
        mov rcx,fp
    .endif
    and [rcx]._flag,not (_IOMYBUF or _IOYOURBUF or _IONBF or _IOSETVBUF or _IOFEOF or _IOFLRTN or _IOCTRLZ)
    or  [rcx]._flag,edx
    mov [rcx]._bufsiz,r9d
    mov [rcx]._ptr,rax
    mov [rcx]._base,rax
    xor eax,eax
    mov [rcx]._cnt,eax
    ret

setvbuf endp

    end
