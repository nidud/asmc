include tinfo.inc
include string.inc
include stdio.inc
include stdlib.inc
include io.inc
include direct.inc
include ini.inc
include wsub.inc

	.code

topenh_atol PROC
	.if	strchr( esi, ',' )
		inc	eax
		mov	esi,eax
		atol  ( esi )
		or	esi,esi
		mov	edx,eax
		mov	eax,1
	.endif
	ret
topenh_atol ENDP

topenh PROC USES esi edi ebx fname:LPSTR

	local	entry, loff, boff, xoff

	mov	edi,cinifile

	.if	iniopen( fname )

		mov	entry,0

		.while	inientryid( ".", entry )

			mov	esi,eax
			inc	entry
			atol  ( esi )
			mov	loff,eax

			.break .if !topenh_atol()
			mov	ebx,edx
			.break .if !topenh_atol()
			mov	boff,edx
			.break .if !topenh_atol()
			mov	xoff,edx

			.break .if !strchr( esi, ',' )
			lea	esi,[eax+1]
			expenviron( esi )

			.continue .if filexist( esi ) != 1

			push	cinifile
			mov	cinifile,edi
			topen ( esi )
			pop	ecx
			mov	cinifile,ecx
			.break .if !eax

			ASSUME	esi: PTR S_TINFO

			mov	tinfo,eax
			mov	esi,eax
			mov	eax,loff
			mov	[esi].ti_loff,eax
			mov	[esi].ti_yoff,ebx
			mov	eax,xoff
			mov	[esi].ti_xoff,eax
			mov	eax,boff
			mov	[esi].ti_boff,eax
		.endw
		call	iniclose
		mov	eax,tinfo
		test	eax,eax
	.endif
	mov	cinifile,edi
	ret
topenh ENDP

tsaveh	PROC USES esi edi ebx handle:SINT

	local	buf[512]:BYTE

	tigetfile( tinfo )
	mov	esi,eax
	mov	edi,edx

	oswrite( handle, "[.]\r\n", 5 )
	xor	ebx,ebx

	.while	esi

		sprintf( addr buf, "%d=%d,%d,%d,%d,%s\r\n", ebx,
			[esi].ti_loff,
			[esi].ti_yoff,
			[esi].ti_boff,
			[esi].ti_xoff,
			[esi].ti_file )

		strlen( addr buf )
		mov	ecx,eax
		oswrite( handle, addr buf, ecx )
		inc	ebx
		.break .if esi == edi
		mov	esi,[esi].ti_next
		.break .if !tistate( esi )
	.endw
	ret
tsaveh	ENDP

	ASSUME	esi: NOTHING

topenedi PROC fname:LPSTR

	local	cu:S_CURSOR

	GetCursor( addr cu )

	.if	tistate( tinfo )
		tihide( tinfo )
	.endif

	topenh( fname )

	.if	tistate( tinfo )
		tishow( tinfo )
		tmodal()
	.endif
	SetCursor( addr cu )
	mov	eax,tinfo
	ret
topenedi ENDP

tloadfiles PROC

	local	path[_MAX_PATH]:BYTE

	.if	wgetfile( addr path, "*.edi", 3 )

		_close( eax )

		.if	tistate( tinfo )
			tihide ( tinfo )
		.endif

		topenh( addr path )

		.if	tistate( tinfo )
			tishow ( tinfo )
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

tsavefiles PROC

	local	path[_MAX_PATH]:BYTE

	.if	wgetfile( addr path, "*.edi", 2 )

		push	eax
		tsaveh( eax )
		call	_close
	.endif
	mov	eax,_TI_CONTINUE
	ret

tsavefiles ENDP

	END
