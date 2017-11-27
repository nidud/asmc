.xlist

CFREADONY	equ 0001h
CFSYSTEM	equ 0002h
CFDIRECTORY	equ 0004h
CFSELECTED	equ 0008h
CFDELETEALL	equ 0010h

externdef	confirmflag:WORD

confirm_continue	PROTO _CType :PTR BYTE
confirm_delete		PROTO _CType :PTR BYTE, :WORD
confirm_delete_file	PROTO _CType :PTR BYTE, :WORD
confirm_delete_sub	PROTO _CType :PTR BYTE

.list

