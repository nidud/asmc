ifndef _WINCON_
define _WINCON_
.pragma list(push, 0)

include winapifamily.inc
include wincontypes.inc

.pragma pack(push, size_t)

ifndef NOGDI
include wingdi.inc
endif

ifndef NOAPISET
.pragma comment(lib, kernel32)
include consoleapi.inc
include consoleapi2.inc
include consoleapi3.inc
endif

.pragma pack(pop)

define CONSOLE_REAL_OUTPUT_HANDLE (-2)
define CONSOLE_REAL_INPUT_HANDLE  (-3)
define CONSOLE_TEXTMODE_BUFFER  1

.pragma list(pop)
endif

