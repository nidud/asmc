;
; Code Info is a RAM-resident (TSR) utility that accesses
; Code Information (help) using an editor or similar
;
; The program activates by Shift-Left + Shift-Right
;
; Change history:
; 2015-07-31 - expand environ in source path [.file]
; 2014-09-11 - added option create file to edit source
; 2014-09-11 - read [CodeInfo] at startup to avoid use dz.ci
; 2014-08-25 - changed library -- auto SSE usage
; 2014-08-25 - changed to GlobalAlloc() -- use more memory
; 2014-08-18 - fixed bug in CIPutSection()
; 2014-08-18 - fixed bug in EditText()
; 2014-08-18 - Changed short key Tab to F6
; 2014-08-18 - expanded size of struct to 2048
; 2014-08-12 - update screen metrics before pop-up..
; 2013-11-23 - made edit dialog movable -- Mouse/Alt-Up...
; 2013-11-20 - fixed bug in CIDelSection
; 2013-11-04 - converted to 32-bit
;
include consx.inc
include direct.inc
include io.inc
include iost.inc
include string.inc
include alloc.inc
include errno.inc
include stdlib.inc
include ini.inc
include tview.inc
include tinfo.inc

externdef _pgmpath:dword

;-------------------------------------------------------------------------
; DZCI
;-------------------------------------------------------------------------

	.data

DLLPROC		equ CodeInfo
POPUPKEY	equ SHIFT_RIGHT or SHIFT_LEFT
MAXLABEL	equ 32		; label size in memory
MAXLABELS	equ 8000	; labels in memory
MAXLSTACK	equ 9

S_LABEL		STRUC
section		db MAXLABEL dup(?)
c_decl		db 128 dup(?)
arg0		db 96 dup(?)
arg1		db 96 dup(?)
arg2		db 96 dup(?)
arg3		db 96 dup(?)
arg4		db 96 dup(?)
arg5		db 96 dup(?)
arg6		db 96 dup(?)
ret0		db 96 dup(?)
ret1		db 96 dup(?)
ret2		db 96 dup(?)
incfile		db 128 dup(?)
info		db 192 dup(?)
ref0		db 48 dup(?)
ref1		db 48 dup(?)
ref2		db 48 dup(?)
ref3		db 48 dup(?)
ref4		db 48 dup(?)
ref5		db 48 dup(?)
ref6		db 48 dup(?)
ref7		db 48 dup(?)
ref8		db 48 dup(?)
ref9		db 48 dup(?)
srcfile		db 128 dup(?)
S_LABEL		ENDS ; 2048

externdef	IDD_CIEdit:DWORD
externdef	IDD_CIDict:DWORD
externdef	IDD_CISetup:DWORD
externdef	IDD_CIHelp:DWORD
externdef	IDD_CICreate:DWORD

callstack	dd 0
idleh		dd 0	; current idle() pointer
active		dd 0

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

MAXENTRIES	equ 24
ID_INCLUDE	equ 12
ID_INFO		equ 13

cisection	S_LABEL <>
cilstack	S_LABEL MAXLSTACK dup(<>)
cilcount	dd 0
cisrcpath	db _MAX_PATH dup(0)
ciincpath	db _MAX_PATH dup(0)
cifile		db _MAX_PATH dup(0)
cifileid	dd 0
cp_CodeInfo	db "CodeInfo",0 ; [CodeInfo] in dz.ini
cilabels	dd 0		; sizeof(S_LABEL) * MAXLABELS
DLG_CIEdit	dd 0
txtval		dd 0
txtvaled	dd 0

GCMD_CI label DWORD
	dd KEY_F2,	event_save
	dd KEY_F3,	event_view
	dd KEY_F4,	event_edit
	dd KEY_F5,	event_dict
	dd KEY_F8,	event_delete
	dd KEY_F9,	event_conf
	dd KEY_CTRLUP,	event_CTRLUP
	dd KEY_CTRLDN,	event_CTRLDN
	dd KEY_ALTX,	event_exit
	dd 0

cp_conf db ".file",0

CI_LABELS label BYTE
	db 1		; [section]
	db 0		; 00 c_decl
	db 0,0,0,0,0,0,0; 01 arg0
	db 0,0,0	; 08 ret0
	db 3		; 11 include
	db 2		; 12 info
	db 1,1,1,1,1,1,1; 13 ref0
	db 1,1,1
	db 4		; 23 srcfile
	db 5		; 24 time

;
; .CI Index to offset
;
CI_OFFSETS label DWORD	; [section] == offset 0
	dd S_LABEL.c_decl
	dd S_LABEL.arg0
	dd S_LABEL.arg1
	dd S_LABEL.arg2
	dd S_LABEL.arg3
	dd S_LABEL.arg4
	dd S_LABEL.arg5
	dd S_LABEL.arg6
	dd S_LABEL.ret0
	dd S_LABEL.ret1
	dd S_LABEL.ret2
	dd S_LABEL.incfile
	dd S_LABEL.info
	dd S_LABEL.ref0
	dd S_LABEL.ref1
	dd S_LABEL.ref2
	dd S_LABEL.ref3
	dd S_LABEL.ref4
	dd S_LABEL.ref5
	dd S_LABEL.ref6
	dd S_LABEL.ref7
	dd S_LABEL.ref8
	dd S_LABEL.ref9
	dd S_LABEL.srcfile

	.code

	OPTION	PROC: PRIVATE

; Get value of edited text to put '*' (not saved)

gettxtval:
	push	ebx
	lea	edx,cisection
	sub	eax,eax
	mov	ebx,eax
	mov	ecx,sizeof(S_LABEL)
     @@:
	mov	al,[edx]
	inc	edx
	add	ebx,eax
	shl	ebx,1
	adc	ebx,0
	dec	ecx
	jnz	@B
	mov	eax,ebx
	pop	ebx
	ret

puttxtval:
	call	gettxtval
	mov	edx,DLG_CIEdit
	movzx	ecx,[edx].S_DOBJ.dl_rect.rc_x
	add	ecx,1
	movzx	edx,[edx].S_DOBJ.dl_rect.rc_y
	add	edx,2
	cmp	eax,txtval
	mov	eax,' ';0C4h
	je	@F
	mov	eax,'*'
     @@:
	scputc( ecx, edx, 1, eax )
	ret

cigetp	PROC lp, id
	mov	eax,id
	.if eax < MAXENTRIES
		mov	eax,CI_OFFSETS[eax*4]
		add	eax,lp
	.else
		xor	eax,eax
	.endif
	ret
cigetp	ENDP

CIFindSection PROC USES esi edi ebx ecx edx section

	mov	edi,cilabels
	mov	ebx,cilcount
	strlen( section )
	mov	edx,eax
	sub	eax,eax
	.if	edx && ebx

		.repeat
			.if	!_stricmp(edi,section)

				mov	eax,edi
				jmp	@F
			.endif
			add	edi,SIZE S_LABEL
			dec	ebx
		.until !ebx
		xor	eax,eax
	.endif
     @@:
	ret
CIFindSection ENDP

CIRead PROC USES esi edi ebx

	local	lbuf[256]:BYTE

	xor	eax,eax
	mov	cilcount,eax
	mov	edi,cilabels
	mov	ecx,sizeof(S_LABEL) * MAXLABELS
	rep	stosb

	.if ogetl( addr cifile, addr lbuf, 256 )

		mov	edi,cilabels
		.while	ogets()

			lea	esi,lbuf
			mov	al,[esi]
			.if al == '['

				inc	cilcount
				mov	eax,cilcount
				.if eax >= MAXLABELS
					dec	cilcount
					.break
				.endif
				dec	eax
				shl	eax,11
				mov	edi,cilabels
				add	edi,eax
				mov	edx,edi
				inc	esi
				mov	ecx,MAXLABEL
				.repeat
					lodsb
					.break .if al == ']'
					stosb
					.break .if !al
				.untilcxz
				mov	edi,edx

			.elseif al >= '0' && al <= '9'

				mov	ax,[esi+1]
				.if ah == '=' || al == '='
					atol( esi )

					.if cigetp( edi, eax )

						lea	edx,[esi+1]
						.if BYTE PTR [edx] != '='
							inc	edx
						.endif
						inc	edx
						strcpy( eax, edx )
					.endif
				.endif
			.endif
		.endw

		ioclose( addr STDI )

		.if CIFindSection( addr cp_conf )

			mov	edi,eax
			strcpy( addr ciincpath, addr [edi].S_LABEL.incfile )
			expenviron( eax )
			strcpy( addr cisrcpath, addr [edi].S_LABEL.srcfile )
			expenviron( eax )
		.endif
		mov	eax,1
	.endif
	ret
CIRead ENDP

CIWrite PROC USES esi edi ebx

	local	bak[_MAX_PATH]:BYTE

	remove( setfext( strcpy( addr bak, addr cifile ), ".bak" ) )
	rename( addr cifile, addr bak )

	.if SDWORD PTR ioopen( addr STDO, addr cifile, M_WRONLY, 10000h ) > 1

		mov	edi,cilabels
		mov	ebx,cilcount

		.while	ebx

			.if BYTE PTR [edi]

				oprintf( "[%s]\n", edi )
				sub	esi,esi
				.while	cigetp( edi, esi )
					.if BYTE PTR [eax]
						oprintf( "%d=%s\n", esi, eax )
					.endif
					inc	esi
				.endw
			.endif
			add	edi,SIZE S_LABEL
			dec	ebx
		.endw
		ioflush( addr STDO )
		ioclose( addr STDO )
		mov	eax,1
	.endif
	ret
CIWrite ENDP

CIClearSection PROC USES esi edi
	mov	eax,DLG_CIEdit
	movzx	esi,[eax].S_DOBJ.dl_rect.rc_x
	add	esi,35
	movzx	edx,[eax].S_DOBJ.dl_rect.rc_y
	add	edx,6
	mov	ecx,11
	mov	edi,31
	push	edx
	.repeat
		scputc( esi, edx, edi, ' ' )
		inc	edx
	.untilcxz
	pop	edx
	mov	eax,esi
	ret
CIClearSection ENDP

CIPutSection PROC USES esi edi ebx
	call	CIClearSection
	mov	esi,eax
	lea	edi,cisection.ref0
	mov	ecx,7
	.repeat
		.if CIFindSection( edi )
			add	eax,S_LABEL.info
			scputs( esi, edx, 0, 31, eax )
		.endif
		inc	edx
		add	edi,48;MAXLABEL
	.untilcxz
	inc	edx
	mov	ecx,3
	.repeat
		.if CIFindSection( edi )
			add	eax,S_LABEL.info
			scputs( esi, edx, 0, 31, eax )
		.endif
		inc	edx
		add	edi,48;MAXLABEL
	.untilcxz
	add	edx,2
	sub	esi,33
	scputc( esi, edx, 40, ' ' )
	strfn ( addr cifile )
	scputs( esi,edx,0,40,eax )
	dlinit( DLG_CIEdit )
	ret
CIPutSection ENDP

CINextFile PROC USES esi edi ebx
	mov	ebx,cifileid
	inc	ebx
	.if	!inientryid( addr cp_CodeInfo, ebx )
		xor	ebx,ebx
		inientryid( addr cp_CodeInfo, ebx )
	.endif
	.if	eax
		mov	edi,eax
		call	CIWrite
		mov	dx,[edi]
		.if	dl == '%' || dl == '\' || dl == '/' || dh == ':'
			strcpy( addr cifile, edi )
		.else
			strfcat( addr cifile, _pgmpath, edi )
		.endif
		expenviron( eax )
		mov	cifileid,ebx
		call	CIRead
		mov	txtval,0
		call	CIPutSection
		mov	eax,DLG_CIEdit
		mov	[eax].S_DOBJ.dl_index,0
		mov	eax,1
	.endif
	ret
CINextFile ENDP

CIReadSection PROC USES esi edi ebx section

local	tmp[MAXLABEL]:BYTE

	lea edi,tmp
	mov esi,section
	lea ebx,cisection

	.if strcmp( ebx, esi )

		memmove( addr cilstack, ebx, sizeof(S_LABEL) * MAXLSTACK )
	.endif

	strncpy( edi, esi, MAXLABEL-1 )
	mov byte ptr [eax+MAXLABEL-1],0
	strncpy( ebx, edi, MAXLABEL )

	.if CIFindSection( eax )

		memcpy( ebx, eax, sizeof( S_LABEL ) )
		mov txtval,gettxtval()
	.else
		mov txtval,0
	.endif
	puttxtval()
	CIPutSection()
	ret
CIReadSection ENDP

CISaveSection PROC section
	.if	CIFindSection( section )
		memcpy( eax, addr cisection, sizeof(S_LABEL) )
	.else
		mov	eax,cilcount
		.if	eax < MAXLABELS
			shl	eax,11
			add	eax,cilabels
			inc	cilcount
			memcpy( eax, addr cisection, sizeof(S_LABEL) )
		.else
			xor	eax,eax
		.endif
	.endif
	mov	txtval,eax
	.if	eax
		call	gettxtval
		mov	txtval,eax
	.endif
	ret
CISaveSection ENDP

CIDelSection PROC USES esi edi

	.if CIFindSection( addr cisection )

		mov	edi,eax
		mov	esi,eax
		add	esi,sizeof(S_LABEL)
		dec	cilcount
		mov	eax,cilcount
		shl	eax,11
		add	eax,cilabels
		mov	ecx,eax
		sub	ecx,esi
		js	@F
		shr	ecx,2
		rep	movsd
		sub	eax,sizeof(S_LABEL)
	     @@:
		mov	edi,eax
		xor	eax,eax
		mov	ecx,sizeof(S_LABEL) / 4
		rep	stosd
		mov	txtval,eax
	.endif
	lea	edi,cisection
	mov	ecx,sizeof(S_LABEL)
	xor	eax,eax
	rep	stosb
	ret
CIDelSection ENDP

CIViewSrc PROC

	local	path[_MAX_PATH]:BYTE

	.if cisection.srcfile

		tview( strfcat( addr path, addr cisrcpath, addr cisection.srcfile ), 0 )
	.endif
	mov	eax,_C_NORMAL
	ret
CIViewSrc ENDP

CIViewInc PROC

	local	path[_MAX_PATH]:BYTE

	.if cisection.incfile

		tview( strfcat( addr path, addr ciincpath, addr cisection.incfile ), 0 )
	.endif
	mov	eax,_C_NORMAL
	ret
CIViewInc ENDP

ciedit	PROC USES esi file
	mov	esi,tinfo
	mov	tinfo,0
	.if	topen ( file )
		call	tmodal
		call	tclose
		call	CIPutSection
	.endif
	mov	tinfo,esi
	ret
ciedit endp

CIEditSrc PROC

local	path[_MAX_PATH]:BYTE

	.if cisection.srcfile

		.if _access( strfcat( addr path, addr cisrcpath, addr cisection.srcfile ), 0 )

			.if rsmodal( IDD_CICreate )

				.if osopen( addr path, _A_NORMAL, M_WRONLY, A_CREATE ) != -1

					_close( eax )
				.endif
			.else
				jmp toend
			.endif
		.endif
		ciedit( addr path )
	.endif
toend:
	mov eax,_C_NORMAL
	ret

CIEditSrc ENDP

CIEditInc PROC
	local	path[_MAX_PATH]:BYTE
	.if	cisection.incfile
		ciedit( strfcat( addr path, addr ciincpath, addr cisection.incfile ) )
	.endif
	mov	eax,_C_NORMAL
	ret
CIEditInc ENDP

CIMoveUp PROC
	local	ll:S_LABEL
	lea	edx,cisection
	memcpy( addr ll, edx, sizeof(S_LABEL) )
	memcpy( edx, addr cilstack, sizeof(S_LABEL) * MAXLSTACK )
	memcpy( addr [edx + sizeof(S_LABEL) * MAXLSTACK], addr ll, sizeof(S_LABEL) )
	ret
CIMoveUp ENDP

CIMoveDn PROC
	local	ll:S_LABEL
	lea	edx,cisection
	memcpy( addr ll, addr [edx + sizeof(S_LABEL) * MAXLSTACK], sizeof(S_LABEL) )
	memmove( addr cilstack, edx, sizeof(S_LABEL) * MAXLSTACK )
	memcpy( edx, addr ll, sizeof(S_LABEL) )
	ret
CIMoveDn ENDP

editevent PROC USES esi
	local	cursor:S_CURSOR
	GetCursor( addr cursor )
	mov	edx,DLG_CIEdit
	movzx	eax,[edx].S_DOBJ.dl_index
	shl	eax,4
	add	eax,[edx].S_DOBJ.dl_object
	mov	esi,eax
	mov	edx,[edx].S_DOBJ.dl_rect
	mov	eax,[esi].S_TOBJ.to_rect
	add	ax,dx
	mov	edx,eax
	movzx	ecx,[esi].S_TOBJ.to_count
	shl	ecx,4
	movzx	eax,[esi].S_TOBJ.to_flag
	mov	esi,[esi].S_TOBJ.to_data
	dledit( esi, edx, ecx, eax )
	push	eax
	SetCursor( addr cursor )
	pop	eax
	ret
editevent ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

event_help:
	rsmodal( IDD_CIHelp )
	jmp	event_normal
event_CTRLUP:
	call	CIMoveUp
	jmp	event_normalput
event_CTRLDN:
	call	CIMoveDn
	jmp	event_normalput
event_view:
	mov	eax,DLG_CIEdit
	cmp	[eax].S_DOBJ.dl_index,ID_INCLUDE
	je	CIViewInc
	cmp	cisection.srcfile,0
	je	CIViewInc
	jmp	CIViewSrc
event_edit:
	mov	eax,DLG_CIEdit
	cmp	[eax].S_DOBJ.dl_index,ID_INCLUDE
	je	CIEditInc
	jmp	CIEditSrc
event_save:
	CISaveSection( addr cisection )
	call	puttxtval
	jmp	event_normal
event_dict:
	call	CIDict
	jmp	event_normalput
	ret
event_conf:
	push	esi
	push	edi
	.if	rsopen(IDD_CISetup)
		mov	edi,eax
		.if	CIFindSection( addr cp_conf )
			mov	esi,eax
			strcpy( [edi].S_TOBJ.to_data[16], addr [esi].S_LABEL.srcfile )
			strcpy( [edi].S_TOBJ.to_data[32], addr [esi].S_LABEL.incfile )
			dlinit( edi )
			.if	dlevent(edi)
				strcpy( addr [esi].S_LABEL.srcfile,[edi].S_TOBJ.to_data[16] )
				strcpy( addr [esi].S_LABEL.incfile,[edi].S_TOBJ.to_data[32] )
				strcpy( addr cisrcpath,[edi].S_TOBJ.to_data[16] )
				expenviron( eax )
				strcpy( addr ciincpath,[edi].S_TOBJ.to_data[32] )
				expenviron( eax )
			.endif
		.endif
		dlclose( edi )
	.endif
	pop	edi
	pop	esi
	jmp	event_normal
event_exit:
	mov	eax,_C_ESCAPE
	ret
event_delete:
	call	CIDelSection
event_normalput:
	call	CIPutSection
	call	puttxtval
event_normal:
	mov	eax,_C_NORMAL
	ret
event_tedit PROC USES esi edi
	call	editevent
	mov	esi,eax
	.if	eax == KEY_ENTER
		mov	eax,DLG_CIEdit
		movzx	eax,[eax].S_DOBJ.dl_index
		mov	ecx,eax
		mov	al,CI_LABELS[eax]
		.if	al == 1
			lea	eax,cisection
			.if	ecx
				dec	ecx
				cigetp( eax, ecx )
			.endif
			.if	eax && BYTE PTR [eax]
				CIReadSection( eax )
			.endif
		.elseif al == 3
			call	CIViewInc
		.elseif al == 4
			call	CIViewSrc
		.endif
		xor	esi,esi
	.elseif eax == KEY_F6
		call	CINextFile
		xor	esi,esi
	.endif
	call	gettxtval
	.if	txtvaled != eax
		mov	txtvaled,eax
		call	CIPutSection
	.endif
	call	puttxtval
	mov	eax,esi
	ret
event_tedit ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	.data

MAXLINES	equ 12	; visible lines on screen

d_index		dd ?	; index in buffer
d_section	db MAXLABEL dup(0)
dictdlg		dd ?
dictdlgx	dd ?
dictdlgy	dd ?
dictdlgc	dd ?

; this may be a bit "code-page" spesific..

sort_convertable label BYTE
	db	'’','A'
	db	'','O'
	db	'','A'
	db	'µ','A'
	db	'è','T'
	db	'‘','a'
	db	'›','o'
	db	'†','a'
	db	' ','a'
	db	'ç','t'
	db	'Ð','d'
	db	'”','o'
	db	'¡','i'
	db	'Ö','I'
	db	'‚','e'
	db	'¢','o'
	db	'£','u'
	db	'ì','y'

sort_tablesize = (($ - offset sort_convertable) / 2)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

.code

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

dictput PROC USES esi edi ebx
	mov	ebx,dictdlgx
	mov	edx,dictdlgy
	mov	edi,dictdlgc
	sub	edi,4
	mov	eax,dictdlg
	movzx	ecx,[eax].S_DOBJ.dl_rect.rc_row
	sub	ecx,3
	scputc( ebx, edx, edi,' ' )
	scputc( ebx, edx, 32, 0FAh )
	inc	edx
	.repeat
		scputc( ebx, edx, edi, ' ' )
		inc	edx
	.untilcxz
	mov	edx,dictdlgy
	scputs( ebx, edx, 0, 31, addr d_section )
	mov	esi,d_index
	mov	edi,cilcount
	test	edi,edi
	jz	toend
	sub	edi,esi
	cmp	edi,MAXLINES
	jb	@F
	mov	edi,MAXLINES
     @@:
	add	edx,2
	shl	esi,11
	add	esi,cilabels
	lea	ecx,[ebx+30]
     @@:
	scputs( ebx, edx, 0, 28, esi )
	scputs( ecx, edx, 0, 35, addr [esi].S_LABEL.info )
	inc	edx
	add	esi,sizeof(S_LABEL)
	dec	edi
	jnz	@B
	add	ebx,45
	mov	edx,dictdlgy
	scputf( ebx, edx, 0, 5, "%d", d_index )
	add	ebx,8
	scputf( ebx, edx, 0, 5, "%d", cilcount )
	add	ebx,8
	scputf( ebx, edx, 0, 5, "%d", MAXLABELS )
toend:
	ret
dictput ENDP

sortconvch PROC
	push	ebx
	push	ecx
	mov	ebx,offset sort_convertable
	mov	ecx,sort_tablesize
    sortconvch_find:
	cmp	al,[ebx]
	je	sortconvch_found
	add	ebx,2
	dec	ecx
	jnz	sortconvch_find
    sortconvch_end:
	pop	ecx
	pop	ebx
	ret
    sortconvch_found:
	inc	ebx
	mov	al,[ebx]
	jmp	sortconvch_end
sortconvch ENDP

compare PROC USES esi edi ebx edx ecx
	mov	eax,cilabels
	shl	edi,11
	add	edi,eax
	mov	edx,edi
	shl	esi,11
	add	esi,eax
	mov	ebx,esi
	sub	eax,eax
	mov	al,[edi]
	call	sortconvch
	jz	compare_si
	mov	ah,al
	inc	edi
    compare_si:
	mov	al,[esi]
	call	sortconvch
	jz	compare_start
	inc	esi
	or	ah,ah
	jnz	compare_ahal
	mov	ah,[edi]
	inc	edi
	jmp	compare_ahal
    compare_start:
	or	ah,ah
	jnz	compare_skipdi
    compare_continue:
	or	al,al
	jz	compare_endcmp
	mov	al,[edi]
	call	sortconvch
	mov	ah,al
	inc	edi
    compare_skipdi:
	mov	al,[esi]
	call	sortconvch
	inc	esi
    compare_ahal:
	cmp	ah,al
	je	compare_continue
	sub	al,'A'
	cmp	al,'Z' - 'A' + 1
	sbb	cl,cl
	and	cl,'a' - 'A'
	add	al,cl
	add	al,'A'
	xchg	ah,al
	sub	al,'A'
	cmp	al,'Z' - 'A' + 1
	sbb	cl,cl
	and	cl,'a' - 'A'
	add	al,cl
	add	al,'A'
	cmp	al,ah
	je	compare_continue
	sbb	al,al
	sbb	al,-1
    compare_endcmp:
	cmp	al,0
	jle	compare_end
	memxchg( edx, ebx, sizeof(S_LABEL) )
    compare_end:
	ret
compare ENDP

dictsort PROC USES esi edi ebx
	mov	edx,cilcount
    dictsort_loopg:
	shr	edx,1
	jz	dictsort_end
	mov	ebx,edx
    dictsort_loopc:
	cmp	ebx,cilcount
	jae	dictsort_loopg
	mov	ecx,ebx
	sub	ecx,edx
    dictsort_loopn:
	cmp	ecx,0
	jl	dictsort_endn
	mov	edi,ecx
	mov	esi,ecx
	add	esi,edx
	call	compare
	jle	dictsort_endn
	sub	ecx,edx
	jmp	dictsort_loopn
    dictsort_endn:
	inc	ebx
	jmp	dictsort_loopc
    dictsort_end:
	ret
dictsort ENDP

dictfind PROC USES esi edi ebx eax
	mov	eax,edi
	sub	eax,dictdlgx
	mov	ecx,eax
	mov	esi,d_index
	mov	edi,cilcount
	test	edx,edx			; if (DX == 0) search from start
	jnz	dictfind_loop		; (case BKSP)
	xor	esi,esi
	inc	ch
    dictfind_loop:
	cmp	esi,edi			; search from current to end
	jnb	dictfind_start
	mov	ebx,esi
	shl	ebx,11
	add	ebx,cilabels
	push	edi
	mov	edi,offset d_section
	mov	dl,cl
    dictfind_cmp:
	mov	al,[ebx]
	call	sortconvch
	mov	ah,al
	mov	al,[edi]
	call	sortconvch
	inc	edi
	inc	ebx
	or	ax,2020h
	cmp	al,ah
	jne	dictfind_next
	dec	dl
	jnz	dictfind_cmp
	pop	edi
    dictfind_match:
	mov	d_index,esi
	mov	eax,1
	jmp	dictfind_end
    dictfind_next:
	pop	edi
	inc	esi
	jmp	dictfind_loop
    dictfind_start:
	xor	eax,eax
	mov	esi,eax
	test	ch,ch
	jnz	dictfind_end
	inc	ch
	mov	edi,d_index
	cmp	esi,edi
	jb	dictfind_loop
    dictfind_end:
	test	eax,eax
	ret
dictfind ENDP

dictinitdlg PROC
	rsopen( IDD_CIDict )
	jz	@F
	mov	dictdlg,eax
	movzx	edx,[eax].S_DOBJ.dl_rect.rc_x
	add	edx,2
	mov	dictdlgx,edx
	movzx	edx,[eax].S_DOBJ.dl_rect.rc_col
	mov	dictdlgc,edx
	movzx	edx,[eax].S_DOBJ.dl_rect.rc_y
	inc	edx
	mov	dictdlgy,edx
	dlshow( eax )
	inc	eax
     @@:
	ret
dictinitdlg ENDP

dictopen PROC
	mov	d_index,0
	call	dictsort
	sub	edx,edx
	call	dictfind
	call	dictput
	ret
dictopen ENDP

	.data

cidict_keys label DWORD
	dd 0,		cidict_loop
	dd KEY_ESC,	cidict_toend
	dd KEY_ENTER,	cidict_enter
	dd KEY_KPENTER, cidict_enter
	dd KEY_BKSP,	cidict_bksp
	dd KEY_UP,	cidict_up
	dd KEY_DOWN,	cidict_down
	dd KEY_F5,	cidict_toend
	dd KEY_PGUP,	cidict_PGUP
	dd KEY_PGDN,	cidict_PGDN
cidict_count = ($ - cidict_keys) / 8

	.code

cidict_loop:
	_gotoxy( edi, dictdlgy )
	call	tgetevent		; get key
	mov	ecx,cidict_count	; test key
	xor	ebx,ebx
cidict_next:
	cmp	eax,cidict_keys[ebx]
	je	cidict_found
	add	ebx,8
	dec	ecx
	jnz	cidict_next
	jmp	cidict_find	; add char to search string
cidict_found:
	jmp	cidict_keys[ebx+4]
cidict_toend:
	dlclose( dictdlg )
cidict_pop:
	ret
cidict_enter:
	mov	eax,d_index
	shl	eax,11
	add	eax,cilabels
	memcpy( addr cisection, eax, sizeof(S_LABEL) )
	call	gettxtval
	mov	txtval,eax
	jmp	cidict_toend
cidict_bksp:			; delete char and search from start
	mov	eax,edi
	sub	eax,dictdlgx
	jz	cidict_bksp_null
	dec	edi
	xor	edx,edx
	call	dictfind
	jz	cidict_bksp
	mov	ah,0
	mov	ebx,offset d_section
	dec	eax
	add	ebx,eax
	mov	[ebx],ah
	call	dictput
	jmp	cidict_loop
cidict_bksp_null:
	mov	d_section,0
	mov	edi,dictdlgx
cidict_HOME:
	xor	eax,eax
	mov	d_index,eax
	call	dictput
	jmp	cidict_loop
cidict_find:
	test	al,al
	jz	cidict_loop
	mov	edx,eax
	mov	eax,edi
	sub	eax,dictdlgx
	cmp	eax,MAXLABEL
	jge	cidict_loop
	mov	ebx,eax
	mov	al,dl
	mov	ah,0
	mov	WORD PTR d_section[ebx],ax
	mov	edx,1
	push	ebx
	push	edi
	inc	edi
	call	dictfind
	pop	edi
	pop	ebx
	jz	cidict_notfound
	inc	edi
   cidict_update:
	call	dictput
	jmp	cidict_loop
   cidict_notfound:
	xor	eax,eax
	mov	d_section[ebx],al
	jmp	cidict_loop
cidict_up:
	mov	eax,d_index
	or	eax,eax
	jz	cidict_loop
	dec	eax
	mov	d_index,eax
	jmp	cidict_update
cidict_down:
	mov	eax,cilcount
	dec	eax
	cmp	d_index,eax
	jae	cidict_loop
	inc	d_index
	jmp	cidict_update
cidict_PGUP:
	mov	eax,d_index
	cmp	eax,MAXLINES
	jb	cidict_HOME
	sub	eax,MAXLINES
	mov	d_index,eax
	jmp	cidict_update
cidict_PGDN:
	mov	edx,cilcount
	dec	edx
	mov	eax,d_index
	cmp	edx,eax
	je	cidict_loop
	add	eax,MAXLINES
	cmp	eax,edx
	ja	cidict_END
	mov	d_index,eax
	jmp	cidict_update
cidict_END:
	mov	d_index,edx
	jmp	cidict_update

CIDict	PROC USES esi edi ebx
local	cursor:S_CURSOR
	GetCursor( addr cursor )
	call	CursorOn
	call	dictinitdlg
	jz	@F
	strcpy( addr d_section, addr cisection )
	mov	edi,dictdlgx
	strlen( eax )
	add	edi,eax
	call	dictopen
	jz	quit
	call	cidict_loop
	SetCursor( addr cursor )
     @@:
	ret
   quit:
	dlclose( dictdlg )
	jmp	@B
CIDict	ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PopUp PROC USES esi edi ebx

	local	scword[128]:BYTE
	local	ascii:BYTE

	mov	al,tclrascii
	mov	ascii,al
	.if	!callstack
		.if	malloc( sizeof(S_LABEL) * MAXLABELS )
			mov	cilabels,eax
		.else
			jmp	toend
		.endif
	.endif
	inc	callstack
	lea	ebx,cisection
	.if	scgetword( addr scword )
		.if	callstack == 1
			call	CIRead
		.endif
		.if	rsopen( IDD_CIEdit )
			push	DLG_CIEdit
			push	thelp
			mov	tclrascii,' '
			mov	DLG_CIEdit,eax
			mov	edx,[eax].S_DOBJ.dl_object
			mov	thelp,event_help
			mov	[edx].S_TOBJ.to_data,ebx
			mov	[edx].S_TOBJ.to_proc,event_tedit
			xor	ecx,ecx
			.repeat
				add	edx,sizeof(S_TOBJ)
				cigetp( ebx, ecx )
				mov	[edx].S_TOBJ.to_data,eax
				mov	[edx].S_TOBJ.to_proc,event_tedit
				inc	ecx
			.until	ecx == MAXENTRIES
			mov	[edx+16].S_TOBJ.to_data,offset GCMD_CI
			dlshow( DLG_CIEdit )
			CIReadSection( addr scword )
			rsevent( IDD_CIEdit, DLG_CIEdit )
			dlclose( DLG_CIEdit )
			mov	al,ascii
			mov	tclrascii,al
			pop	eax
			mov	thelp,eax
			pop	eax
			mov	DLG_CIEdit,eax
			mov	txtvaled,0
		.endif
		.if	callstack == 1
			call	CIWrite
		.endif
	.endif
	dec	callstack
	.if	ZERO?
		free( cilabels )
	.endif
toend:
	xor	eax,eax
	ret
PopUp ENDP

CIIdle	PROC
	mov	eax,keyshift
	mov	eax,[eax]
	and	eax,POPUPKEY
	cmp	eax,POPUPKEY
	je	@F
	mov	active,0
	jmp	idle
@@:
	cmp	active,1
	je	toend
	mov	active,1
	call	PopUp
	jmp	toend
idle:
	call	idleh
toend:
	ret
CIIdle	ENDP

OPTION	PROC: PUBLIC

CodeInfo PROC
	mov	eax,tdidle
	mov	idleh,eax
	mov	tdidle,CIIdle
	.if	inientryid( addr cp_CodeInfo, 0 )
		mov	edx,[eax]
		.if	dl == '%' || dl == '\' || dl == '/' || dh == ':'
			strcpy( addr cifile, eax )
		.else
			strfcat( addr cifile, _pgmpath, eax )
		.endif
		expenviron( eax )
		mov	cifileid,0
	.endif
	ret
CodeInfo ENDP

	END
