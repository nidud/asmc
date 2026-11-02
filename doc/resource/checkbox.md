Asmc Macro Assembler Reference

## CHECKBOX

Defines a check box control. The control is a small rectangle (check box) that has the specified text displayed next to it (typically, to the right). When the user selects the control, the control highlights the rectangle and sends a message to its parent window.

The CHECKBOX statement, which can only be used in a [DIALOGEX](dialogex.md) statement, defines the text, identifier, dimensions, and attributes of the control.

syntax:

```
CHECKBOX text, id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_text_

Text that is to be displayed to the right of the control.

_style_

Control styles. This value can be a combination of the button class style BS\_CHECKBOX and the WS\_TABSTOP and WS\_GROUP styles.

If you do not specify a style, the default style is BS\_CHECKBOX | WS\_TABSTOP.

#### Example

```
CHECKBOX "Italic", 3, 10, 10, 40, 10
```

#### See Also

[Asmc Resource Compiler](readme.md)
