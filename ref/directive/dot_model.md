Asmc Macro Assembler Reference

### .MODEL

**.MODEL** memorymodel [[, _langtype_]] [[, _stackoption_]]

Initializes the program memory model. The memorymodel can be TINY, SMALL, COMPACT, MEDIUM, LARGE, HUGE, or FLAT. The _langtype_ can be C, BASIC, FORTRAN, PASCAL, SYSCALL, STDCALL, FASTCALL, or VECTORCALL. The stackoption can be NEARSTACK or FARSTACK.

Note: In 64-bit SYSCALL is also an instruction.

#### See Also

[Directives Reference](readme.md)