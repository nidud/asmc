.xlist

MAXHIT	  equ 999

S_SBLK	  STRUC
sb_flag	  DW ?
sb_size	  DW ?
sb_line	  DW ?
sb_offs	  DD ?
sb_file	  DB 2 dup(?)
S_SBLK	  ENDS

INFOSIZE  equ 38
BLOCKSIZE equ SIZE S_SBLK + INFOSIZE

;externdef DLG_FindFile:DWORD
;externdef FCB_FindFile:WORD

ifndef __TVEXE__
FindFile  PROTO _CType :dword, :word
endif

.list
