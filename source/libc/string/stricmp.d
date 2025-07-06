; STRICMP.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include string.inc

    .code

stricmp proc uses si di s1:string_t, s2:string_t

    pushl   ds
    ldr     di,s1
    ldr     si,s2
    mov     al,-1
.0:
    test    al,al
    jz      .1
    mov     al,esl[di]
    mov     ah,[si]
    inc     si
    inc     di
    cmp     al,ah
    je      .0

    sub     ax,'AA'
    cmp     al,'Z'-'A'+1
    sbb     dl,dl
    and     dl,'a'-'A'
    cmp     ah,'Z'-'A'+1
    sbb     dh,dh
    and     dh,'a'-'A'
    add     ax,dx
    add     ax,'AA'
    cmp     al,ah
    je      .0

    sbb     al,al
    sbb     al,-1
.1:
    cbw
    popl    ds
    ret

stricmp endp

    end
