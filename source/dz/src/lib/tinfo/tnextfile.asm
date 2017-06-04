include tinfo.inc

	.code

	ASSUME	edx: PTR S_TINFO

tnextfile PROC

	.if	tigetfile( tinfo )

		.if	ecx > 1

			mov	edx,tinfo
			.if	[edx].ti_next

				mov eax,[edx].ti_next
			.endif

			titogglefile( edx, eax )
		.endif

		mov	tinfo,eax
	.endif
	ret

tnextfile ENDP

	END
