.xlist

_TV_USEMLINE	equ 01h
_TV_USESLINE	equ 02h
_TV_HEXVIEW	equ 04h
_TV_WRAPLINES	equ 08h
_TV_HEXOFFSET	equ 10h
_TV_HIGHCOLOR	equ 20h
_TV_BINVIEW	equ 40h
_TV_CLASSVIEW	equ 80h

IO_MEMREAD	equ 4000h	; View memory area

ifdef __CLASSVIEW__

CLVERSION	equ 0206h
CLCOUNT		equ 23

S_CLASS		STRUC
cl_name		db 28 dup(?)
cl_size		dw ?
cl_type		db ?
cl_format	db ?
S_CLASS		ENDS

TCLSIZE		equ (CLCOUNT*SIZE S_CLASS) + 6
CLFLAGS		equ _D_DOPEN or _D_ONSCR or _D_MYBUF

CLTYPE_CHAR	equ 0
CLTYPE_BYTE	equ 1
CLTYPE_WORD	equ 2
CLTYPE_DWORD	equ 3
CLTYPE_QWORD	equ 4

CLFORM_SIGNED	equ 0
CLFORM_UNSIGNED equ 1
CLFORM_HEX	equ 2
CLFORM_BINARY	equ 3

externdef	tv_clversion:		WORD
externdef	tv_classsize:		WORD
externdef	tv_classrow:		WORD
externdef	tv_class:		S_CLASS
externdef	IDD_TVClass:		DWORD
externdef	IDD_TVSaveClass:	DWORD
externdef	IDD_TVClassFormat:	DWORD
wgetfile	proto _CType :dword, :word

endif

ifdef __MEMVIEW__
tview	proto _CType :dword, :dword, :dword, :dword
else
tview	proto _CType :dword, :dword
endif

.list
