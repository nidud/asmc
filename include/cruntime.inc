.pragma list(push, 0)
include libc.inc
ifndef _CRTBLD
.err <Use of runtime library internal header file.>
endif
if defined (_SYSCRT) AND defined (_WIN64)
define _USE_OLD_STDCPP 1
endif
if defined (_M_X64) OR defined (_M_ARM)
elseifdef _M_IX86
else
.err <Unknown target architecture.>
endif
.pragma list(pop)
