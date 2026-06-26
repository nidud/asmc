
    ; 2.33.14 - Assign float value to qword

    option win64:3

.code

foo proc
   .new a:real8 = -1
   .new b:real8 = 2.0 / 2.0
   .new q:qword = -1.0
    ret
    endp

    end
