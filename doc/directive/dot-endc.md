Asmc Macro Assembler Reference

## .ENDC

.ENDC closes a .CASE statement.

The name was separated from BREAK to have more flexibility with regards to control flow of loops. However, ENDC have the same qualities as BREAK and thus can be used in combination with .IF:

```
	.ENDC .IF al == 2
```

#### See Also

[.SWITCH](dot-switch.md) | [.CASE](dot-case.md) | [.DEFAULT](dot-default.md) | [.GOTOSW](dot-gotosw.md) | [.ENDSW](dot-endsw.md)
