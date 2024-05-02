Asmc Macro Assembler Reference

## OPTION AVXENCODING

OPTION AVXENCODING :[PREFER\_FIRST | PREFER\_VEX[[3]] | PREFER\_EVEX | NO\_EVEX]

- **PREFER\_FIRST** - Use first defined form if possible.
- **PREFER\_VEX** - Use VEX encoding in preference to EVEX encoding.
- **PREFER\_VEX3** - Use 3-byte VEX encoding in preference to EVEX encoding.
- **PREFER\_EVEX** - Use EVEX encoding in preference to VEX encoding.
- **NO\_EVEX** - Don't encode using EVEX.

The **AVXENCODING** order applies only if the instruction prefix form isn't specified for the instruction. The default value is **PREFER\_FIRST**.

#### See Also

[Option](option.md) | [Directives Reference](readme.md) | [{evex}](../symbol/evex.md)
