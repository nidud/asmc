include consx.inc
include stdio.inc

	.data

scancode label byte
	db 02h,03h,04h,05h,06h,07h,08h,09h,0Ah,0Bh ; 1..0
	db 3Bh,3Ch,3Dh,3Eh,3Fh,40h,41h,42h,43h,44h ; F1..F10
	db 47h	; HOME
	db 48h	; UP
	db 49h	; PGUP
	db 4Bh	; LEFT
	db 4Dh	; RIGHT
	db 4Fh	; END
	db 50h	; DOWN
	db 51h	; PGDN
	db 52h	; INS
	db 53h	; DEL
	db 0Fh	; Ctrl-Tab 0F00 --> 9400
	db 85h	; F11
	db 86h	; F12
	db 0
scanshift label byte
	db 02h,03h,04h,05h,06h,07h,08h,09h,0Ah,0Bh
	db 54h,55h,56h,57h,58h,59h,5Ah,5Bh,5Ch,5Dh
	db 47h,48h,49h,4Bh,4Dh,4Fh,50h,51h,52h,53h
	db 0Fh,9Eh,9Fh
scanctrl label byte
	db 02h,03h,04h,05h,06h,07h,08h,09h,0Ah,0Bh
	db 5Eh,5Fh,60h,61h,62h,63h,64h,65h,66h,67h
	db 77h,8Dh,84h,73h,74h,75h,91h,76h,92h,93h
	db 94h,0A8h,0A9h
scanalt label byte
	db 78h,79h,7Ah,7Bh,7Ch,7Dh,7Eh,7Fh,80h,81h
	db 68h,69h,6Ah,6Bh,6Ch,6Dh,6Eh,6Fh,70h,71h
	db 47h,98h,49h,9Bh,9Dh,4Fh,0A0h,51h,52h,53h
	db 0Fh,0B2h,0B3h

	.code

parseshift:
	push	esi
	mov	esi,offset scancode
@@:
	lodsb
	test	al,al
	jz	@F
	cmp	ah,al
	jne	@B
	sub	esi,offset scancode
	mov	ah,[esi+edx-1]
	mov	al,0
@@:
	pop	esi
	ret

	ASSUME	ebx:ptr INPUT_RECORD

ReadEvent PROC USES ebx edi esi ecx

local	Count:dword,
	Event:INPUT_RECORD

	xor edi,edi
	lea ebx,Event

	.if GetNumberOfConsoleInputEvents( hStdInput, addr Count )

		mov	esi,Count
		.while	esi

			ReadConsoleInput( hStdInput, ebx, 1, addr Count )
			.break .if !Count

			movzx eax,[ebx].EventType
			.if eax == KEY_EVENT

				.if UpdateKeyEvent( ebx )

					mov edi,eax
				.endif
			.elseif eax == MOUSE_EVENT

				UpdateMouseEvent( ebx )
			.endif
			dec esi
		.endw
	.endif

	mov eax,keyshift
	mov edx,[eax]
	mov eax,edi
	.if edx & SHIFT_ALTLEFT
		mov al,0
	.endif

	.if ah && !al
		.if edx & SHIFT_RIGHT or SHIFT_LEFT
			mov edx,offset scanshift
			parseshift()
		.elseif edx & SHIFT_CTRL or SHIFT_CTRLLEFT
			mov edx,offset scanctrl
			parseshift()
		.elseif edx & SHIFT_ALT or SHIFT_ALTLEFT
			mov edx,offset scanalt
			parseshift()
		.endif
	.elseif ah
		.if edx & SHIFT_ALT or SHIFT_ALTLEFT
			mov ah,0
		.endif
	.endif

	.if eax
		PushEvent(eax)
	.endif
	ret

ReadEvent ENDP

	END
