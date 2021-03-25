Asmc Macro Assembler Reference

## .CLASS

**.CLASS** _name_ [[ _type_ ]] [[ : public _class_ ]]

Declares a structure type for a [COM interface](https://en.wikipedia.org/wiki/Component_Object_Model).

A class can have the following kinds of members

  - data members
  - member functions

The first entry is added by the assembler
```assembly
lpVtbl ptr nameVtbl ?
; additional data members
```
Member functions are added to a second struct: _name_**Vtbl**
```assembly
name proc    ; constructor - not added
Release proc ; first member function
```

#### See Also

[.ENDS](dot_ends.md) | [.COMDEF](dot_comdef.md) | [.NEW](dot_new.md)
