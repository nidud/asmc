include consx.inc

	.code

rcopen	PROC rect:DWORD, flag:DWORD, attrib:DWORD, ttl:LPSTR, wp:LPWSTR
	.if!( flag & _D_MYBUF )
		rcalloc( rect, flag )
		mov wp,eax
		test eax,eax
		jz toend
	.endif

	rcread( rect, wp )
	mov edx,flag
	and edx,_D_CLEAR or _D_BACKG or _D_FOREG
	jz  toend

	movzx eax,rect.S_RECT.rc_row
	mul rect.S_RECT.rc_col
	mov ecx,attrib

	.switch edx
	  .case _D_CLEAR : wcputw ( wp, eax, ' ' ) : .endc
	  .case _D_COLOR : wcputa ( wp, eax, ecx ) : .endc
	  .case _D_BACKG : wcputbg( wp, eax, ecx ) : .endc
	  .case _D_FOREG : wcputfg( wp, eax, ecx ) : .endc
	  .default
		mov ch,cl
		mov cl,' '
		wcputw( wp, eax, ecx )
	.endsw
	xor eax,eax
	.if eax != ttl
		mov	al,rect.S_RECT.rc_col
		wctitle( wp, eax, ttl )
	.endif
toend:
	mov eax,wp
	test eax,eax
	ret
rcopen	ENDP

	END
