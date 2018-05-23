;
; _udiv256() - Divide
;
; Unsigned binary division of dividend by source.
; Note: The quotient is stored in dividend.
;
include quadmath.inc

.code

ifdef _LINUX
_udiv256 proc uses rbx dividend:PU256, divisor:PU256, reminder:PU256
    mov r10,dividend
    mov r11,reminder
    mov rbx,divisor
else
option cstack:on
option win64:rsp nosave noauto
_udiv256 proc uses rsi rdi rbx dividend:PU256, divisor:PU256, reminder:PU256
    mov r10,rcx ; R10: quotient
    mov r11,r8  ; R11: reminder
    mov rbx,rdx ; RBX: divisor
endif

    mov rsi,r10 ; dividend --> reminder
    mov rdi,r11
    mov ecx,4
    rep movsq

    xor eax,eax ; quotient (dividend) --> 0
    mov rdi,r10
    mov ecx,4
    rep stosq

    .repeat

        or rax,[rbx] ; divisor zero ?
        or rax,[rbx+8]
        or rax,[rbx+16]
        or rax,[rbx+24]
        .ifz
            mov rdi,r11
            mov ecx,4
            rep stosq
            .break
        .endif

        mov rax,[rbx+24]
        .if rax == [r11+24]
            mov rax,[rbx+16]
            .if rax == [r11+16]
                mov rax,[rbx+8]
                .if rax == [r11+8]
                    mov rax,[rbx]
                    cmp rax,[r11]
                .endif
            .endif
        .endif
        .ifa
            ;
            ; divisor > dividend : reminder = dividend, quotient = 0
            ;
            .break
        .else
            .ifz
                ;
                ; divisor == dividend : reminder = 0, quotient = 1
                ;
                mov rdi,r11
                mov ecx,4
                rep stosq
                inc byte ptr [r10]
                .break
            .endif
        .endif

        mov rdi,rbx
        mov rcx,[rdi+24]
        mov rbx,[rdi+16]
        mov rdx,[rdi+8]
        mov rax,[rdi]
        xor r8d,r8d

        .while 1
            add rax,rax
            adc rdx,rdx
            adc rbx,rbx
            adc rcx,rcx
            .break .ifc
            .if rcx == [r11+24]
                .if rbx == [r11+16]
                    .if rdx == [r11+8]
                        cmp rax,[r11]
                    .endif
                .endif
            .endif
            .break .ifa
            inc r8d
        .endw

        .while 1
            rcr rcx,1
            rcr rbx,1
            rcr rdx,1
            rcr rax,1
            sub [r11],rax
            sbb [r11+8],rdx
            sbb [r11+16],rbx
            sbb [r11+24],rcx
            cmc
            .ifnc
                .repeat
                    mov r9,[r10]
                    add [r10],r9
                    mov r9,[r10+8]
                    adc [r10+8],r9
                    mov r9,[r10+16]
                    adc [r10+16],r9
                    mov r9,[r10+24]
                    adc [r10+24],r9
                    dec r8d
                    .ifs
                        add [r11],rax
                        adc [r11+8],rdx
                        adc [r11+16],rbx
                        adc [r11+24],rcx
                        .break(1)
                    .endif
                    shr rcx,1
                    rcr rbx,1
                    rcr rdx,1
                    rcr rax,1
                    add [r11],rax
                    adc [r11+8],rdx
                    adc [r11+16],rbx
                    adc [r11+24],rcx
                .untilb
            .endif
            mov r9,[r10]
            adc [r10],r9
            mov r9,[r10+8]
            adc [r10+8],r9
            mov r9,[r10+16]
            adc [r10+16],r9
            mov r9,[r10+24]
            adc [r10+24],r9
            dec r8d
            .break .ifs
        .endw
    .until 1
    ret

_udiv256 endp

    end
