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

Register parameters are sign-extended to the size indicated by the **min** column. If an argument requires more width than a single register, it may be passed using a register pair up to the limit specified by the **max** column.

### Microsoft x64 calling convention

This is the Microsoft x64 calling convention: a standard C calling convention with a few extensions. For example, a C-style call to a function taking a single 32-bit integer argument can be emitted like this:
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

Because the ABI does not require populating the first four stack slots, Asmc (and most compilers) reserve a fixed shadow space and allocate a frame large enough for the maximum parameters, locals, and saved registers. A typical sequence looks like this:
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
The _magic-number_ is calculated from the maximum number of parameter stack slots used inside the frame plus space for locals, saved nonvolatile registers, and any alignment padding (including the 32-byte shadow space required by the Microsoft x64 ABI). The frame size is rounded up to a 16-byte boundary. This ensures that RSP is always 16-byte aligned and points to the first argument slot; the first assigned stack argument is at RSP+32.

Parameters refer to the stack-position here rather than the register, so if the _callee_ uses (touches) any of these parameters a stack frame is created and the register is saved to the stack:
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

For **Varargs** (and unprototyped calls according to the ABI) each floating‑point argument is placed both in an XMM (floating‑point) register and in the corresponding integer register or stack slot as a 64‑bit double; `float` (32‑bit) values are promoted to double before placement. "Unprototyped" here means arguments without a prototype — for example immediates or SIMD register values. The following example shows the sequence used to prepare such arguments:

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
