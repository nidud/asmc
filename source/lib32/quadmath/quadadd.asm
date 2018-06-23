include quadmath.inc

    .code

_lk_add proc private uses esi edi ebx
    ;
    ; quad float [eax] = quad float [eax] +- quad float [edx]
    ;
local rdx[4],rcx
local rdi,rbp,rbx

    mov rdi,ecx
    push eax            ; save dest.

    push eax
    mov ax,[edx]
    shl eax,16
    mov edi,[edx+2]
    mov ebx,[edx+6]
    mov ecx,[edx+10]
    mov si, [edx+14]
    and si, Q_EXPMASK
    neg si
    mov si, [edx+14]
    rcr ecx,1
    rcr ebx,1
    rcr edi,1
    rcr eax,1
    mov rdx[0],eax
    mov rdx[4],edi
    mov rdx[8],ebx
    mov rdx[12],ecx
    shl esi,16
    pop edi
    mov ax,[edi]
    shl eax,16
    mov edx,[edi+2]
    mov ebx,[edi+6]
    mov ecx,[edi+10]
    mov si, [edi+14]
    and si, Q_EXPMASK
    neg si
    mov si, [edi+14]
    rcr ecx,1
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
        xor esi,rdi         ; flip sign if subtract

        mov edi,eax         ; A is 0 ?
        or  edi,edx
        or  edi,ebx
        or  edi,ecx
        .ifz
            shl si,1        ; place sign in carry
            .ifz
                shr esi,16
                mov eax,rdx[0]  ; return B
                mov edx,rdx[4]
                mov ebx,rdx[8]
                mov ecx,rdx[12]
                shl esi,1
                mov edi,eax     ; check for 0
                or  edi,edx
                or  edi,ebx
                or  edi,ecx
                or  di,si
                .if edi         ; if not zero
                    shr esi,1   ; -> restore sign bit
                .endif
                .break
            .endif
            rcr si,1        ; put back the sign
        .endif

        mov edi,rdx[0]      ; B is 0 ?
        or  edi,rdx[4]
        or  edi,rdx[8]
        or  edi,rdx[12]     ; quit if B is 0
        .ifz
            .break .if !(esi & 0x7FFF0000)
        .endif

        mov edi,esi         ; exponent and sign of A into EDI
        rol edi,16          ; shift to top
        sar edi,16          ; duplicate sign
        sar esi,16          ; ...
        and edi,0x80007FFF  ; isolate signs and exponent
        and esi,0x80007FFF  ; ...
        mov rbp,esi         ; assume A < B
        rol edi,16          ; rotate signs to bottom
        rol esi,16          ; ...
        add si,di           ; calc sign of result
        rol edi,16          ; rotate signs to top
        rol esi,16          ; ...
        sub si,di           ; calculate difference in exponents
        .ifnz               ; if different
            .ifb                ; if B < A
                mov rbp,edi     ; get larger exponent for result
                neg si          ; negate the shift count
                mov edi,rdx[0]  ; flip operands
                mov rdx[0],eax
                mov eax,edi
                mov edi,rdx[4]
                mov rdx[4],edx
                mov edx,edi
                mov edi,rdx[8]
                mov rdx[8],ebx
                mov ebx,edi
                mov edi,rdx[12]
                mov rdx[12],ecx
                mov ecx,edi
            .endif
            .if si > 128    ; if shift count too big
                mov esi,rbp
                shl esi,1       ; get sign
                rcr si,1        ; merge with exponent
                mov eax,rdx[0]  ; get result
                mov edx,rdx[4]
                mov ebx,rdx[8]
                mov ecx,rdx[12]
                .break
            .endif
        .endif

        and si,0xFF         ; zero extend B
        or  esi,esi         ; get bit 0 of sign word - value is 0 if
                            ; both operands have same sign, 1 if not
        .ifs                ; if signs are different
            or  si,0xFF00   ; - set high part to ones
            neg rdx[12]     ; - negate the fraction of op2
            neg rdx[8]
            sbb rdx[12],0
            neg rdx[4]
            sbb rdx[8],0
            neg rdx[0]
            sbb rdx[4],0    ; - flip sign
            xor byte ptr rbp[3],0x80
        .endif

        mov rcx,esi
        xor edi,edi         ; get a zero for sticky bits
        .if esi & 0xFF      ; if shifting required

            movzx esi,byte ptr rcx
            .if esi >= 64       ; if shift count >= 64
                .if eax || edx  ; check low order qword for 1 bits
                    inc edi     ; edi=1 if EDX:EAX non zero
                .endif
                .if esi == 128  ; if shift count is 128
                    or  edi,ecx ; get rest of sticky bits from high part
                    or  edi,ebx
                    xor ebx,ebx ; zero high part
                    xor ecx,ecx
                .endif
                mov eax,ebx     ; shift right 64
                mov edx,ecx
                xor ebx,ebx
                xor ecx,ecx
            .endif
            mov  rbx,ebx        ; get the extra sticky bits
            xchg esi,ecx
            xor  ebx,ebx
            shrd ebx,eax,cl
            or   edi,ebx        ; save them
            mov  ebx,rbx
            shrd eax,edx,cl     ; align the fractions
            shrd edx,ebx,cl
            shrd ebx,esi,cl
            shr  esi,cl
            mov  ecx,esi
        .endif

        add eax,rdx[0]
        adc edx,rdx[4]
        adc ebx,rdx[8]
        adc ecx,rdx[12]
        adc byte ptr rcx[1],0
        .ifs
            .if byte ptr rcx == 128
                xor esi,esi
                .if edi & 0x7FFFFFFF
                    inc esi     ; make single sticky bit
                .endif
                shr esi,1
                adc eax,0       ; round up fraction if required
                adc edx,0
                adc ebx,0
                adc ecx,0
            .endif
            neg ecx
            neg ebx
            sbb ecx,0
            neg edx
            sbb ebx,0
            neg eax
            sbb edx,0
            mov byte ptr rcx[1],0
            xor byte ptr rbp[3],0x80
        .endif
        movzx esi,byte ptr rcx[1]
        or  esi,eax
        or  esi,edx
        or  esi,ebx
        or  esi,ecx
        mov esi,rbp
        .ifnz
            .if !si
                add esi,esi
                rcr si,1
                .break
            .endif
            ;
            ; if top bits are 0
            ;
            .if byte ptr rcx[1] == 0
                rol edi,1   ; set carry from last sticky bit
                rol edi,1
                .repeat
                    dec si  ; decrement exponent
                    .ifz
                        add esi,esi
                        rcr si,1
                        .break(1)
                    .endif
                    rcl eax,1   ; shift fraction left one bit
                    rcl edx,1
                    rcl ebx,1
                    rcl ecx,1
                .untilb         ; until carry
            .endif
            inc si
            cmp si,Q_EXPMASK
            je  overflow
            stc                 ; set carry
            rcr ecx,1           ; shift fraction right 1
            rcr ebx,1
            rcr edx,1
            rcr eax,1
            .ifc                ; if guard bit is on
                shl edi,1       ; get top sticky bit
                .ifz            ; if no more sticky bits
                    ror eax,1   ; set carry with bottom bit of DX
                    rol eax,1
                .endif
                adc eax,0       ; round up fraction if required
                adc edx,0
                adc ebx,0
                adc ecx,0
                .ifc            ; if we got a carry
                    rcr ecx,1   ; shift fraction right 1
                    rcr ebx,1
                    rcr edx,1
                    rcr eax,1
                    inc si      ; increment exponent
                    cmp si,Q_EXPMASK
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
        mov edi,eax
        or  edi,edx
        or  edi,ebx
        .ifz
            mov edi,rdx[0]
            or  edi,rdx[4]
            or  edi,rdx[8]
            .ifz
                .if ecx == 0x80000000 && ecx == rdx[12]
                    sar ecx,1
                    or  esi,-1 ; -NaN
                    .break
                .endif
            .endif
        .endif

        .if ecx == rdx[12]
            .if ebx == rdx[8]
                .if edx == rdx[4]
                    cmp eax,rdx[0]
                .endif
            .endif
        .endif
        jna return_B
        .break

      ; B is a NaN or infinity

      er_NaN_B:

        sub esi,0x10000
        mov edi,rdx[0]
        or  edi,rdx[4]
        or  edi,rdx[8]
        .ifz
            mov ecx,0x80000000
            .if ecx == rdx[12]
                mov eax,esi
                shl eax,16
                xor esi,eax
                and esi,ecx
                sub rdx[12],ecx
            .endif
        .endif

      return_B:
        mov ecx,rdx[12]
        mov ebx,rdx[8]
        mov edx,rdx[4]
        mov eax,rdx[0]
        shr esi,16
        .break

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

    .until 1

    pop edi
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

_lk_add endp

quadsub proc a:ptr, b:ptr

    mov eax,a
    mov edx,b
    mov ecx,0x80000000
    _lk_add()
    ret

quadsub endp

quadadd proc a:ptr, b:ptr

    mov eax,a
    mov edx,b
    xor ecx,ecx
    _lk_add()
    ret

quadadd endp

    end
