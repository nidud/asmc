; ISALNUM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

    option win64:rsp

isalnum proc char:SINT
    lea rax,_ctype
    mov al,[rax+rcx*2+2]
    and eax,_UPPER or _LOWER or _DIGIT
    ret
isalnum endp

    end

