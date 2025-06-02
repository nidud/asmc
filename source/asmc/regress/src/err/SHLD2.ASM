
	.386
	.model small

	.data

vb	db 0
vw	dw 0
vd	dd 0

	.code

main proc
	shld [vb],eax,1	;masm: invalid ops/jwasm: ops must be same size
	shld [vw],eax,1	;masm: delayed, wrong size/jwasm: ops must be same size
	shld [vd],eax,1
	shld bl,eax,1	;masm: byte register cannot be first op/jwasm: ops must be same size
	shld bx,eax,1	;masm: delayed, ops must be same size/jwasm: ops must be same size
	shld ebx,eax,1
	shld ebx,eax	;masm: syntax error/jwasm: invalid instruction operands
	shld ebx,eax,33
	shld ebx,eax,1234	;invalid instruction operands
	shld ebx,eax,cx		;invalid instruction operands
	shld ebx,eax,ecx	;invalid instruction operands
	shld [vb2],eax,1	;masm: delayed, invalid ops/jwasm: no display, 2nd pass error
	shld [vw2],eax,1	;masm: delayed, wrong size/jwasm: no display, 2nd pass error
	shld [vd2],edx,1
	shld ebx,edx,cl
	ret
main endp

	.data

vb2	db 0
vw2	dw 0
vd2	dd 0

    END
