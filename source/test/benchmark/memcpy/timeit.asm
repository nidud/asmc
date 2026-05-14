ifdef _WIN64
procs equ <for x,<0,2,3,4>> ; functions to test...
args_x macro
    mov rcx,m_4096
    mov edx,0
    mov r8d,step_x
    exitm<>
    endm
else
procs equ <for x,<0,1,2,3>>
args_x macro
    push step_x
    push 0
    push m_4096
    exitm<>
    endm
endif

include ../timeit.inc
option  dllimport:<msvcrt>
externdef import memset:ptr

.data
 info_0  db "msvcrt.memset()",0
 info_1  db "libc(__X86__)",0
 info_2  db "libc(__SSE__)",0
 info_3  db "libc(__AVX__)",0
 info_4  db "libc(__AVX512__)",0

.code

memset_t typedef proto :ptr, :dword, :qword

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
        assume rsi:ptr memset_t
        .for ( ebx = 1 : ebx < 290 && nerror < 5 : ebx++ )

            mov rdx,m_4096
            add rdx,4096-17
            sub rdx,rbx
            mov byte ptr [rdx-1],0
            mov eax,'?'
            lea rcx,[rbx+16]
            mov rdi,rdx
            rep stosb
            mov byte ptr [rdi],0
            mov rdi,rdx
            .if ( rsi(rdi, 'x', rbx) != rdi )
                printf("error: rax %06X [%06X] %d.asm\n", rax, rdi, x)
                inc nerror
            .else
                xor edx,edx
                mov rcx,rbx
                .repeat
                    .if byte ptr [rax+rcx-1] != 'x'
                        inc edx
                    .endif
                .untilcxz
                add rax,rbx
                mov ecx,16
                .repeat
                    .if byte ptr [rax+rcx-1] != '?'
                        inc edx
                    .endif
                .untilcxz
                .if edx
                    printf("error: %04X (%d) %d.asm: %s\n", edi, ebx, x, rdi)
                    inc nerror
                .endif
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
    mov rax,memset
    mov proc_p,rax
    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return( 1 )
        .endif
        endm
    GetCycleCount(  1,    8,   1, 1000)
    GetCycleCount(  0,   64,   3, 1000)
    GetCycleCount( 64,  512,  64, 1000)
    GetCycleCount(512, 4096, 256, 400)
    xor eax,eax
    ret
    endp
    end start
