Asmc Macro Assembler Reference

## COMBOBOX

Defines a combination box control (a combo box). A combo box consists of either a static text box or an edit box combined with a list box. The list box can be displayed at all times or pulled down by the user. If the combo box contains a static text box, the text box always displays the selection (if any) in the list box portion of the combo box. If it uses an edit box, the user can type in the desired selection; the list box highlights the first item (if any) that matches what the user has entered in the edit box. The user can then select the item highlighted in the list box to complete the choice. In addition, the combo box can be owner-drawn and of fixed or variable height.

syntax:

```
COMBOBOX id, x, y, width, height [, STYLE style [, extended-style]]
```

#### Parameters

_style_

Control styles. This value can be a combination of the COMBOBOX class styles and any of the following styles: WS\_TABSTOP, WS\_GROUP, WS\_VSCROLL, and WS\_DISABLED.

If you do not specify a style, the default style is CBS\_SIMPLE | WS\_TABSTOP.

The height parameter applies to the height of a combo box with a drop-down list fully expanded.

#### Example

```
COMBOBOX 777, 10, 10, 50, 54, STYLE CBS_SIMPLE or WS_VSCROLL or WS_TABSTOP
```

#### See Also

[Asmc Resource Compiler](readme.md)
