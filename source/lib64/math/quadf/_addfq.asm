include math.inc

option win64:rsp nosave noauto

.code

_subfq proc result:ptr, a:ptr, b:ptr

    mov r9d,0x80000000
    jmp _lk_add

_subfq endp

_addfq proc result:ptr, a:ptr, b:ptr

    xor r9d,r9d

_addfq endp

_lk_add proc private uses rsi rdi rbx result:ptr, a:ptr, b:ptr, sign:dword
    ;
    ; quad float [rcx] = quad float [rdx] +- quad float [r8]
    ;
    mov r10,rcx ; save dest.

    mov rbx,[r8]
    shl rbx,16
    mov rdi,[r8+6]
    mov si,[r8+14]
    and si,0x7FFF
    neg si
    mov si,[r8+14]
    rcr rdi,1
    rcr rbx,1
    shl esi,16
    mov r8,rdx
    mov rdx,[r8+6]
    mov rax,[r8]
    shl rax,16
    mov si,[r8+14]
    and si,0x7FFF
    neg si
    mov si,[r8+14]
    rcr rdx,1
    rcr rax,1

    .repeat             ; create frame -- no loop

        add si,1            ; add 1 to exponent
        jc  er_NaN_A        ; quit if NaN
        jo  er_NaN_A        ; ...
        add esi,0xFFFF      ; readjust low exponent and inc high word
        jc  er_NaN_B        ; quit if NaN
        jo  er_NaN_B        ; ...
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
                .break
            .endif
            rcr si,1        ; put back the sign
        .endif
        .if !rbx && !rdi    ; B is 0 ?
            .break .if !(esi & 0x7FFF0000)
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
                shl esi,1       ; get sign
                rcr si,1        ; merge with exponent
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
            xor esi,0x80000000 ; - flip sign
        .endif

        xor r11,r11         ; get a zero for sticky bits
        .if cl              ; if shifting required
            .if cl >= 64        ; if shift count >= 64
                .if rax         ; check low order qword for 1 bits
                    inc r11     ; r11=1 if RAX non zero
                .endif
                .if cl == 128   ; if shift count is 128
                    or  r11,rdx ; get rest of sticky bits from high part
                    xor rdx,rdx ; zero high part
                .endif
                mov rax,rdx     ; shift right 64
                xor rdx,rdx
            .endif
            xor  r8,r8
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

        .if rax || rdx || ch
            .if !si
                add esi,esi
                rcr si,1
                .break
            .endif
            ;
            ; if top bits are 0
            ;
            .if !ch
                rol r11,1   ; set carry from last sticky bit
                rol r11,1
                .repeat
                    dec si  ; decrement exponent
                    .ifz
                        add esi,esi
                        rcr si,1
                        .break(1)
                    .endif
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
            bt  eax,15
            .ifc                ; if guard bit is on
                shl r11,1       ; get top sticky bit
                .ifz            ; if no more sticky bits
                    ror rax,1   ; set carry with bottom bit of DX
                    rol rax,1
                .endif
                adc rax,0       ; round up fraction if required
                adc rdx,0
                .ifc            ; if we got a carry
                    rcr rdx,1   ; shift fraction right 1
                    rcr rax,1
                    inc si      ; increment exponent
                    cmp si,0x7FFF
                    je  overflow
                .endif
            .endif
        .else
            xor esi,esi
        .endif
        add esi,esi
        rcr si,1
        .break

      ; A is a NaN or infinity

      er_NaN_A:

        dec si
        add esi,0x10000
        .ifnc
            .break .ifno
        .endif
        sub esi,0x10000
        mov r11,0x8000000000000000
        .if !rax && !rbx
            .if rdx == rdi && rdx == r11
                shr rdx,2
                or  si,-1 ; -NaN - FFFF40 ?
                .break
            .endif
        .endif
        .if rdi == rdx
            cmp rbx,rax
        .endif
        jna return_B
        .break

      ; B is a NaN or infinity

      er_NaN_B:

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
        .break

      overflow:
        mov si,0x7FFF
        xor rax,rax
        xor rdx,rdx

    .until 1

    shl rax,1           ; shift bits back
    rcl rdx,1
    shr rax,16          ; 16 low bits
    mov [r10],rax
    mov [r10+6],rdx
    mov [r10+14],si     ; exponent and sign
    mov rax,r10         ; return result
    ret

_lk_add endp

    end
