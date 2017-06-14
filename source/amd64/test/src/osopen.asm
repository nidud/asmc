include io.inc
include stdio.inc

	.code

main	proc

	.assert _osopenA( "test.1", M_WRONLY, 0, 0, A_CREATE, 0 ) != -1
	.assert !_close( eax )
	.assert !remove( "test.1" )
	.assert fopen( "test.1", "w" )
	.assert !fclose( rax )
	.assert !remove( "test.1" )

	ret

main	endp

	end
