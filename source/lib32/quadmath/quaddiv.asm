include quadmath.inc

    .code

quaddiv proc uses esi edi ebx a:ptr, b:ptr

  local dividend:U256, divisor:U256, reminder:U256

    xor eax,eax
    lea edi,divisor
    mov ecx,2*8
    rep stosd

    mov edx,b
    mov ax,[edx]
    shl eax,16
    mov edi,[edx+2]
    mov ecx,[edx+6]
    mov ebx,[edx+10]
    mov si,[edx+14]     ; shift out bits 0..112
    and esi,Q_EXPMASK   ; if not zero
    neg esi             ; - set high bit
    mov si,[edx+14]
    rcr ebx,1
    rcr ecx,1
    rcr edi,1
    rcr eax,1
    mov divisor.m32[0],eax
    mov divisor.m32[4],edi
    mov divisor.m32[8],ecx
    mov divisor.m32[12],ebx
    shl esi,16

    mov edi,a
    mov ax,[edi]
    shl eax,16
    mov edx,[edi+2]
    mov ebx,[edi+6]
    mov ecx,[edi+10]
    mov si,[edi+14]
    and si,Q_EXPMASK
    neg si
    mov si,[edi+14]
    rcr ecx,1           ; dividend to regs..
    rcr ebx,1
    rcr edx,1
    rcr eax,1

    .repeat             ; create frame -- no loop

        add si,1            ; add 1 to exponent
        jc  er_NaN_A        ; quit if NaN
        jo  er_NaN_A        ; ...
        add esi,0xFFFF      ; readjust low exponent and inc high word
        jc  er_NaN_B        ; quit if NaN
        jo  er_NaN_B        ; ...
        sub esi,0x10000     ; readjust high exponent

        mov edi,divisor.m32[0]      ; B is 0 ?
        or  edi,divisor.m32[4]
        or  edi,divisor.m32[8]
        or  edi,divisor.m32[12]
        .ifz
            .if !(esi & 0x7FFF0000)

                mov edi,eax ; A is 0 ?
                or  edi,edx
                or  edi,ebx
                or  edi,ecx
                .ifz        ; exit if A is 0
                    mov edi,esi
                    add di,di
                    .ifz
                        ;
                        ; Invalid operation - return NaN
                        ;
                        mov ecx,0x40000000
                        mov esi,0x7FFF
                        .break
                    .endif
                .endif
                ;
                ; zero divide - return infinity
                ;
                or esi,0x7FFF
                jmp return_m0
            .endif
        .endif

        mov edi,eax         ; A is 0 ?
        or  edi,edx
        or  edi,ebx
        or  edi,ecx
        .ifz
            add si,si
            .break .ifz
            rcr si,1        ; put back the sign
        .endif

        mov edi,esi         ; exponent and sign of A into EDI
        rol edi,16          ; shift to top
        sar edi,16          ; duplicate sign
        sar esi,16          ; ...
        and edi,0x80007FFF  ; isolate signs and exponent
        and esi,0x80007FFF  ; ...
        rol edi,16          ; rotate signs to bottom
        rol esi,16          ; ...
        add di,si           ; calc sign of result
        rol edi,16          ; rotate signs to top
        rol esi,16          ; ...
        .if !di             ; if A is a denormal
            .repeat         ; then normalize it
                dec di      ; - decrement exponent
                shl eax,1   ; - shift fraction left
                rcl edx,1
                rcl ebx,1
                rcl ecx,1
            .until carry?   ; - until implied 1 bit is on
        .endif
        .if !si             ; if B is a denormal
            push eax        ; ...
            .repeat
                dec si
                mov eax,divisor.m32[0]
                add divisor.m32[0],eax
                mov eax,divisor.m32[4]
                adc divisor.m32[4],eax
                mov eax,divisor.m32[8]
                adc divisor.m32[0],eax
                mov eax,divisor.m32[12]
                adc divisor.m32[12],eax
            .until carry?
            pop eax
        .endif
        sub di,si               ; calculate exponent of result
        add di,0x3FFF           ; add in removed bias
        .ifns                   ; overflow ?
            .if di >= 0x7FFF    ; quit if exponent is negative
                mov si,0x7FFF   ; - set infinity
                jmp return_si0  ; return infinity
            .endif
        .endif
        cmp di,-65              ; if exponent is too small
        jl  return_0            ; return underflow

        mov dividend.m32[16],eax    ; save dividend
        mov dividend.m32[20],edx
        mov dividend.m32[24],ebx
        mov dividend.m32[28],ecx
        _udiv256(&dividend, &divisor, &reminder)
        mov esi,edi
        mov eax,dividend.m32[0]     ; load quotient
        mov edx,dividend.m32[4]
        mov ebx,dividend.m32[8]
        mov edi,dividend.m32[12]
        dec si
        shr dividend.m8[16],1       ; overflow bit..
        .ifc
            rcr edi,1
            rcr ebx,1
            rcr edx,1
            rcr eax,1
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
            shrd eax,edx,cl
            shrd edx,ebx,cl
            shrd ebx,edi,cl
            shr edi,cl
            xor esi,esi
        .endif
        mov ecx,edi
        add esi,esi
        rcr si,1
    .until 1

done:

    mov edi,a
    shl eax,1           ; shift bits back
    rcl edx,1
    rcl ebx,1
    rcl ecx,1           ; shift high bit out..
    shr eax,16          ; 16 low bits
    mov [edi],ax
    mov [edi+2],edx
    mov [edi+6],ebx
    mov [edi+10],ecx
    mov [edi+14],si     ; exponent and sign
    mov eax,edi         ; return result
    ret

    overflow:
        mov esi,0x7FFF
    return_si0:
        add esi,esi
        rcr si,1
        jmp return_m0
    return_0:
        xor esi,esi
    return_m0:
        xor eax,eax
        xor edx,edx
        xor ebx,ebx
        xor ecx,ecx
        jmp done

    er_NaN_A: ; A is a NaN or infinity
        dec si
        add esi,0x10000
        .ifnb
            .ifno
                .ifs
                    mov edi,eax
                    or  edi,edx
                    or  edi,ebx
                    .ifz
                        .if ecx == 0x80000000
                            xor esi,0x8000
                        .endif
                    .endif
                .endif
                jmp done
            .endif
        .endif
        sub esi,0x10000
        mov edi,eax
        or  edi,edx
        or  edi,ebx
        .ifz
            mov edi,divisor.m32[0]
            or  edi,divisor.m32[4]
            or  edi,divisor.m32[8]
            .ifz
                .if ecx == 0x80000000 && ecx == divisor.m32[12]
                    sar ecx,1
                    or  esi,-1 ; -NaN
                    jmp done
                .endif
            .endif
        .endif
        .if ecx == divisor.m32[12]
            .if ebx == divisor.m32[8]
                .if edx == divisor.m32[4]
                    cmp eax,divisor.m32[0]
                .endif
            .endif
        .endif
        jna return_B
        jmp done

    er_NaN_B: ; B is a NaN or infinity
        sub esi,0x10000
        mov edi,divisor.m32[0]
        or  edi,divisor.m32[4]
        or  edi,divisor.m32[8]
        .ifz
            mov ecx,0x80000000
            .if ecx == divisor.m32[12]
                mov eax,esi
                shl eax,16
                xor esi,eax
                and esi,ecx
                sub divisor.m32[12],ecx
            .endif
        .endif

    return_B:
        mov ecx,divisor.m32[12]
        mov ebx,divisor.m32[8]
        mov edx,divisor.m32[4]
        mov eax,divisor.m32[0]
        shr esi,16
        jmp done

quaddiv endp

    end
