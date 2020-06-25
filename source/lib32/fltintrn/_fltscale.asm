; _FLTSCALE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fltintrn.inc
include quadmath.inc
include intrin.inc

    .data

    ; Assembler version independent hard values

    table real16 \
        40024000000000000000000000000000r,
        40059000000000000000000000000000r,
        400C3880000000000000000000000000r,
        40197D78400000000000000000000000r,
        40341C37937E08000000000000000000r,
        40693B8B5B5056E16B3BE04000000000r,
        40D384F03E93FF9F4DAA797ED6E38ED6r,
        41A827748F9301D319BF8CDE66D86D62r,
        435154FDD7F73BF3BD1BBB77203731FDr,
        46A3C633415D4C1D238D98CAB8A978A0r,
        4D4892ECEB0D02EA182ECA1A7A51E316r,
        5A923D1676BB8A7ABBC94E9A519C6535r,
        752588C0A40514412F3592982A7F0095r,
        7FFF0000000000000000000000000000r

    .code

    assume ebx:ptr STRFLT

_fltscale proc uses esi edi ebx fp:ptr STRFLT

  local factor:__m128i
  local signed:int_t

    mov ebx,fp
    mov edi,[ebx].exponent
    .ifs ( edi > 4096 )

        __mulq([ebx].mantissa, &table[12*16])
        sub edi,4096

    .elseif ( sdword ptr edi < -4096 )

        __divq([ebx].mantissa, &table[12*16])
        add edi,4096
    .endif

    .if edi

        xor eax,eax
        mov signed,eax
        mov factor.m128i_u32[0],eax
        mov factor.m128i_u32[4],eax
        mov factor.m128i_u32[8],eax
        mov factor.m128i_u32[12],0x3FFF0000 ; 1.0

        .ifs ( edi < 0 )
            neg edi
            inc signed
        .endif
        .if ( edi >= 8192 )
            mov edi,8192
        .endif

        .for ( esi = &table : edi : edi >>= 1, esi += 16 )

            .if ( edi & 1 )

                __mulq(&factor, esi)
            .endif
        .endf

        .if signed
            __divq([ebx].mantissa, &factor)
        .else
            __mulq([ebx].mantissa, &factor)
        .endif
    .endif
    ret

_fltscale endp

    end
