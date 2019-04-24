Asmc Macro Assembler Reference

### .NEW

    .NEW label [[ [count ] ]] [[:type]] [[, label [[ [count] ]] [[type]]]]...
    .NEW label [[:class(...)]] [[, label [[class(...)]]]]...

Within a procedure definition (**PROC**), **.NEW** creates stack-based variables that
exist for the duration of the procedure. The label may be a simple variable or an array
containing count elements. If <type> is a class the default constructor is invoked.

    .classdef C :byte
        atom    byte ?
        get     proc
        set     proc :byte
        .ends

    .new a:C(0)
    * C::C(&a, 0)
    .new p:ptr C(1)
    * mov p,C::C(NULL, 1)

#### See Also

[Directives Reference](readme.md) | [.CLASSDEF](dot_classdef.md)
