; _FLTSETFLAGS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

    assume edi: ptr STRFLT

_fltsetflags proc uses esi edi fp:ptr STRFLT, string:string_t, flags:uint_t

    mov edi,fp
    mov esi,string
    xor eax,eax
    mov [edi],eax
    mov [edi+4],eax
    mov [edi+8],eax
    mov [edi+12],eax
    mov [edi+16],ax
    mov [edi].exponent,eax
    mov ecx,flags
    or  ecx,_ST_ISZERO

    .repeat

        lodsb
        .break .if ( al == 0 )
        .continue(0) .if ( al == ' ' || ( al >= 9 && al <= 13 ) )
        dec esi

        mov ecx,flags
        .if ( al == '+' )

            inc esi
            or  ecx,_ST_SIGN
        .endif

        .if ( al == '-' )

            inc esi
            or  ecx,_ST_SIGN or _ST_NEGNUM
        .endif

        lodsb
        .break .if !al

        or al,0x20
        .if ( al == 'n' )

            mov ax,[esi]
            or  ax,0x2020

            .if ( ax == 'na' )

                add esi,2
                or  ecx,_ST_ISNAN
                mov [edi].mantissa.e,0xFFFF
                movzx eax,byte ptr [esi]

                .if ( al == '(' )

                    lea edx,[esi+1]
                    mov al,[edx]
                    .switch
                      .case al == '_'
                      .case al >= '0' && al <= '9'
                      .case al >= 'a' && al <= 'z'
                      .case al >= 'A' && al <= 'Z'
                        inc edx
                        mov al,[edx]
                        .gotosw
                    .endsw
                    .if al == ')'

                        lea esi,[edx+1]
                    .endif
                .endif
            .else
                dec esi
                or ecx,_ST_INVALID
            .endif
            .break
        .endif

        .if ( al == 'i' )

            mov ax,[esi]
            or  ax,0x2020

            .if ( ax == 'fn' )

                add esi,2
                or ecx,_ST_ISINF
            .else
                dec esi
                or ecx,_ST_INVALID
            .endif
            .break
        .endif

        .if ( al == '0' )

            mov al,[esi]
            or  al,0x20
            .if ( al == 'x' )

                or  ecx,_ST_ISHEX
                add esi,2
            .endif
        .endif
        dec esi

    .until 1

    mov [edi].flags,ecx
    mov [edi].string,esi
    mov eax,ecx
    ret

_fltsetflags endp

    end
