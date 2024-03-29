;
; v2.27 - added .CLASS <Name> [args]
;
ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    option win64:2

.class Class

; 00 lpVtbl ptr ClassVtbl ?

    base    db ?
    Method1 proc local

; 00  -- lpVtbl[0]

    Release proc
    Method2 proc :ptr

    .ends

    assume rcx:ptr Class

foo proc

  local p:ptr Class

    [rcx].Method1()
    [rcx].Method2(rdx)
    [rcx].Release()
    ret

foo endp

    end
