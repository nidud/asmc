include stdlib.inc
include errno.inc
include fltintrn.inc
include crtl.inc

	.code

strtod	PROC USES esi edi ebx string:LPSTR, suffix:dword

	mov esi,_strtoflt( string )
	mov ebx,[esi].S_STRFLT.mantissa
	mov edi,[esi].S_STRFLT.flags
	mov eax,[ebx+8]
	and eax,0x00007FFF

	.switch
	  .case edi & _ST_ISZERO
		.endc
	  .case edi & _ST_ISNAN or _ST_ISINF or _ST_INVALID
		xor eax,eax
		mov [ebx],eax
		.if edi & _ST_NEGNUM
			mov eax,80000000h
		.endif
		mov [ebx+4],eax
		.if edi & _ST_ISNAN or _ST_ISINF
			mov eax,000007FFh
			.if edi & _ST_ISNAN
				mov eax,00008000h
			.endif
			mov [ebx],eax
		.endif
		.endc
	  .case edi & _ST_OVERFLOW
	  .case eax >= 000043FFh
		xor eax,eax
		mov edx,7FF00000h
		.if edi & _ST_NEGNUM
			or edx,80000000h
		.endif
		mov [ebx],eax
		mov [ebx+4],edx
		jmp err_range
	  .case edi & _ST_UNDERFLOW
	  .case eax < 00003BCCh
		xor eax,eax
		mov [ebx],eax
		mov [ebx+4],eax
		jmp err_range
	  .case eax >= 00003BCDh
		mov eax,ebx
		mov edx,ebx
		_iLDFD()
		.if !( edi & _ST_OVERFLOW )
			mov eax,[ebx+4]
			and eax,7FF00000h
			.if !ZERO?
				mov eax,[ebx+4]
				and eax,7FF00000h
				.endc .if eax != 7FF00000h
			.endif
		.endif
		jmp err_range
	  .case eax >= 00003BCCh
		mov eax,ebx
		mov edx,ebx
		_iLDFD()
		mov eax,[ebx]
		or  eax,[ebx+4]
		.if !ZERO?
			mov eax,[ebx+4]
			and eax,7FF00000h
			.endc .if !ZERO?
		.endif
	   err_range:
		mov errno,ERANGE
	.endsw
	mov	eax,suffix
	.if	eax
		mov edx,[esi].S_STRFLT.string
		mov [eax],edx
	.endif
	fld QWORD PTR [ebx]
	ret
strtod	ENDP

	END
