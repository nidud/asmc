; PI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

option floatdigits:31

x = 3.0
y = 1.0
p = x
e = 1.0e-30

While ( x gt e )
    x = x * y / ((y + 1.0) * 4.0)
    y = y + 2.0
    p = p + x / y
    endm
ifdef _WIN64
%echo @CatStr(<64-bit: >, %p)
else
%echo @CatStr(<32-bit: >, %p)
endif
echo pi:     3.1415926535897932384626433832795

end
