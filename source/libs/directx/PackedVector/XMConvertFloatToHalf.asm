; XMCONVERTFLOATTOHALF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMConvertFloatToHalf proc XM_CALLCONV Value:float

    movd eax,xmm0
    mov edx,eax
    shr edx,16
    and edx,0x8000
    and eax,0x7FFFFFFF

    .if ( eax > 0x477FE000 )

        ;; The number is too large to be represented as a half.  Saturate to infinity.

        mov ecx,eax
        and ecx,0x7F800000
        .if ( ( ecx == 0x7F800000 ) && ( eax & 0x7FFFFF ) )

            mov eax,0x7FFF ;; NAN
        .else
            mov eax,0x7C00 ;; INF
        .endif

    .else

        .if ( eax < 0x38800000 )

            ;; The number is too small to be represented as a normalized half.
            ;; Convert it to a denormalized value.

            mov ecx,113
            mov r8d,eax
            shr r8d,23
            sub ecx,r8d

            ;and eax,0x7FFFFF
            or  eax,0x800000
            shr eax,cl

        .else

            ;; Rebias the exponent to represent the value as a normalized half.
            add eax,0xC8000000
        .endif

        mov ecx,eax
        shr ecx,13
        and ecx,1
        add eax,ecx
        add eax,0x0FFF
        shr eax,13
        and eax,0x7FFF
    .endif
    or eax,edx
    movd xmm0,eax
    ret

XMConvertFloatToHalf endp

    end
