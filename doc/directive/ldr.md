Asmc Macro Assembler Reference

## LDR

**LDR** _dst_, _param_

Loads Register _param_ if available.

Example:

```
foo proc c:int_t

    ldr ecx,c
    ...
```

The action taken depends on calling convention.

```
 Calling convention  Action

 SYSCALL   64        mov ecx,edi
 WATCALL   64        mov ecx,eax
 FASTCALL  64        _nothing_
 C/STDCALL 32        mov ecx,c
```

#### See Also

[Procedures](procedures.md) | [Directives Reference](readme.md)
