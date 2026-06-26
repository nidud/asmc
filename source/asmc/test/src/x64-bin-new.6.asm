
    ; 2.33.04 - Assign const value to qword > 32-bit

    option win64:3

.code

foo proc
   .new a:qword = -1
   .new b:qword = 0x40000000
   .new q:qword = 0x4000000000000000
    ret
    endp

    end
