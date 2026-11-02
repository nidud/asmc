Asmc Macro Assembler Reference

## RADIOBUTTON

Defines a radio-button control. The control is a small circle that has the given text displayed next to it, typically to its right. The control highlights the circle and sends a message to its parent window when the user selects the button. The control removes the highlight and sends a message when the button is next selected.

syntax:

```
RADIOBUTTON text, id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_style_

Styles for the radio button, which can be a combination of BUTTON-class styles and the following styles: WS\_TABSTOP, WS\_DISABLED, and WS\_GROUP.

If you do not specify a style, the default style is BS\_RADIOBUTTON | WS\_TABSTOP.

#### Example

The following example demonstrates the use of the RADIOBUTTON statement:

```
RADIOBUTTON "Italic", 100, 10, 10, 40, 10
```

#### See Also

[Asmc Resource Compiler](readme.md)
