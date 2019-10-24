Asmc Macro Assembler Reference

## Disable non Masm extensions.

Command-line options **/Zne**

[.pragma](../directive/dot_pragma.md) **asmc(push, 0)**

### Renamed keywords

[Disable non Masm keywords](Znk.md)

### Keywords removed

#### Conditional Control Flow

- [.assert](../directive/dot_assert.md)
- [.for](../directive/dot_for.md)
- [.endf](../directive/dot_endf.md)
- [.class](../directive/dot_class.md)
- [.comdef](../directive/dot_comdef.md)
- [.ends](../directive/dot_ends.md)
- [.new](../directive/dot_new.md)
- [.switch](../directive/dot_switch.md)
- [.case](../directive/dot_case.md)
- [.endc](../directive/dot_endc.md)
- [.gotosw](../directive/dot_gotosw.md)
- [.default](../directive/dot_default.md)
- [.endsw](../directive/dot_endsw.md)
- [.enum](../directive/dot_enum.md)
- [.return](../directive/dot_return.md)

Flag conditions

- [.if[xx]](../directive/flags.md)
- [.while[xx]](../directive/flags.md)
- [.until[xx]](../directive/flags.md)

Signed compare

- [.ifs](../directive/signed.md)
- [.whiles](../directive/signed.md)
- [.untils](../directive/signed.md)

Return code

- [.if[s][b|w|d]](../directive/return.md)
- [.while[s][b|w|d]](../directive/return.md)
- [.until[s][b|w|d]](../directive/return.md)

#### Conditional Assembly

- [defined](../directive/defined.md)
- [undef](../directive/undef.md)

### Asmc extensions not disabled.

- [.pragma](../directive/dot_pragma.md)

#### See Also

[Asmc Command-Line Reference](readme.md) | [Disable non Masm keywords](Znk.md)
