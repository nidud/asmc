; _DESTOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_destoflt proc uses esi edi ebx fp:ptr STRFLT, buffer:string_t

  local digits:int_t, sigdig:int_t

    mov edx,fp
    mov edi,buffer
    mov esi,[edx].STRFLT.string
    mov ecx,[edx].STRFLT.flags
    xor eax,eax
    mov sigdig,eax
    xor ebx,ebx
    xor edx,edx

    .repeat

        .while 1

            lodsb
            .break .if !al

            .if ( al == '.' )

                .break .if ( ecx & _ST_DOT )
                or ecx,_ST_DOT

            .else

                .if ( ecx & _ST_ISHEX )

                    or al,0x20
                    .break .if al < '0' || al > 'f'
                    .break .if al > '9' && al < 'a'
                .else

                    .break .if ( al < '0' || al > '9' )
                .endif

                .if ( ecx & _ST_DOT )

                    inc sigdig
                .endif

                or ecx,_ST_DIGITS
                or edx,eax

                .continue .if edx == '0' ; if a significant digit

                .if ebx < Q_SIGDIG
                    stosb
                .endif
                inc ebx
            .endif
        .endw
        mov byte ptr [edi],0
        mov digits,ebx

        ;
        ; Parse the optional exponent
        ;
        xor edx,edx
        .if ecx & _ST_DIGITS

            xor edi,edi ; exponent

            .if ( ( ( ecx & _ST_ISHEX ) && ( al == 'p' || al == 'P' ) ) || \
                al == 'e' || al == 'E' )

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
                    .break .if al < '0'
                    .break .if al > '9'

                    .if edi < 100000000 ; else overflow

                        lea ebx,[edi*8]
                        lea edi,[edi*2+ebx-'0']
                        add edi,eax
                    .endif
                    or  ecx,_ST_DIGITS
                    inc esi
                .endw

                .if ( ecx & _ST_NEGEXP )
                    neg edi
                .endif
                .if !( ecx & _ST_DIGITS )
                    mov esi,edx
                .endif

            .else

                dec esi ; digits found, but no e or E
            .endif

            mov edx,edi
            mov eax,sigdig
            mov ebx,digits
            mov edi,Q_DIGITS

            .if ( ecx & _ST_ISHEX )

                mov edi,32
                shl eax,2
            .endif
            sub edx,eax

            mov eax,1
            .if ( ecx & _ST_ISHEX )

                mov eax,4
            .endif

            .if ( ebx > edi )

                add edx,ebx
                mov ebx,edi
                .if ( ecx & _ST_ISHEX )

                    shl edi,2
                .endif
                sub edx,edi
            .endif

            mov edi,buffer
            .while 1

                .break .ifs ebx <= 0
                .break .if byte ptr [edi+ebx-1] != '0'

                add edx,eax
                dec ebx
            .endw
            mov digits,ebx
        .else
            mov eax,fp
            mov esi,[eax].STRFLT.string
        .endif

    .until 1

    mov eax,fp
    mov [eax].STRFLT.flags,ecx
    mov [eax].STRFLT.string,esi
    mov [eax].STRFLT.exponent,edx
    mov eax,digits
    ret

_destoflt endp

    END
