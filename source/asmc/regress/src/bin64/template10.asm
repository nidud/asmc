
    ; 2.32.44 - duplicated names

ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    option casemap:none, win64:auto

.template T
    double real8 ?
   .inline double { retm<[rcx].T.double> }
   .ends

    .code

main proc

  .new a:ptr T

    mov rax,a.double()
    ret

main endp

    end
