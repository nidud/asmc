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
    mov rcx,strlen(rbx)
    mov rax,rbx
    add rbx,rcx

    .while ( byte ptr [rbx-1] == '0' )

        dec rbx
        mov byte ptr [rbx],0
    .endw

    .if ( byte ptr [rbx-1] == '.' )

        mov byte ptr [rbx-1],0
    .endif
    ret

_cropzeros endp

    end
