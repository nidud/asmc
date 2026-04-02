Asmc Macro Assembler Reference

## OPTION CASEMAP

**OPTION CASEMAP**:[NONE|NOTPUBLIC|ALL]

This controls case of identifiers. The default value is ALL.

```
    ALL       (/Cu) Maps all identifiers to upper case (default).
    NONE      (/Cx) Preserves case in public and extern symbols.
    NOTPUBLIC (/Cp) Preserves case of all user identifiers.
```

Note that the case of an identifier is fixed when the symbol is created, not when it is referenced. The case recorded in the object file remains unchanged even if OPTION CASEMAP:ALL is later used.

Example:
```
OPTION CASEMAP:NONE
abc db 1
ABC db 2
OPTION CASEMAP:ALL
mov al,abc
mov cl,ABC
```
#### See Also

[Option](option.md) | [Directives Reference](readme.md) | [Asmc Command-Line Reference](../command/readme.md)
