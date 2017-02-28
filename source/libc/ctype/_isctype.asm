include ctype.inc
include locale.inc
include winnls.inc

__GetStringTypeA proto _CType \
	dwInfoType:	DWORD,
	lpSrcStr:	LPTSTR,
	cchSrc:		SINT,
	lpCharType:	LPWORD,
	code_page:	SINT,
	lcid:		SINT,
	bError:		UINT

	.code

_isctype PROC char:SINT, cmask:SINT

local	chartype:WORD
local	buffer[3]:BYTE

	movzx eax,WORD PTR char
	inc   eax

	.repeat
		.if eax <= 256

			mov ecx,_pctype
			mov eax,[ecx+eax*2-2]
			and eax,cmask
			.break
		.endif

		dec eax
		mov ecx,eax
		shr eax,8
		.if isleadbyte(eax)

			mov buffer[0],ch	; put lead-byte at start of str
			mov buffer[1],cl
			mov buffer[2],0
			mov ecx,2
		.else
			mov buffer[0],cl
			mov buffer[1],0
			mov ecx,1
		.endif

		.if __GetStringTypeA(CT_CTYPE1, addr buffer, ecx, addr chartype, 0, 0, TRUE)

			movzx eax,chartype
			and   eax,cmask
		.endif
	.until 1
	ret

_isctype ENDP

	END

