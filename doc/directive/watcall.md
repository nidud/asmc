Asmc Macro Assembler Reference

## WATCALL

Watcom Register Calling Convention.

Up to 4 registers are assigned to arguments in the order AX, DX, BX, CX. Arguments are assigned from right to left.

<table>
<tr><td>**watcall**</td><td>**param**</td><td>**max**</td><td>**min**</td><td>**clean-up**</td><td>**mangle**</td></tr>
<tr><td>16-bit</td><td>reg</td><td>8</td><td>2</td><td>callee</td><td>foo\_</td></tr>
<tr><td>32-bit</td><td>reg</td><td>16</td><td>4</td><td>caller</td><td>foo\_</td></tr>
<tr><td>64-bit</td><td>reg</td><td>16</td><td>4</td><td>caller</td><td>foo\_</td></tr>
</table>

Register param are sign-extended to **min** and register-pair are allowed up to **max**.

#### See Also

[Procedures](procedures.md) | [Directives Reference](readme.md)
