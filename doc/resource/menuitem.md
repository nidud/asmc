Asmc Macro Assembler Reference

## MENUITEM

Defines a menu item.

syntax:

```
MENUITEM text, result, [optionlist]
MENUITEM SEPARATOR
```

#### Parameters

_text_

The name of the menu item.

The string can contain the escape characters \\t and \\a. The \\t character inserts a tab in the string and is used to align text in columns. Tab characters should be used only in menus, not in menu bars. (For information on menus, see POPUP Resource.) The \\a character aligns all text that follows it flush right to the menu bar or pop-up menu.

_result_

A number that specifies the result generated when the user selects the menu item. This parameter takes an integer value. Menu-item results are always integers; when the user clicks the menu-item name, the result is sent to the window that owns the menu.

_optionlist_

The appearance of the menu item. This optional parameter takes one or more of the following redefined menu options, separated by commas or spaces.

<table>
<tr><td>Option</td><td>Description</td></tr>
<tr><td>CHECKED</td><td>Menu item has a check mark next to it.</td></tr>
<tr><td>GRAYED</td><td>Menu item is initially inactive and appears on the menu in gray or a lightened shade of the menu-text color. This option cannot be used with the INACTIVE option.</td></tr>
<tr><td>HELP</td><td>Identifies a help item. This option has no effect on the appearance of the menu item.</td></tr>
<tr><td>INACTIVE</td><td>Menu item is displayed but it cannot be selected. This option cannot be used with the GRAYED option.</td></tr>
<tr><td>MENUBARBREAK</td><td>Same as MENUBREAK except that for pop-up menus, it separates the new column from the old column with a vertical line.</td></tr>
<tr><td>MENUBREAK</td><td>Places the menu item on a new line for static menu-bar items. For menus, it places the menu item in a new column with no dividing line between the columns.</td></tr>
</table>

MENUITEM SEPARATOR

The MENUITEM SEPARATOR form of the MENUITEM statement creates an inactive menu item that serves as a dividing bar between two active menu items on a menu. Note that this form works inside a MENU block, whereas MENUITEM's inside a MENUEX instead require the form MENUITEM "", -1, MFT\_SEPARATOR.

#### Example

The following example demonstrates the use of the MENUITEM and MENUITEM SEPARATOR statements:

```
MENUITEM "&Roman", 206, CHECKED, GRAYED
MENUITEM SEPARATOR
MENUITEM "&Blackletter", 301
```

#### See Also

[Asmc Resource Compiler](readme.md)
