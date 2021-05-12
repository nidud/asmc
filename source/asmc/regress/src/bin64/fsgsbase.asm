;
; v2.31.11
;
ifndef __ASMC64__
    .x64
    .model flat
endif
    .code

    rdfsbase rax
    rdgsbase rax
    wrfsbase rax
    wrgsbase rax

    wrfsbase rcx
    wrgsbase rdx
    rdfsbase rbx
    rdgsbase rbx

    end
