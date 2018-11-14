; DLLSUPP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc

PUBLIC	_except_list
PUBLIC	_fltused
PUBLIC	_ldused
PUBLIC	_8087
PUBLIC	_real87
PUBLIC	fltused_
PUBLIC	_init_387_emulator

_except_list	equ 0		; FS:[offset]
_fltused	equ 0x9876
_ldused		equ 0x9876

	.data

_init_387_emulator label DWORD
_real87		label BYTE
_8087		label BYTE
fltused_	dd 1
_8087cw		dw 0x127F

	.code

_fltinit:
	fninit
	fwait
	fldcw	_8087cw
	ret

.pragma(init(_fltinit, 20))

	END
