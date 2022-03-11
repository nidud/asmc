; ISCNTRL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

iscntrl proc char:SINT

    lea rax,_ctype
    mov al,[rax+rcx*2+2]
    and eax,_CONTROL
    ret

iscntrl endp

    end

