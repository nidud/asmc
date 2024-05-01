Asmc Macro Assembler Reference

## SEGMENT

name **SEGMENT** [[READONLY]] [[align]] [[combine]] [[use]] [['class']]

statements

name ENDS

Defines a program segment called name having segment attributes align (BYTE, WORD, DWORD, PARA, PAGE), combine (PUBLIC, STACK, COMMON, MEMORY, AT address, PRIVATE), use (USE16, USE32, FLAT), and class.

#### See Also

[Directives Reference](readme.md)