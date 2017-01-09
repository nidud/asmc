include iost.inc
include consx.inc

externdef IDD_Search:dword
externdef searchstring:byte

	.code

cmsearchidd PROC USES esi edi ebx sflag
	.if rsopen( IDD_Search )
		mov	edi,eax
		mov	ebx,eax
		mov	[ebx].S_TOBJ.to_count[1*16],128 shr 4
		mov	[ebx].S_TOBJ.to_data[1*16],offset searchstring
		mov	eax,sflag
		mov	dl,_O_FLAGB
		.if eax & IO_SEARCHCASE
			or	[ebx+2*16],dl
		.endif
		.if eax & IO_SEARCHHEX
			or	[ebx+3*16],dl
		.endif
		mov dl,_O_RADIO
		.if eax & IO_SEARCHCUR
			or	[ebx+6*16],dl
		.else
			or	[ebx+7*16],dl
		.endif
		dlinit( edi )
		.if rsevent( IDD_Search, edi )
			mov	eax,sflag
			and	eax,not IO_SEARCHMASK
			mov	dl,_O_FLAGB
			.if [ebx+2*16] & dl
				or eax,IO_SEARCHCASE
			.endif
			.if [ebx+3*16] & dl
				or eax,IO_SEARCHHEX
			.endif
			.if byte ptr [ebx+6*16] & _O_RADIO
				or eax,IO_SEARCHCUR
			.else
				or eax,IO_SEARCHSET
			.endif
			mov	edx,eax
			xor	eax,eax
			.if searchstring != al
				inc eax
			.endif
		.endif
		mov	esi,edx
		dlclose( edi )
		mov	eax,edx
		mov	edx,esi
	.endif
	test	eax,eax
	ret
cmsearchidd ENDP

	END
