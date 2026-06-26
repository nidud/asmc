
;--- fixed in v2.15:
;--- up to v2.14: strange error msg "symbol redefinition: numfifields"
;--- since v2.15: operands must be in same segment

	.model tiny

;--- define a string in .const
CStr macro text:vararg
local sym
    .const
sym db text,0
    .code
    exitm <offset sym>
endm

	.const

	.data

fifields label word
	dw CStr('Total Free Clusters: ')
	dw CStr('First Free Cluster: ')
numfifields equ ($ - offset fifields) / sizeof word

	.code

start:
    mov cx, numfifields
    ret

END start
