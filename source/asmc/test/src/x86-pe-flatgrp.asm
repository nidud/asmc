
;--- v2.17: 64-bit segments are now automatically added to the flat group,
;--- even if this group has offset size 32. This makes offset calculations
;--- correct for -pe format if segments are mixed.

	.386
	.model flat

	.code

	dd offset main		; this is and was no problem, since _TEXT is FLAT
f64 label fword
	dd offset main64	; since _TEXT64 is now also flat, this offset is ok
	dw 8

main proc c

	jmp [f64]

main endp

	.x64

_TEXT64 segment use64 'CODE'
_TEXT64 ends

	.code _TEXT64

	db 4h dup (-1)		; make offset main64 > 0.

main64 proc
	ret
main64 endp

	end main
