Asmc Macro Assembler Reference

## operator LT

**_expression1_ LT _expression2_**


Returns true (-1) if _expression1_ is less than _expression2_, or returns false (0) if it is not.

_* Non ML compatible usage_

```assembly
    a = -1.0
    while a lt 5.0
        a = a + 1.0
        endm
```

#### See Also

[Operators Reference](readme.md)