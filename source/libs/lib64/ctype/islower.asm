; ISLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

    option win64:rsp

islower proc char:SINT
    lea rax,_ctype
    mov al,[rax+rcx*2+2]
    and eax,_LOWER
    ret
islower endp

    end

