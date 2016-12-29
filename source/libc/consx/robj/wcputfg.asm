include consx.inc

wcputxg PROTO

	.code

wcputfg PROC USES ecx ebx wp:PVOID, l, attrib
	mov	eax,attrib
	mov	ah,70h
	and	al,0Fh
	mov	ecx,l
	mov	ebx,wp
	call	wcputxg
	ret
wcputfg ENDP

	END
