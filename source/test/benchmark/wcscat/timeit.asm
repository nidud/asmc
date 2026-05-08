ifdef _WIN64
procs equ <for x,<0,2,3,4>> ; functions to test...
else
procs equ <for x,<0,1,2,3>>
endif
args_x macro
    imul eax,step_x,2
    lea rdx,str_1[size_s-2]
    sub rdx,rax
    mov rcx,m_endp
    sub rcx,rax
    mov word ptr [rcx-2],0
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
externdef import wcscat:ptr

define size_s 4096 ; maximum data size

.data?
align 16
bss_1   dw 256 dup(?)
bss_2   dw 256 dup(?)
bss_3   dw 256 dup(?)

.data
align 16
str_1   dw size_s/2-1 dup('x'),0

info_0  db "msvcrt.wcscat()",0
info_1  db "libc.wcscat(__X86__)",0
info_2  db "libc.wcscat(__SSE__)",0
info_3  db "libc.wcscat(__AVX__)",0
info_4  db "libc.wcscat(__AVX512__)",0


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
            sub rdx,17*2
            sub rdx,rbx
            sub rdx,rbx
            mov word ptr [rdx],0
            mov eax,'?'
            lea rcx,[rbx+16]
            lea rdi,[rdx+2]
            rep stosw
            mov rdi,rdx
            lea rdx,str_1[size_s-2]
            sub rdx,rbx
            sub rdx,rbx

            .if ( rsi(rdi, rdx) != rdi )
                printf("error: rax %06X [%06X] %d.asm\n", rax, rdi, x)
                inc nerror
            .else
                .for ( ecx = ebx : ecx : ecx-- )
                    .if word ptr [rax+rcx*2-2] != 'x'
                        lea rdx,[rax+rcx*2-2]
                        movzx ecx,word ptr [rdx]
                        printf("error: '%C' ('x') (%d) %d.asm: (%X, %X) %S\n", ecx, ebx, x, edi, edx, rdi)
                        inc nerror
                       .break
                    .endif
                .endf
                lea rax,[rdi+rbx*2]
                .if word ptr [rax]
                    movzx ecx,word ptr [rax]
                    printf("error: [rax+rbx]: '%C' (0) (%d) %d.asm: %S\n", ecx, ebx, x, rdi)
                    inc nerror
                .endif
                .for ( rax = &[rdi+rbx*2+2], ecx = 15 : ecx : ecx-- )
                    .if word ptr [rax+rcx*2-2] != '?'
                        lea rdx,[rax+rcx*2-2]
                        movzx ecx,word ptr [rdx]
                        printf("error: '%C' ('?') (%d) %d.asm: (%X, %X) %S\n", ecx, ebx, x, edi, edx, rdi)
                        inc nerror
                       .break
                    .endif
                .endf
                .if ( ebx )
                    lea edi,[rbx+'0']
                    .for ( rdx = &bss_1, eax = '0' : eax <= edi : eax++ )
                        mov [rdx+rax*2-2-'0'*2],ax
                        mov [rdx+rax*2-2+256*2-'0'*2],ax
                        mov [rdx+rax*2-2+512*2-'0'*2],ax
                        lea rcx,[rbx+rax]
                        mov [rdx+rcx*2-2+512*2-'0'*2],ax
                    .endf
                    xor eax,eax
                    mov [rdx+rbx*2],ax
                    mov [rdx+rbx*2+256*2],ax
                    mov [rdx+rbx*4+512*2],ax
                    rsi(&bss_1, &bss_2)
                    mov rdx,rsi
                    mov rsi,rax
                    lea rdi,bss_3
                    lea ecx,[rbx*2]
                    repz cmpsw
                    mov rsi,rdx
                    .ifnz
                        printf("error%d: (%d) %d.asm: %S\n(%S)\n %S\n", size_t*8, ebx, x, &bss_2, &bss_3, &bss_1)
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
    mov proc_p,wcscat
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
    mov ecx,4096/2-2
    rep stosw
    mov word ptr [rdi],0
    GetCycleCount(  0,  31, 4,100)
    GetCycleCount( 32, 127, 8, 80)
    GetCycleCount(128,1024,16, 40)
    xor eax,eax
    ret
    endp
    end start
