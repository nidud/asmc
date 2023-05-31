; __SETENVP.ASM--
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

__setenvp proc uses rsi rdi rbx envp:string_t

    .new offs[MAXCOUNT]:int_t

    ; size up the environment

    .for ( rdi = GetEnvironmentStringsA(),
           rsi = rax, ; save start of block in ESI
           eax = 0,
           ebx = 0,
           ecx = -1 : al != [rdi] && ebx < MAXCOUNT : )

        .if ( byte ptr [rdi] != '=' )

            mov  rdx,rdi    ; save offset of string
            sub  rdx,rsi
            mov  offs[rbx*int_t],edx
            inc  rbx        ; increase count
        .endif
        repnz scasb         ; next string..
    .endf

    inc ebx                 ; count strings plus NULL
    sub rdi,rsi             ; EDI to size
    malloc( &[rdi+rbx*size_t] ) ; pointers plus size of environment

    mov rcx,envp            ; return result
    mov [rcx],rax
    .if ( rax == NULL )
        .return
    .endif
    mov rcx,rdi
    mov rdi,rax
                            ; new adderss of block
    memcpy( &[rax+rbx*size_t], rsi, rcx )

    xchg rax,rsi            ; ESI to block
    FreeEnvironmentStringsA(rax)

    .for ( ebx--, ecx = 0 : ecx < ebx : ecx++ )

        mov eax,offs[rcx*int_t]
        add rax,rsi
        mov [rdi+rcx*string_t],rax
    .endf
    xor eax,eax
    mov [rdi+rcx*string_t],rax
   .return( rdi )

__setenvp endp
endif
    end
