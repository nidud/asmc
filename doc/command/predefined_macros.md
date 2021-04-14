Asmc Macro Assembler Reference

## Predefined macros

The Asmc assembler predefines certain preprocessor macros depending on the target and the chosen assembler options.

_macros_

The macros listed in the following table.

| Macros | Meaning |
| ------ |:------- |
| **`__ASMC__`** | Defined as an integer literal that represents the version of Asmc. This macro is always defined. |
| **`__ASMC64__`** | Defined as an integer literal that represents the version of Asmc64. This macro is defined by ASMC64.EXE. |
| **`__AVX__`** | Defined as 1 when the /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined. |
| **`__AVX2__`** | Defined as 1 when the /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined. |
| **`__AVX512BW__`** | Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined. |
| **`__AVX512CD__`** | Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined. |
| **`__AVX512DQ__`** | Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined. |
| **`__AVX512F__`** | Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined. |
| **`__AVX512VL__`** | Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined. |
| **`__GUI__`** | Defined as 1 when the /gui option is set. Otherwise, undefined. |
| **`__JWASM__`** | Defined as an integer literal value 212 that represents the compatible version of JWasm. This macro is always defined. |
| **`_LINUX`** | Defined as 1 when the /elf option is set and 2 when the /elf64 option is set. Otherwise, undefined. |
| **`_MSVCRT`** | Defined as 1 when the /nolib option is set. Otherwise, undefined. |
| **`__PE__`** | Defined as 1 when the /pe option is set. Otherwise, undefined. |
| **`__SSE__`** | Defined as 1 when the /arch:SSE, /arch:SSE2, /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined. |
| **`__SSE2__`** | Defined as 1 when the /arch:SSE2, /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined. |
| **`_STDCALL_SUPPORTED`** | Defined as 1 when the /Gz option is set. Otherwise, undefined. |
| **`_UNICODE`** | Defined as 1 when the /ws option is set. Otherwise, undefined. |
| **`__UNIX__`** | Defined as 1 when the /elf or /elf64 options are set. Otherwise, undefined. |
| **`_WIN64`** | Defined as 1 when the compilation target is 64-bit. Otherwise, undefined. |


### Other predefined text macros

| | |
| -------- |:------- |
| **@Version** | Defined as an integer literal value that represents the compatible version of Masm. Currently 800 for Asmc and 1000 for Asmc64. This macro is always defined. |
| **@Date** | The compilation date of the current source file. The date is a constant length string literal of the form yyyy-mm-dd. This macro is always defined. |
| **@Time** | Specifies path for temporary files. This macro is always defined. |
| **@FileName** | The name of the current source file. This expands to a upcase character string literal of _name_, "name.asm" --> "NAME". This macro is always defined. |
| **@FileCur** | The name of the current source file. This expands to a character string literal. This macro is always defined. |
| **@Line** | Defined as the integer line number in the current source file. This macro is always defined. |

#### See Also

[Asmc Command-Line Reference](readme.md)
