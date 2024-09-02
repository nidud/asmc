; XMLOADFLOAT3PK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadFloat3PK proc XM_CALLCONV pSource:ptr XMFLOAT3PK

    ldr rcx,pSource

    ;; X Channel (6-bit mantissa)

    mov eax,[rcx]
    mov edx,eax
    and edx,0x3F        ; pSource->xm (Mantissa)
    shr eax,6           ; pSource->xe (Exponent)
    and eax,0x1f

    .if ( eax == 0x1f ) ;; INF or NAN

        shl edx,17
        or  edx,0x7f800000
        mov eax,edx

    .else

        .if ( eax )

            ;; The value is normalized


        .elseif ( edx )

            ;; The value is denormalized

            ;; Normalize the value in the resulting float

            mov eax,1

            .repeat

                dec eax
                shl edx,1
            .until edx & 0x40

            and edx,0x3F

        .else

            ;; The value is zero

            mov eax,-112
        .endif

        add eax,112
        shl eax,23
        shl edx,17
        or  eax,edx

    .endif
    movd xmm0,eax

    ;; Y Channel (6-bit mantissa)

    mov eax,[rcx]
    mov edx,eax
    shr edx,11      ; pSource->ym (Mantissa)
    and edx,0x3F
    shr eax,17      ; pSource->ye (Exponent)
    and eax,0x1F

    .if ( eax == 0x1f ) ;; INF or NAN

        shl edx,17
        mov eax,0x7f800000
        or  eax,edx

    .else

        .if ( eax )

            ;; The value is normalized

        .elseif ( edx )

            ;; The value is denormalized

            ;; Normalize the value in the resulting float

            mov eax,1

            .repeat

                dec eax
                shl edx,1
            .until (edx & 0x40)

            and edx,0x3F

        .else

            ;; The value is zero

            mov eax,-112
        .endif

        add eax,112
        shl eax,23
        shl edx,17
        or  eax,edx

    .endif

    movd    xmm1,eax
    shufps  xmm0,xmm1,01000100B
    shufps  xmm0,xmm0,01011000B

    ;; Z Channel (5-bit mantissa)

    mov eax,[rcx]
    mov edx,eax
    shr edx,22          ; pSource->zm (Mantissa)
    and edx,0x1F
    shr eax,27
    and eax,0x1F        ; pSource->ze (Exponent)

    .if ( eax == 0x1f ) ;; INF or NAN

        shl edx,17
        mov eax,0x7f800000
        or  eax,edx

    .else

        .if ( eax )

            ;; The value is normalized

        .elseif ( edx )

            ;; The value is denormalized
            ;;
            ;; Normalize the value in the resulting float

            mov eax,1
            .repeat
                dec eax
                shl edx,1
            .until (edx & 0x20)
            and edx,0x1F

        .else

            ;; The value is zero

            mov eax,-112
        .endif

        add eax,112
        shl eax,23
        shl edx,18
        or  eax,edx

    .endif
    movd    xmm1,eax
    shufps  xmm0,xmm1,01000100B
    ret

XMLoadFloat3PK endp

    end
