;
; v2.27 - .if[d|w|b] ( foo() & imm ) -- test rax,imm --> test eax,emm
;
    .x64
    .model flat, fastcall
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