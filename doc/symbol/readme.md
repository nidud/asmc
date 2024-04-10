Asmc Macro Assembler Reference

## Symbols Reference

### Predefined macros

The Asmc assembler predefines certain preprocessor macros depending on the target and the chosen assembler options.

_macros_

The macros listed in the following table.

| Macros | Meaning |
|:------ |:------- |
| **\_\_ASMC\_\_** | Defined as an integer literal that represents the version of Asmc. This macro is always defined. |
| **\_\_ASMC64\_\_** | Defined as an integer literal that represents the version of Asmc64. This macro is defined by ASMC64.EXE. |
| **\_\_AVX\_\_** | Defined as 1 when the /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined. |
| **\_\_AVX2\_\_** | Defined as 1 when the /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined. |
| **\_\_AVX512BW\_\_** | Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined. |
| **\_\_AVX512CD\_\_** | Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined. |
| **\_\_AVX512DQ\_\_** | Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined. |
| **\_\_AVX512F\_\_** | Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined. |
| **\_\_AVX512VL\_\_** | Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined. |
| **\_\_COMPACT\_\_** | Defined as 1 when the /mc option is set. Otherwise, undefined. |
| **\_\_DEBUG\_\_** | Defined as 1 when the /Zi option is set. Otherwise, undefined. |
| **\_\_FLAT\_\_** | Defined as 1 when the /mf option is set. Otherwise, undefined. |
| **\_\_GUI\_\_** | Defined as 1 when the /gui option is set. Otherwise, undefined. |
| **\_\_HUGE\_\_** | Defined as 1 when the /mh option is set. Otherwise, undefined. |
| **\_\_JWASM\_\_** | Defined as an integer literal value 212 that represents the compatible version of JWasm. This macro is always defined. |
| **\_\_LARGE\_\_** | Defined as 1 when the /ml option is set. Otherwise, undefined. |
| **\_M\_IX86\_FP** | Defined as 1 when the /arch:IA32 option is set. Otherwise, undefined. |
| **\_LINUX** | Defined as 1 when the /elf option is set and 2 when the /elf64 option is set. Otherwise, undefined. |
| **\_\_MEDIUM\_\_** | Defined as 1 when the /mm option is set. Otherwise, undefined. |
| **\_MSVCRT** | Defined as 1 when the /nolib option is set. Otherwise, undefined. |
| **\_\_PE\_\_** | Defined as 1 when the /pe option is set. Otherwise, undefined. |
| **\_\_P186\_\_** | Defined as 1 when the /1 option is set. Otherwise, undefined. |
| **\_\_P286\_\_** | Defined as 1 when the /2 option is set. Otherwise, undefined. |
| **\_\_P386\_\_** | Defined as 1 when the /3 option is set. Otherwise, undefined. |
| **\_\_P486\_\_** | Defined as 1 when the /4 option is set. Otherwise, undefined. |
| **\_\_P586\_\_** | Defined as 1 when the /5 option is set. Otherwise, undefined. |
| **\_\_P64\_\_** | Defined as 1 when the /10 option is set. Otherwise, undefined. |
| **\_\_P686\_\_** | Defined as 1 when the /6, /7, /8, or /9 option is set. Otherwise, undefined. |
| **\_\_P86\_\_** | Defined as 1 when the /0 option is set. Otherwise, undefined. |
| **\_\_SMALL\_\_** | Defined as 1 when the /ms option is set. Otherwise, undefined. |
| **\_\_SSE\_\_** | Defined as 1 when the /8, /9, /arch:SSE, /arch:SSE2, /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined. |
| **\_\_SSE2\_\_** | Defined as 1 when the /9, /arch:SSE2, /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined. |
| **\_STDCALL\_SUPPORTED** | Defined as 1 when the /Gz option is set. Otherwise, undefined. |
| **\_\_TINY\_\_** | Defined as 1 when the /mt option is set. Otherwise, undefined. |
| **\_UNICODE** | Defined as 1 when the /ws option is set. Otherwise, undefined. |
| **\_\_UNIX\_\_** | Defined as 1 when the /elf or /elf64 options are set. Otherwise, undefined. |
| **\_WIN64** | Defined as 1 when the compilation target is 64-bit. Otherwise, undefined. |

### Date and Time Information

| | |
| -------- |:------- |
| **@Date** | The compilation date of the current source file. The date is a constant length string literal of the form mm/dd/yy. |
| **@Time** | The system time in 24-hour hh:mm:ss format (text macro). |

### Environment Information

| | |
| --- |:--- |
| **[@Cpu](cpu.md)** | A bit mask specifying the processor mode (numeric equate). |
| **@Environ(_envvar_)** | Value of environment variable _envvar_ (macro function). |
| **@Interface** | Information about the language parameters (numeric equate). |
| **@Version** | Defined as an integer literal value that represents the compatible version of Masm. Currently 800 for Asmc and 1000 for Asmc64. |

### File Information

| | |
| -------- |:------- |
| **@FileName** | The base name of the main file being assembled (text macro). |
| **@FileCur** | The name of the current source file (text macro). |
| **@Line** | Defined as the integer line number in the current source file. |
| **\_\_FILE\_\_** | The name of the current source file (string macro). |
| **\_\_func\_\_** | The name of the current function (string macro). |
| **\_\_LINE\_\_** | Defined as the integer line number in the current source file. |

### Macro Functions

| | |
| -------- |:------- |
| **@CatStr(_string1_[[,_string2_...]])** | Macro function that concatenates one or more strings. Returns a string. |
| **@ComAlloc(_class_[[,_vtable_]])** | Macro function that allocates a CLASS object. Returns a pointer to the new object. |
| **@CStr(_string_\|_index_)** | Macro function that creates a string in the .DATA or .CONST segment. The macro accepts C-escape characters in the string. Strings are added to a stack and reused if duplicated strings are found. The macro returns _string label_. |
| **@InStr([[_position_]],_string1_,_string2_)** | Macro function that finds the first occurrence of _string2_ in _string1_, beginning at position within string1\. If position does not appear, search begins at start of _string1_. Returns a position integer or 0 if string2 is not found. |
| **@Reg(_reg_[[,_bits_]])** | Macro function that convert _reg_ to _reg_[[_bits_]]. _bits_: 8, 16, 32 (default), and 64. The macro returns a string. |
| **@SizeStr(_string_)** | A macro function that returns the length of the given string. Returns an integer. |
| **@SubStr(_string_,_position_[[,_length_]])** | A macro function that returns a substring starting at position. |

### Miscellaneous

| | |
| -------- |:------- |
| **$** | The current value of the location counter. |
| **?** | In data declarations, a value that the assembler allocates but does not initialize. |
| **@@:** | Defines a code label recognizable only between _label1_ and _label2_, where _label1_ is either start of code or the previous @@: label, and _label2_ is either end of code or the next @@: label. |
| **@B** | The location of the previous @@: label. |
| **@F** | The location of the next @@: label. |
| **{evex}** | The Enhanced Vector Extension (EVEX) encoding prefix will be omitted by using an EVEX exclusive instruction or any of the extended SIMD registers. A preceding prefix **{evex}** may be used for EVEX encoding of other instructions. |

### Segment Information

| | |
| -------- |:------- |
| **@code** | The name of the code segment (text macro). |
| **@CodeSize** | 0 for TINY, SMALL, COMPACT, and FLAT models, and 1 for MEDIUM, LARGE, and HUGE models (numeric equate). |
| **@CurSeg** | The name of the current segment (text macro). |
| **@data** | The name of the default data group. Evaluates to DGROUP for all models except FLAT. Evaluates to FLAT under the FLAT memory model (text macro). |
| **@DataSize** | 0 for TINY, SMALL, MEDIUM, and FLAT models, 1 for COMPACT and LARGE models, and 2 for HUGE model (numeric equate). |
| **@fardata** | The name of the segment defined by the .FARDATA directive (text macro). |
| **@fardata?** | The name of the segment defined by the .FARDATA? directive (text macro). |
| **@Model** | 1 for TINY model, 2 for SMALL model, 3 for COMPACT model, 4 for MEDIUM model, 5 for LARGE model, 6 for HUGE model, and 7 for FLAT model (numeric equate). |
| **@stack** | DGROUP for near stacks or STACK for far stacks (text macro). |
| **@WordSize** | Two for a 16-bit, four for a 32-bit, and eight for a 64-bit segment (numeric equate). |

#### See Also

[Directives Reference](../directive/readme.md)
