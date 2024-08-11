; DESTOFLT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

    assume rbx:ptr STRFLT

_destoflt proc __ccall uses rsi rdi rbx fp:ptr STRFLT, buffer:string_t

   .new digits:int_t = 0
   .new sigdig:int_t = 0

    ldr rbx,fp
    ldr rdi,buffer
    mov rsi,[rbx].STRFLT.string
    mov ecx,[rbx].STRFLT.flags
    xor eax,eax
    xor edx,edx

    .while 1

        lodsb
        .break .if !al

        .if ( al == '.' )

            .break .if ( ecx & _ST_DOT )
            or ecx,_ST_DOT

        .else

            .if ( ecx & _ST_ISHEX )

                or al,0x20
                .break .if ( al < '0' || al > 'f' )
                .break .if ( al > '9' && al < 'a' )
            .else
                .break .if ( al < '0' || al > '9' )
            .endif

            .if ( ecx & _ST_DOT )

                inc sigdig
            .endif

            or ecx,_ST_DIGITS
            or edx,eax

            .continue .if ( edx == '0' ) ; if a significant digit

            .if ( digits < Q_SIGDIG )
                stosb
            .endif
            inc digits
        .endif
    .endw
    mov byte ptr [rdi],0

    ;
    ; Parse the optional exponent
    ;
    xor edx,edx
    .if ( ecx & _ST_DIGITS )

        xor edi,edi ; exponent

        .if ( ( ( ecx & _ST_ISHEX ) &&
              ( al == 'p' || al == 'P' ) ) || al == 'e' || al == 'E' )

            mov al,[rsi]
            lea rdx,[rsi-1]
            .if ( al == '+' )
                inc rsi
            .endif
            .if ( al == '-' )
                inc rsi
                or  ecx,_ST_NEGEXP
            .endif
            and ecx,not _ST_DIGITS

            .while 1

                movzx eax,byte ptr [rsi]
                .break .if ( al < '0' )
                .break .if ( al > '9' )

                .if ( edi < 100000000 ) ; else overflow

                    imul edi,edi,10
                    lea edi,[rdi+rax-'0']
                .endif
                or  ecx,_ST_DIGITS
                inc rsi
            .endw

            .if ( ecx & _ST_NEGEXP )
                neg edi
            .endif
            .if !( ecx & _ST_DIGITS )
                mov rsi,rdx
            .endif

        .else

            dec rsi ; digits found, but no e or E
        .endif

        mov edx,edi
        mov eax,sigdig
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

        .if ( digits > edi )

            add edx,digits
            mov digits,edi
            .if ( ecx & _ST_ISHEX )

                shl edi,2
            .endif
            sub edx,edi
        .endif

        .while 1

            .break .if ( digits <= 0 )
             mov edi,digits
             add rdi,buffer
            .break .if ( byte ptr [rdi-1] != '0' )

            add edx,eax
            dec digits
        .endw
    .else
        mov rsi,[rbx].string
    .endif

    mov [rbx].flags,ecx
    mov [rbx].string,rsi
    mov [rbx].exponent,edx
    mov eax,digits
    ret

_destoflt endp

    end
