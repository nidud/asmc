
;--- v2.19: change in parser.c, memory_operand():
;--- offset magnitude for 16-bit segment is determined by
;--- assume ( 32-bit if assume ds:flat, 16-bit if assume ds:data16 ).

	.386

_DATA16 segment word use16 public 'DATA'

	assume ds:_DATA16

v1	dd 12345678h

rmcb dd 0

_DATA16 ends

_TEXT segment dword flat public 'CODE'

_start:
	MOV  AH,4Ch
	INT  21h

	mov [rmcb], edx
	mov edx, [rmcb]
	mov esi, offset rmcb
	ret

_TEXT ends

    END _start
