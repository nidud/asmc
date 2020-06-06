Asmc Macro Assembler Reference

## operator TYPEID

**TYPEID**( [[ type, ]] _expression_ )


Returns a string equivalent of a type from _expression_.

### Example

    ```assembly
    .operator type :abs, :vararg {
        this.typeid(type, _1)(_1, _2)
        }

| _input_ | _output |
| ------ |:------- |
| 0x10000000 | type?i32 |
| 0x100000000 | type?i64 |
| 0x10000000000000000 | type?i128 |
| 1.0 | type?flt |
| ax | type?r16 |
| rax | type?r64 |
| zmm0 | type?r512 |
| addr [rax] | type?pvoid |
| addr i | type?psdword |
| addr rc | type?pRECT |
| i | type?sdword |
| rc | type?RECT |

#### See Also

[Operators Reference](readme.md)