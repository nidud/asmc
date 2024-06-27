Asmc Macro Assembler Reference

## .PRAGMA

**.PRAGMA** INIT | EXIT | PACK | LIST | CREF | COMMENT | WARNING | AUX

- .**pragma**(cref(push, <0|1>))
- .**pragma**(cref(pop))
- .**pragma**(list(push, <0|1>))
- .**pragma**(list(pop))
- .**pragma**(pack(push, _alignment_))
- .**pragma**(pack(pop))
- .**pragma**(init(_proc_, _priority_))
- .**pragma**(exit(_proc_, _priority_))
- .**pragma**(comment(lib, _name_[, _name_]))
- .**pragma**(warning(disable: _num_))
- .**pragma**(warning(push))
- .**pragma**(warning(pop))
- .**pragma**(aux(push, _language_, _fixed_, _reg0_, _reg1_, ..., _regn_))
- .**pragma**(aux(pop))

Pragma aux lets you customize a [Register Calling Convention](procedures.md). The first argument is the language. The second is a boolean value indicating if the parameters have fixed positions followed by up to 8 register to be used as parameters.

The following example modifies the [watcall](watcall.md) convention by flipping the last two registers:
```
.pragma aux(push, watcall, 1, eax, edx, ecx, ebx)
```

#### See Also

[Miscellaneous](miscellaneous.md) | [Directives Reference](readme.md) | [Asmc Warning Messages](../error/warnings.md)
