Asmc Macro Assembler Reference

## MENUEX

Defines the contents of a menu resource. A menu resource is a collection of information that defines the appearance and function of an application menu. A menu is a special input tool that lets a user select commands and open submenus from a list of menu items. It also defines the following:

- Help identifiers on menus.
- Identifiers on menus.
- Use of the MFT\_\* type flags and MFS\_\* state flags. For more information on these flags, see the MENUITEMINFO structure.

syntax:

```
MENUEX { [[MENUITEM itemText [,[id][, [type][, state]]]] |
    POPUP itemText [,[id][, [type][, [state][, helpID]]]] { popupBody } . . .]}
```

#### Parameters

[MENUITEM](menuitem.md)

Defines a menu item.

_itemText_

String containing the text for the menu item. For more information, see MENUITEM.

_id_

Numeric expression indicating the identifier of the menu item.

_type_

Numeric expression indicating the type of the menu item To use the predefined MFT\_\* type values, include the following statement in your file: include winuser.inc

_state_

Numeric expression indicating the state of the menu item To use the predefined MFS\_\* state values, include the following statement in your file: include winuser.inc

[POPUP](popup.md)

Defines a menu item that has a submenu associated with it.

_itemText_

String containing the text for the menu item.

_id_

Numeric expression indicating the identifier of the menu item.

_type_

Numeric expression indicating the type of the menu item To use the predefined MFT\_\* type values, include the following statement in your file: include winuser.inc

_state_

Numeric expression indicating the state of the menu item To use the predefined MFS\_\* state values, include the following statement in your file: include winuser.inc

_helpID_

Numeric expression indicating the identifier used to identify the menu during WM\_HELP processing.

_popupBody_

Contains any combination of the MENUITEM and POPUP statements.

#### Example

```
 MENUEX {
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
