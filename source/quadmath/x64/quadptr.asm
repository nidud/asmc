; QUADPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

__mulq proc a:ptr, b:ptr
    movups xmm0,[rcx]
    movups xmm1,[rdx]
    mulq(xmm0, xmm1)
    mov rax,a
    movups [rax],xmm0
    ret
__mulq endp

__divq proc a:ptr, b:ptr
    movups xmm0,[rcx]
    movups xmm1,[rdx]
    divq(xmm0, xmm1)
    mov rax,a
    movups [rax],xmm0
    ret
__divq endp

__addq proc a:ptr, b:ptr
    movups xmm0,[rcx]
    movups xmm1,[rdx]
    addq(xmm0, xmm1)
    mov rax,a
    movups [rax],xmm0
    ret
__addq endp

__subq proc a:ptr, b:ptr
    movups xmm0,[rcx]
    movups xmm1,[rdx]
    subq(xmm0, xmm1)
    mov rax,a
    movups [rax],xmm0
    ret
__subq endp

__cvtq_h proc a:ptr, b:ptr
    movups xmm0,[rdx]
    cvtq_h(xmm0)
    mov rax,a
    movups [rax],xmm0
    ret
__cvtq_h endp

__cvtq_ss proc a:ptr, b:ptr
    movups xmm0,[rdx]
    cvtq_ss(xmm0)
    mov rax,a
    movups [rax],xmm0
    ret
__cvtq_ss endp

__cvtq_sd proc a:ptr, b:ptr
    movups xmm0,[rdx]
    cvtq_sd(xmm0)
    mov rax,a
    movups [rax],xmm0
    ret
__cvtq_sd endp

__cvtq_ld proc a:ptr, b:ptr
    movups xmm0,[rdx]
    cvtq_ld(xmm0)
    mov rax,a
    movups [rax],xmm0
    ret
__cvtq_ld endp

__cvth_q proc a:ptr, b:ptr
    movd xmm0,[rdx]
    cvth_q(xmm0)
    mov rax,a
    movups [rax],xmm0
    ret
__cvth_q endp

__cvtss_q proc a:ptr, b:ptr
    movd xmm0,[rdx]
    cvtss_q(xmm0)
    mov rax,a
    movups [rax],xmm0
    ret
__cvtss_q endp

__cvtsd_q proc a:ptr, b:ptr
    movq xmm0,[rdx]
    cvtsd_q(xmm0)
    mov rax,a
    movups [rax],xmm0
    ret
__cvtsd_q endp

__cvtld_q proc a:ptr, b:ptr
    movups xmm0,[rdx]
    cvtld_q(xmm0)
    mov rax,a
    movups [rax],xmm0
    ret
__cvtld_q endp

__cvti32_q proc a:ptr, l:int_t
    cvti32_q(ecx)
    mov rax,a
    movups [rax],xmm0
    ret
__cvti32_q endp

__cvti64_q proc a:ptr, ll:int64_t
    cvti64_q(rcx)
    mov rax,a
    movups [rax],xmm0
    ret
__cvti64_q endp

__cvtq_i32 proc a:ptr
    movups xmm0,[rcx]
    cvtq_i32(xmm0)
    ret
__cvtq_i32 endp

__cvtq_i64 proc a:ptr
    movups xmm0,[rcx]
    cvtq_i64(xmm0)
    ret
__cvtq_i64 endp

__cvta_q proc a:ptr, string:string_t, endptr:ptr string_t
    mov rcx,rdx
    cvta_q(rcx, r8)
    mov rax,a
    movups [rax],xmm0
    ret
__cvta_q endp

    end
