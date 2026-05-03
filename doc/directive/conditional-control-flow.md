Asmc Macro Assembler Reference

# Conditional Control Flow

Asmc adds _flags_ and _size_ extensions to directives.

#### Flag Extension

- **[N]A** _above_
- **[N]B** _below_
- **[N]C** _carry_
- **[N]G** _greater (signed)_
- **[N]L** _less (signed)_
- **[N]O** _overflow_
- **[N]P** _parity_
- **[N]S** _signed_
- **[N]Z** _zero_

#### Size Extension

- **B** [BYTE](byte.md)
- **W** [WORD](word.md)
- **D** [DWORD](dword.md)

The format is **DIRECIVE**[[_flags_]][[_size_]] with valid combination **DIRECIVE**[[**S**]][[_size_]], so the only valid flag with _expression_ is **S** (signed). Note that the _size_ extension only effects the return code from a function call within an _expression_. As the default return in 64-bit is RAX this should be sized up according to the actual returned value. The _expression_ ( foo() == -1 ) may otherwise fail if the returned value is **int** (0x00000000FFFFFFFF).

- [.ASSERT (_extension: size_)](dot-assert.md)
- [.BREAK](dot-break.md)
- [.CASE](dot-case.md)
- [.CLASS](dot-class.md)
- [.CONTINUE](dot-continue.md)
- [.COMDEF](dot-comdef.md)
- [.DEFAULT](dot-default.md)
- [.ELSE](dot-else.md)
- [.ELSEIF (_extension: S, D, SD_)](dot-if.md)
- [.ENDC](dot-endc.md)
- [.ENDF](dot-endf.md)
- [.ENDIF](dot-endif.md)
- [.ENDN](dot-endn.md)
- [.ENDS](dot-ends.md)
- [.ENDSW](dot-endsw.md)
- [.ENDW](dot-endw.md)
- [.ENUM](dot-enum.md)
- [.ENUMT](dot-enumt.md)
- [.FOR (_extension: S_)](dot-for.md)
- [.GOTOSW](dot-gotosw.md)
- [.IF (_extension: flag and size_)](dot-if.md)
- [.INLINE](dot-inline.md)
- [.NAMESPACE](dot-namespace.md)
- [.NEW](dot-new.md)
- [.OPERATOR](dot-operator.md)
- [.REPEAT](dot-repeat.md)
- [.RETURN](dot-return.md)
- [.STATIC](dot-static.md)
- [.SWITCH](dot-switch.md)
- [.TEMPLATE](dot-template.md)
- [.UNTIL (_extension: flag and size_)](dot-until.md)
- [.UNTILCXZ](dot-untilcxz.md)
- [.WHILE (_extension: flag and size_)](dot-while.md)

#### See Also

[Directives Reference](readme.md)
