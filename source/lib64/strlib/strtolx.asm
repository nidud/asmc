;
; '128'         - long
; '128 C:\file' - long
; '100h'        - hex
; 'f3 22'       - hex
;
include stdlib.inc
include strlib.inc

    .code

strtolx proc string:string_t

    mov rdx,rcx ; string

    .repeat

        mov al,[rdx]
        inc rdx

        .break .if !al
        .break .if al == ' '

        .continue(0) .if al <= '9'

        xtol(rcx)
        ret

    .until 1

    atol(rcx)
    ret

strtolx endp

    end
