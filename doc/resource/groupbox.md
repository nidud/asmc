Asmc Macro Assembler Reference

## GROUPBOX

Defines a group box control. The control is a rectangle that groups other controls together. The controls are grouped by drawing a border around them and displaying the given text in the upper-left corner.

The GROUPBOX statement, which you can use only in a [DIALOGEX](dialogex.md) statement, defines the text, identifier, dimensions, and attributes of a control window.

syntax:

```
GROUPBOX text, id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_style_

Control styles. This value can be a combination of the button class style BS\_GROUPBOX and the WS\_TABSTOP and WS\_DISABLED styles.

If you do not specify a style, the default style is BS\_GROUPBOX.

#### Remarks

When the style contains WS\_TABSTOP or the text specifies an accelerator, tabbing or pressing the accelerator key moves the focus to the first control within the group.

#### Example

```
GROUPBOX "Options", 101, 10, 10, 100, 100
```

#### See Also

[Asmc Resource Compiler](readme.md)
