ifndef _APISETCONSOLE_
define _APISETCONSOLE_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc
include wincontypes.inc

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

AllocConsole proto WINAPI
FreeConsole proto WINAPI

if (_WIN32_WINNT ge 0x0500)
AttachConsole proto WINAPI :DWORD
define ATTACH_PARENT_PROCESS (-1)
endif

GetConsoleCP proto WINAPI
GetConsoleOutputCP proto WINAPI

define ENABLE_PROCESSED_INPUT              0x0001
define ENABLE_LINE_INPUT                   0x0002
define ENABLE_ECHO_INPUT                   0x0004
define ENABLE_WINDOW_INPUT                 0x0008
define ENABLE_MOUSE_INPUT                  0x0010
define ENABLE_INSERT_MODE                  0x0020
define ENABLE_QUICK_EDIT_MODE              0x0040
define ENABLE_EXTENDED_FLAGS               0x0080
define ENABLE_AUTO_POSITION                0x0100
define ENABLE_VIRTUAL_TERMINAL_INPUT       0x0200

define ENABLE_PROCESSED_OUTPUT             0x0001
define ENABLE_WRAP_AT_EOL_OUTPUT           0x0002
define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
define DISABLE_NEWLINE_AUTO_RETURN         0x0008
define ENABLE_LVB_GRID_WORLDWIDE           0x0010

GetConsoleMode proto WINAPI :HANDLE, :LPDWORD
SetConsoleMode proto WINAPI :HANDLE, :DWORD
GetNumberOfConsoleInputEvents proto WINAPI :HANDLE, :LPDWORD
ReadConsoleInputA proto WINAPI :HANDLE, :PINPUT_RECORD, :DWORD, :LPDWORD
ReadConsoleInputW proto WINAPI :HANDLE, :PINPUT_RECORD, :DWORD, :LPDWORD
ifdef _UNICODE
define ReadConsoleInput  <ReadConsoleInputW>
else
define ReadConsoleInput  <ReadConsoleInputA>
endif

PeekConsoleInputA proto WINAPI :HANDLE, :PINPUT_RECORD, :DWORD, :LPDWORD
PeekConsoleInputW proto WINAPI :HANDLE, :PINPUT_RECORD, :DWORD, :LPDWORD
ifdef _UNICODE
define PeekConsoleInput  <PeekConsoleInputW>
else
define PeekConsoleInput  <PeekConsoleInputA>
endif

CONSOLE_READCONSOLE_CONTROL struct
nLength                 ULONG ?
nInitialChars           ULONG ?
dwCtrlWakeupMask        ULONG ?
dwControlKeyState       ULONG ?
CONSOLE_READCONSOLE_CONTROL ends
PCONSOLE_READCONSOLE_CONTROL typedef ptr CONSOLE_READCONSOLE_CONTROL

ReadConsoleA proto WINAPI :HANDLE, :ptr, :DWORD, :LPDWORD, :PCONSOLE_READCONSOLE_CONTROL
ReadConsoleW proto WINAPI :HANDLE, :ptr, :DWORD, :LPDWORD, :PCONSOLE_READCONSOLE_CONTROL
ifdef _UNICODE
define ReadConsole  <ReadConsoleW>
else
define ReadConsole  <ReadConsoleA>
endif

WriteConsoleA proto WINAPI :HANDLE, :ptr, :DWORD, :LPDWORD, :ptr
WriteConsoleW proto WINAPI :HANDLE, :ptr, :DWORD, :LPDWORD, :ptr
ifdef _UNICODE
define WriteConsole  <WriteConsoleW>
else
define WriteConsole  <WriteConsoleA>
endif

define CTRL_C_EVENT        0
define CTRL_BREAK_EVENT    1
define CTRL_CLOSE_EVENT    2
define CTRL_LOGOFF_EVENT   5
define CTRL_SHUTDOWN_EVENT 6

CALLBACK(PHANDLER_ROUTINE, :DWORD)

SetConsoleCtrlHandler proto WINAPI :PHANDLER_ROUTINE, :BOOL

endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP or WINAPI_PARTITION_SYSTEM)
if (NTDDI_VERSION ge NTDDI_WIN10_RS5)
define PSEUDOCONSOLE_INHERIT_CURSOR (0x1)

CreatePseudoConsole proto WINAPI :COORD, :HANDLE, :HANDLE, :DWORD, :ptr
ResizePseudoConsole proto WINAPI :HPCON, :COORD
ClosePseudoConsole proto WINAPI :HPCON

endif
endif

endif
