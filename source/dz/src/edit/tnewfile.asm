include tinfo.inc

	.code

tnewfile PROC USES esi

	mov	esi,tinfo
	.if	topen( 0 )

		titogglefile( esi, eax )
		mov tinfo,eax
	.endif
	ret

tnewfile ENDP

	END
