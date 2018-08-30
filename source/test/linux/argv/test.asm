include stdio.inc

    .code

main proc uses rbx r12 argc:SINT, argv:ptr

  local arg_count:SINT

    .for (arg_count = argc, ebx = 0,
        r12 = argv: ebx < arg_count: ebx++, r12 += size_t)

        printf("[%d]: %s\n", ebx, [r12])
    .endf
    xor eax,eax
    ret

main endp

    end
