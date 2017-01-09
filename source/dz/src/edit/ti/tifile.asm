include tinfo.inc
include string.inc
include stdio.inc
include wsub.inc
include direct.inc
include io.inc
include iost.inc
include ini.inc
include stdlib.inc
include ctype.inc

	.code

tigetfile PROC USES ebx ti:PTINFO

	xor	eax,eax ; AX first file
	mov	edx,eax ; DX last file
	xor	ecx,ecx ; CX count
	mov	ebx,ti

	.if	ebx

		.if	[ebx].S_TINFO.ti_flag & _T_FILE

			mov	edx,ebx

			.repeat
				mov	eax,ebx
				mov	ebx,[ebx].S_TINFO.ti_prev

			.until !ebx || ebx == edx

			mov	ebx,eax

			.repeat
				mov	edx,ebx
				mov	ebx,[ebx].S_TINFO.ti_next
				add	ecx,1

			.until !ebx || ebx == eax

			add	ebx,1
		.endif
	.endif
	ret

tigetfile ENDP

tigetfilename PROC USES esi edi ti:PTINFO
	mov	esi,ti
	lea	edi,_bufin
	.if	strfn( strcpy( edi, [esi].S_TINFO.ti_file ) ) == edi
		mov	BYTE PTR [edi],0
		GetCurrentDirectory( _MAX_PATH, edi )
		mov	eax,[esi].S_TINFO.ti_file
	.else
		mov	BYTE PTR [eax-1],0
	.endif
	.if	wdlgopen( edi, eax, 0 )
		strcpy( [esi].S_TINFO.ti_file, eax )
	.endif
	test	eax,eax
	ret
tigetfilename ENDP

tiftime PROC USES esi edi ti:PTINFO
	mov	esi,ti
	.if	osopen( [esi].S_TINFO.ti_file, 0, M_RDONLY, A_OPEN ) == -1
		or	[esi].S_TINFO.ti_flag,_T_MODIFIED
		xor	eax,eax
	.else
		mov	edi,eax
		getftime( edi )
		mov	esi,eax
		_close( edi )
		mov	eax,esi
	.endif
	test	eax,eax
	ret
tiftime ENDP

	ASSUME	edx: PTR S_TINFO
	;
	; Produce output to clipboard or file
	;
tiflushl PROC USES esi edi ebx,
	ti:		PTINFO,
	line_start:	UINT,
	offs_start:	UINT,
	line_end:	UINT,
	offs_end:	UINT
local	line_index:	UINT


	mov	edi,offs_start
	mov	ebx,offs_end
	mov	eax,line_start
	mov	line_index,eax

	.if	!tigetline( ti, eax )

		inc	eax
		stc
	.else
		mov	esi,eax
		strtrim( eax )
		tioptimalfill( ti, esi )

		sub	eax,esi
		add	edi,eax
		add	ebx,eax

		.while	1

			inc	edi
			mov	eax,[edx].ti_bcol
			mov	ecx,line_end

			.if	ecx == line_index
				mov	eax,ebx
			.endif

			.if	edi > eax		; end of selection buffer

				.if	ecx == line_index ; break if last line
					xor	eax,eax
					inc	eax
					clc
					.break
				.endif
				jmp	case_EOL	; end of line
			.endif

			mov	al,[esi+edi-1]
			.switch al

			  .case 0
			   case_EOL:

				inc	line_index
				.if	line_index > ecx
					dec	line_index
					xor	eax,eax
					inc	eax
					clc
					jmp	toend
				.endif

				tigetnextl( ti )
				mov	esi,eax

				.if	ZERO?		; break if last line (EOF)
					xor	eax,eax
					inc	eax
					stc
					jmp	toend
				.endif

				strtrim( esi )
				tioptimalfill( ti, esi )
				mov	esi,eax

				sub	edi,edi
				.if	[edx].ti_flag & _T_USECRLF
					;
					; insert line: 0D0A or 0A
					;
					mov	al,0Dh
					call	oputc
				.endif

				mov	al,0Ah
				call	oputc
				jz	case_EOF	; v3.24 -- eof()
				.endc

			  .case 9
				mov	eax,TIMAXTABSIZE-1
				.while	BYTE PTR [esi+edi] == TITABCHAR
					inc	edi
					dec	eax
					.break .if ZERO?
				.endw
				mov	eax,9
			  .default
				call	oputc
				jz	case_EOF
			.endsw
		.endw
	.endif
toend:				; out:	EAX result
	mov	ecx,edi		;	EDX line index
	mov	edx,line_index	;	ECX line offset
	ret
case_EOF:
	xor	eax,eax
	stc
	jmp	toend
tiflushl ENDP

tiflush PROC USES esi edi ebx ti:PTINFO
local	path[_MAX_PATH]:BYTE
	mov	esi,ti
	lea	edi,path
	.if	getfattr( strcpy( edi, [esi].S_TINFO.ti_file ) ) == -1
		.if	tigetfilename( esi )
			strcpy( edi, eax )
		.else
			xor	edi,edi
		.endif
	.elseif eax & _A_RDONLY
		ermsg( 0, "The file is Read-Only" )
		xor	edi,edi
	.endif

	.if	edi

		ioopen( addr STDO, setfext( edi, ".$$$" ), M_WRONLY, OO_MEM64K )

		.if	SDWORD PTR eax > 0

			mov	ecx,[esi].S_TINFO.ti_lcnt
			dec	ecx
			tiflushl( esi, 0, 0, ecx, -1 )

			.if	ZERO?

				ioclose( addr STDO )
				remove( edi )
				xor	edi,edi
			.else

				ioflush( addr STDO )
				ioclose( addr STDO )
				.if	[esi].S_TINFO.ti_flag & _T_USEBAKFILE
					remove( setfext( edi, ".bak" ) )
					rename( [esi].S_TINFO.ti_file, edi )
					setfext( edi, ".$$$" )
				.endif

				remove( [esi].S_TINFO.ti_file )
				rename( edi, [esi].S_TINFO.ti_file )

				lea	edi,[eax+1]
				and	[esi].S_TINFO.ti_flag,not _T_MODIFIED

				tiftime( esi )
				mov	[esi].S_TINFO.ti_time,eax

				;
				; update .INI file ?
				;
				mov	eax,_argv
				mov	ecx,[eax]

				setfext( strcpy( addr path, ecx ), ".ini" )
				.if !_stricmp( [esi].S_TINFO.ti_file, eax )

					iniclose()
					iniopen( addr path )
				.endif
			.endif
		.else
			xor	edi,edi
		.endif
	.endif
	mov	eax,edi
	test	eax,eax
	ret
tiflush ENDP

;
; 1. Attrib	A -	Set background and forground color
; 2. Control	O -	Set color of CONTROL characters
; 3. Quote	Q -	Set color of quoted text
; 4. Digit	D -	Set color of numbers
; 5. Char	C -	Set color of chars
; 6. String	S -	Set color of string
; 7. Begin	B -	Set color from start of string
; 8. Word	W -	Set color of words
; 9. Nested	N -	Set color of nested strings
;

ID_TYPE		equ 0
ID_ATTRIB	equ 1

ST_ATTRIB	equ 1	; attrib	<at> [<char>]
ST_CHAR		equ 2	; char		<at> <chars>
ST_WORD		equ 3	; word		<at> <words> ...
ST_START	equ 4	; start		<at> <string>
ST_NESTED	equ 5	; nested	<at> <string1> <string2>
ST_CONTROL	equ 6	; control	<at>
;ST_STRING	equ 7	; string	<at> <string>
ST_QUOTE	equ 8	; quote		<at>
ST_NUMBER	equ 9	; number	<at>
ST_COUNT	equ ST_NUMBER

S_RDST		STRUC
st_section	db 64 dup(?)
st_label	db 64 dup(?)
st_sp		dd ?
st_eof		dd ?	; style + SIZE style - 2
st_tinfo	dd ?
S_RDST		ENDS

	.data

cp_style	db 'Style',0
cp_default	db 'style_default',0
cp_typech	db 'aoqdcsbwn',0

	.code

	OPTION	PROC: PRIVATE
	ASSUME	ebp : PTR S_RDST

tireadlabel PROC USES esi edi

	lea	esi,[ebp].st_label
	inientryid( esi, ID_TYPE )
	jz	toend
	mov	edi,[ebp].st_sp
	cmp	edi,[ebp].st_eof
	ja	toend

	mov	ebx,eax
	mov	ah,[ebx]
	or	ah,20h
	xor	ecx,ecx
	xchg	ecx,ebx
	mov	al,cp_typech[ebx]
	.while	al
		.break .if al == ah
		inc	ebx
		mov	al,cp_typech[ebx]
	.endw
	test	al,al
	jz	toend
	lea	eax,[ebx+1]	; store type
	stosb
	mov	ebx,ecx
	movzx	esi,al
	xor	ecx,ecx
	xor	eax,eax
	.repeat
		inc	ebx
		mov	al,[ebx]
		.continue .if al == '_'
	.until !( __ctype[eax+1] & _UPPER or _LOWER or _DIGIT )

	push	esi
	mov	esi,ebx

	.repeat
		lodsb
		.if	al == ' '
			mov	eax,esi
			pop	esi
		.else
			.continue .if al
			pop	esi
			mov	eax,ID_ATTRIB
			mov	edx,ebx
			inientryid( edx, eax )
			mov	ecx,1
			.break .if ZERO?
		.endif
		mov	ebx,eax
		add	eax,2
		push	eax
		mov	eax,[ebx]
		or	eax,2020h
		.if	al == 'x'
			movzx	eax,ah
			mov	ah,__ctype[eax+1]
			and	ah,_HEX or _DIGIT
			.if	!ZERO?
				sub	al,'0'
				and	ah,_DIGIT
				.if	ZERO?
					sub	al,39
				.endif
				mov	ebx,[ebp].st_tinfo
				mov	ah,BYTE PTR [ebx+1].S_TINFO.ti_stat
				and	ah,0F0h
				or	al,ah
			.else
			 get_attrib:
				push	ecx
				xtol  ( ebx )
				pop	ecx
			.endif
		.else
			cmp	ah,'x'
			jne	get_attrib
			movzx	eax,al
			mov	ah,__ctype[eax+1]
			and	ah,_HEX or _DIGIT
			jz	get_attrib
			sub	al,'0'
			and	ah,_DIGIT
			.if	ZERO?
				sub	al,39
			.endif
			shl	al,4
			mov	ebx,[ebp].st_tinfo
			mov	ah,BYTE PTR [ebx].S_TINFO.ti_stat[1]
			and	ah,0Fh
			or	al,ah
		.endif

		stosb	; <type>,<attrib>[,<text>]
		pop	ebx
		.repeat
			mov	ah,[ebx]
			inc	ebx
		.until	ah != ' '
		dec	ebx

		.if	esi == ST_ATTRIB
			mov	esi,[ebp].st_tinfo
			mov	BYTE PTR [esi+1].S_TINFO.ti_stat,al
			.if	ah
				xtol  ( ebx )
				mov	BYTE PTR [esi].S_TINFO.ti_stat,al
				mov	[edi],al
				inc	edi
			.endif
			.break
		.endif

		mov	esi,ecx
		inc	esi
		mov	eax,ebx

		getentryid:

		mov	ebx,esi
		mov	esi,eax
		mov	al,[esi]
		mov	ecx,[ebp].st_eof

		.if	al

			copy_word:
			;-----------------------------------
			; word including ; needs quotes ";"
			; note: must be first and last char
			;-----------------------------------
			movzx	eax,al
			.if	al == '"'
				inc	esi
				mov	ah,al
			.endif
			.repeat
				mov	al,[esi]
				inc	esi
				.if	edi < ecx
					.if	al == ' '
						.if	ah
							stosb
							.continue
						.endif
						mov	BYTE PTR [edi],0
						inc	edi
						mov	al,[esi]
						jmp	copy_word
					.endif

					stosb
					.continue .if al

					.if	ah
						dec	edi
						mov	[edi-1],al
					.endif
				.endif
				.break
			.until	0
		.endif

		mov	esi,ebx
		.break .if esi == 100
		mov	eax,esi
		lea	edx,[ebp].st_label
		inc	esi
		inientryid( edx, eax )
		.break .if ZERO?
		jmp	getentryid
	.until	0

	xor	eax,eax
	.if	[edi-1] != al
		stosb
	.endif
	stosb
	mov	[ebp].st_sp,edi
	inc	eax
toend:
	ret
tireadlabel ENDP

tidosection PROC
	push	esi
	push	edi
	sub	esp,64
	mov	edi,esp
	memcpy( edi, addr [ebp].st_section, 64 )
	xor	esi,esi
	.repeat
		mov	eax,esi
		inc	esi
		lea	edx,[ebp].st_section
		inientryid( edx, eax )
		.break .if ZERO?
		mov	edi,eax
		mov	al,[edi]
		.if	al == '['
			mov	ebx,esi
			mov	edx,edi
			mov	esi,edi
			inc	esi
			lea	edi,[ebp].st_section
			.repeat
				lodsb
				stosb
				.break .if !al
			.until	al == ']'
			dec	edi
			sub	eax,eax
			stosb
			mov	esi,ebx
			mov	edi,edx
			call	tidosection
			mov	edx,esp
			strcpy( addr [ebp].st_section, edx )
		.else
			strcpy( addr [ebp].st_label, edi )
			call	tireadlabel
		.endif
	.until	0
	add	esp,64
	pop	edi
	pop	esi
	ret
tidosection ENDP

	ASSUME	ebp : NOTHING
	OPTION	PROC: PUBLIC

tireadstyle PROC USES esi edi ebx ti:PTINFO

	local	rdst:S_RDST
	local	file[_MAX_PATH]:BYTE

	mov	esi,ti

	push	ebp
	lea	ebp,rdst

	mov	eax,[esi].S_TINFO.ti_style
	mov	[ebp].S_RDST.st_sp,eax
	mov	[ebp].S_RDST.st_tinfo,esi

	mov	edi,eax
	add	eax,STYLESIZE-4
	mov	[ebp].S_RDST.st_eof,eax

	xor	eax,eax
	mov	ecx,STYLESIZE/4
	rep	stosd

	strcpy( addr [ebp].S_RDST.st_section, addr cp_default )
	strcpy( addr file, strfn( [esi].S_TINFO.ti_file ) )
	mov	edi,eax

	strlen( eax )
	lea	edx,cp_style
	.if	BYTE PTR [edi+eax-1] == '.'
		mov	BYTE PTR [edi+eax-1],0
	.endif

	inientry( edx, edi )
	jnz	copy

	strext( edi )			; *.ext
	jz	dosection

	lea	ebx,[eax+1]
	mov	BYTE PTR [eax],0
	inientry( edx, ebx )
	jnz	copy

	inientry( edx, edi )
	jz	dosection
copy:
	lea	ecx,[ebp].S_RDST.st_section
	strcpy( ecx, eax )

dosection:
	call	tidosection
	mov	edi,[ebp].S_RDST.st_sp
	xor	eax,eax
	stosw
	inc	eax
	pop	ebp
	ret
tireadstyle ENDP

	ASSUME	esi: PTR S_TINFO

tiread	PROC USES esi edi ebx ti:PTINFO

	local	line_count

	mov	esi,ti		; v2.49 - auto detect CR/LF
	tiftime( esi )
	mov	[esi].ti_time,eax

	mov	line_count,0
	mov	edi,[esi].ti_bp

	.if	ioopen( addr STDI, [esi].ti_file, M_RDONLY, OO_MEMBUF ) != -1

		mov	eax,DWORD PTR STDI.ios_fsize
		mov	[esi].ti_size,eax

		xor	eax,eax
		.if	eax == DWORD PTR STDI.ios_fsize[4]

			mov	line_count,eax	; file offset (size)
			mov	ebx,eax		; line offset (for tabs)
			mov	edx,edi
			add	edx,[esi].ti_blen
			sub	edx,TIMAXTABSIZE

			.while	1

				.if	edi >= edx

					tirealloc( esi )
					jz	err_filetobig

					sub	edi,eax
					add	edi,[esi].ti_bp
					mov	edx,[esi].ti_bp
					add	edx,[esi].ti_blen
					sub	edx,TIMAXTABSIZE
				 .endif

				call	ogetc
				.break .if ZERO?

				.switch al

				  .case 0
					mov	al,0Ah		; @v3.29 - convert 0 to LF
					or	[esi].ti_flag,_T_MODIFIED

				  .case 0Ah
					mov	ecx,line_count
					add	ecx,ebx
					.if	!ZERO?
						.if	BYTE PTR [edi-1] != 0Dh
							and	[esi].ti_flag,not _T_USECRLF
						.endif
					.endif
					stosb
					inc	line_count
					xor	ebx,ebx
					.endc

				  .case 09h
					.if	!( [esi].ti_flag & _T_USETABS )

						or	[esi].ti_flag,_T_MODIFIED
						mov	al,' '
						stosb

						inc	ebx
						mov	ecx,[esi].ti_tabz
						dec	ecx
						and	ecx,TIMAXTABSIZE-1

						.while	ebx & ecx
							.break .if ebx == [esi].ti_bcol
							stosb
							inc	ebx
						.endw
					.else
						stosb
						inc	ebx
					.endif
					.endc

				  .case 0Dh
					or	[esi].ti_flag,_T_USECRLF

				  .default
					stosb
					inc	ebx
				.endsw

				.if	ebx == [esi].ti_bcol

					.if	[esi].ti_flag & _T_USECRLF
						mov	BYTE PTR [edi],0Dh
						inc	edi
					.endif

					mov	BYTE PTR [edi],0Ah
					inc	edi
					stosb

					push	edx
					.if	!( [esi].ti_flag & _T_MODIFIED )

						or	[esi].ti_flag,_T_MODIFIED

						ermsg ( 0, "Line too long, was truncated" )
					.endif
					pop	edx

					inc	line_count
					xor	ebx,ebx
				.endif
			.endw

		.else

		 err_filetobig:

			ermsg( 0, "File too big, no more memory" )

			mov	line_count,-1
			.if	edi != [esi].ti_bp
				dec	edi
			.endif
		.endif
		mov	BYTE PTR [edi],0
		ioclose( addr STDI )

		inc	line_count
		mov	eax,line_count
		mov	[esi].ti_lcnt,eax
	.endif

	mov	eax,line_count
	test	eax,eax

	ret
tiread	ENDP

	END
