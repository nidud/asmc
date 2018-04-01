;
; v2.27 - added .CLASSDEF <Name> [args]
;
    .x64
    .model flat, fastcall
    .code

    option win64:2

.classdef Class :byte, :ptr

; 00 lpVtbl LPCLASSVtbl ?

    base    db ?
    Method1 proc local

; 00 Release proc -- lpVtbl[0]

    Method2 proc :ptr

    .ends

    assume rcx:LPCLASS

foo proc

  local p:LPCLASS

    [rcx].Method1()
    [rcx].Method2(rdx)
    [rcx].Release()
    ret

foo endp

    end
