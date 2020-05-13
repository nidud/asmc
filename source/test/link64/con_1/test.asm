include stdio.inc
include stdlib.inc

    .code

main proc

    printf("link64:con_1\n")
    xor eax,eax
    ret

main endp

mainCRTStartup proc
    exit(main())
mainCRTStartup endp

    end
