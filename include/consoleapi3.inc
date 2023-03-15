ifndef _APISETCONSOLEL3_
define _APISETCONSOLEL3_

include apiset.inc
include apisetcconv.inc
include minwindef.inc
include minwinbase.inc

include wincontypes.inc
include windef.inc

ifndef NOGDI
include wingdi.inc
endif

if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP or WINAPI_PARTITION_SYSTEM)

GetNumberOfConsoleMouseButtons proto WINAPI :LPDWORD

if (_WIN32_WINNT ge 0x0500)

GetConsoleFontSize proto WINAPI :HANDLE, :DWORD
GetCurrentConsoleFont proto WINAPI :HANDLE, :BOOL, :PCONSOLE_FONT_INFO

ifndef NOGDI

CONSOLE_FONT_INFOEX     struct
cbSize                  ULONG ?
nFont                   DWORD ?
dwFontSize              COORD <>
FontFamily              UINT ?
FontWeight              UINT ?
FaceName                WCHAR LF_FACESIZE dup(?)
CONSOLE_FONT_INFOEX     ends
PCONSOLE_FONT_INFOEX    typedef ptr CONSOLE_FONT_INFOEX

GetCurrentConsoleFontEx proto WINAPI :HANDLE, :BOOL, :PCONSOLE_FONT_INFOEX
SetCurrentConsoleFontEx proto WINAPI :HANDLE, :BOOL, :PCONSOLE_FONT_INFOEX

endif

define CONSOLE_NO_SELECTION            0x0000
define CONSOLE_SELECTION_IN_PROGRESS   0x0001
define CONSOLE_SELECTION_NOT_EMPTY     0x0002
define CONSOLE_MOUSE_SELECTION         0x0004
define CONSOLE_MOUSE_DOWN              0x0008

CONSOLE_SELECTION_INFO  struct
dwFlags                 DWORD ?
dwSelectionAnchor       COORD <>
srSelection             SMALL_RECT <>
CONSOLE_SELECTION_INFO  ends
PCONSOLE_SELECTION_INFO typedef ptr CONSOLE_SELECTION_INFO

GetConsoleSelectionInfo proto WINAPI :PCONSOLE_SELECTION_INFO

define HISTORY_NO_DUP_FLAG 0x1

CONSOLE_HISTORY_INFO    struct
cbSize                  UINT ?
HistoryBufferSize       UINT ?
NumberOfHistoryBuffers  UINT ?
dwFlags                 DWORD ?
CONSOLE_HISTORY_INFO    ends
PCONSOLE_HISTORY_INFO   typedef ptr CONSOLE_HISTORY_INFO

GetConsoleHistoryInfo proto WINAPI :PCONSOLE_HISTORY_INFO
SetConsoleHistoryInfo proto WINAPI :PCONSOLE_HISTORY_INFO

define CONSOLE_FULLSCREEN 1
define CONSOLE_FULLSCREEN_HARDWARE 2

GetConsoleDisplayMode proto WINAPI :LPDWORD

define CONSOLE_FULLSCREEN_MODE 1
define CONSOLE_WINDOWED_MODE 2

SetConsoleDisplayMode proto WINAPI :HANDLE, :DWORD, :PCOORD
GetConsoleWindow proto WINAPI

endif

if (_WIN32_WINNT ge 0x0501)

AddConsoleAliasA proto WINAPI :LPSTR, :LPSTR, :LPSTR
AddConsoleAliasW proto WINAPI :LPWSTR, :LPWSTR, :LPWSTR
ifdef _UNICODE
define AddConsoleAlias  <AddConsoleAliasW>
else
define AddConsoleAlias  <AddConsoleAliasA>
endif

GetConsoleAliasA proto WINAPI :LPSTR, :LPSTR, :DWORD, :LPSTR
GetConsoleAliasW proto WINAPI :LPWSTR, :LPWSTR, :DWORD, :LPWSTR
ifdef _UNICODE
define GetConsoleAlias  <GetConsoleAliasW>
else
define GetConsoleAlias  <GetConsoleAliasA>
endif

GetConsoleAliasesLengthA proto WINAPI :LPSTR
GetConsoleAliasesLengthW proto WINAPI :LPWSTR
ifdef _UNICODE
define GetConsoleAliasesLength  <GetConsoleAliasesLengthW>
else
define GetConsoleAliasesLength  <GetConsoleAliasesLengthA>
endif

GetConsoleAliasExesLengthA proto WINAPI
GetConsoleAliasExesLengthW proto WINAPI
ifdef _UNICODE
define GetConsoleAliasExesLength  <GetConsoleAliasExesLengthW>
else
define GetConsoleAliasExesLength  <GetConsoleAliasExesLengthA>
endif

GetConsoleAliasesA proto WINAPI :LPSTR, :DWORD, :LPSTR
GetConsoleAliasesW proto WINAPI :LPWSTR, :DWORD, :LPWSTR
ifdef _UNICODE
define GetConsoleAliases  <GetConsoleAliasesW>
else
define GetConsoleAliases  <GetConsoleAliasesA>
endif

GetConsoleAliasExesA proto WINAPI :LPSTR, :DWORD
GetConsoleAliasExesW proto WINAPI :LPWSTR, :DWORD
ifdef _UNICODE
define GetConsoleAliasExes  <GetConsoleAliasExesW>
else
define GetConsoleAliasExes  <GetConsoleAliasExesA>
endif

endif

ExpungeConsoleCommandHistoryA proto WINAPI :LPSTR
ExpungeConsoleCommandHistoryW proto WINAPI :LPWSTR
ifdef _UNICODE
define ExpungeConsoleCommandHistory  <ExpungeConsoleCommandHistoryW>
else
define ExpungeConsoleCommandHistory  <ExpungeConsoleCommandHistoryA>
endif

SetConsoleNumberOfCommandsA proto WINAPI :DWORD, :LPSTR
SetConsoleNumberOfCommandsW proto WINAPI :DWORD, :LPWSTR
ifdef _UNICODE
define SetConsoleNumberOfCommands  <SetConsoleNumberOfCommandsW>
else
define SetConsoleNumberOfCommands  <SetConsoleNumberOfCommandsA>
endif

GetConsoleCommandHistoryLengthA proto WINAPI :LPSTR
GetConsoleCommandHistoryLengthW proto WINAPI :LPWSTR
ifdef _UNICODE
define GetConsoleCommandHistoryLength  <GetConsoleCommandHistoryLengthW>
else
define GetConsoleCommandHistoryLength  <GetConsoleCommandHistoryLengthA>
endif

GetConsoleCommandHistoryA proto WINAPI :LPSTR, :DWORD, :LPSTR
GetConsoleCommandHistoryW proto WINAPI :LPWSTR, :DWORD, :LPWSTR
ifdef _UNICODE
define GetConsoleCommandHistory  <GetConsoleCommandHistoryW>
else
define GetConsoleCommandHistory  <GetConsoleCommandHistoryA>
endif

if (_WIN32_WINNT ge 0x0501)
GetConsoleProcessList proto WINAPI :LPDWORD, :DWORD
endif

endif

endif
