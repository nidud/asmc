Asmc Macro Assembler Reference

## operator OPATTR

**OPATTR _expression_**

The OPATTR operator returns a one-word constant defining the mode and scope of expression. If _expression_ is not valid or is forward referenced, OPATTR returns a 0. If _expression_ is valid, a nonrelocatable word is returned. The .TYPE operator returns only the low byte (bits 0-7) of the OPATTR operator and is included for compatibility with previous versions of the assembler.

```
Bit       Set If
Position  expression

 0        References a code label
 1        Is a memory expression or has a relocatable data label
 2        Is an immediate expression
 3        Uses direct memory addressing
 4        Is a register expression
 5        References no undefined symbols and is without error
 6        Is an SS-relative memory expression
 7        References an external label
 8-12     Language type:

          Bits     Language

          0000     No language type
          0001     C
          0010     SYSCALL
          0011     STDCALL
          0100     Pascal
          0101     FORTRAN
          0110     Basic
          0111     FASTCALL
          1000     VECTORCALL
          1001     WATCALL

15        Is signed
```

Bit 13 and 14 are undefined and reserved for future expansion.

#### See Also

[Operators Reference](readme.md)
