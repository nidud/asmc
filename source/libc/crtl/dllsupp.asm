include crtl.inc

PUBLIC	_except_list
PUBLIC	_fltused
PUBLIC	_ldused
PUBLIC	_8087
PUBLIC	_real87
PUBLIC	fltused_
PUBLIC	_init_387_emulator

output_formatE	PROTO
output_formatEU PROTO
externdef	output_proctab:DWORD

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
	lea	eax,output_proctab
	lea	ecx,output_formatE
	mov	[eax+4*3],ecx
	mov	[eax+4*4],ecx
	mov	[eax+4*5],ecx
	lea	ecx,output_formatEU
	mov	[eax+4*13],ecx
	mov	[eax+4*14],ecx
	ret

pragma_init	_fltinit, 20

	END
