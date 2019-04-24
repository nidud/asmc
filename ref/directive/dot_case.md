Asmc Macro Assembler Reference

## .CASE

Case opens a case statement. The case statement compares the value of an ordinal expression to each selector, which can be a constant, a subrange, or a list of them separated by commas.

The selector field is separated from action field by Colon or a new line.

	.CASE 1: mov ax,2 : .ENDC
	.CASE 2
	      mov ax,3
	      .ENDC
	.CASE al
	.CASE 0,1,4,7
	.CASE 0..9

In the control table switch .CASE is equal to .IF:

	.CASE al
	.CASE ax <= 2 && !bx

#### See Also

[.SWITCH](dot_switch.md) | [.ENDC](dot_endc.md) | [.DEFAULT](dot_default.md) | [.ENDSW](dot_endsw.md)