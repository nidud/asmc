
    ; 2.37.21 - Assign array

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif

    option win64:3

    .code

foo proc
    ret
foo endp

bar proc
   .new a[3]:real4  = { foo(), foo(), foo() }
   .new b[3]:real8  = { foo(), foo(), foo() }
   .new c[3]:real16 = { foo(), foo(), foo() }
   .new q[3]:qword  = { foo(), foo(), foo() }
    ret
bar endp

    end
