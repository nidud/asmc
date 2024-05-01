Asmc Macro Assembler Reference

## OPTION WSTRING

OPTION WSTRING:[ ON | OFF ]

This toggles ascii/unicode string creation of "quoted strings".

Unicode strings may be used in the [@CStr](../symbol/at-cstr.md) macro, in function calls, or decleared using:

- DW "string",0

The default value is OFF. The command-line switch [/ws](../command/readme.md) turns this option ON.

#### See Also

[Option](option.md) | [Directives Reference](readme.md)
