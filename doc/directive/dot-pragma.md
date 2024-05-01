Asmc Macro Assembler Reference

## .PRAGMA

**.PRAGMA** INIT | EXIT | PACK | LIST | CREF | COMMENT | WARNING

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


#### See Also

[Directives Reference](readme.md) | [Asmc Warning Messages](../error/warnings.md)
