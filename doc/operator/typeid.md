Asmc Macro Assembler Reference

## operator TYPEID

**TYPEID**( [[ type, ]] _expression_ )


Returns a string equivalent of a type from _expression_.

### Example

```assembly
.inline type :abs, :vararg {
    this.typeid(type_, _1)(_1, _2)
    }
```

| _input_ | _output_ |
| ------ |:------- |
| 1 | type_imm |
| 1.0 | type_flt |
| ax | type_word |
| rax | type_qword |
| zmm0 | type_zword |
| addr [rax] | type_ptr |
| addr i | type_ptrsdword |
| addr rc | type_ptrRECT |
| i | type_sdword |
| rc | type_RECT |

#### See Also

[Operators Reference](readme.md)
