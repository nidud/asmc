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
<tr><td>T.q</td><td>4</td><td>Byte offset from T</td></tr>
<tr><td>T.q.b</td><td>1</td><td>Bit offset from q</td></tr>
<tr><td>maskof T.q.c</td><td>0000FF00</td><td></td></tr>
</table>

Memory operands are optimized for expression evaluation.

<table>
<tr><td><b>Instruction</b></td><td><b>Op 1</b></td><td><b>Op 2</b></td><td><b>Action</b></td></tr>
<tr><td>CMP</td><td>a</td><td>0</td><td>TEST</td></tr>
<tr><td>CMP</td><td>a</td><td>1</td><td>MOV/AND/CMP</td></tr>
<tr><td><i>expression</i></td><td>a</td><td></td><td>TEST/JZ</td></tr>
<tr><td><i>expression</i></td><td>a ==</td><td>0</td><td>TEST/JNZ</td></tr>
<tr><td><i>expression</i></td><td>a ==</td><td>1</td><td>TEST/JZ</td></tr>
</table>

#### Supported memory-operands instructions.

<table>
<tr><td><b>Instruction</b></td><td><b>64-Bit</b></td><td><b>32-bit</b></td><td><b>Description</b></td></tr>
<tr><td>MOV mem, imm</td><td>Valid</td><td>Valid</td><td>Move imm to m.field</td></tr>
<tr><td>MOV m64, i64</td><td>Valid</td><td>Valid</td><td>Move i64 to m64.field</td></tr>
<tr><td>MOV mem, reg</td><td>Valid</td><td>Valid</td><td>Move register to m.field</td></tr>
<tr><td>MOV m64, r64</td><td>Valid</td><td>N.E.</td><td>Move r64 to m64.field</td></tr>
<tr><td>MOV reg, mem</td><td>Valid</td><td>Valid</td><td>Move m.field to register</td></tr>
<tr><td>MOV r64, m64</td><td>Valid</td><td>N.E.</td><td>Move m64.field to r64</td></tr>
<tr><td>MOV mem, mem</td><td>Valid</td><td>Valid</td><td>Move m.field to m.field</td></tr>
<tr><td>CMP mem, imm</td><td>Valid</td><td>Valid</td><td>Compare imm to m.field</td></tr>
<tr><td>TEST mem, imm</td><td>Valid</td><td>Valid</td><td>Logical Compare m.field</td></tr>
<tr><td>OR mem, imm</td><td>Valid</td><td>Valid</td><td>Logical Inclusive OR on m.field</td></tr>
<tr><td>XOR mem, imm</td><td>Valid</td><td>Valid</td><td>Logical Exclusive OR on m.field</td></tr>
</table>

#### See Also

[Directives Reference](readme.md) | [Structure and Record](structure-and-record.md) | [MASKOF](../operator/operator-maskof.md) | [WIDTHOF](../operator/operator-widthof.md)
