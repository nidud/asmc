Asmc Macro Assembler Reference

## .IF

**.IF** _condition1_

_statements_

[[**.ELSEIF** _condition2_

_statements_]]

[[**.ELSE**

_statements_]]

**.ENDIF**


Generates code that tests _condition1_ (for example, AX > 7) and executes the _statements_ if that condition is true. If a .ELSE follows, its statements are executed if the original condition was false. Note that the conditions are evaluated at run time.

#### See Also

[Conditional Control Flow](conditional-control-flow.md)
