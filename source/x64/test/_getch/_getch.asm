include conio.inc
include ctype.inc

	.code

main	proc

	_cputs( "Type 'Y' when finished typing keys: " )

	.repeat

		toupper( _getch()  )

	.until	al == 'Y'

	_putch( eax )	;
	_putch( 13 )	; Carriage return
	_putch( 10 )	; Line feed

	xor	eax,eax
	ret

main	endp

	END
