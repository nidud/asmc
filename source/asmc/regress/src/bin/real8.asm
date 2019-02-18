;
; v2.27 - bug using real8 0.0 as argument -- asin(0.0)
;       - allow movq rax,xmm0

    .x64
    .model flat
    .code

    mov  rax,real8 ptr 0.0
    movq rax,xmm0

    end
