Asmc Macro Assembler Reference

## .CASE

    .case [[`<name>`]] expression

Case opens a case statement. The case statement compares the value of an ordinal expression to each selector, which can be a constant, a subrange, or a list of them separated by commas.

The selector field is separated from action field by Colon or a new line.

    .case 1: mov ax,2 : .endc
    .case 2
	  mov ax,3
	  .endc
    .case al
    .case 0,1,4,7
    .case 0..9

In the control table switch .CASE is equal to .IF:

    .case al
    .case ax <= 2 && !bx

Name is optional global name for the case label.

#### See Also

[.SWITCH](dot_switch.md) | [.ENDC](dot_endc.md) | [.DEFAULT](dot_default.md) | [.ENDSW](dot_endsw.md)