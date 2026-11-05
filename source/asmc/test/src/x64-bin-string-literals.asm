
; v2.40.13: Numeric & Advanced Escape Sequences
;
; - Hexadecimal Escape Sequence: \x
; - Universal Character Names:   \u, \U

foo proto asmcall :ptr {}

.code
bar proc
    foo("\x")           ; sbyte "x",0
    foo("\x1")          ; sbyte 0x1,0
    foo("\x22")         ; sbyte 0x22,0
    foo("\x333")        ; sbyte 0x33,"3",0
    foo("\x4444")       ; sbyte 0x44,"44",0
    foo(L"\x")          ; dw "x",0
    foo(L"\x1")         ; dw 0x1,0
    foo(L"\x22")        ; dw 0x22,0
    foo(L"\x333")       ; dw 0x333,0
    foo(L"\x4444")      ; dw 0x4444,0
    foo(L"\x55555")     ; dw 0x5555,"5",0
    foo(L"\U")          ; dw "U",0
    foo(L"\U1")         ; dw 0x1,0x0,0
    foo(L"\U12")        ; dw 0x12,0x0,0
    foo(L"\U123")       ; dw 0x123,0x0,0
    foo(L"\U1234")      ; dw 0x1234,0x0,0
    foo(L"\U12345")     ; dw 0x2345,0x1,0
    foo(L"\U123456")    ; dw 0x3456,0x12,0
    foo(L"\U1234567")   ; dw 0x4567,0x123,0
    foo(L"\U12345678")  ; dw 0x5678,0x1234,0
    foo(L"\U123456789") ; dw 0x5678,0x1234,"9",0
    ret
    endp
    end

