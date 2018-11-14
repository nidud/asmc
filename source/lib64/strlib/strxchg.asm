; STRXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include strlib.inc

    .code

strxchg proc uses rsi rdi rbx dst:LPSTR, old:LPSTR, new:LPSTR

    mov rdi,rcx
    mov rsi,strlen(r8)
    mov rbx,strlen(old)

    .while strstri(rdi, old)    ; find token

        mov rdi,rax             ; EDI to start of token
        lea rcx,[rax+rsi]
        add rax,rbx
        strmove(rcx, rax)       ; move($ + len(new), $ + len(old))
        memmove(rdi, new, rsi)  ; copy($, new, len(new))
        inc rdi                 ; $++
    .endw
    mov rax,dst
    ret

strxchg endp

    END
