Asmc Macro Assembler Reference

## exit pragma

Specifies a functions that runs after the main program exits.

.**pragma** exit(_proc_, _priority_)

```
.pragma exit(foo, 3)
```

Windows (or option -mscrt):
```
option dotname
.CRT$XTA segment align(8) 'CONST'
ifdef _WIN64
 dd imagerel foo, 3
else
 dd foo, 3
endif
.CRT$XTA ends
```

Linux:
```
option dotnamex:on
.fini_array.00003 segment align(8) 'CONST'
ifdef _WIN64
 dq imagerel foo
else
 dd foo, 3
endif
.fini_array.00003 ends
```

#### See Also

[Pragma directive](dot-pragma.md)
