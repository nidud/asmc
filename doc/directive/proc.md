Asmc Macro Assembler Reference

## PROC

Marks start and end of a procedure block called _label_. The statements in the block can be called with the CALL instruction or [INVOKE](invoke.md) directive.

### Syntax

_label_ PROC [_distance_] [_language-type_] [PUBLIC \| PRIVATE \| EXPORT] [&lt;_prologuearg_&gt;] [USES _reglist_] [, _parameter_ [:_tag_] ...] [FRAME [:ehandler-address]]

_statements_

_label_ [ENDP](endp.md)

### Remarks

[FRAME [:_ehandler-address_]] is only valid in 64-bit, and causes ASMC to generate a function table entry in .pdata and unwind information in .xdata for a function's structured exception handling unwind behavior. When the FRAME attribute is used, it must be followed by an [.ENDPROLOG](dot-endprolog.md) directive.

The [_distance_] and [_language-type_] arguments are valid only in 32-bit.

The standard prologue and epilogue code recognizes three operands passed in the &lt;_prologuearg_&gt; list, USESDS, LOADDS and FORCEFRAME. These operands modify the prologue code.

Specifying USESDS saves DS if [@DataSize](../symbol/at-datasize.md) and SI is used. In TINY, SMALL, and MEDIUM [memory model](dot-model.md) ES is set to DS. Specifying LOADDS saves and initializes DS. Specifying FORCEFRAME as an argument generates a stack frame even if no arguments are sent to the procedure and no local variables are declared. If your procedure has any parameters or locals, you do not need to specify FORCEFRAME.

#### See Also

[Directives Reference](readme.md) | [Procedures](procedures.md)
