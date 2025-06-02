Asmc Macro Assembler Reference

# Predefined macros

The Asmc assembler predefines certain preprocessor macros depending on the target and the chosen assembler options.

_macros_

The macros listed in the following table.

<table>
<tr><td><b>__ASMC__</b></td><td>Defined as an integer literal that represents the version of Asmc. This macro is always defined.</td></tr>
<tr><td><b>__ASMC64__</b></td><td>Defined as an integer literal that represents the version of Asmc64. This macro is defined by ASMC64.</td></tr>
<tr><td><b>__AVX__</b></td><td>Defined as 1 when the /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined.</td></tr>
<tr><td><b>__AVX2__</b></td><td>Defined as 1 when the /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined.</td></tr>
<tr><td><b>__AVX512BW__</b></td><td>Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__AVX512CD__</b></td><td>Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__AVX512DQ__</b></td><td>Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__AVX512F__</b></td><td>Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__AVX512VL__</b></td><td>Defined as 1 when the /arch:AVX512 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__COMPACT__</b></td><td>Defined as 1 when the /mc option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__DEBUG__</b></td><td>Defined as 1 when the /Zi option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__FLAT__</b></td><td>Defined as 1 when the /mf option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__GUI__</b></td><td>Defined as 1 when the /gui option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__HUGE__</b></td><td>Defined as 1 when the /mh option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__JWASM__</b></td><td>Defined as an integer literal value 212 that represents the compatible version of JWasm. This macro is always defined.</td></tr>
<tr><td><b>__LARGE__</b></td><td>Defined as 1 when the /ml option is set. Otherwise, undefined.</td></tr>
<tr><td><b>_M_IX86_FP</b></td><td>Defined as 1 when the /arch:IA32 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__MEDIUM__</b></td><td>Defined as 1 when the /mm option is set. Otherwise, undefined.</td></tr>
<tr><td><b>_MSVCRT</b></td><td>Defined as 1 when the /nolib option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__PE__</b></td><td>Defined as 1 when the /pe option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__P186__</b></td><td>Defined as 1 when the /1 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__P286__</b></td><td>Defined as 1 when the /2 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__P386__</b></td><td>Defined as 1 when the /3 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__P486__</b></td><td>Defined as 1 when the /4 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__P586__</b></td><td>Defined as 1 when the /5 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__P64__</b></td><td>Defined as 1 when the /10 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__P686__</b></td><td>Defined as 1 when the /6, /7, /8, or /9 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__P86__</b></td><td>Defined as 1 when the /0 option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__SMALL__</b></td><td>Defined as 1 when the /ms option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__SSE__</b></td><td>Defined as 1 when the /8, /9, /arch:SSE, /arch:SSE2, /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined.</td></tr>
<tr><td><b>__SSE2__</b></td><td>Defined as 1 when the /9, /arch:SSE2, /arch:AVX, /arch:AVX2, or /arch:AVX512 options are set. Otherwise, undefined.</td></tr>
<tr><td><b>_STDCALL_SUPPORTED</b></td><td>Defined as 1 when the /Gz option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__TINY__</b></td><td>Defined as 1 when the /mt option is set. Otherwise, undefined.</td></tr>
<tr><td><b>_UNICODE</b></td><td>Defined as 1 when the /ws option is set. Otherwise, undefined.</td></tr>
<tr><td><b>__UNIX__</b></td><td>Defined as 1 when the /elf or /elf64 options are set. Otherwise, undefined.</td></tr>
<tr><td><b>_WIN64</b></td><td>Defined as 1 when the compilation target is 64-bit. Otherwise, undefined.</td></tr>
</table>

#### See Also

[Symbols Reference](readme.md)
