; _CROPZEROS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include fltintrn.inc

    .code

_cropzeros proc buffer:LPSTR

    add strlen( buffer ),buffer

    .while ( byte ptr [rax-1] == '0' )

        dec rax
        mov byte ptr [rax],0
    .endw

    .if ( byte ptr [rax-1] == '.' )

        mov byte ptr [rax-1],0
    .endif
    ret

_cropzeros endp

    end
