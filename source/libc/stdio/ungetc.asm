; UNGETC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume rbx:LPFILE

ungetc proc uses rdi rbx c:SINT, fp:LPFILE

    ldr edi,c
    ldr rbx,fp

    .if ( (edi == EOF) ||
         !( ([rbx]._flag & _IOREAD) ||
            (([rbx]._flag & _IORW) && !([rbx]._flag & _IOWRT)) ) )

        .return(-1)
    .endif

    .if ( [rbx]._base == NULL )

        _getbuf(rbx)
    .endif

    .if ( [rbx]._ptr == [rbx]._base )

        .if ( [rbx]._cnt )
            .return(-1)
        .endif
        inc [rbx]._ptr
    .endif

    mov eax,edi
    .if ( [rbx]._flag & _IOSTRG )

        dec [rbx]._ptr
        mov rcx,[rbx]._ptr
        .if ( al != [rcx] )

            inc [rbx]._ptr
           .return(-1)
        .endif
    .else
        dec [rbx]._ptr
        mov rcx,[rbx]._ptr
        mov [rcx],al
    .endif

    inc [rbx]._cnt
    and [rbx]._flag,not _IOEOF
    or  [rbx]._flag,_IOREAD
    movzx eax,al
    ret

ungetc endp

    end
