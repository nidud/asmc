
;--- expression evaluator
;--- problem: MakeConst() called by Calculate() in expression evaluator
;---  may force type EXPR_CONST if expression contains undefined symbol.

	.386
	.model flat, stdcall	;-pe requires a .model flat directive

xxx = 1 or UNDEF_SYMBOL   ;was accepted until v2.14
;xxx = UNDEF_SYMBOL or 1  ;was always rejected

	.code
start:
	ret
	END start
