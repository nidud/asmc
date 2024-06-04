
;--- problem: invoke argument of type MT_PTR
;--- error introduced temporarily in v2.16.
;--- when fixing argument of type MT_PTR ( invoke47.asm ):
;--- if the pointer argument is within a struct, argument size
;--- calculation was wrong ( size of the whole struct was used ).

	.386
	.MODEL FLAT, stdcall

HDC typedef ptr

PAINTSTRUCT struct 
hdc			HDC		?
fErase		DWORD	?
fRestore	DWORD	?
fIncUpdate	DWORD	?
PAINTSTRUCT ends

	.code

SetBkMode proc a1:dword, a2:dword
	ret
SetBkMode endp

proc1 proc

local ps:PAINTSTRUCT

	invoke SetBkMode, ps.hdc, 0
	ret

proc1 endp

	end
