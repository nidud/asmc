; __DIVO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    option win64:noauto

u128 struct
l64  dq ?
h64  dq ?
u128 ends

    .code

    assume rdi:ptr u128
    assume rsi:ptr u128
    assume rdx:ptr u128

__divo proc dividend:ptr, divisor:ptr, reminder:ptr

    mov rax,[rdi]
    mov [rdx],rax
    mov rax,[rdi+8]
    mov [rdx+8],rax
    xor eax,eax
    mov [rdi],rax
    mov [rdi+8],rax

    or  rax,[rsi].l64
    or  rax,[rsi].h64
    .ifz
        mov [rdx],rax
        mov [rdx+8],rax
        .return rdi
    .endif

    .if [rsi].h64 == [rdx].h64
        mov rax,[rsi].l64
        cmp rax,[rdx].l64
    .endif
    .return .ifa            ; if divisor > dividend : reminder = dividend, quotient = 0
    .ifz                    ; if divisor == dividend :
        xor eax,eax         ; reminder = 0
        mov [rdx],rax
        mov [rdx+8],rax
        inc byte ptr [rdi]  ; quotient = 1
        .return rdi
    .endif

    mov rcx,[rsi].l64       ; divisor
    mov rsi,[rsi].h64
    mov r8d,-1
    .while 1
        inc r8d
        add rcx,rcx
        adc rsi,rsi
        .break .ifc
        .break .if rsi > [rdx].h64
        .continue .ifb
        .break .if rcx > [rdx].l64
        .continue .ifb
    .endw

    .while 1
        rcr rsi,1
        rcr rcx,1
        sub [rdx].l64,rcx
        sbb [rdx].h64,rsi
        cmc
        .ifnc
            .repeat
                add [rdi].l64,[rdi].l64
                adc [rdi].h64,[rdi].h64
                dec r8d
                .ifs
                    add [rdx].l64,rcx
                    adc [rdx].h64,rsi
                    .break(1)
                .endif
                shr rsi,1
                rcr rcx,1
                add [rdx].l64,rcx
                adc [rdx].h64,rsi
            .untilb
        .endif
        adc [rdi].l64,[rdi].l64
        adc [rdi].h64,[rdi].h64
        dec r8d
        .break .ifs
    .endw
    .return( rdi )

__divo endp

    end
