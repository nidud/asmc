Asmc Macro Assembler Reference

### OPTION FLOATFORMAT

**OPTION FLOATFORMAT**:[E|F|G|X]

This controls the format of float output. The default value is F.

```assembly
option floatdigits: 6, floatformat: e

value = 1.0 / 3.0
%echo @CatStr(<value = >, %value)

value = 3.333333e-001
```

#### See Also

[Directives Reference](readme.md) | [option floatdigits](opt_floatdigits.md)