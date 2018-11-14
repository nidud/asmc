; QUADADD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

quadsub proc a:ptr, b:ptr

    mov r9d,0x80000000
    jmp entry

quadsub endp

quadadd proc a:ptr, b:ptr

    xor r9d,r9d

quadadd endp

entry:

    mov r10,rcx
    push rsi
    push rdi
    push rbx

    mov rbx,[rdx]           ; rdi:rbx - 128 bit value (b) of 112 bit mantissa
    shl rbx,16
    mov rdi,[rdx+6]
    mov si,[rdx+14]
    and si,0x7FFF
    neg si
    mov si,[rdx+14]
    rcr rdi,1               ; extend to 113 bit
    rcr rbx,1               ; bit 112 set if not zero
    shl esi,16
    mov rdx,[rcx+6]         ; rdx:rax - 128 bit value (a) of 112 bit mantissa
    mov rax,[rcx]
    shl rax,16
    mov si,[rcx+14]
    and si,0x7FFF
    neg si
    mov si,[rcx+14]
    rcr rdx,1
    rcr rax,1

    .repeat ; create frame

        add si,1            ; add 1 to exponent
        jc A_is_a_NaN_or_infinity
        jo A_is_a_NaN_or_infinity
        add esi,0xFFFF      ; readjust low exponent and inc high word
        jc B_is_a_NaN_or_infinity
        jo B_is_a_NaN_or_infinity

        sub esi,0x10000     ; readjust high exponent
        xor esi,r9d         ; flip sign if subtract

        .if !rax && !rdx    ; A is 0 ?
            shl si,1        ; place sign in carry
            .ifz
                shr esi,16
                mov rax,rbx     ; return B
                mov rdx,rdi
                shl esi,1
                or  rbx,rdi     ; check for 0
                or  bx,si
                .ifnz           ; if not zero
                    shr esi,1   ; -> restore sign bit
                .endif
                jmp done
            .endif
            rcr si,1        ; put back the sign
        .endif              ; B is 0 ?
        .if !rbx && !rdi && !(esi & 0x7FFF0000)
            jmp done
        .endif

        mov ecx,esi         ; exponent and sign of A into ECX
        rol esi,16          ; shift to top
        sar esi,16          ; duplicate sign
        sar ecx,16          ; ...
        and esi,0x80007FFF  ; isolate signs and exponent
        and ecx,0x80007FFF  ; ...
        mov r9d,ecx         ; assume A < B
        rol esi,16          ; rotate signs to bottom
        rol ecx,16          ; ...
        add cx,si           ; calc sign of result
        rol esi,16          ; rotate signs to top
        rol ecx,16          ; ...
        sub cx,si           ; calculate difference in exponents
        .ifnz               ; if different
            .ifc                ; if B < A
                mov r9d,esi     ; get larger exponent for result
                neg cx          ; negate the shift count
                xchg rbx,rax    ; flip operands
                xchg rdi,rdx
            .endif
            .if cx > 128        ; if shift count too big
                mov esi,r9d
                mov rax,rbx     ; get result
                mov rdx,rdi
                .break
            .endif
        .endif

        mov esi,r9d
        mov ch,0            ; zero extend B
        or  ecx,ecx         ; get bit 0 of sign word - value is 0 if
                            ; both operands have same sign, 1 if not
        .ifs                ; if signs are different
            mov ch,-1       ; - set high part to ones
            neg rdi         ; - negate the fraction of B
            neg rbx
            sbb rdi,0
            xor esi,0x80000000  ; - flip sign
        .endif

        xor r11d,r11d           ; get a zero for sticky bits
        .if cl                  ; if shifting required
            .if cl >= 64        ; if shift count >= 64
                .if rax         ; check low order qword for 1 bits
                    inc r11b    ; r11=1 if RAX non zero
                .endif
                .if cl == 128   ; if shift count is 128
                    or  r11,rdx ; get rest of sticky bits from high part
                    xor rdx,rdx ; zero high part
                .endif
                mov rax,rdx     ; shift right 64
                xor rdx,rdx
            .endif
            xor  r8d,r8d
            shrd r8,rax,cl      ; get the extra sticky bits
            or   r11,r8         ; save them
            shrd rax,rdx,cl     ; align the fractions
            shr  rdx,cl
        .endif

        add rax,rbx
        adc rdx,rdi
        adc ch,0
        .ifs
            .if cl == 128
                xor r8b,r8b
                mov r9,0x7FFFFFFFFFFFFFFF
                .if r11 & r9
                    inc r8b     ; make single sticky bit
                .endif
                shr r8b,1
                adc rax,0       ; round up fraction if required
                adc rdx,0
            .endif
            neg rdx
            neg rax
            sbb rdx,0
            mov ch,0
            xor esi,0x80000000
        .endif

        .if !rax && !rdx && !ch
            mov rsi,rax
        .endif
        .break .if !si

        ; if top bits are 0

        .if !ch
            rol r11,1       ; set carry from last sticky bit
            ror r11,1
            .repeat
                dec si      ; decrement exponent
                .break(1) .ifz
                adc rax,rax ; shift fraction left one bit
                adc rdx,rdx
            .untilb         ; until carry
        .endif

        inc si
        cmp si,0x7FFF
        je  overflow

        stc                 ; set carry
        rcr rdx,1           ; shift fraction right 1
        rcr rax,1
        .if eax & 0x4000    ; if guard bit is on
            add r11,r11     ; get top sticky bit
            .ifz            ; if no more sticky bits
                bt  eax,14  ; set carry with bit 14 of AX
            .endif
            .ifc            ; round up fraction if required
                add rax,0x4000
                adc rdx,0
                .ifc            ; if we got a carry
                    rcr rdx,1   ; shift fraction right 1
                    rcr rax,1
                    inc si      ; increment exponent
                    cmp si,0x7FFF
                    je  overflow
                .endif
            .endif
        .endif
    .until 1

    add esi,esi
    rcr si,1

done:

    shl rax,1           ; shift bits back
    rcl rdx,1
    shr rax,16          ; 16 low bits
    mov [r10],rax
    mov [r10+6],rdx
    mov [r10+14],si     ; exponent and sign
    mov rax,r10         ; return result

    pop rbx
ifndef _LINUX
    pop rdi
    pop rsi
endif
    ret

overflow:
    mov si,0x7FFF
    xor rax,rax
    xor rdx,rdx
    jmp done

A_is_a_NaN_or_infinity:
    dec si
    add esi,0x10000
    .if CARRY? || OVERFLOW?
        sub esi,0x10000
        mov r11,0x8000000000000000
        .if !rax && !rbx && rdx == rdi && rdx == r11
            shr rdx,2
            or  si,-1 ; -NaN - FFFF40 ?
            jmp done
        .endif
        .if rdi == rdx
            cmp rbx,rax
        .endif
        jna return_B
    .endif
    jmp done

B_is_a_NaN_or_infinity:
    sub esi,0x10000
    .if !rbx
        mov rdx,0x8000000000000000
        .if rdx == rdi
            xor esi,r9d
        .endif
    .endif
return_B:
    mov rdx,rdi
    mov rax,rbx
    shr esi,16
    jmp done

    end
