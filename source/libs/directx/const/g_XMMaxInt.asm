; G_XMMAXINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXMath.inc

.data
g_XMMaxInt XMVECTORF32 { { { 65536.0*32768.0 - 128.0, 65536.0*32768.0 - 128.0, 65536.0*32768.0 - 128.0, 65536.0*32768.0 - 128.0 } } }

 end
