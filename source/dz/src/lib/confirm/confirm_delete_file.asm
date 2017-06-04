include io.inc
include confirm.inc

ID_DELETE	equ 1	; return 1
ID_DELETEALL	equ 2	; return 1 + update confirmflag
ID_SKIPFILE	equ 3	; return 0
ID_CANCEL	equ 0	; return -1

	.code

confirm_delete_file PROC USES esi fname:LPSTR, flag
	mov	eax,flag
	mov	edx,confirmflag
	.switch
	  .case al & _A_RDONLY && dl & CFREADONY
		mov	eax,-1
		mov	esi,not (CFREADONY or CFDELETEALL)
		.endc
	  .case al & _A_SYSTEM && dl & CFSYSTEM
		mov	eax,-2
		mov	esi,not (CFSYSTEM or CFDELETEALL)
		.endc
	  .case dl & CFDELETEALL
		xor	eax,eax
		mov	esi,not CFDELETEALL
		.endc
	  .default
		mov	eax,1
		jmp	toend
	.endsw
	.switch confirm_delete( fname, eax )
	  .case ID_DELETEALL
		and	confirmflag,esi
		mov	eax,1
		.endc
	  .case ID_SKIPFILE
		xor	eax,eax
	  .case ID_DELETE
		.endc
	  .default
		mov	eax,-1
	.endsw
toend:
	ret
confirm_delete_file ENDP

	END
