; USESDS0.ASM--
;
; v2.37.14 - <USESDS>
;
.286
.model small, c
.code

string proc <usesds> uses si di p:ptr, q:ptr

    ldr si,p
    ldr di,q
    ret

string endp

string1 proc <usesds> uses di p:ptr

    ldr di,p
    ret

string1 endp

    end
