; _COLORAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.data

at_background byte \
    0x00,   ; BG_DESKTOP
    0x10,   ; BG_PANEL
    0x70,   ; BG_DIALOG
    0x70,   ; BG_MENU
    0x40,   ; BG_ERROR
    0x30,   ; BG_TITLE
    0x30,   ; BG_INVERSE
    0x70,   ; BG_GRAY
    0x30,   ; BG_PBUTTON
    0x30,   ; BG_INVPANEL
    0x30,   ; BG_INVMENU
    0x00,   ; BG_TVIEW
    0x10,   ; BG_TEDIT
    0x10,
    0x00,
    0x00

at_foreground byte \
    0x00,   ; FG_TITLE
    0x0F,   ; FG_FRAME
    0x0F,   ; FG_FILES
    0x07,   ; FG_SYSTEM
    0x08,   ; FG_HIDDEN
    0x00,   ; FG_PBSHADE
    0x00,   ; FG_KEYBAR
    0x07,   ; FG_DESKTOP
    0x08,   ; FG_INACTIVE
    0x00,   ; FG_DIALOG
    0x0A,   ; FG_PANEL
    0x0B,   ; FG_SUBDIR
    0x00,   ; FG_MENU
    0x0F,   ; FG_TITLEKEY
    0x0F,   ; FG_DIALOGKEY
    0x0F,   ; FG_MENUKEY
    16 dup(0)

    end
