Asmc Macro Assembler Reference

# Asmc Operators Reference

## In This Section

- [Arithmetic](arithmetic.md)
- [Control Flow](control-flow.md)
- [Logical and Shift](logical-and-shift.md)
- [Macro](macro.md)
- [Miscellaneous](miscellaneous.md)
- [Record](record.md)
- [Relational](relational.md)
- [Segment](segment.md)
- [Type](type.md)

## Arithmetic

<table>
<tr><td><a href="operator-multiply.md">* (multiply)</a></td><td><a href="operator-field.md">. (field)</td></tr>
<tr><td><a href="operator-index.md">[] (index)</a></td><td><a href="operator-add.md">+ (add)</a></td></tr>
<tr><td><a href="operator-divide.md">/ (divide)</a></td><td><a href="operator-subtract.md">- (subtract or negate)</a></td></tr>
<tr><td><a href="operator-remainder.md">MOD (remainder)</a></td></tr>
</table>

## Control Flow

<table>
<tr><td><a href="operator-logical-not.md">! (runtime logical not)</a></td><td><a href="operator-less-or-equal.md">&lt;= (runtime less or equal)</a></td></tr>
<tr><td><a href="operator-not-equal.md">!= (runtime not equal)</a></td><td><a href="operator-equal.md">== (runtime equal)</a></td></tr>
<tr><td><a href="operator-logical-or.md">|| (runtime logical or)</a></td><td><a href="operator-greater-than.md">&gt; (runtime greater than)</a></td></tr>
<tr><td><a href="operator-logical-and.md">&& (runtime logical and)</a></td><td><a href="operator-greater-or-equal.md">&gt;= (runtime greater or equal)</a></td></tr>
<tr><td><a href="operator-less-than.md">&lt; (runtime less than)</a></td><td><a href="operator-bitwise-and.md">& (runtime bitwise and)</a></td></tr>
<tr><td><a href="operator-carry-test.md">CARRY? (runtime carry test)</a></td><td><a href="operator-overflow-test.md">OVERFLOW? (runtime overflow test)</a></td></tr>
<tr><td><a href="operator-parity-test.md">PARITY? (runtime parity test)</a></td><td><a href="operator-sign-test.md">SIGN? (runtime sign test)</a></td></tr>
<tr><td><a href="operator-zero-test.md">ZERO? (runtime zero test)</a></td></tr>
</table>

## Logical and Shift

<table>
<tr><td><a href="operator-bitwise-add.md">ADD (bitwise add)</a></td><td><a href="operator-and.md">AND (bitwise and)</a></td></tr>
<tr><td><a href="operator-div.md">DIV (bitwise divide)</a></td><td><a href="operator-mul.md">MUL (bitwise multiply)</a></td></tr>
<tr><td><a href="operator-not.md">NOT (bitwise not)</a></td><td><a href="operator-or.md">OR (bitwise or)</a></td></tr>
<tr><td><a href="operator-rol.md">ROL (Rotate bits left)</a></td><td><a href="operator-ror.md">ROR (Rotate bits right)</a></td></tr>
<tr><td><a href="operator-sar.md">SAR (shift bits right)</a></td><td><a href="operator-sal.md">SAL (shift bits left)</a></td></tr>
<tr><td><a href="operator-shl.md">SHL (shift bits left)</a></td><td><a href="operator-shr.md">SHR (shift bits right)</a></td></tr>
<tr><td><a href="operator-sub.md">SUB (bitwise subtract)</a></td><td><a href="operator-xor.md">XOR (bitwise exclusive or)</a></td></tr>
</table>

## Macro

<table>
<tr><td><a href="operator-logical-negation.md">! (character literal)</a></td><td><a href="operator-percent.md">% (treat as text)</a></td></tr>
<tr><td><a href="operator-semicolons.md">;; (treat as comment)</a></td><td><a href="operator-literal.md">&lt; &gt; (treat as one literal)</a></td></tr>
<tr><td><a href="operator-substitution.md">& & (substitute parameter value)</a></td></tr>
</table>

## Miscellaneous

<table>
<tr><td><a href="operator-single-quote.md">' ' (treat as string)</a></td><td><a href="operator-duoble-quote.md">" " (treat as string)</a></td></tr>
<tr><td><a href="operator-colon.md">: (local label definition)</a></td><td><a href="operator-double-colon.md">:: (register segment and offset)</a></td></tr>
<tr><td><a href="operator-double-colon.md">:: (global label definition)</a></td><td><a href="operator-semicolon.md">; (treat as comment)</a></td></tr>
<tr><td><a href="operator-addr.md">ADDR (address of)</a></td><td><a href="operator-dup.md">DUP (repeat declaration)</a></td></tr>
</table>

## Record

<table>
<tr><td><b>Masm specific</b></td><td><b>Asmc</b></td></tr>
<tr><td><a href="operator-mask.md">MASK (get record or field bitmask)</a></td><td><a href="operator-maskof.md">MASKOF</a></td></tr>
<tr><td><a href="operator-width.md">WIDTH (get record or field width)</a></td><td><a href="operator-widthof.md">WIDTHOF</a></td></tr>
</table>

## Relational

<table>
<tr><td><a href="operator-eq.md">EQ (equal)</a></td><td><a href="operator-ge.md">GE (greater or equal)</a></td></tr>
<tr><td><a href="operator-gt.md">GT (greater than)</a></td><td><a href="operator-le.md">LE (less or equal)</a></td></tr>
<tr><td><a href="operator-lt.md">LT (less than)</a></td><td><a href="operator-ne.md">NE (not equal)</a></td></tr>
</table>

## Segment

<table>
<tr><td><a href="operator-colon.md">: (segment override)</a></td><td><a href="operator-double-colon.md">:: (register segment and offset)</a></td></tr>
<tr><td><a href="operator-imagerel.md">IMAGEREL (image relative offset)</a></td><td><a href="operator-lroffset.md">LROFFSET (loader resolved offset)</a></td></tr>
<tr><td><a href="operator-offset.md">OFFSET (segment relative offset)</a></td><td><a href="operator-sectionrel.md">SECTIONREL (section relative offset)</a></td></tr>
<tr><td><a href="operator-seg.md">SEG (get segment)</a></td><td></td></tr>
</table>

## Type

<table>
<tr><td><b>Masm specific</b></td><td><b>Asmc</b></td></tr>
<tr><td><a href="operator-bcst.md">BCST (embedded broadcast type)</a></td><td>BCST</td></tr>
<tr><td><a href="operator-high.md">HIGH (high 8 bits of lowest 16 bits)</a></td><td><a href="operator-highbyte.md">HIGHBYTE</a></td></tr>
<tr><td><a href="operator-high32.md">HIGH32 (high 32 bits of 64 bits)</a></td><td>HIGH32</td></tr>
<tr><td>---</td><td><a href="operator-high64.md">HIGH64 (high 64 bits of 128 bits)</a></td></tr>
<tr><td><a href="operator-highword.md">HIGHWORD (high 16 bits of lowest 32 bits)</a></td><td>HIGHWORD</td></tr>
<tr><td><a href="operator-length.md">LENGTH (number of elements in array)</a></td><td><a href="operator-lengthof.md">LENGTHOF</a></td></tr>
<tr><td><a href="operator-low.md"></a>LOW (low 8 bits)</td><td><a href="operator-lowbyte.md">LOWBYTE</a></td></tr>
<tr><td><a href="operator-low32.md">LOW32 (low 32 bits)</a></td><td>LOW32</td></tr>
<tr><td>---</td><td><a href="operator-low64.md">LOW64 (low 64 bits)</a></td></tr>
<tr><td><a href="operator-lowword.md">LOWWORD (low 16 bits)</a></td><td>LOWWORD</td></tr>
<tr><td><a href="operator-opattr.md">OPATTR (get argument type info)</a></td><td>OPATTR</td></tr>
<tr><td><a href="operator-ptr.md">PTR (pointer to or as type)</a></td><td>PTR</td></tr>
<tr><td><a href="operator-short.md">SHORT (mark short label type)</a></td><td>SHORT</td></tr>
<tr><td><a href="operator-size.md">SIZE (size of type or variable)</a></td><td>SIZEOF</td></tr>
<tr><td><a href="operator-sizeof.md">SIZEOF (size of type or variable)</a></td><td>SIZEOF</td></tr>
<tr><td><a href="operator-this.md">THIS (current location)</a></td><td>---</td></tr>
<tr><td><a href="operator-type.md">TYPE (get expression type)</a></td><td><a href="operator-typeof.md">TYPEOF</a></td></tr>
<tr><td>---</td><td><a href="operator-typeid.md">TYPEID (get expression id)</a></td></tr>
<tr><td><a href="operator-dot-type.md">.TYPE (get argument type info)</a></td><td>.TYPE</td></tr>
</table>

### See Also

[Asmc Reference](../readme.md) | [Directives Reference](../directive/readme.md)

