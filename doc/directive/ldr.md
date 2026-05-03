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
<tr><td>stack</td><td>32</td><td>mov ecx,c</td></tr>
</table>

Special action taken on 16-bit pointers:

<table>
<tr><td><b>Register</b></td><td><b>Near</b></td><td><b>Far</b></td></tr>
<tr><td>ldr si,p</td><td>mov si,p</td><td>lds si,p</td></tr>
<tr><td>ldr reg,p</td><td>mov reg,p</td><td>les reg,p</td></tr>
</table>

When used as parameter the action taken is based on the value of [@DataSize](../symbol/at-datasize.md) as the type is unknown.

<table>
<tr><td><b>Register</b></td><td><b>Near</b></td><td><b>Far</b></td></tr>
<tr><td>ldr(ax)</td><td>ax</td><td>dx::ax</td></tr>
<tr><td>ldr(si)</td><td>si</td><td>ds::si</td></tr>
<tr><td>ldr(reg)</td><td>reg</td><td>es::reg</td></tr>
</table>

#### See Also

[Procedures](procedures.md) | [Directives Reference](readme.md)
