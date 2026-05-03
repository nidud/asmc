Asmc Macro Assembler Reference

## operator &

_expression1_ **&** _expression2_

Bitwise AND.

Used only within [.IF](../directive/dot-if.md), [.WHILE](../directive/dot-while.md), or [.REPEAT](../directive/dot-repeat.md) blocks and evaluated at run time, not at assembly time.

**&**_address_

- _procedure_( **&**_address_ )
- .for ( reg = **&**_address_ :: )
- .return ( **&**_address_ )
- .if ( a == **&**_address_ && b & **&**_address_ )

#### See Also

[Control Flow](control-flow.md) | [Operators Reference](readme.md)
