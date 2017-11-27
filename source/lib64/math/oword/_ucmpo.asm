; _ucmpo() - Unsigned Compare
;
; Subtracts destination value from source without saving results.
; Updates flags based on the subtraction.
;
; Modifies flags: ZF CF (OF,SF,PF,AF undefined)
;
include intn.inc

option win64:rsp nosave noauto

.code

_ucmpo proc a:ptr, b:ptr

    mov rax,[rcx+8]
    sub rax,[rdx+8]
    .ifz
        mov rax,[rcx]
        sub rax,[rdx]
    .endif
    ret

_ucmpo endp

    end
