Asmc Macro Assembler Reference

### OPTION FLOAT

**OPTION FLOAT**:[_size_]

This controls the default size of a float expression value. The options are 4 or 8. The default value is 4.

```assembly
option floatdigits: 8

    .if ( xmm0 > 2.0 )

    .endif
```

#### See Also

[Directives Reference](readme.md) | [.IF](dot_if.md)