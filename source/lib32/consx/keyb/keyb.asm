include consx.inc

	.data
_shift		dd 0
keyshift	dd offset _shift
keybchar	db 0
keybscan	db 0
keybcode	db 0
keybstate	db 0
keybstack	dd MAXKEYSTACK dup(0)
keybcount	dd 0
keybmouse_x	dd 0
keybmouse_y	dd 0

	END
