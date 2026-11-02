Asmc Macro Assembler Reference

## RTEXT

Defines a right-aligned text control. The control is a simple rectangle displaying the given text right-aligned in the rectangle. The text is formatted before it is displayed. Words that would extend past the end of a line are automatically wrapped to the beginning of the next line. Words that are longer than the width of the control are truncated.

The RTEXT statement, which can be used only in a [DIALOGEX](dialogex.md) statement, defines the text, identifier, dimensions, and attributes of the control.

syntax:

```
RTEXT text, id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_style_

Styles for the text control, which can be any combination of the following: WS\_TABSTOP and WS\_GROUP.

If you do not specify a style, the default style is SS\_RIGHT | WS\_GROUP.

#### Example

The following example demonstrates the use of the RTEXT statement:

```
RTEXT "Number of Messages", 4, 30, 50, 100, 10
```

#### See Also

[Asmc Resource Compiler](readme.md)
