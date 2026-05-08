ifdef _WIN64
procs equ <for x,<0,2,3,4>> ; functions to test...
else
procs equ <for x,<0,1,2,3>>
endif
args_x macro
    mov eax,step_x
    lea rdx,str_1[size_s]
    sub rdx,rax
ifdef _WIN64
    mov rcx,m_4096
else
    push edx
    push m_4096
endif
    exitm<>
    endm

;define O_NOFILE

include ../timeit.inc
option  dllimport:<msvcrt>
externdef import strcpy:ptr_t

define size_s 4096 ; maximum data size

.data
str_1   db size_s-1 dup('x'),0

info_0  db "msvcrt.strcpy()",0
info_1  db "libc(__X86__)",0
info_2  db "libc(__SSE__)",0
info_3  db "libc(__AVX__)",0
info_4  db "libc(__AVX512__)",0

.code

strcpy_t typedef proto :ptr, :ptr

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

        assume rsi:ptr strcpy_t
        .for ( ebx = 0 : ebx < 70 && nerror < 10 : ebx++ )

            mov rdx,m_endp
            sub rdx,17
            sub rdx,rbx
            mov byte ptr [rdx-1],0
            mov eax,'?'
            lea rcx,[rbx+16]
            mov rdi,rdx
            rep stosb
            mov byte ptr [rdi],0
            mov rdi,rdx
            lea rdx,str_1[size_s-1]
            sub rdx,rbx
            .if ( rsi(rdi, rdx) != rdi )
                printf("error: rax %06X [%06X] %d.asm\n", rax, rdi, x)
                inc nerror
            .else
                .for ( ecx = ebx : ecx : ecx-- )
                    .if byte ptr [rax+rcx-1] != 'x'
                        movzx ecx,byte ptr [rax+rcx-1]
                        lea rdx,str_1[size_s-1]
                        sub rdx,rbx
                        printf("error%d: '%c' ('x') (%d) %d.asm: %s\n", size_t*8, ecx, ebx, x, rdi)
                        inc nerror
                       .break
                    .endif
                .endf
                .if byte ptr [rdi-1]
                    movzx ecx,byte ptr [rdi-1]
                    printf("error%d: [rax-1]: '%c' (0) (%d) %d.asm: %s\n", size_t*8, ecx, ebx, x, rdi)
                    inc nerror
                .endif
                lea rax,[rdi+rbx]
                .if byte ptr [rax]
                    movzx ecx,byte ptr [rax]
                    lea rdx,str_1[size_s-1]
                    sub rdx,rbx
                    printf("error%d: [rax+rbx]: '%c' (0) (%d) %d.asm:\n%p: %s\n%p: %s\n", size_t*8, ecx, ebx, x, rdi, rdi, rdx, rdx)
                    inc nerror
                .endif
                .for ( rax = &[rdi+rbx+1], ecx = 15 : ecx : ecx-- )
                    .if byte ptr [rax+rcx-1] != '?'
                        movzx ecx,byte ptr [rax+rcx-1]
                        printf("error%d: '%c' ('?') (%d) %d.asm: %s\n", size_t*8, ecx, ebx, x, rdi)
                        inc nerror
                       .break
                    .endif
                .endf
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
    mov rax,strcpy
    mov proc_p,rax
    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return( 1 )
        .endif
        endm
    GetCycleCount(  0,  32, 4, 1000)
    GetCycleCount( 32, 128, 8, 800)
    GetCycleCount(128, 512, 8, 400)
    xor eax,eax
    ret
    endp
    end start
