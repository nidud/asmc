Asmc Macro Assembler Reference

## .FOR

**.FOR[S]** [_initialization_] : [_condition_] : [_increment/decrements_]<br>
   _statements_<br>
   **.ENDF**

Generates code that executes the block of _statements_ while _condition_ remains true.

.FORS is the signed version.

Assignment of values for _initialization_ and _increment/decrements_:

    a++         - inc a
    a--         - dec a
    a <<= i     - shl a,imm/cl
    a >>= i     - shr a,imm/cl
    a |= b      - or  a,b
    a &= b      - and a,b
    a += b      - add a,b
    a -= b      - sub a,b
    a ~= b      - [mov a,b] not a
    a ^= b      - xor a,b
    a = &b      - lea a,b
    a = ~b      - [mov a,b] not a

#### See Also

[Directives Reference](readme.md) | [Flag conditions](flags.md) | [Signed compare](signed.md) | [.ENDF](dot_endf.md)
