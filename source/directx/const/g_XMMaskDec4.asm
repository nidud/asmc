; G_XMMASKDEC4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXMath.inc

.data
g_XMMaskDec4 XMVECTORI32 { { { 0x3FF, 0x3FF shl 10, 0x3FF shl 20, 0x3 shl 30 } } }

 end
