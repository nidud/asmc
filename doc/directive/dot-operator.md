Asmc Macro Assembler Reference

## .OPERATOR

.OPERATOR [ &lt;_type_&gt; ] [ _name_ | _OP_ ] [[ : _args_ ]] { ... }

Declares a inline method type for a Asmc [class interface](dot-class.md).

Arithmetic Operators

```
    Operator        Name  Description

    .operator +     add  - Add
    .operator -     sub  - Subtract
    .operator *     mul  - Multiply
    .operator /     div  - Divide
    .operator %     mod  - Modulus
    .operator ++    inc  - Increment
    .operator --    dec  - Decrement
```

Bitwise Operators

```
    .operator &     and  - Binary AND Operator
    .operator |     or   - Binary OR Operator
    .operator ^     xor  - Binary XOR Operator
    .operator ~     not  - Binary Ones Complement Operator
    .operator &~    andn - Binary AND NOT Operator
    .operator &lt;&lt;    shl  - Binary Left Shift Operator
    .operator &gt;&gt;    shr  - Binary Right Shift Operator
```

Assignment Operators

```
    .operator =     equ  - Simple assignment operator
```

Parameters are added to the name.

```
    .operator = :qword {
        mov [this],_1
        }
```

Operator functions are rendered as macros with fixed argument names. The name may hold a register, a memory location or immediate value depending on calling convention.

```
    class_equ_qword macro this, _1, _2
        mov [this],_1
        exitm&lt;&gt;
        endm
```

Arithmetic Operators +, -, *, and / are evaluated as expressions.

```
    a = b + c * d + e
    a = add(e, add(b, mul(c, d)))
```

Immediate values must be defined as :ABS.

```
    .operator >> :abs { _mm_srli_epi64(xmm0, _1) }
```

#### See Also

[Conditional Control Flow](conditional-control-flow.md)
