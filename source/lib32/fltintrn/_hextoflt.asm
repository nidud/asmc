include ltype.inc
include fltintrn.inc

    .code

_hextoflt proc uses esi edi ebx fp:LPSTRFLT, buffer:LPSTR
local digits, sigdig

    mov edx,fp
    mov edi,buffer
    mov esi,[edx].S_STRFLT.string
    mov ecx,[edx].S_STRFLT.flags
    xor eax,eax
    mov sigdig,eax
    xor ebx,ebx
    xor edx,edx
    ;
    ; Parse the mantissa
    ;
    .while 1
        lodsb
        .break .if !al
        .if al == '.'
            .break .if ecx & _ST_DOT
            or ecx,_ST_DOT
        .else
            .break .if !(_ltype[eax+1] & _HEX)
            .if ecx & _ST_DOT
                inc sigdig
            .endif
            or ecx,_ST_DIGITS
            or edx,eax
            .continue .if edx == '0' ; if a significant digit
            .if ebx < MAX_LD_SIGDIG
                stosb
            .endif
            inc ebx
        .endif
    .endw
    mov digits,ebx
    ;
    ; Parse the optional exponent
    ;
    xor edx,edx
    .if ecx & _ST_DIGITS

        xor edi,edi ; exponent
        .if al == 'p' || al == 'P'

            mov al,[esi]
            lea edx,[esi-1]
            .if al == '+'
                inc esi
            .endif
            .if al == '-'
                inc esi
                or  ecx,_ST_NEGEXP
            .endif
            and ecx,not _ST_DIGITS

            .while 1
                movzx eax,byte ptr [esi]
                .break .if !(_ltype[eax+1] & _DIGIT)
                .if edi < 10000
                    lea ebx,[edi*8]
                    lea edi,[edi*2+ebx-'0']
                    add edi,eax
                .endif
                or  ecx,_ST_DIGITS
                inc esi
            .endw
            .if ecx & _ST_NEGEXP
                neg edi
            .endif
            .if !(ecx & _ST_DIGITS)
                mov esi,edx
            .endif
        .else
            dec esi ; digits found, but no e or E
        .endif

        mov edx,edi
        mov ecx,sigdig
        shl ecx,2
        sub edx,ecx
        mov ebx,digits
        mov eax,MAX_LD_HEXDIG
        .if ebx > eax
            add edx,ebx
            mov ebx,eax
            shl eax,2
            sub edx,eax
        .endif
        mov eax,buffer
        .while 1
            .break .ifs ebx <= 0
            .break .if byte ptr [eax+ebx-1] != '0'
            add edx,4
            dec ebx
        .endw
        mov digits,ebx
    .else
        mov ecx,fp
        mov esi,[ecx].S_STRFLT.string
    .endif
    mov ecx,fp
    mov [ecx].S_STRFLT.string,esi
    mov [ecx].S_STRFLT.exponent,edx
    mov eax,digits
    ret
_hextoflt endp

    END
