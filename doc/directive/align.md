Asmc Macro Assembler Reference

## ALIGN

**ALIGN** [[_number_]]

Aligns the next variable or instruction on a byte that is a multiple of _number_.

The _number_ must be a power of 2, and the assembler will insert between 0 and _number_-1 bytes of padding to ensure that the next variable or instruction starts at an address that is a multiple of _number_.

#### See Also

[Code Labels](code-labels.md) | [Directives Reference](readme.md)
