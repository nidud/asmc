Asmc Macro Assembler Reference

## COMM

**COMM** _definition_ [[, _definition_]] ...

Creates a communal variable with the attributes specified in definition. Each definition has the following form:

[[_langtype_]] [[NEAR | FAR]] _label:type_[[:_count_]]

The label is the name of the variable. The type can be any type specifier (BYTE, WORD, and so on) or an integer specifying the number of bytes. The count specifies the number of data objects (one is the default).

#### See Also

[Scope](scope.md) | [Directives Reference](readme.md)
