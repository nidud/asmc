include tinfo.inc

	.code

tisaveas PROC USES esi ti:PTINFO

	mov	esi,ti

	.if	tigetfilename( esi )

		tiflush( esi )

		xor [esi].S_TINFO.ti_flag,_T_USEMENUS
		titogglemenus( esi )
	.endif
	xor	eax,eax
	ret
tisaveas ENDP

	END
