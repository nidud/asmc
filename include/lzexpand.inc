ifndef _LIBC_
include libc.inc
endif
ifndef _LZEXPAND_
define _LZEXPAND_

define LZERROR_BADINHANDLE	(-1)
define LZERROR_BADOUTHANDLE	(-2)
define LZERROR_READ		(-3)
define LZERROR_WRITE		(-4)
define LZERROR_GLOBALLOC	(-5)
define LZERROR_GLOBLOCK		(-6)
define LZERROR_BADVALUE		(-7)
define LZERROR_UNKNOWNALG	(-8)

LZStart proto WINAPI
LZDone proto WINAPI
CopyLZFile proto WINAPI :SINT, :SINT
LZCopy proto WINAPI :SINT, :SINT
LZInit proto WINAPI :SINT

GetExpandedNameA proto WINAPI :LPSTR, :LPSTR
GetExpandedNameW proto WINAPI :LPWSTR, :LPWSTR
ifdef _UNICODE
define GetExpandedName <GetExpandedNameW>
else
define GetExpandedName <GetExpandedNameA>
endif

LZOpenFileA proto WINAPI :LPSTR, :LPOFSTRUCT, :WORD
LZOpenFileW proto WINAPI :LPWSTR, :LPOFSTRUCT, :WORD
ifdef _UNICODE
define LZOpenFile <LZOpenFileW>
else
define LZOpenFile <LZOpenFileA>
endif

LZSeek proto WINAPI :SINT, :LONG, :SINT
LZRead proto WINAPI :SINT, :LPSTR, :SINT
LZClose proto WINAPI :SINT

endif
