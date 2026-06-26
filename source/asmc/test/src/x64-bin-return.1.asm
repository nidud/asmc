;
; v2.30 .return directive
;
    .code

    T struct
      b    db ?
      w    dw ?
      d    dd ?
    T ends

bar proc
    ret
    endp

foo proc x:sdword
    ret
    endp

main proc
    .return
    .return 0
    .return [rdx].T.b
    .return [rdx].T.w
    .return [rdx].T.d
    .return foo(bar())
    .return .if eax
    .return .if bar()
    .return foo(1) .if bar() > 3
    ret
    endp

    end
