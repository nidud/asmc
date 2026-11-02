Asmc Macro Assembler Reference

## CTEXT

Defines a centered-text control. The control is a simple rectangle displaying the given text centered in the rectangle. The text is formatted before it is displayed. Words that would extend past the end of a line are automatically wrapped to the beginning of the next line. Words that are longer than the width of the control are truncated.

The [LTEXT](ltext.md) statement, which can be used only in a rep statement, defines the text, identifier, dimensions, and attributes of the control.

syntax:

```
CTEXT text, id, x, y, width, height [, STYLE style [, EXSTYLE extended-style]]
```

#### Parameters

_text_

Text that is to be centered in the rectangular area of the control.

_style_

Control styles. This value can be any combination of the following styles: SS\_CENTER, WS\_TABSTOP, and WS\_GROUP.

If you do not specify a style, the default style is SS\_CENTER | WS\_GROUP.

#### Example

```
CTEXT "Filename", 101, 10, 10, 100, 100
```

#### See Also

[Asmc Resource Compiler](readme.md)
