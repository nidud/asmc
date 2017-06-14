include stdio.inc

    .code

wmain proc

    wprintf("con_64W: Win64 console Unicode application\n")
    xor eax,eax
    ret

wmain endp

    end
