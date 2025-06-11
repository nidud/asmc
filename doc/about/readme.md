Asmc Macro Assembler Reference

# About Asmc

Asmc is technically a slow-burning design project to make a functional programming language out of assembly. It started as a modified version of JWasm in 2011 with some simple but specific goals:

- Remove the necessity of labels.
- Merge macro and function calls.
- Enable data declaration where you need it.

The first issue is solved by improving and adding HLL extensions, the second by removing the [INVOKE](../directive/invoke.md) keyword so a function(with brackets) is handled as a macro. The last part is solved by extending the LOCAL functionality beyond the prologue and call it [NEW](../directive/dot-new.md).

So is there's any point trying to compete with modern optimized compilers? Given Asmc is written in assembly it's comparable to similar compiler-built assemblers.

Number of lines in the source code:

<table>
<tr><td><b>Assembler</b></td><td><b>Version</b></td><td><b>Source lines</b></td></tr>
<tr><td>JWASM</td><td>2.19</td><td>61526</td></tr>
<tr><td>UASM</td><td>2.47</td><td>100434</td></tr>
<tr><td>ASMC</td><td>2.36</td><td>94647</td></tr>
</table>

The first test is done on multiple files and the second testing the macro engine:

<table>
<tr><td><b>Assembler</b></td><td><b>Size</b></td><td><b>Machine</b></td><td><b>Clocks(1)</b></td><td><b>Clocks(2)</b></td></tr>
<tr><td>MASM</td><td>665K</td><td>AMD64</td><td>7458</td><td>5031</td></tr>
<tr><td>JWASM</td><td>311K</td><td>I386</td><td>5123</td><td>6437</td></tr>
<tr><td>UASM32</td><td>811K</td><td>I386</td><td>7116</td><td>7203</td></tr>
<tr><td>UASM64</td><td>942K</td><td>AMD64</td><td>6133</td><td>4421</td></tr>
<tr><td>ASMC</td><td>400K</td><td>I386</td><td>3250</td><td>3828</td></tr>
<tr><td>ASMC</td><td>451K</td><td>AMD64</td><td>3250</td><td>3812</td></tr>
</table>

#### See Also

[Asmc Reference](../readme.md) | [Instruction Format](../directive/instruction-format.md) | [Masm Compatible Opeators](../command/option-zne.md)

