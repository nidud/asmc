; v2.22 - added .UNTILAXZ, .UNTILDXZ, and .UNTILBXZ

	.386
	.MODEL	FLAT
	.CODE

	.REPEAT
	.UNTILAXZ
	.REPEAT
	.UNTILBXZ
	.REPEAT
	.UNTILCXZ
	.REPEAT
	.UNTILDXZ
	;
	; same functionality as .if <expression>
	;
	.REPEAT
	.UNTILAXZ (edx > 2 || ebx) && ecx
	.REPEAT
	.UNTILBXZ (eax > 2 || edx) && ecx
	.REPEAT
	.UNTILCXZ (eax > 2 || ebx) && edx
	.REPEAT
	.UNTILDXZ (eax > 2 || ebx) && ecx

	END
