Asmc Macro Assembler Reference

## @CStr

**@CStr(_string_\|_index_)**

Macro function that creates a string in the .DATA or .CONST segment. The macro accepts C-escape characters in the string. Strings are added to a stack and reused if duplicated strings are found. The macro returns _string label_.

#### See Also

[Macro Functions](macro-functions.md) | [Symbols Reference](readme.md)
