Asmc Macro Assembler Reference

## OPTION FLOATDIGITS

**OPTION FLOATDIGITS**:[_count_]

This controls the number of digits in float output. The default value is 1.

```
option floatdigits: 16

value = 1.0 / 3.0
%echo @CatStr(<value = >, %value)

value = 0.3333333333333333
```

#### See Also

[Option](option.md) | [Directives Reference](readme.md) | [option floatformat](opt_floatformat.md)
