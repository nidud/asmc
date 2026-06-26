;
; v2.33 - FASTCALL :vararg in ELF64
;
    .code

    option win64:auto

p1  proc fastcall string:ptr sbyte, argptr:vararg

    nop
    ret

p1  endp


    end
