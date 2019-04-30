Asmc Macro Assembler Reference

### .NEW

**.NEW** label [[ [count ] ]] [[:type]] [[, label [[ [count] ]] [[type]]]]...

**.NEW** label [[:class(...)]] [[, label [[class(...)]]]]...

Within a procedure definition (**PROC**), **.NEW** creates stack-based variables that
exist for the duration of the procedure. The label may be a simple variable or an array
containing count elements. If <type> is a class the default constructor is invoked.

#### See Also

[Directives Reference](readme.md) | [.CLASS](dot_class.md)
