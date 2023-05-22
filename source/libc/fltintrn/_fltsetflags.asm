; _FLTSETFLAGS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc

    .code

    assume rdi: ptr STRFLT

_fltsetflags proc __ccall uses rsi rdi fp:ptr STRFLT, string:string_t, flags:uint_t

    ldr rdi,fp
    ldr rsi,string
    ldr ecx,flags

    xor eax,eax
ifdef _WIN64
    mov [rdi].mantissa.l,rax
    mov [rdi].mantissa.h,rax
else
    mov dword ptr [rdi].mantissa.l[0],eax
    mov dword ptr [rdi].mantissa.l[4],eax
    mov dword ptr [rdi].mantissa.h[0],eax
    mov dword ptr [rdi].mantissa.h[4],eax
endif
    mov [rdi].mantissa.e,ax
    mov [rdi].exponent,eax
    or  ecx,_ST_ISZERO

    .repeat

        lodsb
        .break .if ( al == 0 )
        .continue(0) .if ( al == ' ' || ( al >= 9 && al <= 13 ) )

        dec rsi
        and ecx,not _ST_ISZERO
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
                mov [rdi].mantissa.e,0xFFFF
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
                    .if ( al == ')' )
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

   .return( ecx )

_fltsetflags endp

    end
