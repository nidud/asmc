
; v2.41.03: proper handling for High/Low surrogate

foo proto asmcall :ptr {}

.code
bar proc
    foo(L"\U10FFFF")    ; no error (max)
    foo(L"\U123456")    ; error A2156: constant value out of range
    foo(L"\U1234567")   ; ..
    foo(L"\U12345678")  ; ..
    foo(L"\U123456789") ; ..
    ret
    endp
    end

