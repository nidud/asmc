include tinfo.inc
include stdio.inc
include stdlib.inc

extern	IDD_TEOptions:DWORD

ID_USEMENUS	equ 1*16
ID_OPTIMALFILL	equ 2*16
ID_OVERWRITE	equ 3*16
ID_USEINDENT	equ 4*16
ID_USESTYLE	equ 5*16
ID_USETABS	equ 6*16
ID_USEBAKFILE	equ 7*16
ID_USECRLF	equ 8*16
ID_TABSIZE	equ 9*16

	.code

toption PROC USES ebx

	.if	rsopen( IDD_TEOptions )

		mov	ebx,eax
		mov	eax,titabsize
		sprintf( [ebx].S_TOBJ.to_data[ID_TABSIZE], "%u", eax )

		mov	eax,tiflags
		shr	eax,5
		tosetbitflag( [ebx].S_DOBJ.dl_object, 8, _O_FLAGB, eax )

		dlinit( ebx )

		.if	rsevent( IDD_TEOptions, ebx )

			togetbitflag( [ebx].S_DOBJ.dl_object, 8, _O_FLAGB )
			shl	eax,5
			mov	tiflags,eax

			strtolx( [ebx].S_TOBJ.to_data[ID_TABSIZE] )
			mov	ah,al
			mov	al,128
			.repeat
				shl	ah,1
				.break .if CARRY?
				shr	al,1
			.until ZERO?

			.if	al > TIMAXTABSIZE
				mov	al,TIMAXTABSIZE
			.elseif al < 2
				mov	al,2
			.endif
			movzx	eax,al
			mov	titabsize,eax
		.endif
		dlclose( ebx )
		mov	eax,edx
	.endif
	ret
toption ENDP

	END
