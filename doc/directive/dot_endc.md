Asmc Macro Assembler Reference

## .ENDC

.ENDC closes a .CASE statement.

The name was separated from BREAK to have more flexibility with regards to control flow of loops. However, ENDC have the same qualities as BREAK and thus can be used in combination with .IF:

	.ENDC .IF al == 2

#### See Also

[.SWITCH](dot_switch.md) | [.CASE](dot_case.md) | [.DEFAULT](dot_default.md) | [.GOTOSW](dot_gotosw.md) | [.ENDSW](dot_endsw.md)
