Asmc Macro Assembler Reference

## operator BCST

**_type_ BCST _expression_**

AVX-512 option _Embedded Broadcast_. Same as [ _type_ PTR _expression_{1toxx} ].

_Embedded Broadcast_ allows a scalar value in memory to be applied to all elements of a vector. This option is enabled by adding the element size and the keyword BCST to the memory operand, which is similar to the use of PTR for normal memory references.

#### See Also

[Type](type.md) | [Operators Reference](readme.md)
