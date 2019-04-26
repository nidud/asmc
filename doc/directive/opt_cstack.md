Asmc Macro Assembler Reference

## OPTION CSTACK

**OPTION CSTACK**:[ ON | OFF ]

The **CSTACK** option change the stack frame creation on a [PROC](proc.md) entry if the **USES** clause is used. If set the registers will be pushed before the stack frame is created and popped after the stack is restored. The default setting is OFF.

#### See Also

[Directives Reference](readme.md)