; FBCOLOR.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include dos.inc
include fblk.inc

	PUBLIC	fbcolor

	.code

fbcolor PROC _CType
	.if ax & _A_SELECTED
	    mov al,at_foreground[F_Panel]
	.elseif ax & _A_UPDIR
	    mov al,at_foreground[F_Desktop]
	.elseif ax & _A_SYSTEM
	    mov al,at_foreground[F_System]
	.elseif ax & _A_HIDDEN
	    mov al,at_foreground[F_Hidden]
	.elseif ax & _A_SUBDIR
	    mov al,at_foreground[F_Subdir]
	.else
	    mov al,at_foreground[F_Files]
	.endif
	or al,at_background[B_Panel]
	ret
fbcolor ENDP

	END
