Asmc Macro Assembler Reference

## OPERATOR ::

**rdx::rax**

**edx::eax**

**label::**

**type::id proto ...**

**type::id proc ...**

The first operator is used in [INVOKE](../directive/invoke.md) to create a 128-bit argument in 64-bit.

The second operator is used in [INVOKE](../directive/invoke.md) to create a 64-bit argument in 32-bit.

The third operator is used as a global label within a PROC or as a PUBLIC label outside.

The next two operators is used to define a class member with a hidden (this) argument of _type_.

#### See Also

[Directives Reference](readme.md)
