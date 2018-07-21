
include math.inc

    .code

    option win64:rsp nosave noauto

abs proc x:SINT

    mov     eax,ecx
    neg     eax
    test    ecx,ecx
    cmovns  eax,ecx
    ret

abs endp

    end
