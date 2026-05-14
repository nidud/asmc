ifdef _WIN64
procs equ <for x,<0,2,3,4>> ; functions to test...
else
procs equ <for x,<0,1,2,3>>
endif
args_x macro
    mov rcx,m_endp
    mov eax,step_x
ifdef _UNICODE
    add eax,eax
endif
    sub rcx,rax
ifdef _WIN64
    mov edx,1
else
    push 1
    push ecx
endif
    exitm<>
    endm

include ../timeit.inc

ifdef _UNICODE
define _tcschr <wcschr>
define _W 'W'
else
define _tcschr <strchr>
define _W 'A'
endif
option dllimport:<msvcrt>
externdef import _tcschr:ptr

.data
%info_0  db "msvcrt.&_tcschr&()",0
%info_1  db "libc.&_tcschr&(__X86__)",0
%info_2  db "libc.&_tcschr&(__SSE__)",0
%info_3  db "libc.&_tcschr&(__AVX__)",0
%info_4  db "libc.&_tcschr&(__AVX512BW__)",0

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
        lea rdi,[rcx-2*TCHAR]

        .if ( rsi(m_4096, 2) != 0 )
            mov rcx,rax
            printf("error%d%c: %06X [0] (%d) %d.asm\n", size_t*8, _W, ecx, 4095/TCHAR, x)
            inc nerror
        .endif
        .if ( rsi(m_4096, 1) == 0 )
            mov rcx,rax
            printf("error%d%c: %06X [%06X] (%d) %d.asm\n", size_t*8, _W, ecx, edi, 4096/TCHAR, x)
            inc nerror
        .endif
        .for ( ebx = 2 : ebx < 290 && nerror < 10 : ebx++ )
            mov rcx,m_endp
            sub rcx,rbx
ifdef _UNICODE
            sub rcx,rbx
endif
            .if ( rsi(rcx, 1) != rdi )
                mov rcx,rax
                mov rdx,m_endp
                sub rdx,rbx
ifdef _UNICODE
                sub rcx,rbx
endif
                printf("error%d%c: (%06X) %06X [%06X] (%d) %d.asm\n", size_t*8, _W, edx, ecx, edi, ebx, x)
                inc nerror
            .endif
        .endf
        assume rsi:nothing
    .else
        printf("error%d%c load: %d.asm\n", size_t*8, _W, x)
        inc nerror
    .endif
    ret
    endp

main proc
    mov proc_p,_tcschr
    mov rdi,m_4096
ifdef _UNICODE
    mov ecx,4092/2
    mov eax,'x'
    rep stosw
    mov dword ptr [rdi],1
else
    mov ecx,4094
    mov eax,'x'
    rep stosb
    mov word ptr [rdi],1
endif
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
