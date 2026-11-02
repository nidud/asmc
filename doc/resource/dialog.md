Asmc Macro Assembler Reference

## DIALOG

Defines a dialog box. The statement defines the position and dimensions of the dialog box on the screen as well as the dialog box style.

syntax:

```
DIALOG x, y, width, height  [, optional-statements] {control-statement  . . . }
```

#### Note

DIALOG is an obsolete resource ID. New applications should use [DIALOGEX](dialogex.md).

#### Parameters

_optional-statements_

- [CAPTION](caption.md)
- [CHARACTERISTICS](characteristics.md)
- [CLASS](class.md)
- [EXSTYLE](exstyle.md)
- [FONT](font.md)
- [LANGUAGE](language.md)
- [MENU](menu-statement.md)
- [STYLE](style.md)
- [VERSION](version.md)

#### Example

The following demonstrates the usage of the DIALOG statement:

```
include windows.inc

.resource

 DIALOG 10, 10, 300, 110,
 STYLE WS_POPUP or WS_BORDER,
 CAPTION "Error!" {
    CTEXT "Select One:", 1, 10, 10, 280, 12,
    PUSHBUTTON "&Retry", 2, 75, 30, 60, 12,
    PUSHBUTTON "&Abort", 3, 75, 50, 60, 12,
    PUSHBUTTON "&Ignore", 4, 75, 80, 60, 12
    }
```

#### See Also

[Asmc Resource Compiler](readme.md) | [DIALOGEX](dialogex.md)
