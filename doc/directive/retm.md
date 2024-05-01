Asmc Macro Assembler Reference

## RETM

**RETM** [[_textitem_]]

Terminates expansion of the current repeat or macro block and begins assembly of the next statement outside the block. In a macro function, _textitem_ is the value returned.

RETM deviates from EXITM by skipping the return value if not used.

#### Sample

In this case the latter returns a value but the former do not:

```
    _mm_sqrt_ss( _mm_min_ss( a, b ) )
    _mm_min_ss( _mm_sqrt_ss( a ), b )
```

#### See Also

[Macros](macros.md) | [Directives Reference](readme.md)
