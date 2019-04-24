Asmc Macro Assembler Reference

## .ASSERT

**.ASSERT**[D|W|B] <assert_expression>
**.ASSERT**:[<handler> | ON | OFF | PUSH | POP | PUSHF | POPF | CODE | ENDS]


#### Options

- **ON/OFF**
Main switch.

- **PUSH/POP**
Save and restore the ASMC flag. Stack level is 128.

- **PUSHF/POPF**
Toggles using PUSHF[D|Q] before calling handler.

- **CODE/ENDS**
Assemble code section if ASSERT is ON.

- **Handler**
The assert macro calls this routine if _expression_ is not true. The default handler name is _assert_exit_.

#### See Also

[Directives Reference](readme.md) | [.IF](dot_if.md) | [Return code](return.md)
