ifdef _WIN64
ifdef _UNICODE
procs equ <for x,<0,2,3,4>>
else
procs equ <for x,<0,2,3,4,5,6>>
endif
else
ifdef _UNICODE
procs equ <for x,<0,1,2,3>>
else
procs equ <for x,<0,1,2,3,5,6>>
endif
endif
args_x macro
    mov rcx,m_endp
ifdef _UNICODE
    imul eax,step_x,2
    add  eax,2
else
    mov eax,step_x
    inc eax
endif
    sub rcx,rax
ifndef _WIN64
    push ecx
endif
    exitm<>
    endm

include ../timeit.inc

ifdef _UNICODE
define _tcslen <wcslen>
else
define _tcslen <strlen>
endif
option dllimport:<msvcrt>
externdef import _tcslen:ptr_t

.data
%info_0 db "msvcrt.&_tcslen&()",0
%info_1 db "libc.&_tcslen&(__X86__)",0
%info_2 db "libc.&_tcslen&(__SSE__)",0
%info_3 db "libc.&_tcslen&(__AVX__)",0
%info_4 db "libc.&_tcslen&(__AVX512__)",0
 info_5 db "Intel Silvermont",0
 info_6 db "Intel Atom",0

.code

strlen_t typedef proto :ptr

ClearBuffer proto watcall :dword {
    mov rdi,m_4096
    mov ecx,4095/TCHAR
    rep _tstos
    xor eax,eax
    _tstos
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
        .for ( edi = 0, ebx = 0 : edi < 200 && nerror < 10 : edi+=TCHAR, ebx++ )
            mov rcx,m_endp
            sub rcx,rdi
            sub rcx,TCHAR
            .if ( rsi(rcx) != rbx )
                mov ecx,eax
                printf("error%d: %2d (%d) %d.asm\n", size_t*8, ecx, ebx, x)
                inc nerror
            .endif
        .endf
        mov rbx,m_4096
        mov edi,4096-15*TCHAR
        add rbx,15*TCHAR
        .repeat
            sub edi,TCHAR
            mov TCHAR ptr [rbx+rdi],0
            rsi(rbx)
        .until edi == 4096 - 33*TCHAR - 15*TCHAR
        assume rsi:nothing
        ClearBuffer('x')
    .else
        printf("error load: %d.asm\n", x)
        inc nerror
    .endif
    ret
    endp

main proc
    mov proc_p,_tcslen
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
