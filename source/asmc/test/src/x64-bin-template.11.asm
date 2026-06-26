
    ; 2.32.44 - duplicated names

   .code

    option casemap:none, win64:auto

.template T
    double real8 ?
   .inline double { retm<[rcx].T.double> }
   .ends

main proc
   .new a:ptr T
    mov rax,a.double()
    ret
    endp

    end
