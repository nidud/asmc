Asmc Macro Assembler Reference

## .CASE

**.CASE [[ &lt;_name_&gt; ]] _expression_**

.CASE begins a case statement that compares an ordinal expression's value against one or more selectors. Each selector may be a constant, a subrange, or a comma-separated list of constants and subranges. The selector field is separated from the action field by a colon or a newline. In a control-table switch (a [.SWITCH](dot-switch.md) statement without arguments), _expression_ is evaluated at runtime. 

_name_ is an optional name for the case label.

#### See Also

[Conditional Control Flow](conditional-control-flow.md)
