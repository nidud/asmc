; 7ZA.ASM--
; Copyright (C) 2015 Doszip Developers -- see LICENSE.TXT
;
; This is the "inline" 7za.dll plugin for 7ZA.EXE
;

include doszip.inc

include cfini.inc
include errno.inc
include alloc.inc
include io.inc
include iost.inc
include string.inc
include stdio.inc
include stdlib.inc
include process.inc
include time.inc
include winbase.inc

IDTYPE_7Z	equ 0
IDTYPE_GZ	equ 1
IDTYPE_BZ2	equ 2
IDTYPE_CAB	equ 3
IDTYPE_XZ	equ 4
IDTYPE_TAR	equ 5
IDTYPE_LZMA	equ 6

TYPE_7Z		equ 00007A37h
TYPE_GZ		equ 00008B1Fh
TYPE_BZ2	equ 00005A42h
TYPE_CAB	equ 4643534Dh
TYPE_XZ		equ 587A37FDh

	.data

externdef	IDD_ConfirmAddFiles:DWORD
externdef	cp_ziplst:BYTE

$LIST		dd 0
$PROG		db "7ZA.EXE",0

; default value

ARG_01		db '7za l -y',0		; 01 - Read
ARG_02		db '7za x -y',0		; 02 - Copy - e if not include subdir
ARG_03		db '7za a -y',0		; 03 - Add
ARG_06		db '7za d -y',0		; 06 - Delete
ARG_08		db '7za m -e -y',0	; 08 - Edit
ARG_09		db '7za e -y',0		; 09 - View or copy single file (02)

; format strings

CPF_02		db ' %s -o"%s"',0	; <archive> -o<outpath> @list
CPF_03		db ' %s',0		; <archive> @list

; from [7ZA] config value, or default value

CMD_00		dd 0	; ARG_09 - if files only (02)
CMD_01		dd 0
CMD_02		dd 0
CMD_03		dd 0
CMD_06		dd 0
CMD_08		dd 0
CMD_09		dd 0

config_label	dd ARG_09, CMD_00
		dd ARG_01, CMD_01
		dd ARG_02, CMD_02
		dd ARG_03, CMD_03
		dd 0,0
		dd 0,0
		dd ARG_06, CMD_06
		dd 0,0
		dd ARG_08, CMD_08
		dd ARG_09, CMD_09

; file types

NUMTYPE		equ 7

typ0		db 0
typ1		db ' -tgzip',0
typ2		db ' -tbzip2',0
typ3		db ' -tcab',0
typ4		db ' -txz',0
typ5		db ' -ttar',0
typ6		db ' -tlzma',0

label_types	dd typ0,typ1,typ2,typ3,typ4,typ5,typ6


;-----------------------------
; Flag bits for function calls
;-----------------------------

_DLLF_READ	equ 0001h
_DLLF_COPY	equ 0002h
_DLLF_ADD	equ 0004h
_DLLF_MOVE	equ 0008h
_DLLF_MKDIR	equ 0010h
_DLLF_DELETE	equ 0020h
_DLLF_RENAME	equ 0040h
_DLLF_EDIT	equ 0080h
_DLLF_VIEW	equ 0100h
_DLLF_ATTRIB	equ 0200h
_DLLF_ENTER	equ 0400h
_DLLF_TEST	equ 0800h
_DLLF_GLOBAL	equ 2000h
_DLLF_EDITOR	equ 4000h
					;  test,enter,attrib,view,edit,ren,del,mkdir,move,add,copy,read
label_flag	dd 100100100111B	;   x		     x		   x		  x   x	   x
		dd 100100000011B	;   x		     x				      x	   x
		dd 100100000011B	;   x		     x				      x	   x
		dd 100100000011B	;   x		     x				      x	   x
		dd 100100000011B	;   x		     x				      x	   x
		dd 100100100111B	;   x		     x		   x		  x   x	   x
		dd 100100000011B	;   x		     x				      x	   x

$TYPE		dd typ0			; current type string
$FLAG		dd 100100100111B	; current type flag

modified	db 1
startstring	db '------------------- '
quote		db '"',0


	.code


;-------------------------------------------------------------------------
; Read
;-------------------------------------------------------------------------

lline_getdate:	; 2008-04-28
	atol( edi )
	push	eax
	atol( addr [edi+5] )
	push	eax
	atol( addr [edi+8] )
	mov	dl,al
	pop	eax
	mov	dh,al
	pop	eax
	sub	ax,DT_BASEYEAR
	shl	ax,9
	xchg	ax,dx
	mov	cl,al
	mov	al,ah
	xor	ah,ah
	shl	ax,5
	xchg	ax,dx
	or	ax,dx
	or	al,cl
	ret

lline_gettime:	; 02:19:00
	push	ebx
	invoke	atol,addr [edi+11]
	push	eax
	invoke	atol,addr [edi+14]
	push	eax
	invoke	atol,addr [edi+17]
	pop	ecx
	pop	ebx
	mov	ch,bl
	mov	dh,al
	xor	eax,eax ; DH = second
	mov	al,dh	; CH = hour
	shr	ax,1	; CL = minute
	mov	edx,eax
	mov	al,ch
	mov	ch,ah
	shl	cx,5
	shl	eax,11
	or	eax,ecx
	or	eax,edx ; hhhhhmmmmmmsssss
	pop	ebx
	ret

lline_getattrib:
	xor	eax,eax
	cmp	BYTE PTR [edi+20],'D'
	jne	@F
	mov	al,_A_SUBDIR
@@:
	cmp	BYTE PTR [edi+21],'R'
	jne	@F
	or	al,_A_RDONLY
@@:
	cmp	BYTE PTR [edi+22],'H'
	jne	@F
	or	al,_A_HIDDEN
@@:
	cmp	BYTE PTR [edi+23],'S'
	jne	@F
	or	al,_A_SYSTEM
@@:
	cmp	BYTE PTR [edi+24],'A'
	jne	@F
	or	al,_A_ARCH
@@:
	ret

lline_findfirst:
	call	ogets
	jz	@B
	cmp	BYTE PTR [edi],'-'
	jne	lline_findfirst
	invoke	strncmp,edi,addr startstring, offset quote - offset startstring
	test	eax,eax
	jnz	lline_findfirst
;
;   Date      Time    Attr	   Size	  Compressed  Name
;------------------- ----- ------------ ------------  ------------------------
;		     .....		      790027  7z922.tar
;------------------- ----- ------------ ------------  ------------------------
;					      790027  1 files, 0 folders
;
lline_findnext:
	call	ogets
	jz	lline_findnext_fail
	mov	al,[edi]	; 2008-04-28
	cmp	al,' '
	jne	@F
	strlen( edi )
	cmp	eax,52
	jb	lline_findnext_fail
	jmp	lline_findnext_set
@@:
	cmp	al,'0'
	jb	lline_findnext_fail
	cmp	al,'9'
	ja	lline_findnext_fail
	cmp	BYTE PTR [edi+4],'-'
	jne	lline_findnext_fail
lline_findnext_set:
	xor	eax,eax
	mov	[edi+4],al
	mov	[edi+7],al
	mov	[edi+10],al
	mov	[edi+13],al
	mov	[edi+16],al
	mov	[edi+19],al
	mov	[edi+38],al
	mov	[edi+51],al
	mov	al,[edi+52]
	or	al,al
	ret
lline_findnext_fail:
	xor	eax,eax
	ret

createlist PROC PRIVATE USES esi edi wsub

local	batf[256]:BYTE
local	arch[256]:BYTE
local	cmd[512]:BYTE

	.if $LIST == 0
		.if salloc( strfcat( addr cmd, envtemp, "ziplst.tmp" ) )
			mov	$LIST,eax
		.endif
	.endif
	mov	esi,wsub
	mov	arch,'"'
	strfcat( addr arch+1, [esi].S_WSUB.ws_path, [esi].S_WSUB.ws_file )
	strcat( eax, addr quote )
	strfcat( addr batf, envtemp, "dzcmd.bat" )
	mov	esi,eax
	osopen( eax, 0, M_WRONLY, A_CREATETRUNC )
	mov	edi,eax
	inc	eax
	.if eax
		sprintf( addr cmd, "%s%s > %s\r\n", CMD_01, addr arch, $LIST )
		oswrite( edi, addr cmd, strlen( addr cmd ) )
		_close( edi )
		CreateConsole( addr batf, _P_WAIT or CREATE_NEW_CONSOLE )
		remove( addr batf )
		mov _diskflag,0
		mov eax,1
	.endif
	ret
createlist ENDP

;
; Returns 0 if entry not part of basepath,
; else _A_ARCH or _A_SUBDIR.
;
testentryname PROC PRIVATE USES esi edi ebx wsub, ename
	mov	ebx,wsub
	strlen( [ebx].S_WSUB.ws_arch )
	mov	edi,eax
	mov	esi,ename
	strlen( esi )
	cmp	edi,eax
	jae	testentryname_fail
	cmp	edi,0
	jle	testentryname_flag
	_strnicmp( ename, [ebx].S_WSUB.ws_arch, edi )
	test	eax,eax
	jnz	testentryname_fail
	mov	eax,edi
	mov	al,[esi+eax]
	cmp	al,'\'
	jne	testentryname_fail
    testentryname_copy:
	mov	eax,esi
	add	eax,edi
	inc	eax
	strcpy( esi, eax )
    testentryname_comma:
	cmp	BYTE PTR [esi],','
	jne	testentryname_flag
	mov	eax,esi
	inc	eax
	strcpy( esi, eax )
	jmp	testentryname_comma
    testentryname_flag:
	mov	edi,_A_ARCH
    testentryname_loop:
	lodsb
	test	al,al
	jz	testentryname_find
	cmp	al,'\'
	jne	testentryname_loop
	xor	eax,eax
	mov	[esi-1],al
	mov	edi,_A_SUBDIR
    testentryname_find:
	mov	esi,1
	cmp	[ebx].S_WSUB.ws_count,esi
	jbe	testentryname_ok
    testentryname_cmp:
	cmp	[ebx].S_WSUB.ws_count,esi
	jbe	testentryname_ok
	mov	eax,[ebx].S_WSUB.ws_fcb
	mov	eax,[eax+esi*4]
	add	eax,S_FBLK.fb_name
	_stricmp( ename, eax )
	test	eax,eax
	jz	testentryname_fail
	inc	esi
	jmp	testentryname_cmp
    testentryname_ok:
	mov	eax,edi
	test	eax,eax
    testentryname_end:
	ret
    testentryname_fail:
	xor	eax,eax
	jmp	testentryname_end
testentryname ENDP

warcread PROC USES esi edi ebx wsub

local	fblk, fattrib, ename

	searchp( addr $PROG )
	test eax,eax
	jz error

	mov esi,wsub
	wsfree( esi )
	.if fbupdir( _W_ARCHEXT )
		mov [esi].S_WSUB.ws_count,1
		mov ebx,[esi].S_WSUB.ws_fcb
		mov [ebx],eax
		.if modified
			createlist( esi )
		.endif
		.if ogetl( $LIST, entryname, 512 )
			mov edi,entryname
			lea eax,[edi+53]
			mov ename,eax
			call lline_findfirst
			.while	eax
				.if testentryname( esi, ename )
					mov fattrib,eax
					.if al & _A_SUBDIR || cmpwarg( ename, [esi].S_WSUB.ws_mask)
						strlen( ename )
						add	eax,SIZE S_FBLK
						.break .if !malloc( eax )
						mov	ecx,fattrib
						mov	fblk,eax
						or	ecx,_FB_ARCHEXT
						mov	[eax].S_FBLK.fb_flag,ecx
						add	eax,S_FBLK.fb_name
						strcpy( eax, ename )
						_atoi64( addr [edi+26] )
						mov	ebx,fblk
						mov	DWORD PTR [ebx].S_FBLK.fb_size,eax
						mov	DWORD PTR [ebx].S_FBLK.fb_size+4,edx
						call	lline_getdate
						push	eax
						call	lline_gettime
						pop	ecx
						shl	ecx,16
						or	eax,ecx
						mov	ebx,fblk
						mov	[ebx].S_FBLK.fb_time,eax
						call	lline_getattrib
						mov	ebx,fblk
						or	[ebx],al
						mov	eax,[esi].S_WSUB.ws_count
						shl	eax,2
						add	eax,[esi].S_WSUB.ws_fcb
						mov	[eax],ebx
						inc	[esi].S_WSUB.ws_count
						mov	eax,[esi].S_WSUB.ws_count
						.if eax >= [esi].S_WSUB.ws_maxfb
						    .break .if !wsextend(esi)
						.endif
					.endif
				.endif
				call lline_findnext
			.endw
			ioclose( addr STDI )
			mov modified,0
			mov eax,[esi].S_WSUB.ws_count
		.endif
	.endif
toend:
	ret
error:
	ermsg( 0, "File not found:\n%s", addr $PROG )
	mov eax,ER_READARCH
	jmp toend
warcread ENDP

;-------------------------------------------------------------------------
; Copy
;-------------------------------------------------------------------------

warccopy PROC wsub, fblk, outp, subdcount

local	cmd[_MAX_PATH]:BYTE
local	path[_MAX_PATH]:BYTE
local	list[256]:BYTE

	lea esi,cmd
	mov ebx,outp
	;
	; remove '\' from end of outpath (C:\)
	;
	strlen( strcpy( addr path, ebx ) )
	lea ebx,[ebx+eax-1]
	mov eax,'\'
	.if [ebx] == al
		mov [ebx],ah
	.endif
	;
	; make a list file
	;
	mov mklist.mkl_flag,_MKL_MASK
	mov mklist.mkl_count,0
	.if mkziplst_open()
		strcpy( addr list, edx )
		.if	mkziplst()
			xor eax,eax
		.else
			or  eax,mklist.mkl_count
		.endif
	.endif
	.if eax
		mov edi,CMD_00	; singel file (excluding directory)
		.if subdcount
			mov edi,CMD_02
		.endif
		mov ebx,wsub
		sprintf( esi, edi, [ebx].S_WSUB.ws_file, addr path )
		CreateConsole( addr cmd, _P_WAIT or CREATE_NEW_CONSOLE )
		remove( addr list )
		xor eax,eax
	.endif
	ret
warccopy ENDP

;-------------------------------------------------------------------------
; Add
;
; - add files to <archive>\ root directory only
;-------------------------------------------------------------------------

warcadd PROC dest, wsub, fblk

local	cmd[256]:BYTE
local	path[_MAX_PATH]:BYTE
local	list[256]:BYTE


	.if $FLAG & _DLLF_ADD

		mov eax,1
		mov edx,dest
		mov edx,[edx].S_WSUB.ws_arch
		.if [edx] != ah
			rsmodal( IDD_ConfirmAddFiles ) ; OK == 1, else 0
		.endif

		.if eax
			mov mklist.mkl_flag,_MKL_MASK
			mov mklist.mkl_count,0
			.if mkziplst_open()
				strcpy( addr list, edx )
				.if mkziplst()
					xor eax,eax
				.else
					mov eax,mklist.mkl_count
				.endif
			.endif
			.if eax
				mov edx,dest
				strfcat( addr path, [edx].S_WSUB.ws_path, [edx].S_WSUB.ws_file )
				sprintf( addr cmd, CMD_03, eax )
				CreateConsole( addr cmd, _P_WAIT or CREATE_NEW_CONSOLE )
				remove( addr list )
				inc modified
			.endif
		.endif
	.endif
	xor eax,eax
	ret
warcadd ENDP

;-------------------------------------------------------------------------
; Delete
;-------------------------------------------------------------------------

warcdelete PROC USES esi edi ebx wsub, fblk

local	cmd[256]:BYTE
local	list[256]:BYTE

	.if $FLAG & _DLLF_DELETE
		;----------------------------
		; use mask in directory\[*.*]
		;----------------------------
		mov mklist.mkl_flag,_MKL_MASK
		mov mklist.mkl_count,0
		.if mkziplst_open()
			strcpy( addr list, edx )
			.if mkziplst()
				xor eax,eax
			.else
				or  eax,mklist.mkl_count
			.endif
		.endif
		.if eax
			mov esi,wsub
			mov edi,fblk
			mov ecx,[edi].S_FBLK.fb_flag
			lea eax,[edi].S_FBLK.fb_name
			.if confirm_delete_file( eax, ecx ) && eax != -1
				sprintf( addr cmd, CMD_06, [esi].S_WSUB.ws_file, addr list )
				CreateConsole( addr cmd, _P_WAIT or CREATE_NEW_CONSOLE )
				remove( addr list )
				inc modified
			.endif
		.endif
	.endif
	xor eax,eax
	ret
warcdelete ENDP

;-------------------------------------------------------------------------
; View
;-------------------------------------------------------------------------

tview	PROTO :DWORD, :DWORD

warcview PROC USES esi edi ebx wsub, fblk

local	fbname[_MAX_PATH]:BYTE
local	cmd[_MAX_PATH]:BYTE

	mov esi,wsub
	mov edx,fblk
	lea edi,cmd
	lea ebx,[edx].S_FBLK.fb_name

	strfcat( addr fbname, [esi].S_WSUB.ws_arch, ebx )
	sprintf( edi, CMD_09, [esi].S_WSUB.ws_file, envtemp, eax )
	CreateConsole( edi, _P_WAIT or CREATE_NEW_CONSOLE )
	.if filexist( strfcat( edi, envtemp, ebx ) ) == 1
		tview ( edi, 0 )
		remove( edi )
		mov _diskflag,0
	.endif
	ret
warcview ENDP

;-------------------------------------------------------------------------
; Test
;-------------------------------------------------------------------------

warcgettype PROC PRIVATE fblk, sign

	mov eax,sign
	mov edx,fblk

	.if eax == TYPE_CAB
		mov eax,IDTYPE_CAB+1
	.elseif eax == TYPE_XZ
		mov eax,IDTYPE_XZ+1
	.else
		and eax,0000FFFFh
		.if eax == TYPE_7Z
			mov eax,IDTYPE_7Z+1
		.elseif eax == TYPE_GZ
			mov eax,IDTYPE_GZ+1
		.elseif eax == TYPE_BZ2
			mov eax,IDTYPE_BZ2+1
		.elseif strext( addr  [edx].S_FBLK.fb_name )
			mov edx,eax
			.if !_stricmp( eax, ".tar" )
				mov eax,IDTYPE_TAR+1
			.elseif !_stricmp( edx, ".lzma" )
				mov eax,IDTYPE_LZMA+1
			.else
				xor eax,eax
			.endif
		.endif
	.endif
	ret
warcgettype ENDP

warctest PROC USES esi edi ebx fblk, sign

	local	list[256]:BYTE

	searchp( addr $PROG )
	test	eax,eax
	jz	toend

	lea	ebx,list
	mov	eax,"@ "
	mov	[ebx],eax
	strfcat( addr [ebx+2], envtemp, addr cp_ziplst )

	.if warcgettype( fblk, sign )
		lea	edx,[eax-1]
		mov	eax,label_types[edx*4]
		mov	$TYPE,eax
		mov	eax,label_flag[edx*4]
		mov	$FLAG,eax
		mov	ecx,1		; READ
		call	find
		strcat( eax, " " )
		mov	ecx,0
		call	find
		strcat( eax, addr CPF_02 )
		strcat( eax, ebx )
		mov	ecx,2		; COPY
		call	find
		strcat( eax, addr CPF_02 )
		strcat( eax, ebx )
		mov	ecx,3		; ADD
		call	find
		strcat( eax, addr CPF_03 )
		strcat( eax, ebx )
		mov	ecx,6		; DELETE
		call	find
		strcat( eax, addr CPF_03 )
		strcat( eax, ebx )
		mov	ecx,8		; EDIT
		call	find
		strcat( eax, " %s %s" )
		mov	ecx,9		; VIEW
		call	find
		strcat( eax, " %s -o%s %s" )
		mov	eax,1
		mov	modified,al
	.endif
toend:
	ret
find:
	lea edi,config_label[ecx*8]
	.if !CFGetSectionID( "7ZA", ecx )
		mov eax,[edi]
	.endif
	mov edi,[edi+4]
	mov ecx,[edi]
	.if !ecx
		push eax
		malloc( 128 )
		mov [edi],eax
		mov ecx,eax
		pop eax
	.endif
	strcat( strcpy( ecx, eax ), $TYPE )
	retn
warctest ENDP

	END
