Asmc Macro Assembler Reference

## .SWITCH

**.SWITCH** [[ JMP ]] [[ C | PASCAL ]] [[ _expression_ ]]

The switch exists in three variants:

- Structured switch (Pascal): selects exactly one branch; each [.CASE](dot-case.md) directive is a closed branch.
- Unstructured switch (C, default): behaves like a C switch. Each .CASE directive is a label and the .CASE directives are not closed, so execution falls through into the next .CASE until a [.ENDC](dot-endc.md) statement.
- Control-table switch (no arguments): the _expression_ of each .CASE directive is evaluated at runtime. Otherwise, similar to the unstructured switch.

The **JMP** option skips the range-test in the jump code.






#### See Also

[Conditional Control Flow](conditional-control-flow.md) | [Option Switch](option-switch.md)
