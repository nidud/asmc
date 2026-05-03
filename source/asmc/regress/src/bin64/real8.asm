;
; v2.27 - bug using real8 0.0 as argument -- asin(0.0)
;       - allow movq rax,xmm0

ifndef __ASMC64__
    .x64
    .model flat
endif
    .code

    mov  rax,real8 ptr 0.0
    movq rax,xmm0

    end
