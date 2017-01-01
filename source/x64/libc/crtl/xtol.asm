include stdlib.inc

	.code

	OPTION	WIN64:0, STACKBASE:rsp

xtol	PROC string:LPSTR
	xor	rax,rax
	xor	r8,r8
do:
	mov	al,[rcx]
	or	al,20h
	inc	rcx
	cmp	al,'0'
	jb	toend
	cmp	al,'f'
	ja	toend
	cmp	al,'9'
	ja	@F
	sub	al,'0'
	jmp	@03
@@:
	cmp	al,'a'
	jb	toend
	sub	al,87
@03:
	shl	r8,4
	add	r8,rax
	jmp	do
toend:
	mov	rax,r8
	ret
xtol	ENDP

	END
