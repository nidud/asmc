Asmc Macro Assembler Reference

# Predefined macros

The Asmc assembler predefines certain preprocessor macros depending on the target and the chosen assembler options.

_macros_

The macros listed in the following table.

- **\_\_ASMC\_\_**
Defined as an integer literal that represents the version of Asmc. This macro is always defined.

- **\_\_ASMC64\_\_**
Defined as an integer literal that represents the version of Asmc64. This macro is defined by ASMC64.EXE.

- **\_\_AVX\_\_**
Defined as 1 when the /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined.

- **\_\_AVX2\_\_**
Defined as 1 when the /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined.

- **\_\_AVX512BW\_\_**
- **\_\_AVX512CD\_\_**
- **\_\_AVX512DQ\_\_**
- **\_\_AVX512F\_\_**
- **\_\_AVX512VL\_\_**
Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined.

- **\_\_COMPACT\_\_**
Defined as 1 when the /mc option is set. Otherwise, undefined.

- **\_\_DEBUG\_\_**
Defined as 1 when the /Zi option is set. Otherwise, undefined.

- **\_\_FLAT\_\_**
Defined as 1 when the /mf option is set. Otherwise, undefined.

- **\_\_GUI\_\_**
Defined as 1 when the /gui option is set. Otherwise, undefined.

- **\_\_HUGE\_\_**
Defined as 1 when the /mh option is set. Otherwise, undefined.

- **\_\_JWASM\_\_**
Defined as an integer literal value 212 that represents the compatible version of JWasm. This macro is always defined.

- **\_\_LARGE\_\_**
Defined as 1 when the /ml option is set. Otherwise, undefined.

- **\_M\_IX86\_FP**
Defined as 1 when the /arch:IA32 option is set. Otherwise, undefined.

- **\_\_MEDIUM\_\_**
Defined as 1 when the /mm option is set. Otherwise, undefined.

- **\_MSVCRT**
Defined as 1 when the /nolib option is set. Otherwise, undefined.

- **\_\_PE\_\_**
Defined as 1 when the /pe option is set. Otherwise, undefined.

- **\_\_P186\_\_**
Defined as 1 when the /1 option is set. Otherwise, undefined.

- **\_\_P286\_\_**
Defined as 1 when the /2 option is set. Otherwise, undefined.

- **\_\_P386\_\_**
Defined as 1 when the /3 option is set. Otherwise, undefined.

- **\_\_P486\_\_**
Defined as 1 when the /4 option is set. Otherwise, undefined.

- **\_\_P586\_\_**
Defined as 1 when the /5 option is set. Otherwise, undefined.

- **\_\_P64\_\_**
Defined as 1 when the /10 option is set. Otherwise, undefined.

- **\_\_P686\_\_**
Defined as 1 when the /6, /7, /8, or /9 option is set. Otherwise, undefined.

- **\_\_P86\_\_**
Defined as 1 when the /0 option is set. Otherwise, undefined.

- **\_\_SMALL\_\_**
Defined as 1 when the /ms option is set. Otherwise, undefined.

- **\_\_SSE\_\_**
Defined as 1 when the /8, /9, /arch:SSE, /arch:SSE2, /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined.

- **\_\_SSE2\_\_**
Defined as 1 when the /9, /arch:SSE2, /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined.

- **\_STDCALL\_SUPPORTED**
Defined as 1 when the /Gz option is set. Otherwise, undefined.

- **\_\_TINY\_\_**
Defined as 1 when the /mt option is set. Otherwise, undefined.

- **\_UNICODE**
Defined as 1 when the /ws option is set. Otherwise, undefined.

- **\_\_UNIX\_\_**
Defined as 1 when the /elf or /elf64 options are set. Otherwise, undefined.

- **\_WIN64**
Defined as 1 when the compilation target is 64-bit. Otherwise, undefined.

#### See Also

[Symbols Reference](readme.md)
