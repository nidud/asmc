; STRXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include strlib.inc

    .code

strxchg proc uses esi edi ebx dst:LPSTR, old:LPSTR, new:LPSTR

    mov edi,dst
    mov esi,strlen(new)
    mov ebx,strlen(old)

    .while strstri(edi, old)    ; find token

        mov edi,eax             ; EDI to start of token
        lea ecx,[eax+esi]
        add eax,ebx
        strmove(ecx, eax)       ; move($ + len(new), $ + len(old))
        memmove(edi, new, esi)  ; copy($, new, len(new))
        inc edi                 ; $++
    .endw
    mov eax,dst
    ret

strxchg endp

    END
