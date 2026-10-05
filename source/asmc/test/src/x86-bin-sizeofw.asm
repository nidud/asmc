;
; v2.24 sizeof(unicode string)
;
	.386
	.model flat
	.code

	lea eax,@CStr( "astring" )
	option wstring:on
	lea edx,@CStr( "wstring" )

	mov eax,sizeof(@CStr(1))
	mov edx,sizeof(@CStr(0))

	end
