; _CROPZEROS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include fltintrn.inc

    .code

_cropzeros proc uses rbx buffer:LPSTR

    ldr rbx,buffer

    .for ( rax = rbx, cl = [rbx] : cl && cl != '.' : )

        inc rbx
        mov cl,[rbx]
    .endf

    .if ( cl )

        .for ( rbx++, cl = [rbx] : cl && cl != 'e' && cl != 'E' : )
            inc rbx
            mov cl,[rbx]
        .endf
        mov rdx,rbx
        dec rbx
        .while ( byte ptr [rbx] == '0' )
            dec rbx
        .endw
        .if ( byte ptr [rbx] == '.' )
            dec rbx
        .endif
        .for ( rbx++, cl = [rdx] : cl : )
            mov [rbx],cl
            inc rdx
            inc rbx
            mov cl,[rdx]
        .endf
        mov [rbx],cl
    .endif
    ret

_cropzeros endp

    end
