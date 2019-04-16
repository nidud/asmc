;
; v2.24 sizeof(unicode string)
;
	.386
	.model flat
	.code

	lea eax,@CStr( "astring" )
	option wstring:on
	lea edx,@CStr( "wstring" )

	mov eax,sizeof(DS0000)
	mov edx,sizeof(DS0001)

	end
