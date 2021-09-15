Asmc Macro Assembler Reference

### OPTION NOKEYWORD

- Rename any offending symbols in your code.
- Selectively disable keywords with the OPTION NOKEYWORD directive.

The second option lets you retain the offending symbol names in your code by forcing not recognize them as keywords. For example,

    OPTION NOKEYWORD:<INVOKE STRUCT>

removes the keywords INVOKE and STRUCT from the assembler's list of reserved words. However, you cannot then use the keywords in their intended function, since the assembler no longer recognizes them.

#### See Also

[Directives Reference](readme.md)