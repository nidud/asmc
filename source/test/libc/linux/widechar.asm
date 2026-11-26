include stdio.inc
.code
 main proc
    printf("%%C(0x00F8):\tUnicode char:\t%C\n%%S(\\U1F600):\t%S\n", 0x00F8, L"Unicode string:\t\U1F600")
    xor eax,eax
    ret
    endp

    end
