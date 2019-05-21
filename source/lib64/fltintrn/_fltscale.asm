; _FLTSCALE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include quadmath.inc
include intrin.inc

    .code

    assume rbx:ptr STRFLT

_fltscale proc uses rsi rdi rbx fp:ptr STRFLT

  local factor:__m128i
  local signed:int_t

    mov rbx,rcx
    mov edi,[rbx].exponent
    .ifs ( edi > 4096 )

        __mulq([rbx].mantissa, &_Q_1E4096)
        sub edi,4096

    .elseif ( sdword ptr edi < -4096 )

        __divq([rbx].mantissa, &_Q_1E4096)
        add edi,4096
    .endif

    .if edi

        xor eax,eax
        mov signed,eax
        mov factor.m128i_u64[0],rax
        mov factor.m128i_u32[8],eax
        mov factor.m128i_u32[12],0x3FFF0000 ; 1.0

        .ifs ( edi < 0 )
            neg edi
            inc signed
        .endif
        .if ( edi >= 8192 )
            mov edi,8192
        .endif

        .for ( rsi = &_Q_1E1 : edi : edi >>= 1, rsi += 16 )

            .if ( edi & 1 )

                __mulq(&factor, rsi)
            .endif
        .endf

        .if signed
            __divq([rbx].mantissa, &factor)
        .else
            __mulq([rbx].mantissa, &factor)
        .endif
    .endif
    ret

_fltscale endp

    end
