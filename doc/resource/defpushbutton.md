Asmc Macro Assembler Reference

## DEFPUSHBUTTON

Defines a default push-button control. The control is a small rectangle with a bold outline that represents the default response for the user. The given text is displayed inside the button. The control highlights the button in the usual way when the user clicks the mouse in it and sends a message to its parent window.

syntax:

```
DEFPUSHBUTTON text, id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_text_

Text that is to be centered in the rectangular area of the control.

_style_

Control styles. This value can be a combination of the following styles: BS\_DEFPUSHBUTTON, WS\_TABSTOP, WS\_GROUP, and WS\_DISABLED.

If you do not specify a style, the default style is BS\_DEFPUSHBUTTON | WS\_TABSTOP.

#### Example

```
DEFPUSHBUTTON "Cancel", 101, 10, 10, 24, 50
```

#### See Also

[Asmc Resource Compiler](readme.md)
