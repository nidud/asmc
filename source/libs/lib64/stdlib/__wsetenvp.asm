; __WSETENVP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include malloc.inc
include winbase.inc

    .code

__wsetenvp proc uses rsi rdi rbx envp:wstring_t

    .for ( rdi = GetEnvironmentStringsW(),
           rsi = rax,
           eax = 0,
           ebx = 0,
           ecx = -1 : word ptr [rdi] : )

        .if ( word ptr [rdi] != '=' )

            mov  rdx,rdi
            sub  rdx,rsi
            push rdx
            inc  rbx
        .endif
        repnz scasw
    .endf

    mov eax,ebx ; allocate call-stack
    and eax,1
    lea rax,[rax*8+32]
    sub rsp,rax

    inc rbx
    sub rdi,rsi
    malloc(&[rdi+rbx*8])

    mov rcx,envp
    mov [rcx],rax
    .return .if !rax

    memcpy(&[rax+rbx*8], rsi, rdi)
    xchg rax,rsi
    FreeEnvironmentStringsW(rax)

    lea rax,[rbx-1] ; reset stack
    and eax,1
    lea rsp,[rsp+rax*8+32]
    lea rdi,[rsi-8]
    xor eax,eax

    std
    stosq
    dec rbx
    .whilenz
        pop rax
        add rax,rsi
        stosq
        dec rbx
    .endw
    cld

    mov rax,envp
    mov rax,[rax]
    ret

__wsetenvp endp

    end
