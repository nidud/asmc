Asmc Linker Reference

## /MACHINE

**/MACHINE**:{X64|X86|DOS}

The /MACHINE option specifies the target platform for the program.

LINKW infers the machine type from the .obj files. However, this option adds a [LIBPATH](libpath.md) to %ASMCDIR%\\lib\\{X64|X86} if found, or to {LINKW.EXE dir}\\..\\lib\\{X64|X86|DOS} if specified.

#### See Also

[Asmc Linker Reference](readme.md)
