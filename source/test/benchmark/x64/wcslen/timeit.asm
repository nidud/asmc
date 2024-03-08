
procs equ <for x,<0,1,2,3>> ; add functions to test...

args_x macro
    lea rcx,str_2
    mov eax,step_x
    sub rcx,rax
    exitm<>
    endm

    option dllimport:<msvcrt>
    wcslen proto :ptr byte
    option dllimport:<kernel32>
    MEM_COMMIT equ 0x1000
    MEM_RELEASE equ 0x8000
    PAGE_READWRITE equ 0x04
    VirtualAlloc proto :dword, :dword, :dword, :dword
    VirtualFree proto :ptr, :dword, :dword

include ../timeit.inc

size_s  equ 4096 ; maximum data size

    .data?

    str_1 db size_s dup(?)
    str_2 dd ?

    .data

    info_0 db "msvcrt",0
    info_1 db "scasw",0
    info_2 db "SSE 16",0
    info_3 db "AVX 32",0

    .code

;-------------------------------------------------------------------------------
; test if the algo actually works..
;-------------------------------------------------------------------------------

TEST_OVERLAP equ 1

validate_x proc uses rsi rdi rbx x:dword

    lea rax,proc_p
    mov rsi,[rax+rcx*8]

    .if !rsi

        .if ReadProc(ecx)

            mov rsi,proc_x
        .endif
    .endif

    .if rsi

        .for edi = 0: edi < 200: edi+=2

            lea  rcx,str_1[size_s]
            sub  rcx,rdi
            call rsi
            mov  ecx,edi
            shr  ecx,1

            .if eax != ecx

                printf("error: eax = %d (%d) proc_%d\n", eax, ecx, x)
                inc nerror
            .endif
        .endf

ifdef TEST_OVERLAP

        .if VirtualAlloc(0, 4096, MEM_COMMIT, PAGE_READWRITE)

            mov rbx,rax
            mov rdi,rax
            mov ecx,4096
            mov eax,'x'
            rep stosb
            mov edi,4096-30
            add rbx,30
            .repeat
                sub edi,2
                mov word ptr [rbx+rdi],0
                mov rcx,rbx
                call rsi

            .until edi == 4096 - 66 - 30
            sub rbx,30
            VirtualFree(rbx, 0, MEM_RELEASE)
        .endif
endif

    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret

validate_x ENDP

main proc

    lea rdi,str_1
    mov ecx,size_s
    mov al,'x'
    rep stosb
    xor eax,eax
    stosd

    wcslen(&str_1)
    mov rax,__imp_wcslen
    mov proc_p,rax

    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
           .return 1
        .endif
        endm

    GetCycleCount(0, 10, 2, 8000)
    GetCycleCount(10, 80, 16, 5000)
    GetCycleCount(600, 1000, 200, 1000)
    ret

main endp

    end start
