; CMFILTER.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include stdio.inc
include stdlib.inc
include string.inc
include time.inc

ID_INCLUDE	equ 1*16
ID_EXCLUDE	equ 2*16
ID_MIN_DATE	equ 3*16
ID_MAX_DATE	equ 4*16
ID_MIN_SIZE	equ 5*16
ID_MAX_SIZE	equ 6*16
ID_RDONLY	equ 7*16
ID_HIDDEN	equ 8*16
ID_SYSTEM	equ 9*16
ID_VOLID	equ 10*16
ID_SUBDIR	equ 11*16
ID_ARCH		equ 12*16
ID_OK		equ 13*16
ID_CLEAR	equ 14*16
ID_CANCEL	equ 15*16

	.data

externdef	format_lu:BYTE
externdef	cp_stdmask:SBYTE
externdef	IDD_OperationFilters:DWORD
externdef	IDD_DZFindFile:DWORD
cp_filter	db "Filter",0
filter_keys	dd KEY_F3, cmfilter_load
		dd KEY_F4, cmfilter_date
		dd 0

	.code

cmfilter_load PROC USES esi edi ebx
  local filt[FILT_MAXSTRING]:BYTE
	mov	ebx,tdialog
	mov	eax,IDD_DZFindFile
	mov	dl,[eax].S_ROBJ.rs_count
	mov	edi,0D0Dh
	.if	[ebx].S_DOBJ.dl_count != dl
		mov edi,1
	.endif
	tools_idd( 128, addr filt, addr cp_filter )
	mov	edx,eax
	call	msloop
	.if	edx && edx != MOUSECMD
		mov	eax,edi
		.if	[ebx].S_DOBJ.dl_index != al
			mov [ebx].S_DOBJ.dl_index,ah
		.endif
		movzx	ecx,[ebx].S_DOBJ.dl_index
		shl	ecx,4
		add	ecx,[ebx].S_DOBJ.dl_object
		strcpy( [ecx].S_TOBJ.to_data, addr filt )
		dlinit( ebx )
	.endif
	mov	eax,_C_NORMAL
	ret
cmfilter_load ENDP

cmfilter_date PROC PRIVATE USES edi ebx
	mov	edi,tdialog
	mov	al,[edi].S_DOBJ.dl_index
	.if	al != 2 && al != 3
		mov	[edi].S_DOBJ.dl_index,2
	.endif
	.if	cmcalendar()
		mov	ebx,eax
		movzx	eax,[edi].S_DOBJ.dl_index
		inc	eax
		shl	eax,4
		add	eax,edi
		sprintf( [eax].S_TOBJ.to_data, addr cp_datefrm, edx, ebx, ecx )
		dlinit( edi )
	.endif
	mov	eax,_C_NORMAL
	ret
cmfilter_date ENDP

filter_edit PROC USES esi edi ebx filt:ptr, glcmd:ptr

  local FileTime:FILETIME

	.if	rsopen( IDD_OperationFilters )

		mov	edi,eax
		mov	esi,filt
		mov	filter,esi
		push	thelp
		mov	thelp,event_help

		lea	eax,[esi].S_FILT.of_include
		mov	[edi].S_TOBJ.to_data[ID_INCLUDE],eax
		add	eax,128
		mov	[edi].S_TOBJ.to_data[ID_EXCLUDE],eax
		mov	[edi].S_TOBJ.to_count[ID_INCLUDE],8
		mov	[edi].S_TOBJ.to_count[ID_EXCLUDE],8
		mov	eax,glcmd
		mov	[edi].S_TOBJ.to_data[ID_OK],eax
		mov	[edi].S_TOBJ.to_proc[ID_CLEAR],event_clear
		.if	[esi].S_FILT.of_min_date
			strdate( [edi].S_TOBJ.to_data[ID_MIN_DATE], [esi].S_FILT.of_min_date )
		.endif
		.if	[esi].S_FILT.of_max_date
			strdate( [edi].S_TOBJ.to_data[ID_MAX_DATE], [esi].S_FILT.of_max_date )
		.endif
		.if	[esi].S_FILT.of_min_size
			sprintf( [edi].S_TOBJ.to_data[ID_MIN_SIZE], addr format_lu,[esi].S_FILT.of_min_size )
		.endif
		.if	[esi].S_FILT.of_max_size
			sprintf( [edi].S_TOBJ.to_data[ID_MAX_SIZE], addr format_lu,[esi].S_FILT.of_max_size )
		.endif
		lea	ebx,[edi+ID_RDONLY]
		mov	eax,[esi].S_FILT.of_flag

		tosetbitflag	( ebx, 6, _O_FLAGB, eax )
		dlinit		( edi )
		rsevent		( IDD_OperationFilters, edi )
		dlclose		( edi )

		pop	eax
		mov	thelp,eax
		.if	edx
			togetbitflag( addr [edi][ID_RDONLY], 6, _O_FLAGB )
			or	eax,0FFC0h
			mov	[esi].S_FILT.of_flag,eax
			strtolx( [edi].S_TOBJ.to_data[ID_MAX_SIZE] )
			mov	[esi].S_FILT.of_max_size,eax
			strtolx( [edi].S_TOBJ.to_data[ID_MIN_SIZE] )
			mov	[esi].S_FILT.of_min_size,eax
			atodate( [edi].S_TOBJ.to_data[ID_MAX_DATE] )
			mov	[esi].S_FILT.of_max_date,eax
			atodate( [edi].S_TOBJ.to_data[ID_MIN_DATE] )
			mov	[esi].S_FILT.of_min_date,eax
			mov	eax,_C_NORMAL
		.else
			xor	eax,eax
			mov	filter,eax
		.endif
	.else
		xor	eax,eax
		mov	filter,eax
	.endif
	ret

event_clear:
	mov	ecx,esi
	mov	esi,tdialog
	xor	eax,eax
	mov	edx,[esi].S_TOBJ.to_data[ID_MIN_DATE]
	mov	[edx],al
	mov	edx,[esi].S_TOBJ.to_data[ID_MAX_DATE]
	mov	[edx],al
	mov	edx,[esi].S_TOBJ.to_data[ID_MIN_SIZE]
	mov	[edx],al
	mov	edx,[esi].S_TOBJ.to_data[ID_MAX_SIZE]
	mov	[edx],al
	mov	esi,ecx
	memset( filter, 0, SIZE S_FILT )
	mov	edx,filter
	strcpy( addr [edx].S_FILT.of_include, addr cp_stdmask )
	mov	[edx].S_FILT.of_flag,-1
	mov	eax,tdialog
	add	eax,ID_RDONLY
	tosetbitflag( eax, 6, _O_FLAGB, 0FFFFFFFFh )
	mov	eax,_C_REOPEN
	retn

event_help:
	mov	eax,HELPID_12
	call	view_readme
	retn
filter_edit ENDP

cmfilter PROC
	filter_edit( addr opfilter, addr filter_keys )
	ret
cmfilter ENDP

	END
