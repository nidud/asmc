Asmc Macro Assembler Reference

## option -link

`-link` _link\_options_

`-Bl` _linker_

_linker_

Optional linker. The default is `LINKW` for the Windows version, and `gcc` for Linux.

_link\_options_

The link options. For more information, see [Linker options](../tools/linkw/readme.md).

If link options are omitted the default options added depends on the situation. In Windows the `/LIBPATH` directory is set, and if the `-q` option is used `/NOLOGO` is added. The linux version adds output name from the first object file. Omitting the `-fpic`, `-fPIC`, and `-fplt` options adds `-static` and `-fno-pic` to `gcc`. Additionally, if the option `-MT` is used and no libraries are specified, the standard C library is linked.
```
gcc [-m32 [-no-pie]] [-static] [-nostdlib] [-s] -o name object_files [-l:[x86/]libasmc.a]
```

You can use the [comment](../directive/dot-pragma.md) pragma to specify some linker options.

Valid options for LINK are [/DEFAULTLIB](../tools/linkw/defaultlib.md), [/EXPORT](../tools/linkw/export.md), [/INCLUDE](../tools/linkw/include.md), [/MANIFESTDEPENDENCY](../tools/linkw/manifestdependency.md), [/MERGE](../tools/linkw/merge.md), and [/SECTION](../tools/linkw/section.md).

#### See Also

[Asmc Command-Line Reference](readme.md) | [option -pe](option-pe.md)
