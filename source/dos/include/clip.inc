ifndef __LIBC_INC
 include libc.inc
endif

.xlist

MAXCLIPSIZE	equ 64000

externdef	clipboard: DWORD
externdef	clipbsize: WORD

ClipboardCopy	PROTO _CType :DWORD, :WORD
ClipboardPaste	PROTO _CType
ClipboardFree	PROTO _CType

.list
