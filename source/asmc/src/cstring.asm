include stdio.inc
include string.inc
include ctype.inc

include asmc.inc
include token.inc

MACRO_CSTRING	equ 1

externdef	list_pos:DWORD
AddLineQueue	PROTO :LPSTR

str_item	STRUC
string		LPSTR ?
next		dd ?
index		dd ?
str_item	ENDS
LPSSTR	TYPEDEF PTR str_item

	.code

	OPTION PROCALIGN:4

InsertLine PROC PRIVATE USES esi line:LPSTR
  local oldstat:input_status

	PushInputStatus( addr oldstat )
	mov	esi,ModuleInfo.GeneratedCode
	mov	ModuleInfo.GeneratedCode,0
	strcpy( ModuleInfo.currsource, line )
	Tokenize( ModuleInfo.currsource, 0, ModuleInfo.tokenarray, TOK_DEFAULT )
	mov	ModuleInfo.token_count,eax
	ParseLine( ModuleInfo.tokenarray )
	mov	ModuleInfo.GeneratedCode,esi
	mov	esi,eax
	PopInputStatus( addr oldstat )
	mov	eax,esi
	ret

InsertLine ENDP

ParseCString PROC PRIVATE USES esi edi ebx lbuf:LPSTR, buffer:LPSTR, string:LPSTR
  local sbuf[MAX_LINE_LEN]:SBYTE,	; "binary" string
	stroffset:PTR SBYTE

	mov	esi,string
	mov	edi,buffer
	lea	edx,sbuf
	xor	ebx,ebx
	mov	[edx],ebx
	movsb

	.while	BYTE PTR [esi]

		mov	al,[esi]
		;
		; escape char \\
		;
		.if	al == '\'

			add	esi,1
			mov	al,[esi]
			sub	al,'A'
			cmp	al,'Z' - 'A' + 1
			sbb	ah,ah
			and	ah,'a' - 'A'
			add	al,ah
			add	al,'A'
			movzx	eax,al
			.switch eax
			  .case 'a'
				mov	BYTE PTR [edx],7
				mov	eax,20372C22h	; <",7 >
				jmp	case_format
			  .case 'b'
				mov	BYTE PTR [edx],8
				mov	eax,20382C22h	; <",8 >
				jmp	case_format
			  .case 'f'
				mov	BYTE PTR [edx],12
				mov	eax,32312C22h	; <",12>
				jmp	case_format
			  .case 'n'
				mov	BYTE PTR [edx],10
				mov	eax,30312C22h	; <",10>
				jmp	case_format
			  .case 't'
				mov	BYTE PTR [edx],9
				mov	eax,20392C22h	; <",9 >
			   case_format:
				mov	ecx,buffer
				add	ecx,1
				.if	( ecx == edi && al == [edi-1] ) \
					|| ( al == [edi-1] && ah == [edi-2] )
					shr	eax,16
					sub	edi,1
					stosw
				.else
					stosd
				.endif
				mov	eax,222Ch
				.if	BYTE PTR [edi-1] == ' '
					sub	edi,1
				.endif
				stosb
				mov	[edi],ah
				.endc
			  .case 'r'
				mov	BYTE PTR [edx],13
				mov	eax,33312C22h	; <",13>
				jmp	case_format
			  .case 'v'
				mov	BYTE PTR [edx],11
				mov	eax,31312C22h	; <",11>
				jmp	case_format
			  .case 27h
				mov	BYTE PTR [edx],39
				mov	eax,39332C22h	; <",39>
				jmp	case_format
			  .case 'x'
				movzx	eax,BYTE PTR [esi+1]
				.if	__ctype[eax+1] & _HEX
					add	esi,1
					and	eax,not 30h
					bt	eax,6
					sbb	ecx,ecx
					and	ecx,55
					sub	eax,ecx
					movzx	ecx,BYTE PTR [esi+1]
					.if	__ctype[ecx+1] & _HEX
						add	esi,1
						shl	eax,4
						and	ecx,not 30h
						bt	ecx,6
						sbb	ebx,ebx
						and	ebx,55
						sub	ecx,ebx
						add	eax,ecx
					.endif
					mov	[edi],al
					mov	[edx],al
				.else
					mov	BYTE PTR [edi],'x'
					mov	BYTE PTR [edx],'x'
				.endif
				.endc
			  .case '"'			; <",'"',">
				mov	ah,','
				mov	ecx,buffer
				add	ecx,1
				;
				; db '"',xx",'"',0
				;
				.if	( ecx == edi && al == [edi-1] ) \
					|| ( al == [edi-1] && ah == [edi-2] )
					sub	edi,1
				.else
					stosw
				.endif
				mov	eax,2C272227h
				stosd
				mov	al,'"'
			  .default
				mov	[edi],al
				mov	[edx],al
				.endc
			.endsw
		.elseif al == '"'
			stosb
			.if	BYTE PTR [esi]
				add	esi,1
			.endif
			.break
		.else
			mov	[edi],al
			mov	[edx],al
		.endif
		add	edi,1
		add	edx,1
		.if	BYTE PTR [esi]
			add	esi,1
		.endif
	.endw
	xor	eax,eax
	mov	[edi],al
	mov	[edx],al
	.if	DWORD PTR [edi-3] == 22222Ch
		mov	BYTE PTR [edi-3],0
	.endif
	mov	stroffset,esi

	strlen( addr sbuf )
	mov	ebx,eax
	mov	esi,ModuleInfo.StrStack
	xor	edi,edi

	.while	esi

		mov	edx,[esi].str_item.string
		.if	strlen( edx ) >= ebx

			.if	eax > ebx

				add	edx,eax
				sub	edx,ebx
			.endif
			.if	!strcmp( addr sbuf, edx )

				sub	edx,[esi].str_item.string
				mov	eax,[esi].str_item.index
				.if	edx

					.if	ModuleInfo.wstring
						add	edx,edx
					.endif
					sprintf( lbuf, "DS%04X[%d]", eax, edx )
				.else

					sprintf( lbuf, "DS%04X", eax )
				.endif
				xor	eax,eax
				jmp	toend
			.endif
		.endif
		add	edi,1
		mov	esi,[esi].str_item.next
	.endw

	sprintf( lbuf, "DS%04X", edi )
	add	ebx,sizeof(str_item) + 1
	LclAlloc( ebx )
	mov	ecx,ModuleInfo.StrStack
	mov	[eax].str_item.next,ecx
	mov	ModuleInfo.StrStack,eax
	lea	ecx,[eax+sizeof(str_item)]
	mov	[eax].str_item.string,ecx
	mov	[eax].str_item.index,edi
	strcpy( ecx, addr sbuf )
toend:
	mov	edx,stroffset
	ret
ParseCString ENDP

GenerateCString PROC USES esi edi ebx i, tokenarray:PTR asm_tok

  local rc, q, e, equal, new_str
  local b_label[64]:BYTE
  local b_seg[64]:BYTE
  local b_line[MAX_LINE_LEN]:BYTE
  local b_data[MAX_LINE_LEN]:BYTE
  local buffer[MAX_LINE_LEN]:BYTE
  local lineflags:BYTE
  local brackets:BYTE

	xor	eax,eax
	mov	rc,eax

	.if	ModuleInfo.asmc_syntax && Parse_Pass == PASS_1
		;
		; need "quote"
		;
		mov	ebx,i
		mov	esi,tokenarray
		shl	ebx,4
		add	ebx,esi
		mov	brackets,al
		mov	edx,eax
		;
		; proc( "", ( ... ), "" )
		;
		.while	[ebx].asm_tok.token != T_FINAL

			mov	ecx,[ebx].asm_tok.string_ptr
			movzx	ecx,BYTE PTR [ecx]

			.if ecx == '"'
				mov eax,1
				.break
			.elseif ecx == ')'
				.break .if !brackets
				sub brackets,1
			.elseif ecx == '('
				add brackets,1
				;
				; need one open bracket
				;
				add edx,1
			.endif
			add ebx,16
		.endw

		test	eax,eax
		jz	toend
		xor	eax,eax
		test	edx,edx
		jz	toend

		inc	eax
		mov	rc,eax
		mov	edi,LineStoreCurr
		add	edi,line_item.line
		strcpy( addr b_line, edi )
		mov	BYTE PTR [edi],';'
		strcmp( eax, [esi].asm_tok.tokpos )
		mov	equal,eax
		mov	al,ModuleInfo.line_flags
		mov	lineflags,al

		.while	[ebx].asm_tok.token != T_FINAL

			mov	ecx,[ebx].asm_tok.tokpos
			mov	al,[ecx]
			.if	al == '"'
				mov	edi,ecx
				mov	esi,ecx
				mov	q,ebx
				lea	eax,[ebx+16]
				mov	e,eax
				ParseCString( addr b_label, addr buffer, esi )
				mov	new_str,eax
				mov	esi,edx

				.if	equal
					;
					; strip "string" from LineStoreCurr
					;
					sub	edx,edi
					memcpy( addr b_data, edi, edx )
					mov	BYTE PTR [eax+edx],0
					.if	strstr( addr b_line, eax )
						mov	edi,eax
						lea	eax,[edi+edx]
						M_SKIP_SPACE ecx, eax
						.if	ecx != ',' && ecx != ')'
							.if	strrchr( addr [edi+1], '"' )
								add	eax,1
							.endif
						.endif
						.if	eax
							lea	ecx,b_data
							strcpy( ecx, eax )
							strcpy( edi, "addr " )
							strcat( edi, addr b_label )
							strcat( edi, addr b_data )
						.endif
					.endif
				.endif

				.if	new_str

					.if	ModuleInfo.wstring

						sprintf( addr b_data, " %s dw %s,0", addr b_label, addr buffer )
					.else

						sprintf( addr b_data, " %s db %s,0", addr b_label, addr buffer )
					.endif

				.elseif ModuleInfo.list

					and ModuleInfo.line_flags,NOT LOF_LISTED
				.endif

				mov	eax,q
				mov	eax,[eax].asm_tok.tokpos
				mov	BYTE PTR [eax],0
				mov	eax,tokenarray
				mov	ecx,[eax].asm_tok.tokpos
				strcat( strcpy( addr buffer, ecx ), "addr " )
				lea	ecx,b_label
				strcat( eax, ecx )
				M_SKIP_SPACE ecx, esi
				.if	ecx
					strcat( strcat( eax, " " ), esi )
				.endif

				.if	new_str
					mov	eax,ModuleInfo.currseg
					mov	ecx,[eax].asym._name
					strcat( strcpy( addr b_seg, ecx ), " segment" )
					.break	.if InsertLine( ".data" )
					.break	.if InsertLine( addr b_data )
					.break	.if InsertLine( "_DATA ends" )
					.break	.if InsertLine( addr b_seg )
					mov	rc,eax
				.endif
				strcpy( ModuleInfo.currsource, addr buffer )
				Tokenize( ModuleInfo.currsource, 0, tokenarray, TOK_DEFAULT )
				mov	ModuleInfo.token_count,eax
				mov	eax,i
				shl	eax,4
				add	eax,tokenarray
				mov	q,eax
			.elseif al == ')'
				.break .if !brackets
				sub	brackets,1
				.break .if ZERO?
			.elseif al == '('
				add	brackets,1
			.endif
			add	ebx,16
		.endw
		.if	equal == 0
			StoreLine( ModuleInfo.currsource, list_pos, 0 )
		.else
			mov	ebx,ModuleInfo.GeneratedCode
			mov	ModuleInfo.GeneratedCode,0
			StoreLine( addr b_line, list_pos, 0 )
			mov	ModuleInfo.GeneratedCode,ebx
		.endif
		mov	al,lineflags
		mov	ModuleInfo.line_flags,al
	.endif
	mov	eax,rc

toend:
	ret
GenerateCString ENDP

ifdef MACRO_CSTRING

CString PROC USES esi edi ebx buffer:LPSTR, tokenarray:PTR asm_tok

  local string[MAX_LINE_LEN]:	SBYTE,
	cursrc[MAX_LINE_LEN]:	SBYTE,
	dlabel[32]:		SBYTE

	mov	ebx,tokenarray
	xor	eax,eax

	.while	[ebx].asm_tok.token != T_FINAL

		mov	esi,[ebx].asm_tok.tokpos
		.if	BYTE PTR [esi] == '"'
			ParseCString( addr dlabel, addr string, esi )
			mov	esi,eax
			strcpy( buffer, "offset " )
			strcat( buffer, addr dlabel )
			.if	esi

				.if	ModuleInfo.wstring

					sprintf( addr cursrc, " %s dw %s,0", addr dlabel, addr string )
				.else

					sprintf( addr cursrc, " %s db %s,0", addr dlabel, addr string )
				.endif

				InsertLine( ".data" )
				InsertLine( addr cursrc )
				InsertLine( ".code" )
			.endif
			mov	eax,1
			.break
		.endif
		add	ebx,16
	.endw
	ret
CString ENDP

endif
	END
