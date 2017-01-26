include string.inc
include ctype.inc
include stdio.inc
include stdlib.inc
include alloc.inc

include asmc.inc
include token.inc

MIN_JTABLE	equ 4

ExpandLine	PROTO :LPSTR, :PTR asm_tok
GenerateCString PROTO :SINT,  :PTR asm_tok
EvalOperand	PROTO :SINT,  :PTR asm_tok, :SINT, :PTR expr, :SINT
GetCurrOffset	PROTO


LABELSGLOBAL	equ 0 ; make the generated labels global
;LABELFMT	equ <"@C%04X">
;
; v2.10: static variables moved to ModuleInfo
;
EOLCHAR		equ 10		; line termination char in generated source
NULLC		equ 0
;
; values for struct hll_item.cmd
;
HLL_IF		equ 0
HLL_WHILE	equ 1
HLL_REPEAT	equ 2
HLL_BREAK	equ 3	; .IF behind .BREAK or .CONTINUE
HLL_SWITCH	equ 4
;
; index values for struct hll_item.labels[]
;
LTEST		equ 0 ; test (loop) condition
LEXIT		equ 1 ; block exit
LSTART		equ 2 ; loop start
;
; values for struct hll_item.flags
;
HLLF_ELSEOCCUR	equ 01h
HLLF_ELSEIF	equ 02h
HLLF_WHILE	equ 04h
HLLF_EXPRESSION equ 08h
HLLF_DEFAULT	equ 10h
HLLF_DELAYED	equ 20h		; set by DelayExpand()
;
; .SWITCH <arg_type>
;
HLLF_NOTEST	equ 40h		; direct jump..
HLLF_ARGREG	equ 80h		; register 16/32/64-bit size_t
HLLF_ARGMEM	equ 0100h	; memory if set, else register
HLLF_ARG16	equ 0200h	; size: 8/16/32/64
HLLF_ARG32	equ 0400h
HLLF_ARG64	equ 0800h
HLLF_ARG3264	equ 1000h	; .switch eax in 64-bit assumend rax
;
; .CASE flags
;
HLLF_NUM	equ 2000h	; .case arg is const
HLLF_TABLE	equ 4000h	; .case is in jump table
HLLF_ENDCOCCUR	equ 8000h	; jmp exit in .case omitted

HLLF_IFB	equ 10000h	; .ifb proc() == -1 - rax --> al return
HLLF_IFW	equ 20000h	; .ifw proc() == -1 - rax --> ax return
HLLF_IFD	equ 40000h	; .ifd proc() == -1 - rax --> eax return
HLLF_IFS	equ 80000h	; .ifs proc() > 0   - rax --> sqword ptr rax

;
; item for .IF, .WHILE, .REPEAT, ...
;
hll_item	STRUC
next		dd ?		; hll_item *
caselist	dd ?		; hll_item *
labels		dd 3 dup(?)	; labels for LTEST, LEXIT, LSTART
condlines	LPSTR ?		; .WHILE/ELSEIF/CASE-blocks only: lines to add after 'test' label
cmd		dd ?		; start cmd (IF, WHILE, REPEAT)
flags		dd ?		; v2.08: added
hll_item	ENDS
;
; v2.08: struct added
;
hll_opnd	STRUC
lastjmp		dd ?
lasttruelabel	dd ?		; v2.08: new member
hll_opnd	ENDS

; c binary ops.
; Order of items COP_EQ - COP_LE  and COP_ZERO - COP_OVERFLOW
; must not be changed.

COP_NONE	equ 0
COP_EQ		equ 1		; ==
COP_NE		equ 2		; !=
COP_GT		equ 3		; >
COP_LT		equ 4		; <
COP_GE		equ 5		; >=
COP_LE		equ 6		; <=
COP_AND		equ 7		; &&
COP_OR		equ 8		; ||
COP_ANDB	equ 9		; &
COP_NEG		equ 10		; !
COP_ZERO	equ 11		; ZERO?	 not really a valid C operator
COP_CARRY	equ 12		; CARRY?	 not really a valid C operator
COP_SIGN	equ 13		; SIGN?	 not really a valid C operator
COP_PARITY	equ 14		; PARITY?   not really a valid C operator
COP_OVERFLOW	equ 15		; OVERFLOW? not really a valid C operator

	.data

if LABELSGLOBAL
LABELQUAL	db "::",0
else
LABELQUAL	db ":",0
endif
EOLSTR		db EOLCHAR,0
;
; items in table below must match order COP_ZERO - COP_OVERFLOW
;
flaginstr	db 'z','c','s','p','o'
;
; items in tables below must match order COP_EQ - COP_LE
;
unsign_cjmptype db 'z','z','a','b','b','a'
signed_cjmptype db 'z','z','g','l','l','g'
neg_cjmptype	db 0,1,0,0,1,1

; in Masm, there's a nesting level limit of 20. In JWasm, there's
; currently no limit.

GetHllLabel	MACRO
	inc	ModuleInfo.hll_label
	mov	eax,ModuleInfo.hll_label
	exitm	<eax>
	ENDM

;
; get a C binary operator from the token stream.
; there is a problem with the '<' because it is a "string delimiter"
; which Tokenize() usually is to remove.
; There has been a hack implemented in Tokenize() so that it won't touch the
; '<' if .IF, .ELSEIF, .WHILE, .UNTIL, .UNTILCXZ or .BREAK/.CONTINUE has been
; detected.
;

CHARS_EQ	equ '=' + ( '=' shl 8 )
CHARS_NE	equ '!' + ( '=' shl 8 )
CHARS_GE	equ '>' + ( '=' shl 8 )
CHARS_LE	equ '<' + ( '=' shl 8 )
CHARS_AND	equ '&' + ( '&' shl 8 )
CHARS_OR	equ '|' + ( '|' shl 8 )

	.code

	OPTION	PROC:	PRIVATE

GetCOp	PROC FASTCALL item;:PTR asm_tok


	ASSUME	ecx:PTR asm_tok

	mov	edx,[ecx].string_ptr
	xor	eax,eax
	.if	[ecx].token == T_STRING
		mov	eax,[ecx].stringlen
	.endif

	.if	eax == 2
		movzx	eax,WORD PTR [edx]
		.switch eax
		  .case CHARS_EQ
			mov	eax,COP_EQ
			ret
		  .case CHARS_NE
			mov	eax,COP_NE
			ret
		  .case CHARS_GE
			mov	eax,COP_GE
			ret
		  .case CHARS_LE
			mov	eax,COP_LE
			ret
		  .case CHARS_AND
			mov	eax,COP_AND
			ret
		  .case CHARS_OR
			mov	eax,COP_OR
			ret
		.endsw
		mov	eax,COP_NONE
		ret
	.endif

	.if	eax == 1
		mov	al,[edx]
		.switch eax
		  .case '>'
			mov	eax,COP_GT
			ret
		  .case '<'
			mov	eax,COP_LT
			ret
		  .case '&'
			mov	eax,COP_ANDB
			ret
		  .case '!'
			mov	eax,COP_NEG
			ret
		.endsw
		mov	eax,COP_NONE
		ret
	.endif

	.if	[ecx].token != T_ID
		mov	eax,COP_NONE
		ret
	.endif

	ASSUME	ecx:NOTHING
	;
	; a valid "flag" string must end with a question mark
	;
	.if	BYTE PTR [edx + strlen( edx ) - 1] == '?'
		mov	ecx,[edx]
		and	ecx,not 20202020h
		.switch eax
		  .case 5
			.if	ecx == "OREZ"
				mov	eax,COP_ZERO
				ret
			.endif
			.if	ecx == "NGIS"
				mov	eax,COP_SIGN
				ret
			.endif
			.endc
		  .case 6
			movzx	eax,BYTE PTR [edx+4]
			and	eax,not 20h
			.if	eax == "Y" && ecx == "RRAC"
				mov	eax,COP_CARRY
				ret
			.endif
			.endc
		  .case 7
			movzx	eax,WORD PTR [edx+4]
			and	eax,not 2020h
			.if	eax == "YT" && ecx == "IRAP"
				mov	eax,COP_PARITY
				ret
			.endif
			.endc
		  .case 9
			mov	eax,[edx+4]
			and	eax,not 20202020h
			.if	eax == "WOLF" && ecx == "REVO"
				mov	eax,COP_OVERFLOW
				ret
			.endif
		.endsw
	.endif
	mov	eax,COP_NONE
	ret
GetCOp ENDP

;
; render an instruction
;

RenderInstr PROC USES esi edi ebx,
	dst:		LPSTR,
	inst:		LPSTR,
	start1:		UINT,
	end1:		UINT,
	start2:		UINT,
	end2:		UINT,
	tokenarray:	PTR asm_tok

	;
	; copy the instruction
	;
	mov	esi,inst
	mov	edi,dst
	strlen( esi )
	mov	ecx,eax
	rep	movsb
	mov	eax,' '
	stosb
	;
	; copy the first operand's tokens
	;
	mov	ebx,tokenarray
	mov	ecx,end1
	mov	eax,start1
	shl	ecx,4
	shl	eax,4
	mov	ecx,[ebx+ecx].asm_tok.tokpos
	mov	esi,[ebx+eax].asm_tok.tokpos
	sub	ecx,esi
	rep	movsb

	mov	ecx,end2
	mov	eax,start2

	.if	eax != EMPTY
		mov	WORD PTR [edi],' ,'
		add	edi,2
		;
		; copy the second operand's tokens
		;
		shl	ecx,4
		shl	eax,4
		mov	ecx,[ebx+ecx].asm_tok.tokpos
		mov	esi,[ebx+eax].asm_tok.tokpos
		sub	ecx,esi
		rep	movsb
	.elseif ecx != EMPTY
		sprintf(edi, ", %d", ecx)
		add	edi,eax
	.endif
	mov	WORD PTR [edi],EOLCHAR
	lea	eax,[edi+1]
	ret
RenderInstr ENDP

GetLabelStr PROC FASTCALL l_id, buff
	sprintf( edx, "@C%04X", ecx )
	mov	eax,edx
	ret
GetLabelStr ENDP

;
; render a Jcc instruction
;
RenderJcc PROC USES edi dst, cc, _neg, _label
	;
	; create the jump opcode: j[n]cc
	;
	mov	edi,dst
	mov	eax,'j'
	stosb
	mov	ecx,_neg
	.if	ecx
		mov	eax,'n'
		stosb
	.endif
	mov	eax,cc
	stosb
	mov	eax,' '
	.if	!ecx
		stosb		; make sure there's room for the inverse jmp
	.endif
	stosb
	sprintf( edi, "@C%04X", _label )
	lea	eax,[edi+eax+1]
	mov	WORD PTR [eax-1],EOLCHAR
	ret
RenderJcc ENDP

;
; a "token" in a C expression actually is an assembly expression
;
LGetToken PROC USES esi edi ebx hll:PTR hll_item, i, tokenarray, opnd:PTR expr
	;
	; scan for the next C operator in the token array.
	; because the ASM evaluator may report an error if such a thing
	; is found ( CARRY?, ZERO? and alikes will be regarded as - not yet defined - labels )
	;
	mov	esi,i
	mov	edi,[esi]

	mov	ebx,edi
	shl	ebx,4
	add	ebx,tokenarray

	.while	edi < ModuleInfo.token_count
		.break .if GetCOp( ebx ) != COP_NONE
		add	edi,1
		add	ebx,16
	.endw
	.if	edi == [esi]
		mov	eax,opnd
		mov	[eax].expr.kind,EXPR_EMPTY
		mov	eax,NOT_ERROR
		jmp	toend
	.endif

	EvalOperand( esi, tokenarray, edi, opnd, 0 )
	cmp	eax,ERROR
	je	toend
	;
	; v2.11: emit error 'syntax error in control flow directive'.
	; May happen for expressions like ".if 1 + CARRY?"
	;
	.if	[esi] > edi
		asmerr( 2154 )
	.else
		mov	eax,NOT_ERROR
	.endif
toend:
	ret
LGetToken ENDP

GetLabel PROC FASTCALL hll, index
	mov	eax,[ecx].hll_item.labels[edx*4]
	ret
GetLabel ENDP

; a "simple" expression is
; 1. two tokens, coupled with a <cmp> operator: == != >= <= > <
; 2. two tokens, coupled with a "&" operator
; 3. unary operator "!" + one token
; 4. one token (short form for "<token> != 0")
;

EmitConstError	PROTO	:PTR expr
GetExpression	PROTO	:PTR hll_item,
			:PTR SINT,
			:PTR asm_tok,
			:SDWORD,
			:UINT,
			:LPSTR,
			:PTR hll_opnd

GetSimpleExpression PROC USES esi edi ebx,
	hll:		PTR hll_item,
	i:		PTR SINT,
	tokenarray:	PTR asm_tok,
	ilabel:		SINT,
	is_true:	UINT,
	buffer:		LPSTR,
	hllop:		PTR hll_opnd

local	op:		SINT,
	op1_pos:	SINT,
	op1_end:	SINT,
	op2_pos:	SINT,
	op2_end:	SINT,
	op1		:expr,
	op2		:expr,
	_label

	ASSUME	ebx: PTR asm_tok

	mov	esi,i
	mov	edi,[esi]
	mov	ebx,edi
	shl	ebx,4
	add	ebx,tokenarray
	mov	eax,[ebx].string_ptr
	.while	WORD PTR [eax] == '!'
		add	edi,1
		add	ebx,16
		mov	eax,1
		sub	eax,is_true
		mov	is_true,eax
		mov	eax,[ebx].string_ptr
	.endw
	mov	[esi],edi
	;
	; the problem with '()' is that is might enclose just a standard Masm
	; expression or a "hll" expression. The first case is to be handled
	; entirely by the expression evaluator, while the latter case is to be
	; handled HERE!
	;
	.if	[ebx].token == T_OP_BRACKET

		mov	esi,1
		add	ebx,16
		movzx	eax,[ebx].token
		.while	eax != T_FINAL
			.if	eax == T_OP_BRACKET
				add	esi,1
			.elseif eax == T_CL_BRACKET
				sub	esi,1
				.break .if ZERO?	; a standard Masm expression?
			.else
				.break .if GetCOp( ebx ) != COP_NONE
			.endif
			add	ebx,16
			movzx	eax,[ebx].token
		.endw
		mov	eax,esi
		mov	esi,i
		.if	eax
			inc	DWORD PTR [esi]
			GetExpression( hll, esi, tokenarray, ilabel, is_true, buffer, hllop )
			cmp	eax,ERROR
			je	toend
			mov	ebx,[esi]
			shl	ebx,4
			add	ebx,tokenarray
			.if	[ebx].token != T_CL_BRACKET
				asmerr( 2154 )
				jmp	toend
			.endif
			inc	DWORD PTR [esi]
			mov	eax,NOT_ERROR
			jmp	toend
		.endif
	.endif
	mov	edi,[esi]
	mov	ebx,tokenarray
	;
	; get (first) operand
	;
	mov	op1_pos,edi
	LGetToken( hll, esi, ebx, addr op1 )
	cmp	eax,ERROR
	je	toend
	mov	edi,[esi]
	mov	op1_end,edi

	mov	eax,edi		; get operator
	shl	eax,4
	add	eax,ebx
	GetCOp( eax )
	;
	; lower precedence operator ( && or || ) detected?
	;
	.if	eax == COP_AND || eax == COP_OR
		mov	eax,COP_NONE
	.elseif eax != COP_NONE
		inc	edi
		mov	[esi],edi
	.endif
	mov	op,eax

	GetLabel( hll, ilabel )
	mov	_label,eax
	;
	; check for special operators with implicite operand:
	; COP_ZERO, COP_CARRY, COP_SIGN, COP_PARITY, COP_OVERFLOW
	;
	mov	edx,op
	.if	edx >= COP_ZERO
		.if	op1.kind != EXPR_EMPTY
			asmerr( 2154 )
			jmp	toend
		.endif
		mov	ecx,hllop
		mov	eax,buffer
		mov	[ecx].hll_opnd.lastjmp,eax
		movzx	ecx,flaginstr[edx - COP_ZERO]
		mov	edx,is_true
		xor	edx,1
		RenderJcc( eax, ecx, edx, _label )
		mov	eax,NOT_ERROR
		jmp	toend
	.endif

	mov	eax,op1.kind
	.switch eax
	  .case EXPR_EMPTY
		asmerr( 2154 )	; v2.09: changed from NOT_ERROR to ERROR
		jmp	toend
	  .case EXPR_FLOAT
		asmerr( 2050 )	; v2.10: added
		jmp	toend
	.endsw

	.if	op == COP_NONE
		.switch eax
		  .case EXPR_REG
			.if	!( op1.flags & EXF_INDIRECT )
				.if	Options.masm_compat_gencode
					RenderInstr( buffer, "or",   op1_pos, op1_end, op1_pos, op1_end, ebx )
				.else
					RenderInstr( buffer, "test", op1_pos, op1_end, op1_pos, op1_end, ebx )
				.endif
				mov	edx,hllop
				mov	[edx].hll_opnd.lastjmp,eax
				RenderJcc( eax, 'z', is_true, _label )
				.endc
			.endif
			;
			; no break
			;
		  .case EXPR_ADDR
			RenderInstr( buffer, "cmp", op1_pos, op1_end, EMPTY, 0, ebx )
			mov	edx,hllop
			mov	[edx].hll_opnd.lastjmp,eax
			RenderJcc( eax, 'z', is_true, _label )
			.endc
		  .case EXPR_CONST
			.if	op1.hvalue != 0 && op1.hvalue != -1
				EmitConstError( addr op1 )
				jmp	toend
			.endif
			mov	ecx,hllop
			mov	eax,buffer
			mov	[ecx].hll_opnd.lastjmp,eax
			mov	edx,is_true
			xor	edx,1
			.if	(( is_true && op1.value ) || ( edx && op1.value == 0 ))
				sprintf( buffer, "jmp @C%04X%s", _label, addr EOLSTR )
			.else
				mov	BYTE PTR [eax],NULLC
			.endif
			.endc
		.endsw
		mov	eax,NOT_ERROR
		jmp	toend
	.endif

	;
	; get second operand for binary operator
	;
	mov	edi,[esi]
	mov	op2_pos,edi
	LGetToken( hll, esi, ebx, addr op2 )
	cmp	eax,ERROR
	je	toend

	mov	eax,op2.kind
	.if	eax != EXPR_CONST && eax != EXPR_ADDR && eax != EXPR_REG

		asmerr( 2154 )
		jmp	toend
	.endif
	mov	edi,[esi]
	mov	op2_end,edi

	ASSUME	ebx: NOTHING

	;
	; now generate ASM code for expression
	;
	mov	ecx,op
	.if	ecx == COP_ANDB

		RenderInstr( buffer, "test", op1_pos, op1_end, op2_pos, op2_end, ebx )

		mov	ecx,hllop
		mov	[ecx].hll_opnd.lastjmp,eax
		RenderJcc( eax, 'e', is_true, _label )

	.elseif ecx <= COP_LE
		;
		; ==, !=, >, <, >= or <= operator
		;
		; optimisation: generate 'or EAX,EAX' instead of 'cmp EAX,0'.
		; v2.11: use op2.value64 instead of op2.value
		;
		.if	Options.masm_compat_gencode	   && \
			( ecx == COP_EQ || ecx == COP_NE ) && \
			op1.kind == EXPR_REG		   && \
			!( op1.flags & EXF_INDIRECT )	   && \
			op2.kind == EXPR_CONST		   && \
			DWORD PTR op2.value64 == 0	   && \
			DWORD PTR op2.value64[4] == 0

			RenderInstr( buffer, "test", op1_pos, op1_end, op1_pos, op1_end, ebx )
		.else
			RenderInstr( buffer, "cmp",  op1_pos, op1_end, op2_pos, op2_end, ebx )
		.endif

		mov	ecx,hll
		xor	edi,edi
		.if	[ecx].hll_item.flags & HLLF_IFS

			.if	op1.kind != EXPR_REG

				asmerr( 2154 )
				jmp	toend
			.endif
			inc	edi	; v2.22 - Signed Compare
		.endif

		mov	ecx,op
		movzx	edx,op1.mem_type
		movzx	ebx,op2.mem_type
		and	edx,MT_SPECIAL_MASK
		and	ebx,MT_SPECIAL_MASK

		.if	edi || edx == MT_SIGNED || ebx == MT_SIGNED

			movzx	edx,signed_cjmptype[ecx - COP_EQ]
		.else
			movzx	edx,unsign_cjmptype[ecx - COP_EQ]
		.endif

		mov	ebx,hllop
		mov	[ebx].hll_opnd.lastjmp,eax
		mov	ebx,is_true
		.if	!neg_cjmptype[ecx - COP_EQ]

			xor	ebx,1
		.endif
		RenderJcc( eax, edx, ebx, _label )
	.else

		asmerr( 2154 )
		jmp	toend
	.endif

	mov	eax,NOT_ERROR

toend:
	ret

GetSimpleExpression ENDP

; invert a Jump:
; - Jx	 -> JNx (x = e|z|c|s|p|o )
; - JNx -> Jx	(x = e|z|c|s|p|o )
; - Ja	 -> Jbe, Jae -> Jb
; - Jb	 -> Jae, Jbe -> Ja
; - Jg	 -> Jle, Jge -> Jl
; - Jl	 -> Jge, Jle -> Jg
; added in v2.11:
; - jmp -> 0
; - 0	 -> jmp
;
InvertJump PROC FASTCALL p

	.if	BYTE PTR [ecx] == NULLC ; v2.11: convert 0 to "jmp"
		strcpy( ecx, "jmp " )
		ret
	.endif
	add	ecx,1
	mov	eax,[ecx]

	.switch al
	  .case 'e'
	  .case 'z'
	  .case 'c'
	  .case 's'
	  .case 'p'
	  .case 'o'
		mov	BYTE PTR [ecx+1],al
		mov	BYTE PTR [ecx],'n'
		ret
	  .case 'n'
		mov	BYTE PTR [ecx],ah
		mov	BYTE PTR [ecx+1],' '
		ret
	  .case 'a'
		mov	BYTE PTR [ecx],'b'
		.endc
	  .case 'b'
		mov	BYTE PTR [ecx],'a'
		.endc
	  .case 'g'
		mov	BYTE PTR [ecx],'l'
		.endc
	  .case 'l'
		mov	BYTE PTR [ecx],'g'
		.endc
	  .default
		;
		; v2.11: convert "jmp" to 0
		;
		.if	al == 'm'
			sub	ecx,1
			mov	BYTE PTR [ecx],NULLC
		.endif
		ret
	.endsw

	.if	ah == 'e'
		mov	BYTE PTR [ecx+1],' '
	.else
		mov	BYTE PTR [ecx+1],'e'
	.endif
	ret
InvertJump ENDP


; Replace a label in the source lines generated so far.
; todo: if more than 0xFFFF labels are needed,
; it may happen that length of nlabel > length of olabel!
; then the simple memcpy() below won't work!
;
ReplaceLabel PROC USES esi edi ebx p, olabel, nlabel

local	oldlbl[16]:SBYTE,
	newlbl[16]:SBYTE

	lea	esi,oldlbl
	lea	edi,newlbl
	mov	ebx,p
	GetLabelStr( olabel, esi )
	GetLabelStr( nlabel, edi )
	strlen( edi )
	mov	ebx,eax
	mov	eax,p
	.while	strstr( eax, esi )

		memcpy( eax, edi, ebx )
		add	eax,ebx
	.endw
	ret

ReplaceLabel ENDP

; operator &&, which has the second lowest precedence, is handled here

GetAndExpression PROC USES esi edi ebx,
	hll:		PTR hll_item,
	i:		PTR SINT,
	tokenarray:	PTR asm_tok,
	ilabel:		UINT,
	is_true:	UINT,
	buffer:		LPSTR,
	hllop:		PTR hll_opnd

local	truelabel:	SINT,
	nlabel:		SINT,
	olabel:		SINT,
	buff[16]:	SBYTE

	mov	edi,hllop
	mov	esi,buffer
	mov	truelabel,0

	.while	1

		GetSimpleExpression( hll, i, tokenarray, ilabel, is_true, esi, edi )
		cmp	eax,ERROR
		je	toend
		mov	ebx,i
		mov	eax,[ebx]
		shl	eax,4
		add	eax,tokenarray
		.break .if GetCOp( eax ) != COP_AND
		inc	DWORD PTR [ebx]
		mov	ebx,[edi].hll_opnd.lastjmp
		.if	ebx && is_true

			InvertJump( ebx )

			.if	truelabel == 0

				mov	truelabel,GetHllLabel()
			.endif
			;
			; v2.11: there might be a 0 at lastjmp
			;
			.if	BYTE PTR [ebx]

				strcat( GetLabelStr( truelabel, addr [ebx+4] ), addr EOLSTR )
			.endif
			;
			; v2.22 .while	(eax || edx) && ecx -- failed
			;	.while !(eax || edx) && ecx -- failed
			;
			mov	ebx,esi
			.if	[edi].hll_opnd.lasttruelabel

				ReplaceLabel( ebx, [edi].hll_opnd.lasttruelabel, truelabel )
			.endif
			mov	nlabel,GetHllLabel()
			mov	olabel,GetLabel( hll, ilabel )
			strlen( ebx )
			add	ebx,eax
			sprintf( ebx, "%s%s%s", GetLabelStr( olabel, addr buff ), addr LABELQUAL, addr EOLSTR )
			ReplaceLabel( buffer, olabel, nlabel )
			mov	[edi].hll_opnd.lastjmp,0
		.endif

		strlen( esi )
		add	esi,eax
		mov	[edi].hll_opnd.lasttruelabel,0
	.endw

	.if	truelabel

		strlen( esi )
		add	esi,eax
		strcat( strcat( GetLabelStr( truelabel, esi ), addr LABELQUAL ), addr EOLSTR )
		mov	[edi].hll_opnd.lastjmp,0
	.endif
	mov	 eax,NOT_ERROR
toend:
	ret
GetAndExpression ENDP

; operator ||, which has the lowest precedence, is handled here

GetExpression PROC USES esi edi ebx,
	hll:		PTR hll_item,
	i:		PTR SINT,
	tokenarray:	PTR asm_tok,
	ilabel:		SINT,
	is_true:	UINT,
	buffer:		LPSTR,
	hllop:		PTR hll_opnd

local	truelabel:	SINT,
	nlabel:		SINT,
	olabel:		SINT,
	buff[16]:	SBYTE

	mov	esi,buffer
	mov	edi,hllop
	mov	truelabel,0

	.while	1

		GetAndExpression( hll, i, tokenarray, ilabel, is_true, esi, edi )
		cmp	eax,ERROR
		je	toend

		mov	ebx,i
		mov	eax,[ebx]
		shl	eax,4
		add	eax,tokenarray
		.break .if GetCOp( eax ) != COP_OR
		;
		; the generated code of last simple expression has to be modified
		; 1. the last jump must be inverted
		; 2. a "is_true" label must be created (it's used to jump "behind" the expr)
		; 3. create a new label
		; 4. the current "false" label must be generated
		;
		; if it is a .REPEAT, step 4 is slightly more difficult, since the "false"
		; label is already "gone":
		; 4a. create a new label
		; 4b. replace the "false" label in the generated code by the new label
		;
		inc	DWORD PTR [ebx]
		mov	ebx,[edi].hll_opnd.lastjmp

		.if	ebx && !is_true

			InvertJump( ebx )

			.if	truelabel == 0

				mov	truelabel,GetHllLabel()
			.endif

			.if	BYTE PTR [ebx]

				strcat( GetLabelStr( truelabel, addr [ebx+4] ), addr EOLSTR )
			.endif

			mov	ebx,esi
			.if	[edi].hll_opnd.lasttruelabel

				ReplaceLabel( ebx, [edi].hll_opnd.lasttruelabel, truelabel )
			.endif

			mov	[edi].hll_opnd.lastjmp,0
			mov	nlabel,GetHllLabel()
			mov	olabel,GetLabel( hll, ilabel )
			strlen( ebx )
			add	ebx,eax
			mov	eax,hll
			.if	[eax].hll_item.cmd == HLL_REPEAT

				ReplaceLabel( buffer, olabel, nlabel )
				sprintf( ebx, "%s%s%s", GetLabelStr( nlabel, addr buff ), addr LABELQUAL, addr EOLSTR )
			.else

				sprintf( ebx, "%s%s%s", GetLabelStr( olabel, addr buff ), addr LABELQUAL, addr EOLSTR )
				ReplaceLabel( buffer, olabel, nlabel )
			.endif
		.endif
		strlen( esi )
		add	esi,eax
		mov	[edi].hll_opnd.lasttruelabel,0
	.endw

	.if	truelabel

		mov	ebx,[edi].hll_opnd.lastjmp
		.if	ebx && [edi].hll_opnd.lasttruelabel
			ReplaceLabel( esi, [edi].hll_opnd.lasttruelabel, truelabel )
			strchr( ebx, EOLCHAR )
			mov	BYTE PTR [eax+1],0
		.endif

		strlen( esi )
		add	esi,eax
		strcat( strcat( GetLabelStr( truelabel, esi ), addr LABELQUAL ), addr EOLSTR )
		mov	eax,truelabel
		mov	[edi].hll_opnd.lasttruelabel,eax
	.endif

	mov	eax,NOT_ERROR

toend:
	ret
GetExpression ENDP

;
; evaluate the C like boolean expression found in HLL structs
; like .IF, .ELSEIF, .WHILE, .UNTIL and .UNTILCXZ
; might return multiple lines (strings separated by EOLCHAR)
; - i = index for tokenarray[] where expression starts. Is restricted
;	 to one source line (till T_FINAL)
; - label: label to jump to if expression is <is_true>!
; is_true:
;   .IF:	FALSE
;   .ELSEIF:	FALSE
;   .WHILE:	TRUE
;   .UNTIL:	FALSE
;   .UNTILCXZ: FALSE
;   .BREAK .IF:TRUE
;   .CONT .IF: TRUE
;

	ASSUME	ebx: PTR asm_tok

ExpandCStrings PROC USES ebx tokenarray:PTR asm_tok

	xor	eax,eax
	.if	ModuleInfo.asmc_syntax ;&& Parse_Pass == PASS_1

		xor	edx,edx
		mov	ebx,tokenarray

		.while	[ebx].token != T_FINAL

			.if	[ebx].hll_flags & T_HLL_PROC

				.if	Parse_Pass == PASS_1

					GenerateCString( edx, tokenarray )
					.break
				.endif

				mov	ecx,1
				add	ebx,32
				.if	[ebx-16].token != T_OP_BRACKET

					asmerr( 3018, [ebx-32].string_ptr, [ebx-16].string_ptr )
					.break
				.endif

				.while	[ebx].token != T_FINAL

					mov	edx,[ebx].string_ptr
					movzx	eax,BYTE PTR [edx]

					.if	eax == '"'

						asmerr( 2004, [ebx].string_ptr )
						jmp	toend
					.elseif eax == ')'

						dec	ecx
						.break	.if Zero?

					.elseif eax == '('

						inc	ecx
					.endif
					add	ebx,16
				.endw

				xor	eax,eax
				.break
			.endif
			add	ebx,16
			add	edx,1
		.endw
	.endif
toend:
	ret

ExpandCStrings ENDP

StripSource PROC USES esi edi ebx,
	i:		UINT,		; index first token
	e:		UINT,		; index last token
	tokenarray:	PTR asm_tok
local	b[MAX_LINE_LEN]:SBYTE

	mov	b,0
	lea	eax,b

	mov	ebx,tokenarray
	mov	edi,ebx
	xor	esi,esi

	.while	esi < i

		.if	esi && [ebx].token != T_COMMA && [ebx].token != T_DOT

			strcat( eax, " " )
		.endif

		strcat( eax, [ebx].string_ptr )
		add	esi,1
		add	ebx,16
	.endw

	.if	ModuleInfo.Ofssize == USE32

		strcat( eax, " eax" )
	.elseif ModuleInfo.Ofssize == USE16

		strcat( eax, " ax" );
	.else

		strcat( eax, " rax" )
	.endif

	mov	ebx,e
	shl	ebx,4

	.if	[ebx+edi].token != T_FINAL

		strcat( eax, " " )
		strcat( eax, [ebx+edi].tokpos )
	.endif

	strcpy( ModuleInfo.currsource, eax )
	Tokenize( eax, 0, edi, TOK_DEFAULT )
	mov	ModuleInfo.token_count,eax
	mov	eax,STRING_EXPANDED
	ret
StripSource ENDP

LKRenderHllProc PROC USES esi edi ebx,
	dst:		LPSTR,
	i:		UINT,
	tokenarray:	PTR asm_tok
local	b[MAX_LINE_LEN]:SBYTE,
	br_count

	lea	esi,b
	mov	edi,i
	mov	ebx,edi
	shl	ebx,4
	add	ebx,tokenarray

	strcpy( esi, "invoke " ) ;  assume proc(...)
	strcat( esi, [ebx].string_ptr )

	inc	edi
	add	ebx,16

	.if	[ebx].token == T_OP_BRACKET

		add	ebx,16
		add	edi,1
		mov	br_count,0

		.if	[ebx].token != T_CL_BRACKET

			strcat( esi, "," )

			.while	1

				.if	[ebx].hll_flags & T_HLL_PROC
					LKRenderHllProc( dst, edi, tokenarray )
					cmp	eax,ERROR
					je	toend
				.endif
				movzx	eax,[ebx].token
				movzx	ecx,[ebx-16].token
				.switch
				  .case eax == T_FINAL
					.break
				  .case eax == T_OP_BRACKET
					inc	br_count
					.endc
				  .case eax == T_CL_BRACKET
					.break .if !br_count
					dec	br_count
				  .case eax == T_COMMA
				  .case eax == T_DOT
				  .case eax == T_OP_SQ_BRACKET
				  .case eax == T_CL_SQ_BRACKET
				  .case ecx == T_OP_SQ_BRACKET
				  .case ecx == T_CL_SQ_BRACKET
				  .case ecx == T_DOT
					.endc
				  .default
					strcat( esi, " " )
					.endc
				.endsw
				strcat( esi, [ebx].string_ptr )
				add	edi,1
				add	ebx,16
			.endw
		.endif
		.if	br_count || [ebx].token != T_CL_BRACKET
			mov	eax,ERROR
			jmp	toend
		.endif
		add	edi,1
	.endif

	; v2.21 -pe dllimport:<dll> external proto <no args> error
	;
	; externals need invoke for the [_]_imp_ prefix
	;
	mov	eax,i
	lea	ecx,[eax+3]
	inc	eax

	.if	edi == eax || ( edi == ecx && br_count == 0 )

		.if	SymFind( [ebx-32].string_ptr )

			.if	!( [eax].asym.state == SYM_EXTERNAL && [eax].asym.dll )

				xor	eax,eax
			.endif
		.endif

		.if	!eax

			strcpy( esi, "call" )
			add	eax,6
			strcat( esi, eax )
		.endif
	.endif

	mov	eax,dst
	.if	BYTE PTR [eax] != 0

		strcat( eax, addr EOLSTR )
	.endif
	strcat( eax, esi )
	StripSource( i, edi, tokenarray )
toend:
	ret
LKRenderHllProc ENDP

	ASSUME	ebx: NOTHING

RenderHllProc PROC USES esi edi,
	dst:		LPSTR,
	i:		UINT,
	tokenarray:	PTR asm_tok
local	oldstat:	input_status
	PushInputStatus( addr oldstat )
	LKRenderHllProc( dst, i, tokenarray )
	mov	esi,eax
	LclAlloc( MAX_LINE_LEN )
	mov	edi,eax
	strcpy( eax, ModuleInfo.currsource )
	PopInputStatus( addr oldstat )
	Tokenize( edi, 0, tokenarray, TOK_DEFAULT )
	mov	ModuleInfo.token_count,eax
	mov	eax,esi
	ret
RenderHllProc ENDP

;
; write assembly test lines to line queue.
; v2.11: local line buffer removed; src pointer has become a parameter.
;
AddLineQueue PROTO :LPSTR

QueueTestLines PROC PUBLIC USES esi edi src
	mov	esi,src
	.while	esi
		mov	edi,esi
		.if	strchr( esi, EOLCHAR )
			mov	BYTE PTR [eax],0
			inc	eax
		.endif
		mov	esi,eax
		.if	BYTE PTR [edi]
			AddLineQueue( edi )
		.endif
	.endw
	mov	eax,NOT_ERROR
	ret
QueueTestLines ENDP

ExpandHllProc PROC PUBLIC USES esi edi dst, i, tokenarray:PTR asm_tok

	mov	eax,dst
	mov	BYTE PTR [eax],0

	.if	ModuleInfo.asmc_syntax

		mov	esi,i
		mov	edi,esi
		shl	edi,4
		add	edi,tokenarray

		.while	esi < ModuleInfo.token_count
			.if	[edi].asm_tok.hll_flags & T_HLL_PROC
				ExpandCStrings( tokenarray )
				RenderHllProc( dst, esi, tokenarray )
				cmp	eax,ERROR
				je	toend
				.break
			.endif
			add	edi,16
			add	esi,1
		.endw
	.endif
	mov	eax,NOT_ERROR
toend:
	ret
ExpandHllProc ENDP

QueueTestLines proto :dword

EvaluateHllExpression PROC USES esi edi ebx,
	hll:		PTR hll_item,
	i:		PTR SINT,
	tokenarray:	PTR asm_tok,
	ilabel:		SDWORD,
	is_true:	DWORD,
	buffer:		LPSTR
local	hllop:		hll_opnd,
	b[MAX_LINE_LEN]:SBYTE

	mov	esi,i
	mov	ebx,tokenarray

	xor	eax,eax
	mov	hllop.lastjmp,eax
	mov	hllop.lasttruelabel,eax

	mov	edx,hll
	mov	eax,[edx].hll_item.flags
	and	eax,HLLF_EXPRESSION

	.if	ModuleInfo.asmc_syntax && !eax && [ebx].asm_tok.hll_flags & T_HLL_DELAY

		mov	edi,[esi]
		.while	edi < ModuleInfo.token_count

			mov	eax,edi
			shl	eax,4
			.if	[ebx+eax].asm_tok.hll_flags & T_HLL_MACRO

				strcpy( buffer, [ebx].asm_tok.tokpos )
				mov	eax,hll
				or	[eax].hll_item.flags,HLLF_EXPRESSION

				.if	[ebx].asm_tok.hll_flags & T_HLL_DELAYED

					or    [eax].hll_item.flags,HLLF_DELAYED
				.endif

				mov	eax,NOT_ERROR
				jmp	toend
			.endif
			add	edi,1
		.endw
	.endif

	lea	edi,b

	.if	ExpandHllProc( edi, [esi], ebx ) != ERROR

		mov	ecx,buffer
		mov	BYTE PTR [ecx],0

		.if	GetExpression( hll, esi, ebx, ilabel, is_true,
				ecx, addr hllop ) != ERROR

			mov	eax,[esi]
			shl	eax,4
			add	ebx,eax

			.if	[ebx].asm_tok.token != T_FINAL

				asmerr( 2154 )
				jmp	toend
			.endif

			mov	eax,hll
			mov	eax,[eax].hll_item.flags
			and	eax,HLLF_IFD or HLLF_IFW or HLLF_IFB

			.if	eax && BYTE PTR [edi]

				; "cmp ax ," ...

				mov	edx,buffer
				mov	ecx," xa "
				.if	ModuleInfo.Ofssize == USE64

					mov	ecx,"xar "
				.elseif	 ModuleInfo.Ofssize == USE32

					mov	ecx,"xae "
				.endif

				.if	[edx+3] == ecx

					.switch eax

					  .case HLLF_IFD
						.if	ModuleInfo.Ofssize != USE64

							asmerr( 2085 )
							jmp	toend
						.endif
						mov	BYTE PTR [edx+4],'e'
						.endc

					  .case HLLF_IFW
						.if	ModuleInfo.Ofssize == USE16

							asmerr( 2085 )
							jmp	toend
						.endif
						mov	BYTE PTR [edx+4],' '
						.endc
					  .case HLLF_IFB
						.if	ModuleInfo.Ofssize == USE16

							mov	BYTE PTR [edx+5],'l'
						.else
							mov	DWORD PTR [edx+4],'la  '
						.endif
						.endc
					.endsw
				.endif
			.endif

			.if	BYTE PTR [edi]

				strlen( edi )
				mov	WORD PTR [edi+eax],EOLCHAR
				strcat( edi, buffer )
				strcpy( buffer, edi )
			.endif

			mov	eax,NOT_ERROR
		.endif
	.endif
toend:
	ret

EvaluateHllExpression ENDP

; for .UNTILCXZ: check if expression is simple enough.
; what's acceptable is ONE condition, and just operators == and !=
; Constants (0 or != 0) are also accepted.

CheckCXZLines PROC USES esi edi ebx p

	mov	esi,p
	mov	edi,1
	xor	ebx,ebx
	;
	; syntax ".untilcxz 1" has a problem: there's no "jmp" generated at all.
	; if this syntax is to be supported, activate the #if below.
	;
	mov	eax,[esi]
	.while	al
		.if	al == EOLCHAR
			mov	edi,1
			add	ebx,edi
		.elseif edi
			xor	edi,edi
			.if	al == 'j'
				shr	eax,8
				.if	al == 'm' && !ebx
					mov	edx,2	; 2 chars, to replace "jmp" by "loope"
				.elseif ebx == 1 && ( al == 'z' || (al == 'n' && ah == 'z') )
					mov	edx,3	; 3 chars, to replace "jz"/"jnz" by "loopz"/"loopnz"
				.else			; anything else is "too complex"
					mov	eax,ERROR
					jmp	toend
				.endif
				strlen( esi )
				.while	SDWORD PTR eax >= 0
					add	esi,eax
					mov	cl,[esi]
					mov	[esi+edx],cl
					sub	esi,eax
					dec	eax
				.endw
				mov	eax,"pool"
				mov	[esi],eax
				.if	edx == 2
					mov	BYTE PTR [esi+4],'e'
				.endif
			.endif
		.endif
		add	esi,1
		mov	eax,[esi]
	.endw
	mov	eax,NOT_ERROR
	.if	ebx > 2
		mov	eax,ERROR
	.endif
toend:
	ret
CheckCXZLines ENDP

ExpandHllExpression PROC USES esi edi ebx,
	hll:		PTR hll_item,
	i:		PTR,
	tokenarray:	PTR asm_tok,
	ilabel:		SINT,
	is_true:	SINT,
	buffer:		LPSTR
local	rc:		DWORD,
	oldstat:	input_status,
	delayed:	BYTE

	mov	rc,NOT_ERROR
	mov	esi,hll
	mov	ebx,tokenarray
	mov	edi,buffer

	PushInputStatus( addr oldstat )

	.if	[esi].hll_item.flags & HLLF_WHILE
		mov	edi,[esi].hll_item.condlines
	.endif
	strcpy( ModuleInfo.currsource, edi )
	Tokenize( ModuleInfo.currsource, 0, ebx, TOK_DEFAULT )
	mov	ModuleInfo.token_count,eax

	.if	Parse_Pass == PASS_1

		.if	ModuleInfo.line_queue.head
			RunLineQueue()
		.endif
		.if	[esi].hll_item.flags & HLLF_DELAYED
			mov	NoLineStore,1
			ExpandLine( ModuleInfo.currsource, ebx )
			mov	NoLineStore,0
			cmp	eax,NOT_ERROR
			jne	toend
		.endif
		.if	[esi].hll_item.flags & HLLF_WHILE
			and	[esi].hll_item.flags,not HLLF_WHILE
		.endif
		EvaluateHllExpression( hll, i, ebx, ilabel, is_true, buffer )
		mov	rc,eax
		QueueTestLines( buffer )

	.elseif Parse_Pass != PASS_1

		.if	ModuleInfo.list
			LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
		.endif
		RunLineQueue()
		ExpandLine( ModuleInfo.currsource, ebx )
		mov	rc,eax
		.if	eax == NOT_ERROR
			.if	[esi].hll_item.flags & HLLF_WHILE
				and	[esi].hll_item.flags,not HLLF_WHILE
			.endif
			EvaluateHllExpression( esi, i, ebx, ilabel, is_true, buffer )
			mov	rc,eax
			QueueTestLines( buffer )
		.endif
	.endif

	PopInputStatus( addr oldstat )
	Tokenize( ModuleInfo.currsource, 0, ebx, TOK_DEFAULT )
	mov	ModuleInfo.token_count,eax
	mov	eax,hll
	and	[eax].hll_item.flags,not HLLF_EXPRESSION
	mov	eax,rc
toend:
	ret
ExpandHllExpression ENDP

	ASSUME	esi:PTR hll_item

RenderCase PROC USES esi edi ebx hll:PTR hll_item, case:PTR hll_item, buffer:LPSTR
	mov	esi,hll
	mov	ebx,case
	mov	edi,buffer
	mov	edx,[ebx].hll_item.condlines
	.if	!edx
		AddLineQueueX( "jmp %s", GetLabelStr( [ebx].hll_item.labels[LSTART*4], edi ) )
	.else
		.if	strchr( edx, '.' ) && BYTE PTR [eax+1] == '.'
			mov	BYTE PTR [eax],0
			add	eax,2
			push	eax
			AddLineQueueX( "cmp %s,%s", [esi].condlines, edx )
			AddLineQueueX( "jb %s", GetLabelStr( GetHllLabel(), edi ) )
			pop	eax
			AddLineQueueX( "cmp %s,%s", [esi].condlines, eax )
			lea	eax,[edi+16]
			AddLineQueueX( "jbe %s", GetLabelStr( [ebx].hll_item.labels[LSTART*4], eax ) )
			AddLineQueueX( "%s%s", edi, addr LABELQUAL )
		.else
			AddLineQueueX( "cmp %s,%s", [esi].condlines, edx )
			AddLineQueueX( "je %s", GetLabelStr( [ebx].hll_item.labels[LSTART*4], edi ) )
		.endif
	.endif
	ret
RenderCase ENDP

RenderCCMP PROC USES esi edi ebx hll:PTR hll_item, buffer:LPSTR
	mov	esi,hll
	mov	edi,buffer
	AddLineQueueX( "%s%s", edi, addr LABELQUAL )
	mov	ebx,[esi].caselist
	.while	ebx
		RenderCase( esi, ebx, edi )
		mov	ebx,[ebx].hll_item.caselist
	.endw
	ret
RenderCCMP ENDP

GetLowCount PROC hll:PTR hll_item, min, dist
	mov	ecx,min
	add	ecx,dist
	mov	edx,hll
	xor	eax,eax
	mov	edx,[edx].hll_item.caselist
	.while	edx
		.if	[edx].hll_item.flags & HLLF_TABLE && \
			SDWORD PTR ecx >= [edx].hll_item.labels
			add	eax,1
		.endif
		mov	edx,[edx].hll_item.caselist
	.endw
	ret
GetLowCount ENDP

GetHighCount PROC hll:PTR hll_item, max, dist
	mov	ecx,max
	sub	ecx,dist
	mov	edx,hll
	xor	eax,eax
	mov	edx,[edx].hll_item.caselist
	.while	edx
		.if	[edx].hll_item.flags & HLLF_TABLE && \
			SDWORD PTR ecx <= [edx].hll_item.labels
			add	eax,1
		.endif
		mov	edx,[edx].hll_item.caselist
	.endw
	ret
GetHighCount ENDP

SetLowCount PROC USES esi hll:PTR hll_item, count, min, dist
	mov	ecx,min
	mov	edx,count
	add	ecx,dist
	xor	eax,eax
	mov	esi,hll
	mov	esi,[esi].caselist
	.while	esi
		.if	[esi].flags & HLLF_TABLE && SDWORD PTR ecx < [esi].labels
			and	[esi].flags,NOT HLLF_TABLE
			dec	DWORD PTR [edx]
			add	eax,1
		.endif
		mov	esi,[esi].caselist
	.endw
	mov	edx,[edx]
	ret
SetLowCount ENDP

SetHighCount PROC USES esi hll:PTR hll_item, count, max, dist
	mov	ecx,max
	mov	edx,count
	sub	ecx,dist
	xor	eax,eax
	mov	esi,hll
	mov	esi,[esi].caselist
	.while	esi
		.if	[esi].flags & HLLF_TABLE && SDWORD PTR ecx > [esi].labels
			and	[esi].flags,NOT HLLF_TABLE
			dec	DWORD PTR [edx]
			add	eax,1
		.endif
		mov	esi,[esi].caselist
	.endw
	mov	edx,[edx]
	ret
SetHighCount ENDP

GetCaseVal PROC FASTCALL hll, val
	mov	eax,[ecx].hll_item.caselist
	.while	eax
		.if	[eax].hll_item.flags & HLLF_TABLE && \
			[eax].hll_item.labels == edx
			.break
		.endif
		mov	ecx,eax
		mov	eax,[eax].hll_item.caselist
	.endw
	ret
GetCaseVal ENDP

RemoveVal PROC FASTCALL hll, val
	.if	GetCaseVal()
		and	[eax].hll_item.flags,NOT HLLF_TABLE
		mov	eax,1
	.endif
	ret
RemoveVal ENDP

GetCaseValue PROC USES esi edi ebx hll, tokenarray, dcount, scount
	local	i, opnd:expr

	xor	edi,edi ; dynamic count
	xor	ebx,ebx ; static count

	mov	esi,hll
	mov	esi,[esi].caselist
	.while	esi
		.if	[esi].flags & HLLF_NUM
			or	[esi].flags,HLLF_TABLE
			Tokenize( [esi].condlines, 0, tokenarray, TOK_DEFAULT )
			mov	ModuleInfo.token_count,eax
			mov	i,0
			mov	ecx,eax
			EvalOperand( addr i, tokenarray, ecx, addr opnd, EXPF_NOERRMSG )
			.break .if eax != NOT_ERROR
			mov	eax,DWORD PTR opnd.value64
			mov	edx,DWORD PTR opnd.value64[4]
			.if	opnd.kind == EXPR_ADDR
				mov	ecx,opnd.sym
				add	eax,[ecx].asym._offset
				xor	edx,edx
			.endif
			mov	[esi].labels[LTEST*4],eax
			mov	[esi].labels[LEXIT*4],edx
			inc	ebx
		.elseif [esi].condlines
			inc	edi
		.endif
		mov	esi,[esi].caselist
	.endw
	Tokenize( ModuleInfo.currsource, 0, tokenarray, TOK_DEFAULT )
	mov	ModuleInfo.token_count,eax

	mov	eax,dcount
	mov	[eax],edi
	mov	eax,scount
	mov	[eax],ebx
	;
	; error A3022 : .CASE redefinition : %s(%d) : %s(%d)
	;
	.if	ebx && Parse_Pass != PASS_1
		mov	esi,hll
		mov	esi,[esi].caselist
		mov	edi,[esi].caselist
		.while	edi
			.if	[esi].flags & HLLF_NUM
				.if	GetCaseVal( esi, [esi].labels )
					asmerr( 3022,
						[esi].condlines,
						[esi].labels,
						[eax].hll_item.condlines,
						[eax].hll_item.labels )
				.endif
			.endif
			mov	esi,[esi].caselist
			mov	edi,[esi].caselist
		.endw
	.endif

	mov	eax,ebx
	ret
GetCaseValue ENDP

GetMaxCaseValue PROC USES esi edi ebx hll, min, max, min_table, max_table

	mov	esi,hll
	xor	edi,edi
	mov	eax,80000000h
	mov	edx,7FFFFFFFh
	mov	esi,[esi].caselist
	.while	esi
		.if	[esi].flags & HLLF_TABLE
			inc	edi
			mov	ecx,[esi].labels
			.if	SDWORD PTR eax <= ecx
				mov	eax,ecx
			.endif
			.if	SDWORD PTR edx >= ecx
				mov	edx,ecx
			.endif
		.endif
		mov	esi,[esi].caselist
	.endw

	.if	!edi
		mov	eax,edi
		mov	edx,edi
	.endif

	mov	ebx,max
	mov	ecx,min
	mov	[ebx],eax
	mov	[ecx],edx

	mov	esi,hll
	mov	ecx,1
	mov	eax,MIN_JTABLE
	.if	!( [esi].flags & HLLF_ARGREG )
		add	eax,2
		add	ecx,1
		.if	!( [esi].flags & HLLF_ARG16 or HLLF_ARG32 or HLLF_ARG64 )
			add	eax,1
			.if	!( ModuleInfo.hll_switch & SWITCH_REGAX )
				add	eax,10
			.endif
		.endif
	.endif
	mov	esi,min_table
	mov	[esi],eax
	mov	esi,max_table
	mov	eax,edi
	shl	eax,cl
	mov	[esi],eax

	mov	eax,[ebx]
	sub	eax,edx
	mov	ecx,edi
	add	eax,1
	ret
GetMaxCaseValue ENDP

RenderCaseExit PROC FASTCALL hll, buffer
	mov	eax,hll
	.while	[eax].hll_item.caselist
		mov	eax,[eax].hll_item.caselist
	.endw
	.if	eax != hll
		.if	!( [eax].hll_item.flags & HLLF_ENDCOCCUR )
			.if	Parse_Pass == PASS_1 && !( ModuleInfo.hll_switch & SWITCH_PASCAL )
				asmerr( 7007 )
			.endif
			AddLineQueueX( "jmp %s", GetLabelStr( [hll].hll_item.labels[LEXIT*4], buffer ) )
		.endif
	.endif
	ret
RenderCaseExit ENDP

	ASSUME	esi: PTR asm_tok

IsCaseColon PROC USES esi edi ebx tokenarray:PTR asm_tok
	mov	esi,tokenarray
	xor	edi,edi
	xor	edx,edx
	.while	[esi].token != T_FINAL
		mov	al,[esi].token
		mov	ah,[esi-16].token
		mov	ecx,[esi-16].tokval
		.switch

		  .case al == T_OP_BRACKET : inc edx : .endc
		  .case al == T_CL_BRACKET : dec edx : .endc

		  .case al == T_COLON

			.endc	.if edx
			.endc	.if ah == T_REG && ecx >= T_ES && ecx <= T_ST

			mov	[esi].token,T_FINAL
			mov	edi,esi
			.break
		.endsw
		add	esi,16
	.endw
	mov	eax,edi
	ret
IsCaseColon ENDP

	ASSUME	ebx: PTR asm_tok

RenderMultiCase PROC USES esi edi ebx,
	i:		PTR SDWORD,
	buffer:		PTR SBYTE,
	tokenarray:	PTR asm_tok
local	result:		DWORD,
	colon:		DWORD

	mov	ebx,tokenarray
	add	ebx,16
	mov	eax,ebx
	mov	esi,ebx
	xor	edi,edi
	mov	result,edi

	IsCaseColon( ebx )
	mov	colon,eax

	.while	1
		;
		; Split .case 1,2,3 to
		;
		;	.case 1
		;	.case 2
		;	.case 3
		;
		mov	al,[ebx].token
		.switch al

		  .case T_FINAL : .break

		  .case T_OP_BRACKET : inc edi : .endc
		  .case T_CL_BRACKET : dec edi : .endc

		  .case T_COMMA
			.endc .if edi

			mov	edx,[ebx].tokpos
			mov	BYTE PTR [edx],0
			strcpy( buffer, [esi].tokpos )
			lea	esi,[ebx+16]
			mov	BYTE PTR [edx],','

			inc	result
			AddLineQueueX( ".case %s", buffer )
			mov	[ebx].token,T_FINAL
		.endsw
		add	ebx,16
	.endw

	mov	ebx,colon
	.if	ebx
		mov	[ebx].token,T_COLON
	.endif

	mov	eax,result
	.if	eax

		AddLineQueueX( ".case %s", [esi].tokpos )

		mov	ebx,tokenarray
		xor	eax,eax
		.while	[ebx].token != T_FINAL
			add	eax,1
			add	ebx,16
		.endw
		mov	ebx,i
		mov	[ebx],eax

		.if	ModuleInfo.hll_switch & SWITCH_PASCAL

			and	ModuleInfo.hll_switch,NOT SWITCH_PASCAL

			.if	ModuleInfo.list
				LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
			.endif
			RunLineQueue()

			or	ModuleInfo.hll_switch,SWITCH_PASCAL
		.endif
		mov	eax,1
	.endif
	ret
RenderMultiCase ENDP

CompareMaxMin PROC reg, max, min, around
	AddLineQueueX( "cmp %s,%d", reg, min )
	AddLineQueueX( "jl %s", around )
	AddLineQueueX( "cmp %s,%d", reg, max )
	AddLineQueueX( "jg %s", around )
	ret
CompareMaxMin ENDP

;
; Move .SWITCH <arg> to [R|E]AX
;
GetSwitchArg PROC USES ebx reg, flags, arg

	.if	!( ModuleInfo.hll_switch & SWITCH_REGAX )
		AddLineQueueX( "push %s", reg )
	.endif

	mov	eax,flags
	mov	edx,reg
	mov	ebx,arg

	.if	!( eax & HLLF_ARG16 or HLLF_ARG32 or HLLF_ARG64 )
		;
		; BYTE value
		;
		mov	ecx,ModuleInfo.curr_cpu
		and	ecx,P_CPU_MASK
		.if	ecx >= P_386
			.if	eax & HLLF_ARGMEM
				AddLineQueueX( "movsx %s,BYTE PTR %s", edx, ebx )
			.else
				AddLineQueueX( "movsx %s,%s", edx, ebx )
			.endif
		.else
			.if	_stricmp( "al", ebx )
				AddLineQueueX( "mov al,%s", ebx )
			.endif
			AddLineQueue ( "cbw" )
		.endif

	.elseif eax & HLLF_ARG16
		;
		; WORD value
		;
		.if	ModuleInfo.Ofssize == USE16
			.if	eax & HLLF_ARGMEM
				AddLineQueueX( "mov %s,WORD PTR %s", edx, ebx )
			.elseif _stricmp( ebx, edx )
				AddLineQueueX( "mov %s,%s", edx, ebx )
			.endif
		.elseif eax & HLLF_ARGMEM
			AddLineQueueX( "movsx %s,WORD PTR %s", edx, ebx )
		.else
			AddLineQueueX( "movsx %s,%s", edx, ebx )
		.endif

	.elseif eax & HLLF_ARG32
		;
		; DWORD value
		;
		.if	ModuleInfo.Ofssize == USE32
			.if	eax & HLLF_ARGMEM
				AddLineQueueX( "mov %s,DWORD PTR %s", edx, ebx )
			.elseif _stricmp( ebx, edx )
				AddLineQueueX( "mov %s,%s", edx, ebx )
			.endif
		.elseif eax & HLLF_ARGMEM
			AddLineQueueX( "movsx %s,DWORD PTR %s", edx, ebx )
		.else
			AddLineQueueX( "movsx %s,%s", edx, ebx )
		.endif
	.else
		;
		; QWORD value
		;
		AddLineQueueX( "mov %s,QWORD PTR %s", edx, ebx )
	.endif

	ret
GetSwitchArg ENDP

	ASSUME	esi: PTR hll_item
	ASSUME	ebx:	PTR hll_item

RenderSwitch PROC USES esi edi ebx,
	hll:		PTR hll_item,
	tokenarray:	PTR asm_tok,
	buffer:		LPSTR,	; *switch.labels[LSTART]
	l_exit:		LPSTR	; *switch.labels[LEXIT]

local	r_dw:		DWORD,	; dw/dd/dq
	r_db:		DWORD,	; "DB"/"DW"
	r_ax:		DWORD,	; ax/eax/rax
	r_sp:		DWORD,	; esp/rsp
	r_size:		DWORD,	; 2/4/8
	dynamic:	DWORD,	; number of dynmaic cases
	default:	DWORD,	; hll_item * if exist
	static:		DWORD,	; number of static const values
	tables:		DWORD,	; number of tables
	lcount:		DWORD,	; number of labels in table
	icount:		DWORD,	; number of index to labels in table
	tcases:		DWORD,	; number of cases in table
	ncases:		DWORD,	; number of cases not in table
	min_table:	DWORD,
	max_table:	DWORD,
	min[2]:		SDWORD, ; minimum const value
	max[2]:		SDWORD, ; maximum const value
	dist:		SDWORD, ; max - min
	l_start[16]:	SBYTE,	; current start label
	l_jtab[16]:	SBYTE,	; jump table address
	labelx[16]:	SBYTE,	; label symbol
	use_index:	BYTE


	mov	esi,hll
	mov	edi,buffer
	xor	eax,eax
	mov	tables,eax
	mov	ncases,eax
	mov	default,eax
	;
	; get static case-count
	;
	GetCaseValue( esi, tokenarray, addr dynamic, addr static )

	.if	!( ModuleInfo.hll_switch & SWITCH_TABLE ) || eax < MIN_JTABLE
		;
		; Time NOTABLE/TABLE
		;
		; .case * 3	4	7	8	9	10	16	60
		; NOTABLE 1401	2130	5521	5081	7681	9481	18218	158245
		; TABLE	  1521	3361	4402	6521	7201	7881	9844	68795
		; elseif  1402	4269	5787	7096	8481	10601	22923	212888
		;
		RenderCCMP( esi, edi )
		jmp	toend
	.endif

	mov	ecx,2
	mov	edx,"xa"
	mov	eax,"wd"
	.if	ModuleInfo.Ofssize == USE32
		mov	ecx,4
		mov	edx,"xae"
		mov	eax,"dd"
		mov	r_sp,"pse"
	.elseif ModuleInfo.Ofssize == USE64
		mov	ecx,8
		mov	edx,"xar"
		mov	eax,"qd"
		mov	r_sp,"psr"
	.endif
	mov	r_dw,eax
	mov	r_ax,edx
	mov	r_size,ecx

	strcpy( addr l_start, edi )
	;
	; flip exit to default if exist
	;
	.if	[esi].flags & HLLF_ELSEOCCUR
		mov	ebx,[esi].caselist
		mov	eax,esi
		.while	ebx
			.if	[ebx].flags & HLLF_DEFAULT
				mov	[eax].hll_item.caselist,0
				mov	default,ebx
				GetLabelStr( [ebx].labels[LSTART*4], l_exit )
				.break
			.endif
			mov	eax,ebx
			mov	ebx,[ebx].caselist
		.endw
	.endif
	mov	cl,ModuleInfo.casealign
	.if	cl
		mov	eax,1
		shl	eax,cl
		AddLineQueueX( "ALIGN %d", eax )
	.endif
	AddLineQueueX( "%s%s", addr l_start, addr LABELQUAL )

	.if	dynamic
		mov	eax,esi
		mov	ebx,[esi].caselist
		.while	ebx
			.if !( [ebx].flags & HLLF_NUM )
				mov	ecx,[ebx].caselist
				mov	[eax].hll_item.caselist,ecx
				RenderCase( esi, ebx, edi )
			.endif
			mov	eax,ebx
			mov	ebx,[ebx].caselist
		.endw
	.endif

	.while	[esi].condlines

		GetMaxCaseValue( esi, addr min, addr max, addr min_table, addr max_table )
		mov	dist,eax
		mov	tcases,ecx
		mov	ncases,0

		.break	.if ecx < min_table
		mov	ebx,ecx

		.while	ebx >= min_table && max > edx && eax > max_table

			GetLowCount ( esi, min, max_table )
			mov	ebx,eax
			GetHighCount( esi, max, max_table )

			.switch
			  .case ebx < min_table
				.break	.if !RemoveVal( esi, min )
				sub	tcases,eax
				.endc
			  .case eax < min_table
				.break	.if !RemoveVal( esi, max )
				sub	tcases,eax
				.endc
			  .case ebx >= eax
				mov	ebx,tcases
				SetLowCount( esi, addr tcases, min, max_table )
				.endc
			  .default
				mov	ebx,tcases
				SetHighCount( esi, addr tcases, max, max_table )
				.endc
			.endsw
			add	ncases,eax

			GetMaxCaseValue( esi, addr min, addr max, addr min_table, addr max_table )
			mov	dist,eax
			.break .if ebx == tcases
			mov	ebx,tcases
		.endw
		mov	eax,tcases
		.break	.if eax < min_table

		mov	use_index,0
		.if	eax < dist && ModuleInfo.Ofssize == USE64
			inc	use_index
		.endif
		;
		; Create the jump table lable
		;
		GetLabelStr( GetHllLabel(), addr l_jtab )

		mov	edi,l_exit
		.if	ncases
			GetLabelStr( GetHllLabel(), addr l_start )
			mov	edi,eax
		.endif

		mov	ebx,[esi].condlines
		mov	eax,[esi].flags
		mov	cl,ModuleInfo.Ofssize

		.switch

		  .case cl == USE16
			.if	!( eax & HLLF_NOTEST )
				CompareMaxMin( ebx, max, min, edi )
			.endif
			.if	!( ModuleInfo.hll_switch & SWITCH_REGAX )
				AddLineQueue( "push ax" )
			.endif
			.if	[esi].flags & HLLF_ARGREG

				.if	ModuleInfo.hll_switch & SWITCH_REGAX
					.if	_stricmp( "ax", ebx )
						AddLineQueueX( "mov ax,%s", ebx )
					.endif
					AddLineQueue( "xchg ax,bx" )
				.else
					AddLineQueue( "push bx" )
					AddLineQueue( "push ax" )
					.if	_stricmp( "bx", ebx )
						AddLineQueueX( "mov bx,%s", ebx )
					.endif
				.endif
			.else
				.if	!( ModuleInfo.hll_switch & SWITCH_REGAX )
					AddLineQueue( "push bx" )
				.endif
				GetSwitchArg( "ax", [esi].flags, ebx )
				.if	ModuleInfo.hll_switch & SWITCH_REGAX
					AddLineQueue( "xchg ax,bx" )
				.else
					AddLineQueue( "mov bx,ax" )
				.endif
			.endif
			.if	min
				AddLineQueueX( "sub bx,%d", min )
			.endif
			AddLineQueue ( "add bx,bx" )

			.if	ModuleInfo.hll_switch & SWITCH_REGAX

				AddLineQueueX( "mov bx,cs:[bx+%s]", addr l_jtab )
				AddLineQueue ( "xchg ax,bx" )
				AddLineQueue ( "jmp ax" )
			.else
				AddLineQueueX( "mov ax,cs:[bx+%s]", addr l_jtab )
				AddLineQueue ( "mov bx,sp" )
				AddLineQueue ( "mov ss:[bx+4],ax" )
				AddLineQueue ( "pop ax" )
				AddLineQueue ( "pop bx" )
				AddLineQueue ( "retn" )
			.endif
			.endc

		  .case !( eax & HLLF_ARGREG )

			.if !( cl == USE64 && eax & HLLF_ARG3264 )

				.if	!( eax & HLLF_NOTEST )
					CompareMaxMin( ebx, max, min, edi )
				.endif
				GetSwitchArg( addr r_ax, [esi].flags, ebx )

				lea	ebx,r_ax
				.if	use_index
					.if	dist < 256
						AddLineQueueX( "movzx %s,BYTE PTR [%s+IT%s-(%d)]", ebx, ebx, addr l_jtab, min )
					.else
						AddLineQueueX( "movzx %s,WORD PTR [%s*2+IT%s-(%d*2)]", ebx, ebx, addr l_jtab, min )
					.endif
					.if	ModuleInfo.hll_switch & SWITCH_REGAX
						AddLineQueueX( "jmp [%s*%d+%s]", ebx, r_size, addr l_jtab )
					.else
						AddLineQueueX( "mov %s,[%s*%d+%s]", ebx, ebx, r_size, addr l_jtab )
					.endif
				.else
					.if	ModuleInfo.hll_switch & SWITCH_REGAX
						AddLineQueueX( "jmp [%s*%d+%s-(%d*%d)]", ebx, r_size, addr l_jtab, min, r_size )
					.else
						AddLineQueueX( "mov %s,[%s*%d+%s-(%d*%d)]", ebx, ebx, r_size, addr l_jtab, min, r_size )
					.endif
				.endif
				.if	!( ModuleInfo.hll_switch & SWITCH_REGAX )
					AddLineQueueX( "xchg %s,[%s]", ebx, addr r_sp )
					AddLineQueue ( "retn" )
				.endif
				.endc
			.endif

			strcpy( ebx, "rax" )
			mov	eax,[esi].flags

		  .default

			.if	!( eax & HLLF_NOTEST )
				CompareMaxMin( ebx, max, min, edi )
			.endif
			.if	use_index
				.if	!( ModuleInfo.hll_switch & SWITCH_REGAX )
					AddLineQueueX( "push %s", ebx )
				.endif
				.if	dist < 256
					AddLineQueueX( "movzx %s,BYTE PTR [%s+IT%s-(%d)]", ebx, ebx, addr l_jtab, min )
				.else
					AddLineQueueX( "movzx %s,WORD PTR [%s*2+IT%s-(%d*2)]", ebx, ebx, addr l_jtab, min )
				.endif
				.if	ModuleInfo.hll_switch & SWITCH_REGAX
					AddLineQueueX( "jmp [%s*%d+%s]", ebx, r_size, addr l_jtab )
				.else
					AddLineQueueX( "mov %s,[%s*%d+%s]", ebx, ebx, r_size, addr l_jtab )
					AddLineQueueX( "xchg %s,[%s]", ebx, addr r_sp )
					AddLineQueue ( "retn" )
				.endif
			.else
				AddLineQueueX( "jmp [%s*%d+%s-(%d*%d)]", ebx, r_size, addr l_jtab, min, r_size )
			.endif
			.endc
		.endsw

		;
		; Create the jump table
		;
		AddLineQueueX( "ALIGN %d", r_size )
		AddLineQueueX( "%s%s", addr l_jtab, addr LABELQUAL )

		.if	use_index

			push	edi
			or	ebx,-1	; offset
			or	edi,-1	; table index

			mov	esi,[esi].caselist
			.while	esi

				.if	[esi].flags & HLLF_TABLE

					.break	.if !SymFind( GetLabelStr( [esi].labels[LSTART*4],
							      addr labelx ) )

					.if	ebx != [eax].asym._offset

						mov	ebx,[eax].asym._offset
						inc	edi
					.endif
					;
					; use case->next pointer as index...
					;
					mov	[esi].next,edi
				.endif
				mov	esi,[esi].caselist
			.endw
			mov	edx,esi
			inc	edi
			mov	lcount,edi
			pop	edi
			mov	esi,hll

			or	ebx,-1
			mov	esi,[esi].caselist
			.while	esi

				.if	[esi].flags & HLLF_TABLE && ebx != [esi].next

					AddLineQueueX( " %s %s ; .case %s",
						       addr r_dw,
						       GetLabelStr( [esi].labels[LSTART*4],
								    addr labelx ),
						       [esi].condlines )

					mov	ebx,[esi].next
				.endif
				mov	esi,[esi].caselist
			.endw
			mov	esi,hll

			AddLineQueueX( " %s %s ; .default", addr r_dw, l_exit )

			mov	eax,max
			sub	eax,min
			inc	eax
			mov	icount,eax
			mov	ebx,"BD"
			.if	eax > 256
				.if	ModuleInfo.Ofssize == USE16
					asmerr( 2022, 1, 2 )
					jmp	toend
				.endif
				mov	ebx,"WD"
			.endif
			mov	r_db,ebx
			AddLineQueueX( "IT%s LABEL BYTE", addr l_jtab )

			xor	ebx,ebx
			.while	ebx < icount
				;
				; loop from min value
				;
				mov	eax,min
				add	eax,ebx

				.if	GetCaseVal( esi, eax )
					;
					; Unlink block
					;
					mov	edx,[eax].hll_item.caselist
					mov	[ecx].hll_item.caselist,edx
					;
					; write block to table
					;
					AddLineQueueX( " %s %d", addr r_db, [eax].hll_item.next )

				.else
					;
					; else make a jump to exit or default label
					;
					AddLineQueueX( " %s %d", addr r_db, lcount )
				.endif
				inc	ebx
			.endw
			AddLineQueueX( "ALIGN %d", r_size )
		.else
			xor	ebx,ebx
			.while	ebx < dist
				;
				; loop from min value
				;
				mov	eax,min
				add	eax,ebx

				.if	GetCaseVal( esi, eax )
					;
					; Unlink block
					;
					mov	edx,[eax].hll_item.caselist
					mov	[ecx].hll_item.caselist,edx
					;
					; write block to table
					;
					mov	ecx,[eax].hll_item.labels[LSTART*4]
					AddLineQueueX( "%s %s", addr r_dw,
						GetLabelStr( ecx, buffer ) )
				.else
					;
					; else make a jump to exit or default label
					;
					AddLineQueueX( "%s %s", addr r_dw, l_exit )
				.endif
				inc	ebx
			.endw
		.endif

		.if	ncases
			;
			; Create the new start label
			;
			AddLineQueueX( "%s%s", addr l_start, addr LABELQUAL )

			mov	ebx,[esi].caselist
			.while	ebx
				or	[ebx].flags,HLLF_TABLE
				mov	ebx,[ebx].caselist
			.endw
		.endif
	.endw

	mov	ebx,[esi].caselist
	.while	ebx
		RenderCase( esi, ebx, buffer )
		mov	ebx,[ebx].caselist
	.endw
	.if	default && [esi].caselist
		AddLineQueueX( "jmp %s", l_exit )
	.endif
toend:
	ret
RenderSwitch ENDP

GetJumpString proc cmd

	mov	eax,cmd
	.switch eax
	  .case T_DOT_IFA
	  .case T_DOT_IFNBE:	mov eax,@CStr( "jbe" ): .endc
	  .case T_DOT_IFB
	  .case T_DOT_IFC
	  .case T_DOT_IFNAE:	mov eax,@CStr( "jae" ): .endc
	  .case T_DOT_IFE
	  .case T_DOT_IFZ:	mov eax,@CStr( "jne" ): .endc
	  .case T_DOT_IFG
	  .case T_DOT_IFNLE:	mov eax,@CStr( "jle" ): .endc
	  .case T_DOT_IFL
	  .case T_DOT_IFNGE:	mov eax,@CStr( "jge" ): .endc
	  .case T_DOT_IFNB
	  .case T_DOT_IFNC
	  .case T_DOT_IFAE:	mov eax,@CStr( "jb " ): .endc
	  .case T_DOT_IFBE
	  .case T_DOT_IFNA:	mov eax,@CStr( "ja " ): .endc
	  .case T_DOT_IFGE
	  .case T_DOT_IFNL:	mov eax,@CStr( "jl " ): .endc
	  .case T_DOT_IFLE
	  .case T_DOT_IFNG:	mov eax,@CStr( "jg " ): .endc
	  .case T_DOT_IFS:	mov eax,@CStr( "jns" ): .endc
	  .case T_DOT_IFNS:	mov eax,@CStr( "js " ): .endc
	  .case T_DOT_IFNE
	  .case T_DOT_IFNZ:	mov eax,@CStr( "jz " ): .endc
	  .case T_DOT_IFO:	mov eax,@CStr( "jno" ): .endc
	  .case T_DOT_IFNO:	mov eax,@CStr( "jo " ): .endc
	  .case T_DOT_IFP
	  .case T_DOT_IFPE:	mov eax,@CStr( "jnp" ): .endc
	  .case T_DOT_IFNP
	  .case T_DOT_IFPO:	mov eax,@CStr( "jp " ): .endc
	.endsw
	ret
GetJumpString endp

	OPTION	PROC:	PUBLIC
	ASSUME	ebx:	PTR asm_tok
	ASSUME	esi:	PTR hll_item

; .IF, .WHILE, .SWITCH or .REPEAT directive

HllStartDir PROC USES esi edi ebx,
	i:		SINT,
	tokenarray:	PTR asm_tok

local	rc:		SINT,
	cmd:		UINT,
	buff[16]:	SBYTE,
	buffer[MAX_LINE_LEN]:SBYTE,
	cmdstr[MAX_LINE_LEN]:SBYTE

	mov	rc,NOT_ERROR
	mov	ebx,tokenarray
	lea	edi,buffer

	mov	eax,i
	shl	eax,4
	;
	; added v2.22 to seperate:
	;
	; .IFS from .IFS <expression>
	; .IFB from .IFB <expression>
	;
	movzx	ecx,[ebx+eax+16].token
	push	ecx
	mov	eax,[ebx+eax].tokval
	mov	cmd,eax
	;
	; skip directive
	;
	inc	i
	;
	; v2.06: is there an item on the free stack?
	;
	mov	esi,ModuleInfo.HllFree

	.if	!esi

		LclAlloc( sizeof( hll_item ) )
		mov	esi,eax
	.endif

	ExpandCStrings( tokenarray )

	; structure for .IF .ELSE .ENDIF
	;   cond jump to LTEST-label
	;   ...
	;   jmp LEXIT
	; LTEST:
	;   ...
	; LEXIT:

	; structure for .IF .ELSEIF
	;   cond jump to LTEST
	;   ...
	;   jmp LEXIT
	; LTEST:
	;   cond jump to (new) LTEST
	;   ...
	;   jmp LEXIT
	; LTEST:
	;   ...

	; structure for .WHILE, .SWITCH and .REPEAT:
	;  jmp LTEST (for .WHILE and .SWITCH only)
	; LSTART:
	; ...
	; LTEST: (jumped to by .continue)
	;	 a) test end condition, cond jump to LSTART label
	;	 b) unconditional jump to LSTART label
	; LEXIT: (jumped to by .BREAK)

	xor	eax,eax
	mov	[esi].labels[LEXIT*4],eax
	mov	[esi].flags,eax
	mov	eax,cmd
	pop	ecx

	.switch eax

	  .case T_DOT_IFS
		.if	ecx != T_FINAL

			or	[esi].flags,HLLF_IFS
			jmp	case_IF
		.endif
		jmp	case_IFx
	  .case T_DOT_IFB
		.if	ecx != T_FINAL

			or	[esi].flags,HLLF_IFB
			jmp	case_IF
		.endif
	  .case T_DOT_IFA
	  .case T_DOT_IFAE
	  .case T_DOT_IFBE .. T_DOT_IFPO
	  .case T_DOT_IFZ

	     case_IFx:
		mov	[esi].cmd,HLL_IF
		mov	[esi].labels[LSTART*4],0
		mov	[esi].labels[LTEST*4],GetHllLabel()

		GetLabelStr( [esi].labels[LTEST*4], addr buff )
		.if	GetJumpString( cmd )

			strcat( strcpy( addr buffer, eax ), " " )
			lea	ecx,buff
			AddLineQueue( strcat( eax, ecx ) )
		.endif
		.endc

	  .case T_DOT_IFSD
		or	[esi].flags,HLLF_IFS
	  .case T_DOT_IFD
		or	[esi].flags,HLLF_IFD
		jmp	case_IF
	  .case T_DOT_IFSW
		or	[esi].flags,HLLF_IFS
	  .case T_DOT_IFW
		or	[esi].flags,HLLF_IFW
		jmp	case_IF
	  .case T_DOT_IFSB
		or	[esi].flags,HLLF_IFB OR HLLF_IFS
	  .case T_DOT_IF

	     case_IF:

		mov	[esi].cmd,HLL_IF
		mov	[esi].labels[LSTART*4],0 ; not used by .IF
		mov	[esi].labels[LTEST*4],GetHllLabel()
		;
		; get the C-style expression, convert to ASM code lines
		;
		EvaluateHllExpression( esi, addr i, ebx, LTEST, 0, edi )
		mov	rc,eax
		.if	eax == NOT_ERROR

			QueueTestLines( edi )
			;
			; if no lines have been created, the LTEST label isn't needed
			;
			.if	BYTE PTR [edi] == NULLC
				mov	[esi].labels[LTEST*4],0
			.endif
		.endif
		.endc

	  .case T_DOT_ASSERTD
		mov	[esi].flags,HLLF_IFD
		jmp	_DOT_ASSERT
	  .case T_DOT_ASSERTW
		mov	[esi].flags,HLLF_IFW
		jmp	_DOT_ASSERT
	  .case T_DOT_ASSERTB
		mov	[esi].flags,HLLF_IFB
	  .case T_DOT_ASSERT
		_DOT_ASSERT:

		mov	edx,i
		shl	edx,4
		mov	al,[ebx+edx].asm_tok.token
		.if	al == T_COLON

			add	i,2
			mov	edi,[ebx+edx+16].asm_tok.string_ptr
			mov	al,[ebx+edx+16].asm_tok.token

			.if	al == T_ID
				.if	SymFind( edi )

					free  ( ModuleInfo.assert_proc )
					salloc( edi )
					mov	ModuleInfo.assert_proc,eax
					jmp	unlink_hll
				.endif
			.endif

			.data
				assert_stack db 124 dup(0)
				assert_stid  dd 0

				externdef CurrIfState:DWORD
			.code

			conditional_assembly_prepare proto :dword

			.if	!_stricmp( edi, "CODE" )

				.if	!( ModuleInfo.asmc_syntax & ASMCFLAG_ASSERT )

					conditional_assembly_prepare( T_IF )
					mov	CurrIfState,BLOCK_DONE
				.endif
				jmp	unlink_hll
			.endif

			.if	!_stricmp( edi, "ENDS" )
				;
				; Converted to ENDIF in Tokenize()
				;
				jmp	unlink_hll
			.endif

			.if	!_stricmp( edi, "PUSH" )

				mov	al,ModuleInfo.asmc_syntax
				mov	ecx,assert_stid
				.if	ecx < 124
					mov	assert_stack[ecx],al
					inc	assert_stid
				.endif
				jmp	unlink_hll
			.endif

			.if	!_stricmp( edi, "POP" )

				mov	ecx,assert_stid
				mov	al,assert_stack[ecx]
				mov	ModuleInfo.asmc_syntax,al
				.if	ecx
					dec	assert_stid
				.endif
				jmp	unlink_hll
			.endif

			.if	!_stricmp( edi, "ON" )

				or	ModuleInfo.asmc_syntax,ASMCFLAG_ASSERT
				jmp	unlink_hll
			.endif

			.if	!_stricmp( edi, "OFF" )

				and	ModuleInfo.asmc_syntax,NOT ASMCFLAG_ASSERT
				jmp	unlink_hll
			.endif

			.if	!_stricmp( edi, "PUSHF" )

				or	ModuleInfo.asmc_syntax,ASMCFLAG_PUSHF
				jmp	unlink_hll
			.endif

			.if	!_stricmp( edi, "POPF" )

				and	ModuleInfo.asmc_syntax,NOT ASMCFLAG_PUSHF
				jmp	unlink_hll
			.endif

			asmerr( 2008, edi )
			jmp	unlink_hll

		.elseif al == T_FINAL || !(ModuleInfo.asmc_syntax & ASMCFLAG_ASSERT)

			;.if	!Options.quiet
			;.endif
			jmp	unlink_hll
		.endif

		mov	edx,i
		shl	edx,4
		strcpy( addr cmdstr, [ebx+edx].tokpos )

		.if	ModuleInfo.asmc_syntax & ASMCFLAG_PUSHF
			.if	ModuleInfo.Ofssize == USE64
				AddLineQueue( "pushfq" )
				AddLineQueue( "sub rsp,28h" )
			.else
				AddLineQueue( "pushfd" )
			.endif
		.endif

		mov	[esi].cmd,HLL_IF
		mov	[esi].labels[LSTART*4],0
		mov	[esi].labels[LTEST*4],GetHllLabel()

		GetLabelStr( GetHllLabel(), addr buff )
		;
		; get the C-style expression, convert to ASM code lines
		;
		mov	rc,EvaluateHllExpression( esi, addr i, ebx, LTEST, 0, edi )
		.if	eax != NOT_ERROR
			jmp	unlink_hll
		.endif

		QueueTestLines( edi )

		.if	ModuleInfo.asmc_syntax & ASMCFLAG_PUSHF
			.if	ModuleInfo.Ofssize == USE64
				AddLineQueue( "add rsp,28h" )
				AddLineQueue( "popfq" )
			.else
				AddLineQueue( "popfd" )
			.endif
		.endif
		AddLineQueueX( "jmp %s", addr buff )
		AddLineQueueX( "%s%s", GetLabelStr( [esi].labels[LTEST*4], edi ), addr LABELQUAL )
		.if	ModuleInfo.asmc_syntax & ASMCFLAG_PUSHF
			.if	ModuleInfo.Ofssize == USE64
				AddLineQueue( "add rsp,28h" )
				AddLineQueue( "popfq" )
			.else
				AddLineQueue( "popfd" )
			.endif
		.endif
		;
		; if no lines have been created, the LTEST label isn't needed
		;
		.if	BYTE PTR [edi] == NULLC
			jmp	unlink_hll
		.endif

		mov	eax,ModuleInfo.assert_proc
		.if	!eax

			mov	eax,@CStr( "assert_exit" )
			mov	ModuleInfo.assert_proc,eax
		.endif

		AddLineQueueX( "%s()", eax )
		AddLineQueue ( "db @CatStr(!\",\%\@FileName,<(>,\%@Line,<): >,!\")" )

		lea	ebx,cmdstr
		.while	strchr( ebx, '"' )

			mov	byte ptr [eax],0
			xchg	ebx,eax
			inc	ebx
			.if	byte ptr [eax]
				AddLineQueueX( "db \"%s\",22h", eax )
			.else
				AddLineQueue( "db 22h" )
			.endif
		.endw
		.if	byte ptr [ebx]

			AddLineQueueX( "db \"%s\"", ebx )
		.endif
		AddLineQueue( "db 0" )
		;
		; all done - create the exit label
		;
		AddLineQueueX( "%s%s", addr buff, addr LABELQUAL )
		jmp	unlink_hll

	  .case T_DOT_SWITCH
		mov	[esi].cmd,HLL_SWITCH
		mov	[esi].flags,HLLF_WHILE
		.if	ModuleInfo.hll_switch & SWITCH_NOTEST
			or	[esi].flags,HLLF_NOTEST
			and	ModuleInfo.hll_switch,NOT SWITCH_NOTEST
		.endif
		xor	eax,eax
		mov	[esi].labels[LSTART*4], eax	; set by .CASE
		mov	[esi].labels[LTEST*4],	eax	; set by .CASE
		mov	[esi].labels[LEXIT*4],	eax	; set by .BREAK
		mov	[esi].condlines,	eax
		mov	[esi].caselist,		eax

		mov	eax,i
		shl	eax,4
		.if	[ebx+eax].asm_tok.token != T_FINAL
			ExpandHllProc( edi, i, ebx )
			cmp	eax,ERROR
			je	toend

			.if	BYTE PTR [edi]
				QueueTestLines( edi )
				or	[esi].flags,HLLF_ARGREG
				jmp	set_arg_size
			.else
				mov	ecx,i
				shl	ecx,4
				mov	eax,[ebx+ecx].asm_tok.tokval
				.switch eax
				  .case T_AX .. T_DI
					or	[esi].flags,HLLF_ARG16
					.if	ModuleInfo.Ofssize == USE16
						or	[esi].flags,HLLF_ARGREG
					.endif
				  .case T_AL .. T_BH
					.endc
				  .case T_EAX
					.if	ModuleInfo.Ofssize == USE64
						or	[esi].flags,HLLF_ARG3264
					.endif
				  .case T_ECX .. T_EDI
					or	[esi].flags,HLLF_ARG32
					.if	ModuleInfo.Ofssize == USE32
						or	[esi].flags,HLLF_ARGREG
					.endif
					.endc
				  .case T_RAX .. T_R15
					or	[esi].flags,HLLF_ARG64
					.if	ModuleInfo.Ofssize == USE64
						or	[esi].flags,HLLF_ARGREG
					.endif
					.endc
				  .default
					or	[esi].flags,HLLF_ARGMEM
					mov	eax,[ebx+ecx].asm_tok.string_ptr
					.if	SymFind( eax )
						mov	eax,[eax].asym.total_size
						.if	eax == 2
							or	[esi].flags,HLLF_ARG16
						.elseif eax == 4
							or	[esi].flags,HLLF_ARG32
						.elseif eax == 8
							or	[esi].flags,HLLF_ARG64
						.endif
					.else
					set_arg_size:
						.if	ModuleInfo.Ofssize == USE16
							or	[esi].flags,HLLF_ARG16
						.elseif ModuleInfo.Ofssize == USE32
							or	[esi].flags,HLLF_ARG32
						.else
							or	[esi].flags,HLLF_ARG64
						.endif
					.endif
				.endsw
			.endif

			strlen( strcpy( edi, [ebx+16].asm_tok.tokpos ) )
			inc	eax
			push	eax
			LclAlloc( eax )
			pop	ecx
			mov	[esi].condlines,eax
			memcpy( eax, edi, ecx )
		.endif
		.endc

	  .case T_DOT_WHILE
		or	[esi].flags,HLLF_WHILE
	  .case T_DOT_REPEAT
		;
		; create the label to start of loop
		;
		mov	[esi].labels[LSTART*4],GetHllLabel()
		mov	[esi].labels[LTEST*4],0 ; v2.11: test label is created only if needed

		.if	cmd == T_DOT_WHILE

			mov	[esi].cmd,HLL_WHILE
			mov	[esi].condlines,0
			mov	eax,i
			shl	eax,4
			.if	[ebx+eax].asm_tok.token != T_FINAL
				EvaluateHllExpression( esi, addr i, ebx, LSTART, 1, edi )
				mov	rc,eax
				.if	eax == NOT_ERROR
					strlen( edi )
					inc	eax
					push	eax
					LclAlloc( eax )
					pop	ecx
					mov	[esi].condlines,eax
					memcpy( eax, edi, ecx )
				.endif
			.else
				mov	BYTE PTR [edi],NULLC ; just ".while" without expression is accepted
			.endif

			; create a jump to test label
			; optimisation: if line at 'test' label is just a jump,
			; dont create label and don't jump!
			;
			.if	_memicmp( edi, "jmp", 3 )
				mov	[esi].labels[LTEST],GetHllLabel()
				AddLineQueueX( "jmp %s", GetLabelStr( [esi].labels[LTEST*4], addr buff ) )
			.endif
		.else
			mov	[esi].cmd,HLL_REPEAT
		.endif

		mov	cl,ModuleInfo.loopalign
		.if	cl
			mov	eax,1
			shl	eax,cl
			AddLineQueueX( "ALIGN %d", eax )
		.endif
		AddLineQueueX( "%s%s", GetLabelStr( [esi].labels[LSTART*4], addr buff ), addr LABELQUAL )
		.endc
	.endsw

	mov	eax,i
	shl	eax,4

	.if	![esi].flags && ([ebx+eax].asm_tok.token != T_FINAL && rc == NOT_ERROR)

		asmerr( 2008, [ebx+eax].asm_tok.tokpos )
		mov	rc,eax
	.endif
	;
	; v2.06: remove the item from the free stack
	;
	.if	esi == ModuleInfo.HllFree

		mov	eax,[esi].next
		mov	ModuleInfo.HllFree,eax
	.endif
	mov	eax,ModuleInfo.HllStack
	mov	[esi].next,eax
	mov	ModuleInfo.HllStack,esi

unlink_hll:

	.if	ModuleInfo.list

		LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
	.endif

	.if	ModuleInfo.line_queue.head	; might be NULL! (".if 1")

		RunLineQueue()
	.endif

	mov	eax,rc

toend:
	ret
HllStartDir ENDP

;
; .ENDIF, .ENDW, .UNTIL and .UNTILCXZ directives.
; These directives end a .IF, .WHILE or .REPEAT block.
;
HllEndDir PROC USES esi edi ebx i:SINT, tokenarray:PTR asm_tok

local	rc:		SINT,
	buffer		[MAX_LINE_LEN]:SBYTE,
	l_exit[16]:	SBYTE	; exit or default label

	mov	esi,ModuleInfo.HllStack
	.if	!esi
		asmerr( 1011 )
		jmp	toend
	.endif

	mov	eax,[esi].next
	mov	ecx,ModuleInfo.HllFree
	mov	ModuleInfo.HllStack,eax
	mov	[esi].next,ecx
	mov	ModuleInfo.HllFree,esi
	mov	rc,NOT_ERROR
	lea	edi,buffer
	mov	ebx,tokenarray
	mov	ecx,[esi].cmd
	mov	edx,i
	shl	edx,4
	mov	eax,[ebx+edx].tokval

	.switch eax

	  .case T_DOT_ENDIF
		.if	ecx != HLL_IF
			asmerr( 1011 )
			jmp	toend
		.endif
		inc	i
		;
		; if a test label isn't created yet, create it
		;
		mov	eax,[esi].labels[LTEST*4]
		.if	eax
			AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), addr LABELQUAL )
		.endif
		.endc

	  .case T_DOT_ENDSW
		.if	ecx != HLL_SWITCH
			asmerr( 1011 )
			jmp	toend
		.endif
		inc	i
		.endc .if [esi].labels[LTEST*4] == 0
		.if	[esi].labels[LSTART*4] == 0
			mov	[esi].labels[LSTART*4],GetHllLabel()
		.endif
		.if	[esi].labels[LEXIT*4] == 0
			mov	[esi].labels[LEXIT*4],GetHllLabel()
		.endif
		GetLabelStr( [esi].labels[LEXIT*4], edi )
		RenderCaseExit( esi, edi )
		strcpy( addr l_exit, edi )
		GetLabelStr( [esi].labels[LSTART*4], edi )

		ASSUME	ebx:PTR hll_item
		mov	ebx,[esi].caselist

		mov	cl,ModuleInfo.casealign
		.if	cl
			mov	eax,1
			shl	eax,cl
			AddLineQueueX( "ALIGN %d", eax )
		.endif

		.if	![esi].condlines

			AddLineQueueX( "%s%s", edi, addr LABELQUAL )

			.while	ebx
				.if	![ebx].condlines
					AddLineQueueX( "jmp %s", GetLabelStr( [ebx].labels[LSTART*4], edi ) )
				.else
					.if [ebx].flags & HLLF_EXPRESSION
						mov	i,1
						or	[ebx].flags,HLLF_WHILE
						ExpandHllExpression( ebx, addr i, tokenarray, LSTART, 1, edi )
					.else
						QueueTestLines( [ebx].condlines )
					.endif
				.endif
				mov	ebx,[ebx].caselist
			.endw
		.else
			RenderSwitch( esi, tokenarray, edi, addr l_exit )
		.endif

		ASSUME	ebx:PTR asm_tok
		mov	eax,ModuleInfo.token_count
		mov	i,eax
		.endc

	  .case T_DOT_ENDW
		.if	ecx != HLL_WHILE
			asmerr( 1011 )
			jmp	toend
		.endif
		;
		; create test label
		;
		mov	eax,[esi].labels[LTEST*4]
		.if	eax

			AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), addr LABELQUAL )
		.endif
		inc	i
		.if	[esi].flags & HLLF_EXPRESSION
			ExpandHllExpression( esi, addr i, tokenarray, LSTART, 1, edi )
		.else
			QueueTestLines( [esi].condlines )
		.endif
		.endc

	  .case T_DOT_UNTILCXZ
		.if	ecx != HLL_REPEAT
			asmerr( 1010, [ebx+edx].string_ptr )
			jmp	toend
		.endif

		inc	i
		lea	ebx,[ebx+edx+16]

		mov	eax,[esi].labels[LTEST*4]
		.if	eax ; v2.11: LTEST only needed if .CONTINUE has occured
			AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), addr LABELQUAL )
		.endif
		;
		; read in optional (simple) expression
		;
		.if	[ebx].token != T_FINAL
			EvaluateHllExpression( esi, addr i, tokenarray, LSTART, 0, edi )
			mov	rc,eax
			.if	eax == NOT_ERROR
				CheckCXZLines( edi )
				mov	rc,eax
				.if	eax == NOT_ERROR
					QueueTestLines( edi )	; write condition lines
				.else
					asmerr( 2062 )
				.endif
			.endif
		.else
			.if	Options.masm_compat_gencode
				AddLineQueueX( "loop %s", GetLabelStr( [esi].labels[LSTART*4], edi ) )
			.else
				.if	ModuleInfo.Ofssize == USE32
					strcpy( edi, "ecx" )
				.elseif ModuleInfo.Ofssize == USE16
					strcpy( edi, "cx" )
				.else
					strcpy( edi, "rcx" )
				.endif
				AddLineQueueX( " dec %s", edi )
				AddLineQueueX( " jnz %s", GetLabelStr( [esi].labels[LSTART*4], edi ) )
			.endif
		.endif
		.endc

	  .case T_DOT_UNTIL
		.if	ecx != HLL_REPEAT
			asmerr( 1010, [ebx+edx].string_ptr )
			jmp	toend
		.endif

		inc	i
		lea	ebx,[ebx+edx+16]
		mov	eax,[esi].labels[LTEST*4]
		.if	eax	; v2.11: LTEST only needed if .CONTINUE has occured
			AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), addr LABELQUAL )
		.endif
		;
		; read in (optional) expression
		; if expression is missing, just generate nothing
		;
		.if	[ebx].token != T_FINAL
			EvaluateHllExpression( esi, addr i, tokenarray, LSTART, 0, edi )
			mov	rc,eax
			.if	eax == NOT_ERROR
				QueueTestLines( edi )	; write condition lines
			.endif
		.endif
		.endc
	.endsw

	;
	; create the exit label if it has been referenced
	;
	mov	eax,[esi].labels[LEXIT*4]
	.if	eax
		AddLineQueueX( "%s%s", GetLabelStr( eax, edi ), addr LABELQUAL )
	.endif

	mov	ebx,i
	shl	ebx,4
	add	ebx,tokenarray
	.if	[ebx].token != T_FINAL && rc == NOT_ERROR
		asmerr(2008, [ebx].tokpos )
		mov	rc,ERROR
	.endif

	.if	ModuleInfo.list
		LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
	.endif
	;
	; v2.11: always run line-queue if it's not empty.
	;
	.if	ModuleInfo.line_queue.head
		RunLineQueue()
	.endif
	mov	eax,rc
toend:
	ret
HllEndDir ENDP

;
; .ELSE, .ELSEIF, .CONTINUE and .BREAK directives.
; .ELSE, .ELSEIF:
;    - create a jump to exit label
;    - render test label if it was referenced
;    - for .ELSEIF, create new test label and evaluate expression
; .CONTINUE, .BREAK:
;    - jump to test / exit label of innermost .WHILE/.REPEAT block
;
HllExitDir PROC USES esi edi ebx i, tokenarray:PTR asm_tok

local	rc:	SINT,
	cmd:	SINT,
	buff	[16]:SBYTE,
	buffer	[MAX_LINE_LEN]:SBYTE

	mov	esi,ModuleInfo.HllStack
	.if	!esi
		asmerr( 1011 )
		jmp	toend
	.endif

	ExpandCStrings( tokenarray )

	lea	edi,buffer
	mov	rc,NOT_ERROR
	mov	ebx,i
	shl	ebx,4
	add	ebx,tokenarray
	mov	eax,[ebx].tokval
	mov	cmd,eax

	.switch eax

	  .case T_DOT_DEFAULT
		.if	[esi].flags & HLLF_ELSEOCCUR
			asmerr( 2142 )
			jmp	toend
		.endif
		.if	[ebx+16].token != T_FINAL
			asmerr( 2008, [ebx].tokpos )
			jmp	toend
		.endif
		or	[esi].flags,HLLF_ELSEOCCUR

	  .case T_DOT_CASE

		.while	esi && [esi].cmd != HLL_SWITCH

			mov	esi,[esi].next
		.endw
		.if	[esi].cmd != HLL_SWITCH

			asmerr( 1010, [ebx].string_ptr )
			jmp	toend
		.endif

		.if	[esi].labels[LSTART*4] == 0

			mov	[esi].labels[LSTART*4],GetHllLabel()
			AddLineQueueX( "jmp %s", GetLabelStr( [esi].labels[LSTART*4], edi ) )
		.else
			.if ModuleInfo.hll_switch & SWITCH_PASCAL
				.if	[esi].labels[LEXIT*4] == 0
					mov	[esi].labels[LEXIT*4],GetHllLabel()
				.endif
				RenderCaseExit( esi, edi )
			.elseif Parse_Pass == PASS_1
				mov	eax,esi
				.while	[eax].hll_item.caselist
					mov	eax,[eax].hll_item.caselist
				.endw
				.if	eax != esi && !( [eax].hll_item.flags & HLLF_ENDCOCCUR )
					asmerr( 7007 )
				.endif
			.endif
		.endif

		;
		; .case a, b, c, ...
		;
		.endc .if RenderMultiCase( addr i, edi, ebx )

		mov	cl,ModuleInfo.casealign
		.if	cl
			mov	eax,1
			shl	eax,cl
			AddLineQueueX( "ALIGN %d", eax )
		.endif
		inc	[esi].labels[LTEST*4]
		mov	ecx,GetHllLabel()
		push	ecx
		AddLineQueueX( "%s%s", GetLabelStr( ecx, edi ), addr LABELQUAL )
		LclAlloc( sizeof( hll_item ) )
		pop	ecx
		mov	edx,esi
		mov	esi,eax
		mov	eax,[edx].hll_item.condlines
		mov	[esi].labels[LSTART*4],ecx
		.while	[edx].hll_item.caselist
			mov	edx,[edx].hll_item.caselist
		.endw
		mov	[edx].hll_item.caselist,esi

		inc	i	; skip past the .case token
		add	ebx,16

		push	eax	; handle .case <expression> : ...
		push	ebx
		push	esi
		;add	ebx,16	; skip past <expression>
		xor	esi,esi
		.while	IsCaseColon( ebx )
			mov	ebx,eax
			.if	esi
				mov	eax,[ebx].tokpos
				mov	BYTE PTR [eax],0
				AddLineQueue( esi )
				mov	eax,[ebx].tokpos
				mov	BYTE PTR [eax],':'
			.else
				sub	eax,tokenarray
				shr	eax,4
				mov	ModuleInfo.token_count,eax
			.endif
			add	ebx,16
			mov	esi,[ebx].tokpos
		.endw
		.if	esi
			AddLineQueue( esi )
		.endif
		pop	esi
		pop	ebx
		pop	eax

		.if	eax && cmd != T_DOT_DEFAULT
			push	eax
			push	ebx
			push	edi
			xor	edi,edi

			.while	1
				movzx	eax,[ebx].token
				;
				; .CASE BYTE PTR [reg+-*imm]
				; .CASE ('A'+'L') SHR (8 - H_BITS / ... )
				;
				.switch eax

				  .case T_CL_BRACKET
					.if	edi == 1
						.if	[ebx+16].token == T_FINAL
							or	[esi].flags,HLLF_NUM
							.break
						.endif
					.endif
					sub	edi,2
				  .case T_OP_BRACKET
					inc	edi
				  .case T_PERCENT	; %
				  .case T_INSTRUCTION	; XOR, OR, NOT,...
				  .case '+'
				  .case '-'
				  .case '*'
				  .case '/'
					.endc

				  .case T_STYPE ; BYTE, WORD, ...
					.break .if [ebx+16].tokval == T_PTR
					jmp	STRING

				  .case T_FLOAT ; 1..3 ?
					.break	.if [ebx+16].token == T_DOT
					jmp	STRING
				  .case T_UNARY_OPERATOR	; offset x
					.break	.if [ebx].tokval != T_OFFSET
					jmp	STRING
				  .case T_ID
					.if	SymFind( [ebx].string_ptr )
						.break	.if [eax].asym.state != SYM_INTERNAL
						.break	.if !([eax].asym.mem_type == MT_NEAR || \
							      [eax].asym.mem_type == MT_EMPTY)
					.elseif Parse_Pass != PASS_1
						.break
					.endif
				  .case T_STRING
				  .case T_NUM
					STRING:
					.if	[ebx+16].token == T_FINAL
						or [esi].flags,HLLF_NUM
						.break
					.endif
					.endc
				  .default
				  ; T_REG
				  ; T_OP_SQ_BRACKET
				  ; T_DIRECTIVE
				  ; T_QUESTION_MARK
				  ; T_BAD_NUM
				  ; T_DBL_COLON
				  ; T_CL_SQ_BRACKET
				  ; T_COMMA
				  ; T_COLON
				  ; T_FINAL
					.break
				.endsw
				add	ebx,16
			.endw
			pop	edi
			pop	ebx
			pop	eax
		.endif

		.if	cmd == T_DOT_DEFAULT
			or	[esi].flags,HLLF_DEFAULT
		.else
			.if	[ebx].token == T_FINAL
				asmerr( 2008, [ebx-16].tokpos )
				jmp	toend
			.endif
			.if	!eax
				mov	ebx,i
				EvaluateHllExpression( esi, addr i, tokenarray, LSTART, 1, edi )
				mov	i,ebx
				mov	rc,eax
				.endc .if eax == ERROR
			.else
				mov	eax,ModuleInfo.token_count
				shl	eax,4
				add	eax,tokenarray
				mov	eax,[eax].asm_tok.tokpos
				sub	eax,[ebx].tokpos
				mov	WORD PTR [edi+eax],0
				memcpy( edi, [ebx].tokpos, eax )
			.endif
			strlen( edi )
			inc	eax
			push	eax
			LclAlloc( eax )
			pop	ecx
			mov	[esi].condlines,eax
			memcpy( eax, edi, ecx )
		.endif
		mov	eax,ModuleInfo.token_count
		mov	i,eax
		.endc

	  .case T_DOT_ELSEIF
		or	[esi].flags,HLLF_ELSEIF
	  .case T_DOT_ELSE
		.if	[esi].cmd != HLL_IF
			asmerr( 1010, [ebx].string_ptr )
			jmp	toend
		.endif
		;
		; v2.08: check for multiple ELSE clauses
		;
		.if	[esi].flags & HLLF_ELSEOCCUR
			asmerr( 2142 )
			jmp	toend
		.endif
		push	eax
		;
		; the exit label is only needed if an .ELSE branch exists.
		; That's why it is created delayed.
		;
		.if	[esi].labels[LEXIT*4] == 0
			mov	[esi].labels[LEXIT*4],GetHllLabel()
		.endif
		AddLineQueueX( "jmp %s", GetLabelStr( [esi].labels[LEXIT*4], edi ) )

		.if	[esi].labels[LTEST*4] > 0
			AddLineQueueX( "%s%s", GetLabelStr( [esi].labels[LTEST*4], edi ), addr LABELQUAL )
			mov	[esi].labels[LTEST*4],0
		.endif
		inc	i
		pop	eax
		.if	eax == T_DOT_ELSEIF
			;
			; create new labels[LTEST] label
			;
			mov	[esi].labels[LTEST*4],GetHllLabel()
			EvaluateHllExpression( esi, addr i, tokenarray, LTEST, 0, edi )
			mov	rc,eax
			.if	eax == NOT_ERROR
				.if	[esi].flags & HLLF_EXPRESSION
					ExpandHllExpression( esi, addr i, tokenarray, LTEST, 0, edi )
					mov	eax,ModuleInfo.token_count
					mov	i,eax
				.else
					QueueTestLines( edi )
				.endif
			.endif
		.else
			or	[esi].flags,HLLF_ELSEOCCUR
		.endif
		.endc

	  .case T_DOT_BREAK
	  .case T_DOT_CONTINUE

		mov	edx,esi
		.while	esi && ( [esi].cmd == HLL_IF || [esi].cmd == HLL_SWITCH )

			mov	esi,[esi].next
		.endw

	  .case T_DOT_ENDC

		.if	eax == T_DOT_ENDC

			mov	edx,esi
			.while	esi && [esi].cmd == HLL_IF

				mov	esi,[esi].next
			.endw
		.endif

		.if	!esi || ( eax == T_DOT_ENDC && [esi].cmd != HLL_SWITCH )

			asmerr( 1011 )
			jmp	toend
		.endif
		;
		; v2.11: create 'exit' and 'test' labels delayed.
		;
		.if	eax == T_DOT_BREAK || eax == T_DOT_ENDC

			.if	[esi].labels[LEXIT*4] == 0

				mov	[esi].labels[LEXIT*4],GetHllLabel()
			.endif
			mov	ecx,LEXIT
		.else
			;
			; 'test' is not created for .WHILE loops here; because
			; if it doesn't exist, there's no condition to test.
			;
			.if	[esi].cmd == HLL_REPEAT && [esi].labels[LTEST*4] == 0

				mov	[esi].labels[LTEST*4],GetHllLabel()
			.endif
			mov	ecx,LSTART
			.if	[esi].labels[LTEST*4]

				mov	ecx,LTEST
			.endif
		.endif
		;
		; .BREAK .IF ... or .CONTINUE .IF ?
		;
		inc	i
		add	ebx,16
		.if	[ebx].token != T_FINAL

			.if	[ebx].token == T_DIRECTIVE

				xor	edx,edx
				mov	eax,[ebx].tokval
				.switch eax
				  .case T_DOT_IFS
					.if	[ebx+16].token != T_FINAL

						or	edx,HLLF_IFS
					.endif
				  .case T_DOT_IFB
					cmp	[ebx+16].token,T_FINAL
					jne	case_IF
				  .case T_DOT_IFA
				  .case T_DOT_IFAE
				  .case T_DOT_IFBE .. T_DOT_IFPO
				  .case T_DOT_IFZ

					inc	i
					GetLabelStr( [esi].labels[ecx*4], addr buff )
					strcpy( edi, GetJumpString( [ebx].tokval ) )
					strcat( edi, " " )
					strcat( edi, addr buff )
					InvertJump( edi )
					AddLineQueue( edi )
					.endc

				  .case T_DOT_IFSB
				  .case T_DOT_IFSW
				  .case T_DOT_IFSD
					or	edx,HLLF_IFS
				  .case T_DOT_IF
				  .case T_DOT_IFW
				  .case T_DOT_IFD

				     case_IF:
					push	[esi].cmd
					push	[esi].condlines
					push	[esi].flags
					mov	[esi].flags,edx
					mov	[esi].cmd,HLL_BREAK
					inc	i
					;
					; v2.11: set rc and don't exit if an error occurs; see hll3.aso
					;
					EvaluateHllExpression( esi, addr i, tokenarray, ecx, 1, edi )
					mov	rc,eax
					.if	eax == NOT_ERROR

						QueueTestLines( edi )
					.endif
					pop	[esi].flags
					pop	[esi].condlines
					pop	[esi].cmd
				.endsw
			.endif
		.else
			push	edx
			AddLineQueueX( "jmp %s", GetLabelStr( [esi].hll_item.labels[ecx*4], edi ) )
			pop	edx
			.if	[edx].hll_item.cmd == HLL_SWITCH
				;
				; unconditional jump from .case
				; - set flag to skip exit-jumps
				;
				mov	esi,edx
				mov	eax,esi
				.while	[esi].caselist
					mov	esi,[esi].caselist
				.endw
				.if	eax != esi
					or	[esi].flags,HLLF_ENDCOCCUR
				.endif
			.endif
		.endif
		.endc
	.endsw
	mov	ebx,i
	shl	ebx,4
	add	ebx,tokenarray
	.if	[ebx].token != T_FINAL && rc == NOT_ERROR
		asmerr(2008, [ebx].tokpos )
		mov	rc,ERROR
	.endif

	.if	ModuleInfo.list
		LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
	.endif
	;
	; v2.11: always run line-queue if it's not empty.
	;
	.if	ModuleInfo.line_queue.head
		RunLineQueue()
	.endif

	mov	eax,rc
toend:
	ret
HllExitDir ENDP

; check if an hll block has been left open. called after pass 1

HllCheckOpen PROC
	.if	ModuleInfo.HllStack
		asmerr( 1010, ".if-.repeat-.while" )
	.endif
	ret
HllCheckOpen ENDP

; HllInit() is called for each pass

HllInit PROC pass
	mov	ModuleInfo.hll_label,0	; init hll label counter
	ret
HllInit ENDP

	END
