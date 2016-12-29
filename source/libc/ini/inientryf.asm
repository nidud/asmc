include ini.inc
include string.inc

	.code

inientryf PROC section:LPSTR, entry:LPSTR, inifile:LPSTR
	local	result[256]:byte
	mov	edx,cinifile
	.if	iniopen( inifile )
		.if	inientry( section, entry )
			lea	ecx,result
			strcpy( ecx, eax )
		.endif
		call	iniclose
	.endif
	mov	cinifile,edx
	test	eax,eax
	ret
inientryf ENDP

	END
