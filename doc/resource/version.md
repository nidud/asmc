Asmc Macro Assembler Reference

## VERSION

Defines version information about a resource that can be used by tools that read and write resource files. The specified dword value appears with the resource in the compiled .RES file. However, the value is not stored in the executable file and has no significance to the system.

The VERSION statement appears before the beginning of the body of an ACCELERATORS, DIALOGEX, MENU, RCDATA, or STRINGTABLE resource definition. The specified value applies only to that resource.

syntax:

```
VERSION dword
```

#### Parameters

_dword_

A user-defined DWORD value.

#### See Also

[Asmc Resource Compiler](readme.md)
