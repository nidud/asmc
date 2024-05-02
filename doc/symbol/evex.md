Asmc Macro Assembler Reference

## {evex}

The Enhanced Vector Extension (EVEX) encoding prefix will be omitted by using an EVEX exclusive instruction or any of the extended SIMD registers. A preceding prefix **{evex}** may be used for EVEX encoding of other instructions.

**{modifiers}**

- **{sae}** - Suppress All Exceptions
- **{k1}** - Merge Mask
- **{k1}{z}** - Zero Mask

Rounding

- **{rn-sae}** - To nearest or even
- **{rd-sae}** - Toward negative infinity
- **{ru-sae}** - Toward positive infinity
- **{rz-sae}** - Toward zero

#### See Also

[Miscellaneous](miscellaneous.md) | [Symbols Reference](readme.md) | [Option AVXENCODING](../directive/option-avxencoding.md)
