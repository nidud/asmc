; TOGETBITFLAG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

togetbitflag proc uses rbx tobj:PTOBJ, count:int_t, flag:uint_t

    ldr     ebx,flag
    ldr     eax,count
    ldr     rdx,tobj

    mov     ecx,eax
    dec     eax
    imul    eax,eax,TOBJ
    add     rdx,rax
    xor     eax,eax

    .while ecx
        .if bx & [rdx]
            or al,1
        .endif
        shl eax,1
        sub rdx,TOBJ
        dec ecx
    .endw
    shr eax,1
    ret

togetbitflag endp

    end
