include stdio.inc

    .code

main proc argc:SINT, argv:ptr
local q, i

    .for eax=argc, q=eax, rbx=argv, i=0: q: q--, i++, rbx+=size_t

        printf("[%d]: %s\n", i, [rbx])
    .endf
    xor eax,eax
    ret

main endp

    end
