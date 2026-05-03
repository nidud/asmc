Asmc Macro Assembler Reference

## init pragma

Specifies a functions that runs before the program starts.

.**pragma** init(_proc_, _priority_)

```
.pragma init(foo, 3)
```

Windows (or option -mscrt):
```
option dotname
.CRT$XIA segment align(8) 'CONST'
ifdef _WIN64
 dd imagerel foo, 3
else
 dd foo, 3
endif
.CRT$XIA ends
```

Linux:
```
option dotnamex:on
.init_array.00003 segment align(8) 'CONST'
ifdef _WIN64
 dq imagerel foo
else
 dd foo, 3
endif
.init_array.00003 ends
```

#### See Also

[Pragma directive](dot-pragma.md)
