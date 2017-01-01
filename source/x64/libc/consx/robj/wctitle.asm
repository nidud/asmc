include consx.inc

	.code

wctitle PROC p:PVOID, l, string:LPSTR
	mov	al,' '
	mov	ah,at_background[B_Title]
	or	ah,at_foreground[F_Title]
	wcputw( rcx, edx, eax )
	wcenter( p, l, string )
	ret
wctitle ENDP

	END
