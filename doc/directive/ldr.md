Asmc Macro Assembler Reference

## LDR

**LDR**(_param_)

**LDR** _dst_, _param_

Loads Register _param_ if available.

Example:

```
foo proc c:int_t

    ldr ecx,c
    bar(ldr(c))
```

The action taken depends on calling convention.

<table>
<tr><td><b>Calling convention</b></td><td><b>bits</b></td><td><b>Action</b></td></tr>
<tr><td>syscall</td><td>64</td><td>mov ecx,edi</td></tr>
<tr><td>watcall</td><td>64/32</td><td>mov ecx,eax</td></tr>
<tr><td>fastcall</td><td>64/32</td><td><i>nothing</i></td></tr>
<tr><td>C/stdcall/..</td><td>32</td><td>mov ecx,c</td></tr>
</table>

#### See Also

[Procedures](procedures.md) | [Directives Reference](readme.md)
