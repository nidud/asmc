; ISDIGIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

    option win64:rsp

isdigit proc char:SINT
    lea rax,_ctype
    mov al,[rax+rcx*2+2]
    and eax,_DIGIT
    ret
isdigit endp

    end

