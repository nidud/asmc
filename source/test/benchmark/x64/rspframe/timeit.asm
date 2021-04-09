
procs  equ <for x,<0,1>> ; add functions to test...

args_x macro
    exitm<>
    endm

include ../timeit.inc

    .data
    info_0 db "win64:rbp save auto",0
    info_1 db "win64:rsp save auto",0

    .code

validate_x proc x:dword

    lea rax,proc_p
    mov rax,[rax+rcx*8]
    .if !rax
        .if ReadProc(ecx)
            mov rax,proc_x
        .endif
    .endif
    .if rax
        call rax
        .if eax
            printf("error: %d [0] %d.asm\n", eax, x)
            inc nerror
        .endif
    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret

validate_x endp

main proc

    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return 1
        .endif
        endm

    GetCycleCount(0, 2, 1, 1000)
    ret

main endp

    end start
