Asmc Macro Assembler Reference

## .PUSHREG

Generates a UWOP_PUSH_NONVOL unwind code entry for the specified register number using the current offset in the prologue.

**.PUSHREG** register

.PUSHREG allows users to specify how a frame function unwinds, and is only allowed within the prologue, which extends from the PROC FRAME declaration to the [.ENDPROLOG](dot_endprolog.md) directive. These directives do not generate code; they only generate .xdata and .pdata. .PUSHREG should be preceded by instructions that actually implement the actions to be unwound. It is a good practice to wrap both the unwind directives and the code they are meant to unwind in a macro to ensure agreement.

#### See Also

[Directives Reference](readme.md)
