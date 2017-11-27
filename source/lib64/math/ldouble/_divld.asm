include intn.inc

option win64:rsp nosave noauto

.code

_divld proc uses rsi rdi rbx result:ptr, a:ptr, b:ptr

    push rcx            ; save dest.

    mov rbx,[r8]
    mov si, [r8+8]
    shl esi,16
    mov rax,[rdx]
    mov si, [rdx+8]

    .repeat             ; create frame -- no loop

        add si,1            ; add 1 to exponent
        jc  er_NaN_A        ; quit if NaN
        jo  er_NaN_A        ; ...
        add esi,0xFFFF      ; readjust low exponent and inc high word
        jc  er_NaN_B        ; quit if NaN
        jo  er_NaN_B        ; ...
        sub esi,0x10000     ; readjust high exponent

        .if !rbx            ; B is 0 ?
            .if !(esi & 0x7FFF0000)

                .if !rax    ; exit if A is 0
                    mov edi,esi
                    add di,di
                    .ifz
                        ;
                        ; Invalid operation - return NaN
                        ;
                        mov rax,0xC000000000000000
                        or  esi,0xFFFF
                        .break
                    .endif
                .endif
                ;
                ; zero divide - return signed infinity
                ;
                mov rax,0x8000000000000000
                or  esi,0x7FFF
                .break
            .endif
        .endif

        .if !rax            ; A is 0 ?
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
            .until carry?   ; - until implied 1 bit is on
        .endif
        .if !si             ; if B is a denormal
            .repeat         ; ...
                dec si
                shl rbx,1
            .until carry?
        .endif
        sub di,si               ; calculate exponent of result
        add di,0x3FFF           ; add in removed bias
        .ifns                   ; overflow ?
            .if di >= 0x7FFF    ; quit if exponent is negative
                mov si,0x7FFF   ; - set infinity
                add esi,esi
                rcr si,1
                mov rax,0x8000000000000000
                .break          ; return infinity
            .endif
        .endif
        .ifs di < -65           ; if exponent is too small
            xor eax,eax         ; return underflow
            xor esi,esi
            .break
        .endif

        mov r8,rax              ; save dividend
        mov r9,rbx              ; save divisor
        mov rdi,rsi             ; save exponent

        mov rsi,rax
        .if rax <= rbx
            sub rax,rbx
        .endif
        mov r10,rax
        xor rdx,rdx
        mov rax,rsi
        div rbx
        mov r11,rax
        mul rbx
        .if r10b & 1
            add rax,rbx
        .endif
        neg rbx
        sbb rsi,rax
        .ifnz
            .repeat
                sub r11,1
                adc rax,rbx
                adc rsi,r9
            .untilz
        .endif

        mov rax,rsi
        mov rbx,r10
        mov esi,edi

        dec si
        shr ebx,1           ; overflow bit..
        .ifc
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
            shr rax,cl
            xor si,si
        .endif
        add esi,esi
        rcr si,1
        .break

      ; A is a NaN or infinity

      er_NaN_A:

        mov r8,0x8000000000000000
        dec si
        add esi,0x10000
        .ifnc
            .ifno
                .ifs
                    .if rax == r8
                        xor esi,0x8000
                    .endif
                .endif
                .break
            .endif
        .endif
        sub esi,0x10000
        .if rax == r8 && rbx == r8
            sar rax,1
            or  esi,-1 ; -NaN
            .break
        .endif
        .if rax <= rbx
            mov rax,rbx
            shr esi,16
        .endif
        .break

      ; B is a NaN or infinity

      er_NaN_B:

        sub esi,0x10000
        mov rax,0x8000000000000000
        .if rbx == rax
            mov eax,esi
            shl eax,16
            xor esi,eax
            and esi,0x80000000
            xor rbx,rbx
        .endif
        mov rax,rbx
        shr esi,16
        .break

    .until 1

    pop rdx
    mov [rdx],rax
    mov [rdx+8],si      ; exponent and sign
    mov rax,rdx         ; return result
    ret

_divld endp

    end
