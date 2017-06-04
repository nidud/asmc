;
; .for <initialization>: <condition>: <increment/decrement>
;
include string.inc
include asmc.inc
include token.inc
include hll.inc

	.code

strtrim PROC string:LPSTR

	.if strlen( string )

		mov ecx,eax
		add ecx,string
		.while 1
			dec ecx
			.break .if byte ptr [ecx] > ' '
			mov byte ptr [ecx],0
			dec eax
			.break .if ZERO?
		.endw
	.endif
	ret

strtrim ENDP

GetCondition proc private string:ptr sbyte

	mov ecx,string
	mov al,[ecx]
	.while al == ' ' || al == 9

		add ecx,1
		mov al,[ecx]
	.endw
	mov string,ecx

	xor edx,edx
	.while	1
		mov al,[ecx]
		.switch al
		  .case 0: .break
		  .case '(': inc edx : .endc
		  .case ')': dec edx : .endc
		  .case ','
			.endc .if edx

			mov [ecx],dl
			mov al,[ecx-1]
			.if al == ' ' || al == 9

				mov [ecx-1],dl
			.endif
			inc ecx
			mov al,[ecx]
			.while	al == ' ' || al == 9
				inc ecx
				mov al,[ecx]
			.endw
			mov edx,string
			.if BYTE PTR [edx] == 0 && al

				mov string,ecx
				xor edx,edx
				.continue(0)
			.endif
			.break
		.endsw
		add ecx,1
	.endw

	mov edx,string
	movzx eax,BYTE PTR [edx]
	ret

GetCondition ENDP

ParseAssignment proc private uses ecx edx esi edi ebx buffer:ptr sbyte, tokenarray:ptr asm_tok

	mov esi,buffer
	mov edx,tokenarray
	mov ebx,[edx].asm_tok.tokpos

	.repeat
ifdef _LINUX
		.if !strchr(ebx, '+')
		    .if !strchr(ebx, '-')
			strchr(ebx, '=')
		    .endif
		.endif
		.if !eax
else
		.if !_mbspbrk(ebx, "+-=")
endif

			asmerr( 2008, ebx )
			xor eax,eax
			.break
		.endif
		mov edi,eax
		.if byte ptr [eax+1] == ' '

			lea ecx,[eax+2]
			inc eax
			strcpy(eax, ecx)
		.endif

		mov ecx,[ebx]
		.switch cx

		  .case '--'
			add ebx,2
			strcat( esi, "dec " )
			strcat( esi, ebx )
			strcat( esi, "\n" )
			.endc

		  .case '++'
			add ebx,2
			strcat( esi, "inc " )
			strcat( esi, ebx )
			strcat( esi, "\n" )
			.endc

		  .default

			mov eax,[edi]
			mov BYTE PTR [edi],0
			add edi,2
			.switch
			  .case ax == '&='
				mov ecx,@CStr( "lea " )
				.endc
			  .case ax == '++'
				mov ecx,@CStr( "inc " )
				.endc
			  .case ax == '--'
				mov ecx,@CStr( "dec " )
				.endc
			  .case ax == '=+'
				mov ecx,@CStr( "add " )
				.endc
			  .case ax == '=-'
				mov ecx,@CStr( "sub " )
				.endc
			  .case al == '='
				mov ecx,@CStr( "mov " )
				sub edi,1
				.endc
			  .default
				asmerr( 2008, ebx )
				xor ecx,ecx
				xor eax,eax
			.endsw
			.endc .if !ecx

			push eax
			push ecx
			M_SKIP_SPACE eax, edi
			strtrim(ebx)
			strtrim(edi)
			pop ecx
			pop eax
			;
			; = &# --> lea #
			; = ~# --> mov reg,# : not reg
			;
			; mov reg,0 --> xor reg,reg
			;
			.if al == '='

				.if BYTE PTR [edi] == '&'

					inc edi
					mov ecx,@CStr( "lea " )

				.elseif BYTE PTR [edi] == '~'

					inc edi
					strcat( esi, ecx )
					strcat( esi, ebx )
					strcat( esi, ", " )
					strcat( esi, edi )
					strcat( esi, "\n" )
					mov BYTE PTR [edi],0
					mov ecx,@CStr( "not " )

				.elseif WORD PTR [edi] == '0'

					mov edx,tokenarray
					mov eax,[edx].asm_tok.tokval

					.if (eax >= T_AL && eax <= T_EDI) || \
					    (ModuleInfo.Ofssize == USE64 && \
					    eax >= T_R8B && eax <= T_R15)

						mov ecx,@CStr( "xor " )
						mov edi,ebx
					.endif
				.endif
			.endif
			strcat( esi, ecx )
			strcat( esi, ebx )
			.if BYTE PTR [edi]

				strcat( esi, ", " )
				strcat( esi, edi )
			.endif
			strcat( esi, "\n" )
		.endsw
	.until	1
	ret

ParseAssignment endp

RenderAssignment proc private uses esi edi ebx dest:ptr sbyte,
	source:ptr sbyte, tokenarray:ptr asm_tok

  local buffer[MAX_LINE_LEN]:SBYTE
  local tokbuf[MAX_LINE_LEN]:SBYTE

	mov edi,source
	lea esi,buffer
	;
	; <expression1>, <expression2>, ..., [: | 0]
	;
	.while GetCondition(edi)

		mov ebx,ecx ; next expression
		mov edi,edx ; this expression
		lea edx,tokbuf
		Tokenize( strcpy( edx, edi ), 0, tokenarray, TOK_DEFAULT )
		mov ModuleInfo.token_count,eax

		.break .if ExpandHllProc( esi, 0, tokenarray ) == ERROR

		.if byte ptr [esi] ; function calls expanded

			strcat( strcat( dest, esi ), "\n" )
			mov byte ptr [esi],0
		.endif

		.break .if !ParseAssignment(esi, tokenarray)
		strcat( strcat( dest, esi ), "\n" )
		mov edi,ebx
	.endw
	mov eax,dest
	movzx eax,byte ptr [eax]
	ret

RenderAssignment endp

	assume	ebx:ptr asm_tok
	assume	esi:ptr hll_item

ForDirective proc uses esi edi ebx i:SINT, tokenarray:ptr asm_tok

local	rc:SINT,
	cmd:UINT,
	p:LPSTR,
	q:LPSTR,
	buff[16]:SBYTE,
	buffer[MAX_LINE_LEN]:SBYTE,
	cmdstr[MAX_LINE_LEN]:SBYTE,
	tokbuf[MAX_LINE_LEN]:SBYTE

	mov rc,NOT_ERROR
	mov ebx,tokenarray
	lea edi,buffer

	mov eax,i
	shl eax,4
	mov eax,[ebx+eax].tokval
	mov cmd,eax
	inc i

	.repeat
		.if eax == T_DOT_ENDF

			mov esi,ModuleInfo.HllStack
			.if !esi

				asmerr(1011)
				.break
			.endif

			mov edx,[esi].next
			mov ecx,ModuleInfo.HllFree
			mov ModuleInfo.HllStack,edx
			mov [esi].next,ecx
			mov ModuleInfo.HllFree,esi

			.if [esi].cmd != HLL_WHILE

				asmerr( 1011 )
				.break
			.endif

			mov eax,[esi].labels[LTEST*4]
			.if eax

				AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), LABELQUAL )
			.endif

			.if [esi].condlines

				QueueTestLines( [esi].condlines )
			.endif

			AddLineQueueX( "jmp %s", GetLabelStr( [esi].labels[LSTART*4], edi ) )

			mov eax,[esi].labels[LEXIT*4]
			.if eax

				AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), LABELQUAL )
			.endif
			mov eax,i
			shl eax,4
			add ebx,eax
			.if [ebx].token != T_FINAL && rc == NOT_ERROR

				mov rc,asmerr( 2008, [ebx].tokpos )
			.endif
		.else

			mov esi,ModuleInfo.HllFree
			.if !esi

				mov esi,LclAlloc( sizeof( hll_item ) )
			.endif
			ExpandCStrings(tokenarray)

			xor eax,eax
			mov [esi].labels[LEXIT*4],eax
			.if cmd == T_DOT_FORS

				or eax,HLLF_IFS
			.endif
			mov [esi].flags,eax
			mov [esi].cmd,HLL_WHILE

			; create the loop labels

			mov [esi].labels[LSTART*4],GetHllLabel()
			mov [esi].labels[LTEST*4],GetHllLabel()
			mov [esi].labels[LEXIT*4],GetHllLabel()

			mov eax,i
			shl eax,4
			add ebx,eax
			.if [ebx].token == T_OP_BRACKET

				inc i
				add ebx,16
			.endif

			.if !strchr(strcpy(edi, [ebx].tokpos), ':')

				asmerr( 2206 )
				.break
			.endif

			mov BYTE PTR [eax],0
			inc eax
			M_SKIP_SPACE ecx, eax
			mov p,eax
			.if !strchr(eax, ':')

				asmerr( 2206 )
				.break
			.endif

			mov BYTE PTR [eax],0
			inc eax
			M_SKIP_SPACE ecx, eax
			mov q,eax
			strtrim(eax)
			M_SKIP_SPACE ecx, edi
			strtrim(edi)
			strtrim(p)

			.if [ebx-16].token == T_OP_BRACKET

				.if strrchr(q, ')')

					mov BYTE PTR [eax],0
					strtrim(q)
				.endif
			.endif

			lea ebx,cmdstr
			mov BYTE PTR [ebx],0
			.if RenderAssignment(ebx, edi, tokenarray)

				QueueTestLines( ebx )
			.endif
			AddLineQueueX( "%s%s",
				GetLabelStr( [esi].labels[LSTART*4], addr buff ), LABELQUAL )

			mov BYTE PTR [ebx],0
			mov [esi].condlines,0

			.if RenderAssignment(ebx, q, tokenarray)

				strlen( ebx )
				inc	eax
				push	eax
				LclAlloc( eax )
				pop	ecx
				mov	[esi].condlines,eax
				memcpy( eax, ebx, ecx )
			.endif

			mov edi,p
			mov BYTE PTR [ebx],0
			.while GetCondition(edi)

				push ecx
				mov edi,edx

				lea edx,tokbuf
				Tokenize( strcat( strcpy( edx, ".if " ), edi ),
					0, tokenarray, TOK_DEFAULT )
				mov ModuleInfo.token_count,eax

				mov i,1
				EvaluateHllExpression( esi, addr i, tokenarray,
					LEXIT, 0, ebx )
				mov rc,eax

				.if eax == NOT_ERROR

					QueueTestLines( ebx )
				.endif
				pop edi
			.endw

			.if esi == ModuleInfo.HllFree

				mov eax,[esi].next
				mov ModuleInfo.HllFree,eax
			.endif

			mov eax,ModuleInfo.HllStack
			mov [esi].next,eax
			mov ModuleInfo.HllStack,esi

		.endif

		.if ModuleInfo.list

			LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
		.endif

		.if ModuleInfo.line_queue.head

			RunLineQueue()
		.endif

		mov eax,rc

	.until	1
	ret

ForDirective endp

	END
