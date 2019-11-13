; __SETENVP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include malloc.inc
include winbase.inc

    .code

__setenvp proc uses rsi rdi rbx envp:string_t

    ; size up the environment

    .for ( rdi = GetEnvironmentStringsA(),
           rsi = rax, ; save start of block in ESI
           eax = 0,
           ebx = 0,
           ecx = -1 : al != [rdi] : )

        .if ( byte ptr [rdi] != '=' )

            mov  rdx,rdi    ; save offset of string
            sub  rdx,rsi
            push rdx
            inc  rbx        ; increase count
        .endif
        repnz scasb         ; next string..
    .endf

    mov eax,ebx             ; allocate call-stack
    and eax,1
    lea rax,[rax*8+32]
    sub rsp,rax

    inc ebx                 ; count strings plus NULL
    sub rdi,rsi             ; EDI to size
    malloc(&[rdi+rbx*8])    ; pointers plus size of environment

    mov rcx,envp            ; return result
    mov [rcx],rax

    .return .if rax == NULL
                            ; new adderss of block
    memcpy(&[rax+rbx*8], rsi, rdi)

    xchg rax,rsi            ; ESI to block
    FreeEnvironmentStringsA(rax)

    lea rax,[rbx-1]         ; reset stack
    and eax,1
    lea rsp,[rsp+rax*8+32]
    lea rdi,[rsi-8]         ; EDI to end of pointers array
    xor eax,eax             ; set last pointer to NULL
    std                     ; move backwards
    stosq
    dec ebx
    .whilenz
        pop rax             ; pop offset in reverse
        add rax,rsi         ; add address of block
        stosq
        dec ebx
    .endw
    cld                     ; clear flag

    mov rcx,envp            ; return address of new _environ
    mov rax,[rcx]
    ret

__setenvp ENDP

    END
