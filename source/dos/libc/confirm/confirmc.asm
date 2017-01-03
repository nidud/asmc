; CONFIRMC.ASM--
; Copyright (C) 2015 Doszip Developers
include conio.inc

extrn IDD_ConfirmContinue:DWORD

	.code

confirm_continue PROC _CType PUBLIC msg:PTR BYTE
  local dialog:DWORD
	.if rsopen(IDD_ConfirmContinue)
	    stom dialog
	    invoke dlshow,dx::ax
	    lodm msg
	    .if ax
		push bx
		les bx,dialog
		mov cl,es:[bx][5]
		mov bl,es:[bx][4]
		add cl,02h
		add bl,04h
		invoke scpath,bx,cx,34,dx::ax
		pop bx
	    .endif
	    invoke dlmodal,dialog
	.endif
	ret
confirm_continue ENDP

	END
