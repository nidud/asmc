Asmc Macro Assembler Reference

## .SAVEREG

Generates either a UWOP_SAVE_NONVOL or a UWOP_SAVE_NONVOL_FAR unwind code entry for the specified register (reg) and offset (offset) using the current prologue offset. MASM will choose the most efficient encoding.

**.SAVEREG** _reg_, _offset_

.SAVEREG allows Asmc users to specify how a frame function unwinds and is only allowed within the prologue, which extends from the PROC FRAME declaration to the .ENDPROLOG directive. These directives do not generate code; they only generate .xdata and .pdata. .SAVEREG should be preceded by instructions that actually implement the actions to be unwound. It is a good practice to wrap both the unwind directives and the code they are meant to unwind in a macro to ensure agreement.

#### See Also

[x64](x64.md) | [Directives Reference](readme.md)
