Asmc Macro Assembler Reference

## String Literals

A "string-literal" is formed by enclosing characters from the representable character set within double quotation marks (" ").

When a string literal is used in an expression, [escape sequences](escape-sequences.md) in the string are processed. Otherwise, the string is treated as a sequence of characters, and if _type_ evaluates to a _wide_ string type, the string is converted to a wide string.

### Syntax

**_expression_**( [`L`] `"` _char-sequence_ `"` [ `...`] )

**_type_** `"` _char-sequence_ `"` [ `, ...` ]

Where:
- `_expression_`: An expression that evaluates to the string literal.
- `_type_`: A type specifier for the string literal.
- `L`: An optional prefix indicating a wide character string.
- `_char-sequence_`: A sequence of characters forming the string.

### Examples
```asm
_tprintf("Hello, World!\n")
_wprintf(L"Wide String Example\n")

helloString TCHAR "Hello, World!",10,0
```

#### See Also

[Directives Reference](readme.md) | [Escape Sequences](escape-sequences.md) | [Data Allocation](data-allocation.md)
