;
; v2.27 - .if[d|w|b] ( foo() & imm ) -- test rax,imm --> test eax,emm
;
ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

foo proc
    ret
foo endp

bar proc

    .ifd foo() & 1
    .endif
    .ifw foo() & 1
    .endif
    .ifb foo() & 1
    .endif
    ret

bar endp

    end