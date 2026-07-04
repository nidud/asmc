
;--- v2.21: fixed 2 errors:
;--- 1. GPF in jwasm assembling "mov xxxProc, offset x"
;---    location: parser.c, memory_operand(), calling SizeFromMemtype() with type=NULL!
;--- 2. error 'INVOKE requires prototype'
;---    location: invoke.c, InvokeDirective(), case "if ( sym->mem_type == MT_PROC )" added
;--- so the assumption that MT_PROC is "obsolete" ( see listing.c ) obviously wasn't correct...

	.286
	.MODEL small
	.dosseg
	.stack 2048
	option casemap:none

	.code

n1 proc near stdcall hFile:word, pBuffer:ptr, wSize:word
	ret
n1 endp
n2 proc near stdcall hFile:word, pBuffer:ptr, wSize:word
	ret
n2 endp
f1 proc far stdcall hFile:word, pBuffer:ptr, wSize:word
	ret
f1 endp
f2 proc far stdcall hFile:word, pBuffer:ptr, wSize:word
	ret
f2 endp

PNEAR typedef proto near stdcall :word, :ptr, :word
PFAR  typedef proto far  stdcall :word, :ptr, :word

main proc c

local nearProc[2]:PNEAR
local farProc[2]:PFAR

	mov nearProc+0, offset n1
	mov nearProc+2, offset n2
	mov word ptr farProc+0, offset f1
	mov word ptr farProc+2, cs
	mov word ptr farProc+4, offset f2
	mov word ptr farProc+6, cs
	invoke nearProc[0], 1, 0, 2
	invoke nearProc[2], 1, 0, 2
	invoke farProc[0], 1, 0, 2
	invoke farProc[4], 1, 0, 2
	ret

main endp

	END
