; _FLTSETFLAGS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

    assume rdi: ptr STRFLT

_fltsetflags proc uses rsi rdi fp:ptr STRFLT, string:string_t, flags:uint_t

    mov rdi,rcx
    mov rsi,rdx
    xor eax,eax
    mov rdx,[rdi].mantissa
    mov [rdx],rax
    mov [rdx+8],rax
    mov [rdi].exponent,eax
    mov ecx,r8d
    or  ecx,_ST_ISZERO

    .repeat

        lodsb
        .break .if ( al == 0 )
        .continue(0) .if ( al == ' ' || ( al >= 9 && al <= 13 ) )
        dec rsi

        mov ecx,r8d
        .if ( al == '+' )

            inc rsi
            or  ecx,_ST_SIGN
        .endif

        .if ( al == '-' )

            inc rsi
            or  ecx,_ST_SIGN or _ST_NEGNUM
        .endif

        lodsb
        .break .if !al

        or al,0x20
        .if ( al == 'n' )

            mov ax,[rsi]
            or  ax,0x2020

            .if ( ax == 'na' )

                add rsi,2
                or  ecx,_ST_ISNAN
                mov rdx,[rdi].mantissa
                mov eax,0x7FFF
                .if ecx & _ST_NEGNUM
                    or eax,0x8000
                .endif
                mov [rdx+14],ax
                movzx eax,byte ptr [rsi]

                .if ( al == '(' )

                    lea rdx,[rsi+1]
                    mov al,[rdx]
                    .switch
                      .case al == '_'
                      .case al >= '0' && al <= '9'
                      .case al >= 'a' && al <= 'z'
                      .case al >= 'A' && al <= 'Z'
                        inc rdx
                        mov al,[rdx]
                        .gotosw
                    .endsw
                    .if al == ')'

                        lea rsi,[rdx+1]
                    .endif
                .endif
            .else
                dec rsi
                or  ecx,_ST_INVALID
            .endif
            .break
        .endif

        .if ( al == 'i' )

            mov ax,[rsi]
            or  ax,0x2020

            .if ( ax == 'fn' )

                add rsi,2
                or  ecx,_ST_ISINF
            .else
                dec rsi
                or  ecx,_ST_INVALID
            .endif
            .break
        .endif

        .if ( al == '0' )

            mov al,[rsi]
            or  al,0x20
            .if ( al == 'x' )

                or  ecx,_ST_ISHEX
                add rsi,2
            .endif
        .endif
        dec rsi

    .until 1

    mov [rdi].flags,ecx
    mov [rdi].string,rsi
    mov eax,ecx
    ret

_fltsetflags endp

    end
