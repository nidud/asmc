Asmc Macro Assembler Reference

## MENU

Defines the contents of a menu resource. A menu resource is a collection of information that defines the appearance and function of an application menu. A menu is a special input tool that lets a user select commands and open submenus from a list of menu items.

syntax:

```
MENU [optional-statements] {item-definitions ...}
```

#### Parameters

_optional-statements_

- [CHARACTERISTICS](characteristics.md)
- [LANGUAGE](language.md)
- [VERSION](version.md)


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
