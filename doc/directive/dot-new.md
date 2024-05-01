Asmc Macro Assembler Reference

## .NEW

**.NEW** label [[ [count ] ]] [[:type]] [[, label [[ [count] ]] [[type]]]]...

**.NEW** label [[:class(...)]] [[, label [[class(...)]]]]...

Within a procedure definition (**PROC**), **.NEW** creates stack-based variables that exist for the duration of the procedure. The label may be a simple variable or an array containing count elements. If _type_ is a class the default constructor is invoked.

#### See Also

[Conditional Control Flow](conditional-control-flow.md)
