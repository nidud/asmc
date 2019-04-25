Asmc Macro Assembler Reference

### OPTION SWITCH

**OPTION SWITCH:[ C | PASCAL | TABLE | NOTABLE | NOREGS | REGAX ]**

The [switch](dot_switch.md) comes in two main types: a structured switch (Pascal) or an unstructured switch (C). The default type is unstructured.

The **TABLE** and **NOTABLE** options control the jump-table creation in the switch. The default setting is **NOTABLE**.

The **NOREGS** and **REGAX** options control the usage of registers in jump-table creation in the switch. R10/r11 is used in 64-bit else [E]AX. The default setting is **NOREGS** for ASMC and **REGAX** for ASMC64.

#### See Also

[Directives Reference](readme.md) | [.SWITCH](dot_switch.md)