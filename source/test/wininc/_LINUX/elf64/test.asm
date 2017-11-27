; _LINUX and _WIN64 defined by Asmc if switch -elf[64] or -win64 is used

include stdio.inc

    .code

main proc argc:SINT, argv:ptr

    printf("[%d]: %p\n", argc, argv)
    xor eax,eax
    ret

main endp

    end
