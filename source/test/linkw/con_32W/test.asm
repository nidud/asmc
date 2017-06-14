include stdio.inc

    .code

wmain proc

    wprintf("con_32W: Win32 console Unicode application\n")
    xor eax,eax
    ret

wmain endp

    end
