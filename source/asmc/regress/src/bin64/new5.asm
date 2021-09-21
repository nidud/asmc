
    ; 2.33.04 - Assign const value to qword > 32-bit

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option win64:3

    .code

foo proc

   .new a:qword = -1
   .new b:qword = 0x40000000
   .new q:qword = 0x4000000000000000
    ret

foo endp

    end
