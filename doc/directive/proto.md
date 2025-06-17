Asmc Macro Assembler Reference

## PROTO

label **PROTO** [[distance]] [[langtype]] [[, [[parameter]]:tag]]... [\{...\}]

Prototypes a function or an _inline function_.

```
_mm256_mpsadbw_epu8 proto :yword, :yword, i:abs {
    vmpsadbw ymm0, ymm0, ymm1, i
    }
```

#### See Also

[Procedures](procedures.md) | [Directives Reference](readme.md)
