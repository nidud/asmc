Asmc Macro Assembler Reference

# Asmc Operators Reference

## Arithmetic

- [* (multiply)](#operator-multiply)
- [+ (add)](#operator-add)
- [- (subtract or negate)](#operator-subtract)
- [. (field)](#operator-field)
- [/ (divide)](#operator-divide)
- [\[\] (index)](#operator-index)
- [MOD (remainder)](#operator-remainder)

## Control Flow

- [! (runtime logical not)](#operator-logical-not)
- [!= (runtime not equal)](#operator-not-equal)
- [|| (runtime logical or)](#operator-logical-or)
- [&& (runtime logical and)](#operator-logical-and)
- [< (runtime less than)](#operator-less-than)
- [<= (runtime less or equal)](#operator-less-or-equal)
- [== (runtime equal)](#operator-equal)
- [> (runtime greater than)](#operator-greater-than)
- [>= (runtime greater or equal)](#operator-greater-or-equal)
- [& (runtime bitwise and)](#operator-bitwise-and)
- [CARRY? (runtime carry test)](#operator-carry-test)
- [OVERFLOW? (runtime overflow test)](#operator-overflow-test)
- [PARITY? (runtime parity test)](#operator-parity-test)
- [SIGN? (runtime sign test)](#operator-sign-test)
- [ZERO? (runtime zero test)](#operator-zero-test)

## Logical and Shift

- [ADD (bitwise add)](#operator-bitwise-add)
- [AND (bitwise and)](#operator-and)
- [DIV (bitwise divide)](#operator-div)
- [MUL (bitwise multiply)](#operator-mul)
- [NOT (bitwise not)](#operator-not)
- [OR (bitwise or)](#operator-or)
- [SAR (shift bits right)](#operator-sar)
- [SAL (shift bits left)](#operator-sal)
- [SHL (shift bits left)](#operator-shl)
- [SHR (shift bits right)](#operator-shr)
- [SUB (bitwise subtract)](#operator-sub)
- [XOR (bitwise exclusive or)](#operator-xor)

## Macro

- [! (character literal)](#operator-logical-negation)
- [% (treat as text)](#operator-percent)
- [;; (treat as comment)](#operator-semicolons)
- [< > (treat as one literal)](#operator-literal)
- [& & (substitute parameter value)](#operator-substitution)

## Miscellaneous

- [' ' (treat as string)](#operator-single-quote)
- [" " (treat as string)](#operator-duoble-quote)
- [: (local label definition)](#operator-colon)
- [:: (register segment and offset)](#operator-double-colon)
- [:: (global label definition)](#operator-double-colon)
- [; (treat as comment)](#operator-semicolon)
- [ADDR (address of)](#operator-addr)
- [DUP (repeat declaration)](#operator-dup)

## Record

- [MASK (get record or field bitmask)](#operator-mask)
- [MASKOF (get record or field bitmask)](#operator-maskof)
- [WIDTH (get record or field width)](#operator-width)

## Relational

- [EQ (equal)](#operator-eq)
- [GE (greater or equal)](#operator-ge)
- [GT (greater than)](#operator-gt)
- [LE (less or equal)](#operator-le)
- [LT (less than)](#operator-lt)
- [NE (not equal)](#operator-ne)

## Segment

- [: (segment override)](#operator-colon)
- [:: (register segment and offset)](#operator-duoble-colon)
- [IMAGEREL (image relative offset)](#operator-imagerel)
- [LROFFSET (loader resolved offset)](#operator-lroffset)
- [OFFSET (segment relative offset)](#operator-offset)
- [SECTIONREL (section relative offset)](#operator-sectionrel)
- [SEG (get segment)](#operator-seg)

## Type

- [HIGH (high 8 bits of lowest 16 bits)](#operator-high)
- [HIGH32 (high 32 bits of 64 bits)](#operator-high32)
- [HIGH64 (high 64 bits of 128 bits)](#operator-high64)
- [HIGHBYTE (high 8 bits of lowest 16 bits)](#operator-highbyte)
- [HIGHWORD (high 16 bits of lowest 32 bits)](#operator-highword)
- [LENGTH (number of elements in array)](#operator-length)
- [LENGTHOF (number of elements in array)](#operator-lengthof)
- [LOW (low 8 bits)](#operator-low)
- [LOW32 (low 32 bits)](#operator-low32)
- [LOW64 (low 64 bits)](#operator-low64)
- [LOWBYTE (low 8 bits)](#operator-lowbyte)
- [LOWWORD (low 16 bits)](#operator-lowword)
- [OPATTR (get argument type info)](#operator-opattr)
- [PTR (pointer to or as type)](#operator-ptr)
- [SHORT (mark short label type)](#operator-short)
- [SIZE (size of type or variable)](#operator-size)
- [SIZEOF (size of type or variable)](#operator-sizeof)
- [THIS (current location)](#operator-this)
- [TYPE (get expression type)](#operator-type)
- [TYPEID (get expression id)](#operator-typeid)
- [TYPEOF (get expression type)](#operator-typeof)
- [.TYPE (get argument type info)](#operator-.type)

### See Also

[Directives Reference](directive.md)


### operator Multiply

    operator *

**_expression1_ * _expression2_**

Returns _expression1_ times _expression2_.


### operator Add

    operator +

**_expression1_ + _expression2_**
**_+expression_**

The first operator returns _expression1_ plus _expression2_.

The second operator reverses the sign of _expression_.


### operator Subtract

**_expression1_ - _expression2_**

Returns _expression1_ minus _expression2_.


### operator Field

**_expression_. _field_ [[. _field_]]...**

**[_register_]. _field_ [[. _field_]]...**

The first operator returns _expression_ plus the offset of _field_ within its structure or union.

The second operator returns value at the location pointed to by _register_ plus the offset of _field_ within its structure or union.

**Indirection**

In Asmc the unary indirection operator (.) may also accesses a value indirectly, through a pointer. The operand must be a pointer type. The result of the operation is the value addressed by the operand; that is, the value at the address to which its operand points. The type of the result is the type that the operand addresses.

The result of the indirection operator is _type_ if the operand is of type _pointer to type_. If the operand points to a function, the result is a function designator.


### operator Divide

**_expression1_ / _expression2_**

Returns _expression1_ divided by _expression2_.


### operator Index

**_expression1_ [_expression2_]**

Returns _expression1_ plus [_expression2_].


### operator Remainder

**_expression1_ MOD _expression2_**

Returns the integer value of the remainder (modulo) when dividing _expression1_ by _expression2_.


### operator Logical NOT

**!_character_**

Treats _character_ as a literal character rather than as an operator or symbol.


### operator Not Equal

**_expression1_ != _expression2_**

Is not equal to. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Logical OR

**_expression1_ || _expression2_**

Logical OR. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Logical AND

**_expression1_ && _expression2_**

Logical AND. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Less Than

**_expression1_ < _expression2_**

Is less than. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Less Or Equal

**_expression1_ <= _expression2_**

Is less than or equal to. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Equal

**_expression1_ == _expression2_**

Is equal to. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Greater Than

**_expression1_ > _expression2_**

Is greater than. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Greater Or Equal

**_expression1_ >= _expression2_**

Is greater than or equal to. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Bitwise AND

_expression1_ **&** _expression2_

Bitwise AND. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.

**&**_address_

_procedure_( **&**_address_ )

.for ( reg = **&**_address_ :: )

.return ( **&**_address_ )

.if ( a == **&**_address_ && b & **&**_address_ )


### operator Carry Test

**CARRY?**

Status of carry flag. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Overflow Test

**OVERFLOW?**

Status of overflow flag. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Parity Test

**PARITY?**

Status of parity flag. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Sign Test

**SIGN?**

Status of sign flag. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Zero Test

**ZERO?**

Status of zero flag. Used only within [.IF](directive.md#dot-if), [.WHILE](directive.md#dot-while), or [.REPEAT](directive.md#dot-repeat) blocks and evaluated at run time, not at assembly time.


### operator Bitwise ADD

**_expression1_ ADD _expression2_**

Returns the result of a bitwise ADD operation for _expression1_ plus _expression2_.

```assembly

; Manipulating float using binary operators

sqrt_approx macro f

      local x

        x = f sub 00010000000000000000000000000000r
        x = x shr 1
        x = x add 20000000000000000000000000000000r
        exitm<x>
        endm
```

### operator AND

**_expression1_ AND _expression2_**

Returns the result of a bitwise AND operation for _expression1_ and _expression2_.


### operator DIV

**_expression1_ DIV _expression2_**

Returns the 128 bit result of a bitwise DIV operation for _expression1_ / _expression2_.

```
; Manipulating float using binary operators

x = 1.0 shl 1
y = x div 2
```


### operator MUL

**_expression1_ MUL _expression2_**

Returns the 128 bit result of a bitwise MUL operation for _expression1_ * _expression2_.

```
; Manipulating float using binary operators

x = 1.0 shr 1
y = x mul 2
```


### operator NOT

**NOT _expression_**

Returns _expression_ with all bits reversed.


### operator OR

**_expression1_ OR _expression2_**

Returns the result of a bitwise OR operation for _expression1_ and _expression2_.


### operator SAR

**_expression_ SAR _count_**

Returns the result of shifting the bits of _expression_ right _count_ number of bits with the current sign bit replicated in the leftmost bit.


### operator SAL

**_expression_ SAL _count_**

Returns the result of shifting the bits of _expression_ left _count_ number of bits.


### operator SHL

**_expression_ SHL _count_**

Returns the result of shifting the bits of _expression_ left _count_ number of bits.


### operator SHR

**_expression_ SHR _count_**

Returns the result of shifting the bits of _expression_ right _count_ number of bits.


### operator SUB

**_expression1_ SUB _expression2_**

Returns the result of a bitwise SUB operation for _expression1_ minus _expression2_.

```
; Manipulating float using binary operators

sqrt_approx macro f

      local x

        x = f sub 00010000000000000000000000000000r
        x = x shr 1
        x = x add 20000000000000000000000000000000r
        exitm<x>
        endm
```


### operator XOR

**_expression1_ XOR _expression2_**

Returns the result of a bitwise XOR operation for _expression1_ and _expression2_.


### operator Logical Negation

**!_expression_**

Logical negation. Used only within .IF, .WHILE, or .REPEAT blocks and evaluated at run time, not at assembly time.


### operator Percent

**%_expression_**

Treats the value of _expression_ in a macro argument as text.


### operator Semicolons

**_;;text_**

Treats _text_ as a comment in a macro that appears only in the macro definition. The listing does not show text where the macro is expanded.


### operator Literal

**&lt;text&gt;**

Treats _text_ as a single literal element.


### operator Substitution

**&parameter&**

Replaces _parameter_ with its corresponding argument value.


### operator Single Quote

**'text'**

Treats 'text' as a string.


### operator Duoble Quote

**"text"**

Treats "text" as a string.


### operator Colon

**_segment_: _expression_**

Overrides the default segment of _expression_ with _segment_. The _segment_ can be a segment register, group name, segment name, or segment expression. The _expression_ must be a constant.


### operator Double Colon

**rdx::rax**

**edx::eax**

**label::**

**type::id proto ...**

**type::id proc ...**

The first operator is used in [INVOKE](directive.md#invoke) to create a 128-bit argument in 64-bit.

The second operator is used in [INVOKE](directive.md#invoke) to create a 64-bit argument in 32-bit.

The third operator is used as a global label within a PROC or as a PUBLIC label outside.

The next two operators is used to define a class member with a hidden (this) argument of _type_.


### operator Semicolon

**_;text_**

Treats _text_ as a comment.


### operator ADDR

See the [INVOKE](directive.md#invoke) directive.


### operator DUP

**_count_ DUP (_initialvalue_ [[, _initialvalue_]]...)**

Specifies _count_ number of declarations of _initialvalue_.


### operator MASK

**MASK {_recordfieldname_ | _record_}**

Returns a bit mask in which the bits in _recordfieldname_ or _record_ are set and all other bits are cleared.

_Note: **MASK** is disable by default in Asmc. Use [MASKOF](#operator-maskof) or [switch -Zne](command.md#disable-non-masm-extensions) to enable Masm compatible opeators._


### operator MASKOF

**MASKOF {_recordfieldname_ | _record_}**

Returns a bit mask in which the bits in _recordfieldname_ or _record_ are set and all other bits are cleared.


### operator WIDTH

**WIDTH {_recordfieldname_ | _record_}**

Returns the width in bits of the current _recordfieldname_ or _record_.

_Note: **WIDTH** is disable by default in Asmc. Use [switch -Zne](command.md#disable-non-masm-extensions) to enable Masm compatible opeators._


### operator EQ

**_expression1_ EQ _expression2_**

Returns true (-1) if _expression1_ equals _expression2_, or returns false (0) if it does not.

_* Non ML compatible usage_

    a = 1.0
    while a eq 1.0
        a = a - 1.0
        endm


### operator GE

**_expression1_ GE _expression2_**

Returns true (-1) if _expression1_ is greater than or equal to _expression2_, or returns false (0) if it is not.

_* Non ML compatible usage_

    a = 10.0
    while a ge 5.0
        a = a - 1.0
        endm


### operator GT

**_expression1_ GT _expression2_**

Returns true (-1) if _expression1_ is greater than _expression2_, or returns false (0) if it is not.

_* Non ML compatible usage_

    a = 10.0
    while a gt 5.0
        a = a - 1.0
        endm


### operator LE

**_expression1_ LE _expression2_**

Returns true (-1) if _expression1_ is less than or equal to _expression2_, or returns false (0) if it is not.

_* Non ML compatible usage_

    a = 1.0
    while a le 5.0
        a = a + 1.0
        endm


### operator LT

**_expression1_ LT _expression2_**

Returns true (-1) if _expression1_ is less than _expression2_, or returns false (0) if it is not.

_* Non ML compatible usage_

    a = -1.0
    while a lt 5.0
        a = a + 1.0
        endm


### operator NE

**_expression1_ NE _expression2_**

Returns true (-1) if _expression1_ does not equal _expression2_, or returns false (0) if it does.


### operator IMAGEREL

**IMAGEREL _expression_**

Returns the image relative offset of _expression_.

The resulting value is often referred to as an RVA or Relative Virtual Address.


### operator LROFFSET

**LROFFSET _expression_**

Returns the offset of _expression_. Same as OFFSET, but it generates a loader resolved offset, which allows Windows to relocate code segments.


### operator OFFSET

**OFFSET _expression_**

Returns the offset of _expression_.


### operator SECTIONREL

**SECTIONREL _expression_**

Returns the section relative offset of _expression_ relative to the section containing the target in the final executable.


### operator SEG

**SEG _expression_**

Returns the _segment_ of _expression_.


### operator HIGH

**HIGH _expression_**

Returns the high byte of _expression_.

_Note: **HIGH** is disable by default in Asmc. Use [HIGHBYTE](#operator-highbyte) or [switch -Zne](command.md#disable-non-masm-extensions) to enable Masm compatible opeators._


### Operator HIGH32

**HIGH32 _expression_**

Returns the high dword of _expression_.


### Operator HIGH64

**HIGH64 _expression_**

Returns the high qword of _expression_.


### Operator HIGHBYTE

**HIGHBYTE _expression_**

Returns the high byte of _expression_.


### Operator HIGHWORD

**HIGHWORD _expression_**

Returns the high word of _expression_.


### Operator LENGTH

See [SIZEOF](#operator-sizeof).


### Operator LENGTHOF

See [SIZEOF](#operator-sizeof).


### Operator LOW

**LOW _expression_**

Returns the low byte of _expression_.

_Note: **LOW** is disable by default in Asmc. Use [LOWBYTE](#operator-lowbyte) or [switch -Zne](command.md#disable-non-masm-extensions) to enable Masm compatible opeators._


### Operator LOW32

**LOW32 _expression_**

Returns the low dword of _expression_.


### Operator LOW64

**LOW64 _expression_**

Returns the low qword of _expression_.


### Operator LOWBYTE

**LOWBYTE _expression_**

Returns the low byte of _expression_.


### Operator LOWWORD

**LOWWORD _expression_**

Returns the low word of _expression_.


### Operator OPATTR

**OPATTR _expression_**

The OPATTR operator returns a one-word constant defining the mode and scope of expression. If _expression_ is not valid or is forward referenced, OPATTR returns a 0. If _expression_ is valid, a nonrelocatable word is returned. The .TYPE operator returns only the low byte (bits 0-7) of the OPATTR operator and is included for compatibility with previous versions of the assembler.

```
Bit       Set If
Position  expression

 0        References a code label
 1        Is a memory expression or has a relocatable data label
 2        Is an immediate expression
 3        Uses direct memory addressing
 4        Is a register expression
 5        References no undefined symbols and is without error
 6        Is an SS-relative memory expression
 7        References an external label
 8-12     Language type:

          Bits     Language

          0000     No language type
          0001     C
          0010     SYSCALL
          0011     STDCALL
          0100     Pascal
          0101     FORTRAN
          0110     Basic
          0111     FASTCALL
          1000     VECTORCALL
          1001     WATCALL

15        Is signed
```

Bit 13 and 14 are undefined and reserved for future expansion.


### Operator PTR

**_type_ PTR _expression_**

**[[_distance_]] PTR _type_**

The first operator forces the _expression_ to be treated as having the specified _type_.

The second operator specifies a pointer to _type_.


### Operator SHORT

**SHORT _label_**

Sets the type of _label_ to short. All jumps to _label_ must be short (within the range -128 to +127 bytes from the jump instruction to label).


### Operator SIZE

See [SIZEOF](#operator-sizeof).


### Operator SIZEOF

**LENGTHOF _variable_**
**SIZEOF _variable_**
**SIZEOF _type_**
**LENGTH _expression_**
**SIZE _expression_**

The LENGTHOF operator returns the number of data items allocated for variable. The SIZEOF operator returns the total number of bytes allocated for variable or the size of type in bytes. For variables, SIZEOF is equal to the value of LENGTHOF times the number of bytes in each element.

The LENGTH and SIZE operators are allowed for compatibility with previous versions of Masm using the switch [switch -Zne](command.md#disable-non-masm-extensions). When applied to a data label, the LENGTH operator returns the number of elements created by the DUP operator; otherwise it returns 1. When applied to a data label, the SIZE operator returns the number of bytes allocated by the first initializer at the variable label.


### Operator THIS

**THIS _type_**

Returns an operand of specified type whose offset and segment values are equal to the current location counter value.

_Note: **THIS** is disable by default in Asmc. Use [switch -Zne](https://github.com/nidud/asmc/blob/master/doc/command.md#disable-non-masm-extensions) to enable Masm compatible opeators._


### Operator TYPE

**TYPE _expression_**

Returns the type of _expression_.

_Note: **TYPE** is disable by default in Asmc. Use [switch -Zne](command.md#disable-non-masm-extensions) to enable Masm compatible opeators._


### operator TYPEID

**TYPEID**( [[ type, ]] _expression_ )

Returns a string equivalent of a type from _expression_.

### Example

```
.inline type :abs, :vararg {
    this.typeid(type_, _1)(_1, _2)
    }
```

| _input_ | _output_ |
| ------ |:------- |
| 1 | type_imm |
| 1.0 | type_flt |
| ax | type_word |
| rax | type_qword |
| zmm0 | type_zword |
| addr [rax] | type_ptr |
| addr i | type_ptrsdword |
| addr rc | type_ptrRECT |
| i | type_sdword |
| rc | type_RECT |


### Operator TYPEOF

**TYPEOF _expression_**

Returns the type of _expression_.


### Operator .TYPE

See [OPATTR](#operator-opattr).
