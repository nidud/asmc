Asmc Macro Assembler Reference

## OPTION FLOATFORMAT

**OPTION FLOATFORMAT**:[E|F|G|X]

This controls the format of float output. The default value is F.

```
option floatdigits: 6, floatformat: e

value = 1.0 / 3.0
%echo @CatStr(<value = >, %value)

value = 3.333333e-001
```

#### See Also

[Option](option.md) | [Directives Reference](readme.md) | [option floatdigits](option-floatdigits.md)
