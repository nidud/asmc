Asmc Macro Assembler Reference

## @CStr

**@CStr**( _string_ )


Macro function that creates a string in the .DATA segment. The macro accepts C-escape characters in the string. Strings are added to a stack and reused if duplicated strings are found. The macro returns _offset string_.

Example

	mov	eax,@CStr( "\tCreate a \"C\" string: %s%d\n" )
	mov	ebx,@CStr( "string: %s%d\n" )
	mov	ecx,@CStr( "%s%d\n" )
	mov	edx,@CStr( "%d\n" )
	mov	edi,@CStr( "\n" )

Generated code

	.data
	DS0000 db 9,"Create a ",'"',"C",'"'," string: %s%d",10,0
	.code
	mov	eax,offset DS0000
	mov	ebx,offset DS0000[14]
	mov	ecx,offset DS0000[22]
	mov	edx,offset DS0000[24]
	mov	edi,offset DS0000[26]

#### See Also

[Symbols Reference](readme.md)
