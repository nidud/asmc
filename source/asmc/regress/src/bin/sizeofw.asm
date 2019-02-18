;
; v2.24 sizeof(unicode string)
;
	.386
	.model flat
	.code

	mov eax,@CStr( "astring" )
	option wstring:on
	mov edx,@CStr( "wstring" )

	mov eax,sizeof(DS0000)
	mov edx,sizeof(DS0001)

	end
