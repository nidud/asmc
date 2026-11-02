Asmc Macro Assembler Reference

## OPTION CODEPAGE

**OPTION CODEPAGE**:_value_

This controls Unicode creation. Value is the first argument to MultiByteToWideChar() if value differ from CP\_UTF8. The default value is CP\_UTF8 (65001).

The switch /ws is also extended to /ws[_value_].

```
    option codepage:865     ; /ws865
    option codepage:CP_UTF8 ; /ws65001
```

#### See Also

[Option](option.md) | [Directives Reference](readme.md) | [Asmc Command-Line Reference](../command/readme.md)
