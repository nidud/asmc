Asmc Macro Assembler Reference

## .BREAK

.**BREAK**(_n_) [[.**IF** _condition_]]

Generates code to terminate a [.WHILE](dot-while.md) or [.REPEAT](dot-repeat.md) block if _condition_ is true.

**BREAK**[(_n_)] is optional nesting level to terminate.

```
    .while 1
        .break              ; break .while 1
        .while 2
            .break(1)       ; break .while 1
            .while 3
                .break(2)   ; break .while 1
                .while 4
                    .break(3)   ; break .while 1
                    .break(2)   ; break .while 2
                    .break(1)   ; break .while 3
                .endw
            .endw
        .endw
    .endw
```

#### See Also

[Directives Reference](readme.md) | [.CONTINUE](dot-continue.md)
