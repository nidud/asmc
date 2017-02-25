include alloc.inc
include tinfo.inc
include io.inc
include direct.inc
include cfini.inc
include wsub.inc

	.code

TIOpenSession PROC USES esi edi pCFINI, Section:LPSTR

local	tflag,tabz,x,b,y,l,index

	.if	__CFGetSection( pCFINI, Section )

		mov	edi,eax
		xor	eax,eax
		mov	index,eax
		mov	tflag,eax
		mov	tabz,eax

		.while	CFReadFileName( edi, addr index, 1 )

			mov	esi,eax
			.break .if !topen(esi, tflag)

			mov	tinfo,eax
			free  ( esi )

			ASSUME	esi: PTR S_TINFO

			mov	esi,tinfo
			mov	eax,tabz
			.if	eax

				mov	[esi].ti_tabz,eax
			.endif
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

TIOpenSession ENDP

TISaveSession PROC USES esi edi ebx __ini, section:LPSTR

local	buffer[1024]:	sbyte,
	handle:		dword

	.if	tigetfile(tinfo)

		mov	esi,eax
		mov	edi,edx

		mov	eax,__ini
		.if	eax

			.if	__CFAddSection( eax, section )

				mov	handle,eax

				CFDelEntries( eax )

				xor	ebx,ebx

				.while	esi

					mov	eax,[esi].ti_flag
					and	eax,_T_TECFGMASK

					CFAddEntryX( handle, "%d=%X,%X,%X,%X,%X,%X,%s", ebx,
						[esi].ti_loff,
						[esi].ti_yoff,
						[esi].ti_boff,
						[esi].ti_xoff,
						[esi].ti_tabz,
						eax,
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

TISaveSession ENDP

	ASSUME	esi: NOTHING

topenedi PROC USES esi fname:LPSTR

local	cursor:S_CURSOR

	.if	__CFRead( 0, fname )

		mov	esi,eax

		.if	__CFGetSection( esi, "." )

			CursorGet( addr cursor )

			.if	tistate( tinfo )

				tihide( tinfo )
			.endif

			TIOpenSession( esi, "." )

			.if	tistate( tinfo )

				tishow( tinfo )
				tmodal()
			.endif

			CursorSet( addr cursor )
		.endif
		__CFClose( esi )
	.endif

	mov	eax,tinfo
	ret

topenedi ENDP

tloadfiles PROC USES esi edi ebx

local	path[_MAX_PATH]:BYTE

	.if	wgetfile( addr path, "*.edi", _WOPEN )

		_close( eax )

		.if	__CFRead( 0, addr path )

			mov	esi,eax

			.if	__CFGetSection( esi, "." )

				.if	tistate( tinfo )

					tihide( tinfo )
				.endif

				TIOpenSession( esi, "." )

				.if	tistate( tinfo )

					tishow( tinfo )
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

	CursorGet( addr cu )
	call	tloadfiles
	xor	eax,eax
	call	tmodal
	CursorSet( addr cu )
	mov	eax,_TI_CONTINUE
	ret

topensession ENDP

tsavefiles PROC USES esi

local	path[_MAX_PATH]:BYTE

	.if	wgetfile( addr path, "*.edi", _WSAVE )

		_close( eax )

		.if	__CFAlloc()

			mov	esi,eax

			TISaveSession( esi, "." )
			__CFWrite( esi, addr path )
			__CFClose( esi )
		.endif
	.endif
	mov	eax,_TI_CONTINUE
	ret

tsavefiles ENDP

	END
