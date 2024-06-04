
;--- v2.17: regression in v2.16
;--- invoke generated a PUSHD in the case below

	.model small
	.x64

CStr macro text:vararg
local sym
CONST64 segment
sym db text,0
CONST64 ends
	exitm <addr sym>
endm

_TEXT64 segment use64 public 'CODE'
_TEXT64 ends
CONST64 segment use64 public 'CONST'
CONST64 ends

	.code _TEXT64

printf proc c fmt:ptr
	ret
printf endp

	invoke printf, CStr("x")
	ret

	end
