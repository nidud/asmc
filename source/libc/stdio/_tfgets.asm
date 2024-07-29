; _TFGETS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

    .code

    assume rbx:ptr _iobuf

_fgetts proc uses rbx buf:LPTSTR, count:SINT, fp:LPFILE

    ldr rbx,buf
    xor eax,eax
    .if ( count <= eax )

        .return
    .endif

    .for ( count-- : count : count-- )

        .ifsd ( _fgettc(fp) < 0 )

            .if ( rbx == buf )

                .return(NULL)
            .endif
            .break
        .endif

        mov [rbx],_tal
        add rbx,TCHAR
       .break .if ( eax == 10 )
    .endf
    xor eax,eax
    mov [rbx],_tal
    mov rax,buf
    ret

_fgetts endp

    end
