; G_BOXOFFSET.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXCollision.inc

.data
g_BoxOffset XMVECTORF32 \
    { { { -1.0, -1.0,  1.0, 0.0 } } },
    { { {  1.0, -1.0,  1.0, 0.0 } } },
    { { {  1.0,  1.0,  1.0, 0.0 } } },
    { { { -1.0,  1.0,  1.0, 0.0 } } },
    { { { -1.0, -1.0, -1.0, 0.0 } } },
    { { {  1.0, -1.0, -1.0, 0.0 } } },
    { { {  1.0,  1.0, -1.0, 0.0 } } },
    { { { -1.0,  1.0, -1.0, 0.0 } } }

    end
