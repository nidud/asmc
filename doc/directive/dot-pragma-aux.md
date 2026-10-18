Asmc Macro Assembler Reference

## aux pragma

Pragma aux lets you customize the [asmcall](asmcall.md) calling convention. Up to eight registers may be used as parameters.

Pragma aux specifies which registers are used to pass parameters to a function. The syntax is as follows:

.**pragma** aux(_reg0_, _reg1_, ..., _regn_)

.**pragma** aux(pop)

The first form specifies which registers are used to pass parameters to a function. The second form restores the previous calling convention.

```
.pragma aux(eax, edx, ecx)
```
#### See Also

[Pragma directive](dot-pragma.md)
