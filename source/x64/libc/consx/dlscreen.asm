include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

dlscreen PROC USES rbx dobj:PTR S_DOBJ, attrib:DWORD

	mov	rbx,rcx
	xor	eax,eax
	mov	[rbx],eax
	mov	eax,_scrcol	; adapt to current screen
	mov	ah,BYTE PTR _scrrow
	inc	ah
	shl	eax,16
	mov	[rbx].S_DOBJ.dl_rect,eax
	mov	r8d,edx
	rcopen( eax, _D_CLEAR or _D_BACKG, r8d, 0, 0 )

	.if	!ZERO?
		mov [rbx].S_DOBJ.dl_wp,rax
		mov [rbx].S_DOBJ.dl_flag,_D_DOPEN
		mov rax,rbx
	.endif
	ret
dlscreen ENDP

	END
