Asmc Macro Assembler Reference

## operator .

- **_expression_. _field_ [[. _field_]]...**
- **[_register_]. _field_ [[. _field_]]...**

The first operator returns _expression_ plus the offset of _field_ within its structure or union.

The second operator returns value at the location pointed to by _register_ plus the offset of _field_ within its structure or union.

**Indirection**

In Asmc the unary indirection operator (.) may also accesses a value indirectly, through a pointer. The operand must be a pointer type. The result of the operation is the value addressed by the operand; that is, the value at the address to which its operand points. The type of the result is the type that the operand addresses.

The result of the indirection operator is _type_ if the operand is of type _pointer to type_. If the operand points to a function, the result is a function designator.

#### See Also

[Arithmetic](arithmetic.md) | [Operators Reference](readme.md)
