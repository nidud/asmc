include tinfo.inc

extern	IDD_TESave:DWORD

	.code

tisavechanges PROC USES esi edi ti:PTINFO

	.if	rsopen( IDD_TESave )
		mov	esi,eax
		dlshow( eax )
		sub	ecx,ecx
		mov	cl,[esi][6]
		sub	cl,10
		mov	ax,[esi][4]
		add	ax,0205h
		mov	dl,ah
		mov	edi,ti
		scpath( eax, edx, ecx, [edi].S_TINFO.ti_file )
		rsevent( IDD_TESave, esi )
		dlclose( esi )
		mov	eax,edx
	.endif
	ret

tisavechanges ENDP

	END
