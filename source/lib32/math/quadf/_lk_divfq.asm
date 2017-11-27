include intn.inc

.code

_lk_divfq proc uses esi edi ebx
    ;
    ;  quad float [ECX] = quad float [EAX] / quad float [EDX]
    ;
local rax[8],rdx[8],rcx[8]

    push ecx            ; save dest.
    push eax            ; save dividend

    xor eax,eax
    lea edi,rdx
    mov ecx,2*8
    rep stosd

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
    mov rdx[0],eax      ; divisor to stack (rdx)
    mov rdx[4],edi
    mov rdx[8],ecx
    mov rdx[12],ebx
    shl esi,16

    pop edi             ; restore dividend
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

        mov edi,rdx[0]      ; B is 0 ?
        or  edi,rdx[4]
        or  edi,rdx[8]
        or  edi,rdx[12]
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
                ; zero divide - return signed infinity
                ;
                mov esi,0xFFFF
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
                mov eax,rdx[0]
                add rdx[0],eax
                mov eax,rdx[4]
                adc rdx[4],eax
                mov eax,rdx[8]
                adc rdx[0],eax
                mov eax,rdx[12]
                adc rdx[12],eax
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

        mov rax[16],eax         ; save dividend
        mov rax[20],edx
        mov rax[24],ebx
        mov rax[28],ecx

        _divnd(&rax, &rdx, &rcx, 8)

        mov esi,edi
        mov eax,rax[0]          ; load quotient
        mov edx,rax[4]
        mov ebx,rax[8]
        mov edi,rax[12]
        dec si
        shr rax[16],1           ; overflow bit..
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
        .break

      ; A is a NaN or infinity

      er_NaN_A:

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
                .break
            .endif
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

_lk_divfq endp

    end
