Asmc Macro Assembler Reference

# Processor

The CPU directive enables assembly of instructions for the given processor and disables assembly of instructions introduced with later processors.

<table>
<tr><td><b>.8086</b></td><td>8086 and 8087 (and the identical 8088) instructions. This is the default mode for processors.</td></tr>
<tr><td><b>.8087</b></td><td>8087 instructions. This is the default mode for coprocessors.</td></tr>
<tr><td><b>.NO87</b></td><td>Disallows assembly of all floating-point instructions.</td></tr>
<tr><td><b>.186</b></td><td>80186 and 8087 instructions.</td></tr>
<tr><td><b>.286</b></td><td>80286 and 80287 nonprivileged instructions.</td></tr>
<tr><td><b>.286p</b></td><td>80286 and 80287 privileged instructions.</td></tr>
<tr><td><b>.287</b></td><td>80287 instructions.</td></tr>
<tr><td><b>.386</b></td><td>80386 and 80387 nonprivileged instructions.</td></tr>
<tr><td><b>.386p</b></td><td>80386 and 80387 privileged instructions.</td></tr>
<tr><td><b>.387</b></td><td>80387 instructions.</td></tr>
<tr><td><b>.486</b></td><td>80486 nonprivileged instructions.</td></tr>
<tr><td><b>.486p</b></td><td>80486 privileged instructions.</td></tr>
<tr><td><b>.586</b></td><td>Pentium nonprivileged instructions.</td></tr>
<tr><td><b>.586p</b></td><td>Pentium privileged instructions.</td></tr>
<tr><td><b>.686</b></td><td>Pentium Pro nonprivileged instructions.</td></tr>
<tr><td><b>.686p</b></td><td>Pentium Pro privileged instructions.</td></tr>
<tr><td><b>.K3D</b></td><td>K3D instructions.</td></tr>
<tr><td><b>.MMX</b></td><td>MMX or single-instruction, multiple data (SIMD) instructions.</td></tr>
<tr><td><b>.XMM</b></td><td>Internet Streaming SIMD Extension instructions.</td></tr>
<tr><td><b>.X64</b></td><td>x86-64 nonprivileged instructions.</td></tr>
<tr><td><b>.X64p</b></td><td>x86-64 privileged instructions.</td></tr>
</table>

#### See Also

[Directives Reference](readme.md) | [option CPU](../command/option-cpu.md)
