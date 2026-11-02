Asmc Macro Assembler Reference

## PUSHBUTTON

Defines a push-button control. The control is a round-cornered rectangle containing the given text. The text is centered in the control. The control sends a message to its parent whenever the user chooses the control.

syntax:

```
PUSHBUTTON text, id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_style_

Styles for the pushbutton, which can be a combination of the BS\_PUSHBUTTON style and the following styles: WS\_TABSTOP, WS\_DISABLED, and WS\_GROUP.

If you do not specify a style, the default style is BS\_PUSHBUTTON | WS\_TABSTOP.

#### Example

The following example demonstrates the use of the PUSHBUTTON statement:

```
PUSHBUTTON "ON", 7, 10, 10, 20, 10
```

#### See Also

[Asmc Resource Compiler](readme.md)
