Asmc Macro Assembler Reference

## operator TYPEID

**TYPEID**( [[ type, ]] _expression_ )


Returns a string equivalent of a type from _expression_.

### Example

```assembly
.inline type :abs, :vararg {
    this.typeid(type, _1)(_1, _2)
    }
```

| _input_ | _output_ |
| ------ |:------- |
| 0x10000000 | typeIMM32 |
| 0x100000000 | typeIMM64 |
| 0x10000000000000000 | typeIMM128 |
| 1.0 | typeIMMFLT |
| ax | typeREG16 |
| rax | typeREG64 |
| zmm0 | typeREG512 |
| addr [rax] | typePVOID |
| addr i | typePSDWORD |
| addr rc | typePRECT |
| i | typeSDWORD |
| rc | typeRECT |

#### See Also

[Operators Reference](readme.md)