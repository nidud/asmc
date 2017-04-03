include string.inc

include asmc.inc
include token.inc

; v2.11: EXPR_UNDEF changed to EXPR_ERROR, value -1

; argument types accepted by unary operators

AT_TYPE		equ 01h		; type
AT_LABEL	equ 02h		; label (direct memory)
AT_IND		equ 04h		; indirect memory
AT_REG		equ 08h		; register
AT_FIELD	equ 10h		; struct field
AT_NUM		equ 20h		; number
AT_BF		equ 40h		; bitfield and record types
AT_UNDEF	equ 80h		; undefined label
AT_FLOAT	equ 100h	; float constant

; flags for last argument of EvalOperand()

EXPF_NOERRMSG	equ 1		; suppress error messages
EXPF_NOUNDEF	equ 2		; don't accept or create undefined symbols
EXPF_ONEOPND	equ 4		; private flag, used inside expreval.c only
EXPF_IN_SQBR	equ 8		; private flag, used inside expreval.c only

AT_CONST	equ AT_TYPE  or AT_NUM
AT_TL		equ AT_TYPE  or AT_LABEL
AT_TLN		equ AT_TYPE  or AT_LABEL or AT_NUM
AT_TLF		equ AT_TYPE  or AT_LABEL or AT_FIELD
AT_TLFN		equ AT_TYPE  or AT_LABEL or AT_FIELD or AT_NUM
AT_TBF		equ AT_TYPE  or AT_BF
AT_LF		equ AT_LABEL or AT_FIELD
AT_LIF		equ AT_LABEL or AT_IND	 or AT_FIELD
AT_LFN		equ AT_LABEL or AT_FIELD or AT_NUM
AT_TLR		equ AT_TYPE  or AT_LABEL or AT_REG
AT_ALL		equ AT_TYPE  or AT_LABEL or AT_IND or AT_REG or AT_FIELD or AT_NUM or AT_UNDEF or AT_BF or AT_FLOAT

	.code

init_expr PROC FASTCALL opnd
	xor eax,eax
	mov [ecx].expr.value,eax
	mov [ecx].expr.hvalue,eax
	mov DWORD PTR [ecx].expr.hlvalue[0],eax
	mov DWORD PTR [ecx].expr.hlvalue[4],eax
	mov [ecx].expr.quoted_string,eax
	mov [ecx].expr.base_reg,eax
	mov [ecx].expr.idx_reg,eax
	mov [ecx].expr.label_tok,eax
	mov [ecx].expr.override,eax
	mov [ecx].expr._instr,EMPTY		; -2
	mov [ecx].expr.kind,EXPR_EMPTY	; -2
	mov [ecx].expr.mem_type,MT_EMPTY	; 0C0h
	mov [ecx].expr.scale,al
	mov [ecx].expr.Ofssize,USE_EMPTY	; 0FEh
	mov [ecx].expr.flags,al
	mov [ecx].expr.sym,eax
	mov [ecx].expr.mbr,eax
	mov [ecx].expr._type,eax
	ret
init_expr ENDP

TokenAssign PROC FASTCALL opnd1, opnd2

	mov eax,DWORD PTR [edx].expr.llvalue[0]
	mov DWORD PTR [ecx].expr.llvalue[0],eax
	mov eax,DWORD PTR [edx].expr.llvalue[4]
	mov DWORD PTR [ecx].expr.llvalue[4],eax
	mov eax,DWORD PTR [edx].expr.hlvalue[0]
	mov DWORD PTR [ecx].expr.hlvalue[0],eax
	mov eax,DWORD PTR [edx].expr.hlvalue[4]
	mov DWORD PTR [ecx].expr.hlvalue[4],eax
	mov eax,[edx].expr.quoted_string		; probably useless
	mov [ecx].expr.quoted_string,eax

	mov eax,[edx].expr.base_reg
	mov [ecx].expr.base_reg,eax
	mov eax,[edx].expr.idx_reg
	mov [ecx].expr.idx_reg,eax
	mov eax,[edx].expr.label_tok
	mov [ecx].expr.label_tok,eax
	mov eax,[edx].expr.override
	mov [ecx].expr.override,eax
	mov eax,[edx].expr._instr
	mov [ecx].expr._instr,eax
	mov eax,[edx].expr.kind
	mov [ecx].expr.kind,eax
	mov eax,DWORD PTR [edx].expr.mem_type
	mov DWORD PTR [ecx].expr.mem_type,eax
	mov eax,[edx].expr.sym
	mov [ecx].expr.sym,eax
	mov eax,[edx].expr.mbr
	mov [ecx].expr.mbr,eax

	ret
TokenAssign ENDP

	ALIGN	16

is_expr_item PROC FASTCALL item
;
; Check if a token is a valid part of an expression.
; chars + - * / . : [] and () are operators.
; also done here:
; T_INSTRUCTION	 SHL, SHR, AND, OR, XOR changed to T_BINARY_OPERATOR
; T_INSTRUCTION	 NOT			changed to T_UNARY_OPERATOR
; T_DIRECTIVE	 PROC			changed to T_STYPE
; for the new operators the precedence is set.
; DUP, comma or other instructions or directives terminate the expression.
;

	movzx edx,[ecx].asm_tok.token
	mov eax,1

	.switch edx
	  .case T_INSTRUCTION
		mov edx,[ecx].asm_tok.tokval
		.switch edx
		  .case T_SHL
		  .case T_SHR
			mov [ecx].asm_tok.token,T_BINARY_OPERATOR
			mov [ecx].asm_tok.precedence,8
			ret
		  .case T_NOT
			mov [ecx].asm_tok.token,T_UNARY_OPERATOR
			mov [ecx].asm_tok.precedence,11
			ret
		  .case T_AND
			mov [ecx].asm_tok.token,T_BINARY_OPERATOR
			mov [ecx].asm_tok.precedence,12
			ret
		  .case T_OR
		  .case T_XOR
			mov [ecx].asm_tok.token,T_BINARY_OPERATOR
			mov [ecx].asm_tok.precedence,13
			ret
		.endsw
		xor eax,eax
		ret

	  .case T_RES_ID
		.if [ecx].asm_tok.tokval == T_DUP
			xor eax,eax
		.endif
		ret

	  .case T_DIRECTIVE
		.if [ecx].asm_tok.tokval == T_PROC
			mov [ecx].asm_tok.token,T_STYPE
			mov edx,ecx
			mov cl,ModuleInfo._model
			shl eax,cl
			and eax,0070h
			mov eax,T_FAR
			.if ZERO?
				mov eax,T_NEAR
			.endif
			mov [edx].asm_tok.tokval,eax
			mov eax,1
			ret
		.endif

	  .case T_COMMA
		xor eax,eax
		ret
	.endsw
	ret
is_expr_item ENDP

	END
