Asmc Macro Assembler Reference

### .SAFESEH

**.SAFESEH** identifier

Registers a function as a structured exception handler. identifier must be the ID for a locally defined PROC or EXTRN PROC. A LABEL is not allowed. The .SAFESEH directive requires the /safeseh Asmc.exe command-line option. See /SAFESEH for more information.

#### See Also

[Directives Reference](readme.md)