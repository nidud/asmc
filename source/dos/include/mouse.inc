ifndef __LIBC_INC
 include libc.inc
endif

.xlist

MOUSECMD	equ -1
KEY_MSLEFT	equ  1
KEY_MSRIGTH	equ  2
KEY_MOUSEPRESS	equ  KEY_MSLEFT or KEY_MSRIGTH

mousehide	PROTO _CType
mouseshow	PROTO _CType
mouseset	PROTO _CType
mouseget	PROTO _CType
mouseon		PROTO _CType
mouseoff	PROTO _CType
mousep		PROTO _CType
mousey		PROTO _CType
mousex		PROTO _CType
msloop		PROTO _CType
mousewait	PROTO _CType :WORD, :WORD, :WORD

HideMouseCursor macro
ifdef __MOUSE__
    call mousehide
endif
    endm

ShowMouseCursor macro
ifdef __MOUSE__
    call mouseshow
endif
    endm

.list
