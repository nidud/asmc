Asmc Macro Assembler Reference

## option -0..10[p]

Selects CPU/instruction set. Most values correspond to [cpu directives](../directive/processor.md).

<table>
<tr><td><b>Option</b></td><td><b>CPU directive</b></td><td><b>Defines</b></td></tr>
<tr><td>-0</td><td>.8086 (default)</td><td></td></tr>
<tr><td>-1</td><td>.186</td><td>__186__</td></tr>
<tr><td>-2</td><td>.286</td><td>__286__</td></tr>
<tr><td>-3</td><td>.386</td><td>__386__</td></tr>
<tr><td>-4</td><td>.486</td><td>__486__</td></tr>
<tr><td>-5</td><td>.586</td><td>__586__</td></tr>
<tr><td>-6</td><td>.686</td><td>__686__</td></tr>
<tr><td>-7</td><td>.686 and .MMX (P2)</td><td></td></tr>
<tr><td>-8</td><td>.686 and .MMX (P3)</td><td>__SSE__</td></tr>
<tr><td>-9</td><td>.686 and .MMX (P4)</td><td>__SSE2__</td></tr>
<tr><td>-10</td><td>.x64 (x86-64 cpu)</td><td>__P64__</td></tr>
</table>

[**p**] allows privileged instructions.

These options are not available in ASMC64.

#### See Also

[Asmc Command-Line Reference](readme.md) | [Processor](../directive/processor.md)
