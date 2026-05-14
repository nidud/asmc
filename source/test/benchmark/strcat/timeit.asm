ifdef _WIN64
procs equ <for x,<0,2,3,4>> ; functions to test...
else
procs equ <for x,<0,1,2,3>>
endif
args_x macro
    mov eax,step_x
ifdef _UNICODE
    add eax,eax
    lea rdx,str_1[size_s-2]
    sub rdx,rax
    mov rcx,m_endp
    sub rcx,rax
    mov word ptr [rcx-2],0
else
    lea rdx,str_1[size_s-1]
    sub rdx,rax
    mov rcx,m_endp
    sub rcx,rax
    mov byte ptr [rcx-1],0
endif
ifdef _WIN64
    mov rcx,m_4096
else
    push edx
    push m_4096
endif
    exitm<>
    endm

include ../timeit.inc

ifdef _UNICODE
define _tcscat <wcscat>
else
define _tcscat <strcat>
endif
option  dllimport:<msvcrt>
externdef import _tcscat:ptr

define size_s 4096 ; maximum data size

.data?
align   16
bss_1   TCHAR 256 dup(?)
bss_2   TCHAR 256 dup(?)
bss_3   TCHAR 256 dup(?)

.data
align   16
str_1   TCHAR size_s/TCHAR-1 dup('x'),0

%info_0 db "msvcrt.&_tcscat&()",0
%info_1 db "libc.&_tcscat&(__X86__)",0
%info_2 db "libc.&_tcscat&(__SSE__)",0
%info_3 db "libc.&_tcscat&(__AVX__)",0
%info_4 db "libc.&_tcscat&(__AVX512BW__)",0

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
            sub rdx,17*TCHAR
            lea eax,[rbx*TCHAR]
            sub rdx,rax
            mov TCHAR ptr [rdx],0
            mov eax,'?'
            lea rcx,[rbx+16]
            lea rdi,[rdx+TCHAR]
            rep _tstos
            mov rdi,rdx
            lea rdx,str_1[size_s-TCHAR]
            lea eax,[rbx*TCHAR]
            sub rdx,rax

            .if ( rsi(rdi, rdx) != rdi )
                printf("error: %06X [%06X] %d.asm\n", rax, rdi, x)
                inc nerror
            .else
                .for ( edx = 0, ecx = ebx : ecx : ecx-- )
                    .if TCHAR ptr [rax+rcx*TCHAR-TCHAR] != 'x'
                        lea rdx,[rax+rcx*TCHAR-TCHAR]
                        movzx ecx,TCHAR ptr [rdx]
                        %printf("error: '%c' ('x') (%d) %d.asm: (%X, %X) %&_F&\n", ecx, ebx, x, edi, edx, rdi)
                        inc nerror
                       .break
                    .endif
                .endf
                lea rax,[rdi+rbx*TCHAR]
                .if TCHAR ptr [rax]
                    movzx ecx,TCHAR ptr [rax]
                    %printf("error: [rax+rbx]: '%c' (0) (%d) %d.asm: %&_F&\n", ecx, ebx, x, rdi)
                    inc nerror
                .endif
                .for ( rax = &[rdi+rbx*TCHAR+TCHAR], ecx = 15 : ecx : ecx-- )
                    .if TCHAR ptr [rax+rcx*TCHAR-TCHAR] != '?'
                        lea rdx,[rax+rcx*TCHAR-TCHAR]
                        movzx ecx,TCHAR ptr [rdx]
                        %printf("error: '%c' ('?') (%d) %d.asm: (%X, %X) %&_F&\n", ecx, ebx, x, edi, edx, rdi)
                        inc nerror
                       .break
                    .endif
                .endf
                .if ( ebx )
                    lea edi,[rbx+'0']
                    .for ( rdx = &bss_1, eax = '0' : eax <= edi : eax++ )
                        mov [rdx+rax*TCHAR-TCHAR-'0'*TCHAR],_tal
                        mov [rdx+rax*TCHAR-TCHAR+256*TCHAR-'0'*TCHAR],_tal
                        mov [rdx+rax*TCHAR-TCHAR+512*TCHAR-'0'*TCHAR],_tal
                        lea rcx,[rbx+rax]
                        mov [rdx+rcx*TCHAR-TCHAR+512*TCHAR-'0'*TCHAR],_tal
                    .endf
                    xor eax,eax
                    mov [rdx+rbx*TCHAR],_tal
                    mov [rdx+rbx*TCHAR+256*TCHAR],_tal
                    mov [rdx+rbx*(2*TCHAR)+512*TCHAR],_tal
                    rsi(&bss_1, &bss_2)
                    mov rdx,rsi
                    mov rsi,rax
                    lea rdi,bss_3
                    lea ecx,[rbx*2]
                    repz _tcmps
                    mov rsi,rdx
                    .ifnz
                        %printf("error%d: (%d) %d.asm: %&_F&\n(%&_F&)\n %&_F&\n", size_t*8, ebx, x, &bss_2, &bss_3, &bss_1)
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
    mov proc_p,_tcscat
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
    mov ecx,4096/TCHAR-TCHAR
    rep _tstos
    mov TCHAR ptr [rdi],0
    GetCycleCount(  0,  31, 4, 100)
    GetCycleCount( 32, 127, 8, 80)
    GetCycleCount(128,1024,16, 40)
    xor eax,eax
    ret
    endp
    end start
