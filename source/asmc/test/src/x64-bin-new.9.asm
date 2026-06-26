
    ; 2.37.21 - Assign array

    option win64:3

    .code

foo proc
    ret
    endp

bar proc
   .new a[3]:real4  = { 1.0, foo(), foo() }
   .new b[3]:real8  = { foo(), foo(), foo() }
   .new c[3]:real16 = { foo(), foo(), foo() }
   .new q[3]:qword  = { foo(), foo(), foo() }
    ret
    endp

    end
