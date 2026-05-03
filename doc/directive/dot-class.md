Asmc Macro Assembler Reference

## .CLASS

**.CLASS** _name_ [[ _type_ ]] [[ : public _class_ ]]

Declares a structure type for a COM interface.

A class can have the following kinds of members

- data members
- member functions

The first entry is added by the assembler

- lpVtbl ptr _name_**Vtbl** ?
- _additional data members_

Member functions are added to a second struct: _name_**Vtbl**

- _name_ proc (_constructor - not added_)
- Release proc (_first member function_)


#### See Also

[Conditional Control Flow](conditional-control-flow.md)

