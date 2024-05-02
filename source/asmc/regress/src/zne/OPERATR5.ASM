
;--- operators SIZEOF, LENGTHOF, SIZE, LENGTH, TYPE
;--- for LOCAL and LABEL

	.model small
	option casemap:none

S1 struct
	db ?,?
S1 ends

	.code

v0	label dword

v1	label S1
	S1 <>

v2	label S1
	S1 <>
	S1 <>

v3	label near

	dw sizeof v0, lengthof v0, SIZE v0, LENGTH v0
	dw sizeof v1, lengthof v1, SIZE v1, LENGTH v1
	dw sizeof v2, lengthof v2, SIZE v2, LENGTH v2

p1	proc

local lcl1:S1
local lcl2[3]:S1

	dw sizeof lcl1, lengthof lcl1, SIZE lcl1, LENGTH lcl1
	dw sizeof lcl2, lengthof lcl2, SIZE lcl2, LENGTH lcl2

p1	endp

	END
