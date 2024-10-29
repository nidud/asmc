Asmc Macro Assembler Reference

## aux pragma

Pragma aux lets you customize the [asmcall](asmcall.md) Calling Convention. Up to 8 register may be used as parameters.

.**pragma** aux(_reg0_, _reg1_, ..., _regn_)

```
.pragma aux(eax, edx, ecx)
```
#### See Also

[Pragma directive](dot-pragma.md)
