Asmc Macro Assembler Reference

## ASMCALL

User Defined Convention.

Registers are by default assigned to arguments in the order AX/DX/CX, EAX/EDX/ECX, or RAX/RDX/RCX/R8/R9/R10/R11. Arguments are assigned from right to left.

The 32 and 64-bit version assign float values to SIMD registers 0 to 15.

<table>
<tr><td><b>asmcall</b></td><td><b>param</b></td><td><b>max</b></td><td><b>min</b></td><td><b>clean-up</b></td><td><b>mangle</b></td></tr>
<tr><td>16-bit</td><td>reg</td><td>4</td><td>2</td><td>caller</td><td>foo</td></tr>
<tr><td>32-bit</td><td>reg</td><td>8</td><td>4</td><td>caller</td><td>foo</td></tr>
<tr><td>64-bit</td><td>reg</td><td>16</td><td>4</td><td>caller</td><td>foo</td></tr>
</table>

Register param are sign-extended to **min** and register-pair are allowed up to **max**.

#### See Also

[Procedures](procedures.md) | [Directives Reference](readme.md) | [.PRAGMA](dot-pragma.md)
