Asmc Macro Assembler Reference

## .REPEAT

_statements_

[**.UNTIL**](dot-until.md) _condition_

Generates code that repeats execution of the block of _statements_ until _condition_ becomes true. [.UNTILCXZ](dot-untilcxz.md), which becomes true when CX is zero, may be substituted for .UNTIL. The _condition_ is optional with **.UNTILCXZ**.

#### See Also

[Conditional Control Flow](conditional-control-flow.md)
