; DLLEVENT.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

dllevent PROC _CType PUBLIC ldlg:DWORD, listp:DWORD
local	prevlst:DWORD
	movmx	prevlst,tdllist
	movmx	tdllist,listp
	invoke	dlevent,ldlg
	mov	dx,ax
	movmx	tdllist,prevlst
	mov	ax,dx
	ret
dllevent ENDP

	END
