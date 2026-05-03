
;--- once more the MT_PTR problem: MT_PTR in arrays

	.286
	.model small
	option casemap:none

PNEAR typedef ptr
PFAR  typedef ptr far

	.data

arrayn1 PNEAR 2 dup (0)
arrayf1 PFAR  2 dup (0)

	.code

proc1 proc c p1:PNEAR
	ret
proc1 endp

proc2 proc c p1:PFAR
	ret
proc2 endp

start proc

local arrayn2[2]:PNEAR
local arrayf2[2]:PFAR

	invoke proc1, arrayn1[1*sizeof PNEAR]
	invoke proc1, arrayn2[1*sizeof PNEAR]
	invoke proc2, arrayf1[1*sizeof PFAR]
	invoke proc2, arrayf2[1*sizeof PFAR]
	mov ax, 4C00h
	int 21h
start endp

	end start
