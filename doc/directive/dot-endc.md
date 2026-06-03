Asmc Macro Assembler Reference

## .ENDC

**.ENDC [[ ( _level_ ) ]] [[ .IF ( _expression_ ) ]]**

.ENDC is a directive that marks the end of a [.CASE](dot-case.md) statement. It is used to indicate that the current case block has ended and control should be transferred to the end of the [.SWITCH](dot-switch.md) statement.

_level_ is an optional parameter that specifies the level of nesting for the switch statement. If not specified, it defaults to 0, indicating that it ends the current case block.

#### See Also

[Conditional Control Flow](conditional-control-flow.md)
