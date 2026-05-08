ifdef _WIN64
procs equ <for x,<0,2,3,4>> ; functions to test...
else
procs equ <for x,<0,1,2,3>>
endif
args_x macro
    mov eax,step_x
    lea rdx,str_1[size_s-1]
    sub rdx,rax
    mov rcx,m_endp
    sub rcx,rax
    mov byte ptr [rcx-1],0
ifdef _WIN64
    mov rcx,m_4096
else
    push edx
    push m_4096
endif
    exitm<>
    endm

include ../timeit.inc
option  dllimport:<msvcrt>
externdef import strcat:ptr

define size_s 4096 ; maximum data size

.data?
db ?
bss_1   db 256 dup(?)
bss_2   db 256 dup(?)
bss_3   db 256 dup(?)

.data
str_1   db size_s-1 dup('x'),0

info_0  db "msvcrt.strcat()",0
info_1  db "libc(__X86__)",0
info_2  db "libc(__SSE__)",0
info_3  db "libc(__AVX__)",0
info_4  db "libc(__AVX512__)",0


.code

strcat_t typedef proto :ptr, :ptr

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

        assume rsi:ptr strcat_t
        .for ( ebx = 0 : ebx < 80 && nerror < 10 : ebx++ )

            mov rdx,m_endp
            sub rdx,17
            sub rdx,rbx
            mov byte ptr [rdx],0
            mov eax,'?'
            lea rcx,[rbx+16]
            lea rdi,[rdx+1]
            rep stosb
            mov rdi,rdx
            lea rdx,str_1[size_s-1]
            sub rdx,rbx

            .if ( rsi(rdi, rdx) != rdi )
                printf("error: rax %06X [%06X] %d.asm\n", rax, rdi, x)
                inc nerror
            .else
                .for ( edx = 0, ecx = ebx : ecx : ecx-- )
                    .if byte ptr [rax+rcx-1] != 'x'
                        lea rdx,[rax+rcx-1]
                        movzx ecx,byte ptr [rdx]
                        printf("error: '%c' ('x') (%d) %d.asm: (%X, %X) %s\n", ecx, ebx, x, edi, edx, rdi)
                        inc nerror
                       .break
                    .endif
                .endf
                lea rax,[rdi+rbx]
                .if byte ptr [rax]
                    movzx ecx,byte ptr [rax]
                    printf("error: [rax+rbx]: '%c' (0) (%d) %d.asm: %s\n", ecx, ebx, x, rdi)
                    inc nerror
                .endif
                .for ( rax = &[rdi+rbx+1], ecx = 15 : ecx : ecx-- )
                    .if byte ptr [rax+rcx-1] != '?'
                        lea rdx,[rax+rcx-1]
                        movzx ecx,byte ptr [rdx]
                        printf("error: '%c' ('?') (%d) %d.asm: (%X, %X) %s\n", ecx, ebx, x, edi, edx, rdi)
                        inc nerror
                       .break
                    .endif
                .endf
                .if ( ebx )
                    lea edi,[rbx+'0']
                    .for ( rdx = &bss_1, eax = '0' : eax <= edi : eax++ )
                        mov [rdx+rax-1-'0'],al
                        mov [rdx+rax-1+256-'0'],al
                        mov [rdx+rax-1+512-'0'],al
                        lea rcx,[rbx+rax]
                        mov [rdx+rcx-1+512-'0'],al
                    .endf
                    mov [rdx+rbx],ah
                    mov [rdx+rbx+256],ah
                    mov [rdx+rbx*2+512],ah
                    rsi(&bss_1, &bss_2)
                    mov rdx,rsi
                    mov rsi,rax
                    lea rdi,bss_3
                    lea ecx,[rbx*2]
                    repz cmpsb
                    mov rsi,rdx
                    .ifnz
                        printf("error%d: (%d) %d.asm: %s\n(%s)\n %s\n", size_t*8, ebx, x, &bss_2, &bss_3, &bss_1)
                        inc nerror
                    .endif
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
    mov proc_p,strcat
    procs
        validate_x(x)
        .if nerror
            printf("hit any key to continue...\n")
            _getch()
            .return( 1 )
        .endif
        endm
    mov rdi,m_4096
    mov eax,'x'
    mov ecx,4096-1
    rep stosb
    mov [rdi],ah
    GetCycleCount(  0,  31, 4, 100)
    GetCycleCount( 32, 127, 8, 80)
    GetCycleCount(128,1024,16, 40)
    xor eax,eax
    ret
    endp
    end start
