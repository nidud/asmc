Asmc Macro Assembler Reference

### OPTION EPILOGUE

**OPTION EPILOGUE**:[FLAGS|NONE|EPILOGUEDEF|_macroname_]

    OPTION EPILOGUE:macroname

Instructs the assembler to call the _macroname_ to generate a user-defined epilogue instead of the standard epilogue code when a RET instruction is encountered.

    OPTION EPILOGUE:EPILOGUEDEF

Revert to the standard epilogue code.

    OPTION EPILOGUE:None

Completely suppress epilogue generation.

In this case, no user-defined macro is called, and the assembler does not generate a default code sequence. This state remains in effect until the next OPTION EPILOGUE is encountered.

#### See Also

[Directives Reference](readme.md) | [OPTION PROLOGUE](opt_prologue.md)