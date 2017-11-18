include intn.inc

.code

_divfq proc uses rsi rdi rbx r:ptr, a:ptr, b:ptr
    ;
    ;  quad float [RCX] = quad float [RDX] / quad float [R8]
    ;
local _rax[4]:qword,
      _rdx[4]:qword,
      _rcx[4]:qword

    mov rbx,[r8]
    shl rbx,16
    mov rcx,[r8+6]
    mov si,[r8+14]      ; shift out bits 0..112
    and esi,Q_EXPMASK   ; if not zero
    neg esi             ; - set high bit
    mov si,[r8+14]
    rcr rcx,1
    rcr rbx,1
    shl esi,16

    mov rax,[rdx]
    shl rax,16
    mov si,[rdx+14]
    and si,Q_EXPMASK
    neg si
    mov si,[rdx+14]
    mov rdx,[rdx+6]
    rcr rdx,1
    rcr rax,1

    .repeat                 ; create frame -- no loop

        add si,1            ; add 1 to exponent
        jc  er_NaN_A        ; quit if NaN
        jo  er_NaN_A        ; ...
        add esi,0xFFFF      ; readjust low exponent and inc high word
        jc  er_NaN_B        ; quit if NaN
        jo  er_NaN_B        ; ...
        sub esi,0x10000     ; readjust high exponent

        mov rdi,rbx         ; B is 0 ?
        or  rdi,rcx
        .ifz
            .if !(esi & 0x7FFF0000)

                mov rdi,rax ; A is 0 ?
                or  rdi,rdx
                .ifz        ; exit if A is 0
                    mov edi,esi
                    add di,di
                    .ifz
                        ;
                        ; Invalid operation - return NaN
                        ;
                        mov rcx,0x4000000000000000
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

        mov rdi,rax         ; A is 0 ?
        or  rdi,rdx
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
                shl rax,1   ; - shift fraction left
                rcl rdx,1
            .until carry?   ; - until implied 1 bit is on
        .endif
        .if !si             ; if B is a denormal
            .repeat
                dec si
                add rbx,rbx
                adc rcx,rcx
            .until carry?
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

        mov _rdx[0],rbx
        mov _rdx[8],rcx
        mov _rax[16],rax         ; save dividend
        mov _rax[24],rdx
        xor rax,rax
        mov _rax[0],rax
        mov _rax[8],rax
        mov _rdx[16],rax
        mov _rdx[24],rax

        _divnd(&_rax, &_rdx, &_rcx, 4)

        mov esi,edi
        mov rax,_rax[0]         ; load quotient
        mov rdx,_rax[8]
        dec si
        shr _rax[16],1          ; overflow bit..
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
            shr rdx,cl
            xor esi,esi
        .endif
        add esi,esi
        rcr si,1
        .break

      ; A is a NaN or infinity

      er_NaN_A:

        mov r8,0x8000000000000000
        dec si
        add esi,0x10000
        .ifnb
            .ifno
                .ifs
                    mov rdi,rax
                    or  edi,edx
                    .ifz
                        .if rdx == r8
                            xor esi,0x8000
                        .endif
                    .endif
                .endif
                .break
            .endif
        .endif
        sub esi,0x10000
        mov rdi,rax
        or  edi,edx
        .ifz
            mov rdi,rcx
            or  edi,ebx
            .ifz
                .if rdx == r8 && rcx == rdx
                    sar rdx,1
                    or  esi,-1 ; -NaN
                    .break
                .endif
            .endif
        .endif
        .if rdx == rcx
            cmp rax,rbx
        .endif
        jna return_B
        .break

      ; B is a NaN or infinity

      er_NaN_B:

        sub esi,0x10000
        mov rdi,rcx
        or  edi,ebx
        .ifz
            mov rdx,0x8000000000000000
            .if rdx == rcx
                mov eax,esi
                shl eax,16
                xor esi,eax
                and esi,0x80000000
                sub rcx,rdx
            .endif
        .endif

      return_B:
        mov rdx,rcx
        mov rax,rbx
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
        xor rax,rax
        xor rdx,rdx

    .until 1

    mov rdi,r
    shl rax,1           ; shift bits back
    rcl rdx,1           ; shift high bit out..
    shr rax,16          ; 16 low bits
    mov [rdi],rax
    mov [rdi+6],rdx
    mov [rdi+14],si     ; exponent and sign
    mov rax,rdi         ; return result
    ret

_divfq endp

    end
