; XMVECTORSHIFTLEFT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorShiftLeft proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR, Elements:uint32_t

    .assert( r8d < 4 )

    XMVectorPermute(xmm0, xmm1, r8d, &[r8+1], &[r8+2], &[r8+3])
    ret

XMVectorShiftLeft endp

    end
