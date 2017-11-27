; _divnd() - Divide
;
; Unsigned binary division of dividend by source.
; Note: The quotient is stored in dividend.
;
include intn.inc
include malloc.inc

option cstack:on
option win64:nosave noauto

.code

_divnd proc uses rsi rdi rbx r12 dividend:ptr, divisor:ptr, reminder:ptr, n:dword

    mov r10,rcx ; R10: quotient
    mov r11,r8  ; R11: reminder
    mov rbx,rdx ; RBX: divisor

    mov rsi,rcx ; dividend --> reminder
    mov rdi,r8
    mov ecx,r9d
    rep movsq

    xor eax,eax ; quotient (dividend) --> 0
    mov rdi,r10
    mov ecx,r9d
    rep stosq

    .repeat

        mov rcx,rbx
        mov rdx,r10
        mov r8d,r9d
        call _cmpnd ; divisor zero ?
        .ifz
            mov rdi,r11
            mov ecx,r9d
            rep stosq
            .break
        .endif

        mov rcx,rbx
        mov rdx,r11
        mov r8d,r9d
        call _cmpnd
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
                mov ecx,r9d
                rep stosq
                inc byte ptr [r10]
                .break
            .endif
        .endif
        ;
        ; Allocate stack space for divisor
        ;
        lea rax,[rsp-_GRANULARITY]
        mov ecx,r9d
        shl ecx,3
        .while ecx > _PAGESIZE_
            sub rax,_PAGESIZE_
            test [rax],rax
            sub ecx,_PAGESIZE_
        .endw
        sub rax,rcx
        and rax,-(_GRANULARITY)
        test [rax],rax
        mov rsp,rax
        mov rdi,rax
        mov rsi,rbx
        mov rbx,rax
        mov ecx,r9d
        rep movsq
        xor r12,r12

        .while 1
            mov rsi,rbx
            mov ecx,r9d
            xor edx,edx
            .repeat
                mov rax,[rsi]
                shr edx,1
                adc [rsi],rax
                sbb edx,edx
                add rsi,8
            .untilcxz
            shr edx,1
            jc  @F
            mov rcx,rbx
            mov rdx,r11
            mov r8d,r9d
            call _cmpnd
            ja  @F
            inc r12
        .endw

        .while 1
            mov rdi,r10
            mov ecx,r9d
            sbb edx,edx
            .repeat
                mov rax,[rdi]
                shr edx,1
                adc [rdi],rax
                sbb edx,edx
                add rdi,8
            .untilcxz
            dec r12
            .break .ifs
         @@:
            mov rsi,rbx
            mov ecx,r9d
            sbb edx,edx
            .repeat
                mov rax,[rsi+rcx*8-8]
                shr edx,1
                rcr rax,1
                mov [rsi+rcx*8-8],rax
                sbb edx,edx
            .untilcxz
            mov rdi,r11
            mov ecx,r9d
            xor edx,edx
            .repeat
                mov rax,[rsi]
                shr edx,1
                sbb [rdi],rax
                sbb edx,edx
                add rsi,8
                add rdi,8
            .untilcxz
            shr edx,1
            cmc
            .continue .if CARRY?
            .repeat
                mov rdi,r10
                mov ecx,r9d
                xor edx,edx
                .repeat
                    mov rax,[rdi]
                    shr edx,1
                    adc [rdi],rax
                    sbb edx,edx
                    add rdi,8
                .untilcxz
                dec r12
                mov rdi,r11
                mov rsi,rbx
                mov ecx,r9d
                .ifs
                    xor edx,edx
                    .repeat
                        mov rax,[rsi]
                        shr edx,1
                        adc [rdi],rax
                        sbb edx,edx
                        add rsi,8
                        add rdi,8
                    .untilcxz
                    .break(1)
                .endif
                xor edx,edx
                .repeat
                    mov rax,[rsi+rcx*8-8]
                    shr edx,1
                    rcr rax,1
                    sbb edx,edx
                    mov [rsi+rcx*8-8],rax
                .untilcxz
                xor edx,edx
                mov ecx,r9d
                .repeat
                    mov rax,[rsi]
                    shr edx,1
                    adc [rdi],rax
                    sbb edx,edx
                    add rsi,8
                    add rdi,8
                .untilcxz
                shr edx,1
            .until CARRY?
        .endw
    .until 1
    ret

_divnd endp

    end
