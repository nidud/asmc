Asmc Macro Assembler Reference

## OPTION CODEPAGE

**OPTION CODEPAGE**:_value_

This controls Unicode creation. Value is the first argument to MultiByteToWideChar(). The default value is 0.

The switch /ws is also extended to /ws[_value_].

```
    option codepage:865     ; /ws865
    option codepage:CP_UTF8 ; /ws65001
```

#### See Also

[Directives Reference](readme.md) | [Asmc Command-Line Reference](../command/readme.md)