Asmc Macro Assembler Reference

### OPTION LOOPALIGN

**OPTION LOOPALIGN**:[0|2|4|8|16]

This controls the alignment for .WHILE and .REPEAT labels. The default value is 0.

```assembly
jmp loop_start
ALIGN <loopalign> ; align label after jump
loop_label:
```
#### See Also

[Directives Reference](readme.md)