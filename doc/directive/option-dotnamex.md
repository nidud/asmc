Asmc Macro Assembler Reference

## OPTION DOTNAMEX

**OPTION DOTNAMEX**[ ON | OFF ]

Allows names of identifiers that begin with a period to have dotted names. The default is OFF.

This to support C++ generated assembly code.

```
    .name..
    .name.00100
```

#### See Also

[Directives Reference](readme.md) | [DOTNAME](option-dotname.md)