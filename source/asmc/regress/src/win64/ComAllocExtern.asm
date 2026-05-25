
; v2.39 - allow external members

    option casemap:none, win64:auto

.class A
    foo proc ; external A_foo
   .ends
.class B : public A
    bar proc ; external B_bar
   .ends
.class N : public B
   N proc
   my_local proc
   my_extern proc
  .ends

malloc proto :dword

    .code

N::my_local proc
    ret
    endp

N::N proc
    @ComAlloc(N)
    ret
    endp

main proc
   .new p:ptr N()
    ret
    endp

    end
