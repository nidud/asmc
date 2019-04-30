Asmc Macro Assembler Reference

## Disable non Masm extensions.

Command-line options **/Zne**

.pragma **asmc(push, 0)**

### Renamed keywords

Asmc allows in addition to **C** the following keywords to be used as identifiers. In Masm compatible mode they will be renamed.

    Masm      Asmc

    name      .name
    page      .page
    subtitle  .subtitle
    subttl    .subttl
    title     .title
    low       .low
    high      .high
    size      .size
    length    .length
    this      .this
    mask      .mask
    width     .width
    type      typeof

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
- [.gotosw[1|2|3]](../directive/dot_gotosw.md)
- [.default](../directive/dot_default.md)
- [.endsw](../directive/dot_endsw.md)

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
