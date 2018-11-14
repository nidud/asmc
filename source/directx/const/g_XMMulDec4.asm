; G_XMMULDEC4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXMath.inc

.data
g_XMMulDec4 XMVECTORF32 { { { 1.0, 1.0 / 1024.0, 1.0 / (1024.0*1024.0), 1.0 / (1024.0*1024.0*1024.0) } } }

 end
