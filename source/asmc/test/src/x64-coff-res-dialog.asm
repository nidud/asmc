
; Dialog

define WS_POPUP  0x80000000
define WS_BORDER 0x00800000

.resource
 DIALOG 10, 10, 300, 110,
 STYLE WS_POPUP or WS_BORDER,
 CAPTION "Error!" {
    CTEXT "Select One:", 1, 10, 10, 280, 12,
    PUSHBUTTON "&Retry", 2, 75, 30, 60, 12,
    PUSHBUTTON "&Abort", 3, 75, 50, 60, 12,
    PUSHBUTTON "&Ignore", 4, 75, 80, 60, 12
    }

 end
