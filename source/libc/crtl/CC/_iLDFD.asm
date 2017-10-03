include math.inc
include errno.inc

.code
    ;
    ; long double [eax] to double [edx]
    ;
_iLDFD proc uses ecx ebx esi

    push edx
    movzx ecx,word ptr [eax+8]

    mov edx,[eax+4]
    mov eax,[eax]
    mov esi,0xFFFFF800
    mov ebx,eax

    .repeat

        shl ebx,22
        .ifc
            .ifz
                shl esi,1
            .endif
            add eax,0x0800
            adc edx,0
            .ifc
                mov edx,0x80000000
                inc cx
            .endif
        .endif

        and eax,esi
        mov ebx,ecx
        and cx,0x7FFF
        add cx,0x03FF-0x3FFF
        .if cx < 0x07FF

            .if !cx
                shrd eax,edx,12
                shl  edx,1
                shr  edx,12
            .else
                shrd eax,edx,11
                shl  edx,1
                shrd edx,ecx,11
            .endif
            shl bx,1
            rcr edx,1
            .break
        .endif

        .if cx < 0xC400

            shrd eax,edx,11
            shl edx,1
            shr edx,11
            shl bx,1
            rcr edx,1
            or  edx,0x7FF00000
            .if cx != 0x43FF
                ;
                ; OVERFLOW exception
                ;
                mov errno,ERANGE
            .endif
            .break
        .endif

        .ifs cx < -52

            xor eax,eax
            xor edx,edx
            shl ebx,17
            rcr edx,1
            .break
        .endif

        sub cx,12
        neg cx
        .if cl >= 32

            sub cl,32
            mov esi,eax
            mov eax,edx
            xor edx,edx
        .endif
        shrd esi,eax,cl
        shrd eax,edx,cl
        shr  edx,cl
        add  esi,esi
        adc  eax,0
        adc  edx,0
    .until 1
    pop esi
    mov [esi],eax
    mov [esi+4],edx
    ret
_iLDFD endp

    END
