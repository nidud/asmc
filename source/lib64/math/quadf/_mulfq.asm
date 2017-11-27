include intn.inc

.code

_mulfq proc uses rsi rdi rbx result:ptr, _a:ptr, _b:ptr
    ;
    ;  quad float [RCX] = quad float [RDX] * quad float [R8]
    ;
local a[2]:qword, b[2]:qword, h[2]:qword

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

        mov a,rax
        mov a[8],rdx
        mov b,rbx
        mov b[8],rcx

        _mulow(&a, &b, &h)  ; A * B
        mov rcx,b[8]

        mov edi,dword ptr a[12]
        mov r8d,dword ptr h[12]
        mov rax,h
        mov rdx,h[8]
        .if !(r8d & 0x80000000) ; if not normalized
            shl edi,1
            rcl rax,1
            rcl rdx,1
            dec si
        .endif
        shl edi,1
        .ifb
            .ifz
                .if a[8]
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
        .break

      ; A is a NaN or infinity

      er_NaN_A:

        mov r8,0x8000000000000000
        mov rdi,rax
        or  edi,edx
        .ifz
            .if rdx == r8
                mov rdi,rbx
                or  rdi,rcx
                .ifz
                    mov esi,-1 ; -NaN
                    .break
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
                .break
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
                .break .ifnz
                .break .if rdx != r8
                or si,si
                .ifs
                    xor esi,0x80000000
                .endif
            .endif
            jmp return_B
        .endif
        .break

      ; B is a NaN or infinity

      er_NaN_B:

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

    mov rcx,rax
    mov rax,result
    shl rcx,1
    rcl rdx,1
    shr rcx,16
    mov [rax],rcx
    mov [rax+6],rdx
    mov [rax+14],si
    ret

_mulfq endp

    end
