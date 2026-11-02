Asmc Macro Assembler Reference

## LTEXT

Defines a left-aligned text control. The control is a simple rectangle displaying the given text left-aligned in the rectangle. The text is formatted before it is displayed. Words that would extend past the end of a line are automatically wrapped to the beginning of the next line. Words that are longer than the width of the control are truncated.

The LTEXT statement, which can be used only in a [DIALOGEX](dialogex.md) statement, defines the text, identifier, dimensions, and attributes of the control.

syntax:

```
LTEXT text, id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_style_

Control styles. This value can be any combination of the BS\_RADIOBUTTON style and the following styles: SS\_LEFT, WS\_TABSTOP, and WS\_GROUP.

If you do not specify a style, the default style is SS\_LEFT | WS\_GROUP.

#### Example

This example defines a left-aligned text control that is labeled Filename:

```
LTEXT "Filename", 101, 10, 10, 100, 100
```

#### See Also

[Asmc Resource Compiler](readme.md)
