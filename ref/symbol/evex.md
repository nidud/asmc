Asmc Macro Assembler Reference

## Enhanced vector extension

{**evex**}

The EVEX encoding prefix will be omitted by using an EVEX exclusive instruction or any of the extended SIMD registers. A preceding prefix (**{evex}**) may be used for EVEX encoding of other instructions.

    vcomisd xmm0,xmm1        ; normal
    vcomisd xmm0,xmm16       ; prefix (auto)
    {evex} vcomisd xmm0,xmm1 ; prefix

#### See Also

[Symbols Reference](readme.md)