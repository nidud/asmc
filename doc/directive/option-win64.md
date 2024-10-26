Asmc Macro Assembler Reference

## OPTION WIN64

**OPTION WIN64:[ RSP | RBP | [NO]ALIGN | [NO]SAVE | [NO]AUTO | [NO]FRAME] ]**

The first three flag-bits may be set directly and correspond to SAVE (bit 0), AUTO (bit 1), and ALIGN (bit 2).

SAVE forces parameters passed in registers to be written to their locations on the stack upon function entry. AUTO will calculate the maximum stack needed for function calls and ALIGN will use 16-byte alignment for local variables.

FRAME is the same as option FRAME:ADD.

#### See Also

[Option](option.md) | [Directives Reference](readme.md) | [FRAME](option-frame.md)
