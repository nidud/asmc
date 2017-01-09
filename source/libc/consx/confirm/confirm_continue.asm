include consx.inc

extrn IDD_ConfirmContinue:DWORD

	.code

confirm_continue PROC USES ebx msg
	.if	rsopen( IDD_ConfirmContinue )
		mov	ebx,eax
		dlshow( eax )
		mov	eax,msg
		.if	eax
			mov dx,[ebx+4]
			add dx,0204h
			mov cl,dh
			scpath( edx, ecx, 34, eax )
		.endif
		dlmodal( ebx )
	.endif
	ret
confirm_continue ENDP

	END
