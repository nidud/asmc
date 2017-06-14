include crtl.inc
include strlib.inc

	.code	; Test if <ext> == bat | cmd | com | exe

	OPTION	WIN64:2, STACKBASE:rsp

__isexec PROC filename:LPSTR
	.if	strext( rcx )
		mov	eax,[rax+1]
		or	eax,'   '
		.switch eax
		  .case 'dmc':	mov eax,_EXEC_CMD: .endc
		  .case 'exe':	mov eax,_EXEC_EXE: .endc
		  .case 'moc':	mov eax,_EXEC_COM: .endc
		  .case 'tab':	mov eax,_EXEC_BAT: .endc
		  .default
			xor	eax,eax
		.endsw
	.endif
	ret
__isexec ENDP

	END
