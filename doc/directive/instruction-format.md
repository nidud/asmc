Asmc Macro Assembler Reference

# Instruction Format

## Syntax

Instructions are written in source code according to this syntax:

_prefix mnemonic operand-list_

## Prefix

You can prefix some instructions with keywords that set options for how the instruction is encoded. The REP, REPE, REPZ, REPNE, and REPNZ keywords are used with string instructions to do memcpy or strlen kinds of operations in a single instruction. The LOCK keyword makes certain operations on memory operands atomic. You can combine it with the XACQUIRE and XRELEASE keywords to do Hardware Lock Elision (HLE) on supported processors, which allows greater transactional parallelism in certain cases.

The remaining prefixes control how AVX instructions are encoded.

<table>
<tr><td><b>Keyword</b></td><td><b>Usage</b></td></tr>
<tr><td><b>REP</b></td><td>Repeat the string operation by the count in (E)CX.</td></tr>
<tr><td><b>REPE, REPZ</b></td><td>Repeat the string operation while the comparison is equal, limited by the count in (E)CX.</td></tr>
<tr><td><b>REPNE, REPNZ</b></td><td>Repeat the string operation while the comparison is not-equal, limited by the count in (E)CX.</td></tr>
<tr><td><b>LOCK</b></td><td>Perform the operation atomically on a memory operand.</td></tr>
<tr><td><b>XACQUIRE</b></td><td>Begin an HLE transaction, most often used with LOCK prefix.</td></tr>
<tr><td><b>XRELEASE</b></td><td>Complete an HLE transaction, most often used with LOCK prefix.</td></tr>
<tr><td><b>VEX</b></td><td>Encode an AVX instruction using a VEX prefix.</td></tr>
<tr><td><b>VEX2</b></td><td>Encode an AVX instruction using a 2-byte VEX prefix.</td></tr>
<tr><td><b>VEX3</b></td><td>Encode an AVX instruction using a 3-byte VEX prefix.</td></tr>
<tr><td><b>EVEX, {evex}</b></td><td>Encode an AVX instruction using an EVEX prefix.</td></tr>
</table>

### EVEX

The Enhanced Vector Extension (EVEX) encoding prefix will be omitted by using an EVEX exclusive instruction or any of the extended SIMD registers. A preceding prefix may be used for EVEX encoding of other instructions.

```assembly
  vaddps xmm1 {k1}, xmm2, xmm3            ; merge-masking
  vsubps ymm0 {k4}{z}, ymm1, ymm2         ; zero-masking
  vmulps zmm0, zmm1, dword bcst [rcx]     ; embedded broadcast
  vdivps zmm0, zmm1, zmm2 {rz-sae}        ; embedded rounding
  vmaxss xmm1, xmm2, xmm3 {sae}           ; suppress all exceptions
```

### Modifiers

<table>
<tr><td><b>{sae}</b></td><td>Suppress All Exceptions</td></tr>
<tr><td><b>{k1}</b></td><td>Merge Mask</td></tr>
<tr><td><b>{k1}{z}</b></td><td>Zero Mask</td></tr>
</table>

### Rounding modes

<table>
<tr><td><b>{rn-sae}</b></td><td>To nearest or even</td></tr>
<tr><td><b>{rd-sae}</b></td><td>Toward negative infinity</td></tr>
<tr><td><b>{ru-sae}</b></td><td>Toward positive infinity</td></tr>
<tr><td><b>{rz-sae}</b></td><td>Toward zero</td></tr>
</table>

#### See Also

[Directives Reference](readme.md) | [Option AVXENCODING](option-avxencoding.md)
