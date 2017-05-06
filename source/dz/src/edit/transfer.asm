include tinfo.inc
include alloc.inc
include string.inc
include stdio.inc
include stdlib.inc
include io.inc
include errno.inc
include direct.inc
include cfini.inc
include wsub.inc
include process.inc

history_event_list PROTO
extern	IDD_DZTransfer:DWORD

	.data

MAXERROR	equ 100		; read .err file from compile

ERFILE		STRUC
m_file		db _MAX_PATH dup(?)
m_info		db 256 dup(?)
m_line		dd ?
ERFILE		ENDS

cp_AltFX	db 'AltF'
cp_AltX		db '1',0
cp_ShiftFX	db 'ShiftF'
cp_ShiftX	db '1',0,0,0
error_count	dd 0
error_id	dd 0
err_file	dd 0
file_ext	dd 0
chars		db "\abcdefghijklmnopqrstuvwxyz0123456789_@",0

	.code

	OPTION PROC: PRIVATE
;
; Parse output from Edit command
;
; WCC	 '<file>(<line>): Error! <id>: <message>'
; JWasm	 '<file>(<line>) : Error <id>: <message>: <text>'
; Masm	 '<file>(<line>) : error <id>: <message>'
;

clear_error PROC
	free(err_file)
	xor eax,eax
	mov err_file,eax
	mov error_id,eax
	mov error_count,eax
	ret
clear_error ENDP

	ASSUME ebx:PTR ERFILE

ParseLine PROC USES ecx edi esi ebx

	mov eax,SIZE ERFILE
	mul error_count
	add eax,err_file
	mov ebx,eax
	mov al,[esi]

	.switch al
	  .case 'A'..'Z'
		or al,20h
	.endsw

	lea edi,chars
	mov ecx,sizeof( chars )
	repne scasb

	.if BYTE PTR [edi-1]

		mov edi,esi

		.if strchr( edi, 40 )

			mov cl,[eax+1]
			.if cl >= '0' && cl <= '9'

				mov esi,eax
				mov BYTE PTR [esi],0
				inc esi
				atol(esi)
				inc esi
				mov [ebx].m_line,eax
				strnzcpy( addr [ebx].m_file, edi, _MAX_PATH-1 )

				.if BYTE PTR [eax+1] != ':'

					GetFullPathName( eax, _MAX_PATH, eax, 0 )
				.endif

				.if strchr( esi, ':' )

					inc eax
					mov esi,eax
				.endif

				strnzcpy( addr [ebx].m_info, esi, 255 )
				inc error_count
			.endif
		.endif
	.endif
	ret
ParseLine ENDP

	ASSUME ebx:NOTHING

ParseOutput PROC USES esi edi ebx

local	pBuffer, bSize, FName[_MAX_PATH]:BYTE

	clear_error()

	mov edx,tinfo
	mov eax,[edx].S_TINFO.ti_file
	lea edi,FName

	.if osopen( setfext( strcpy( edi, strfn( eax ) ), ".err" ), 0, M_RDONLY, A_OPEN ) != -1

		mov esi,eax
		inc _filelength(esi)
		mov bSize,eax

		.if malloc(eax)

			mov pBuffer,eax
			mov edi,eax
			mov ebx,bSize
			dec ebx
			osread( esi, eax, ebx )
			mov BYTE PTR [edi+ebx],0
			_close( esi )

			.if malloc( MAXERROR*SIZE ERFILE )

				mov err_file,eax
				memset( eax, 0, MAXERROR*SIZE ERFILE )
				mov esi,edi
				mov ecx,bSize

				.while	error_count < MAXERROR-1

					mov al,10
					repne scasb
					.break .if !ecx
					mov BYTE PTR [edi-2],0
					ParseLine()
					mov esi,edi
				.endw
				ParseLine()
			.endif
			free(pBuffer)
		.else
			_close(esi)
		.endif
	.endif
	mov eax,error_count
	ret

ParseOutput ENDP

GetMessageId PROC id

	mov eax,err_file
	.if eax

		mov eax,SIZE ERFILE
		mul id
		add eax,err_file
	.endif
	ret

GetMessageId ENDP

tifindfile PROC USES esi edi ebx fname

	.if tigetfile( tinfo )

		mov esi,eax
		.repeat
			.if !_stricmp( fname, [esi].S_TINFO.ti_file )

				mov eax,esi
				.break
			.endif
			xor eax,eax
			cmp esi,edx
			mov esi,[esi].S_TINFO.ti_next
		.until	ZERO?
	.endif
	test eax,eax
	ret

tifindfile ENDP

LoadMessageFile PROC USES esi edi ebx M

	mov esi,tinfo
	mov edi,M

	.repeat
		.if !tifindfile( addr [edi].ERFILE.m_file )

			.break .if !topen( addr [edi].ERFILE.m_file, 0 )

			mov eax,tinfo
		.endif

		.if eax != esi

			mov tinfo,esi
			mov tinfo,titogglefile(esi, eax)
			mov esi,tinfo
		.endif

		mov eax,[edi].ERFILE.m_line
		.if eax

			dec eax
		.endif

		tialigny(esi, eax)
		tiputs(esi)

		lea eax,[edi].ERFILE.m_info
		mov ebx,[esi].S_TINFO.ti_ypos
		add ebx,[esi].S_TINFO.ti_yoff
		inc ebx
		.if ebx > [esi].S_TINFO.ti_rows

			sub ebx,2
		.endif

		scputs( [esi].S_TINFO.ti_xpos, ebx, 4Fh, [esi].S_TINFO.ti_cols, eax )
		xor eax,eax
		mov [esi].S_TINFO.ti_scrc,eax
		inc eax
	.until	1
	ret

LoadMessageFile ENDP

cmspawnini PROC USES ebx IniSection

	local	screen:S_DOBJ,
		cursor:S_CURSOR

	CursorGet( addr cursor )

	mov ebx,tinfo
	.if dlscreen( addr screen, 0007h ) ; edx

		.if [ebx].S_TINFO.ti_flag & _T_MODIFIED


			tiflush( ebx )
		.endif

		.if CFExpandCmd( __srcfile, [ebx].S_TINFO.ti_file, IniSection )

			mov ebx,eax
			dlshow( addr screen )

			.if !CreateConsole( ebx, _P_WAIT )

				mov eax,errno
				mov eax,sys_errlist[eax*4]
				ermsg( 0, "Unable to execute command:\n\n%s\n\n'%s'", __srcfile, eax )
				xor eax,eax
			.endif
		.endif
		dlclose( addr screen )
		mov eax,edx
	.endif
	push eax
	CursorSet( addr cursor )
	pop  eax
	ret

cmspawnini ENDP

tiexecuteini PROC

	push eax
	clear_error()
	pop  eax

	.if cmspawnini( eax )

		.if ParseOutput()

			tinexterror()
		.endif
	.endif
	ret
tiexecuteini ENDP

	OPTION	PROC: PUBLIC

tipreviouserror PROC

	.if error_count

		.if GetMessageId( error_id )

			LoadMessageFile( eax )

			.if error_id

				dec error_id
			.else

				mov eax,error_count
				dec eax
				mov error_id,eax
			.endif
		.endif
	.endif
	mov eax,_TI_CONTINUE
	ret

tipreviouserror ENDP

tinexterror PROC

	.if error_count

		.if GetMessageId( error_id )

			LoadMessageFile( eax )

			mov eax,error_id
			inc eax
			.if eax >= error_count

				xor eax,eax
			.endif
			mov error_id,eax
		.endif
	.endif
	mov eax,_TI_CONTINUE
	ret

tinexterror ENDP

TIAltFx PROC id

	clear_error()

	mov eax,id
	add al,'0'
	mov cp_AltX,al

	.if cmspawnini( addr cp_AltFX )

		.if ParseOutput()

			tinexterror()
		.endif
	.endif
	ret
TIAltFx ENDP

TIShiftFx PROC id

	clear_error()
	mov eax,id
	add al,'0'
	mov cp_ShiftX,al

	.if cmspawnini( addr cp_ShiftFX )

		.if ParseOutput()

			tinexterror()
		.endif
	.endif
	ret
TIShiftFx ENDP

MAXALTCMD	equ 6
MAXSHIFTCMD	equ 9
MAXEXTCMD	equ (MAXALTCMD + MAXSHIFTCMD)

transfer_initsection:

	movzx	eax,[edi].S_DOBJ.dl_index
	inc	eax

	.if eax >= 7

		lea edx,[eax-6+'0']
		mov cp_ShiftX,dl
		lea ebx,cp_ShiftFX
	.else
		lea edx,[eax+1+'0']
		.if eax == 6

		    add edx,2
		.endif
		mov cp_AltX,dl
		lea ebx,cp_AltFX
	.endif

	mov	edx,eax
	shl	edx,4
	mov	esi,[edi+edx].S_TOBJ.to_data
	ret

transfer_edit proc private uses esi ebx

	transfer_initsection()

	.if tgetline( "Edit Transfer Command", esi, 60, 256 )

		.if CFAddSection( ebx )

			CFAddEntryX( eax, "%s=%s", file_ext, esi )
		.endif
		dlinit(edi)
	.endif
	ret

transfer_edit endp

event_transfer proc private uses edi
	.while dlxcellevent() == KEY_F4
	    mov edi,tdialog
	    transfer_edit()
	.endw
	ret
event_transfer endp

titransfer PROC USES esi edi ebx

local	ext[_MAX_PATH]:SBYTE

	mov ebx,tinfo
	mov eax,[ebx].S_TINFO.ti_file
	lea ebx,ext
	mov file_ext,ebx

	.if strrchr( strcpy( ebx, strfn( eax ) ), '.' )

		mov BYTE PTR [eax],0
		inc eax
		.if BYTE PTR [eax]

			strcpy( ebx, eax )
		.endif
	.endif

	.repeat

		.break .if !rsopen(IDD_DZTransfer)
		mov edi,eax
		mov edx,event_transfer
		mov ecx,MAXEXTCMD
		.repeat
			add eax,sizeof(S_TOBJ)
			mov [eax].S_TOBJ.to_proc,edx
		.untilcxz

		mov esi,2
		.while esi < 10

			lea eax,[esi+'0']
			mov cp_AltX,al

			.if CFGetSection( addr cp_AltFX )

				.if CFGetEntry( eax, ebx )

					lea edx,[esi-1]
					.if esi == 9
						sub edx,2
					.endif
					shl edx,4
					strcpy([edi+edx].S_TOBJ.to_data, eax)
				.endif
			.endif

			inc esi
			.if esi == 7

				mov esi,9
			.endif
		.endw

		mov esi,1
		.while esi < 10

			lea eax,[esi+'0']
			mov cp_ShiftX,al

			.if CFGetSection( addr cp_ShiftFX )

				.if CFGetEntry( eax, ebx )

					lea edx,[esi+6]
					shl edx,4
					strcpy([edi+edx].S_TOBJ.to_data, eax)
				.endif
			.endif
			inc esi
		.endw


		dlshow(edi)
		dlinit(edi)

		.while rsevent(IDD_DZTransfer, edi)

			transfer_initsection()
			.if byte ptr [esi] == 0

				transfer_edit()
			.else
				dlclose(edi)
				mov eax,ebx
				tiexecuteini()
				.break(1)
			.endif
		.endw
		dlclose(edi)
		xor eax,eax
	.until	1
	ret

titransfer ENDP

	END
