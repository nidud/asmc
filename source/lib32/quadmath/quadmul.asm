; QUADMUL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

quadmul proc uses esi edi ebx a:ptr, b:ptr

  local multiplier:U128, multiplicand:U128, highproduct:U128

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
    mov multiplicand.m32[0],eax
    mov multiplicand.m32[4],edi
    mov multiplicand.m32[8],ecx
    mov multiplicand.m32[12],ebx
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
    rcr ecx,1
    rcr ebx,1
    rcr edx,1
    rcr eax,1

    .repeat

        add si,1            ; add 1 to exponent
        jc  er_NaN_A        ; quit if NaN
        jo  er_NaN_A        ; ...
        add esi,0xFFFF      ; readjust low exponent and inc high word
        jc  er_NaN_B        ; quit if NaN
        jo  er_NaN_B        ; ...
        sub esi,0x10000     ; readjust high exponent
        mov edi,eax         ; A is 0 ?
        or  edi,edx
        or  edi,ebx
        or  edi,ecx
        .ifz                ; exit if A is 0
            add si,si       ; place sign in carry
            .break .ifz     ; return 0
            rcr si,1        ; restore sign of A
        .endif
        mov edi,multiplicand.m32[0] ; exit if B is 0
        or  edi,multiplicand.m32[4]
        or  edi,multiplicand.m32[8]
        or  edi,multiplicand.m32[12]
        .ifz
            .if !(esi & 0x7FFF0000)
                jmp return_0
            .endif
        .endif
        mov edi,esi         ; exponent and sign of A into EDI
        rol edi,16          ; shift to top
        sar edi,16          ; duplicate sign
        sar esi,16          ; ...
        and edi,0x80007FFF  ; isolate signs and exponent
        and esi,0x80007FFF  ; ...
        add esi,edi         ; determine exponent of result and sign
        sub si,0x3FFE       ; remove extra bias
        .ifnc               ; exponent negative ?
            cmp si,0x7FFF   ; overflow ?
            ja  overflow
        .endif
        .ifs si < -64       ; exponent too small ?
            dec si
            jmp return_si0
        .endif

        mov multiplier.m32[0],eax
        mov multiplier.m32[4],edx
        mov multiplier.m32[8],ebx
        mov multiplier.m32[12],ecx

        _mul256(&multiplier, &multiplicand, &highproduct)  ; A * B

        mov edi,multiplier.m32[12]
        mov eax,highproduct.m32[0]
        mov edx,highproduct.m32[4]
        mov ebx,highproduct.m32[8]
        mov ecx,highproduct.m32[12]
        .if !(ecx & 0x80000000) ; if not normalized
            shl edi,1
            rcl eax,1
            rcl edx,1
            rcl ebx,1
            rcl ecx,1
            dec si
        .endif
        shl edi,1
        .ifb
            .ifz
                .if multiplier.m32[8]
                    stc
                .else
                    bt eax,0
                .endif
            .endif
            adc eax,0
            adc edx,0
            adc ebx,0
            adc ecx,0
            .ifb
                rcr ecx,1
                rcr ebx,1
                rcr edx,1
                rcr eax,1
                inc si
                cmp si,0x7FFF
                jz  overflow
            .endif
        .endif
        or si,si
        .ifng
            .ifz
                and si,0xFF00
                inc si
            .else
                neg si
            .endif
            movzx edi,si
            xchg ecx,edi
            shrd eax,edx,cl
            shrd edx,ebx,cl
            shrd ebx,edi,cl
            shr edi,cl
            mov ecx,edi
            xor si,si
        .endif
        add esi,esi
        rcr si,1
    .until 1

done:

    mov edi,eax
    mov eax,a
    shl edi,1
    rcl edx,1
    rcl ebx,1
    rcl ecx,1
    shr edi,16
    mov [eax],di
    mov [eax+2],edx
    mov [eax+6],ebx
    mov [eax+10],ecx
    mov [eax+14],si
    ret

    er_NaN_A: ; A is a NaN or infinity

        mov edi,eax
        or  edi,edx
        or  edi,ebx
        .ifz
            .if ecx == 0x80000000
                mov edi,multiplicand.m32[0]
                or  edi,multiplicand.m32[4]
                or  edi,multiplicand.m32[8]
                or  edi,multiplicand.m32[12]
                .ifz
                    mov esi,-1 ; -NaN
                    jmp done
                .endif
            .endif
        .endif
        dec si
        add esi,0x10000
        .ifnb
            .ifno
                mov edi,eax
                or  edi,edx
                or  edi,ebx
                .ifz
                    .if ecx == 0x80000000
                        or esi,esi
                        .ifs
                            xor esi,0x8000
                        .endif
                    .endif
                .endif
                jmp done
            .endif
        .endif
        sub esi,0x10000
        .if ecx == multiplicand.m32[12]
            .if ebx == multiplicand.m32[8]
                .if edx == multiplicand.m32[4]
                    cmp eax,multiplicand.m32[0]
                .endif
            .endif
        .endif
        .ifna
            .ifz
                mov edi,eax
                or  edi,edx
                or  edi,ebx
                jnz done
                cmp ecx,0x80000000
                jne done
                or si,si
                .ifs
                    xor esi,ecx
                .endif
            .endif
            jmp return_B
        .endif
        jmp done

    er_NaN_B: ; B is a NaN or infinity

        sub esi,0x10000
        mov edi,multiplicand.m32[0]
        or  edi,multiplicand.m32[4]
        or  edi,multiplicand.m32[8]
        .ifz
            .if multiplicand.m32[12] == 0x80000000
                mov edi,eax
                or  edi,edx
                or  edi,ebx
                or  edi,ecx
                .ifz
                    mov esi,-1 ; -NaN
                .else
                    or  si,si
                    .ifs
                        xor esi,multiplicand.m32[12] ; flip sign bit
                    .endif
                .endif
            .endif
        .endif

    return_B:
        mov ecx,multiplicand.m32[12]
        mov ebx,multiplicand.m32[8]
        mov edx,multiplicand.m32[4]
        mov eax,multiplicand.m32[0]
        shr esi,16
        jmp done

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

quadmul endp

    end
