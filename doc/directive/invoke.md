Asmc Macro Assembler Reference

## INVOKE

**INVOKE** expression [[, arguments]]

Calls the procedure at the address given by expression, passing the arguments on the stack or in registers according to the standard calling conventions of the language type. Each argument passed to the procedure may be an expression, a register pair, or an address expression (an expression preceded by ADDR).

The Asmc specific convention is **_expression_**( _arguments_ ).

String arguments can be passed as C-style quoted strings, including (L"Unicode strings").

An immediate vector expression may be passed as an argument to a procedure parameter that is passed in a vector register. The number of values assigned must match the size of the vector register being used. For example:
```
bar proto :real4 {}
baz proto :real8, :real8 {}

foo proc uses xmm6 xmm7 x:real8
    bar( { 1.0, 2.0, 3.0, 4.0 } )
    baz( { 1.0, 2.0 }, { 3.0, 4.0 } )
    ret
    endp
```

#### See Also

[Procedures](procedures.md) | [Inline functions](inline-functions.md) | [Directives Reference](readme.md)
