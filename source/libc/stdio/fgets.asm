include stdio.inc
IFDEF	_UNICODE
XC	equ <ax>
FGETS	equ <fgetws>
FILBUF	equ <_filwbuf>
ELSE
XC	equ <al>
FGETS	equ <fgets>
FILBUF	equ <_filbuf>
ENDIF
	.code

	ASSUME	ebx:ptr _iobuf

FGETS	PROC USES ebx buf:LPTSTR, count:SINT, fp:LPFILE

	mov	edx,buf
	mov	ecx,count
	mov	ebx,fp
	xor	eax,eax

	.repeat
		.break .ifs ecx <= eax

		dec	ecx
		.for  : ecx : ecx--

			dec	[ebx]._cnt
			.ifl
				push	edx
				push	ecx
				FILBUF( ebx )
				pop	ecx
				pop	edx
				.if	eax == -1

					.break .if edx != buf

					xor eax,eax
					.break(1)
				.endif
			.else
				mov	eax,[ebx]._ptr
				add	[ebx]._ptr,TCHAR
				mov	XC,[eax]
			.endif
			mov	[edx],XC
			add	edx,TCHAR
			.break .if XC == 10
		.endf
		mov	TCHAR ptr [edx],0
		mov	eax,buf
		test	eax,eax
	.until	1
	ret

FGETS	ENDP

	END
