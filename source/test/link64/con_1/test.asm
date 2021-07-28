include stdio.inc
include stdlib.inc
include winnt.inc

extern __ImageBase:IMAGE_DOS_HEADER ; created by LINK

    .code

main proc

    printf("Address of __ImageBase:\t%p\n", &__ImageBase)
    printf("Address of main:\t%p\n", &main)

    lea rdx,__ImageBase
    mov eax,__ImageBase.e_lfanew
    mov eax,[rdx+rax].IMAGE_NT_HEADERS.OptionalHeader.AddressOfEntryPoint
    add rdx,rax

    printf("Address Of EntryPoint:\t%p\n", rdx)

    .return(0)

main endp

mainCRTStartup proc
    exit(main())
mainCRTStartup endp

    end

