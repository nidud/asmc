; _cmpow() - Signed Compare
;
; Subtracts destination value from source without saving results.
; Updates flags based on the subtraction.
;
; Modifies flags: OF SF ZF CF (PF,AF undefined)
;
include intn.inc
include limits.inc

option win64:rsp nosave noauto

.code

_cmpow proc a:ptr, b:ptr

    mov rax,[rcx]
    sub rax,[rdx]
    .ifz
        mov rax,[rcx+8]
        sub rax,[rdx+8]
    .else
        mov rax,[rcx+8]
        sbb rax,[rdx+8]
        .ifz
            .ifo
                .ifnc
                    mov eax,INT_MIN
                    sub eax,INT_MAX
                .endif
            .else
                inc eax
            .endif
        .endif
    .endif
    ret

_cmpow endp

    end
