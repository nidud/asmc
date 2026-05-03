Asmc Macro Assembler Reference

## IF

**IF** _expression1_

_if-statements_

[[**ELSEIF** _expression2_

_elseif-statements_]]

[[**ELSE**

_else-statements_]]

**ENDIF**

Grants assembly of _if-statements_ if _expression1_ is true (nonzero) or _elseif-statements_ if _expression1_ is false (0) and _expression2_ is true. The following directives may be substituted for ELSEIF: ELSEIFB, ELSEIFDEF, ELSEIFDIF, ELSEIFDIFI, ELSEIFE, ELSEIFIDN, ELSEIFIDNI, ELSEIFNB, and ELSEIFNDEF. Optionally, assembles elsestatements if the previous expression is false. Note that the expressions are evaluated at assembly time.

#### See Also

[Conditional Assembly](conditional-assembly.md) | [Directives Reference](readme.md)
