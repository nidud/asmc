include res/bitmap.inc

.resource

LANGUAGE 9, 1

ICON res/small.ico

BITMAP res/scaled100.bmp
BITMAP res/scaled125.bmp
BITMAP res/scaled150.bmp
BITMAP res/scaled200.bmp

MENU {
    POPUP "&Options" {
        MENUITEM "Increase Font Size (+)", IDM_FONT_INCREASE,
        MENUITEM "Decrease Font Size (-)", IDM_FONT_DECREASE,
        MENUITEM SEPARATOR,
        MENUITEM "Rescale on &DPICHANGED", IDM_RESCALE_ON_DPICHANGED,
        MENUITEM SEPARATOR,
        MENUITEM "E&xit", IDM_EXIT
    }
}

ACCELERATORS {
    "R", IDM_RESCALE_NOW,            ASCII
    "r", IDM_RESCALE_NOW,            ASCII
    "D", IDM_RESCALE_ON_DPICHANGED,  ASCII
    "d", IDM_RESCALE_ON_DPICHANGED,  ASCII
    "+", IDM_FONT_INCREASE,          ASCII
    "=", IDM_FONT_INCREASE,          ASCII
    "-", IDM_FONT_DECREASE,          ASCII
    "X", IDM_EXIT,                   ASCII
    "x", IDM_EXIT,                   ASCII
}

STRINGTABLE {
   "DPITUTORIAL",
   "DPI Awareness Tutorial"
}

end
