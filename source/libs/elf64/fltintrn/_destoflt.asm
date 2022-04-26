; _DESTOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

_destoflt proc uses rbx fp:ptr STRFLT, buffer:string_t

  local digits:int_t, sigdig:int_t

    mov rbx,buffer
    mov rsi,[fp].STRFLT.string
    mov ecx,[fp].STRFLT.flags
    xor eax,eax
    mov sigdig,eax
    xor r9d,r9d
    xor edx,edx

    .repeat

        .while 1

            mov al,[rsi]
            inc rsi
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
                    mov [rbx],al
                    inc rbx
                .endif
                inc r9d
            .endif
        .endw
        mov byte ptr [rbx],0
        mov digits,r9d

        ;
        ; Parse the optional exponent
        ;
        xor edx,edx
        .if ecx & _ST_DIGITS

            xor r8d,r8d ; exponent

            .if ( ( ( ecx & _ST_ISHEX ) && ( al == 'p' || al == 'P' ) ) || \
                al == 'e' || al == 'E' )

                mov al,[rsi]
                lea rdx,[rsi-1]
                .if al == '+'
                    inc rsi
                .endif
                .if al == '-'
                    inc rsi
                    or  ecx,_ST_NEGEXP
                .endif
                and ecx,not _ST_DIGITS

                .while 1

                    movzx eax,byte ptr [rsi]
                    .break .if al < '0'
                    .break .if al > '9'

                    .if r8d < 100000000 ; else overflow

                        lea r9,[r8*8]
                        lea r8,[r8*2+r9-'0']
                        add r8,rax
                    .endif
                    or  ecx,_ST_DIGITS
                    inc rsi
                .endw

                .if ( ecx & _ST_NEGEXP )
                    neg r8d
                .endif
                .if !( ecx & _ST_DIGITS )
                    mov rsi,rdx
                .endif

            .else

                dec rsi ; digits found, but no e or E
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

            .while 1

                .break .ifs r9d <= 0
                .break .if byte ptr [rbx+r9-1] != '0'

                add edx,eax
                dec r9d
            .endw
            mov digits,r9d
        .else
            mov rsi,[fp].STRFLT.string
        .endif

    .until 1

    mov [fp].STRFLT.flags,ecx
    mov [fp].STRFLT.string,rsi
    mov [fp].STRFLT.exponent,edx
    mov eax,digits
    ret

_destoflt endp

    end
