Asmc Macro Assembler Reference

## CLASS

Defines the class of the dialog box.

The CLASS statement appears in the optional section before a DIALOG statement's main. If no class is given, the standard dialog class is used.

syntax:

```
CLASS class
```

#### Parameters

_class_

A 16-bit unsigned integer or a string, enclosed in double quotation marks ("), that identifies the class of the dialog box. If the window procedure for the class does not process a message sent to it, it must call the DefDlgProc function to ensure that all messages are handled properly for the dialog box. A private class can use DefDlgProc as the default window procedure. The class must be registered with the cbWndExtra member of the WNDCLASS structure set to DLGWINDOWEXTRA.

#### Remarks

The CLASS statement should only be used with special cases, because it overrides the normal processing of a dialog box. The CLASS statement converts a dialog box to a window of the specified class; depending on the class, this could give undesirable results. Do not use the redefined control-class names with this statement.

#### Example

The following example demonstrates the use of the CLASS statement:

```
CLASS myclassID
```

#### See Also

[Asmc Resource Compiler](readme.md)
