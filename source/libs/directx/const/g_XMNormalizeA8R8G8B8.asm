; G_XMNORMALIZEA8R8G8B8.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXMath.inc

.data
g_XMNormalizeA8R8G8B8 label XMVECTORF32
    dd 0x33808081
    dd 0x37808081
    real4 1.0 / 255.0
    dd 0x2F808081
 end
