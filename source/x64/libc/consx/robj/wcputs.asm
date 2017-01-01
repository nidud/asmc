include consx.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

wcputs	PROC USES rsi rdi p:PVOID, l, max, string:LPSTR
	mov	rdi,rcx
	movzx	rdx,dl
	add	rdx,rdx
	movzx	rcx,r8w
	mov	ah,ch
	mov	ch,[rdi+1]
	and	ch,0F0h
	.if	ch == at_background[B_Menus]
		or	ch,at_foreground[F_MenusKey]
	.elseif ch == at_background[B_Dialog]
		or	ch,at_foreground[F_DialogKey]
	.else
		xor	ch,ch
	.endif
	mov	rsi,r9
	call	__wputs
	ret
wcputs	ENDP

	END
