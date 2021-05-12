;
; v2.27 - added .COMDEF <Name>
;
ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    option win64:2
    PVOID typedef ptr

.comdef Class

    Method1 proc :ptr
    Method2 proc :ptr

    .ends

    assume rcx:ptr Class

foo proc

  local p:ptr Class

    [rcx].Method1(rdx)
    [rcx].Method2(rdx)
    ret

foo endp

    end

