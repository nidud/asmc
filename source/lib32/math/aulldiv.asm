; AULLDIV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

    .486
    .model flat, c
    .code

    ; Unsigned binary division of EDX:EAX by ECX:EBX
    ;
    ;  dividend / divisor = [quotient.remainder](dividend.divisor)
    ;

_U8D::

    .repeat

        .break .if ecx

        dec ebx
        .ifnz

            inc ebx
            .if ebx <= edx
                mov  ecx,eax
                mov  eax,edx
                xor  edx,edx
                div  ebx        ; edx / ebx
                xchg ecx,eax
            .endif
            div ebx             ; edx:eax / ebx
            mov ebx,edx
            mov edx,ecx
            xor ecx,ecx
        .endif
        ret
    .until 1

    .repeat

        .break .if ecx < edx
        .ifz
            .if ebx <= eax
                sub eax,ebx
                mov ebx,eax
                xor ecx,ecx
                xor edx,edx
                mov eax,1
                ret
            .endif
        .endif
        xor  ecx,ecx
        xor  ebx,ebx
        xchg ebx,eax
        xchg ecx,edx
        ret

    .until 1

    push ebp
    push esi
    push edi

    xor ebp,ebp
    xor esi,esi
    xor edi,edi

    .repeat

        add ebx,ebx
        adc ecx,ecx
        .ifnc
            inc ebp
            .continue(0) .if ecx < edx
            .ifna
                .continue(0) .if ebx <= eax
            .endif
            add esi,esi
            adc edi,edi
            dec ebp
            .break .ifs
        .endif
        .while 1
            rcr ecx,1
            rcr ebx,1
            sub eax,ebx
            sbb edx,ecx
            cmc
            .continue(0) .ifc
            .repeat
                add esi,esi
                adc edi,edi
                dec ebp
                .break(1) .ifs
                shr ecx,1
                rcr ebx,1
                add eax,ebx
                adc edx,ecx
            .untilb
            adc esi,esi
            adc edi,edi
            dec ebp
            .break(1) .ifs
        .endw
        add eax,ebx
        adc edx,ecx
    .until 1
    mov ebx,eax
    mov ecx,edx
    mov eax,esi
    mov edx,edi
    pop edi
    pop esi
    pop ebp
    ret

_aulldiv::

    push    ebx
    mov     eax,4[esp+4]
    mov     edx,4[esp+8]
    mov     ebx,4[esp+12]
    mov     ecx,4[esp+16]
    call    _U8D
    pop     ebx
    ret     16

    END
