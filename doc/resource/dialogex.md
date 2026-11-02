Asmc Macro Assembler Reference

## DIALOGEX

Defines a dialog box. The statement defines the position and dimensions of the dialog box on the screen as well as the dialog box style. It also defines the following:

- Help IDs on the dialog itself as well as on controls within the dialog box.
- Use of the EXSTYLE statement for the dialog box itself as well as on controls within the dialog box.
- Font weight and italic settings for the font to be used in the dialog box.
- Control-specific data for controls within the dialog box.
- Use of the BEDIT, IEDIT, and HEDIT predefined system class names.

syntax:

```
DIALOGEX x, y, width, height [, HELP helpID] [, optional-statements]  {control-statements}
```

#### Parameters

_x_

Location on the screen of the left side of the dialog box, in dialog units.

_y_

Location on the screen of the top of the dialog box, in dialog units.

_width_

Width of the dialog box, in dialog units.

_height_

Height of the dialog box, in dialog units.

_helpID_

Numeric expression indicating the ID used to identify the dialog box during WM_HELP processing.

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

_control-statements_

Body of the DIALOGEX resource is made up of any number of control statements. There are four families of control statements: generic, static, button, and edit.

#### Example

The following demonstrates the usage of the DIALOG statement:

```
include windows.inc

.resource
 DIALOGEX 0, 0, 260, 183,
 STYLE DS_SETFONT or DS_MODALFRAME or DS_FIXEDSYS or WS_POPUP or WS_CAPTION or WS_SYSMENU,
 CAPTION "DialogTitle",
 FONT 8, "MS Shell Dlg", 400, 0, 0x1 {
    }
```

#### See Also

[Asmc Resource Compiler](readme.md) | [DIALOG](dialog.md)
