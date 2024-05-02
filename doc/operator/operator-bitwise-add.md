Asmc Macro Assembler Reference

## operator ADD

**_expression1_ ADD _expression2_**

Returns the result of a bitwise ADD operation for _expression1_ plus _expression2_.

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

[Logical and Shift](logical-and-shift.md) | [Operators Reference](readme.md)
