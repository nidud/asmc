include consx.inc

DOUBLE_CLICK	equ 2
MOUSE_WHEELED	equ 4
MOUSE_HWHEELED	equ 8

	.code

	ASSUME	rbx:ptr INPUT_RECORD

UpdateMouseEvent PROC USES rbx pInput:ptr INPUT_RECORD
	mov	rbx,pInput
	movzx	eax,[rbx].MouseEvent.dwMousePosition.x
	mov	keybmouse_x,eax
	mov	ax,[rbx].MouseEvent.dwMousePosition.y
	mov	keybmouse_y,eax
	mov	rax,keyshift
	mov	edx,[rax]
	and	edx,not SHIFT_MOUSEFLAGS
	mov	eax,[rbx].MouseEvent.dwButtonState
	mov	ecx,eax
	and	eax,3h
	shl	eax,16
	or	eax,edx
	mov	edx,[rbx].MouseEvent.dwEventFlags
	mov	ebx,eax
	cmp	edx,MOUSE_WHEELED
	jne	toend
	mov	eax,KEY_MOUSEUP
	cmp	ecx,0
	jg	@F
	mov	eax,KEY_MOUSEDN
@@:
	PushEvent( eax )
toend:
	mov	rdx,keyshift
	mov	[rdx],ebx
	ret
UpdateMouseEvent ENDP

	END
