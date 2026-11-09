Asmc Macro Assembler Reference

## AUTOCHECKBOX

Defines an automatic check box control. The control is a small rectangle (check box) that has the specified text displayed next to it (typically, to the right). When the user chooses the control, the control highlights the rectangle and sends a message to its parent window.

The AUTOCHECKBOX statement can only be used in the body of a DIALOG or DIALOGEX statement.

syntax:

```
AUTOCHECKBOX text, id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_style_

Styles of the control. This value can be a combination of the button class style BS\_AUTOCHECKBOX and the WS\_TABSTOP and WS\_GROUP styles.

If you do not specify a style, the default style is BS\_AUTOCHECKBOX | WS\_TABSTOP.

#### Example

```
AUTOCHECKBOX "Italic", 3, 10, 10, 40, 10
```

#### See Also

[Asmc Resource Compiler](readme.md)
