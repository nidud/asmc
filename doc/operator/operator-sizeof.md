Asmc Macro Assembler Reference

## operator SIZEOF

- **LENGTHOF _variable_**
- **SIZEOF _variable_**
- **SIZEOF _type_**
- **LENGTH _expression_**
- **SIZE _expression_**

The LENGTHOF operator returns the number of data items allocated for variable. The SIZEOF operator returns the total number of bytes allocated for variable or the size of type in bytes. For variables, SIZEOF is equal to the value of LENGTHOF times the number of bytes in each element.

The LENGTH and SIZE operators are allowed for compatibility with previous versions of Masm. When applied to a data label, the LENGTH operator returns the number of elements created by the DUP operator; otherwise it returns 1. When applied to a data label, the SIZE operator returns the number of bytes allocated by the first initializer at the variable label.

#### See Also

[Operators Reference](readme.md) | [Type](type.md) | [Masm Compatible Opeators](../command/option-zne.md)
