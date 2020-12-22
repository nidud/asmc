; __DIVO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    option win64:rsp noauto

u128 struct
l64  dq ?
h64  dq ?
u128 ends

    .code

    assume rcx:ptr u128
    assume rdx:ptr u128
    assume r8:ptr u128

__divo proc dividend:ptr, divisor:ptr, reminder:ptr

    mov rax,[rcx]
    mov [r8],rax
    mov rax,[rcx+8]
    mov [r8+8],rax
    xor eax,eax
    mov [rcx],rax
    mov [rcx+8],rax

    or  rax,[rdx].l64
    or  rax,[rdx].h64
    .ifz
        mov [r8],rax
        mov [r8+8],rax
        .return rcx
    .endif

    .if [rdx].h64 == [r8].h64
        mov rax,[rdx].l64
        cmp rax,[r8].l64
    .endif
    .return .ifa            ; if divisor > dividend : reminder = dividend, quotient = 0
    .ifz                    ; if divisor == dividend :
        xor eax,eax         ; reminder = 0
        mov [r8],rax
        mov [r8+8],rax
        inc byte ptr [rcx]  ; quotient = 1
        .return rcx
    .endif

    mov r10,[rdx].l64       ; divisor
    mov r11,[rdx].h64
    mov r9d,-1
    .while 1
        inc r9d
        add r10,r10
        adc r11,r11
        .break .ifc
        .break .if r11 > [r8].h64
        .continue .ifb
        .break .if r10 > [r8].l64
        .continue .ifb
    .endw

    .while 1
        rcr r11,1
        rcr r10,1
        sub [r8].l64,r10
        sbb [r8].h64,r11
        cmc
        .ifnc
            .repeat
                add [rcx].l64,[rcx].l64
                adc [rcx].h64,[rcx].h64
                dec r9d
                .ifs
                    add [r8].l64,r10
                    adc [r8].h64,r11
                    .break(1)
                .endif
                shr r11,1
                rcr r10,1
                add [r8].l64,r10
                adc [r8].h64,r11
            .untilb
        .endif
        adc [rcx].l64,[rcx].l64
        adc [rcx].h64,[rcx].h64
        dec r9d
        .break .ifs
    .endw
    mov rax,rcx
    ret

__divo endp

    end
