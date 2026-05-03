Asmc Macro Assembler Reference

## .NEW

**.NEW** label [[ [count ] ]] [[:type]] [[, label [[ [count] ]] [[type]]]]...

**.NEW** label [[:class(...)]] [[, label [[class(...)]]]]...

Within a procedure definition (**PROC**), **.NEW** creates stack-based variables that exist for the duration of the procedure. The label may be a simple variable or an array containing count elements. If _type_ is a class the default constructor is invoked.

Unlike **LOCAL**, **.NEW** variables automatically inherit the previous defined type. This allows for more concise definitions when multiple variables of the same type are needed.

### Parameters
- **label**: The name of the variable or array to create.
- **count**: (Optional) The number of elements in the array. If omitted, a single variable is created.
- **type**: (Optional) The data type of the variable or array elements. If omitted, the type of the previous variable is used.
- **,**: (Optional) Used to separate multiple variable or array definitions.

### Example
```
.new rc:RECT, rl, rr
	; rc, rl, and rr are all of type RECT
```
#### See Also

[Conditional Control Flow](conditional-control-flow.md)
