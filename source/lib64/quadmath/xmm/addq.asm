; ADDQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto


addq proc vectorcall A:real16, B:real16

    xor r8d,r8d
    jmp _lk_addq

addq endp


    align 16

subq proc vectorcall A:real16, B:real16

    mov r8d,0x80000000

subq endp


_lk_addq proc private uses rsi rdi rbx A:real16, B:real16, negate:uint_t

    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    movq    rbx,xmm1
    movhlps xmm0,xmm1
    movq    rdi,xmm0

    shld    rsi,rdi,16
    shld    rdi,rbx,16
    shl     rbx,16
    mov     r9d,esi
    and     r9d,Q_EXPMASK
    neg     r9d
    rcr     rdi,1
    rcr     rbx,1

    shld    rsi,rdx,16
    shld    rdx,rax,16
    shl     rax,16
    mov     r9d,esi
    and     r9d,Q_EXPMASK
    neg     r9d
    rcr     rdx,1
    rcr     rax,1

    jmp     entry

    .switch jmp rcx

      .case 0
        mov rax,rbx
        mov rdx,rdi
        shr esi,16
        .endc

      .case 1
        mov esi,0x7FFF
        xor eax,eax
        xor edx,edx
        .endc

      .case 2                   ; A is a NaN or infinity

        dec si
        add esi,0x10000
        .ifnc
            .endc .ifno
        .endif
        sub esi,0x10000

        mov rcx,0x8000000000000000
        .if ( !rax && !rbx && rdx == rcx && rdi == rcx )

            sar edi,1
            or  esi,-1  ; -NaN
            .endc
        .endif

        .if rdx == rdi
            cmp rax,rbx
        .endif
        .gotosw(0) .ifna
        .endc

      .case 3                   ; B is a NaN or infinity

        sub esi,0x10000
        mov rcx,0x8000000000000000

        .if ( rbx == 0 && rdi == rcx )

            mov eax,esi
            shl eax,16
            xor esi,eax
            and esi,0x80000000
            shl rdi,32
            shr rdi,32
        .endif
        .gotosw(0)

      .case 4                   ; A is 0
        shl si,1                ; place sign in carry
        .ifz
            shr esi,16          ; return B
            mov rax,rbx
            mov rdx,rdi
            shl esi,1
            .if ( rax || rdx )  ; if not zero
                shr esi,1       ; -> restore sign bit
            .endif
            .endc
        .endif
        rcr si,1                ; put back the sign
        .gotosw(6)

      .case <entry> 5

        add si,1                ; add 1 to exponent
        .gotosw(2) .ifc         ; quit if NaN
        .gotosw(2) .ifo
        add esi,0xFFFF          ; readjust low exponent and inc high word
        .gotosw(3) .ifc         ; quit if NaN
        .gotosw(3) .ifo
        sub esi,0x10000         ; readjust high exponent
        xor esi,r8d             ; flip sign if subtract

        .gotosw(4) .if ( !rax && !rdx )

      .case 6
                                ; quit if B is 0
        .endc .if ( !( esi & 0x7FFF0000 ) && !rbx && !rdi )

        mov ecx,esi             ; exponent and sign of A into EDI
        rol esi,16              ; shift to top
        sar esi,16              ; duplicate sign
        sar ecx,16              ; ...
        and esi,0x80007FFF      ; isolate signs and exponent
        and ecx,0x80007FFF      ; ...
        mov r9d,ecx             ; assume A < B
        rol esi,16              ; rotate signs to bottom
        rol ecx,16              ; ...
        add cx,si               ; calc sign of result
        rol esi,16              ; rotate signs to top
        rol ecx,16              ; ...
        sub cx,si               ; calculate difference in exponents

        .ifnz                   ; if different
            .ifb                ; if B < A
                mov  r9d,esi    ; get larger exponent for result
                neg  cx         ; negate the shift count
                xchg rax,rbx    ; flip operands
                xchg rdx,rdi
            .endif
            .if cx > 128        ; if shift count too big
                mov esi,r9d
                shl esi,1       ; get sign
                rcr si,1        ; merge with exponent
                mov rax,rbx
                mov rdx,rdi
                .endc
            .endif
        .endif
        mov esi,r9d
        mov ch,0                ; zero extend B
        or  ecx,ecx             ; get bit 0 of sign word - value is 0 if
                                ; both operands have same sign, 1 if not
        .ifs                    ; if signs are different
            mov ch,-1           ; - set high part to ones
            neg rdi
            neg rbx
            sbb rdi,0
            xor esi,0x80000000  ; - flip sign
        .endif

        .repeat

            xor r8d,r8d         ; get a zero for sticky bits
            .if cl              ; if shifting required
                .if cl >= 64    ; if shift count >= 64
                    .if rax     ; check low order qword for 1 bits
                        inc r8d ; r11=1 if RAX non zero
                    .endif
                    .if cl == 128   ; if shift count is 128
                        shr rdx,32  ; get rest of sticky bits from high part
                        or  r8d,edx
                        xor edx,edx ; zero high part
                    .endif
                    mov rax,rdx     ; shift right 64
                    xor edx,edx
                .endif
                xor  r9d,r9d
                mov  r10d,eax
                shr  r10d,15
                shrd r9d,r10d,cl    ; get the extra sticky bits
                or   r8d,r9d        ; save them
                shrd rax,rdx,cl     ; align the fractions
                shr  rdx,cl
            .endif
            add rax,rbx
            adc rdx,rdi
            adc ch,0
            .ifs
                .if cl == 128
                    .if r8d & 0x7FFFFFFF
                        stc
                    .else
                        clc
                    .endif
                    adc rax,0       ; round up fraction if required
                    adc rdx,0
                .endif
                neg rdx
                neg rax
                sbb rdx,0
                mov ch,0
                xor esi,0x80000000
            .endif
            mov r9d,ecx
            and r9d,0xFF00
            or  r9,rax
            or  r9,rdx
            .ifz
                xor esi,esi
            .endif
            .break .if !si
            ;
            ; if top bits are 0
            ;
            test ch,ch
            mov ecx,r8d
            .ifz
                rol ecx,1       ; set carry from last sticky bit
                rol ecx,1
                .repeat
                    dec si      ; decrement exponent
                    .break(1) .ifz
                    adc rax,rax
                    adc rdx,rdx
                .untilb         ; until carry
            .endif
            inc si
            .gotosw(1) .if si == Q_EXPMASK
            stc                 ; set carry
            rcr rdx,1           ; shift fraction right 1
            rcr rax,1
            add ecx,ecx         ; get top sticky bit
            .ifc                ; set carry with bit 14 of AX
                adc rax,0x4000  ; round up fraction if required
                adc rdx,0
                .ifc            ; if we got a carry
                    rcr rdx,1   ; shift fraction right 1
                    rcr rax,1
                    inc si      ; increment exponent
                    .gotosw(1) .if si == Q_EXPMASK
                .endif
            .endif

        .until 1

        add esi,esi
        rcr si,1

    .endsw

    shl rax,1
    rcl rdx,1
    shrd rax,rdx,16
    shrd rdx,rsi,16
    movq xmm0,rax
    movq xmm1,rdx
    movlhps xmm0,xmm1
    ret

_lk_addq endp

    end
