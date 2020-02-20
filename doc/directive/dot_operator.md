Asmc Macro Assembler Reference

## .OPERATOR

.OPERATOR [ _name_ | _OP_ ] [[ : _args_ ]] [[ { ... } ]]

Declares a method type for a Asmc class interface.

Arithmetic Operators

    Operator        Name  Description

    .operator +     radd  - Add
    .operator -     rsub  - Subtract
    .operator *     rmul  - Multiply
    .operator /     rdiv  - Divide
    .operator %     rmod  - Modulus
    .operator ++    rinc  - Increment
    .operator --    rdec  - Decrement

Bitwise Operators

    .operator &     rand  - Binary AND Operator
    .operator |     ror   - Binary OR Operator
    .operator ^     rxor  - Binary XOR Operator
    .operator ~     rnot  - Binary Ones Complement Operator
    .operator &~    randn - Binary AND NOT Operator
    .operator <<    rshl  - Binary Left Shift Operator
    .operator >>    rshr  - Binary Right Shift Operator

Assignment Operators

    .operator =     mequ  - Simple assignment operator
    .operator +=    madd  - Add AND assignment operator
    .operator -=    msub  - Subtract AND assignment operator
    .operator *=    mmul  - Multiply AND assignment operator
    .operator /=    mdiv  - Divide AND assignment operator
    .operator %=    mmod  - Modulus AND assignment operator
    .operator ~=    mnot  - Bitwise NOT assignment operator
    .operator <<=   mshl  - Left shift AND assignment operator
    .operator >>=   mshr  - Right shift AND assignment operator
    .operator &=    mand  - Bitwise AND assignment operator
    .operator &~=   mandn - Bitwise AND NOT assignment operator
    .operator ^=    mxor  - Bitwise exclusive OR and assignment operator
    .operator |=    mand  - Bitwise inclusive OR and assignment operator

The size of the three first parameters are added to the name.

    .operator = :qword, :dword { ; mequ84
        mov [this],_1
        retm<this>
        }

Inline functions are rendered as macros with fixed argument names. The name may hold a register, a memory location or immediate value depending on calling convention.

    class_mequ84 macro this, _1, _2
        mov [this],_1
        retm<this>
        endm

Immediate values must be defined as :ABS.

    .operator >> :abs { exitm<_mm_srli_epi64(xmm0, _1)> }

#### See Also

[.CLASS](dot_class.md) | [.ENDS](dot_ends.md)
