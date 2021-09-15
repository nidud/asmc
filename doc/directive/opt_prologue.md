Asmc Macro Assembler Reference

### OPTION PROLOGUE

**OPTION PROLOGUE**:[NONE|PROLOGUEDEF|_macroname_]

    OPTION PROLOGUE:macroname

Instructs the assembler to call the _macroname_ to generate a user-defined prologue instead of the standard prologue code when a RET instruction is encountered.

    OPTION PROLOGUE:PROLOGUEDEF

Revert to the standard prologue code.

    OPTION PROLOGUE:None

Completely suppress prologue generation.

In this case, no user-defined macro is called, and the assembler does not generate a default code sequence. This state remains in effect until the next OPTION PROLOGUE is encountered.

#### See Also

[Directives Reference](readme.md) | [OPTION EPILOGUE](opt_epilogue.md)