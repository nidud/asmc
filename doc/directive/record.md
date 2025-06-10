Asmc Macro Assembler Reference

## RECORD

recordname **RECORD** fieldname:width [[= expression]] [[, fieldname:width [[= expression]]]]...

Declares a record type consisting of the specified fields. fieldname names the field, width specifies the number of bits, and expression gives its initial value.

The first field in the declaration always goes into the most significant bits of the record. Subsequent fields are placed to the right in the succeeding bits. If the fields do not total exactly 8, 16, or 32 bits as appropriate, the entire record is shifted right, so the last bit of the last field is the lowest bit of the record. Unused bits in the high end of the record are initialized to 0.

### Embedded records

Asmc also allows embedded C-style records in structures in the same way as STRUC and UNION.

```
name STRUC
RECORD [[ name ]]
 fieldname type:width ?
 ...
ENDS
name ENDS
```
Note that the record field names here are not global (Masm design flaw) and there are no packing as the size is predefined similar to C bit-fields, and the first field in the declaration always goes into the least significant bits of the record. Asmc support accessing record fields as follows:

```
.template T
    x   dd ?
    record q
     a  dd :  1 ?
     b  dd :  7 ?
     c  dd :  8 ?
     d  dd : 16 ?
    ends
   .ends

```
Record fields are bit offsets from RECORD and Record names byte offsets from Type.

<table>
<tr><td><b>Const</b></td><td><b>Value</b></td><td></td></tr>
<tr><td><b>T.q</b></td><td>4</td><td>Byte offset from T</td></tr>
<tr><td><b>T.q.b</b></td><td>1</td><td>Bit offset from q</td></tr>
<tr><td><b>maskof(T.q.c)</b></td><td>0000FF00</td><td></td></tr>
</table>

Memory operands are optimized for expression evaluation so the CMP instruction should not be used directly for testing bit-flags.

<table>
<tr><td><b>Instruction</b></td><td><b>Op1</b></td><td><b>Op2</b></td><td><b>Action</b></td></tr>
<tr><td>CMP</td><td>a</td><td>0</td><td>TEST a, 1</td></tr>
<tr><td>CMP</td><td>a</td><td>1</td><td>TEST a, 1</td></tr>
<tr><td><i>expression</i></td><td>a</td><td></td><td>TEST/JZ</td></tr>
<tr><td><i>expression</i></td><td>a ==</td><td>0</td><td>TEST/JNZ</td></tr>
<tr><td><i>expression</i></td><td>a ==</td><td>1</td><td>TEST/JZ</td></tr>
<tr><td>CMP</td><td>b</td><td>0</td><td>TEST</td></tr>
<tr><td>CMP</td><td>b</td><td>1</td><td>MOV/AND/CMP</td></tr>
<tr><td>CMP</td><td>c</td><td>1</td><td>CMP</td></tr>
<tr><td>TEST</td><td>a</td><td>1</td><td>TEST</td></tr>
<tr><td>TEST</td><td>b</td><td>1</td><td>TEST</td></tr>
<tr><td>TEST</td><td>c</td><td>1</td><td>TEST</td></tr>
<tr><td>OR</td><td>a</td><td>1</td><td>OR</td></tr>
<tr><td>OR</td><td>b</td><td>1</td><td>OR</td></tr>
<tr><td>OR</td><td>c</td><td>1</td><td>OR</td></tr>
<tr><td>XOR</td><td>a</td><td>1</td><td>XOR</td></tr>
<tr><td>XOR</td><td>b</td><td>1</td><td>XOR</td></tr>
<tr><td>XOR</td><td>c</td><td>1</td><td>XOR</td></tr>
<tr><td>MOV</td><td>a</td><td>0</td><td>AND</td></tr>
<tr><td>MOV</td><td>a</td><td>1</td><td>OR</td></tr>
<tr><td>MOV</td><td>b</td><td>1</td><td>AND/OR</td></tr>
<tr><td>MOV</td><td>c</td><td>1</td><td>MOV</td></tr>
<tr><td>MOV</td><td>a</td><td>EAX</td><td>AND/OR</td></tr>
<tr><td>MOV</td><td>b</td><td>EAX</td><td>SHL/AND/OR</td></tr>
<tr><td>MOV</td><td>c</td><td>EAX</td><td>MOV</td></tr>
<tr><td>MOV</td><td>d</td><td>EAX</td><td>MOV</td></tr>
<tr><td>MOV</td><td>EAX</td><td>a</td><td>MOV/AND</td></tr>
<tr><td>MOV</td><td>EAX</td><td>b</td><td>MOV/AND/SHR</td></tr>
<tr><td>MOV</td><td>EAX</td><td>c</td><td>MOVZX</td></tr>
<tr><td>MOV</td><td>EAX</td><td>d</td><td>MOVZX</td></tr>
</table>

#### See Also

[Structure and Record](structure-and-record.md) | [Directives Reference](readme.md)
