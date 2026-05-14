ifdef _WIN64
procs equ <for x,<0,2,3,4>> ; functions to test...
else
procs equ <for x,<0,1,2,3>>
endif
args_x macro
    mov eax,step_x
ifdef _UNICODE
    add eax,eax
endif
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

include ../timeit.inc

ifdef _UNICODE
define _tcscpy <wcscpy>
else
define _tcscpy <strcpy>
endif
option dllimport:<msvcrt>
externdef import _tcscpy:ptr

define size_s 4096 ; maximum data size

.data
align   16
str_1   TCHAR size_s/TCHAR-1 dup('x'),0

%info_0 db "msvcrt.&_tcscpy&()",0
%info_1 db "libc.&_tcscpy&(__X86__)",0
%info_2 db "libc.&_tcscpy&(__SSE__)",0
%info_3 db "libc.&_tcscpy&(__AVX__)",0
%info_4 db "libc.&_tcscpy&(__AVX512BW__)",0

align 16
IDB = '0'
test256 label TCHAR
while IDB lt 140+'0'
TCHAR IDB
IDB = IDB + 1
endm
tnul TCHAR 0

.code

strcpy_t typedef proto :ptr, :ptr

validate_x proc uses rsi rdi rbx x:dword

   .new a:ptr
   .new b:ptr

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
            sub rdx,17*TCHAR
            lea eax,[rbx*TCHAR]
            sub rdx,rax
            mov TCHAR ptr [rdx-TCHAR],0
            mov eax,'?'
            lea rcx,[rbx+16]
            mov rdi,rdx
            rep _tstos
            mov TCHAR ptr [rdi],0
            mov rdi,rdx
            lea rdx,str_1[size_s-TCHAR]
            lea eax,[rbx*TCHAR]
            sub rdx,rax
            mov b,rdx

            .if ( rsi(rdi, rdx) != rdi )

                printf("error: %06X [%06X] %d.asm\n", rax, rdi, x)
                inc nerror
               .break
            .endif
            .for ( ecx = ebx : ecx : ecx-- )
                .if TCHAR ptr [rax+rcx*TCHAR-TCHAR] != 'x'
                    movzx ecx,TCHAR ptr [rax+rcx*TCHAR-TCHAR]
                    %printf("error%d%c: '%c' ('x') (%d) %d.asm:\n%p: %&_F&\n", size_t*8, _W, ecx, ebx, x, rdi, rdi)
                    inc nerror
                   .break
                .endif
            .endf
            .if TCHAR ptr [rdi-TCHAR]
                movzx ecx,TCHAR ptr [rdi-TCHAR]
                %printf("error%d: [rax-1]: '%c' (0) (%d) %d.asm: %&_F&\n", size_t*8, ecx, ebx, x, rdi)
                inc nerror
            .endif
            lea rax,[rdi+rbx*TCHAR]
            .if TCHAR ptr [rax]
                movzx ecx,TCHAR ptr [rax]
                mov rdx,b
                %printf("error%d: [rax+rbx]: '%c' (0) (%d) %d.asm:\n%p: %s\n%p: %&_F&\n", size_t*8, ecx, ebx, x, rdi, rdi, rdx, rdx)
                inc nerror
            .endif
            .for ( rax = &[rdi+rbx*TCHAR+TCHAR], ecx = 15 : ecx : ecx-- )
                .if TCHAR ptr [rax+rcx*TCHAR-TCHAR] != '?'
                    movzx ecx,TCHAR ptr [rax+rcx*TCHAR-TCHAR]
                    printf("error%d: '%c' ('?') (%d) %d.asm: %s\n", size_t*8, ecx, ebx, x, rdi)
                    inc nerror
                   .break
                .endif
            .endf
            mov rdi,m_4096
            lea eax,[rbx*TCHAR]
            add rdi,rax
            mov a,rdi
            lea rdi,tnul
            sub rdi,rax
            rsi(a, rdi)
            xor ecx,ecx
            mov rdx,rsi
            mov rsi,rax
            mov ecx,ebx
            repe _tcmps
            xchg rsi,rdx
            .ifnz
                mov TCHAR ptr [rax+rbx*TCHAR],0
                %printf("error%d: (%d) %d.asm:\n%s\n%&_F&\n", size_t*8, ebx, x, rdi, rdx)
                inc nerror
            .endif
            .if ( ebx )
                mov rdx,a
                add rdx,TCHAR
                rsi(a, rdx)
                lea rdi,tnul+TCHAR
                lea ecx,[rbx*TCHAR]
                sub rdi,rcx
                xor ecx,ecx
                mov rdx,rsi
                mov rsi,rax
                lea ecx,[rbx-1]
                repe _tcmps
                xchg rsi,rdx
                .ifnz
                    mov rcx,rax
                    mov TCHAR ptr [rax+rbx*TCHAR],0
                    %printf("error%d: %06X, +1 (%d) %d.asm:\n%s\n%&_F&\n", size_t*8, ecx, ebx, x, rdi, rdx)
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
    mov proc_p,_tcscpy
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
