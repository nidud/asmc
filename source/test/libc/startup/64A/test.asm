include stdio.inc

.code

main proc
    .for(rsi=rdx, edi=ecx, ebx=0: edi: ebx++, edi--)
        lodsq
        printf("[%d]: %s\n", ebx, rax)
    .endf
    xor eax,eax
    ret
main endp

    end
