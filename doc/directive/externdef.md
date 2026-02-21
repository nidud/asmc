Asmc Macro Assembler Reference

## EXTERNDEF

**EXTERNDEF** [[langtype]] [[IMPORT|EXPORT]] name:type [[, [[langtype]] name:type]]...

Defines one or more external variables, labels, or symbols called name whose type is type. If name is defined in the module, it is treated as PUBLIC. If name is referenced in the module, it is treated as EXTERN. If name is not referenced, it is ignored. The type can be ABS, which imports name as a constant. Normally used in include files.

The `IMPORT` keyword is used with the `-pe` option to mark a symbol as imported from a DLL; in this case, the symbol represents a pointer to the external symbol. `EXPORT` marks a symbol to be exported from a dynamic module (for example, a DLL), making it available to external modules.

#### See Also

[Scope](scope.md) | [Directives Reference](readme.md)
