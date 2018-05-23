include quadmath.inc

    .code

ifdef _LINUX
quadmul proc uses rbx r12 a:ptr, b:ptr
    mov r12,rdi
    mov rdx,rsi
else
option win64:rsp nosave noauto
quadmul proc uses rsi rdi rbx r12 a:ptr, b:ptr
    mov r12,rcx
endif
    mov rbx,[rdx]
    shl rbx,16
    mov rcx,[rdx+6]
    mov si,[rdx+14]      ; shift out bits 0..112
    and esi,Q_EXPMASK   ; if not zero
    neg esi             ; - set high bit
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

    .repeat

        add si,1            ; add 1 to exponent
        jc  er_NaN_A        ; quit if NaN
        jo  er_NaN_A        ; ...
        add esi,0xFFFF      ; readjust low exponent and inc high word
        jc  er_NaN_B        ; quit if NaN
        jo  er_NaN_B        ; ...
        sub esi,0x10000     ; readjust high exponent
        mov rdi,rax         ; A is 0 ?
        or  rdi,rdx
        .ifz                ; exit if A is 0
            add si,si       ; place sign in carry
            .break .ifz     ; return 0
            rcr si,1        ; restore sign of A
        .endif
        mov rdi,rbx         ; exit if B is 0
        or  rdi,rcx
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

        mov r10,rbx
        mov r11,rcx
        mov r8,rax
        mov r9,rcx
        mov rcx,rdx

        .if !rdx && !r11
            mul     r10
            xor     r10,r10
        .else
            mul     r10
            mov     rbx,rdx
            mov     rdi,rax
            mov     rax,rcx
            mul     r11
            mov     r11,rdx
            xchg    r10,rax
            mov     rdx,rcx
            mul     rdx
            add     rbx,rax
            adc     r10,rdx
            adc     r11,0
            mov     rax,r8
            mov     rdx,r9
            mul     rdx
            add     rbx,rax
            adc     r10,rdx
            adc     r11,0
            mov     rdx,rbx
            mov     rax,rdi
        .endif

        mov rdi,rdx
        mov rax,r10
        mov rdx,r11
        test rdx,rdx
        .ifns ; if not normalized
            shl rdi,1
            rcl rax,1
            rcl rdx,1
            dec si
        .endif

        shl rdi,1
        .ifb
            .ifz
                .if edi
                    stc
                .else
                    bt eax,0
                .endif
            .endif
            adc rax,0
            adc rdx,0
            .ifb
                rcr rdx,1
                rcr rax,1
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
            movzx ecx,si
            shrd rax,rdx,cl
            shr rdx,cl
            xor si,si
        .endif
        add esi,esi
        rcr si,1
    .until 1

done:
    shl rax,1
    rcl rdx,1
    shr rax,16
    mov [r12],rax
    mov [r12+6],rdx
    mov [r12+14],si
    mov rax,r12
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
    xor rax,rax
    xor rdx,rdx
    jmp done

er_NaN_B:   ; B is a NaN or infinity

    sub esi,0x10000
    mov rdi,rbx
    or  edi,ecx
    .ifz
        mov r8,0x8000000000000000
        .if rcx == r8
            mov rdi,rax
            or  rdi,rdx
            .ifz
                mov esi,-1          ; -NaN
            .else
                or  si,si
                .ifs
                    xor esi,0x80000000   ; flip sign bit
                .endif
            .endif
        .endif
    .endif

return_B:
    mov rdx,rcx
    mov rax,rbx
    shr esi,16
    jmp done

er_NaN_A:   ; A is a NaN or infinity

    mov r8,0x8000000000000000
    mov rdi,rax
    or  edi,edx
    .ifz
        .if rdx == r8
            mov rdi,rbx
            or  rdi,rcx
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
            mov rdi,rax
            or  edi,edx
            .ifz
                .if rdx == r8
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
    .if rdx == rcx
        cmp rax,rbx
    .endif
    .ifna
        .ifz
            mov rdi,rax
            or  edi,edx
            jnz done
            cmp rdx,r8
            jne done
            or si,si
            .ifs
                xor esi,0x80000000
            .endif
        .endif
        jmp return_B
    .endif
    jmp done

quadmul endp

    end
