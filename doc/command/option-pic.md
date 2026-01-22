Asmc Macro Assembler Reference

## Position Independent Code (PIC)

Generate position-independent code for ELF.

These options (`-fpic` and `-fPIC`) instruct the assembler to generate position-independent code suitable for use in shared libraries. When either of these options is used, the assembler defines the corresponding preprocessor macros with the [specified value](../symbol/predefined-macros.md).

The difference between `-fpic` and `-fPIC` is that `-fPIC` generates **GOTX** relocations for global data accesses. In contrast, `-fpic` generates **GOT** relocations. Additionally, the option `-fno-plt` can also be used in conjunction with `-fpic` or `-fPIC` to avoid using the Procedure Linkage Table (PLT) for function calls.

The `-fno-pic` option can be used to disable position-independent code generation. This is the default behavior for Asmc.

#### See Also

[Asmc Command-Line Reference](readme.md)
