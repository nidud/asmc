Asmc Macro Assembler Reference

## PROC

_label_ PROC [[_distance_]] [[_langtype_]] [[PUBLIC|PRIVATE|EXPORT]]
[[_prologuearg_]] [[USES _reglist_]] [[, _parameter_ [[:_tag_]] ...]]
[[FRAME [[:ehandler-address]] ]]
_statements_
_label_ [ENDP](endp.md)

Marks start and end of a procedure block called _label_. The statements in the block can be called with the CALL instruction or [INVOKE](invoke.md) directive.

#### See Also

[Procedures](procedures.md) | [Directives Reference](readme.md)
