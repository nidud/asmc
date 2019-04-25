Asmc Macro Assembler Reference

## Flag conditions

The options listed may be used as directive **.IF**_xx_, **.WHILE**_xx_, and **.UNTIL**_xx_.

_xx_

- **A**
_NBE_
Above | _Not Below or Equal_

- **B**
_C/NAE_
Below | _Carry_ | _Not Above or Equal_

- **C**
_C/NAE_
Below | _Carry_ | _Not Above or Equal_

- **G**
_NLE_
Greater | _Not Less or Equal_ (signed)

- **L**
_NGE_
Less | _Not Greater or Equal_ (signed)

- **O**
Overflow (signed)

- **P**
_PE_
Parity | _Parity Even_

- **S**
Signed (signed)

- **Z**
_E_
Zero | _Equal_

- **NA**
_BE_
Not Above | _Not Below or Equal_

- **NB**
_NC/AE_
Not Below | _Not Carry_ | _Above or Equal_

- **NC**
_NC/AE_
Not Below | _Not Carry_ | _Above or Equal_

- **NG**
_LE_
Not Greater | _Less or Equal_ (signed)

- **NL**
_GE_
Not Less | _Greater or Equal_ (signed)

- **NO**
Not Overflow (signed)

- **NP**
_PO_
No Parity | _Parity Odd_

- **NS**
Not Signed (signed)

- **NZ**
_NE_

Not Zero | _Not Equal_

Note that if used with _condition_ the directive may have a different meaning.

#### See Also

[Directives Reference](readme.md) | [Signed compare](signed.md) | [Return code](return.md)
