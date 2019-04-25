Asmc Macro Assembler Reference

### EXTERNDEF

**EXTERNDEF** [[langtype]] name:type [[, [[langtype]] name:type]]...

Defines one or more external variables, labels, or symbols called name whose type is type. If name is defined in the module, it is treated as PUBLIC. If name is referenced in the module, it is treated as EXTERN. If name is not referenced, it is ignored. The type can be ABS, which imports name as a constant. Normally used in include files.

#### See Also

[Directives Reference](readme.md)