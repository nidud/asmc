; G_XMNORMALIZEX16Y16Z16W16.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXMath.inc

.data
g_XMNormalizeX16Y16Z16W16 XMVECTORF32 { { { 1.0 / 32767.0, 1.0 / 32767.0, 1.0 / (32767.0*65536.0), 1.0 / (32767.0*65536.0) } } }

 end
