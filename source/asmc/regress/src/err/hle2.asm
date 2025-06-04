;
; v2.36.36 - XACQUIRE and XRELEASE prefix
;
ifndef __ASMC64__
    .x64
    .model flat
endif
.code

    XRELEASE CMP [rcx],rax      ; error
    XACQUIRE CMP [rcx],rax      ; error
    XRELEASE MOV [rcx],rax      ; ok
    XACQUIRE MOV [rcx],rax      ; error
    XACQUIRE LOCK MOV [rcx],rax ; error

    end
