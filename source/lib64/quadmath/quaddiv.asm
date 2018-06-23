include quadmath.inc

    .code

ifdef _LINUX
quaddiv proc uses rbx r12 a:ptr, b:ptr
  local dividend:U256, divisor:U256, reminder:U256
    mov r12,rdi
    mov rdx,rsi
else
option win64:nosave
quaddiv proc uses rsi rdi rbx r12 a:ptr, b:ptr
  local dividend:U256, divisor:U256, reminder:U256
    mov r12,rcx
endif

    mov rbx,[rdx]
    shl rbx,16
    mov rcx,[rdx+6]
    mov si,[rdx+14]         ; shift out bits 0..112
    and esi,Q_EXPMASK       ; if not zero
    neg esi                 ; - set high bit
    mov si,[rdx+14]
    rcr rcx,1
    rcr rbx,1
    shl esi,16
    mov rax,[r12]
    shl rax,16
    mov si,[r12+14]
    and si,Q_EXPMASK
    neg si
    mov si,[r12+14]
    mov rdx,[r12+6]
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

                        ; Invalid operation - return NaN

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

        mov divisor.m64[0],rbx
        mov divisor.m64[8],rcx
        mov dividend.m64[16],rax
        mov dividend.m64[24],rdx
        xor eax,eax
        mov dividend.m64[0],rax
        mov dividend.m64[8],rax
        mov divisor.m64[16],rax
        mov divisor.m64[24],rax
        _udiv256(&dividend, &divisor, &reminder)
        mov esi,edi
        mov rax,dividend.m64[0] ; load quotient
        mov rdx,dividend.m64[8]
        dec si
        shr dividend.m8[16],1   ; overflow bit..
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
    .until 1

done:

    shl rax,1           ; shift bits back
    rcl rdx,1           ; shift high bit out..
    shr rax,16          ; 16 low bits
    mov [r12],rax
    mov [r12+6],rdx
    mov [r12+14],si     ; exponent and sign
    mov rax,r12         ; return result
    ret

er_NaN_A: ; A is a NaN or infinity

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
                jmp done
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
                    jmp done
                .endif
            .endif
        .endif
        .if rdx == rcx
            cmp rax,rbx
        .endif
        jna return_B
        jmp done

er_NaN_B: ; B is a NaN or infinity

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
        xor rax,rax
        xor rdx,rdx
        jmp done

quaddiv endp

    end
