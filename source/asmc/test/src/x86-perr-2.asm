
;--- test -pe
;--- v2.15: assembly-time variables did accept certain "undefined" expressions.

	.386
	.model flat, stdcall

;IMAGE_FILE_DLL              EQU 2000h

@pe_file_flags = @pe_file_flags or IMAGE_FILE_DLL

	.code

LibMain proc hModule:dword, dwReason:dword, dwReserved:dword
	mov eax,1
	ret
LibMain endp

	END LibMain

;--- a simple line like
;--- @pe_file_flags = IMAGE_FILE_DLL 
;--- was always correctly rejected. The odd behavior above was due to
;--- function calculate() in expreval.c. function MakeConst()
;--- might change - in pass 1 - an expression containing an undefined symbol
;--- to a constant! CreateAssemblyTimeVariable() checked for undefined symbols
;--- in the expression, but this information might have got lost in the evaluator.
