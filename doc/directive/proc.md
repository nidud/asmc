Asmc Macro Assembler Reference

### PROC

    label PROC [[distance]] [[langtype]] [[visibility]] [[]]
        [[USES reglist]] [[, parameter [[:tag]]]]...
        statements
    label ENDP

Marks start and end of a procedure block called label. The statements in the block can be called with the CALL instruction or INVOKE directive.

#### See Also

[Directives Reference](readme.md)