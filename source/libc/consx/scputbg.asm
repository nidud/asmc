include consx.inc

	.code

scputbg PROC USES eax edx x, y, l, a
	mov	edx,a
	mov	ecx,l
	and	dl,0F0h
	.repeat
		getxya( x, y )
		and	al,0Fh
		or	al,dl
		scputa( x, y, 1, eax )
		inc	x
	.untilcxz
	ret
scputbg ENDP

	END
