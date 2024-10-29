Asmc Macro Assembler Reference

## comment pragma

Places a comment record into an object file or executable file.

**.pragma** comment( _comment-type_ [ , _"comment-string"_ ] )

**lib**, _lib-file_ [ , _dll-file_ ]

Places a library-search record in the object file using [includelib](includelib.md) or [option dllimport](option-dllimport.md) if the [-pe](../command/option-pe.md) option is used. The default extension is .LIB and .DLL.

```
.pragma comment(lib, kernel32)
.pragma comment(lib, libc, msvcrt)
```

**linker**, _linkeroption_

Places a [linker option](../command/option-link.md) in the object file. You can use this comment-type to specify a linker option instead of passing it to the command line or specifying it in the development environment. For example, you can specify the /include option to force the inclusion of a symbol:
```
.pragma comment(linker, "/include:__mySymbol")
```

#### See Also

[Pragma directive](dot-pragma.md)
