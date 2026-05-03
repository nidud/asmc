Asmc Macro Assembler Reference

## .PUSHFRAME

Generates a UWOP_PUSH_MACHFRAME unwind code entry. If the optional code is specified, the unwind code entry is given a modifier of 1. Otherwise the modifier is 0.

.PUSHFRAME allows users to specify how a frame function unwinds and is only allowed within the prologue, which extends from the PROC FRAME declaration to the .ENDPROLOG directive. These directives do not generate code; they only generate **.xdata** and **.pdata**. .PUSHFRAME should be preceded by instructions that actually implement the actions to be unwound. It is a good practice to wrap both the unwind directives and the code they are meant to unwind in a macro to ensure agreement.

#### See Also

[x64](x64.md) | [Directives Reference](readme.md)
