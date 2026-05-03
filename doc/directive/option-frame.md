Asmc Macro Assembler Reference

## OPTION FRAME

**OPTION FRAME**:[AUTO|NOAUTO|ADD]

This is only valid in 64-bit, and causes ASMC to generate a function table entry in .pdata and unwind information in .xdata for a function's structured exception handling unwind behavior.

When the FRAME attribute is used, it must be followed by an [.ENDPROLOG](dot-endprolog.md) directive.

The option AUTO automatically generate epilogues for procedures with the FRAME attribute.

ADD will auto add unwind information for all procedures regardless if the FRAME attribute is used or not. It will also set the option AUTO.

#### See Also

[Option](option.md) | [Directives Reference](readme.md) | [Asmc Command-Line Reference](../command/readme.md)
