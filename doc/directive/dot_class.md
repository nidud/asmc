Asmc Macro Assembler Reference

## .CLASS

**.CLASS** _name_ [[ _type_ ]] [[ : public _class_ ]]

Declares a structure type for a [COM interface](https://en.wikipedia.org/wiki/Component_Object_Model).

A class can have the following kinds of members

  - data members
```assembly
lpVtbl ptr nameVtbl ?
...
```
  - member functions

#### See Also

[.ENDS](dot_ends.md) | [.COMDEF](dot_comdef.md) | [.NEW](dot_new.md)
