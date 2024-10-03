include stdio.inc

    .code

main proc

    printf("MSVCRT Console Application: external mainCRTStartup\n")
    xor eax,eax
    ret

main endp

    end

