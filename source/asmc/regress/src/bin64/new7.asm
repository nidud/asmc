
    ; 2.33.52 - Assign qfloat/ldouble value

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option win64:3

    .code

foo proc

   .new a:real16 = xmm0
   .new b:real16 = 16.0 / 2.0
   .new c:real10 = 10.0 / 2.0
    ret

foo endp

    end
