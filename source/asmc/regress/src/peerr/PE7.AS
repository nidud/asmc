
;--- should create error because 32-bit fixup used
;--- and base is >= 80000000h

	.x64
	.model flat
	option dotname

	option dotname

.hdr$2 segment flat public 'HDR'
	org 24+24	;locate 'ImageBase' in PE header
;	dq 400000h
	dq 80000000h
;	dq 100000000h
.hdr$2 ends

CStr macro text:vararg
local sym
	.const
sym db text,0
	.code
	exitm <addr sym>
endm

    .data
var1 db 0
var2 db 0
    .code

main proc

	push main
	pop rcx
	lea rcx, main
	sub rax, rcx
	mov eax, main
	mov ebx, offset var1
	ret
main endp

    end main
