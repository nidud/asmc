ifndef __LIBC_INC
 include libc.inc
endif

.xlist

.enum
  CONFIRM_CANCEL,
  CONFIRM_DELETE,
  CONFIRM_DELETEALL,
  CONFIRM_JUMP

CFREADONY	equ 0001h
CFSYSTEM	equ 0002h
CFDIRECTORY	equ 0004h
CFSELECTED	equ 0008h
CFDELETEALL	equ 0010h

externdef	confirmflag:DWORD

confirm_continue	PROTO :DWORD
confirm_delete		PROTO :LPSTR, :DWORD
confirm_delete_file	PROTO :LPSTR, :DWORD
confirm_delete_sub	PROTO :LPSTR

.list

