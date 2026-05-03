;
; v2.23 misscalculation of argument offset using cstack + stackbase:esp
;
	.386
	.model flat, stdcall
	.code

	option cstack:on
	option stackbase:esp

foo	proc uses edi a1, a2, a3:qword

	mov ecx,a1
	mov edx,a2
	mov ebx,dword ptr a3
	ret

foo	endp

bar	proc uses edi a1, a2, a3:qword

	foo(a1, a2, a3)
	foo(a1, a2, a3)

bar	endp

	END
