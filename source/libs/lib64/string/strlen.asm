; STRLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

    option win64:rsp noauto

strlen proc uses rdi string:string_t

    mov     rdi,rcx
    mov     ecx,-1
    xor     eax,eax
    repnz   scasb
    not     ecx
    dec     ecx
    mov     eax,ecx
    ret

strlen endp

    end
