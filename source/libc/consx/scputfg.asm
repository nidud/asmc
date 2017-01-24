include consx.inc

	.code

scputfg PROC USES eax ecx edx x, y, l, a
	mov	edx,a
	mov	ecx,l
	and	dl,0Fh
	.repeat
		getxya( x, y )
		and	al,0F0h
		or	al,dl
		scputa( x, y, 1, eax )
		inc	x
	.untilcxz
	ret
scputfg ENDP

	END
