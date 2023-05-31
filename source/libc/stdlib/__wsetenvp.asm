; __WSETENVP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include malloc.inc
include winbase.inc

define MAXCOUNT 256

    .code

ifndef __UNIX__

__wsetenvp proc uses rsi rdi rbx envp:wstring_t

    .new offs[MAXCOUNT]:int_t

    .for ( rdi = GetEnvironmentStringsW(),
           rsi = rax,
           eax = 0,
           ebx = 0,
           ecx = -1 : word ptr [rdi] && ebx < MAXCOUNT : )

        .if ( word ptr [rdi] != '=' )

            mov  rdx,rdi
            sub  rdx,rsi
            mov  offs[rbx*int_t],edx
            inc  rbx
        .endif
        repnz scasw
    .endf

    inc rbx
    sub rdi,rsi
    malloc(&[rdi+rbx*size_t])

    mov rcx,envp
    mov [rcx],rax
    .return .if !rax

    mov rcx,rdi
    mov rdi,rax
    memcpy(&[rax+rbx*size_t], rsi, rcx)
    xchg rax,rsi
    FreeEnvironmentStringsW(rax)

    .for ( ebx--, ecx = 0 : ecx < ebx : ecx++ )

        mov eax,offs[rcx*int_t]
        add rax,rsi
        mov [rdi+rcx*string_t],rax
    .endf
    xor eax,eax
    mov [rdi+rcx*string_t],rax
   .return( rdi )

__wsetenvp endp
endif
    end
