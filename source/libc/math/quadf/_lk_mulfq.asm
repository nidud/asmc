include intn.inc

.code

_lk_mulfq proc uses esi edi ebx
local b[4]
local h[4]
local a[4]
    ;
    ;  quad float [EBX] = quad float [EAX] * quad float [EDX]
    ;
    push ecx
    push eax

    mov si,[edx+14]
    mov ax,[edx]
    shl eax,16
    mov edi,[edx+2]
    mov ecx,[edx+6]
    mov ebx,[edx+10]
    and si,0x7FFF
    cmp si,0x3FFF
    mov si,[edx+14]
    cmc
    rcr ebx,1
    rcr ecx,1
    rcr edi,1
    rcr eax,1
    mov b,eax
    mov b[4],edi
    mov b[8],ecx
    mov b[12],ebx
    shl esi,16

    pop edi
    mov si,[edi+14]
    mov ax,[edi]
    shl eax,16
    mov edx,[edi+2]
    mov ebx,[edi+6]
    mov ecx,[edi+10]
    and si,0x7FFF
    cmp si,0x3FFF
    mov si,[edi+14]
    cmc
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
        mov edi,b           ; exit if B is 0
        or  edi,b[4]
        or  edi,b[8]
        or  edi,b[12]
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
        .ifnb               ; exponent negative ?
            cmp si,0x7FFF   ; overflow ?
            jnc overflow
        .endif
        .ifs si < -64       ; exponent too small ?
            dec si
            jmp return_si0
        .endif

        mov a,eax
        mov a[4],edx
        mov a[8],ebx
        mov a[12],ecx

        _mulow(&a, &b, &h)  ; A * B

        mov edi,a[12]
        mov eax,h
        mov edx,h[4]
        mov ebx,h[8]
        mov ecx,h[12]
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
                .if a[8]
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
        .break

      ; A is a NaN or infinity

      er_NaN_A:

        mov edi,eax
        or  edi,edx
        or  edi,ebx
        .ifz
            .if ecx == 0x80000000
                mov edi,b
                or  edi,b[4]
                or  edi,b[8]
                or  edi,b[12]
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
                .break
            .endif
        .endif
        sub esi,0x10000
        .if ecx == b[12]
            .if ebx == b[8]
                .if edx == b[4]
                    cmp eax,b
                .endif
            .endif
        .endif
        .ifna
            .ifz
                mov edi,eax
                or  edi,edx
                or  edi,ebx
                .break .ifnz
                .break .if ecx != 0x80000000
                or si,si
                .ifs
                    xor esi,ecx
                .endif
            .endif
            jmp return_B
        .endif
        .break

      ; B is a NaN or infinity

      er_NaN_B:

        sub esi,0x10000
        mov edi,b
        or  edi,b[4]
        or  edi,b[8]
        .ifz
            .if b[12] == 0x80000000
                mov edi,eax
                or  edi,edx
                or  edi,ebx
                or  edi,ecx
                .ifz
                    mov esi,-1          ; -NaN
                .else
                    or  si,si
                    .ifs
                        xor esi,b[12]   ; flip sign bit
                    .endif
                .endif
            .endif
        .endif

      return_B:
        mov ecx,b[12]
        mov ebx,b[8]
        mov edx,b[4]
        mov eax,b
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

    mov edi,eax
    pop eax
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

_lk_mulfq endp

    end
