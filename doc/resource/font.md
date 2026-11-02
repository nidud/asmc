Asmc Macro Assembler Reference

## FONT

Defines the font with which the system will draw text in the dialog box. The font must have been previously loaded; for example, by calling the LoadResource function.

syntax:

```
FONT pointsize, "typeface", weight, italic, charset
```

#### Parameters

_pointsize_

The size of the font, in points.

_typeface_

The name of the typeface. This parameter must be enclosed in quotes (").

_weight_

The weight of the font in the range 0 through 1000. For example, 400 is normal and 700 is bold. If this value is 0, the default weight is used. For a list of predefined values, see the FW\_\* values defined in WinGDI.inc.

_italic_

Indicates an italic font if set to TRUE.

_charset_

The character set. For a list of values, see the lfCharSet member of the LOGFONT structure.

#### Example

The following example demonstrates the use of the FONT statement:

```
FONT 12, "MS Shell Dlg"
```

#### See Also

[Asmc Resource Compiler](readme.md)
