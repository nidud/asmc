Asmc Linker Reference

## /EXPORT

**/EXPORT**:_entryname_[,@_ordinal_[,NONAME]][,DATA]

The /EXPORT option specifies a function or data item to export from your program so that other programs can call the function or use the data. Exports are usually defined in a DLL.

The _entryname_ is the name of the function or data item as it is to be used by the calling program. _ordinal_ specifies an index into the exports table in the range 1 through 65,535; if you do not specify _ordinal_, LINKW assigns one. The NONAME keyword exports the function only as an ordinal, without an _entryname_.

There are four methods for exporting a definition, listed in recommended order of use:

- [EXPORT](../directive/proc.md) in the source code
- An EXPORTS statement in a .def file
- An /EXPORT specification in a LINKW command
- A [comment](../directive/dot-pragma.md) directive in the source code, of the form .pragma comment(linker, "/export: definition ").

#### See Also

[Asmc Linker Reference](link.md)
