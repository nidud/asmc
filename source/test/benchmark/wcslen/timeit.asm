ifdef _WIN64
procs equ <for x,<0,2,3,4>> ; functions to test...
else
procs equ <for x,<0,1,2,3>>
endif
args_x macro
    imul eax,step_x,2
    mov  rcx,m_endp
    add  eax,2
    sub  rcx,rax
ifndef _WIN64
    push ecx
endif
    exitm<>
    endm

include ../timeit.inc

option dllimport:<msvcrt>
externdef import wcslen:ptr_t
option dllimport:none

.data
 info_0 db "msvcrt.wcslen()",0
 info_1 db "libc(__X86__)",0
 info_2 db "libc(__SSE__)",0
 info_3 db "libc(__AVX__)",0
 info_4 db "libc(__AVX512__)",0

.code

wcslen_t typedef proto :ptr

ClearBuffer proto watcall :dword {
    mov rdi,m_4096
    mov ecx,4094/2
    rep stosw
    xor eax,eax
    stosw
    }

validate_x proc uses rsi rdi rbx x:dword

    ldr ecx,x
    lea rax,proc_p
    mov rsi,[rax+rcx*size_t]
    .if !rsi
        .if ReadProc(ecx)
            mov rsi,proc_x
        .endif
    .endif
    .if rsi
        ClearBuffer('x')
        assume rsi:ptr wcslen_t
        .for ( edi = 0, ebx = 0 : edi < 200 && nerror < 10 : edi+=2, ebx++ )
            mov rcx,m_endp
            sub rcx,rdi
            sub rcx,2
            .if ( rsi(rcx) != rbx )
                printf("error: eax = %d (%d) proc_%d\n", eax, ebx, x)
                inc nerror
            .endif
        .endf
        mov rbx,m_4096
        mov edi,4096-30
        add rbx,30
        .repeat
            sub edi,2
            mov word ptr [rbx+rdi],0
            rsi(rbx)
        .until edi == 4096 - 66 - 30
        assume rsi:nothing
        ClearBuffer('x')
    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret
    endp

main proc
    mov rax,wcslen
    mov proc_p,rax
    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return 1
        .endif
        endm
    GetCycleCount(  0,   31,   3, 4000)
    GetCycleCount( 32,  127,   8, 2000)
    GetCycleCount(128, 2047, 128,  500)
    ret
    endp
    end start
