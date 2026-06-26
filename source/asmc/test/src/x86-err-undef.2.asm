
;--- v2.18: problem if the name of struct member matches the name
;--- of a stack variable ( or a procedure ):
;--- if the structured variable isn't defined, the stack variable 
;--- becomes "unknown". Worse, if a listing is to be produced, an
;--- infinite loop may be entered.

	.386
	.MODEL flat
	option casemap:none

DDS struct
dwSize dd ?
dwOfs  dd ?
DDS ends

	.data

;dds DDS <0,0>	;<--- problem: the variable isn't defined

	.code

P1 proc

local dwFirst:dword
local dwSize:dword
local dwThird:dword

	mov dwSize, 1
	mov dds.dwSize, 0
	ret

P1 endp

start:
	call P1
	ret

	end start
