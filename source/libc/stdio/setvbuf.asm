; SETVBUF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include malloc.inc
include limits.inc

    .code

    assume rbx:LPFILE

setvbuf proc uses rbx fp:LPFILE, buf:string_t, type:int_t, bsize:size_t

    ldr rbx,fp
    ldr edx,type
    ldr rcx,bsize

    .if ( edx != _IONBF && ( rcx < 2 || rcx > INT_MAX || ( edx != _IOFBF && edx != _IOLBF ) ) )
        .return( -1 )
    .endif

    fflush( rbx )
    _freebuf( rbx )

    mov edx,_IOYOURBUF or _IOSETVBUF
    mov rax,buf
    mov rcx,bsize

    .if ( type & _IONBF )

        mov edx,_IONBF
        lea rax,[rbx]._charbuf
        mov ecx,4

    .elseif ( rax == NULL )

        .if ( malloc( rcx ) == NULL )

            dec rax
           .return
        .endif
        mov edx,_IOMYBUF or _IOSETVBUF
        mov rcx,bsize
    .endif

    mov [rbx]._ptr,rax
    mov [rbx]._base,rax
    and [rbx]._flag,not (_IOMYBUF or _IOYOURBUF or _IONBF or _IOSETVBUF or _IOFEOF or _IOFLRTN or _IOCTRLZ)
    or  [rbx]._flag,edx
    mov [rbx]._bufsiz,ecx
    xor eax,eax
    mov [rbx]._cnt,eax
    ret

setvbuf endp

    end
