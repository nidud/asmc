Asmc Macro Assembler Reference

### .REPEAT

**.REPEAT**<br>
   _statements_<br>
 **.UNTIL** _condition_

Generates code that repeats execution of the block of _statements_ until _condition_ becomes true. [.UNTILCXZ](dot_untilcxz.md), which becomes true when CX is zero, may be substituted for .UNTIL. The _condition_ is optional with **.UNTILCXZ**.

#### See Also

[Directives Reference](readme.md) | [Signed compare](signed.md) | [Return code](return.md)