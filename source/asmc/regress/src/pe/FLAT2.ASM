
;--- v2.19: in flat model, variables in 16-bit segments
;--- should be accessible directly ( Masm compatible ).
;--- Previously, this wasn't possible, since 16-bit segments
;--- are NOT part of FLAT group and hence image base wasn't added
;--- to dir32 fixups.

	.386
	.model flat

	.data

v1	dd 12345678h

_DATA$16 segment use16 byte public 'DATA'

rmcb dd 0

_DATA$16 ends

	.code

_start:
	MOV  AH,4Ch
	INT  21h

	mov esi, offset rmcb
	mov [rmcb], edx
	mov edx, [rmcb]
	ret
	END _start
