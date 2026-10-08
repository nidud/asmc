Asmc Macro Assembler Reference

## option -Gw

Option -Gw will make Asmc create COMDAT sections for assembler generated data (strings, floats, and vectors). This option is equivalent to the [Option COMDAT](../directive/option-comdat.md) directive.

The generated COMDAT sections will be named after the symbol they contain. A string data section will be prefixed by `__str@` for COFF and `.gnu.linkonce.r.` for ELF, and will be suffixed by the hash value of the string data in addition to characters indicating the type. Vectors and floats will follow the same naming convention, with the prefix `__xmm@`, `__ymm@`, and `__zmm@` for vectors and `__real@` for floats. The hash value will be calculated based on the data content, ensuring that identical data will result in the same section name.

Data items will be made public and string data items will be named `prefix` + `hash` + `type`, where the type is either `A` for ASCII strings or `W` for wide strings. For example, a string "Hello" will be named `__str@<hash>A`, where `<hash>` is the hash value of the string "Hello". Floats and vectors items will be named `prefix` + `hex-value` of the data. For example, a float value of 1.0 will be named `__real@3f800000`. Vectors will be aligned to 16 bytes for XMM, 32 bytes for YMM, and 64 bytes for ZMM.

#### See Also

[Asmc Command-Line Reference](readme.md) | [Option COMDAT](../directive/option-comdat.md)
