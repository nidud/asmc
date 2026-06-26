
    ; constructor

    option casemap:none
    option win64:auto

.class C
    C proc :dword
   .ends

.data
 x C (4) dup(<>)

.code

main proc
    C(0)
    ret
    endp

C::C proc val:dword
    ret
    endp

    end
