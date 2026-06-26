
;--- this caused a GPF in v2.11 - v2.13
;--- because the FLAT group triggers a fixup creation,
;--- but in codegen.c it isn't always checked if the fixup
;--- has an associated symbol.

;--- another issue: if -bin option was used, the offsets
;--- (41ah & 41ch) were overwritten by 0! See bin.c, DoFixup()

    .386
    .model flat

    .code

main proc c
    mov ax,flat:[41ah]
    cmp ax,flat:[41ch]	;<-caused a crash
    ret
main endp

    end
