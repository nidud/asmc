; SETVBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc
include limits.inc

    .code

    assume r12:ptr FILE

setvbuf proc uses rbx r12 r13 r14 fp:ptr FILE, buf:string_t, tp:size_t, bsize:size_t

    .if ( tp != _IONBF && ( bsize < 2 || bsize > INT_MAX || ( tp != _IOFBF && tp != _IOLBF ) ) )
        .return -1
    .endif

    mov r12,fp
    mov r13,buf
    mov r14,tp
    mov rbx,bsize

    fflush(r12)
    _freebuf(r12)

    mov edx,_IOYOURBUF or _IOSETVBUF
    mov rax,r13

    .if ( r14 & _IONBF )

        mov edx,_IONBF
        lea rax,[r12]._charbuf
        mov ebx,4

    .elseif ( rax == NULL )

        .if ( malloc(rbx) == NULL )

            dec rax
           .return
        .endif
        mov edx,_IOMYBUF or _IOSETVBUF
    .endif

    and [r12]._flag,not ( _IOMYBUF or _IOYOURBUF or _IONBF or _IOSETVBUF or _IOFEOF or _IOFLRTN or _IOCTRLZ )
    or  [r12]._flag,edx
    mov [r12]._bufsiz,ebx
    mov [r12]._ptr,rax
    mov [r12]._base,rax
    xor eax,eax
    mov [r12]._cnt,eax
    ret

setvbuf endp

    end
