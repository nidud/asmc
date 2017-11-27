include intn.inc

option win64:rsp nosave noauto

.code

_mulld proc uses rsi rdi rbx result:ptr, a:ptr, b:ptr

    push rcx            ; save dest.

    mov rbx,[r8]
    mov si, [r8+8]
    shl esi,16
    mov rax,[rdx]
    mov si, [rdx+8]

    .repeat

        add si,1            ; add 1 to exponent
        jc  er_NaN_A        ; quit if NaN
        jo  er_NaN_A        ; ...
        add esi,0xFFFF      ; readjust low exponent and inc high word
        jc  er_NaN_B        ; quit if NaN
        jo  er_NaN_B        ; ...
        sub esi,0x10000     ; readjust high exponent
        .if !rax            ; exit if A is 0
            add si,si       ; place sign in carry
            .break .ifz     ; return 0
            rcr si,1        ; restore sign of A
        .endif
        .if !rbx            ; exit if B is 0
            .if !(esi & 0x7FFF0000)
                xor eax,eax
                xor esi,esi
                .break
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
            add esi,esi
            rcr si,1
            xor eax,eax
            .break
        .endif

        mul rbx
        or  rdx,rdx
        .ifns
            add rdx,rdx
            adc rax,rax
            dec si
        .endif
        add rdx,rdx
        .ifc
            .ifz
                .if esi
                    stc
                .else
                    bt eax,0
                .endif
            .endif
            adc rax,0
            .ifc
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
            mov ecx,esi
            shr rax,cl
            xor si,si
        .endif
        add esi,esi
        rcr si,1
        .break

      ; A is a NaN or infinity

      er_NaN_A:
        mov r8,0x8000000000000000
        .if rax == r8 && !rbx
            sar rax,1
            or  esi,-1 ; -NaN
            .break
        .endif
        dec si
        add esi,0x10000
        .ifnb
            .ifno
                .if rax == r8
                    or esi,esi
                    .ifs
                        xor esi,0x8000
                    .endif
                .endif
                .break
            .endif
        .endif
        sub esi,0x10000
        .if rax <= rbx
            .ifz
                .break .if rax != r8
                or si,si
                .ifs
                    xor esi,0x80000000
                .endif
            .endif
            mov rax,rbx
            shr esi,16
        .endif
        .break

      ; B is a NaN or infinity

      er_NaN_B:
        mov r8,0x8000000000000000
        sub esi,0x10000
        .if !rbx && rax == r8
            sar rax,1
            or  esi,-1          ; -NaN
            .break
        .endif
        or  si,si
        .ifs
            xor esi,0x80000000 ; flip sign bit
        .endif
        mov rax,rbx
        shr esi,16
        .break

      overflow:
        mov esi,0x7FFF
        mov rax,0x8000000000000000
        .break

    .until 1

    pop rdx
    mov [rdx],rax
    mov [rdx+8],si      ; exponent and sign
    mov rax,rdx         ; return result
    ret

_mulld endp

    end
