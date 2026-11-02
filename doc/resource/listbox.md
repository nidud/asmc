Asmc Macro Assembler Reference

## LISTBOX

Defines commonly used controls for a dialog box or window. The control is a rectangle containing a list of strings (such as filenames) from which the user can select.

The LISTBOX statement, which can only be used in a [DIALOGEX](dialogex.md) or WINDOW statement, defines the identifier, dimensions, and attributes of a control window.

syntax:

```
LISTBOX id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_style_

Control styles. This value can be a combination of the list-box class styles and any of the following styles: WS\_BORDER and WS\_VSCROLL.

If you do not specify a style, the default style is LBS\_NOTIFY | WS\_BORDER.

#### Example

```
LISTBOX 101, 10, 10, 100, 100
```

#### See Also

[Asmc Resource Compiler](readme.md)
