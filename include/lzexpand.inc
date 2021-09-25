ifndef __LIBC_INC
 include libc.inc
endif
ifndef _LZEXPAND_
define _LZEXPAND_

LZERROR_BADINHANDLE	equ -1
LZERROR_BADOUTHANDLE	equ -2
LZERROR_READ		equ -3
LZERROR_WRITE		equ -4
LZERROR_GLOBALLOC	equ -5
LZERROR_GLOBLOCK	equ -6
LZERROR_BADVALUE	equ -7
LZERROR_UNKNOWNALG	equ -8

;INT
LZStart proto WINAPI
;VOID
LZDone proto WINAPI
;LONG
CopyLZFile proto WINAPI :SINT, :SINT
;LONG
LZCopy proto WINAPI :SINT, :SINT
;INT
LZInit proto WINAPI :SINT

;INT
GetExpandedNameA proto WINAPI :LPSTR, :LPSTR
GetExpandedNameW proto WINAPI :LPWSTR, :LPWSTR
ifdef _UNICODE
GetExpandedName equ <GetExpandedNameW>
else
GetExpandedName equ <GetExpandedNameA>
endif

;INT
LZOpenFileA proto WINAPI :LPSTR, :LPOFSTRUCT, :WORD
LZOpenFileW proto WINAPI :LPWSTR, :LPOFSTRUCT, :WORD
ifdef _UNICODE
LZOpenFile equ <LZOpenFileW>
else
LZOpenFile equ <LZOpenFileA>
endif

;LONG
LZSeek proto WINAPI :SINT, :LONG, :SINT
;INT
LZRead proto WINAPI :SINT, :LPSTR, :SINT
;VOID
LZClose proto WINAPI :SINT

endif
