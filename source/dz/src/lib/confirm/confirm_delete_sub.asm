include confirm.inc

ID_DELETE	equ 1	; return 1
ID_DELETEALL	equ 2	; return 1 + update confirmflag
ID_SKIPFILE	equ 3	; return 0
ID_CANCEL	equ 0	; return -1

	.code

confirm_delete_sub PROC path:LPSTR
	mov	eax,1
	.if	confirmflag & CFDIRECTORY
		.if	confirm_delete(path,1) == ID_DELETEALL
			and confirmflag,not (CFDIRECTORY or CFDELETEALL)
			mov eax,1
		.elseif eax == ID_SKIPFILE
			mov eax,-1
		.elseif eax != ID_DELETE
			xor eax,eax
		.endif
	.endif
	ret
confirm_delete_sub ENDP

	END
