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

setvbuf proc uses rsi rdi rbx fp:LPFILE, buf:LPSTR, tp:size_t, bsize:size_t

    ldr rbx,fp
    ldr rsi,tp
    ldr rdi,bsize

    .if ( esi != _IONBF && ( edi < 2 || edi > INT_MAX || ( esi != _IOFBF && esi != _IOLBF ) ) )
        .return( -1 )
    .endif

    fflush( rbx )
    _freebuf( rbx )

    mov edx,_IOYOURBUF or _IOSETVBUF
    mov rax,buf

    .if ( esi & _IONBF )

        mov edx,_IONBF
        lea rax,[rbx]._charbuf
        mov edi,4

    .elseif ( rax == NULL )

        .if ( malloc( rdi ) == NULL )

            dec rax
            .return
        .endif
        mov edx,_IOMYBUF or _IOSETVBUF
    .endif

    and [rbx]._flag,not (_IOMYBUF or _IOYOURBUF or _IONBF or _IOSETVBUF or _IOFEOF or _IOFLRTN or _IOCTRLZ)
    or  [rbx]._flag,edx
    mov [rbx]._bufsiz,edi
    mov [rbx]._ptr,rax
    mov [rbx]._base,rax
    xor eax,eax
    mov [rbx]._cnt,eax
    ret

setvbuf endp

    end
