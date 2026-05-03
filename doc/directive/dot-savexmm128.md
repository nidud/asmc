Asmc Macro Assembler Reference

## .SAVEXMM128

Generates either a UWOP_SAVE_XMM128 or a UWOP_SAVE_XMM128_FAR unwind code entry for the specified XMM register and offset using the current prologue offset.

**.SAVEXMM128** _xmmreg_, _offset_

.SAVEXMM128 allows Asmc users to specify how a frame function unwinds, and is only allowed within the prologue, which extends from the PROC FRAME declaration to the .ENDPROLOG directive. These directives do not generate code; they only generate .xdata and .pdata. .SAVEXMM128 should be preceded by instructions that actually implement the actions to be unwound. It is a good practice to wrap both the unwind directives and the code they are meant to unwind in a macro to ensure agreement.

_offset_ must be a multiple of 16.

#### See Also

[x64](x64.md) | [Directives Reference](readme.md)
