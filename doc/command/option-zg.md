Asmc Macro Assembler Reference

## option -Zg

Generate code to match Masm.

**Asmc generated code versus JWasm and Masm (-Zg).**

<table border="3">
<tr><td><b>Expression</b></td><td><b>Asmc</b></td><td><b>JWasm</b></td><td><b>-Zg</b> (Masm)</td></tr>
<tr><td>[!]reg [== 0]</td><td><i>test reg,reg</i></td><td><i>cmp reg,0</i></td><td><i>or reg,reg</i></td></tr>
<tr><td>xmm &lt;=&gt; xmm</td><td><i>comiss xmm,xmm</i></td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>test m32,1</td><td><i>byte ptr m32</i></td><td><i>dword ptr m32</i></td><td><i>dword ptr m32</i></td></tr>
<tr><td>test m64,1</td><td><i>byte ptr m64</i></td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>or m,0x0100</td><td><i>byte ptr m[-1]</i></td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>prologue</td><td><i>sub r/e/sp, size</i></td><td><i>sub r/e/sp, size</i></td><td><i>add r/e/sp, -size</i></td></tr>
<tr><td>.untilcxz</td><td><i>dec ecx<br>jnz label</i></td><td><i>loop label</i></td><td><i>loop label</i></td></tr>
<tr><td><b>m64 param</b></td><td><i>r/m32</i></td><td><i>error</i></td><td><i>error A2114</i></td></tr>
<tr><td><i>signed</i></td><td><i>mov eax,r/m32<br>cdq<br>push edx<br>push eax</i></td><td>---</td><td>---</td></tr>
<tr><td><i>unsigned</i></td><td><i>push 0<br>push r/m32</i></td><td>---</td><td>---</td></tr>
<tr><td><b>Mem operand</b></td><td><i>acc</i></td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>mov mem,mem</td><td>--- <i>[rep movs]</i></td><td>---</td><td>---</td></tr>
<tr><td>cmp ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>test ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>adc ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>add ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>sbb ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>sub ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>and ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>or ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>xor ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>comiss m32,m32</td><td><i>xmm</i></td><td>---</td><td>---</td></tr>
<tr><td>comisd m64,m64</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td><b>Float operand</b></td><td><i>data label</i></td><td><i>error</i></td><td><i>error</i></td></tr>
<tr><td>movaps xmm,imm</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>mov/s/d ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>movs/s/d ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>adds/s/d ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>subs/s/d ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>muls/s/d ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>divs/s/d ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>comis/s/d ---</td><td>---</td><td>---</td><td>---</td></tr>
<tr><td>ucomis/s/d ---</td><td>---</td><td>---</td><td>---</td></tr>
</table>

#### See Also

[Asmc Command-Line Reference](readme.md)
