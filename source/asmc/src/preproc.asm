include io.inc
include stdio.inc
include stdlib.inc
include string.inc

include asmc.inc

REMOVECOMENT	equ 0 ; 1=remove comments from source
TF3_ISCONCAT	equ 1 ; line was concatenated
TF3_EXPANSION	equ 2 ; expansion operator % at pos 0

externdef	CurrIfState: dword
externdef	directive_tab: dword

WritePreprocessedLine	PROTO :DWORD
ExpandText		PROTO :DWORD, :DWORD, :DWORD
LabelMacro		PROTO FASTCALL :DWORD
ExpandLine		PROTO :DWORD, :DWORD
ExpandLineItems		PROTO :DWORD, :DWORD, :DWORD, :DWORD, :DWORD
CreateConstant		PROTO :DWORD
StoreLine		PROTO :DWORD, :DWORD, :DWORD

	.code

	OPTION	PROCALIGN:4
	ASSUME	ebx: PTR asm_tok

; preprocessor directive or macro procedure is preceded
; by a code label.

WriteCodeLabel PROC USES esi edi ebx line, tokenarray:PTR asm_tok

	mov ebx,tokenarray

	.if [ebx].asm_tok.token != T_ID
		asmerr( 2008, [ebx].asm_tok.string_ptr )
		jmp toend
	.endif
	;
	; ensure the listing is written with the FULL source line
	;
	.if ModuleInfo.curr_file[LST*4]
		LstWrite( LSTTYPE_LABEL, 0, 0 )
	.endif
	;
	; v2.04: call ParseLine() to parse the "label" part of the line
	;
	movzx esi,[ebx+32].asm_tok.token
	mov [ebx+32].asm_tok.token,T_FINAL
	mov edi,[ebx+32].asm_tok.tokpos
	mov al,[edi]
	mov BYTE PTR [edi],0
	push ModuleInfo.token_count
	mov ModuleInfo.token_count,2
	push eax
	ParseLine( ebx )
	.if Options.preprocessor_stdout
		WritePreprocessedLine( line )
	.endif
	pop eax
	mov [edi],al
	pop ModuleInfo.token_count
	mov eax,esi
	mov [ebx+32].asm_tok.token,al
	mov eax,NOT_ERROR

toend:
	ret
WriteCodeLabel ENDP


; PreprocessLine() is the "preprocessor".
; 1. the line is tokenized with Tokenize(), Token_Count set
; 2. (text) macros are expanded by ExpandLine()
; 3. "preprocessor" directives are executed

PreprocessLine PROC USES esi ebx line:LPSTR, tokenarray:PTR asm_tok

	mov ebx,tokenarray
	xor eax,eax
	;
	; v2.11: GetTextLine() removed - this is now done in ProcessFile()
	; v2.08: moved here from GetTextLine()
	;
	mov ModuleInfo.CurrComment,eax
	;
	; v2.06: moved here from Tokenize()
	;
	mov ModuleInfo.line_flags,al
	;
	; Token_Count is the number of tokens scanned
	;
	Tokenize( line, eax, ebx, eax )
	mov ModuleInfo.token_count,eax

if REMOVECOMENT eq 0
	.if !ModuleInfo.token_count && ( CurrIfState == BLOCK_ACTIVE || ModuleInfo.listif )
		LstWriteSrcLine()
	.endif
endif

	mov  eax,ModuleInfo.token_count
	test eax,eax
	jz   toend
	;
	; CurrIfState != BLOCK_ACTIVE && Token_Count == 1 | 3 may happen
	; if a conditional assembly directive has been detected by Tokenize().
	; However, it's important NOT to expand then
	;
	.if CurrIfState == BLOCK_ACTIVE
		shl eax,4
		.if [ebx+eax].bytval & TF3_EXPANSION
			ExpandText( line, ebx, 1 )
			mov esi,eax
		.else
			xor esi,esi
			.if !LabelMacro( ebx )
				.if !DelayExpand( ebx )
					ExpandLine( line, ebx )
					mov esi,eax
				.elseif Parse_Pass == PASS_1
					ExpandLineItems( line, 0, ebx, 0, 1 )
				.endif
			.endif
		.endif
		.if sdword ptr esi < NOT_ERROR
			xor eax,eax
			jmp toend
		.endif
	.endif

	xor esi,esi
	.if ModuleInfo.token_count > 2 && \
	    ( [ebx+16].asm_tok.token == T_COLON || [ebx+16].asm_tok.token == T_DBL_COLON )
		mov esi,32
	.endif

	;
	; handle "preprocessor" directives:
	; IF, ELSE, ENDIF, ...
	; FOR, REPEAT, WHILE, ...
	; PURGE
	; INCLUDE
	; since v2.05, error directives are no longer handled here!
	;
	.if [ebx+esi].token == T_DIRECTIVE && [ebx+esi].dirtype <= DRT_INCLUDE

		;
		; if i != 0, then a code label is located before the directive
		;
		.if esi > 16
			.if WriteCodeLabel( line, ebx ) == ERROR
				xor eax,eax
				jmp toend
			.endif
		.endif

		movzx eax,[ebx+esi].dirtype
		shr  esi,4
		push ebx
		push esi
		call directive_tab[eax*4]
		xor  eax,eax
		jmp  toend
	.endif

	;
	; handle preprocessor directives which need a label
	;

	.if [ebx].token == T_ID && [ebx+16].token == T_DIRECTIVE
		movzx	eax,[ebx+16].dirtype
		.switch eax
		  .case DRT_EQU
			;
			; EQU is a special case:
			; If an EQU directive defines a text equate
			; it MUST be handled HERE and 0 must be returned to the caller.
			; This will prevent further processing, nothing will be stored
			; if FASTPASS is on.
			; Since one cannot decide whether EQU defines a text equate or
			; a number before it has scanned its argument, we'll have to
			; handle it in ANY case and if it defines a number, the line
			; must be stored and, if -EP is set, written to stdout.
			;
			.if CreateConstant( ebx )
				mov esi,eax
				.if [eax].asym.state != SYM_TMACRO
					.if StoreState && Parse_Pass == PASS_1
						StoreLine( ModuleInfo.currsource, 0, 0 )
					.endif
					.if Options.preprocessor_stdout
						WritePreprocessedLine( line )
					.endif
				.endif
				;
				; v2.03: LstWrite() must be called AFTER StoreLine()!
				;
				.if ModuleInfo.list
					mov eax,LSTTYPE_TMACRO
					.if [esi].asym.state == SYM_INTERNAL
						mov eax,LSTTYPE_EQUATE
					.endif
					LstWrite( eax, 0, esi )
				.endif
			.endif
			xor eax,eax
			jmp toend
		  .case DRT_MACRO
		  .case DRT_CATSTR ; CATSTR + TEXTEQU directives
		  .case DRT_SUBSTR
			movzx eax,[ebx+16].dirtype
			push ebx
			push 1
			call directive_tab[eax*4]
			xor eax,eax
			jmp toend
		.endsw
	.endif
	mov eax,ModuleInfo.token_count
toend:
	ret
PreprocessLine ENDP

	END