Asmc Macro Assembler Reference

## .CDAT

**.CDAT** _name_[[ ( _alignment_ ) ]]

Starts a communal data section (COMDAT) with item name _name_ and a segment name formed by concatenating _prefix_ and _name_. On Windows the prefix is `__cdat@`; on Linux it is `.gnu.linkonce.r.`. The segment is read-only.

Example:
```
.cdat my_ymm(32)
 my_ymm real4 8 dup(1.0)

```

#### See Also

[Simplified Segment](simplified-segment.md) | [Directives Reference](readme.md) | [Option -Gw](../command/option-gw.md)
