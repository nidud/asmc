include alloc.inc
include tinfo.inc
include io.inc
include direct.inc
include cfini.inc
include wsub.inc

	.code

topenh	PROC USES esi edi section:LPSTR

local	x,b,y,l,index

	.if	CFGetSection( section )

		mov	edi,eax
		mov	index,0

		.while	CFReadFileName( edi, addr index, 1 )

			mov	esi,eax
			.break .if !topen(esi)

			mov	tinfo,eax
			free  ( esi )

			ASSUME	esi: PTR S_TINFO

			mov	esi,tinfo
			mov	eax,l
			mov	[esi].ti_loff,eax
			mov	eax,y
			mov	[esi].ti_yoff,eax
			mov	eax,x
			mov	[esi].ti_xoff,eax
			mov	eax,b
			mov	[esi].ti_boff,eax
		.endw

		mov	eax,tinfo
		test	eax,eax
	.endif
	ret

topenh ENDP

tsaveh	PROC USES esi edi ebx __ini, section:LPSTR

local	buffer[1024]:	sbyte,
	handle:		dword

	.if	tigetfile(tinfo)

		mov	esi,eax
		mov	edi,edx

		mov	eax,__ini
		.if	eax

			.if	__CFAddSection( eax, section )

				mov	handle,eax
				xor	ebx,ebx

				.while	esi

					CFAddEntryX( handle, "%d=%X,%X,%X,%X,%s", ebx,
						[esi].ti_loff,
						[esi].ti_yoff,
						[esi].ti_boff,
						[esi].ti_xoff,
						[esi].ti_file )

					inc	ebx
					.break .if esi == edi
					mov	esi,[esi].ti_next
					.break .if !tistate(esi)
				.endw
			.endif
		.endif
	.endif
	ret

tsaveh	ENDP

	ASSUME	esi: NOTHING

topenedi PROC USES esi edi ebx fname:LPSTR

local	cursor:S_CURSOR

	.if	__CFRead( 0, fname )

		mov	esi,eax

		.if	__CFGetSection( esi, "." )

			mov	edi,eax

			.if	CFAddSection( "." )

				mov	ebx,eax

				mov	eax,[edi].S_CFINI.cf_info
				mov	[ebx].S_CFINI.cf_info,eax

				GetCursor( addr cursor )

				.if	tistate( tinfo )

					tihide( tinfo )
				.endif

				topenh( "." )

				mov	[ebx].S_CFINI.cf_info,0

				.if	tistate( tinfo )

					tishow( tinfo )
					tmodal()
				.endif

				SetCursor( addr cursor )
			.endif
		.endif

		__CFClose( esi )
	.endif

	mov	eax,tinfo
	ret

topenedi ENDP

tloadfiles PROC USES esi edi ebx

	local	path[_MAX_PATH]:BYTE

	.if	wgetfile( addr path, "*.edi", 3 )

		_close( eax )

		.if	__CFRead( 0, addr path )

			mov	esi,eax

			.if	__CFGetSection( esi, "." )

				mov	edi,eax

				.if	CFAddSection( "." )

					mov	ebx,eax

					mov	eax,[edi].S_CFINI.cf_info
					mov	[ebx].S_CFINI.cf_info,eax

					.if	tistate( tinfo )

						tihide ( tinfo )
					.endif

					topenh( "." )

					mov	[ebx].S_CFINI.cf_info,0

					.if	tistate( tinfo )

						tishow ( tinfo )
					.endif
				.endif
			.endif

			__CFClose( esi )
		.endif
	.endif

	mov	eax,_TI_CONTINUE
	ret

tloadfiles ENDP

topensession PROC

local	cu:S_CURSOR

	GetCursor( addr cu )
	call	tloadfiles
	xor	eax,eax
	call	tmodal
	SetCursor( addr cu )
	mov	eax,_TI_CONTINUE
	ret

topensession ENDP

tsavefiles PROC USES esi edi ebx

local	path[_MAX_PATH]:BYTE

	.if	wgetfile( addr path, "*.edi", 2 )

		_close( eax )

		.if	__CFAlloc()

			mov	esi,eax

			tsaveh( esi, "." )
			__CFWrite( esi, addr path )
			__CFClose( esi )
		.endif
	.endif
	mov	eax,_TI_CONTINUE
	ret

tsavefiles ENDP

	END
