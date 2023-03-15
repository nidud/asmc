ifndef _APISETCONSOLEL2_
define _APISETCONSOLEL2_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

include wincontypes.inc
include windef.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

define FOREGROUND_BLUE      0x0001
define FOREGROUND_GREEN     0x0002
define FOREGROUND_RED       0x0004
define FOREGROUND_INTENSITY 0x0008
define BACKGROUND_BLUE      0x0010
define BACKGROUND_GREEN     0x0020
define BACKGROUND_RED       0x0040
define BACKGROUND_INTENSITY 0x0080
define COMMON_LVB_LEADING_BYTE    0x0100
define COMMON_LVB_TRAILING_BYTE   0x0200
define COMMON_LVB_GRID_HORIZONTAL 0x0400
define COMMON_LVB_GRID_LVERTICAL  0x0800
define COMMON_LVB_GRID_RVERTICAL  0x1000
define COMMON_LVB_REVERSE_VIDEO   0x4000
define COMMON_LVB_UNDERSCORE      0x8000

define COMMON_LVB_SBCSDBCS        0x0300

FillConsoleOutputCharacterA proto WINAPI :HANDLE, :CHAR, :DWORD, :COORD, :LPDWORD
FillConsoleOutputCharacterW proto WINAPI :HANDLE, :WCHAR, :DWORD, :COORD, :LPDWORD
ifdef _UNICODE
define FillConsoleOutputCharacter  <FillConsoleOutputCharacterW>
else
define FillConsoleOutputCharacter  <FillConsoleOutputCharacterA>
endif

FillConsoleOutputAttribute proto WINAPI :HANDLE, :WORD, :DWORD, :COORD, :LPDWORD
GenerateConsoleCtrlEvent proto WINAPI :DWORD, :DWORD
CreateConsoleScreenBuffer proto WINAPI :DWORD, :DWORD, :ptr, :DWORD, :LPVOID
SetConsoleActiveScreenBuffer proto WINAPI :HANDLE
FlushConsoleInputBuffer proto WINAPI :HANDLE
SetConsoleCP proto WINAPI :UINT
SetConsoleOutputCP proto WINAPI :UINT

CONSOLE_CURSOR_INFO     struct
dwSize                  DWORD ?
bVisible                BOOL ?
CONSOLE_CURSOR_INFO     ends
PCONSOLE_CURSOR_INFO    typedef ptr CONSOLE_CURSOR_INFO

GetConsoleCursorInfo proto WINAPI :HANDLE, :PCONSOLE_CURSOR_INFO
SetConsoleCursorInfo proto WINAPI :HANDLE, :ptr

CONSOLE_SCREEN_BUFFER_INFO struct
dwSize                  COORD <>
dwCursorPosition        COORD <>
wAttributes             WORD ?
srWindow                SMALL_RECT <>
dwMaximumWindowSize     COORD <>
CONSOLE_SCREEN_BUFFER_INFO ends
PCONSOLE_SCREEN_BUFFER_INFO typedef ptr CONSOLE_SCREEN_BUFFER_INFO

GetConsoleScreenBufferInfo proto WINAPI :HANDLE, :PCONSOLE_SCREEN_BUFFER_INFO

CONSOLE_SCREEN_BUFFER_INFOEX struct
cbSize                  ULONG ?
dwSize                  COORD <>
dwCursorPosition        COORD <>
wAttributes             WORD ?
srWindow                SMALL_RECT <>
dwMaximumWindowSize     COORD <>
wPopupAttributes        WORD ?
bFullscreenSupported    BOOL ?
ColorTable              COLORREF 16 dup(?)
CONSOLE_SCREEN_BUFFER_INFOEX ends
PCONSOLE_SCREEN_BUFFER_INFOEX typedef ptr CONSOLE_SCREEN_BUFFER_INFOEX

GetConsoleScreenBufferInfoEx proto WINAPI :HANDLE, :PCONSOLE_SCREEN_BUFFER_INFOEX
SetConsoleScreenBufferInfoEx proto WINAPI :HANDLE, :PCONSOLE_SCREEN_BUFFER_INFOEX
SetConsoleScreenBufferSize proto WINAPI :HANDLE, :COORD
SetConsoleCursorPosition proto WINAPI :HANDLE, :COORD
GetLargestConsoleWindowSize proto WINAPI :HANDLE
SetConsoleTextAttribute proto WINAPI :HANDLE, :WORD
SetConsoleWindowInfo proto WINAPI :HANDLE, :BOOL, :ptr
WriteConsoleOutputCharacterA proto WINAPI :HANDLE, :LPCSTR, :DWORD, :COORD, :LPDWORD
WriteConsoleOutputCharacterW proto WINAPI :HANDLE, :LPCWSTR, :DWORD, :COORD, :LPDWORD
ifdef _UNICODE
define WriteConsoleOutputCharacter  <WriteConsoleOutputCharacterW>
else
define WriteConsoleOutputCharacter  <WriteConsoleOutputCharacterA>
endif

WriteConsoleOutputAttribute proto WINAPI :HANDLE, :ptr, :DWORD, :COORD, :LPDWORD
ReadConsoleOutputCharacterA proto WINAPI :HANDLE, :LPSTR, :DWORD, :COORD, :LPDWORD
ReadConsoleOutputCharacterW proto WINAPI :HANDLE, :LPWSTR, :DWORD, :COORD, :LPDWORD
ifdef _UNICODE
define ReadConsoleOutputCharacter  <ReadConsoleOutputCharacterW>
else
define ReadConsoleOutputCharacter  <ReadConsoleOutputCharacterA>
endif

ReadConsoleOutputAttribute proto WINAPI :HANDLE, :LPWORD, :DWORD, :COORD, :LPDWORD
WriteConsoleInputA proto WINAPI :HANDLE, :ptr, :DWORD, :LPDWORD
WriteConsoleInputW proto WINAPI :HANDLE, :ptr, :DWORD, :LPDWORD
ifdef _UNICODE
define WriteConsoleInput  <WriteConsoleInputW>
else
define WriteConsoleInput  <WriteConsoleInputA>
endif

ScrollConsoleScreenBufferA proto WINAPI :HANDLE, :ptr, :ptr, :COORD, :ptr
ScrollConsoleScreenBufferW proto WINAPI :HANDLE, :ptr, :ptr, :COORD, :ptr
ifdef _UNICODE
define ScrollConsoleScreenBuffer  <ScrollConsoleScreenBufferW>
else
define ScrollConsoleScreenBuffer  <ScrollConsoleScreenBufferA>
endif

WriteConsoleOutputA proto WINAPI :HANDLE, :ptr, :COORD, :COORD, :PSMALL_RECT
WriteConsoleOutputW proto WINAPI :HANDLE, :ptr, :COORD, :COORD, :PSMALL_RECT
ifdef _UNICODE
define WriteConsoleOutput  <WriteConsoleOutputW>
else
define WriteConsoleOutput  <WriteConsoleOutputA>
endif

ReadConsoleOutputA proto WINAPI :HANDLE, :PCHAR_INFO, :COORD, :COORD, :PSMALL_RECT
ReadConsoleOutputW proto WINAPI :HANDLE, :PCHAR_INFO, :COORD, :COORD, :PSMALL_RECT
ifdef _UNICODE
define ReadConsoleOutput  <ReadConsoleOutputW>
else
define ReadConsoleOutput  <ReadConsoleOutputA>
endif

GetConsoleTitleA proto WINAPI :LPSTR, :DWORD
GetConsoleTitleW proto WINAPI :LPWSTR, :DWORD
ifdef _UNICODE
define GetConsoleTitle  <GetConsoleTitleW>
else
define GetConsoleTitle  <GetConsoleTitleA>
endif

if (_WIN32_WINNT ge 0x0600)

GetConsoleOriginalTitleA proto WINAPI :LPSTR, :DWORD
GetConsoleOriginalTitleW proto WINAPI :LPWSTR, :DWORD
ifdef _UNICODE
define GetConsoleOriginalTitle  <GetConsoleOriginalTitleW>
else
define GetConsoleOriginalTitle  <GetConsoleOriginalTitleA>
endif

endif

SetConsoleTitleA proto WINAPI :LPCSTR
SetConsoleTitleW proto WINAPI :LPCWSTR
ifdef _UNICODE
define SetConsoleTitle  <SetConsoleTitleW>
else
define SetConsoleTitle  <SetConsoleTitleA>
endif

endif

endif
