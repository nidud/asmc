
; Menu with option-list

.resource
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
 end
