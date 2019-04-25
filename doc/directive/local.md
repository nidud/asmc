Asmc Macro Assembler Reference

### LOCAL

**LOCAL** localname [[, localname]]...

**LOCAL** label [[ [count ] ]] [[:type]] [[, label [[ [count] ]] [[type]]]]...

In the first directive, within a macro, **LOCAL** defines labels that are unique to each instance of the macro.

In the second directive, within a procedure definition (**PROC**), **LOCAL** creates stack-based variables that exist for the duration of the procedure. The label may be a simple variable or an array containing count elements.

#### See Also

[Directives Reference](readme.md)