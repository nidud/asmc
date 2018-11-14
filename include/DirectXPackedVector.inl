ifndef __DIRECTXPACKEDVECTOR_INL
__DIRECTXPACKEDVECTOR_INL equ <>


inl_XMConvertFloatToHalf macro Value

    _mm_store_ps(xmm0, Value)

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
    retm<xmm0>
    endm


inl_XMConvertHalfToFloat macro Value

    _mm_store_ps(xmm0, Value)

    movd eax,xmm0
    mov ecx,eax
    mov edx,eax
    and eax,0x03FF          ;; Mantissa
    and edx,0x7C00          ;; Exponent

    .if ( edx == 0x7C00 )   ;; INF/NAN

        mov edx,0x8f

    .elseif ( edx )         ;; The value is normalized

        movzx edx,cx
        shr edx,10
        and edx,0x1F

    .elseif ( eax )         ;; The value is denormalized

        mov edx,1           ;; Normalize the value in the resulting float
        .repeat
            dec edx
            shl eax,1
        .until eax & 0x0400
        and eax,0x03FF

    .else                   ;; The value is zero

        mov edx,-112
    .endif

    and ecx,0x8000          ;; Sign
    shl ecx,16
    add edx,112             ;; Exponent
    shl edx,23
    shl eax,13              ;; Mantissa
    or  eax,edx
    or  eax,ecx
    movd xmm0,eax

    retm<xmm0>
    endm


inl_XMLoadColor macro ptr_XMCOLOR
if defined(_XM_NO_INTRINSICS_) or defined(_XM_ARM_NEON_INTRINSICS_)
elseif defined(_XM_SSE_INTRINSICS_)
    ;; Splat the color in all four entries
    movd xmm0,_mm_getptr(ptr_XMCOLOR)
    XM_PERMUTE_PS()
    ;; Shift R&0xFF0000, G&0xFF00, B&0xFF, A&0xFF000000
    _mm_and_si128(xmm0, g_XMMaskA8R8G8B8)
    ;; a is unsigned! Flip the bit to convert the order to signed
    _mm_xor_si128(xmm0, g_XMFlipA8R8G8B8)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(xmm0)
    ;; RGB + 0, A + 0x80000000.f to undo the signed order.
    _mm_add_ps(xmm0, g_XMFixAA8R8G8B8)
    ;; Convert 0-255 to 0.0f-1.0f
    _mm_mul_ps(xmm0, g_XMNormalizeA8R8G8B8)
endif
    retm<xmm0>
    endm


inl_XMLoadHalf2 macro pSource

    movzx   eax,_mm_getptr(pSource,rcx).XMHALF2.x
    movzx   edx,_mm_getptr(pSource,rcx).XMHALF2.y
    movd    xmm0,edx
    movd    xmm2,eax
    XMConvertHalfToFloat(xmm0)
    movaps  xmm1,xmm0
    XMConvertHalfToFloat(xmm2)
    shufps  xmm0,xmm1,01000100B
    shufps  xmm0,xmm0,01011000B

    retm<xmm0>
    endm


inl_XMLoadShortN2 macro ptr_XMSHORTN2
    ;; Splat the two shorts in all four entries (WORD alignment okay,
    ;; DWORD alignment preferred)
    _mm_load_ps1(_mm_getptr(ptr_XMSHORTN2))
    ;; Mask x&0xFFFF, y&0xFFFF0000,z&0,w&0
    _mm_and_ps(xmm0, g_XMMaskX16Y16)
    ;; x needs to be sign extended
    _mm_xor_ps(xmm0, g_XMFlipX16Y16)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; x - 0x8000 to undo the signed order.
    _mm_add_ps(xmm0, g_XMFixX16Y16)
    ;; Convert -1.0f - 1.0f
    _mm_mul_ps(xmm0, g_XMNormalizeX16Y16)
    ;; Clamp result (for case of -32768)
    _mm_max_ps( xmm0, g_XMNegativeOne )
    retm<xmm0>
    endm


inl_XMLoadShort2 macro ptr_XMSHORT2
    ;; Splat the two shorts in all four entries (WORD alignment okay,
    ;; DWORD alignment preferred)
    _mm_load_ps1(_mm_getptr(ptr_XMSHORT2))
    ;; Mask x&0xFFFF, y&0xFFFF0000,z&0,w&0
    _mm_and_ps(xmm0, g_XMMaskX16Y16)
    ;; x needs to be sign extended
    _mm_xor_ps(xmm0, g_XMFlipX16Y16)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; x - 0x8000 to undo the signed order.
    _mm_add_ps(xmm0, g_XMFixX16Y16)
    ;; Y is 65536 too large
    _mm_mul_ps(xmm0, g_XMFixupY16)
    retm<xmm0>
    endm


inl_XMLoadUShortN2 macro pSource
    ;; Splat the two shorts in all four entries (WORD alignment okay,
    ;; DWORD alignment preferred)
    _mm_load_ps1(_mm_getptr(pSource))
    ;; Mask x&0xFFFF, y&0xFFFF0000,z&0,w&0
    _mm_and_ps(xmm0, g_XMMaskX16Y16)
    ;; y needs to be sign flipped
    _mm_xor_ps(xmm0, g_XMFlipY)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; y + 0x8000 to undo the signed order.
    _mm_add_ps(xmm0, _mm_get_epi32(0.0, 32768.0 * 65536.0, 0.0, 0.0))
    ;; Y is 65536 times too large
    _mm_mul_ps(xmm0, _mm_get_epi32(1.0 / 65535.0, 1.0 / (65535.0 * 65536.0), 0.0, 0.0))
    retm<xmm0>
    endm


inl_XMLoadUShort2 macro pSource
    ;; Splat the two shorts in all four entries (WORD alignment okay,
    ;; DWORD alignment preferred)
    _mm_load_ps1(_mm_getptr(pSource))
    ;; Mask x&0xFFFF, y&0xFFFF0000,z&0,w&0
    _mm_and_ps(xmm0, g_XMMaskX16Y16)
    ;; y needs to be sign flipped
    _mm_xor_ps(xmm0, g_XMFlipY)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; Y is 65536 times too large
    _mm_mul_ps(xmm0, g_XMFixupY16)
    ;; y + 0x8000 to undo the signed order.
    _mm_add_ps(xmm0, _mm_get_epi32(0.0, 32768.0, 0.0, 0.0))
    retm<xmm0>
    endm


inl_XMLoadByteN2 macro pSource
    movsx eax,_mm_getptr(pSource).XMBYTEN2.x
    .if al == -128
        mov eax,-1.0
        movd xmm0,eax
    .else
        cvtsi2ss xmm0,eax
        mov eax,1.0/127.0
        movd xmm1,eax
        mulss xmm0,xmm1
    .endif
    movsx eax,_mm_getptr(pSource).XMBYTEN2.y
    .if al == -128
        mov eax,-1.0
        movd xmm1,eax
    .else
        cvtsi2ss xmm1,eax
        mov eax,1.0/127.0
        movd xmm2,eax
        mulss xmm1,xmm2
    .endif
    shufps xmm0,xmm1,01000100B
    shufps xmm0,xmm0,01011000B
    retm<xmm0>
    endm


inl_XMLoadByte2 macro pSource

    movsx   eax,_mm_getptr(pSource).XMBYTE2.x
    movsx   edx,_mm_getptr(pSource).XMBYTE2.y
    cvtsi2ss xmm0,eax
    cvtsi2ss xmm1,edx
    shufps  xmm0,xmm1,01000100B
    shufps  xmm0,xmm0,01011000B

    retm<xmm0>
    endm


inl_XMLoadUByteN2 macro pSource

    mov      eax,1.0/255.0
    movd     xmm2,eax
    movzx    eax,_mm_getptr(pSource).XMUBYTEN2.x
    cvtsi2ss xmm0,eax
    mulss    xmm0,xmm2
    movzx    eax,_mm_getptr(pSource).XMUBYTEN2.y
    cvtsi2ss xmm1,eax
    mulss    xmm1,xmm2
    shufps   xmm0,xmm1,01000100B
    shufps   xmm0,xmm0,01011000B

    retm<xmm0>
    endm


inl_XMLoadUByte2 macro pSource

    movzx    eax,_mm_getptr(pSource).XMUBYTE2.x
    cvtsi2ss xmm0,eax
    movzx    eax,_mm_getptr(pSource).XMUBYTE2.y
    cvtsi2ss xmm1,eax
    shufps   xmm0,xmm1,01000100B
    shufps   xmm0,xmm0,01011000B

    retm<xmm0>
    endm


inl_XMLoadU565 macro pSource

    movzx    eax,_mm_getptr(pSource).XMU565.v
    mov      edx,eax
    and      eax,0x1F
    cvtsi2ss xmm0,eax

    mov      eax,edx
    shr      eax,5
    and      eax,0x3F
    cvtsi2ss xmm1,eax
    shufps   xmm0,xmm1,01000100B
    shufps   xmm0,xmm0,01011000B

    shr      edx,11
    and      edx,0x1F
    cvtsi2ss xmm1,edx
    shufps   xmm0,xmm1,01000100B

    retm<xmm0>
    endm


inl_XMLoadFloat3PK macro pSource

    ;; X Channel (6-bit mantissa)

    mov eax,_mm_getptr(pSource,rcx)
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

    mov eax,_mm_getptr(pSource,rcx)
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

    mov eax,_mm_getptr(pSource,rcx)
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
            ;;
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

    retm<xmm0>
    endm


inl_XMLoadFloat3SE macro pSource

    mov      edx,_mm_getptr(pSource)
    mov      eax,edx
    shr      eax,27
    shl      eax,23
    add      eax,0x33800000
    movd     xmm2,eax

    mov      eax,edx
    and      eax,0x8FF
    cvtsi2ss xmm0,eax
    mulss    xmm0,xmm2

    mov      eax,edx
    shr      eax,9
    and      eax,0x8FF
    cvtsi2ss xmm1,eax
    mulss    xmm1,xmm2

    shufps   xmm0,xmm1,01000100B
    shufps   xmm0,xmm0,01011000B

    shr      edx,18
    and      edx,0x8FF
    cvtsi2ss xmm1,edx
    mulss    xmm1,xmm2
    movd     eax,xmm1

    mov      edx,1.0
    shl      rdx,32
    or       rax,rdx
    movq     xmm1,rax
    shufps   xmm0,xmm1,01000100B

    retm<xmm0>
    endm


inl_XMLoadHalf4 macro pSource

    movzx   eax,_mm_getptr(pSource).XMHALF4.x
    movd    xmm1,eax
    movzx   eax,_mm_getptr(pSource).XMHALF4.y
    movd    xmm2,eax
    movzx   eax,_mm_getptr(pSource).XMHALF4.z
    movd    xmm3,eax
    movzx   eax,_mm_getptr(pSource).XMHALF4.w
    movd    xmm4,eax

    movss   xmm2,XMConvertHalfToFloat(xmm2)
    movss   xmm3,XMConvertHalfToFloat(xmm3)
    movss   xmm4,XMConvertHalfToFloat(xmm4)
    XMConvertHalfToFloat(xmm1)

    shufps  xmm0,xmm2,01000100B
    shufps  xmm0,xmm0,01011000B
    shufps  xmm3,xmm4,01000100B
    shufps  xmm3,xmm3,01011000B
    shufps  xmm0,xmm3,01000100B

    retm<xmm0>
    endm

inl_XMLoadShortN4 macro pSource
    ;; Splat the color in all four entries (x,z,y,w)
    _mm_load1_pd(_mm_getptr(pSource))
    ;; Shift x&0ffff,z&0xffff,y&0xffff0000,w&0xffff0000
    _mm_and_ps(_mm_castpd_ps(xmm0), g_XMMaskX16Y16Z16W16)
    ;; x and z are unsigned! Flip the bits to convert the order to signed
    _mm_xor_ps(xmm0, g_XMFlipX16Y16Z16W16)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; x and z - 0x8000 to complete the conversion
    _mm_add_ps(xmm0, g_XMFixX16Y16Z16W16)
    ;; Convert to -1.0f - 1.0f
    _mm_mul_ps(xmm0, g_XMNormalizeX16Y16Z16W16)
    ;; Very important! The entries are x,z,y,w, flip it to x,y,z,w
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,1,2,0))
    ;; Clamp result (for case of -32768)
    _mm_max_ps( xmm0, g_XMNegativeOne )

    retm<xmm0>
    endm


inl_XMLoadShort4 macro pSource

    ;; Splat the color in all four entries (x,z,y,w)
    _mm_load1_pd(_mm_getptr(pSource))
    ;; Shift x&0ffff,z&0xffff,y&0xffff0000,w&0xffff0000
    _mm_and_ps(_mm_castpd_ps(xmm0), g_XMMaskX16Y16Z16W16)
    ;; x and z are unsigned! Flip the bits to convert the order to signed
    _mm_xor_ps(xmm0, g_XMFlipX16Y16Z16W16)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; x and z - 0x8000 to complete the conversion
    _mm_add_ps(xmm0, g_XMFixX16Y16Z16W16)
    ;; Fix y and w because they are 65536 too large
    _mm_mul_ps(xmm0, g_XMFixupY16W16)
    ;; Very important! The entries are x,z,y,w, flip it to x,y,z,w
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,1,2,0))

    retm<xmm0>
    endm


inl_XMLoadUShortN4 macro pSource
    ;; Splat the color in all four entries (x,z,y,w)
    _mm_load1_pd(_mm_getptr(pSource))
    ;; Shift x&0ffff,z&0xffff,y&0xffff0000,w&0xffff0000
    _mm_and_ps(_mm_castpd_ps(xmm0), g_XMMaskX16Y16Z16W16)
    ;; y and w are signed! Flip the bits to convert the order to unsigned
    _mm_xor_ps(xmm0, g_XMFlipZW)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; y and w + 0x8000 to complete the conversion
    _mm_add_ps(xmm0, _mm_get_epi32(0.0, 0.0, 32768.0*65536.0, 32768.0*65536.0))
    ;; Fix y and w because they are 65536 too large
    _mm_mul_ps(xmm0, _mm_get_epi32(1.0/65535.0, 1.0/65535.0, 1.0/(65535.0*65536.0), 1.0/(65535.0*65536.0)))
    ;; Very important! The entries are x,z,y,w, flip it to x,y,z,w
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,1,2,0))
    retm<xmm0>
    endm


inl_XMLoadUShort4 macro pSource
    ;; Splat the color in all four entries (x,z,y,w)
    _mm_load1_pd(_mm_getptr(pSource))
    ;; Shift x&0ffff,z&0xffff,y&0xffff0000,w&0xffff0000
    _mm_and_ps(_mm_castpd_ps(xmm0), g_XMMaskX16Y16Z16W16)
    ;; y and w are signed! Flip the bits to convert the order to unsigned
    _mm_xor_ps(xmm0, g_XMFlipZW)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; Fix y and w because they are 65536 too large
    _mm_mul_ps(xmm0, g_XMFixupY16W16)
    ;; y and w + 0x8000 to complete the conversion
    _mm_add_ps(xmm0, _mm_get_epi32(0.0, 0.0, 32768.0, 32768.0))
    ;; Very important! The entries are x,z,y,w, flip it to x,y,z,w
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,1,2,0))
    retm<xmm0>
    endm


inl_XMLoadXDecN4 macro pSource
    ;; Splat the color in all four entries
    _mm_load_ps1(_mm_getptr(pSource))
    ;; Shift R&0xFF0000, G&0xFF00, B&0xFF, A&0xFF000000
    _mm_and_ps(xmm0, g_XMMaskA2B10G10R10)
    ;; a is unsigned! Flip the bit to convert the order to signed
    _mm_xor_ps(xmm0, g_XMFlipA2B10G10R10)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; RGB + 0, A + 0x80000000.f to undo the signed order.
    _mm_add_ps(xmm0, g_XMFixAA2B10G10R10)
    ;; Convert 0-255 to 0.0f-1.0f
    _mm_mul_ps(xmm0, g_XMNormalizeA2B10G10R10)
    ;; Clamp result (for case of -512)
    _mm_max_ps( xmm0, g_XMNegativeOne )
    retm<xmm0>
    endm


inl_XMLoadXDec4 macro pSource
    ;; Splat the color in all four entries
    _mm_load_ps1(_mm_getptr(pSource))
    ;; Shift R&0xFF0000, G&0xFF00, B&0xFF, A&0xFF000000
    _mm_and_ps(xmm0, g_XMMaskDec4)
    ;; a is unsigned! Flip the bit to convert the order to signed
    _mm_xor_ps(xmm0, _mm_get_epi32(0x200, 0x200 shl 10, 0x200 shl 20, 0x80000000))
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; RGB + 0, A + 0x80000000.f to undo the signed order.
    _mm_add_ps(xmm0, _mm_get_epi32(-512.0, -512.0*1024.0, -512.0*1024.0*1024.0, 32768.0*65536.0))
    ;; Convert 0-255 to 0.0f-1.0f
    _mm_mul_ps(xmm0, g_XMMulDec4)
    retm<xmm0>
    endm


inl_XMLoadDecN4 macro pSource
    ;; Splat the color in all four entries
    _mm_load_ps1(_mm_getptr(pSource))
    ;; Shift R&0xFF0000, G&0xFF00, B&0xFF, A&0xFF000000
    _mm_and_ps(xmm0, g_XMMaskDec4)
    ;; a is unsigned! Flip the bit to convert the order to signed
    _mm_xor_ps(xmm0, g_XMXorDec4)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; RGB + 0, A + 0x80000000.f to undo the signed order.
    _mm_add_ps(xmm0, g_XMAddDec4)
    ;; Convert 0-255 to 0.0f-1.0f
    _mm_mul_ps(xmm0, _mm_get_epi32(1.0/511.0, 1.0/(511.0*1024.0), 1.0/(511.0*1024.0*1024.0), 1.0/(1024.0*1024.0*1024.0)))
    ;; Clamp result (for case of -512/-1)
    _mm_max_ps( xmm0, g_XMNegativeOne )
    retm<xmm0>
    endm


inl_XMLoadDec4 macro pSource
    ;; Splat the color in all four entries
    _mm_load_ps1(_mm_getptr(pSource))
    ;; Shift R&0xFF0000, G&0xFF00, B&0xFF, A&0xFF000000
    _mm_and_ps(xmm0, g_XMMaskDec4)
    ;; a is unsigned! Flip the bit to convert the order to signed
    _mm_xor_ps(xmm0, g_XMXorDec4)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; RGB + 0, A + 0x80000000.f to undo the signed order.
    _mm_add_ps(xmm0, g_XMAddDec4)
    ;; Convert 0-255 to 0.0f-1.0f
    _mm_mul_ps(xmm0, g_XMMulDec4)
    retm<xmm0>
    endm


inl_XMLoadUDecN4 macro pSource
    ;; Splat the color in all four entries
    _mm_load_ps1(_mm_getptr(pSource))
    ;; Shift R&0xFF0000, G&0xFF00, B&0xFF, A&0xFF000000
    _mm_and_ps(xmm0, g_XMMaskDec4)
    ;; a is unsigned! Flip the bit to convert the order to signed
    _mm_xor_ps(xmm0, g_XMFlipW)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; RGB + 0, A + 0x80000000.f to undo the signed order.
    _mm_add_ps(xmm0, g_XMAddUDec4)
    ;; Convert 0-255 to 0.0f-1.0f
    _mm_mul_ps(xmm0, _mm_get_epi32(1.0/1023.0, 1.0/(1023.0*1024.0), 1.0/(1023.0*1024.0*1024.0), 1.0/(3.0*1024.0*1024.0*1024.0)))
    retm<xmm0>
    endm


inl_XMLoadUDecN4_XR macro pSource

    mov     edx,_mm_getptr(pSource).XMUDECN4.v
    mov     eax,edx
    and     eax,0x3FF
    sub     eax,0x180
    cvtsi2ss xmm0,eax
    mov     eax,510.0
    movd    xmm2,eax
    divss   xmm0,xmm2

    mov     eax,edx
    shr     eax,10
    and     eax,0x3FF
    sub     eax,0x180
    cvtsi2ss xmm1,eax
    divss   xmm1,xmm2
    shufps  xmm0,xmm1,01000100B
    shufps  xmm0,xmm0,01011000B

    mov     eax,edx
    shr     eax,20
    and     eax,0x3FF
    sub     eax,0x180
    cvtsi2ss xmm1,eax
    divss   xmm1,xmm2

    shr     edx,30
    cvtsi2ss xmm2,edx
    mov     eax,3.0
    movd    xmm3,eax
    divss   xmm2,xmm3
    shufps  xmm1,xmm2,01000100B
    shufps  xmm1,xmm1,01011000B
    shufps  xmm0,xmm1,01000100B

    retm<xmm0>
    endm


inl_XMLoadUDec4 macro pSource
    ;; Splat the color in all four entries
    _mm_load_ps1(_mm_getptr(pSource))
    ;; Shift R&0xFF0000, G&0xFF00, B&0xFF, A&0xFF000000
    _mm_and_ps(xmm0, g_XMMaskDec4)
    ;; a is unsigned! Flip the bit to convert the order to signed
    _mm_xor_ps(xmm0, g_XMFlipW)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; RGB + 0, A + 0x80000000.f to undo the signed order.
    _mm_add_ps(xmm0, g_XMAddUDec4)
    ;; Convert 0-255 to 0.0f-1.0f
    _mm_mul_ps(xmm0, g_XMMulDec4)
    retm<xmm0>
    endm


inl_XMLoadByteN4 macro pSource
    ;; Splat the color in all four entries (x,z,y,w)
    _mm_load1_ps(_mm_getptr(pSource))
    ;; Mask x&0ff,y&0xff00,z&0xff0000,w&0xff000000
    _mm_and_ps(xmm0, g_XMMaskByte4)
    ;; x,y and z are unsigned! Flip the bits to convert the order to signed
    _mm_xor_ps(xmm0, g_XMXorByte4)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; x, y and z - 0x80 to complete the conversion
    _mm_add_ps(xmm0, g_XMAddByte4)
    ;; Fix y, z and w because they are too large
    _mm_mul_ps(xmm0, _mm_get_epi32(1.0/127.0, 1.0/(127.0*256.0), 1.0/(127.0*65536.0), 1.0/(127.0*65536.0*256.0)))
    ;; Clamp result (for case of -128)
    _mm_max_ps( xmm0, g_XMNegativeOne )
    retm<xmm0>
    endm


inl_XMLoadByte4 macro pSource
    ;; Splat the color in all four entries (x,z,y,w)
    _mm_load1_ps(_mm_getptr(pSource))
    ;; Mask x&0ff,y&0xff00,z&0xff0000,w&0xff000000
    _mm_and_ps(xmm0, g_XMMaskByte4)
    ;; x,y and z are unsigned! Flip the bits to convert the order to signed
    _mm_xor_ps(xmm0, g_XMXorByte4)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; x, y and z - 0x80 to complete the conversion
    _mm_add_ps(xmm0, g_XMAddByte4)
    ;; Fix y, z and w because they are too large
    _mm_mul_ps(xmm0, _mm_get_epi32(1.0, 1.0/256.0, 1.0/65536.0, 1.0/(65536.0*256.0)))
    retm<xmm0>
    endm


inl_XMLoadUByteN4 macro pSource
    ;; Splat the color in all four entries (x,z,y,w)
    _mm_load1_ps(_mm_getptr(pSource))
    ;; Mask x&0ff,y&0xff00,z&0xff0000,w&0xff000000
    _mm_and_ps(xmm0, g_XMMaskByte4)
    ;; w is signed! Flip the bits to convert the order to unsigned
    _mm_xor_ps(xmm0, g_XMFlipW)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; w + 0x80 to complete the conversion
    _mm_add_ps(xmm0, g_XMAddUDec4)
    ;; Fix y, z and w because they are too large
    _mm_mul_ps(xmm0, _mm_get_epi32(1.0/255.0, 1.0/(255.0*256.0), 1.0/(255.0*65536.0), 1.0/(255.0*65536.0*256.0)))
    retm<xmm0>
    endm


inl_XMLoadUByte4 macro pSource
    ;; Splat the color in all four entries (x,z,y,w)
    _mm_load1_ps(_mm_getptr(pSource))
    ;; Mask x&0ff,y&0xff00,z&0xff0000,w&0xff000000
    _mm_and_ps(xmm0, g_XMMaskByte4)
    ;; w is signed! Flip the bits to convert the order to unsigned
    _mm_xor_ps(xmm0, g_XMFlipW)
    ;; Convert to floating point numbers
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ;; w + 0x80 to complete the conversion
    _mm_add_ps(xmm0, g_XMAddUDec4)
    ;; Fix y, z and w because they are too large
    _mm_mul_ps(xmm0, _mm_get_epi32(1.0, 1.0/256.0, 1.0/65536.0, 1.0/(65536.0*256.0)))
    retm<xmm0>
    endm


inl_XMLoadUNibble4 macro pSource

    movzx   edx,_mm_getptr(pSource).XMUNIBBLE4.v
    mov     eax,edx
    and     eax,0xF
    cvtsi2ss xmm0,eax

    mov     eax,edx
    shr     eax,4
    and     eax,0xF
    cvtsi2ss xmm1,eax
    shufps  xmm0,xmm1,01000100B
    shufps  xmm0,xmm0,01011000B

    mov     eax,edx
    shr     eax,8
    and     eax,0xF
    cvtsi2ss xmm1,eax

    shr     edx,12
    and     edx,0xF
    cvtsi2ss xmm2,edx

    shufps  xmm1,xmm2,01000100B
    shufps  xmm1,xmm1,01011000B
    shufps  xmm0,xmm1,01000100B

    retm<xmm0>
    endm


inl_XMLoadU555 macro pSource

    movzx   edx,_mm_getptr(pSource).XMU555.v
    mov     eax,edx
    and     eax,0x1F
    cvtsi2ss xmm0,eax
    mov     eax,edx
    shr     eax,5
    and     eax,0x1F
    cvtsi2ss xmm1,eax
    shufps  xmm0,xmm1,01000100B
    shufps  xmm0,xmm0,01011000B
    mov     eax,edx
    shr     eax,10
    and     eax,0x1F
    cvtsi2ss xmm1,eax
    shr     edx,15
    and     edx,0x1
    cvtsi2ss xmm2,edx
    shufps  xmm1,xmm2,01000100B
    shufps  xmm1,xmm1,01011000B
    shufps  xmm0,xmm1,01000100B
    retm<xmm0>
    endm


inl_XMStoreColor macro pDestination, V
    _mm_store_ps(xmm0, V)
    ;; Set <0 to 0
    _mm_max_ps(xmm0, g_XMZero)
    ;; Set>1 to 1
    _mm_min_ps(xmm0, g_XMOne)
    ;; Convert to 0-255
    _mm_mul_ps(xmm0, _mm_get_epi32(255.0, 255.0, 255.0, 255.0))
    ;; Shuffle RGBA to ARGB
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(3,0,1,2))
    ;; Convert to int
    _mm_cvtps_epi32(xmm0)
    ;; Mash to shorts
    _mm_packs_epi32(xmm0, xmm0)
    ;; Mash to bytes
    _mm_packus_epi16(xmm0, xmm0)
    ;; Store the color
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreHalf2 macro pDestination, V
    push rbx
    mov rbx,pDestination
    XMConvertFloatToHalf(xmm1)
    mov [rbx].XMHALF2.x,ax
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0, 3, 2, 1))
    XMConvertFloatToHalf(xmm1)
    mov [rbx].XMHALF2.y,ax
    pop rbx
    exitm<>
    endm


inl_XMStoreShortN2 macro pDestination, V
    _mm_store_ps(xmm0, V)
    _mm_max_ps(xmm0, g_XMNegativeOne)
    _mm_min_ps(xmm0, g_XMOne)
    _mm_mul_ps(xmm0, _mm_get_epi32(32767.0, 32767.0, 32767.0, 32767.0))
    _mm_cvtps_epi32(xmm0)
    _mm_packs_epi32(xmm0, xmm0)
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreShort2 macro pDestination, V
    _mm_store_ps(xmm0, V)
    ;; Bounds check
    _mm_max_ps(xmm0, _mm_get_epi32(-32767.0, -32767.0, -32767.0, -32767.0))
    _mm_min_ps(xmm0, _mm_get_epi32(32767.0, 32767.0, 32767.0, 32767.0))
    ;; Convert to int with rounding
    _mm_cvtps_epi32(xmm0)
    ;; Pack the ints into shorts
    _mm_packs_epi32(xmm0, xmm0)
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreUShortN2 macro pDestination, V
    _mm_store_ps(xmm0, V)
    ;; Bounds check
    _mm_max_ps(xmm0, g_XMZero)
    _mm_min_ps(xmm0, g_XMOne)
    _mm_mul_ps(xmm0, _mm_get_epi32(65535.0, 65535.0, 65535.0, 65535.0))
    ;; Convert to int with rounding
    _mm_cvtps_epi32(xmm0)
    ;; Since the SSE pack instruction clamps using signed rules,
    ;; manually extract the values to store them to memory
    movd    edx,xmm0
    mov     _mm_getptr(pDestination).XMUSHORTN2.x,dx
    shufps  xmm0,xmm0,11100110B
    movd    edx,xmm0
    mov     _mm_getptr(pDestination).XMUSHORTN2.y,dx
    exitm<>
    endm


inl_XMStoreUShort2 macro pDestination, V
    _mm_store_ps(xmm0, V)
    ;; Bounds check
    _mm_max_ps(xmm0, g_XMZero)
    _mm_min_ps(xmm0, _mm_get_epi32(65535.0, 65535.0, 65535.0, 65535.0))
    ;; Convert to int with rounding
    _mm_cvtps_epi32(xmm0)
    ;; Since the SSE pack instruction clamps using signed rules,
    ;; manually extract the values to store them to memory
    movd    edx,xmm0
    mov     _mm_getptr(pDestination).XMUSHORT2.x,dx
    shufps  xmm0,xmm0,11100110B
    movd    edx,xmm0
    mov     _mm_getptr(pDestination).XMUSHORT2.y,dx
    exitm<>
    endm


inl_XMStoreByteN2 macro pDestination, V
    _mm_store_ps(xmm0, V)
    inl_XMVectorClamp(xmm0, g_XMNegativeOne, g_XMOne)
    inl_XMVectorMultiply(xmm0, _mm_get_epi32(127.0, 127.0, 127.0, 127.0))
    inl_XMVectorRound(xmm0)
    cvtps2dq xmm0,xmm0
    movq rdx,xmm0
    mov _mm_getptr(pDestination).XMBYTEN2.x,dl
    shr rdx,32
    mov _mm_getptr(pDestination).XMBYTEN2.y,dl
    exitm<>
    endm


inl_XMStoreByte2 macro pDestination, V

    _mm_store_ps(xmm0, V)
    _mm_store_ps(xmm1, _mm_get_epi32(-127.0, -127.0, -127.0, -127.0))
    _mm_store_ps(xmm2, _mm_get_epi32(127.0, 127.0, 127.0, 127.0))

    inl_XMVectorClamp(xmm0, xmm1, xmm2)
    inl_XMVectorRound(xmm0)
    _mm_cvtps_epi32(xmm0)
    movq rdx,xmm0
    mov _mm_getptr(pDestination).XMBYTE2.x,dl
    shr rdx,32
    mov _mm_getptr(pDestination).XMBYTE2.y,dl
    exitm<>
    endm


inl_XMStoreUByteN2 macro pDestination, V
    _mm_store_ps(xmm0, V)
    inl_XMVectorSaturate(xmm0)
    inl_XMVectorMultiplyAdd(xmm0, _mm_get_epi32(255.0, 255.0, 255.0, 255.0), g_XMOneHalf)
    inl_XMVectorTruncate(xmm0)
    _mm_cvtps_epi32(xmm0)
    movq rdx,xmm0
    mov _mm_getptr(pDestination).XMUBYTEN2.x,dl
    shr rdx,32
    mov _mm_getptr(pDestination).XMUBYTEN2.y,dl
    exitm<>
    endm


inl_XMStoreUByte2 macro pDestination, V
    _mm_store_ps(xmm0, V)
    inl_XMVectorClamp(xmm0, _mm_setzero_ps(xmm1), _mm_get_epi32(255.0, 255.0, 255.0, 255.0))
    inl_XMVectorRound(xmm0)
    _mm_cvtps_epi32(xmm0)
    movq rdx,xmm0
    mov _mm_getptr(pDestination).XMUBYTE2.x,dl
    shr rdx,32
    mov _mm_getptr(pDestination).XMUBYTE2.y,dl
    exitm<>
    endm


inl_XMStoreU565 macro pDestination, V
    _mm_store_ps(xmm0, V)
    ;; Bounds check
    _mm_max_ps(xmm0, g_XMZero)
    _mm_min_ps(xmm0, _mm_get_epi32(31.0, 63.0, 31.0, 0.0))
    ;; Convert to int with rounding
    _mm_cvtps_epi32(xmm0)
    ;; No SSE operations will write to 16-bit values, so we have to extract them manually
    movd    eax,xmm0
    and     eax,0x1F
    shufps  xmm0,xmm0,01001110B
    movd    edx,xmm0
    and     edx,0x3F
    shl     edx,5
    or      eax,edx
    movq    rdx,xmm0
    shr     rdx,32
    and     edx,0x1F
    shl     edx,11
    or      eax,edx
    mov     _mm_getptr(pDestination,rcx).XMU565.v,ax
    exitm<>
    endm


inl_XMStoreFloat3PK macro pDestination, V

    _mm_store_ps(xmm0, V)

    ;; X & Y Channels (5-bit exponent, 6-bit mantissa)
    ;; Z Channel (5-bit exponent, 5-bit mantissa)

    .for(edx=0: edx < 3: ++edx)

        movd eax,xmm0
        XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0, 3, 2, 1))
        shld r11,r10,32
        shl r10,32

        mov r8d,eax
        and r8d,0x80000000
        mov r9d,eax
        and r9d,0x7FFFFFFF

        mov eax,r9d
        and eax,0x7F800000

        .if (eax == 0x7F800000)

            ;; INF or NAN

            .if edx == 2

                mov eax,0x3E0

                .if ( r9d & 0x7FFFFF )

                    mov eax,r9d
                    shr eax,18
                    mov r8d,r9d
                    shr r8d,13
                    or  eax,r8d
                    mov r8d,r9d
                    shr r8d,3
                    or  eax,r8d
                    or  eax,r9d
                    and eax,0x1F
                    or  eax,0x3E0

                .elseif ( r8d )

                    xor eax,eax
                .endif

            .else

                mov eax,0x7C0

                .if ( r9d & 0x7FFFFF )

                    mov eax,r9d
                    shr eax,17
                    mov r8d,r9d
                    shr r8d,11
                    shr r9d,6
                    or  eax,r8d
                    or  eax,r9d
                    and eax,0x3F
                    or  eax,0x7C0

                .elseif ( r8d )

                    ;; -INF is clamped to 0 since 3PK is positive only

                    xor eax,eax
                .endif
            .endif

            or  r10,rax

        .elseif ( r8d )

            ;; 3PK is positive only, so clamp to zero

        .else

            .if edx == 2

                .if (r9d > 0x477C0000)

                    ;; The number is too large to be represented as a float10, set to max

                    mov eax,0x3DF
                    or  r10,rax

                .else

                    .if (r9d < 0x38800000)

                        ;; The number is too small to be represented as a normalized float10
                        ;; Convert it to a denormalized value.

                        mov r8,rcx
                        mov eax,r9d
                        shr eax,23
                        mov ecx,113
                        sub ecx,eax
                        and r9d,0x7FFFFF
                        or  r9d,0x800000
                        shr r9d,cl
                        mov rcx,r8

                    .else

                        ;; Rebias the exponent to represent the value as a normalized float10

                        add r9d,0xC8000000
                    .endif

                    lea rax,[r9+0x1FFFF]
                    shr r9d,18
                    and r9d,1
                    add eax,r9d
                    shr eax,18
                    and eax,0x3FF
                    or  r10,rax
                .endif

            .else

                .if (r9d > 0x477E0000)

                    ;; The number is too large to be represented as a float11, set to max

                    mov eax,0x7BF
                    or  r10,rax

                .else

                    .if (r9d < 0x38800000)

                        ;; The number is too small to be represented as a normalized float11
                        ;; Convert it to a denormalized value.

                        mov r8,rcx
                        mov eax,r9d
                        shr eax,23
                        mov ecx,113
                        sub ecx,eax
                        and r9d,0x7FFFFF
                        or  r9d,0x800000
                        shr r9d,cl
                        mov rcx,r8

                    .else

                        ;; Rebias the exponent to represent the value as a normalized float11

                        add r9d,0xC8000000
                    .endif

                    mov eax,r9d
                    shr eax,17
                    and eax,1
                    add eax,0xFFFF
                    add eax,r9d
                    shr eax,17
                    and eax,0x7FF
                    or  r10,rax
                .endif
            .endif
        .endif
    .endf

    ;; Pack Result into memory

    mov r8d,r10d
    shr r10,32
    and r11d,0x7ff
    and r10d,0x7ff
    and r8d,0x3ff
    shl r10d,11
    shl r8d,22
    or  r11d,r10d
    or  r11d,r8d
    mov _mm_getptr(pDestination).XMFLOAT3PK.v,r11d

    exitm<>
    endm


inl_XMStoreFloat3SE macro pDestination, V
    exitm<.err<Not implemented>>
    endm


inl_XMStoreHalf4 macro pDestination, V
    push rdi
    mov rdi,pDestination
    XMConvertFloatToHalf(xmm1)
    stosw
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0, 3, 2, 1))
    XMConvertFloatToHalf(xmm1)
    stosw
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0, 3, 2, 1))
    XMConvertFloatToHalf(xmm1)
    stosw
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0, 3, 2, 1))
    XMConvertFloatToHalf(xmm1)
    stosw
    pop rdi
    exitm<>
    endm


inl_XMStoreShortN4 macro pDestination, V
    _mm_store_ps(xmm0, V)
    _mm_max_ps(xmm0, g_XMNegativeOne)
    _mm_min_ps(xmm0, g_XMOne)
    _mm_mul_ps(xmm0, _mm_get_epi32(32767.0, 32767.0, 32767.0, 32767.0))
    _mm_cvtps_epi32(xmm0)
    _mm_packs_epi32(xmm0, xmm0)
    _mm_store_sd(_mm_getptr(pDestination), _mm_castsi128_pd(xmm0))
    exitm<>
    endm


inl_XMStoreShort4 macro pDestination, V
    _mm_store_ps(xmm0, V)
    ;; Bounds check
    _mm_max_ps(xmm0, _mm_get_epi32(-32767.0, -32767.0, -32767.0, -32767.0))
    _mm_min_ps(xmm0, _mm_get_epi32(32767.0, 32767.0, 32767.0, 32767.0))
    ;; Convert to int with rounding
    _mm_cvtps_epi32(xmm0)
    ;; Pack the ints into shorts
    _mm_packs_epi32(xmm0, xmm0)
    _mm_store_sd(_mm_getptr(pDestination), _mm_castsi128_pd(xmm0))
    exitm<>
    endm


inl_XMStoreUShortN4 macro pDestination, V
  local dptr
    _mm_store_ps(xmm0, V)
    ;; Bounds check
    _mm_max_ps(xmm0, g_XMZero)
    _mm_min_ps(xmm0, g_XMOne)
    _mm_mul_ps(xmm0, _mm_get_epi32(65535.0, 65535.0, 65535.0, 65535.0))
    ;; Convert to int with rounding
    _mm_cvtps_epi32(xmm0)
    ;; Since the SSE pack instruction clamps using signed rules,
    ;; manually extract the values to store them to memory
    dptr equ _mm_getptr(pDestination,rcx)
    mov dptr.XMUSHORTN4.x,_mm_extract_epi16(xmm0, 0)
    mov dptr.XMUSHORTN4.y,_mm_extract_epi16(xmm0, 2)
    mov dptr.XMUSHORTN4.z,_mm_extract_epi16(xmm0, 4)
    mov dptr.XMUSHORTN4.w,_mm_extract_epi16(xmm0, 6)
    exitm<>
    endm


inl_XMStoreUShort4 macro pDestination, V
  local dptr
    _mm_store_ps(xmm0, V)
    ;; Bounds check
    _mm_max_ps(xmm0, g_XMZero)
    _mm_min_ps(xmm0, _mm_get_epi32(65535.0, 65535.0, 65535.0, 65535.0))
    ;; Convert to int with rounding
    _mm_cvtps_epi32(xmm0)
    ;; Since the SSE pack instruction clamps using signed rules,
    ;; manually extract the values to store them to memory
    dptr equ _mm_getptr(pDestination,rcx)
    mov dptr.XMUSHORT4.x,_mm_extract_epi16(xmm0, 0)
    mov dptr.XMUSHORT4.y,_mm_extract_epi16(xmm0, 2)
    mov dptr.XMUSHORT4.z,_mm_extract_epi16(xmm0, 4)
    mov dptr.XMUSHORT4.w,_mm_extract_epi16(xmm0, 6)
    exitm<>
    endm


inl_XMStoreXDecN4 macro pDestination, V
    _mm_store_ps(xmm0, V)
    ; XMXDECN4
    _mm_max_ps(xmm0, _mm_get_epi32(-1.0, -1.0, -1.0, 0.0))
    _mm_min_ps(xmm0, g_XMOne)
    ;; Scale by multiplication
    _mm_mul_ps(xmm0, _mm_get_epi32(511.0, 511.0*1024.0, 511.0*1048576.0, 3.0*536870912.0))
    ;; Convert to int (W is unsigned)
    _mm_cvtps_epi32(xmm0)
    ;; Mask off any fraction
    _mm_and_si128(xmm0, _mm_get_epi32(0x3FF, 0x3FF shl 10, 0x3FF shl 20, 0x3 shl 29))
    ;; To fix W, add itself to shift it up to <<30 instead of <<29
    _mm_and_si128(_mm_store_ps(xmm1, xmm0), g_XMMaskW)
    _mm_add_epi32(xmm0, xmm1)
    ;; Do a horizontal or of all 4 entries
    _mm_store_ps(xmm1, xmm0)
    XM_PERMUTE_PS(_mm_castsi128_ps(xmm1), _MM_SHUFFLE(0,3,2,1))
    _mm_or_si128(xmm0, _mm_castps_si128(xmm1))
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0,3,2,1))
    _mm_or_si128(xmm0, _mm_castps_si128(xmm1))
    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0,3,2,1))
    _mm_or_si128(xmm0, _mm_castps_si128(xmm1))
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreXDec4 macro pDestination, V
    _mm_store_ps(xmm1, V)
    ;; Clamp to bounds
    _mm_max_ps(xmm1, _mm_get_epi32(-511.0, -511.0, -511.0, 0.0))
    _mm_min_ps(xmm1, _mm_get_epi32(511.0, 511.0, 511.0, 3.0))
    ;; Scale by multiplication
    _mm_mul_ps(xmm1, _mm_get_epi32(1.0, 1024.0/2.0, 1024.0*1024.0, 1024.0*1024.0*1024.0/2.0))
    ;; Convert to int
    _mm_cvttps_epi32(xmm1)
    ;; Mask off any fraction
    _mm_and_si128(xmm1, _mm_get_epi32(0x3FF, 0x3FF shl (10-1), 0x3FF shl 20, 0x3 shl (30-1)))
    ;; Do a horizontal or of 4 entries
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(3,2,3,2))
    ;; x = x|z, y = y|w
    _mm_or_si128(xmm1, xmm0)
    ;; Move Z to the x position
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(1,1,1,1))
    ;; Perform a single bit left shift on y|w
    _mm_add_epi32(xmm0, xmm0)
    ;; i = x|y|z|w
    _mm_or_si128(xmm0, xmm1)
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreDecN4 macro pDestination, V
    _mm_store_ps(xmm1, V)
    ;; Clamp to bounds
    _mm_max_ps(xmm1, g_XMNegativeOne)
    _mm_min_ps(xmm1, g_XMOne)
    ;; Scale by multiplication
    _mm_mul_ps(xmm1, _mm_get_epi32(511.0, 511.0*1024.0, 511.0*1024.0*1024.0, 1.0*1024.0*1024.0*1024.0))
    ;; Convert to int
    _mm_cvttps_epi32(xmm1)
    ;; Mask off any fraction
    _mm_and_si128(xmm1, _mm_get_epi32(0x3FF, 0x3FF shl 10, 0x3FF shl 20, 0x3 shl 30))
    ;; Do a horizontal or of 4 entries
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(3,2,3,2))
    ;; x = x|z, y = y|w
    _mm_or_si128(xmm1, xmm0)
    ;; Move Z to the x position
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(1,1,1,1))
    ;; i = x|y|z|w
    _mm_or_si128(xmm0, xmm1)
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreDec4 macro pDestination, V
    _mm_store_ps(xmm1, V)
    ;; Clamp to bounds
    _mm_max_ps(xmm1, _mm_get_epi32(-511.0, -511.0, -511.0, -1.0))
    _mm_min_ps(xmm1, _mm_get_epi32(511.0, 511.0, 511.0, 1.0))
    ;; Scale by multiplication
    _mm_mul_ps(xmm1, _mm_get_epi32(1.0, 1024.0, 1024.0*1024.0, 1024.0*1024.0*1024.0))
    ;; Convert to int
    _mm_cvttps_epi32(xmm1)
    ;; Mask off any fraction
    _mm_and_si128(xmm1, _mm_get_epi32(0x3FF, 0x3FF shl 10, 0x3FF shl 20, 0x3 shl 30))
    ;; Do a horizontal or of 4 entries
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(3,2,3,2))
    ;; x = x|z, y = y|w
    _mm_or_si128(xmm1, xmm0)
    ;; Move Z to the x position
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm1, _MM_SHUFFLE(1,1,1,1))
    ;; i = x|y|z|w
    _mm_or_si128(xmm0, xmm1)
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreUDecN4 macro pDestination, V
    _mm_store_ps(xmm1, V)
    ;; Clamp to bounds
    _mm_max_ps(xmm1, g_XMZero)
    _mm_min_ps(xmm1, g_XMOne)
    ;; Scale by multiplication
    _mm_mul_ps(xmm1, _mm_get_epi32(1023.0, 1023.0*1024.0*0.5, 1023.0*1024.0*1024.0, 3.0*1024.0*1024.0*1024.0*0.5))
    ;; Convert to int
    _mm_cvttps_epi32(xmm1)
    ;; Mask off any fraction
    _mm_and_si128(xmm1, _mm_get_epi32(0x3FF, 0x3FF shl (10-1), 0x3FF shl 20, 0x3 shl (30-1)))
    ;; Do a horizontal or of 4 entries
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(3,2,3,2))
    ;; x = x|z, y = y|w
    _mm_or_si128(xmm1, xmm0)
    ;; Move Z to the x position
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(1,1,1,1))
    ;; Perform a left shift by one bit on y|w
    _mm_add_epi32(xmm0, xmm0)
    ;; i = x|y|z|w
    _mm_or_si128(xmm0, xmm1)
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreUDecN4_XR macro pDestination, V
    _mm_store_ps(xmm0, V)
    inl_XMVectorMultiplyAdd( xmm0, _mm_get_epi32(510.0, 510.0, 510.0, 3.0), _mm_get_epi32(384.0, 384.0, 384.0, 0.0) )
    inl_XMVectorClamp( xmm0, g_XMZero, _mm_get_epi32(1023.0, 1023.0, 1023.0, 3.0) )
    _mm_extract_epi16(xmm0, 0)
    and eax,0x3FF
    mov edx,eax
    _mm_extract_epi16(xmm0, 2)
    and eax,0x3FF
    shl eax,10
    or  edx,eax
    _mm_extract_epi16(xmm0, 4)
    and eax,0x3FF
    shl eax,20
    or  edx,eax
    _mm_extract_epi16(xmm0, 6)
    shl eax,30
    or  edx,eax
    mov _mm_getptr(pDestination),edx
    exitm<>
    endm


inl_XMStoreUDec4 macro pDestination, V
    _mm_store_ps(xmm1, V)
    ;; Clamp to bounds
    _mm_max_ps(xmm1, g_XMZero)
    _mm_min_ps(xmm1, _mm_get_epi32(1023.0, 1023.0, 1023.0, 3.0))
    ;; Scale by multiplication
    _mm_mul_ps(xmm1, _mm_get_epi32(1.0, 1024.0/2.0, 1024.0*1024.0, 1024.0*1024.0*1024.0/2.0))
    ;; Convert to int
    _mm_cvttps_epi32(xmm1)
    ;; Mask off any fraction
    _mm_and_si128(xmm1, _mm_get_epi32(0x3FF, 0x3FF shl (10-1), 0x3FF shl 20, 0x3 shl (30-1)))
    ;; Do a horizontal or of 4 entries
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(3,2,3,2))
    ;; x = x|z, y = y|w
    _mm_or_si128(xmm1, xmm0)
    ;; Move Z to the x position
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(1,1,1,1))
    ;; Perform a left shift by one bit on y|w
    _mm_add_epi32(xmm0, xmm0)
    ;; i = x|y|z|w
    _mm_or_si128(xmm0, xmm1)
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreByteN4 macro pDestination, V
    _mm_store_ps(xmm1, V)
    ;; Clamp to bounds
    _mm_max_ps(xmm1, g_XMNegativeOne)
    _mm_min_ps(xmm1, g_XMOne)
    ;; Scale by multiplication
    _mm_mul_ps(xmm1, _mm_get_epi32(127.0, 127.0*256.0, 127.0*256.0*256.0, 127.0*256.0*256.0*256.0))
    ;; Convert to int
    _mm_cvttps_epi32(xmm1)
    ;; Mask off any fraction
    _mm_and_si128(xmm1, _mm_get_epi32(0xFF, 0xFF shl 8, 0xFF shl 16, 0xFF shl 24))
    ;; Do a horizontal or of 4 entries
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(3,2,3,2))
    ;; x = x|z, y = y|w
    _mm_or_si128(xmm1, xmm0)
    ;; Move Z to the x position
    _mm_store_ps(xmm0, xmm1)
    _mm_shuffle_epi32(xmm0, _MM_SHUFFLE(1,1,1,1))
    ;; i = x|y|z|w
    _mm_or_si128(xmm0, xmm1)
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreByte4 macro pDestination, V
    _mm_store_ps(xmm1, V)
    ;; Clamp to bounds
    _mm_max_ps(xmm1, _mm_get_epi32(-127.0, -127.0, -127.0, -127.0))
    _mm_min_ps(xmm1, _mm_get_epi32(127.0, 127.0, 127.0, 127.0))
    ;; Scale by multiplication
    _mm_mul_ps(xmm1, _mm_get_epi32(1.0, 256.0, 256.0*256.0, 256.0*256.0*256.0))
    ;; Convert to int
    _mm_cvttps_epi32(xmm1)
    ;; Mask off any fraction
    _mm_and_si128(xmm1, _mm_get_epi32(0xFF, 0xFF shl 8, 0xFF shl 16, 0xFF shl 24))
    ;; Do a horizontal or of 4 entries
    _mm_shuffle_epi32(_mm_store_ps(xmm0, xmm1), _MM_SHUFFLE(3,2,3,2))
    ;; x = x|z, y = y|w
    _mm_or_si128(xmm1, xmm0)
    ;; Move Z to the x position
    _mm_shuffle_epi32(_mm_store_ps(xmm0, xmm1), _MM_SHUFFLE(1,1,1,1))
    ;; i = x|y|z|w
    _mm_or_si128(xmm0, xmm1)
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreUByteN4 macro pDestination, V
    _mm_store_ps(xmm1, V)
    ;; Clamp to bounds
    _mm_max_ps(xmm1, g_XMZero)
    _mm_min_ps(xmm1, g_XMOne)
    ;; Scale by multiplication
    _mm_mul_ps(xmm1, _mm_get_epi32(255.0, 255.0*256.0*0.5, 255.0*256.0*256.0, 255.0*256.0*256.0*256.0*0.5))
    ;; Convert to int
    _mm_cvttps_epi32(xmm1)
    ;; Mask off any fraction
    _mm_and_si128(xmm1, _mm_get_epi32(0xFF, 0xFF shl (8-1), 0xFF shl 16, 0xFF shl (24-1)))
    ;; Do a horizontal or of 4 entries
    _mm_shuffle_epi32(_mm_store_ps(xmm0, xmm1), _MM_SHUFFLE(3,2,3,2))
    ;; x = x|z, y = y|w
    _mm_or_si128(xmm1, xmm0)
    ;; Move Z to the x position
    _mm_shuffle_epi32(_mm_store_ps(xmm0, xmm1), _MM_SHUFFLE(1,1,1,1))
    ;; Perform a single bit left shift to fix y|w
    _mm_add_epi32(xmm0, xmm0)
    ;; i = x|y|z|w
    _mm_or_si128(xmm0, xmm1)
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreUByte4 macro pDestination, V
    _mm_store_ps(xmm1, V)
    ;; Clamp to bounds
    _mm_max_ps(xmm1, g_XMZero)
    _mm_min_ps(xmm1, _mm_get_epi32(255.0, 255.0, 255.0, 255.0))
    ;; Scale by multiplication
    _mm_mul_ps(xmm1, _mm_get_epi32(1.0, 256.0*0.5, 256.0*256.0, 256.0*256.0*256.0*0.5))
    ;; Convert to int
    _mm_cvttps_epi32(xmm1)
    ;; Mask off any fraction
    _mm_and_si128(xmm1, _mm_get_epi32(0xFF, 0xFF shl (8-1), 0xFF shl 16, 0xFF shl (24-1)))
    ;; Do a horizontal or of 4 entries
    _mm_shuffle_epi32(_mm_store_ps(xmm0, xmm1), _MM_SHUFFLE(3,2,3,2))
    ;; x = x|z, y = y|w
    _mm_or_si128(xmm1, xmm0)
    ;; Move Z to the x position
    _mm_shuffle_epi32(_mm_store_ps(xmm0, xmm1), _MM_SHUFFLE(1,1,1,1))
    ;; Perform a single bit left shift to fix y|w
    _mm_add_epi32(xmm0, xmm0)
    ;; i = x|y|z|w
    _mm_or_si128(xmm0, xmm1)
    _mm_store_ss(_mm_getptr(pDestination), _mm_castsi128_ps(xmm0))
    exitm<>
    endm


inl_XMStoreUNibble4 macro pDestination, V
    _mm_store_ps(xmm1, V)
    ;; Bounds check
    _mm_max_ps(xmm1, g_XMZero)
    _mm_min_ps(xmm1, _mm_get_epi32(15.0, 15.0, 15.0, 15.0))
    ;; Convert to int with rounding
    _mm_cvtps_epi32(xmm1)
    ;; No SSE operations will write to 16-bit values, so we have to extract them manually
    _mm_extract_epi16(xmm1, 0)
    and eax,0xF
    mov edx,eax
    _mm_extract_epi16(xmm1, 2)
    and eax,0xF
    shl eax,4
    or  edx,eax
    _mm_extract_epi16(xmm1, 4)
    and eax,0xF
    shl eax,8
    or  edx,eax
    _mm_extract_epi16(xmm1, 6)
    and eax,0xF
    shl eax,12
    or  edx,eax
    mov _mm_getptr(pDestination),dx
    exitm<>
    endm


inl_XMStoreU555 macro pDestination, V
    _mm_store_ps(xmm1, V)
    ;; Bounds check
    _mm_max_ps(xmm1, g_XMZero)
    _mm_min_ps(xmm1, _mm_get_epi32(31.0, 31.0, 31.0, 1.0))
    ;; Convert to int with rounding
    _mm_cvtps_epi32(xmm1)
    ;; No SSE operations will write to 16-bit values, so we have to extract them manually
    _mm_extract_epi16(xmm1, 0)
    and eax,0x1F
    mov edx,eax
    _mm_extract_epi16(xmm1, 2)
    and eax,0x1F
    shl eax,5
    or  edx,eax
    _mm_extract_epi16(xmm1, 4)
    and eax,0x1F
    shl eax,10
    or  edx,eax
    _mm_extract_epi16(xmm1, 6)
    neg eax
    sbb eax,eax
    and eax,0x8000
    or  edx,eax
    mov _mm_getptr(pDestination).XMU555.v,dx
    exitm<>
    endm

endif
