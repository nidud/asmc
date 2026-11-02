Asmc Macro Assembler Reference

## POPUP

Defines a menu item that can contain menu items and submenus.

syntax:

```
POPUP text, [optionlist] {item-definitions ...}
```

#### Parameters

_text_

String that contains the name of the menu. This string must be enclosed in double quotation marks (").

_optionlist_

This parameter specifies redefined menu options that specify the appearance of the menu item. This optional parameter can be one or more of the following.

<table>
<tr><td>Option</td><td>Description</td></tr>
<tr><td>CHECKED</td><td>Menu item has a check mark next to it. This option is not valid for a top-level menu.</td></tr>
<tr><td>GRAYED</td><td>Menu item is initially inactive and appears on the menu in gray or a lightened shade of the menu-text color. This option cannot be used with the INACTIVE option.</td></tr>
<tr><td>HELP</td><td>Identifies a help item. The menu item is place at the right-most position on the menu bar.</td></tr>
<tr><td>INACTIVE</td><td>Menu item is displayed but it cannot be selected. This option cannot be used with the GRAYED option.</td></tr>
<tr><td>MENUBARBREAK</td><td>Same as MENUBREAK except that for pop-up menus, it separates the new column from the old column with a vertical line.</td></tr>
<tr><td>MENUBREAK</td><td>Places the menu item on a new line for static menu-bar items. For menus, it places the menu item in a new column with no dividing line between the columns.</td></tr>
</table>

#### Example

```
 MENU {
    POPUP "&Elements" {
         MENUITEM "&Oxygen", 200,
         MENUITEM "&Carbon", 201, CHECKED,
         MENUITEM "&Hydrogen", 202,
         MENUITEM SEPARATOR,
         MENUITEM "&Sulfur", 203,
         MENUITEM "Ch&lorine", 204
        },
    POPUP "&Compounds" {
         POPUP "&Sugars" {
            MENUITEM "&Glucose", 301,
            MENUITEM "&Sucrose", 302, CHECKED,
            MENUITEM "&Lactose", 303, MENUBREAK,
            MENUITEM "&Fructose", 304
            },
         POPUP "&Acids" {
            MENUITEM "&Hydrochloric", 401,
            MENUITEM "&Sulfuric", 402
            }
        }
    }
```

#### See Also

[Asmc Resource Compiler](readme.md)
