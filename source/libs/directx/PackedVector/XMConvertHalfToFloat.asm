; XMCONVERTHALFTOFLOAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMConvertHalfToFloat proc XM_CALLCONV Value:HALF

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
    ret

XMConvertHalfToFloat endp

    end
