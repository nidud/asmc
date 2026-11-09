Asmc Macro Assembler Reference

## AUTORADIOBUTTON

Defines an automatic radio button control. This control automatically performs mutual exclusion with the other AUTORADIOBUTTON controls in the same group. When the button is chosen, the application is notified with BN\_CLICKED.

syntax:

```
AUTORADIOBUTTON text, id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_text_

Text that will appear next to the radio button.

_style_

Styles for the automatic radio button, which can be a combination of BUTTON-class styles and the following styles: WS\_TABSTOP, WS\_DISABLED, and WS\_GROUP.

If you do not specify a style, the default style is BS\_AUTORADIOBUTTON | WS\_TABSTOP.

#### Example

The following example demonstrates the use of the AUTORADIOBUTTON statement:

```
AUTORADIOBUTTON "Italic", 100, 10, 10, 40, 10
```

#### See Also

[Asmc Resource Compiler](readme.md)
