Asmc Macro Assembler Reference

## operator &

_expression1_ **&** _expression2_

Bitwise AND. Used within [.IF](../directive/dot_if.md), [.WHILE](../directive/dot_while.md), or [.REPEAT](../directive/dot_repeat.md) blocks and evaluated at run time, not at assembly time.

**&**_address_

_procedure_( **&**_address_ )

.for ( reg = **&**_address_ :: )

.return ( **&**_address_ )

.if ( a == **&**_address_ && b & **&**_address_ )

#### See Also

[Operators Reference](readme.md) | [ADDR](addr.md) | [.FOR](../directive/dot_for.md)
