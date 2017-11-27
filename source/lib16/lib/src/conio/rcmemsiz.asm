; RCMEMSIZ.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

.code

rcmemsize PROC _CType PUBLIC USES dx rc:DWORD, dflag:size_t
	mov ax,WORD PTR rc+2
	mov dx,ax
	mul ah
	add ax,ax
	.if BYTE PTR dflag & _D_SHADE
	    add dl,dh
	    add dl,dh
	    mov dh,0
	    sub dx,2
	    add ax,dx
	.endif
	ret
rcmemsize ENDP

	END
