Asmc Macro Assembler Reference

## STRINGTABLE

Defines one or more string resources for an application. String resources are simply null-terminated Unicode strings that can be loaded when needed from the executable file, using the LoadString function.

syntax:

```
STRINGTABLE [optional-statements] {string [, ...]}
```

#### Parameters

_optional-statements_

- [CHARACTERISTICS](characteristics.md)
- [LANGUAGE](language.md)
- [VERSION](version.md)

#### Note

- For STRINGTABLE resources the stringID start at 384 (0x180) where each table allocates 16 strings. This means the maximum number of strings in one table is 16.
- The default _codepage_ for converting "strings" to Unicode is CP\_UTF8. See [Option _codepage_](../directive/option-codepage.md) for more information.

#### Example

```
define IDS_HELLO    384
define IDS_GOODBYE  385
define IDS_HELLO2   400

.resource
 STRINGTABLE {
    "Hello string number 385",
    "Goodbye string number 384"
    }
 STRINGTABLE {
    "Hello from string number 400"
    }
```

#### See Also

[Asmc Resource Compiler](readme.md) | [Option _codepage_](../directive/option-codepage.md)
