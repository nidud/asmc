ifndef __LIBC_INC
 include libc.inc
endif

.xlist

ifndef __INC_CONIO
__INC_CONIO	EQU 1

IFDEF __PE__
option	dllimport:<msvcrt>
ENDIF

ifndef _WCHAR_T_DEFINED
_WCHAR_T_DEFINED EQU 1
WCHAR_T TYPEDEF WORD
endif

ifndef _WINT_T_DEFINED
_WINT_T_DEFINED EQU 1
WINT_T TYPEDEF WORD
endif

ifdef _CONIO_RETRO_COLORS
BLACK		equ 0
BLUE		equ 1
GREEN		equ 2
CYAN		equ 3
RED		equ 4
MAGENTA		equ 5
BROWN		equ 6
LIGHTGRAY	equ 7
DARKGRAY	equ 8
LIGHTBLUE	equ 9
LIGHTGREEN	equ 10
LIGHTCYAN	equ 11
LIGHTRED	equ 12
LIGHTMAGENTA	equ 13
YELLOW		equ 14
WHITE		equ 15
endif

_cgets		proto :LPSTR
_clreol		proto
_clrscr		proto
_cprintf	proto _CDecl :LPSTR, :VARARG
_cputs		proto :LPSTR
_cscanf		proto _CDecl :LPSTR, :VARARG
_cwprintf	proto _CDecl :LPWSTR, :VARARG
_getch		proto
_getche		proto
_gotoxy		proto :UINT, :UINT
_inp		proto :UINT
_inpw		proto :UINT
_inpd		proto :UINT
_kbhit		proto
_outp		proto :UINT, :UINT
_outpw		proto :UINT, :UINT
_outpd		proto :UINT, :ULONG
_putch		proto :UINT
_textbackground proto :UINT
_textcolor	proto :UINT
_ungetch	proto :UINT
_wherex		proto
_wherey		proto

_cputws		proto :LPWSTR
_putwch		proto :UINT ; WCHAR_T
_getwch		proto

;;;;;;;;;;;;;;; crtl

externdef hStdInput:  HANDLE
externdef hStdOutput: HANDLE
externdef hStdError:  HANDLE

;;;;;;;;;;;;;;; kernel32.dll
IFDEF __PE__
option	dllimport:<kernel32>
ENDIF

ENABLE_WINDOW_INPUT	equ 8
ENABLE_MOUSE_INPUT	equ 16

FOREGROUND_BLUE		equ 01h
FOREGROUND_GREEN	equ 02h
FOREGROUND_RED		equ 04h
FOREGROUND_INTENSITY	equ 08h
BACKGROUND_BLUE		equ 10h
BACKGROUND_GREEN	equ 20h
BACKGROUND_RED		equ 40h
BACKGROUND_INTENSITY	equ 80h

SWP_NOSIZE		equ 01h
SWP_NOACTIVATE		equ 10h
SWP_NOZORDER		equ 04h

CHAR_INFO	STRUCT
Char		dw ?
Attributes	dw ?
CHAR_INFO	ENDS
PCHAR_INFO	TYPEDEF PTR CHAR_INFO

COORD		STRUCT
x		dw ?
y		dw ?
COORD		ENDS

SMALL_RECT	STRUCT
Left		dw ?
Top		dw ?
Right		dw ?
Bottom		dw ?
SMALL_RECT	ENDS
PSMALL_RECT	TYPEDEF PTR SMALL_RECT

CONSOLE_SCREEN_BUFFER_INFO	STRUCT
dwSize				COORD <>
dwCursorPosition		COORD <>
wAttributes			dw ?
srWindow			SMALL_RECT <>
dwMaximumWindowSize		COORD <>
CONSOLE_SCREEN_BUFFER_INFO	ENDS
PCONSOLE_SCREEN_BUFFER_INFO	TYPEDEF PTR CONSOLE_SCREEN_BUFFER_INFO

CONSOLE_CURSOR_INFO	STRUCT
dwSize			dd ?
bVisible		dd ?
CONSOLE_CURSOR_INFO	ENDS
PCONSOLE_CURSOR_INFO	TYPEDEF PTR CONSOLE_CURSOR_INFO

;BOOL
FillConsoleOutputAttribute proto _CType \
	hConsoleOutput:		HANDLE, ; handle to screen buffer
	wAttribute:		DWORD,	; color attribute to write (WORD)
	nLength:		DWORD,	; number of character cells to write to
	dwWriteCoord:		COORD,	; x- and y-coordinates of first cell
	lpNumberOfAttrsWritten: LPDWORD ; pointer to number of cells written to
;BOOL
FlushConsoleInputBuffer proto _CType \
	hConsoleInput:	HANDLE	; handle to console input buffer
;BOOL
GetConsoleCursorInfo proto _CType \
	hConsoleOutput:		HANDLE, ; handle to console screen buffer
	lpConsoleCursorInfo:	PCONSOLE_CURSOR_INFO
;BOOL
GetConsoleMode proto _CType \
	hConsoleHandle: HANDLE, ; handle to console input or screen buffer
	lpMode:		LPDWORD ; current mode flags
;BOOL
GetConsoleScreenBufferInfo proto _CType \
	hConsoleOutput:	  HANDLE, ; handle to console screen buffer
	lpConsoleScreenBufferInfo:PCONSOLE_SCREEN_BUFFER_INFO ; address of screen buffer info
;HWND
GetConsoleWindow proto _CType
;HWND
GetForegroundWindow proto _CType
;COORD
GetLargestConsoleWindowSize proto _CType \
	hConsoleOutput: HANDLE	; handle to console screen buffer
;BOOL
ReadConsoleOutputAttribute proto _CType \
	hConsoleOutput:		HANDLE, ; handle to a console screen buffer
	lpAttribute:		LPWORD, ; address of buffer to receive attributes
	nLength:		DWORD,	; number of character cells to read from
	dwReadCoord:		COORD,	; coordinates of first cell to read from
	lpNumberOfAttrsRead:	LPDWORD ; address of number of cells read from
;BOOL
SetConsoleActiveScreenBuffer proto _CType \
	hConsoleOutput: HANDLE	; handle to console screen buffer
;BOOL
SetConsoleCP proto _CType \
	wCodePageID:	UINT	; code page to set
;BOOL
SetConsoleCtrlHandler proto _CType \
	HandlerRoutine: ptr,;PHANDLER_ROUTINE, ; address of handler function
	_Add:		DWORD	; handler to add or remove
;BOOL
SetConsoleCursorInfo proto _CType \
	hConsoleOutput: HANDLE, ; handle to console screen buffer
	lpConsoleCursorInfo:	PCONSOLE_CURSOR_INFO ; address of cursor information
;BOOL
SetConsoleCursorPosition proto _CType \
	hConsoleOutput:		HANDLE, ; handle to console screen buffer
	dwCursorPosition:	COORD	; new cursor position coordinates
;BOOL
SetConsoleMode proto _CType \
	hConsoleHandle: HANDLE, ; handle to console input or screen buffer
	dwMode:		DWORD	; input or output mode to set
;BOOL
SetConsoleOutputCP proto _CType \
	wCodePageID:	UINT	; code page to set
;BOOL
SetConsoleScreenBufferSize proto _CType \
	hConsoleOutput: HANDLE, ; handle to console screen buffer
	dwSize:		COORD	; new size in character rows and cols.
;BOOL
SetConsoleTextAttribute proto _CType \
	hConsoleOutput: HANDLE, ; handle to console screen buffer
	wAttributes:	DWORD	; (WORD) text and background colors
;BOOL
SetConsoleWindowInfo proto _CType \
	hConsoleOutput:		HANDLE, ; handle to console screen buffer
	bAbsolute:		DWORD,	; (BOOL) coordinate type flag
	lpConsoleWindow:	PTR SMALL_RECT ; address of new window rectangle
;BOOL
SetWindowPos proto _CType \
	hWnd:		HANDLE, ; HWND
	hWndInsertAfter:HANDLE, ; HWND
	X:		UINT,
	Y:		UINT,
	_cx:		UINT,
	_cy:		UINT,
	uFlags:		UINT
;BOOL
WriteConsoleA proto _CType \
	hConsoleOutput:		HANDLE,
	lpBuffer:		PVOID,
	nNumberOfCharsToWrite:	DWORD,
	lpNumberOfCharsWritten: LPDWORD,
	lpReserved:		PVOID
WriteConsoleW proto _CType	:HANDLE, :PVOID, :DWORD, :LPDWORD, :PVOID
;BOOL
WriteConsoleOutputAttribute proto _CType \
	hConsoleOutput:		HANDLE, ; handle to a console screen buffer
	lpAttribute:		PTR WORD,; pointer to buffer to write attributes from
	nLength:		DWORD,	; number of character cells to write to
	wWriteCoord:		COORD,	; coordinates of first cell to write to
	lpNumberOfAttrsWritten: LPDWORD ; pointer to number of cells written to
;BOOL
FillConsoleOutputCharacterA proto _CType \
	hConsoleOutput:		HANDLE, ; handle to screen buffer
	cCharacter:		DWORD,	; (TCHAR) character to write
	nLength:		DWORD,	; number of character cells to write to
	dwWriteCoord:		COORD,	; x- and y-coordinates of first cell
	lpNumberOfCharsWritten: LPDWORD ; pointer to number of cells written to
FillConsoleOutputCharacterW proto _CType :HANDLE, :DWORD, :DWORD, :COORD, :LPDWORD
;BOOL
ReadConsoleOutputA proto _CType \
	hConsoleOutput: HANDLE,		; handle to a console screen buffer
	lpBuffer:	PCHAR_INFO,	; address of buffer that receives data
	dwBufferSize:	COORD,		; column-row size of destination buffer
	dwBufferCoord:	COORD,		; upper-left cell to write to
	lpReadRegion:	PSMALL_RECT	; address of rectangle to read from
ReadConsoleOutputW proto _CType :HANDLE, :PCHAR_INFO, :COORD, :COORD, :PSMALL_RECT
;BOOL
ReadConsoleOutputCharacterA proto _CType \
	hConsoleOutput:		HANDLE, ; handle to a console screen buffer
	lpCharacter:		LPSTR,	; address of buffer to receive characters
	nLength:		DWORD,	; number of character cells to read from
	dwReadCoord:		COORD,	; coordinates of first cell to read from
	lpNumberOfCharsRead:	LPDWORD ; address of number of cells read from
ReadConsoleOutputCharacterW proto _CType :HANDLE, :LPWSTR, :DWORD, :COORD, :LPDWORD
;BOOL
SetConsoleTitleA proto _CType \
	lpConsoleTitle: LPSTR	; address of new title
SetConsoleTitleW proto _CType :LPWSTR
;BOOL
WriteConsoleOutputA proto _CType \
	hConsoleOutput: HANDLE,		; handle to a console screen buffer
	lpBuffer:	PCHAR_INFO,	; pointer to buffer with data to write
	dwBufferSize:	COORD,		; column-row size of source buffer
	dwBufferCoord:	COORD,		; upper-left cell to write from
	lpWriteRegion:	PSMALL_RECT	; pointer to rectangle to write to
WriteConsoleOutputW proto _CType :HANDLE, :PCHAR_INFO, :COORD, :COORD, :PSMALL_RECT
;BOOL
WriteConsoleOutputCharacterA proto _CType \
	hConsoleOutput:		HANDLE, ; handle to a console screen buffer
	lpCharacter:		LPSTR,	; pointer to buffer to write characters from
	nLength:		DWORD,	; number of character cells to write to
	dwWriteCoord:		COORD,	; coordinates of first cell to write to
	lpNumberOfCharsWritten: LPDWORD ; pointer to number of cells written to
WriteConsoleOutputCharacterW proto _CType :HANDLE, :LPWSTR, :DWORD, :COORD, :LPDWORD

ifdef __W95__
 externdef pGetForegroundWindow:dword
 externdef pGetConsoleWindow:dword
 externdef pSetWindowPos:dword
else
 pGetForegroundWindow		equ <GetForegroundWindow>
 pGetConsoleWindow		equ <GetConsoleWindow>
 pSetWindowPos			equ <SetWindowPos>
endif

ifdef _UNICODE
 FillConsoleOutputCharacter	equ <FillConsoleOutputCharacterW>
 ReadConsoleOutput		equ <ReadConsoleOutputW>
 ReadConsoleOutputCharacter	equ <ReadConsoleOutputCharacterW>
 SetConsoleTitle		equ <SetConsoleTitleW>
 WriteConsole			equ <WriteConsoleW>
 WriteConsoleOutput		equ <WriteConsoleOutputW>
 WriteConsoleOutputCharacter	equ <WriteConsoleOutputCharacterW>
else
 FillConsoleOutputCharacter	equ <FillConsoleOutputCharacterA>
 ReadConsoleOutput		equ <ReadConsoleOutputA>
 ReadConsoleOutputCharacter	equ <ReadConsoleOutputCharacterA>
 SetConsoleTitle		equ <SetConsoleTitleA>
 WriteConsole			equ <WriteConsoleA>
 WriteConsoleOutput		equ <WriteConsoleOutputA>
 WriteConsoleOutputCharacter	equ <WriteConsoleOutputCharacterA>
endif

MAPVK_VK_TO_VSC		equ 0
MAPVK_VSC_TO_VK		equ 1

KEY_EVENT		equ 1
MOUSE_EVENT		equ 2
MAXINPUTRECORDS		equ 100

KEY_EVENT_RECORD	STRUCT
bKeyDown		dd ?
wRepeatCount		dw ?
wVirtualKeyCode		dw ?
wVirtualScanCode	dw ?
Char			dw ?
dwControlKeyState	dd ?
KEY_EVENT_RECORD	ENDS

MOUSE_EVENT_RECORD	STRUCT
dwMousePosition		COORD <>
dwButtonState		dd ?
dwControlKeyState	dd ?
dwEventFlags		dd ?
MOUSE_EVENT_RECORD	ENDS

WINDOW_BUFFER_SIZE_RECORD STRUCT
dwSize			COORD <>
WINDOW_BUFFER_SIZE_RECORD ENDS

MENU_EVENT_RECORD	STRUCT
dwCommandId		dd ?
MENU_EVENT_RECORD	ENDS

FOCUS_EVENT_RECORD	STRUCT
bSetFocus		dd ?
FOCUS_EVENT_RECORD	ENDS

INPUT_RECORD		STRUCT
EventType		dw ?
two_byte_alignment	dw ?
UNION
  KeyEvent		KEY_EVENT_RECORD <>
  MouseEvent		MOUSE_EVENT_RECORD <>
  WindowBufferSizeEvent WINDOW_BUFFER_SIZE_RECORD <>
  MenuEvent		MENU_EVENT_RECORD <>
  FocusEvent		FOCUS_EVENT_RECORD <>
ENDS
INPUT_RECORD		ENDS
PINPUT_RECORD		TYPEDEF PTR INPUT_RECORD

; BOOL
GetNumberOfConsoleInputEvents proto _CType \
	hConsoleInput:		HANDLE, ; handle to console input buffer
	lpcNumberOfEvents:	LPDWORD ; address for number of events
; BOOL
ReadConsoleInputA proto _CType \
	hConsoleInput:		HANDLE,		; handle to a console input buffer
	lpBuffer:		PINPUT_RECORD,	; address of the buffer for read data
	nLength:		DWORD,		; number of records to read
	lpNumberOfEventsRead:	LPDWORD		; address of number of records read
ReadConsoleInputW proto _CType :HANDLE, :PINPUT_RECORD, :DWORD, :LPDWORD
; BOOL
PeekConsoleInputA proto _CType \
	hConsoleInput:		HANDLE,		; handle to a console input buffer
	lpBuffer:		PINPUT_RECORD,	; pointer to the buffer for peek data
	nLength:		DWORD,		; number of records to read
	lpNumberOfEventsRead:	LPDWORD		; pointer to number of records read
PeekConsoleInputW proto _CType :HANDLE, :PINPUT_RECORD, :DWORD, :LPDWORD
; BOOL
WriteConsoleInputA proto _CType \
	hConsoleInput:		HANDLE,		; handle to a console input buffer
	lpBuffer:		PINPUT_RECORD,	; pointer to the buffer for write data
	nLength:		DWORD,		; number of records to write
	lpNumberOfEventsWritten:LPDWORD		; pointer to number of records written
WriteConsoleInputW proto _CType :HANDLE, :PINPUT_RECORD, :DWORD, :LPDWORD

ifdef __W95__
 externdef pGetKeyState:dword
else
 pGetKeyState equ <GetKeyState>
endif

;;;;;;;;;;;;;;; user32.dll
IFDEF __PE__
option	dllimport:<user32>
ENDIF

VK_LSHIFT	equ 0xA0
VK_RSHIFT	equ 0xA1
VK_LCONTROL	equ 0xA2
VK_RCONTROL	equ 0xA3
VK_ESCAPE	equ 0x1B

; SHORT
GetAsyncKeyState proto _CType \
	vKey:		SINT
; SHORT
GetKeyState proto _CType \
	nVirtKey:	SINT
;UINT
MapVirtualKeyA proto _CType \
	uCode:		UINT,
	uMapType:	UINT
MapVirtualKeyW proto _CType :UINT, :UINT

ifdef _UNICODE
 ReadConsoleInput	equ <ReadConsoleInputW>
 PeekConsoleInput	equ <PeekConsoleInputW>
 WriteConsoleInput	equ <WriteConsoleInputW>
 MapVirtualKey		equ <MapVirtualKeyW>
else
 ReadConsoleInput	equ <ReadConsoleInputA>
 PeekConsoleInput	equ <PeekConsoleInputA>
 WriteConsoleInput	equ <WriteConsoleInputA>
 MapVirtualKey		equ <MapVirtualKeyA>
endif
endif	; __INC_CONIO

.list
