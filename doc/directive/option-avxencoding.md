Asmc Macro Assembler Reference

## OPTION AVXENCODING

Selects the preferred encoding of AVX instructions.

### Syntax

OPTION AVXENCODING: _preference_

### Preferences

<table>
<tr><td><b>Preference</b></td><td><b>Encoding preference priority</b></td></tr>
<tr><td><b>PREFER_FIRST</b></td><td>Use first defined form if possible.</td></tr>
<tr><td><b>PREFER_VEX</b></td><td>Use VEX encoding in preference to EVEX encoding.</td></tr>
<tr><td><b>PREFER_VEX3</b></td><td>Use 3-byte VEX encoding in preference to EVEX encoding.</td></tr>
<tr><td><b>PREFER_EVEX</b></td><td>Use EVEX encoding in preference to VEX encoding.</td></tr>
<tr><td><b>NO_EVEX</b></td><td>Don't encode using EVEX.</td></tr>
</table>

The **AVXENCODING** order applies only if the instruction prefix form isn't specified for the instruction. The default value is **PREFER\_FIRST**.

#### See Also

[Directives Reference](readme.md) | [Option](option.md) | [Instruction Format](instruction-format.md)
