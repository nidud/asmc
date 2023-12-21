; FGETWS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fgetws proc uses rbx buf:LPWSTR, count:SINT, fp:LPFILE

    ldr rbx,buf
    .if ( count <= 0 )
        .return( NULL )
    .endif

    .for ( count-- : count : count-- )

        .ifsd ( fgetwc(fp) < 0 )

            .if ( rbx == buf )

                .return(NULL)
            .endif
            .break
        .endif

        mov [rbx],ax
        add rbx,2
       .break .if ( eax == 10 )
    .endf
    mov wchar_t ptr [rbx],0
   .return( buf )

fgetws endp

    end
