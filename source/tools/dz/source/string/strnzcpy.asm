; STRNZCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strlib.inc

    .code

strnzcpy PROC USES esi edi dst:LPSTR, src:LPSTR, count:SIZE_T

    mov     edi,dst
    mov     esi,src
    mov     ecx,count

    .assert ecx
L1:
    mov     al,[esi]
    mov     [edi],al
    test    al,al
    jz      L2
    inc     edi
    inc     esi
    dec     ecx
    jnz     L1
    mov     [edi],cl
L2:
    mov     eax,dst
    ret

strnzcpy ENDP

    END
