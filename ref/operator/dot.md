Asmc Macro Assembler Reference

## operator .

**_expression_. _field_ [[. _field_]]...**


**[_register_]. _field_ [[. _field_]]...**


The first operator returns _expression_ plus the offset of _field_ within its structure or union.

The second operator returns value at the location pointed to by _register_ plus the offset of _field_ within its structure or union.

#### See Also

[Operators Reference](readme.md)