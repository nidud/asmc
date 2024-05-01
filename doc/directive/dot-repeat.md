Asmc Macro Assembler Reference

### .REPEAT

**.REPEAT**

_statements_

**.UNTIL** _condition_

Generates code that repeats execution of the block of _statements_ until _condition_ becomes true. [.UNTILCXZ](dot-untilcxz.md), which becomes true when CX is zero, may be substituted for .UNTIL. The _condition_ is optional with **.UNTILCXZ**.

#### See Also

[Directives Reference](readme.md) | [Signed compare](signed-compare.md) | [Return code](return-code.md)