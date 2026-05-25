Asmc Macro Assembler Reference

## @ComAlloc

**@ComAlloc(_Class_[[,_expression1_[[,_expression2_]]]])**

Macro function that allocates a CLASS object. Returns a pointer to the new object.

If _expression1_ is added and evaluates to a label or register, a _vtable_ is assumed. In that case, if _expression2_ is added and evaluates to a CONST value or register, additional size is assumed. Else, if _expression1_ evaluates to a CONST value, additional size is assumed. Note that the _vtable_ argument has to be a nonvolatile-register but the size argument not.

Data members of the new object are initialized to zero. If a _vtable_ is assumed, the first member of the new object is set to the _vtable_ value.

Undefined members of the _vtable_ are resolved by selecting the first (topmost) occurrence of the member function.

Example:
```
.class A            ; top level class
    foo proc        ; external A_foo
   .ends
.class B : public A ; derived class
    bar proc        ; external B_bar
   .ends
.class N : public B ; derived class
    N proc          ; constructor for N
    member1 proc    ; local N_member1
    member2 proc    ; external N_member2
   .ends
N::member1 proc     ; local N_member1
    ret
    endp
N::N proc           ; constructor for N
    @ComAlloc(N)    ; allocate N with NVtbl and size of N
    ret             ; return pointer to new N
    endp
```

The above example defines a class hierarchy with three classes: A, B, and N. The @ComAlloc macro is used in the constructor of class N to allocate an object of type N, which includes a vtable (NVtbl) that contains the addresses of the member functions A\_foo, B\_bar, N\_member1, and N\_member2.

#### See Also

[Macro Functions](macro-functions.md) | [Symbols Reference](readme.md)
