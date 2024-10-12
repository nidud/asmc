Asmc Macro Assembler Reference

## option -link

**-link** _link\_options_

**-Bl** _linker_

_linker_

Optional linker. The default is LINKW for the Windows version, and gcc for Linux.

_link\_options_

The link options. For more information, see [Linker options](../tools/linkw/readme.md).

If link options are omitted the default options added depends on the situation. In Windows the /LIBPATH:_directory_ is set, and if the -q option is used /NOLOGO is added. The linux version adds output name from the first object file. Omitting the -fpic option adds static libraries.
```
gcc [-m32 -static] [-nostdlib] -o name object_files [-l:[x86/]libasmc.a]
```

#### See Also

[Asmc Command-Line Reference](readme.md) | [option -pe](option-pe.md)
