
    ; 2.33.14 - Assign float value to qword

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option win64:3

    .code

foo proc

   .new a:real8 = -1
   .new b:real8 = 2.0 / 2.0
   .new q:qword = -1.0
    ret

foo endp

    end
