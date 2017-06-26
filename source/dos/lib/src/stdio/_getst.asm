; _GETST.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

lastiob equ (offset _iob + (_NSTREAM_ * (SIZE S_FILE)))

	.code

_getst	PROC _CType PUBLIC USES bx
	mov bx,offset _iob
	mov dx,0
	.repeat
	   xor ax,ax
	   .if !([bx].S_FILE.iob_flag & _IOREAD or _IOWRT or _IORW)
		mov  [bx].S_FILE.iob_cnt,ax
		mov  [bx].S_FILE.iob_flag,ax
		stom [bx].S_FILE.iob_bp
		stom [bx].S_FILE.iob_base
		dec  ax
		mov  [bx].S_FILE.iob_file,ax
		mov  ax,bx
		mov dx,ds
		.break
	    .endif
	    add bx,SIZE S_FILE
	.until bx == lastiob
	ret
_getst	ENDP

	END
