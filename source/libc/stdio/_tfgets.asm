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
    .if ( count <= 0 )
        .return( NULL )
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
    mov TCHAR ptr [rbx],0
   .return( buf )

_fgetts endp

    end
