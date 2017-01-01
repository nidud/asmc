include io.inc
include stdio.inc

	.code

main	proc

	.assert osopen( "test.1", _A_NORMAL, M_WRONLY, A_CREATE ) != -1
	.assert !_close( eax )
	.assert !remove( "test.1" )
	.assert fopen( "test.1", "w" )
	.assert !fclose( rax )
	.assert !remove( "test.1" )

	ret

main	endp

	end
