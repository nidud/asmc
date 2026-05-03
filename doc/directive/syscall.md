Asmc Macro Assembler Reference

## SYSCALL

System V AMD64 ABI Convention.

- Stack aligned on 16 bytes boundary.
- 128 bytes red zone below stack.
- The kernel interface uses RDI, RSI, RDX, R10, R8 and R9.
- In C++, this is the first parameter.

Registers are assigned to arguments in the order RDI, RSI, RDX, RCX, R8, R9. Arguments are assigned from right to left.

In addition syscall support passing 8 SIMD registers and param-positions are not fixed.

<table>
<tr><td><b>syscall</b></td><td><b>param</b></td><td><b>max</b></td><td><b>min</b></td><td><b>clean-up</b></td><td><b>mangle</b></td></tr>
<tr><td>16-bit</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr>
<tr><td>32-bit</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr>
<tr><td>64-bit</td><td>stack</td><td>16</td><td>4</td><td>caller</td><td>foo</td></tr>
</table>

Register param are sign-extended to **min** and register-pair are allowed up to **max**.

Asmc allocates stack for arguments so parameter refer to the stack-position rather than the register. If any of these parameters are used the register is saved to the stack:
```
    option win64:auto save

foo proc syscall a1:word, a2:dword
    mov ax,a1 ; use parameter
    ret
foo endp

0000 push    rbp
0001 mov     rbp, rsp
0004 sub     rsp, 16
0008 mov     word ptr [rbp-10H], di
000C mov     ax, word ptr [rbp-10H]
0010 leave
0011 ret
...
    mov ax,di ; use register

0000 push    rbp
0001 mov     rbp, rsp
0004 mov     ax, di
0007 leave
0008 ret
```
Note that a stack-frame is added here regardless if the argument is used or not as the ABI demand the stack to be aligned 16.

#### See Also

[Procedures](procedures.md) | [Directives Reference](readme.md)
