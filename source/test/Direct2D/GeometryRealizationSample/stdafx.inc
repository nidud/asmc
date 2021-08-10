ifndef WINVER
define WINVER 0x0501
endif
ifndef _WIN32_WINNT
define _WIN32_WINNT 0x0501
endif
ifndef _WIN32_WINDOWS
define _WIN32_WINDOWS 0x0410
endif
ifndef _WIN32_IE
define _WIN32_IE 0x0600
endif
define _USE_MATH_DEFINES

include windows.inc
include stdlib.inc
include malloc.inc
include memory.inc
include wchar.inc
include math.inc
include strsafe.inc
include d2d1.inc
include d2d1helper.inc
include dwrite.inc
include wincodec.inc
include tchar.inc

option dllimport:none

include geometryrealization.inc
include ringbuffer.inc
include GeometryRealizationSample.inc
