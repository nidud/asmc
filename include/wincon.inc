ifndef __LIBC_INC
 include libc.inc
endif
ifndef _WINDEF_
 include windef.inc
endif
.xlist
;
; module contains the public data structures, data types, This ?
; procedures exported by the NT console subsystem. and ?
;
ifndef _WINCON_
_WINCON_ equ 1

ifdef __PE__
option	dllimport:<kernel32>
endif

COORD			STRUC
x			dw ?
y			dw ?
COORD			ENDS
PCOORD			typedef ptr COORD

SMALL_RECT		STRUC
Left			dw ?
Top			dw ?
Right			dw ?
Bottom			dw ?
SMALL_RECT		ENDS
PSMALL_RECT		typedef ptr SMALL_RECT

KEY_EVENT_RECORD	STRUC
bKeyDown		BOOL ?
wRepeatCount		dw ?
wVirtualKeyCode		dw ?
wVirtualScanCode	dw ?
UNION
  UnicodeChar		dw ?
  AsciiChar		db ?
ENDS
dwControlKeyState	dd ?
KEY_EVENT_RECORD	ENDS
PKEY_EVENT_RECORD	typedef ptr KEY_EVENT_RECORD

;;
;; ControlKeyState flags
;;

RIGHT_ALT_PRESSED	equ 0x0001 ;; the right alt key is pressed.
LEFT_ALT_PRESSED	equ 0x0002 ;; the left alt key is pressed.
RIGHT_CTRL_PRESSED	equ 0x0004 ;; the right ctrl key is pressed.
LEFT_CTRL_PRESSED	equ 0x0008 ;; the left ctrl key is pressed.
SHIFT_PRESSED		equ 0x0010 ;; the shift key is pressed.
NUMLOCK_ON		equ 0x0020 ;; the numlock light is on.
SCROLLLOCK_ON		equ 0x0040 ;; the scrolllock light is on.
CAPSLOCK_ON		equ 0x0080 ;; the capslock light is on.
ENHANCED_KEY		equ 0x0100 ;; the key is enhanced.
NLS_DBCSCHAR		equ 0x00010000 ;; DBCS for JPN: SBCS/DBCS mode.
NLS_ALPHANUMERIC	equ 0x00000000 ;; DBCS for JPN: Alphanumeric mode.
NLS_KATAKANA		equ 0x00020000 ;; DBCS for JPN: Katakana mode.
NLS_HIRAGANA		equ 0x00040000 ;; DBCS for JPN: Hiragana mode.
NLS_ROMAN		equ 0x00400000 ;; DBCS for JPN: Roman/Noroman mode.
NLS_IME_CONVERSION	equ 0x00800000 ;; DBCS for JPN: IME conversion.
NLS_IME_DISABLE		equ 0x20000000 ;; DBCS for JPN: IME enable/disable.

MOUSE_EVENT_RECORD	STRUC
dwMousePosition		COORD <>
dwButtonState		dd ?
dwControlKeyState	dd ?
dwEventFlags		dd ?
MOUSE_EVENT_RECORD	ENDS
PMOUSE_EVENT_RECORD	typedef ptr MOUSE_EVENT_RECORD

;;
;; ButtonState flags
;;

FROM_LEFT_1ST_BUTTON_PRESSED equ 0x0001
RIGHTMOST_BUTTON_PRESSED     equ 0x0002
FROM_LEFT_2ND_BUTTON_PRESSED equ 0x0004
FROM_LEFT_3RD_BUTTON_PRESSED equ 0x0008
FROM_LEFT_4TH_BUTTON_PRESSED equ 0x0010

;;
;; EventFlags
;;

MOUSE_MOVED		equ 0x0001
DOUBLE_CLICK		equ 0x0002
MOUSE_WHEELED		equ 0x0004

WINDOW_BUFFER_SIZE_RECORD STRUC
dwSize			COORD <>
WINDOW_BUFFER_SIZE_RECORD ENDS
PWINDOW_BUFFER_SIZE_RECORD typedef ptr WINDOW_BUFFER_SIZE_RECORD

MENU_EVENT_RECORD	STRUC
dwCommandId		UINT ?
MENU_EVENT_RECORD	ENDS
PMENU_EVENT_RECORD	typedef ptr MENU_EVENT_RECORD

FOCUS_EVENT_RECORD	STRUC
bSetFocus		BOOL ?
FOCUS_EVENT_RECORD	ENDS
PFOCUS_EVENT_RECORD	typedef ptr FOCUS_EVENT_RECORD

INPUT_RECORD		STRUC DWORD
EventType		dw ?
UNION
 KeyEvent		KEY_EVENT_RECORD <>
 MouseEvent		MOUSE_EVENT_RECORD <>
 WindowBufferSizeEvent	WINDOW_BUFFER_SIZE_RECORD <>
 MenuEvent		MENU_EVENT_RECORD <>
 FocusEvent		FOCUS_EVENT_RECORD <>
ENDS
INPUT_RECORD		ENDS
PINPUT_RECORD		typedef ptr INPUT_RECORD

;;
;;  EventType flags:
;;

KEY_EVENT		equ 0x0001 ;; Event contains key event record
MOUSE_EVENT		equ 0x0002 ;; Event contains mouse event record
WINDOW_BUFFER_SIZE_EVENT equ 0x0004 ;; Event contains window change event record
MENU_EVENT		equ 0x0008 ;; Event contains menu event record
FOCUS_EVENT		equ 0x0010 ;; event contains focus change

CHAR_INFO		STRUC
UNION
 UnicodeChar		WCHAR ?
 AsciiChar		CHAR ?
ENDS
Attributes		dw ?
CHAR_INFO		ENDS
PCHAR_INFO		typedef ptr CHAR_INFO

;;
;; Attributes flags:
;;

FOREGROUND_BLUE			equ 0x0001 ;; text color contains blue.
FOREGROUND_GREEN		equ 0x0002 ;; text color contains green.
FOREGROUND_RED			equ 0x0004 ;; text color contains red.
FOREGROUND_INTENSITY		equ 0x0008 ;; text color is intensified.
BACKGROUND_BLUE			equ 0x0010 ;; background color contains blue.
BACKGROUND_GREEN		equ 0x0020 ;; background color contains green.
BACKGROUND_RED			equ 0x0040 ;; background color contains red.
BACKGROUND_INTENSITY		equ 0x0080 ;; background color is intensified.
COMMON_LVB_LEADING_BYTE		equ 0x0100 ;; Leading Byte of DBCS
COMMON_LVB_TRAILING_BYTE	equ 0x0200 ;; Trailing Byte of DBCS
COMMON_LVB_GRID_HORIZONTAL	equ 0x0400 ;; DBCS: Grid attribute: top horizontal.
COMMON_LVB_GRID_LVERTICAL	equ 0x0800 ;; DBCS: Grid attribute: left vertical.
COMMON_LVB_GRID_RVERTICAL	equ 0x1000 ;; DBCS: Grid attribute: right vertical.
COMMON_LVB_REVERSE_VIDEO	equ 0x4000 ;; DBCS: Reverse fore/back ground attribute.
COMMON_LVB_UNDERSCORE		equ 0x8000 ;; DBCS: Underscore.
COMMON_LVB_SBCSDBCS		equ 0x0300 ;; SBCS or DBCS flag.


CONSOLE_SCREEN_BUFFER_INFO STRUC
dwSize			COORD <>
dwCursorPosition	COORD <>
wAttributes		dw ?
srWindow		SMALL_RECT <>
dwMaximumWindowSize	COORD <>
CONSOLE_SCREEN_BUFFER_INFO ENDS
PCONSOLE_SCREEN_BUFFER_INFO typedef ptr CONSOLE_SCREEN_BUFFER_INFO

CONSOLE_CURSOR_INFO	STRUC
dwSize			dd ?
bVisible		BOOL ?
CONSOLE_CURSOR_INFO	ENDS
PCONSOLE_CURSOR_INFO	typedef ptr CONSOLE_CURSOR_INFO

;;
;; typedef for ctrl-c handler routines
;;

;BOOL
PHANDLER_ROUTINE	typedef proto _CType CtrlType:DWORD

CTRL_C_EVENT		equ 0
CTRL_BREAK_EVENT	equ 1
CTRL_CLOSE_EVENT	equ 2
;; 3 is reserved!
;; 4 is reserved!
CTRL_LOGOFF_EVENT	equ 5
CTRL_SHUTDOWN_EVENT	equ 6

;;
;;  Input Mode flags:
;;

ENABLE_PROCESSED_INPUT	equ 0x0001
ENABLE_LINE_INPUT	equ 0x0002
ENABLE_ECHO_INPUT	equ 0x0004
ENABLE_WINDOW_INPUT	equ 0x0008
ENABLE_MOUSE_INPUT	equ 0x0010

;;
;; Output Mode flags:
;;

ENABLE_PROCESSED_OUTPUT equ 0x0001
ENABLE_WRAP_AT_EOL_OUTPUT equ 0x0002

;;
;; direct API definitions.
;;

;BOOL
PeekConsoleInputA proto _CType \
	 hConsoleInput: HANDLE,
	      lpBuffer: PINPUT_RECORD,
	       nLength: DWORD,
 lpNumberOfEventsRead : LPDWORD
PeekConsoleInputW proto _CType \
	 hConsoleInput: HANDLE,
	      lpBuffer: PINPUT_RECORD,
	       nLength: DWORD,
 lpNumberOfEventsRead : LPDWORD
ifdef _UNICODE
PeekConsoleInput	equ <PeekConsoleInputW>
else
PeekConsoleInput	equ <PeekConsoleInputA>
endif ;; NOT UNICODE

;BOOL
ReadConsoleInputA proto _CType \
	 hConsoleInput: HANDLE,
	      lpBuffer: PINPUT_RECORD,
	       nLength: DWORD,
 lpNumberOfEventsRead : LPDWORD
ReadConsoleInputW proto _CType \
	 hConsoleInput: HANDLE,
	      lpBuffer: PINPUT_RECORD,
	       nLength: DWORD,
 lpNumberOfEventsRead : LPDWORD
ifdef _UNICODE
ReadConsoleInput	equ <ReadConsoleInputW>
else
ReadConsoleInput	equ <ReadConsoleInputA>
endif ;; NOT UNICODE

;BOOL
WriteConsoleInputA proto _CType \
	   hConsoleInput: HANDLE,
		lpBuffer: ptr INPUT_RECORD,
		 nLength: DWORD,
 lpNumberOfEventsWritten: LPDWORD

;BOOL
WriteConsoleInputW proto _CType \
	   hConsoleInput: HANDLE,
		lpBuffer: ptr INPUT_RECORD,
		 nLength: DWORD,
 lpNumberOfEventsWritten: LPDWORD
ifdef _UNICODE
WriteConsoleInput	equ <WriteConsoleInputW>
else
WriteConsoleInput	equ <WriteConsoleInputA>
endif ;; NOT UNICODE

;BOOL
ReadConsoleOutputA proto _CType \
	hConsoleOutput: HANDLE,
	      lpBuffer: PCHAR_INFO,
	  dwBufferSize: COORD,
	 dwBufferCoord: COORD,
	 lpReadRegion : PSMALL_RECT
ReadConsoleOutputW proto _CType \
	hConsoleOutput: HANDLE,
	      lpBuffer: PCHAR_INFO,
	  dwBufferSize: COORD,
	 dwBufferCoord: COORD,
	 lpReadRegion : PSMALL_RECT
ifdef _UNICODE
ReadConsoleOutput	equ <ReadConsoleOutputW>
else
ReadConsoleOutput	equ <ReadConsoleOutputA>
endif ;; NOT UNICODE

;BOOL
WriteConsoleOutputA proto _CType \
	hConsoleOutput: HANDLE,
	      lpBuffer: ptr CHAR_INFO,
	  dwBufferSize: COORD,
	 dwBufferCoord: COORD,
	lpWriteRegion : PSMALL_RECT
WriteConsoleOutputW proto _CType \
	hConsoleOutput: HANDLE,
	      lpBuffer: ptr CHAR_INFO,
	  dwBufferSize: COORD,
	 dwBufferCoord: COORD,
	lpWriteRegion : PSMALL_RECT
ifdef _UNICODE
WriteConsoleOutput	equ <WriteConsoleOutputW>
else
WriteConsoleOutput	equ <WriteConsoleOutputA>
endif ;; NOT UNICODE

;BOOL
ReadConsoleOutputCharacterA proto _CType \
	hConsoleOutput: HANDLE,
	   lpCharacter: LPSTR,
	       nLength: DWORD,
	   dwReadCoord: COORD,
  lpNumberOfCharsRead : LPDWORD
ReadConsoleOutputCharacterW proto _CType \
	hConsoleOutput: HANDLE,
	   lpCharacter: LPWSTR,
	       nLength: DWORD,
	   dwReadCoord: COORD,
  lpNumberOfCharsRead : LPDWORD
ifdef _UNICODE
ReadConsoleOutputCharacter equ <ReadConsoleOutputCharacterW>
else
ReadConsoleOutputCharacter equ <ReadConsoleOutputCharacterA>
endif ;; NOT UNICODE

;BOOL
ReadConsoleOutputAttribute proto _CType \
	hConsoleOutput: HANDLE,
	   lpAttribute: LPWORD,
	       nLength: DWORD,
	   dwReadCoord: COORD,
  lpNumberOfAttrsRead : LPDWORD

;BOOL
WriteConsoleOutputCharacterA proto _CType \
	hConsoleOutput: HANDLE,
	   lpCharacter: LPCSTR,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfCharsWritten : LPDWORD
WriteConsoleOutputCharacterW proto _CType \
	hConsoleOutput: HANDLE,
	   lpCharacter: LPCWSTR,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfCharsWritten : LPDWORD
ifdef _UNICODE
WriteConsoleOutputCharacter equ <WriteConsoleOutputCharacterW>
else
WriteConsoleOutputCharacter equ <WriteConsoleOutputCharacterA>
endif ;; NOT UNICODE

;BOOL
WriteConsoleOutputAttribute proto _CType \
	hConsoleOutput: HANDLE,
	   lpAttribute: ptr WORD,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfAttrsWritten: LPDWORD

;BOOL
FillConsoleOutputCharacterA proto _CType \
	hConsoleOutput: HANDLE,
	    cCharacter: DWORD,;CHAR,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfCharsWritten : LPDWORD
FillConsoleOutputCharacterW proto _CType \
	hConsoleOutput: HANDLE,
	    cCharacter: DWORD,;WCHAR,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfCharsWritten: LPDWORD
ifdef _UNICODE
FillConsoleOutputCharacter equ <FillConsoleOutputCharacterW>
else
FillConsoleOutputCharacter equ <FillConsoleOutputCharacterA>
endif ;; NOT UNICODE

;BOOL
FillConsoleOutputAttribute proto _CType \
	hConsoleOutput: HANDLE,
	    wAttribute: WORD,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfAttrsWritten: LPDWORD

;BOOL
GetConsoleMode proto _CType \
	hConsoleHandle: HANDLE,
	       lpMode : LPDWORD

;BOOL
GetNumberOfConsoleInputEvents proto _CType \
	 hConsoleInput: HANDLE,
      lpNumberOfEvents: LPDWORD

;BOOL
GetConsoleScreenBufferInfo proto _CType \
	hConsoleOutput: HANDLE,
lpConsoleScreenBufferInfo : PCONSOLE_SCREEN_BUFFER_INFO

;COORD
GetLargestConsoleWindowSize proto _CType \
	hConsoleOutput: HANDLE

;BOOL
GetConsoleCursorInfo proto _CType \
	hConsoleOutput: HANDLE,
  lpConsoleCursorInfo : PCONSOLE_CURSOR_INFO

;BOOL
GetNumberOfConsoleMouseButtons proto _CType \
lpNumberOfMouseButtons: LPDWORD

;BOOL
SetConsoleMode proto _CType \
	hConsoleHandle: HANDLE,
	       dwMode : DWORD

;BOOL
SetConsoleActiveScreenBuffer proto _CType \
	hConsoleOutput: HANDLE

;BOOL
FlushConsoleInputBuffer proto _CType \
	 hConsoleInput: HANDLE

;BOOL
SetConsoleScreenBufferSize proto _CType \
	hConsoleOutput: HANDLE,
	       dwSize : COORD

;BOOL
SetConsoleCursorPosition proto _CType \
	hConsoleOutput: HANDLE,
     dwCursorPosition : COORD

;BOOL
SetConsoleCursorInfo proto _CType \
	hConsoleOutput: HANDLE,
   lpConsoleCursorInfo: ptr CONSOLE_CURSOR_INFO

;BOOL
ScrollConsoleScreenBufferA proto _CType \
	hConsoleOutput: HANDLE,
     lpScrollRectangle: ptr SMALL_RECT,
       lpClipRectangle: ptr SMALL_RECT,
   dwDestinationOrigin: COORD,
		lpFill: ptr SMALL_RECT

;BOOL
ScrollConsoleScreenBufferW proto _CType \
	hConsoleOutput: HANDLE,
     lpScrollRectangle: ptr SMALL_RECT,
       lpClipRectangle: ptr SMALL_RECT,
   dwDestinationOrigin: COORD,
		lpFill: ptr CHAR_INFO
ifdef _UNICODE
ScrollConsoleScreenBuffer equ <ScrollConsoleScreenBufferW>
else
ScrollConsoleScreenBuffer equ <ScrollConsoleScreenBufferA>
endif ;; NOT UNICODE

;BOOL
SetConsoleWindowInfo proto _CType \
	hConsoleOutput: HANDLE,
	     bAbsolute: BOOL,
       lpConsoleWindow: ptr SMALL_RECT

;BOOL
SetConsoleTextAttribute proto _CType \
	hConsoleOutput: HANDLE,
	  wAttributes : WORD

;BOOL
SetConsoleCtrlHandler proto _CType \
	HandlerRoutine: PHANDLER_ROUTINE,
		  _Add: BOOL

;BOOL
GenerateConsoleCtrlEvent proto _CType \
	   dwCtrlEvent: DWORD,
     dwProcessGroupId : DWORD

;BOOL
AllocConsole proto _CType

;BOOL
FreeConsole proto _CType


;DWORD
GetConsoleTitleA proto _CType \
	lpConsoleTitle: LPSTR,
		nSize : DWORD
GetConsoleTitleW proto _CType \
	lpConsoleTitle: LPWSTR,
		nSize : DWORD
ifdef _UNICODE
GetConsoleTitle		equ <GetConsoleTitleW>
else
GetConsoleTitle		equ <GetConsoleTitleA>
endif ;; NOT UNICODE

;BOOL
SetConsoleTitleA proto _CType \
       lpConsoleTitle : LPCSTR
SetConsoleTitleW proto _CType \
       lpConsoleTitle : LPCWSTR
ifdef _UNICODE
SetConsoleTitle		equ <SetConsoleTitleW>
else
SetConsoleTitle		equ <SetConsoleTitleA>
endif ;; NOT UNICODE

;BOOL
ReadConsoleA proto _CType \
	 hConsoleInput: HANDLE,
	      lpBuffer: LPVOID,
  nNumberOfCharsToRead: DWORD,
   lpNumberOfCharsRead: LPDWORD,
	   lpReserved : LPVOID
ReadConsoleW proto _CType \
	 hConsoleInput: HANDLE,
	      lpBuffer: LPVOID,
  nNumberOfCharsToRead: DWORD,
   lpNumberOfCharsRead: LPDWORD,
	   lpReserved : LPVOID
ifdef _UNICODE
ReadConsole		equ <ReadConsoleW>
else
ReadConsole		equ <ReadConsoleA>
endif ;; NOT UNICODE

;BOOL
WriteConsoleA proto _CType \
	hConsoleOutput: HANDLE,
	      lpBuffer: PVOID,
 nNumberOfCharsToWrite: DWORD,
lpNumberOfCharsWritten: LPDWORD,
	    lpReserved: LPVOID
WriteConsoleW proto _CType \
	hConsoleOutput: HANDLE,
	      lpBuffer: PVOID,
 nNumberOfCharsToWrite: DWORD,
lpNumberOfCharsWritten: LPDWORD,
	    lpReserved: LPVOID
ifdef _UNICODE
WriteConsole		equ <WriteConsoleW>
else
WriteConsole		equ <WriteConsoleA>
endif ;; NOT UNICODE

CONSOLE_TEXTMODE_BUFFER equ 1

;HANDLE
CreateConsoleScreenBuffer proto _CType \
       dwDesiredAccess: DWORD,
	   dwShareMode: DWORD,
  lpSecurityAttributes: ptr SECURITY_ATTRIBUTES,
	       dwFlags: DWORD,
    lpScreenBufferData: LPVOID

;UINT
GetConsoleCP proto _CType

;BOOL
SetConsoleCP proto _CType \
	  wCodePageID : UINT

;UINT
GetConsoleOutputCP proto _CType

;BOOL
SetConsoleOutputCP proto _CType \
	  wCodePageID : UINT

endif ;; _WINCON_

.list
