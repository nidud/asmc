; DIVQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp noauto

divq proc vectorcall uses rsi rdi rbx r12 r13 r14 A:real16, B:real16

    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    movq    rbx,xmm1
    movhlps xmm0,xmm1
    movq    rdi,xmm0

    shld    rsi,rdi,16
    shld    rdi,rbx,16
    shl     rbx,16
    mov     r8d,esi
    and     r8d,Q_EXPMASK
    neg     r8d
    rcr     rdi,1
    rcr     rbx,1
    shld    rsi,rdx,16
    shld    rdx,rax,16
    shl     rax,16
    mov     r8d,esi
    and     r8d,Q_EXPMASK
    neg     r8d
    rcr     rdx,1
    rcr     rax,1

    .repeat ; create frame -- no loop

        add     si,1            ; add 1 to exponent
        jc      er_NaN_A        ; quit if NaN
        jo      er_NaN_A        ; ...
        add     esi,0xFFFF      ; readjust low exponent and inc high word
        jc      er_NaN_B        ; quit if NaN
        jo      er_NaN_B        ; ...
        sub     esi,0x10000     ; readjust high exponent

        .if ( !rbx && !rdi )

            .if !( esi & 0x7FFF0000 )

                .if ( !rax && !rdx ) ; exit if A is 0

                    mov edi,esi
                    add di,di

                    .ifz

                        ; Invalid operation - return NaN

                        mov rdx,0x4000000000000000
                        mov esi,0x7FFF
                        .break
                    .endif
                .endif

                ; zero divide - return infinity

                or esi,0x7FFF
                jmp return_m0
            .endif
        .endif

        .if ( !rax && !rdx )
            add si,si
            .break .ifz
            rcr si,1        ; put back the sign
        .endif
        mov ecx,esi         ; exponent and sign of A into EDI
        rol ecx,16          ; shift to top
        sar ecx,16          ; duplicate sign
        sar esi,16          ; ...
        and ecx,0x80007FFF  ; isolate signs and exponent
        and esi,0x80007FFF  ; ...
        rol ecx,16          ; rotate signs to bottom
        rol esi,16          ; ...
        add cx,si           ; calc sign of result
        rol ecx,16          ; rotate signs to top
        rol esi,16          ; ...
        .if !cx             ; if A is a denormal
            .repeat         ; then normalize it
                dec cx      ; - decrement exponent
                add rax,rax ; - shift fraction left
                adc rdx,rdx
            .untilb         ; - until implied 1 bit is on
        .endif
        .if !si             ; if B is a denormal
            .repeat
                dec si
                add rbx,rbx
                adc rdi,rdi
            .untilb
        .endif
        sub cx,si           ; calculate exponent of result
        add cx,0x3FFF       ; add in removed bias
        .ifns               ; overflow ?
            .if cx >= 0x7FFF    ; quit if exponent is negative
                mov si,0x7FFF   ; - set infinity
                jmp return_si0  ; return infinity
            .endif
        .endif
        cmp cx,-65          ; if exponent is too small
        jl return_0         ; return underflow

        mov     r10,rbx
        mov     r11,rdi
        mov     r13,rax
        mov     r14,rdx
        xor     eax,eax
        xor     edx,edx
        xor     ebx,ebx
        or      rdi,r10
        jz      D4
        xor     r8d,r8d
        xor     r9d,r9d
        xor     edi,edi
        xor     r12d,r12d
        mov     esi,127
D0:
        inc     esi
        add     r10,r10
        adc     r11,r11
        jc      D1
        cmp     r11,r14
        jb      D0
        ja      D1
        cmp     r10,r13
        jbe     D0
D1:
        rcr     r11,1
        rcr     r10,1
        rcr     r9,1
        rcr     r8,1
        sub     rdi,r8
        sbb     r12,r9
        sbb     r13,r10
        sbb     r14,r11
        cmc
        jc      D3
D2:
        add     rax,rax
        adc     rdx,rdx
        adc     rbx,rbx
        dec     esi
        js      D4
        shr     r11,1
        rcr     r10,1
        rcr     r9,1
        rcr     r8,1
        add     rdi,r8
        adc     r12,r9
        adc     r13,r10
        adc     r14,r11
        jnc     D2
D3:
        adc     rax,rax
        adc     rdx,rdx
        adc     rbx,rbx
        dec     esi
        jns     D1
D4:
        mov     esi,ecx
        dec     si
        shr     bl,1    ; overflow bit..
        .ifc
            rcr rdx,1
            rcr rax,1
            inc esi
        .endif
        or si,si
        .ifng
            .ifz
                mov cl,1
            .else
                neg si
                mov ecx,esi
            .endif
            shrd rax,rdx,cl
            shr  rdx,cl
            xor esi,esi
        .endif
        add esi,esi
        rcr si,1
        .break

      er_NaN_A:             ; A is a NaN or infinity
        dec si
        add esi,0x10000
        mov r8,0x8000000000000000
        .ifnb
            .ifno
                .ifs
                    .if !rax && rdx == r8
                        xor esi,0x8000
                    .endif
                .endif
                .break
            .endif
        .endif
        sub esi,0x10000
        .if !rax && !rbx && rdx == r8 && rdi == r8
            sar edi,1
            or  esi,-1 ; -NaN
            .break
        .endif
        .if rdx == rdi
            cmp rax,rbx
        .endif
        jna return_B
        .break

      er_NaN_B:             ; B is a NaN or infinity
        sub esi,0x10000
        .if !rbx
            mov rdx,0x8000000000000000
            .if rdx == rdi
                mov r9d,esi
                shl r9d,16
                xor esi,r9d
                and esi,0x80000000
                sub edi,0x80000000
            .endif
        .endif

      return_B:
        mov rax,rbx
        mov rdx,rdi
        shr esi,16
        .break
      return_0:
        xor esi,esi
        jmp return_m0
      return_si0:
        add esi,esi
        rcr si,1
      return_m0:
        xor eax,eax
        xor edx,edx
    .until 1

    shl rax,1
    rcl rdx,1
    shrd rax,rdx,16
    shrd rdx,rsi,16
    movq xmm0,rax
    movq xmm1,rdx
    movlhps xmm0,xmm1   ; return result
    ret

divq endp

    end
