Asmc Macro Assembler Reference

## PUSHBOX

Defines a push-box control, which is identical to a [PUSHBUTTON](pushbutton.md), except that it does not display a button face or frame; only the text appears.

syntax:

```
PUSHBOX text, id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_style_

Styles for the pushbox, which can be a combination of the BS\_PUSHBOX style and the following styles: WS\_TABSTOP, WS\_DISABLED, and WS\_GROUP.

If you do not specify a style, the default style is BS\_PUSHBOX | WS\_TABSTOP.

#### See Also

[Asmc Resource Compiler](readme.md)
