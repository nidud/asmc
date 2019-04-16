	.386
	.model flat, stdcall

	.data

	@CStr( "no return value" )
     dd @CStr( "return offset" )

	.code

	mov eax,offset @CStr( "\tCreate a \"C\" string: %s%d\n" )
	mov ebx,offset @CStr( "string: %s%d\n" )
	mov ecx,offset @CStr( "%s%d\n" )
	mov edx,offset @CStr( "%d\n" )
	mov edi,offset @CStr( "\n" )

	END
