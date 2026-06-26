;
; v2.24 sizeof(unicode string)
;
	.386
	.model flat
	.code

	lea eax,@CStr( "astring" )
	option wstring:on
	lea edx,@CStr( "wstring" )

	mov eax,sizeof(D$0000)
	mov edx,sizeof(D$0001)

	end
