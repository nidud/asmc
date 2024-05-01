Asmc Macro Assembler Reference

## @Cpu

A bit mask specifying the processor mode (numeric equate).

#### bit mask

```
Bits     Mode

0x0001   No FPU
0x0002   8087
0x0003   80287
0x0004   80387
0x0008   Privileged opcode
0x0000   8086 (default)
0x0010   80186
0x0020   80286
0x0030   80386
0x0040   80486
0x0050   Pentium
0x0060   Pentium Pro
0x0070   x64 cpu
0x0100   MMX extension instructions
0x0200   3DNow extension instructions
0x0400   SSE1 extension instructions
0x0800   SSE2 extension instructions
0x1000   SSE3 extension instructions
0x2000   SSSE3 extension instructions
0x4000   SSE4 extension instructions
0x8000   AVX extension instructions
```
#### See Also

[Symbols Reference](readme.md)

