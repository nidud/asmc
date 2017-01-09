include direct.inc

	.code

_disk_init PROC USES edi disk

	mov	edi,disk

	.if	!_disk_test( edi )

;		beep( 5, 7 )
		.if	_disk_select( "Select disk" )

			_disk_init( eax )
			mov	edi,eax
		.endif
	.endif

	mov	eax,edi
	ret

_disk_init ENDP

	END
