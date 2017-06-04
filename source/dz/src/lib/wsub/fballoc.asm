include alloc.inc
include string.inc
include wsub.inc

	.code

fballoc PROC USES ebx fname:LPSTR, ftime:DWORD, fsize:QWORD, flag:DWORD


	add	strlen(fname),SIZE S_FBLK
	.if	malloc(eax)

		mov	ebx,eax
		add	eax,S_FBLK.fb_name
		strcpy( eax, fname )
		mov	eax,flag
		mov	[ebx].S_FBLK.fb_flag,eax
		mov	eax,ftime
		mov	[ebx].S_FBLK.fb_time,eax
		mov	eax,DWORD PTR fsize[0]
		mov	DWORD PTR [ebx].S_FBLK.fb_size,eax
		mov	eax,DWORD PTR fsize[4]
		mov	DWORD PTR [ebx].S_FBLK.fb_size[4],eax
		mov	eax,ebx
	.endif
	ret

fballoc ENDP

	END
