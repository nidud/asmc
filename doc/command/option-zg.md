Asmc Macro Assembler Reference

## option -Zg

Generate code to match Masm.

**Asmc generated code versus JWasm and Masm (-Zg).**

<table border="3">
<tr><td><b>Expression</b></td><td><b>Asmc</b></td><td><b>JWasm</b></td><td><b>-Zg</b> (Masm)</td></tr>
<tr><td>[!]reg [== 0]</td><td><i>test reg,reg</i></td><td><i>cmp reg,0</i></td><td><i>or reg,reg</i></td></tr>
<tr><td>xmm [] xmm</td><td><i>comiss xmm,xmm</i></td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>.untilcxz</td><td><i>dec ecx<br>jnz label</i></td><td><i>loop label</i></td><td><i>loop label</i></td></tr>
<tr><td>test m32,1</td><td><i>byte ptr m32</i></td><td><i>dword ptr m32</i></td><td><i>dword ptr m32</i></td></tr>
<tr><td>test m64,1</td><td><i>byte ptr m64</i></td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>or m,0x0100</td><td><i>byte ptr m[-1]</i></td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>mov mem,mem</td><td><i>uses ?ax<br>or rep movsb</i></td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>cmp mem,mem</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>test mem,mem</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>adc mem,mem</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>add mem,mem</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>sbb mem,mem</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>sub mem,mem</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>and mem,mem</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>or mem,mem</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>xor mem,mem</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>comiss m32,m32</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>comisd m64,m64</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>movaps xmm,imm</td><td><i>imm to .data</i></td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>movq xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>movsd xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>addsd xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>subsd xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>mulsd xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>divsd xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>comisd xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>ucomisd xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>movd xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>movss xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>addss xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>subss xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>mulss xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>divss xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>comiss xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>ucomiss xmm,imm</td><td>---</td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td><b>foo proto :qword</b></td><td></td><td></td><td></td></tr>
<tr><td>foo(r/m32)</td><td><i>push 0<br>push m32</i></td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td><i>signed</i></td><td><i>mov eax,m32<br>cdq<br>push edx<br>push eax</i></td><td><i>error</i></td><td><i>error</i></td></tr>
</table>

#### See Also

[Asmc Command-Line Reference](readme.md)
