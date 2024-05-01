Asmc Macro Assembler Reference

## .ENDC

.ENDC closes a [.CASE](dot-case.md) statement.

The name was separated from [.BREAK](dot-break.md) to have more flexibility with regards to control flow of loops. However, .ENDC have the same qualities as [.BREAK](dot-break.md) and thus can be used in combination with [.IF](dot-if.md):

- .ENDC [.IF](dot-if.md) ( al == 2 )


#### See Also

[Conditional Control Flow](conditional-control-flow.md)
