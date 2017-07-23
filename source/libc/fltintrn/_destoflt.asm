include ltype.inc
include fltintrn.inc

    .code

_destoflt proc uses esi edi ebx fp:LPSTRFLT, buffer:LPSTR
ifdef __REAL16__
local maxdig, maxsig
endif
local digits, sigdig

    mov edx,fp
    mov edi,buffer
    mov esi,[edx].S_STRFLT.string
    mov ecx,[edx].S_STRFLT.flags
    xor eax,eax
    mov sigdig,eax
    xor ebx,ebx
    xor edx,edx
ifdef __REAL16__
    mov maxdig,MAX_LD_DIGITS
    mov maxsig,MAX_LD_SIGDIG
    .if ecx & _ST_QFLT
        mov maxdig,MAX_Q_DIGITS
        mov maxsig,MAX_Q_SIGDIG
    .endif
else
maxdig equ <MAX_LD_DIGITS>
maxsig equ <MAX_LD_SIGDIG>
endif
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
            .break .if !(_ltype[eax+1] & _DIGIT)
            .if ecx & _ST_DOT
                inc sigdig
            .endif
            or ecx,_ST_DIGITS
            or edx,eax
            .continue .if edx == '0' ; if a significant digit
            .if ebx < maxsig
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
        .if al == 'e' || al == 'E'

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
                .if edi < 2000
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
        sub edx,sigdig
        mov ebx,digits
        mov eax,maxdig
        .if ebx > eax
            add edx,ebx
            sub edx,eax
            mov ebx,eax
        .endif
        mov eax,buffer
        .while 1
            .break .ifs ebx <= 0
            .break .if byte ptr [eax+ebx-1] != '0'
            inc edx
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

_destoflt endp

    END
