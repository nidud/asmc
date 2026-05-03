
;--- operator SIZEOF, SIZE, LENGTHOF, LENGTH
;--- for EXTERNALS

ifdef __ASMC__
option masm:on
endif
	.286
	.model small,stdcall
	.stack 100h

	includelib <operatr2.lib>

	.code

extern e1: byte
extern e2: word
extern e3: ptr ptr byte
extern e4: near
extern e5: far
extern e6: proto :dword

comm c1: byte
comm c2: byte : 3

p1 proc a1:near, a2:far

	dw sizeof e1
	dw sizeof e2
	dw sizeof e3
;	dw sizeof e4	;needs data label
;	dw sizeof e5
;	dw sizeof e6
	dw sizeof c1
	dw sizeof c2

;--- SIZE for externals was wrong before v2.05
	dw SIZE e1
	dw SIZE e2
	dw SIZE e3
	dw SIZE e4
	dw SIZE e5
	dw SIZE e6
	dw SIZE c1
	dw SIZE c2
	dw SIZE a1
	dw SIZE a2

	dw lengthof e1	;non-comm should always return 1
	dw lengthof e2
	dw lengthof e3
;	dw lengthof e4	;needs data label
;	dw lengthof e5
;	dw lengthof e6
	dw lengthof c1
	dw lengthof c2

	dw LENGTH e1 ;should always return 1
	dw LENGTH e2
	dw LENGTH e3
	dw LENGTH e4
	dw LENGTH e5
	dw LENGTH e6
	dw LENGTH c1
	dw LENGTH c2

p1 endp

start:
	mov ah,4ch
	int 21h

	END start
