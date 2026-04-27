ifdef _WIN64
procs equ <for x,<0,2,3>> ; functions to test...
else
procs equ <for x,<0,1,2,3>>
endif
args_x macro
    mov rcx,m_endp
ifdef _WIN64
    mov eax,step_x
    sub rcx,rax
    mov edx,1
else
    sub ecx,step_x
    push 1
    push ecx
endif
    exitm<>
    endm

include ../timeit.inc

option dllimport:<msvcrt>
externdef import strchr:ptr

.data
info_0  db "msvcrt.strchr()",0
info_1  db "libc(__X86__)",0
info_2  db "libc(__SSE__)",0
info_3  db "libc(__AVX__)",0

.code

strchr_t typedef proto :ptr, :dword

validate_x proc uses rsi rdi rbx x

    ldr ecx,x
    lea rax,proc_p
    mov rsi,[rax+rcx*size_t]
    .if !rsi
        .if ReadProc(ecx)
            mov rsi,proc_x
        .endif
    .endif
    .if rsi
        assume rsi:ptr strchr_t
        mov rcx,m_endp
        lea rdi,[rcx-2]

        .if ( rsi(m_4096, 2) != 0 )
            mov rcx,rax
            printf("error: eax %06X [0] (%d) %d.asm\n", rcx, 4095, x)
            inc nerror
        .endif
        .if ( rsi(m_4096, 1) == 0 )
            mov rcx,rax
            printf("error: eax %06X [%06X] (%d) %d.asm\n", rcx, rdi, 4096, x)
            inc nerror
        .endif
        .for ( ebx = 2 : ebx < 290 && nerror < 10 : ebx++ )
            mov rcx,m_endp
            sub rcx,rbx
            .if ( rsi(rcx, 1) != rdi )
                mov rcx,rax
                printf("error: eax %06X [%06X] (%d) %d.asm\n", rcx, rdi, ebx, x)
                inc nerror
            .endif
        .endf
        assume rsi:nothing
    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret
    endp

main proc
    mov rax,strchr
    mov proc_p,rax
    mov rdi,m_4096
    mov ecx,4094
    mov eax,'x'
    rep stosb
    mov word ptr [rdi],1
    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return( 1 )
        .endif
        endm
    GetCycleCount(   1,   31, 3, 1000)
    GetCycleCount( 127,  129, 1,  500)
    GetCycleCount(1023, 1029, 1,  200)
    xor eax,eax
    ret
    endp
    end start
