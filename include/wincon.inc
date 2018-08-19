ifndef _WINCON_
_WINCON_ equ <>
.pragma list(push, 0)
ifndef _WINDEF_
 include windef.inc
endif

ifdef __PE__
option	dllimport:<kernel32>
else
includelib kernel32.lib
endif

COORD			STRUC
x			SWORD ?
y			SWORD ?
COORD			ENDS
PCOORD			typedef ptr COORD

SMALL_RECT		STRUC
Left			SWORD ?
Top			SWORD ?
Right			SWORD ?
Bottom			SWORD ?
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


RIGHT_ALT_PRESSED	equ 0x0001
LEFT_ALT_PRESSED	equ 0x0002
RIGHT_CTRL_PRESSED	equ 0x0004
LEFT_CTRL_PRESSED	equ 0x0008
SHIFT_PRESSED		equ 0x0010
NUMLOCK_ON		equ 0x0020
SCROLLLOCK_ON		equ 0x0040
CAPSLOCK_ON		equ 0x0080
ENHANCED_KEY		equ 0x0100
NLS_DBCSCHAR		equ 0x00010000
NLS_ALPHANUMERIC	equ 0x00000000
NLS_KATAKANA		equ 0x00020000
NLS_HIRAGANA		equ 0x00040000
NLS_ROMAN		equ 0x00400000
NLS_IME_CONVERSION	equ 0x00800000
NLS_IME_DISABLE		equ 0x20000000

MOUSE_EVENT_RECORD	STRUC
dwMousePosition		COORD <>
dwButtonState		dd ?
dwControlKeyState	dd ?
dwEventFlags		dd ?
MOUSE_EVENT_RECORD	ENDS
PMOUSE_EVENT_RECORD	typedef ptr MOUSE_EVENT_RECORD


FROM_LEFT_1ST_BUTTON_PRESSED equ 0x0001
RIGHTMOST_BUTTON_PRESSED     equ 0x0002
FROM_LEFT_2ND_BUTTON_PRESSED equ 0x0004
FROM_LEFT_3RD_BUTTON_PRESSED equ 0x0008
FROM_LEFT_4TH_BUTTON_PRESSED equ 0x0010


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


KEY_EVENT		equ 0x0001
MOUSE_EVENT		equ 0x0002
WINDOW_BUFFER_SIZE_EVENT equ 0x0004
MENU_EVENT		equ 0x0008
FOCUS_EVENT		equ 0x0010

CHAR_INFO		STRUC
UNION
 UnicodeChar		WCHAR ?
 AsciiChar		CHAR ?
ENDS
Attributes		dw ?
CHAR_INFO		ENDS
PCHAR_INFO		typedef ptr CHAR_INFO


FOREGROUND_BLUE			equ 0x0001
FOREGROUND_GREEN		equ 0x0002
FOREGROUND_RED			equ 0x0004
FOREGROUND_INTENSITY		equ 0x0008
BACKGROUND_BLUE			equ 0x0010
BACKGROUND_GREEN		equ 0x0020
BACKGROUND_RED			equ 0x0040
BACKGROUND_INTENSITY		equ 0x0080
COMMON_LVB_LEADING_BYTE		equ 0x0100
COMMON_LVB_TRAILING_BYTE	equ 0x0200
COMMON_LVB_GRID_HORIZONTAL	equ 0x0400
COMMON_LVB_GRID_LVERTICAL	equ 0x0800
COMMON_LVB_GRID_RVERTICAL	equ 0x1000
COMMON_LVB_REVERSE_VIDEO	equ 0x4000
COMMON_LVB_UNDERSCORE		equ 0x8000
COMMON_LVB_SBCSDBCS		equ 0x0300


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


;BOOL
CALLBACK(PHANDLER_ROUTINE, :DWORD)

CTRL_C_EVENT		equ 0
CTRL_BREAK_EVENT	equ 1
CTRL_CLOSE_EVENT	equ 2
CTRL_LOGOFF_EVENT	equ 5
CTRL_SHUTDOWN_EVENT	equ 6


ENABLE_PROCESSED_INPUT	equ 0x0001
ENABLE_LINE_INPUT	equ 0x0002
ENABLE_ECHO_INPUT	equ 0x0004
ENABLE_WINDOW_INPUT	equ 0x0008
ENABLE_MOUSE_INPUT	equ 0x0010


ENABLE_PROCESSED_OUTPUT equ 0x0001
ENABLE_WRAP_AT_EOL_OUTPUT equ 0x0002


;BOOL
PeekConsoleInputA proto WINAPI \
	 hConsoleInput: HANDLE,
	      lpBuffer: PINPUT_RECORD,
	       nLength: DWORD,
 lpNumberOfEventsRead : LPDWORD
PeekConsoleInputW proto WINAPI \
	 hConsoleInput: HANDLE,
	      lpBuffer: PINPUT_RECORD,
	       nLength: DWORD,
 lpNumberOfEventsRead : LPDWORD
ifdef _UNICODE
PeekConsoleInput	equ <PeekConsoleInputW>
else
PeekConsoleInput	equ <PeekConsoleInputA>
endif

;BOOL
ReadConsoleInputA proto WINAPI \
	 hConsoleInput: HANDLE,
	      lpBuffer: PINPUT_RECORD,
	       nLength: DWORD,
 lpNumberOfEventsRead : LPDWORD
ReadConsoleInputW proto WINAPI \
	 hConsoleInput: HANDLE,
	      lpBuffer: PINPUT_RECORD,
	       nLength: DWORD,
 lpNumberOfEventsRead : LPDWORD
ifdef _UNICODE
ReadConsoleInput	equ <ReadConsoleInputW>
else
ReadConsoleInput	equ <ReadConsoleInputA>
endif

;BOOL
WriteConsoleInputA proto WINAPI \
	   hConsoleInput: HANDLE,
		lpBuffer: ptr INPUT_RECORD,
		 nLength: DWORD,
 lpNumberOfEventsWritten: LPDWORD

;BOOL
WriteConsoleInputW proto WINAPI \
	   hConsoleInput: HANDLE,
		lpBuffer: ptr INPUT_RECORD,
		 nLength: DWORD,
 lpNumberOfEventsWritten: LPDWORD
ifdef _UNICODE
WriteConsoleInput	equ <WriteConsoleInputW>
else
WriteConsoleInput	equ <WriteConsoleInputA>
endif

;BOOL
ReadConsoleOutputA proto WINAPI \
	hConsoleOutput: HANDLE,
	      lpBuffer: PCHAR_INFO,
	  dwBufferSize: COORD,
	 dwBufferCoord: COORD,
	 lpReadRegion : PSMALL_RECT
ReadConsoleOutputW proto WINAPI \
	hConsoleOutput: HANDLE,
	      lpBuffer: PCHAR_INFO,
	  dwBufferSize: COORD,
	 dwBufferCoord: COORD,
	 lpReadRegion : PSMALL_RECT
ifdef _UNICODE
ReadConsoleOutput	equ <ReadConsoleOutputW>
else
ReadConsoleOutput	equ <ReadConsoleOutputA>
endif

;BOOL
WriteConsoleOutputA proto WINAPI \
	hConsoleOutput: HANDLE,
	      lpBuffer: ptr CHAR_INFO,
	  dwBufferSize: COORD,
	 dwBufferCoord: COORD,
	lpWriteRegion : PSMALL_RECT
WriteConsoleOutputW proto WINAPI \
	hConsoleOutput: HANDLE,
	      lpBuffer: ptr CHAR_INFO,
	  dwBufferSize: COORD,
	 dwBufferCoord: COORD,
	lpWriteRegion : PSMALL_RECT
ifdef _UNICODE
WriteConsoleOutput	equ <WriteConsoleOutputW>
else
WriteConsoleOutput	equ <WriteConsoleOutputA>
endif

;BOOL
ReadConsoleOutputCharacterA proto WINAPI \
	hConsoleOutput: HANDLE,
	   lpCharacter: LPSTR,
	       nLength: DWORD,
	   dwReadCoord: COORD,
  lpNumberOfCharsRead : LPDWORD
ReadConsoleOutputCharacterW proto WINAPI \
	hConsoleOutput: HANDLE,
	   lpCharacter: LPWSTR,
	       nLength: DWORD,
	   dwReadCoord: COORD,
  lpNumberOfCharsRead : LPDWORD
ifdef _UNICODE
ReadConsoleOutputCharacter equ <ReadConsoleOutputCharacterW>
else
ReadConsoleOutputCharacter equ <ReadConsoleOutputCharacterA>
endif

;BOOL
ReadConsoleOutputAttribute proto WINAPI \
	hConsoleOutput: HANDLE,
	   lpAttribute: LPWORD,
	       nLength: DWORD,
	   dwReadCoord: COORD,
  lpNumberOfAttrsRead : LPDWORD

;BOOL
WriteConsoleOutputCharacterA proto WINAPI \
	hConsoleOutput: HANDLE,
	   lpCharacter: LPCSTR,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfCharsWritten : LPDWORD
WriteConsoleOutputCharacterW proto WINAPI \
	hConsoleOutput: HANDLE,
	   lpCharacter: LPCWSTR,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfCharsWritten : LPDWORD
ifdef _UNICODE
WriteConsoleOutputCharacter equ <WriteConsoleOutputCharacterW>
else
WriteConsoleOutputCharacter equ <WriteConsoleOutputCharacterA>
endif

;BOOL
WriteConsoleOutputAttribute proto WINAPI \
	hConsoleOutput: HANDLE,
	   lpAttribute: ptr WORD,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfAttrsWritten: LPDWORD

;BOOL
FillConsoleOutputCharacterA proto WINAPI \
	hConsoleOutput: HANDLE,
	    cCharacter: DWORD,;CHAR,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfCharsWritten : LPDWORD
FillConsoleOutputCharacterW proto WINAPI \
	hConsoleOutput: HANDLE,
	    cCharacter: DWORD,;WCHAR,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfCharsWritten: LPDWORD
ifdef _UNICODE
FillConsoleOutputCharacter equ <FillConsoleOutputCharacterW>
else
FillConsoleOutputCharacter equ <FillConsoleOutputCharacterA>
endif

;BOOL
FillConsoleOutputAttribute proto WINAPI \
	hConsoleOutput: HANDLE,
	    wAttribute: WORD,
	       nLength: DWORD,
	  dwWriteCoord: COORD,
lpNumberOfAttrsWritten: LPDWORD

;BOOL
GetConsoleMode proto WINAPI \
	hConsoleHandle: HANDLE,
	       lpMode : LPDWORD

;BOOL
GetNumberOfConsoleInputEvents proto WINAPI \
	 hConsoleInput: HANDLE,
      lpNumberOfEvents: LPDWORD

;BOOL
GetConsoleScreenBufferInfo proto WINAPI \
	hConsoleOutput: HANDLE,
lpConsoleScreenBufferInfo : PCONSOLE_SCREEN_BUFFER_INFO

;COORD
GetLargestConsoleWindowSize proto WINAPI \
	hConsoleOutput: HANDLE

;BOOL
GetConsoleCursorInfo proto WINAPI \
	hConsoleOutput: HANDLE,
  lpConsoleCursorInfo : PCONSOLE_CURSOR_INFO

;BOOL
GetNumberOfConsoleMouseButtons proto WINAPI \
lpNumberOfMouseButtons: LPDWORD

;BOOL
SetConsoleMode proto WINAPI \
	hConsoleHandle: HANDLE,
	       dwMode : DWORD

;BOOL
SetConsoleActiveScreenBuffer proto WINAPI \
	hConsoleOutput: HANDLE

;BOOL
FlushConsoleInputBuffer proto WINAPI \
	 hConsoleInput: HANDLE

;BOOL
SetConsoleScreenBufferSize proto WINAPI \
	hConsoleOutput: HANDLE,
	       dwSize : COORD

;BOOL
SetConsoleCursorPosition proto WINAPI \
	hConsoleOutput: HANDLE,
     dwCursorPosition : COORD

;BOOL
SetConsoleCursorInfo proto WINAPI \
	hConsoleOutput: HANDLE,
   lpConsoleCursorInfo: ptr CONSOLE_CURSOR_INFO

;BOOL
ScrollConsoleScreenBufferA proto WINAPI \
	hConsoleOutput: HANDLE,
     lpScrollRectangle: ptr SMALL_RECT,
       lpClipRectangle: ptr SMALL_RECT,
   dwDestinationOrigin: COORD,
		lpFill: ptr SMALL_RECT

;BOOL
ScrollConsoleScreenBufferW proto WINAPI \
	hConsoleOutput: HANDLE,
     lpScrollRectangle: ptr SMALL_RECT,
       lpClipRectangle: ptr SMALL_RECT,
   dwDestinationOrigin: COORD,
		lpFill: ptr CHAR_INFO
ifdef _UNICODE
ScrollConsoleScreenBuffer equ <ScrollConsoleScreenBufferW>
else
ScrollConsoleScreenBuffer equ <ScrollConsoleScreenBufferA>
endif

;BOOL
SetConsoleWindowInfo proto WINAPI \
	hConsoleOutput: HANDLE,
	     bAbsolute: BOOL,
       lpConsoleWindow: ptr SMALL_RECT

;BOOL
SetConsoleTextAttribute proto WINAPI \
	hConsoleOutput: HANDLE,
	  wAttributes : WORD

;BOOL
SetConsoleCtrlHandler proto WINAPI \
	HandlerRoutine: PHANDLER_ROUTINE,
		  _Add: BOOL

;BOOL
GenerateConsoleCtrlEvent proto WINAPI \
	   dwCtrlEvent: DWORD,
     dwProcessGroupId : DWORD

;BOOL
AllocConsole proto WINAPI

;BOOL
FreeConsole proto WINAPI


;DWORD
GetConsoleTitleA proto WINAPI \
	lpConsoleTitle: LPSTR,
		nSize : DWORD
GetConsoleTitleW proto WINAPI \
	lpConsoleTitle: LPWSTR,
		nSize : DWORD
ifdef _UNICODE
GetConsoleTitle		equ <GetConsoleTitleW>
else
GetConsoleTitle		equ <GetConsoleTitleA>
endif

;BOOL
SetConsoleTitleA proto WINAPI \
       lpConsoleTitle : LPCSTR
SetConsoleTitleW proto WINAPI \
       lpConsoleTitle : LPCWSTR
ifdef _UNICODE
SetConsoleTitle		equ <SetConsoleTitleW>
else
SetConsoleTitle		equ <SetConsoleTitleA>
endif

;BOOL
ReadConsoleA proto WINAPI \
	 hConsoleInput: HANDLE,
	      lpBuffer: LPVOID,
  nNumberOfCharsToRead: DWORD,
   lpNumberOfCharsRead: LPDWORD,
	   lpReserved : LPVOID
ReadConsoleW proto WINAPI \
	 hConsoleInput: HANDLE,
	      lpBuffer: LPVOID,
  nNumberOfCharsToRead: DWORD,
   lpNumberOfCharsRead: LPDWORD,
	   lpReserved : LPVOID
ifdef _UNICODE
ReadConsole		equ <ReadConsoleW>
else
ReadConsole		equ <ReadConsoleA>
endif

;BOOL
WriteConsoleA proto WINAPI \
	hConsoleOutput: HANDLE,
	      lpBuffer: PVOID,
 nNumberOfCharsToWrite: DWORD,
lpNumberOfCharsWritten: LPDWORD,
	    lpReserved: LPVOID
WriteConsoleW proto WINAPI \
	hConsoleOutput: HANDLE,
	      lpBuffer: PVOID,
 nNumberOfCharsToWrite: DWORD,
lpNumberOfCharsWritten: LPDWORD,
	    lpReserved: LPVOID
ifdef _UNICODE
WriteConsole		equ <WriteConsoleW>
else
WriteConsole		equ <WriteConsoleA>
endif

CONSOLE_TEXTMODE_BUFFER equ 1

;HANDLE
CreateConsoleScreenBuffer proto WINAPI \
       dwDesiredAccess: DWORD,
	   dwShareMode: DWORD,
  lpSecurityAttributes: ptr SECURITY_ATTRIBUTES,
	       dwFlags: DWORD,
    lpScreenBufferData: LPVOID

;UINT
GetConsoleCP proto WINAPI

;BOOL
SetConsoleCP proto WINAPI \
	  wCodePageID : UINT

;UINT
GetConsoleOutputCP proto WINAPI

;BOOL
SetConsoleOutputCP proto WINAPI \
	  wCodePageID : UINT

CONSOLE_FULLSCREEN_MODE equ 1
CONSOLE_WINDOWED_MODE	equ 2

;BOOL
SetConsoleDisplayMode proto WINAPI \
	hConsoleOutput: HANDLE,
	       dwFlags: DWORD,
lpNewScreenBufferDimensions: PCOORD

.pragma list(pop)
endif
