; _CROPZEROS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include fltintrn.inc

    .code

_cropzeros proc buffer:LPSTR

    mov edx,strlen(buffer)
    add edx,buffer
    mov eax,'0'
    .while [edx-1] == al

        mov [edx-1],ah
        dec edx
    .endw
    .if byte ptr [edx-1] == '.'

        mov [edx-1],ah
    .endif
    ret

_cropzeros endp

    END
