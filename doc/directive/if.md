Asmc Macro Assembler Reference

### IF

**IF** _expression1_
   _ifstatements_
   [[**ELSEIF** _expression2_
      _elseifstatements_]]
   [[**ELSE**
      _elsestatements_]]
   **ENDIF**

Grants assembly of _ifstatements_ if _expression1_ is true (nonzero) or _elseifstatements_ if _expression1_ is false (0) and _expression2_ is true.

The following directives may be substituted for ELSEIF: ELSEIFB, ELSEIFDEF, ELSEIFDIF, ELSEIFDIFI, ELSEIFE, ELSEIFIDN, ELSEIFIDNI, ELSEIFNB, and ELSEIFNDEF. Optionally, assembles elsestatements if the previous expression is false. Note that the expressions are evaluated at assembly time.

#### See Also

[Directives Reference](readme.md)