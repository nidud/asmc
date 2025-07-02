; _TSETENVP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
ifndef __UNIX__
include string.inc
include malloc.inc
include winbase.inc
include tchar.inc
endif

define MAXCOUNT 256

    .code

ifndef __UNIX__

_tsetenvp proc uses rsi rdi rbx envp:tarray_t

    .new offs[MAXCOUNT]:int_t

    .for ( rdi = _tenvptr,
           rsi = rdi,
           eax = 0,
           ebx = 0,
           ecx = -1 : tchar_t ptr [rdi] && ebx < MAXCOUNT : )

        .if ( tchar_t ptr [rdi] != '=' )

            mov  rdx,rdi
            sub  rdx,rsi
            mov  offs[rbx*int_t],edx
            inc  rbx
        .endif
        repnz _tscasb
    .endf

    inc rbx
    malloc(&[rbx*size_t])
    mov rcx,envp
    mov [rcx],rax

    .if ( rax )

        .for ( rdi = rax, ebx--, ecx = 0 : ecx < ebx : ecx++ )

            mov eax,offs[rcx*int_t]
            add rax,rsi
            mov [rdi+rcx*size_t],rax
        .endf
        xor eax,eax
        mov [rdi+rcx*size_t],rax
        mov rax,rdi
    .endif
    ret

_tsetenvp endp

endif

    end
