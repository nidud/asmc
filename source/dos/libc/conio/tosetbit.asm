; TOSETBIT.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

tosetbitflag PROC _CType PUBLIC USES si di bx tobj:DWORD,
	count:size_t, flag:size_t, bitflag:DWORD
	les bx,tobj
	mov dx,WORD PTR bitflag
	mov si,flag
	mov cx,count
	mov ax,si
	not ax
	mov di,16
	.if cx
	    .repeat
		and es:[bx],ax
		shr dx,1
		.if CARRY?
		    or es:[bx],si
		.endif
		add bx,SIZE S_TOBJ
		dec di
		.if ZERO?
		    mov dx,WORD PTR bitflag+2
		.endif
	    .untilcxz
	.endif
	ret
tosetbitflag ENDP

	END
