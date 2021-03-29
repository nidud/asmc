
    ; template: inline argument count

    .x64
    .model flat, fastcall

    option casemap:none
    option win64:auto

.template constructor

    atom byte ?

    .inline constructor :abs, :abs, :abs {
        nop
        ifnb <_3>
            nop
        endif
        }

    Release proc

    .ends

    .code

main proc

    .new c:constructor(1, 2.0)

    ret

main endp

    end
