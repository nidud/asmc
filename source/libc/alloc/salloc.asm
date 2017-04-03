include alloc.inc
include string.inc

	.code

salloc	PROC string:LPSTR
	.if strlen( string )
		inc eax
		.if malloc( eax )
			strcpy( eax, string )
			test eax,eax
		.endif
	.endif
	ret
salloc	ENDP

	END
