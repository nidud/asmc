Asmc Macro Assembler Reference

## CHARACTERISTICS

Defines information about a resource that can be used by tools that read and write resource-definition files. The specified DWORD value appears with the resource in the compiled .res file. However, the value is not stored in the executable file and has no significance to the system.

The CHARACTERISTICS statement appears before the beginning of the body of an ACCELERATORS, DIALOG, MENU, RCDATA, or STRINGTABLE resource definition. The specified value applies only to that resource.

syntax:

```
CHARACTERISTICS dword
```

#### Parameters

_dword_

User-defined DWORD value.

#### See Also

[Asmc Resource Compiler](readme.md)
