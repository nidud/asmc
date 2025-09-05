Asmc Macro Assembler Reference

## FASTCALL

Microsoft \_\_fastcall Convention.

Registers are assigned to arguments in the order AX/DX/BX, ECX/EDX, or RCX/RDX/R8/R9. Arguments (except from 16-bit) are assigned from right to left.

<table>
<tr><td><b>fastcall</b></td><td><b>param</b></td><td><b>max</b></td><td><b>min</b></td><td><b>clean-up</b></td><td><b>mangle</b></td></tr>
<tr><td>16-bit</td><td>reg</td><td>4</td><td>2</td><td>callee</td><td>@foo@n</td></tr>
<tr><td>32-bit</td><td>reg</td><td>4</td><td>4</td><td>callee</td><td>@foo@n</td></tr>
<tr><td>64-bit</td><td>stack</td><td>16</td><td>4</td><td>caller</td><td>foo</td></tr>
</table>

Register param are sign-extended to **min** and register-pair are allowed up to **max**.

### Microsoft x64 calling convention

This is a _standard C calling convention_ with some additions, so a C-style call to a prototype with one integer argument could thus be rendered like this:
```
push    rbp     ; align 16
mov     rbp,rsp
mov     ecx,1   ; integer argument passed in register
push    0       ; mandatory stack: 4*8
push    0
push    0       ; - the standard C convention:
push    rcx     ; * push 1
call    foo     ; * call foo
add     rsp,4*8 ; * standard C clean-up
leave           ; * add  rsp,8

```

As it's not mandated by the ABI to fill the first 4 stack positions with values, what's done by Asmc (and compilers in general) is something like this:
```
push    rbp
mov     rbp,rsp
sub     rsp,magic-number

assign arguments (register and stack)
call function-1
assign arguments
call function-2
...
assign arguments
call function-n

leave

```
The _magic-number_ is calculated from the maximum number of parameters used inside the frame + locals + saved nonvolatile-register + alignment. This means that RSP is always aligned 16 and points to the first argument, and the first assigned stack argument is RSP+32.

Parameter refer to the stack-position here rather than the register, so if the _callee_ uses (touch) any of these parameters a stack-frame is created and the register is saved to the stack:
```
    option win64:auto save

foo proc a1:word, a2:dword
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

For **Varargs** (_and Unprototyped functions according to the ABI_) floating-point values are assign both to the integer register and the floating-point register as [double precision](real8.md). Unprototyped means _immediate values_ or _SIMD registers_ here, but it also means that fully prototyped float values are converted to double precision as shown in the following example:

```
    .data
     d real8 2.0
     f real4 6.0
...
    printf(rax, d, xmm1, real4 ptr xmm2, 5.0, f)

    * cvtss2sd xmm0, dword ptr [f]
    * movsd   qword ptr [rsp+28H], xmm0
    * mov     dword ptr [rsp+20H], 0x00000000
    * mov     dword ptr [rsp+24H], 0x40140000
    * cvtss2sd xmm3, xmm2
    * movq    r9, xmm3
    * movsd   xmm2, xmm1
    * movq    r8, xmm2
    * movsd   xmm1, qword ptr [d]
    * movq    rdx, xmm1
    * mov     rcx, rax
    * call    printf
```
#### See Also

[Procedures](procedures.md) | [Directives Reference](readme.md)
