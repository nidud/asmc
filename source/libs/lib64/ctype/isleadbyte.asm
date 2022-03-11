; ISLEADBYTE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isleadbyte proc wc:SINT

    lea rax,_ctype
    mov ax,[rax+rcx*2+2]
    and eax,_LEADBYTE
    ret

isleadbyte endp

    end

