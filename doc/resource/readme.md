Asmc Macro Assembler Reference

# Asmc Resource Compiler

### In This Section

- About Asmc Resource Compiler
- Parsing Resource-Definition Statements
- Resource-Definition Statements

### About Asmc Resource Compiler

Converts resource-definition statements into a binary resource that can be used by the Asmc internal linker or MS Windows linker. The resource-definition statements are similar to those used by the Microsoft Resource Compiler (RC). The Asmc Resource Compiler supports a subset of the RC syntax, and is not compatible with all RC resource-definition statements.

### Parsing Resource-Definition Statements

Each line has to begin with a resource-definition statement. The resource-definition statements are case-sensitive.

The unique 16-bit unsigned integer value that identifies a resource starts at 100, except for STRINGTABLE resources, which start at 384 (0x180) where each table allocates 16 strings. This means the maximum number of resource-definitions is 256 (100..383).

Lines are textual and can be continued by using a comma (,) at the end of the line. Statements beyond the default parameters can be specified in any order, but must be prefixed with their respective statement keywords.

Example:

The RC-specific syntax for a dialog box:
```
nameID DIALOGEX x, y, width, height [, helpID] [optional-statements]  {control-statements}
```
The Asmc-specific syntax for a dialog box:
```
DIALOGEX x, y, width, height [, HELP helpID] [, optional-statements]  {control-statements}
```

### Resource-Definition Statements

The resource-definition statements can be divided into the following categories:

- Resources
- Controls
- Statements

The following tables describe the resource-definition statements.

#### Resources

The following table describes the resource-definition statements that define resources.

<table>
<tr><td>Resource</td><td>Description</td></tr>
<tr><td><a href="accelerators.md">ACCELERATORS</a></td><td>Defines keyboard shortcuts for menu items.</td></tr>
<tr><td><a href="cursor.md">CURSOR</a></td><td>Defines a cursor by specifying the name of the file that contains it.</td></tr>
<tr><td><a href="dialog.md">DIALOG</a></td><td>Defines a dialog box.</td></tr>
<tr><td><a href="dialogex.md">DIALOGEX</a></td><td>Defines an extended dialog box.</td></tr>
<tr><td><a href="icon.md">ICON</a></td><td>Defines an icon by specifying the name of the file that contains it.</td></tr>
<tr><td><a href="language.md">LANGUAGE</a></td><td>Sets the language for all resources.</td></tr>
<tr><td><a href="menu.md">MENU</a></td><td>Defines a menu.</td></tr>
<tr><td><a href="menuex.md">MENUEX</a></td><td>Defines an extended menu.</td></tr>
<tr><td><a href="stringtable.md">STRINGTABLE</a></td><td>Defines string resources. String resources are Unicode strings that can be loaded from the executable file.</td></tr>
</table>

#### Controls

<table>
<tr><td>Control</td><td>Description</td></tr>
<tr><td><a href="checkbox.md">CHECKBOX</a></td><td>Creates a check box control.</td></tr>
<tr><td><a href="combobox.md">COMBOBOX</a></td><td>Creates a combo box control.</td></tr>
<tr><td><a href="control.md">CONTROL</a></td><td>Creates a control.</td></tr>
<tr><td><a href="ctext.md">CTEXT</a></td><td>Creates a static text control.</td></tr>
<tr><td><a href="defpushbutton.md">DEFPUSHBUTTON</a></td><td>Creates a default push button control.</td></tr>
<tr><td><a href="edittext.md">EDITTEXT</a></td><td>Creates an edit control.</td></tr>
<tr><td><a href="groupbox.md">GROUPBOX</a></td><td>Creates a group box control.</td></tr>
<tr><td><a href="listbox.md">LISTBOX</a></td><td>Creates a list box control.</td></tr>
<tr><td><a href="ltext.md">LTEXT</a></td><td>Creates a static text control.</td></tr>
<tr><td><a href="menuitem.md">MENUITEM</a></td><td>Creates a menu item.</td></tr>
<tr><td><a href="popup.md">POPUP</a></td><td>Creates a popup menu.</td></tr>
<tr><td><a href="pushbox.md">PUSHBOX</a></td><td>Creates a push box control.</td></tr>
<tr><td><a href="pushbutton.md">PUSHBUTTON</a></td><td>Creates a push button control.</td></tr>
<tr><td><a href="radiobutton.md">RADIOBUTTON</a></td><td>Creates a radio button control.</td></tr>
<tr><td><a href="rtext.md">RTEXT</a></td><td>Creates a static text control.</td></tr>
</table>

#### Statements

<table>
<tr><td>Statement</td><td>Description</td></tr>
<tr><td>ALT</td><td>See <a href="accelerators.md">ACCELERATORS</a>.</td></tr>
<tr><td>ASCII</td><td>See <a href="accelerators.md">ACCELERATORS</a>.</td></tr>
<tr><td><a href="caption.md">CAPTION</a></td><td>Sets the title for a dialog box.</td></tr>
<tr><td><a href="characteristics.md">CHARACTERISTICS</a></td><td>Specifies information about a resource that can be used by tool that can read or write resource-definition files.</td></tr>
<tr><td><a href="menuitem.md">CHECKED</a></td><td>Specifies that a check box control is initially checked.</td></tr>
<tr><td><a href="class.md">CLASS</a></td><td>Sets the class of the dialog box.</td></tr>
<tr><td>CONTROL</td><td>See <a href="accelerators.md">ACCELERATORS</a>.</td></tr>
<tr><td><a href="exstyle.md">EXSTYLE</a></td><td>Sets the extended window style of the dialog box.</td></tr>
<tr><td><a href="font.md">FONT</a></td><td>Sets the font with which the system will draw text for the dialog box.</td></tr>
<tr><td><a href="menuitem.md">GRAYED</a></td><td>Specifies that a control is initially grayed out.</td></tr>
<tr><td><a href="menuitem.md">INACTIVE</a></td><td>Specifies that a control is initially inactive.</td></tr>
<tr><td><a href="menu-statement.md">MENU</a></td><td>Sets the menu for the dialog box.</td></tr>
<tr><td><a href="menuitem.md">MENUBARBREAK</a></td><td>Sets a bar break for the menu.</td></tr>
<tr><td><a href="menuitem.md">MENUBREAK</a></td><td>Sets a break for the menu.</td></tr>
<tr><td>NOINVERT</td><td>See <a href="accelerators.md">ACCELERATORS</a>.</td></tr>
<tr><td>SHIFT</td><td>See <a href="accelerators.md">ACCELERATORS</a>.</td></tr>
<tr><td><a href="style.md">STYLE</a></td><td>Sets the window style for the dialog box.</td></tr>
<tr><td><a href="version.md">VERSION</a></td><td>Specifies version information for a resource that can be used by tool that can read or write resource-definition files.</td></tr>
<tr><td>VIRTKEY</td><td>See <a href="accelerators.md">ACCELERATORS</a>.</td></tr>
</table>

#### See Also

[Simplified Segment](../directve/simplified-segment.md) | [Option -pe](../command/option-pe.md)
