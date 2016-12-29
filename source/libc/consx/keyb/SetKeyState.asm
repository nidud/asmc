include consx.inc

	.code

SetKeyState PROC USES esi edi eax
	mov	edi,keyshift
	mov	esi,[edi]
	and	esi,not 01FF030Fh
	push	VK_LSHIFT
	call	pGetKeyState
	.if	ah & 80h
		or esi,SHIFT_LEFT or SHIFT_KEYSPRESSED
	.endif
	push	VK_RSHIFT
	call	pGetKeyState
	.if	ah & 80h
		or esi,SHIFT_RIGHT or SHIFT_KEYSPRESSED
	.endif
	push	VK_LCONTROL
	call	pGetKeyState
	.if	ah & 80h
		or esi,SHIFT_CTRLLEFT
	.endif
	push	VK_RCONTROL
	call	pGetKeyState
	.if	ah & 80h
		or esi,SHIFT_CTRL
	.endif
	mov	[edi],esi
	ret
SetKeyState ENDP

	END
