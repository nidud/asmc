Asmc Macro Assembler Reference

## VECTORCALL

Microsoft \_\_vectorcall Convention.

Registers are assigned to arguments in the order ECX/EDX or RCX/RDX/R8/R9. Arguments are assigned from right to left.

In addition vectorcall support passing 6 SIMD registers. In 64-bit the arguments are fixed (max 6) but "floating" in 32-bit (max 8).

<table>
<tr><td><b>vectorcall</b></td><td><b>param</b></td><td><b>max</b></td><td><b>min</b></td><td><b>clean-up</b></td><td><b>mangle</b></td></tr>
<tr><td>16-bit</td><td>-</td><td>-</td><td>-</td><td>-</td><td>-</td></tr>
<tr><td>32-bit</td><td>reg</td><td>4</td><td>4</td><td>callee</td><td>foo@@n</td></tr>
<tr><td>64-bit</td><td>stack</td><td>16</td><td>4</td><td>caller</td><td>foo@@n</td></tr>
</table>

Register param are sign-extended to **min** and register-pair are allowed up to **max**.

The caller allocates stack for arguments in 64-bit, so parameter refer to the stack-position rather than the register. If the callee uses (touch) any of these parameters a stack-frame is created and the register is saved to the stack:
```
    option win64:auto save

foo proc vectorcall a1:word, a2:dword
    mov si,a1 ; use parameter
    ret
foo endp

0000 mov     [rsp+8H], rcx
0005 push    rbp
0006 mov     rbp, rsp
0009 mov     si, [rbp+10H]
000D leave
000E ret
...
    mov si,cx ; use register

0000 mov     si, cx
0003 ret
```

#### See Also

[Procedures](procedures.md) | [Directives Reference](readme.md)
