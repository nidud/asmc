ifdef _WIN64
procs equ <for x,<0,2,3,4,5,6>> ; functions to test...
else
procs equ <for x,<0,1,2,3,5,6>>
endif
args_x macro
    mov eax,step_x
    mov rcx,m_endp
    inc eax
    sub rcx,rax
ifndef _WIN64
    push ecx
endif
    exitm<>
    endm

include ../timeit.inc

option dllimport:<msvcrt>
externdef import strlen:ptr_t
option dllimport:none

.data
 info_0 db "msvcrt.strlen()",0
 info_1 db "libc(__X86__)",0
 info_2 db "libc(__SSE__)",0
 info_3 db "libc(__AVX__)",0
 info_4 db "libc(__AVX512__)",0
 info_5 db "Intel Silvermont",0
 info_6 db "Intel Atom",0
 info_7 db "ucrt",0

.code

strlen_t typedef proto :ptr

ClearBuffer proto watcall :dword {
    mov rdi,m_4096
    mov ecx,4095
    rep stosb
    xor eax,eax
    stosb
    }

validate_x proc uses rsi rdi rbx x:dword

    mov ecx,x
    lea rax,proc_p
    mov rsi,[rax+rcx*size_t]
    .if !rsi
        .if ReadProc(ecx)
            mov rsi,proc_x
        .endif
    .endif
    .if rsi
        ClearBuffer('x')
        assume rsi:ptr strlen_t
        .for ( edi = 0 : edi < 200 && nerror < 10 : edi++ )
            mov rcx,m_endp
            sub rcx,rdi
            dec rcx
            .if ( rsi(rcx) != rdi )
                mov ecx,eax
                printf("error%d: %2d (%d) %d.asm\n", size_t*8, ecx, edi, x)
                inc nerror
            .endif
        .endf
        mov rbx,m_4096
        mov edi,4096-15
        add rbx,15
        .repeat
            dec edi
            mov byte ptr [rbx+rdi],0
            rsi(rbx)
        .until edi == 4096 - 33 - 15
        assume rsi:nothing
        ClearBuffer('x')
    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret
    endp

main proc
    mov rax,strlen
    mov proc_p,rax
    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return 1
        .endif
        endm
    GetCycleCount(0, 15, 2, 4000)
    GetCycleCount(16, 127, 8, 2000)
    GetCycleCount(128, 256, 14, 500)
    GetCycleCount(1024, 2048, 218, 400)
    xor eax,eax
    ret
    endp
    end start
