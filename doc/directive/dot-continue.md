Asmc Macro Assembler Reference

## .CONTINUE

**.CONTINUE**[([0]1..n)] [[**.IF** _condition_]]

Generates code to jump to the top of a [.WHILE](dot_while.md) or [.REPEAT](dot_repeat.md) block if _condition_ is true.

**.CONTINUE**[(1..n)] is optional nesting level to continue.

```
    .while 1
        .continue                   ; continue .while 1
        .while 2
            .continue(1)            ; continue .while 1
            .while 3
                .continue(2)        ; continue .while 1
                .while 4
                    .continue(3)    ; continue .while 1
                    .continue(2)    ; continue .while 2
                    .continue(1)    ; continue .while 3
                .endw
            .endw
        .endw
    .endw
```

**.CONTINUE**[(0[1..n])] jump's directly to START label: no TEST.

```
    .while 1
        .continue(0)    ; Jump to START label
        .continue       ; Jump to START label
    .endw
    .while eax
        .continue(0)    ; Jump to START label
        .continue       ; Jump to TEST label
    .endw
    .repeat
        .continue(0)    ; Jump to START label
        .continue       ; Jump to EXIT label
        .break          ; Jump to EXIT label
    .until 1
```

#### See Also

[Conditional Control Flow](conditional-control-flow.md)

