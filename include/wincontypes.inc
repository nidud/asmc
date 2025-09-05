ifndef _WINCONTYPES_
define _WINCONTYPES_
ifndef _MINWINDEF_
include minwindef.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM or WINAPI_PARTITION_GAMES)

COORD                   struct
X                       sword ?
Y                       sword ?
COORD                   ends
PCOORD                  typedef ptr COORD

SMALL_RECT              struct
Left                    sword ?
Top                     sword ?
Right                   sword ?
Bottom                  sword ?
SMALL_RECT              ends
PSMALL_RECT             typedef ptr SMALL_RECT

KEY_EVENT_RECORD        struct
bKeyDown                BOOL ?
wRepeatCount            dw ?
wVirtualKeyCode         dw ?
wVirtualScanCode        dw ?
union uChar
 UnicodeChar            dw ?
 AsciiChar              CHAR ?
ends
dwControlKeyState       DWORD ?
KEY_EVENT_RECORD        ends
PKEY_EVENT_RECORD       typedef ptr KEY_EVENT_RECORD

define RIGHT_ALT_PRESSED     0x0001
define LEFT_ALT_PRESSED      0x0002
define RIGHT_CTRL_PRESSED    0x0004
define LEFT_CTRL_PRESSED     0x0008
define SHIFT_PRESSED         0x0010
define NUMLOCK_ON            0x0020
define SCROLLLOCK_ON         0x0040
define CAPSLOCK_ON           0x0080
define ENHANCED_KEY          0x0100
define NLS_DBCSCHAR          0x00010000
define NLS_ALPHANUMERIC      0x00000000
define NLS_KATAKANA          0x00020000
define NLS_HIRAGANA          0x00040000
define NLS_ROMAN             0x00400000
define NLS_IME_CONVERSION    0x00800000
define ALTNUMPAD_BIT         0x04000000
define NLS_IME_DISABLE       0x20000000

MOUSE_EVENT_RECORD      struct
dwMousePosition         COORD <>
dwButtonState           dd ?
dwControlKeyState       dd ?
dwEventFlags            dd ?
MOUSE_EVENT_RECORD      ends
PMOUSE_EVENT_RECORD     typedef ptr MOUSE_EVENT_RECORD

define FROM_LEFT_1ST_BUTTON_PRESSED    0x0001
define RIGHTMOST_BUTTON_PRESSED        0x0002
define FROM_LEFT_2ND_BUTTON_PRESSED    0x0004
define FROM_LEFT_3RD_BUTTON_PRESSED    0x0008
define FROM_LEFT_4TH_BUTTON_PRESSED    0x0010

define MOUSE_MOVED   0x0001
define DOUBLE_CLICK  0x0002
define MOUSE_WHEELED 0x0004
if(_WIN32_WINNT ge 0x0600)
define MOUSE_HWHEELED 0x0008
endif

WINDOW_BUFFER_SIZE_RECORD struct
dwSize                  COORD <>
WINDOW_BUFFER_SIZE_RECORD ends
PWINDOW_BUFFER_SIZE_RECORD typedef ptr WINDOW_BUFFER_SIZE_RECORD

MENU_EVENT_RECORD       struct
dwCommandId             dd ?
MENU_EVENT_RECORD       ends
PMENU_EVENT_RECORD      typedef ptr MENU_EVENT_RECORD

FOCUS_EVENT_RECORD      struct
bSetFocus               BOOL ?
FOCUS_EVENT_RECORD      ends
PFOCUS_EVENT_RECORD     typedef ptr FOCUS_EVENT_RECORD

INPUT_RECORD            struct 4
EventType               WORD ?
union Event
 KeyEvent               KEY_EVENT_RECORD <>
 MouseEvent             MOUSE_EVENT_RECORD <>
 WindowBufferSizeEvent  WINDOW_BUFFER_SIZE_RECORD <>
 MenuEvent              MENU_EVENT_RECORD <>
 FocusEvent             FOCUS_EVENT_RECORD <>
ends
INPUT_RECORD            ends
PINPUT_RECORD           typedef ptr INPUT_RECORD

define KEY_EVENT         0x0001
define MOUSE_EVENT       0x0002
define WINDOW_BUFFER_SIZE_EVENT 0x0004
define MENU_EVENT 0x0008
define FOCUS_EVENT 0x0010

CHAR_INFO               struct
union Char
 UnicodeChar            dw ?
 AsciiChar              CHAR ?
ends
Attributes              dw ?
CHAR_INFO               ends
PCHAR_INFO              typedef ptr CHAR_INFO

CONSOLE_FONT_INFO       struct
nFont                   dd ?
dwFontSize              COORD <>
CONSOLE_FONT_INFO       ends
PCONSOLE_FONT_INFO      typedef ptr CONSOLE_FONT_INFO

HPCON                   typedef ptr

endif

endif
