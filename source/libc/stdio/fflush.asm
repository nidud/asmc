; FFLUSH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc

    .code

    assume rbx:LPFILE

fflush proc uses rbx rdi rsi fp:LPFILE

    ldr rbx,fp
    xor esi,esi
    mov eax,[rbx]._flag
    and eax,_IOREAD or _IOWRT

    .if ( eax == _IOWRT && [rbx]._flag & _IOMYBUF or _IOYOURBUF )

        mov rdi,[rbx]._ptr
        sub rdi,[rbx]._base
        .ifg
            .ifd ( _write( [rbx]._file, [rbx]._base, edi ) == edi )
                .if ( [rbx]._flag & _IORW )
                    and [rbx]._flag,not _IOWRT
                .endif
            .else
                or [rbx]._flag,_IOERR
                mov rsi,-1
            .endif
        .endif
    .endif

    mov rax,[rbx]._base
    mov [rbx]._ptr,rax
    mov [rbx]._cnt,0
   .return( rsi )

fflush endp

    end
