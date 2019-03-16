; _ALLOCA64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

    .code

    option win64:rsp nosave noauto

_alloca64 proc byte_count:uint_t, res_stack:uint_t

    mov rax,[rsp]   ; return addres
    add rsp,8       ; start of call
    add rcx,rdx     ; reserved stack

    .while rcx > _PAGESIZE_

        sub  rsp,_PAGESIZE_
        test [rsp],eax
        sub  rcx,_PAGESIZE_
    .endw

    sub  rsp,rcx
    and  rsp,-(_GRANULARITY)
    test [rsp],eax
    mov  rcx,rax
    lea  rax,[rsp+rdx]
    jmp  rcx

_alloca64 endp

    end
