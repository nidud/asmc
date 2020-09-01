; G_XMNORMALIZEA2B10G10R10.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXMath.inc

.data
g_XMNormalizeA2B10G10R10 label XMVECTORF32
    real4 1.0 / 511.0
    dd 0x36004020
    dd 0x31004020
    dd 0x2FAAAAAB
 end
