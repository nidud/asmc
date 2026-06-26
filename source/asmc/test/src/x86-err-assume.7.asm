
;--- v2.19: emit error "cannot use 16-bit register with a 32-bit address"
;--- if assumed register is flat; this is masm-compatible.

	.386
	assume ss:flat

_TEXT16 segment use16 word public 'CODE'
	mov [bx+2],ax   ;no error, since DS isn't assumed
	mov [bp+2],ax
_TEXT16 ends

_TEXT segment use32 dword public 'CODE'
	mov [bx+2],ax   ;no error, since DS isn't assumed
	mov [bp+2],ax
_TEXT ends

    END
