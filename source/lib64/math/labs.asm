
include math.inc

    .code

    option win64:rsp nosave noauto

labs proc x:SINT

    mov     eax,ecx
    neg     eax
    test    ecx,ecx
    cmovns  eax,ecx
    ret

labs endp

    end
