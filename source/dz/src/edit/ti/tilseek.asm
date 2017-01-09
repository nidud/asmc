include tinfo.inc
include stdio.inc
include stdlib.inc

extern	IDD_TESeek:DWORD

	.code

tilseek PROC USES esi edi ti:PTINFO

	mov	esi,ti

	.if	rsopen( IDD_TESeek )

		mov	edi,eax

		mov	ecx,[esi].S_TINFO.ti_loff
		add	ecx,[esi].S_TINFO.ti_yoff
		inc	ecx

		sprintf( [edi+24], "%u", ecx )
		dlinit ( edi )

		.if	rsevent( IDD_TESeek, edi )
			.if	strtolx( [edi+24] )
				dec	eax
				tialigny( esi, eax )
			.endif
		.endif
		dlclose( edi )
		tiputs ( esi )
	.endif
	xor	eax,eax
	ret
tilseek ENDP

	END
