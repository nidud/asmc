include consx.inc

wcputxg PROTO

	.code

wcputbg PROC USES ecx ebx wp:PVOID, l, attrib
	mov	eax,attrib
	mov	ah,0Fh
	and	al,0F0h
	mov	ecx,l
	mov	ebx,wp
	call	wcputxg
	ret
wcputbg ENDP

	END
