Asmc Macro Assembler Reference

## .PRAGMA

**.PRAGMA** INIT | EXIT | PACK | LIST | CREF | COMMENT | WARNING | WSTRING | AUX

- .**pragma** cref(push, <0|1>)
- .**pragma** cref(pop)
- .**pragma** list(push, <0|1>)
- .**pragma** list(pop)
- .**pragma** pack(push, _alignment_)
- .**pragma** pack(pop)
- .**pragma** init(_proc_, _priority_)
- .**pragma** exit(_proc_, _priority_)
- .**pragma** comment(lib, _name_[, _name_])
- .**pragma** comment(linker, _linkeroption_)
- .**pragma** warning(disable: _num_)
- .**pragma** warning(push)
- .**pragma** warning(pop)
- .**pragma** wstring(push, <0|1>)
- .**pragma** wstring(pop)
- .**pragma** aux(_reg0_, _reg1_, ..., _regn_)

Pragma aux lets you customize the [ASMCALL](asmcall.md) Calling Convention. Up to 8 register may be used as parameters.

#### See Also

[Miscellaneous](miscellaneous.md) | [Directives Reference](readme.md) | [Asmc Warning Messages](../error/warnings.md)
