; GETEVENT.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include keyb.inc
include mouse.inc

	.code

getevent PROC _CType PUBLIC
    getevent_loop:
	call	getkey
	jnz	getevent_end
	call	tupdate
	test	ax,ax
	jnz	getevent_esc
  ifdef __MOUSE__
	call	mousep
	jz	getevent_loop
	mov	ax,MOUSECMD
  else
	jmp	getevent_loop
  endif
    getevent_end:
	ret
    getevent_esc:
	mov	ax,KEY_ESC
	jmp	getevent_end
getevent ENDP

	END
