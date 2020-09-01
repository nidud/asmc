; _DESTOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_destoflt proc fp:ptr STRFLT, buffer:string_t

  local digits:int_t, sigdig:int_t

    mov r10,rcx
    mov r8,rdx
    mov r11,[rcx].STRFLT.string
    mov ecx,[rcx].STRFLT.flags
    xor eax,eax
    mov sigdig,eax
    xor r9d,r9d
    xor edx,edx

    .repeat

        .while 1

            mov al,[r11]
            inc r11
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

                .if r9d < Q_SIGDIG
                    mov [r8],al
                    inc r8
                .endif
                inc r9d
            .endif
        .endw
        mov byte ptr [r8],0
        mov digits,r9d

        ;
        ; Parse the optional exponent
        ;
        xor edx,edx
        .if ecx & _ST_DIGITS

            xor r8d,r8d ; exponent

            .if ( ( ( ecx & _ST_ISHEX ) && ( al == 'p' || al == 'P' ) ) || \
                al == 'e' || al == 'E' )

                mov al,[r11]
                lea rdx,[r11-1]
                .if al == '+'
                    inc r11
                .endif
                .if al == '-'
                    inc r11
                    or  ecx,_ST_NEGEXP
                .endif
                and ecx,not _ST_DIGITS

                .while 1

                    movzx eax,byte ptr [r11]
                    .break .if al < '0'
                    .break .if al > '9'

                    .if r8d < 100000000 ; else overflow

                        lea r9,[r8*8]
                        lea r8,[r8*2+r9-'0']
                        add r8,rax
                    .endif
                    or  ecx,_ST_DIGITS
                    inc r11
                .endw

                .if ( ecx & _ST_NEGEXP )
                    neg r8d
                .endif
                .if !( ecx & _ST_DIGITS )
                    mov r11,rdx
                .endif

            .else

                dec r11 ; digits found, but no e or E
            .endif

            mov edx,r8d
            mov eax,sigdig
            mov r9d,digits
            mov r8d,Q_DIGITS

            .if ( ecx & _ST_ISHEX )

                mov r8d,32
                shl eax,2
            .endif
            sub edx,eax

            mov eax,1
            .if ( ecx & _ST_ISHEX )

                mov eax,4
            .endif

            .if ( r9d > r8d )

                add edx,r9d
                mov r9d,r8d
                .if ( ecx & _ST_ISHEX )

                    shl r8d,2
                .endif
                sub edx,r8d
            .endif

            mov r8,buffer
            .while 1

                .break .ifs r9d <= 0
                .break .if byte ptr [r8+r9-1] != '0'

                add edx,eax
                dec r9d
            .endw
            mov digits,r9d
        .else
            mov r11,[r10].STRFLT.string
        .endif

    .until 1

    mov [r10].STRFLT.flags,ecx
    mov [r10].STRFLT.string,r11
    mov [r10].STRFLT.exponent,edx
    mov eax,digits
    ret

_destoflt endp

    END
