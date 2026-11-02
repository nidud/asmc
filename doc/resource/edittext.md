Asmc Macro Assembler Reference

## EDITTEXT

Defines an edit control belonging to the EDIT class. It creates a rectangular region in which the user can type and edit text. The control displays a cursor when the user clicks the mouse in it. The user can then use the keyboard to enter text or edit the existing text. Editing keys include the BACKSPACE and DELETE keys. The user can also use the mouse to select characters to be deleted or to select the place to insert new characters.

syntax:

```
EDITTEXT id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_style_

Control styles. This value can be a combination of the edit class styles and the following styles: WS\_TABSTOP, WS\_GROUP, WS\_VSCROLL, WS\_HSCROLL, and WS\_DISABLED.

If you do not specify a style, the default style is ES\_LEFT | WS\_BORDER | WS\_TABSTOP.

#### Example

```
EDITTEXT  3, 10, 10, 100, 10
```

#### See Also

[Asmc Resource Compiler](readme.md)
