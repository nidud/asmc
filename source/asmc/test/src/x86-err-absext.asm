ifdef __ASMC__
option masm:on
endif

;--- "absolute" externals

	.286
	.model small

externdef E1:abs

	.code

	mov ax, seg E1		;is to fail
	mov ax, offset E1
	mov ax, LOW E1
	mov ax, HIGH E1
	mov ax, lowword E1
	mov ax, highword E1	;is to fail
	mov ax, TYPE E1
	mov ax, opattr E1
	mov ax, .TYPE E1

	mov ax, LENGTH E1
	mov ax, SIZE E1
	mov ax, lengthof E1	;jwasm rejects
	mov ax, sizeof E1	;jwasm rejects

	end
