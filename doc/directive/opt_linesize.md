Asmc Macro Assembler Reference

### OPTION LINESIZE

**OPTION LINESIZE**:[_size_]

This controls the maximum source line length. The default value is 2048.

```assembly
value = 1.e3000

%echo @CatStr(<value = >, %value)

value = #not enough space

option linesize:4000
%echo @CatStr(<value = >, %value)

value = 1[...]0.0
```

#### See Also

[Directives Reference](readme.md) | [option floatdigits](opt_floatdigits.md)