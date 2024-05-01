Asmc Macro Assembler Reference

# Asmc Operators Reference

## Arithmetic

- [* (multiply)](operator-multiply.md)
- [+ (add)](operator-add.md)
- [- (subtract or negate)](operator-subtract.md)
- [. (field)](operator-field.md)
- [/ (divide)](operator-divide.md)
- [\[\] (index)](operator-index.md)
- [MOD (remainder)](operator-remainder.md)

## Control Flow

- [! (runtime logical not)](operator-logical-not.md)
- [!= (runtime not equal)](operator-not-equal.md)
- [|| (runtime logical or)](operator-logical-or.md)
- [&& (runtime logical and)](operator-logical-and.md)
- [&lt; (runtime less than)](operator-less-than.md)
- [&lt;= (runtime less or equal)](operator-less-or-equal.md)
- [== (runtime equal)](operator-equal.md)
- [&gt; (runtime greater than)](operator-greater-than.md)
- [&gt;= (runtime greater or equal)](operator-greater-or-equal.md)
- [& (runtime bitwise and)](operator-bitwise-and.md)
- [CARRY? (runtime carry test)](operator-carry-test.md)
- [OVERFLOW? (runtime overflow test)](operator-overflow-test.md)
- [PARITY? (runtime parity test)](operator-parity-test.md)
- [SIGN? (runtime sign test)](operator-sign-test.md)
- [ZERO? (runtime zero test)](operator-zero-test.md)

## Logical and Shift

- [ADD (bitwise add)](operator-bitwise-add.md)
- [AND (bitwise and)](operator-and.md)
- [DIV (bitwise divide)](operator-div.md)
- [MUL (bitwise multiply)](operator-mul.md)
- [NOT (bitwise not)](operator-not.md)
- [OR (bitwise or)](operator-or.md)
- [SAR (shift bits right)](operator-sar.md)
- [SAL (shift bits left)](operator-sal.md)
- [SHL (shift bits left)](operator-shl.md)
- [SHR (shift bits right)](operator-shr.md)
- [SUB (bitwise subtract)](operator-sub.md)
- [XOR (bitwise exclusive or)](operator-xor.md)

## Macro

- [! (character literal)](operator-logical-negation.md)
- [% (treat as text)](operator-percent.md)
- [;; (treat as comment)](operator-semicolons.md)
- [&lt; &gt; (treat as one literal)](operator-literal.md)
- [& & (substitute parameter value)](operator-substitution.md)

## Miscellaneous

- [' ' (treat as string)](operator-single-quote.md)
- [" " (treat as string)](operator-duoble-quote.md)
- [: (local label definition)](operator-colon.md)
- [:: (register segment and offset)](operator-double-colon.md)
- [:: (global label definition)](operator-double-colon.md)
- [; (treat as comment)](operator-semicolon.md)
- [ADDR (address of)](operator-addr.md)
- [DUP (repeat declaration)](operator-dup.md)

## Record

- [MASK (get record or field bitmask)](operator-mask.md)
- [MASKOF (get record or field bitmask)](operator-maskof.md)
- [WIDTH (get record or field width)](operator-width.md)

## Relational

- [EQ (equal)](operator-eq.md)
- [GE (greater or equal)](operator-ge.md)
- [GT (greater than)](operator-gt.md)
- [LE (less or equal)](operator-le.md)
- [LT (less than)](operator-lt.md)
- [NE (not equal)](operator-ne.md)

## Segment

- [: (segment override)](operator-colon.md)
- [:: (register segment and offset)](operator-duoble-colon.md)
- [IMAGEREL (image relative offset)](operator-imagerel.md)
- [LROFFSET (loader resolved offset)](operator-lroffset.md)
- [OFFSET (segment relative offset)](operator-offset.md)
- [SECTIONREL (section relative offset)](operator-sectionrel.md)
- [SEG (get segment)](operator-seg.md)

## Type

- [HIGH (high 8 bits of lowest 16 bits)](operator-high.md)
- [HIGH32 (high 32 bits of 64 bits)](operator-high32.md)
- [HIGH64 (high 64 bits of 128 bits)](operator-high64.md)
- [HIGHBYTE (high 8 bits of lowest 16 bits)](operator-highbyte.md)
- [HIGHWORD (high 16 bits of lowest 32 bits)](operator-highword.md)
- [LENGTH (number of elements in array)](operator-length.md)
- [LENGTHOF (number of elements in array)](operator-lengthof.md)
- [LOW (low 8 bits)](operator-low.md)
- [LOW32 (low 32 bits)](operator-low32.md)
- [LOW64 (low 64 bits)](operator-low64.md)
- [LOWBYTE (low 8 bits)](operator-lowbyte.md)
- [LOWWORD (low 16 bits)](operator-lowword.md)
- [OPATTR (get argument type info)](operator-opattr.md)
- [PTR (pointer to or as type)](operator-ptr.md)
- [SHORT (mark short label type)](operator-short.md)
- [SIZE (size of type or variable)](operator-size.md)
- [SIZEOF (size of type or variable)](operator-sizeof.md)
- [THIS (current location)](operator-this.md)
- [TYPE (get expression type)](operator-type.md)
- [TYPEID (get expression id)](operator-typeid.md)
- [TYPEOF (get expression type)](operator-typeof.md)
- [.TYPE (get argument type info)](operator-dot-type.md)

### See Also

[Directives Reference](directive.md)

