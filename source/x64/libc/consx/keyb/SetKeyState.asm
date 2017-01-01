include consx.inc

	.code

SetKeyState PROC USES rsi rdi rax
	mov	rdi,keyshift
	mov	esi,[rdi]
	and	esi,not 01FF030Fh

	GetKeyState(VK_LSHIFT)
	.if	ah & 80h
		or esi,SHIFT_LEFT or SHIFT_KEYSPRESSED
	.endif
	GetKeyState(VK_RSHIFT)
	.if	ah & 80h
		or esi,SHIFT_RIGHT or SHIFT_KEYSPRESSED
	.endif
	GetKeyState(VK_LCONTROL)
	.if	ah & 80h
		or esi,SHIFT_CTRLLEFT
	.endif
	GetKeyState(VK_RCONTROL)
	.if	ah & 80h
		or esi,SHIFT_CTRL
	.endif
	mov	[rdi],esi
	ret
SetKeyState ENDP

	END
