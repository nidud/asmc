
;--- v2.17: comm var access with a type information
;--- didn't work until v2.17, because the type wasn't stored in the symbol.

	.386
	.model small
	option casemap:none

SIMPLESTR struct
dwSize		dd ?
dwInfo		dd ?
wFlat		dw ?
wRunMode	dw ?
SIMPLESTR ends

comm c var1:SIMPLESTR

	.code

	mov ds, cs:[var1.wFlat]
	ret

	end

