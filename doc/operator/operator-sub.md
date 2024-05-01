Asmc Macro Assembler Reference

## operator SUB

**_expression1_ SUB _expression2_**

Returns the result of a bitwise SUB operation for _expression1_ minus _expression2_.

```
; Manipulating float using binary operators

sqrt_approx macro f

      local x

        x = f sub 00010000000000000000000000000000r
        x = x shr 1
        x = x add 20000000000000000000000000000000r
        exitm<x>
        endm
```

#### See Also

[Operators Reference](readme.md)
