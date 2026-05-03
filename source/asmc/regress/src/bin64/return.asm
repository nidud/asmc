;
; v2.30 .return directive
;
ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
    .code

    T struct
      b    db ?
      w    dw ?
      d    dd ?
    T ends

bar proc
    ret
bar endp

foo proc x:sdword
    ret
foo endp

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

main endp

    end
