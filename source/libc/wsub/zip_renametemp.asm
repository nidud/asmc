include io.inc
include iost.inc
include wsub.inc

	.code

zip_renametemp PROC
	ioclose( addr STDI )
	ioclose( addr STDO )
	filexist( edi )		; 1 file, 2 subdir
	dec	eax
	jnz	error
	remove( esi )
	rename( edi, esi )	 ; 0 or -1
	ret
error:
	mov	eax,-1
	ret
zip_renametemp ENDP

	end
