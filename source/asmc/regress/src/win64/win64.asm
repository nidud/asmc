
	.code

	.win64: rbp

p1	proc
	ret
p1	endp

	.win64: noauto

p2	proc
	ret
p2	endp

	.win64: rsp auto

p3	proc
	ret
p3	endp

p4	proc uses rdi a1:byte, a2:word, a3:dword, a4:qword
	mov al,a1
	mov ax,a2
	mov eax,a3
	mov rax,a4
	ret
p4	endp

	.win64: nosave noauto

p5	proc uses rdi a1:byte, a2:word, a3:dword, a4:qword
	mov	al,a1
	mov	ax,a2
	mov	eax,a3
	mov	rax,a4
	ret
p5	endp


p6	proc uses rdi a1:byte, a2:word, a3:dword, a4:qword

  local l1:	byte,
	l2:	xmmword,
	l3:	byte,
	l4:	ymmword,
	l5:	byte

	lea	rax,l1
	lea	rax,l2
	lea	rax,l3
	lea	rax,l4
	lea	rax,l5

	mov	al,a1
	mov	ax,a2
	mov	eax,a3
	mov	rax,a4

	ret
p6	endp

	.win64: align

p7	proc uses rdi a1:byte, a2:word, a3:dword, a4:qword

  local l1:	byte,
	l2:	xmmword,
	l3:	byte,
	l4:	ymmword,
	l5:	byte

	lea	rax,l1
	lea	rax,l2
	lea	rax,l3
	lea	rax,l4
	lea	rax,l5

	mov	al,a1
	mov	ax,a2
	mov	eax,a3
	mov	rax,a4

	ret
p7	endp

	.win64: rbp

p8	proc uses rdi a1:byte, a2:word, a3:dword, a4:qword

  local l1:	byte,
	l2:	xmmword,
	l3:	byte,
	l4:	ymmword,
	l5:	byte

	lea	rax,l1
	lea	rax,l2
	lea	rax,l3
	lea	rax,l4
	lea	rax,l5

	mov	al,a1
	mov	ax,a2
	mov	eax,a3
	mov	rax,a4

	ret
p8	endp

	option cstack:on

	.win64: rbp noalign

p9	proc
	ret
p9	endp

	.win64: noauto

p10	proc
	ret
p10	endp

	.win64: rsp auto

p11	proc
	ret
p11	endp

p12	proc uses rdi a1:byte, a2:word, a3:dword, a4:qword
	mov al,a1
	mov ax,a2
	mov eax,a3
	mov rax,a4
	ret
p12	endp

	.win64: nosave noauto

p13	proc uses rdi a1:byte, a2:word, a3:dword, a4:qword
	mov	al,a1
	mov	ax,a2
	mov	eax,a3
	mov	rax,a4
	ret
p13	endp


p14	proc uses rdi a1:byte, a2:word, a3:dword, a4:qword

  local l1:	byte,
	l2:	xmmword,
	l3:	byte,
	l4:	ymmword,
	l5:	byte

	lea	rax,l1
	lea	rax,l2
	lea	rax,l3
	lea	rax,l4
	lea	rax,l5

	mov	al,a1
	mov	ax,a2
	mov	eax,a3
	mov	rax,a4

	ret
p14	endp

	.win64: align

p15	proc uses rdi a1:byte, a2:word, a3:dword, a4:qword

  local l1:	byte,
	l2:	xmmword,
	l3:	byte,
	l4:	ymmword,
	l5:	byte

	lea	rax,l1
	lea	rax,l2
	lea	rax,l3
	lea	rax,l4
	lea	rax,l5

	mov	al,a1
	mov	ax,a2
	mov	eax,a3
	mov	rax,a4

	ret
p15	endp

	.win64: rbp

p16	proc uses rdi a1:byte, a2:word, a3:dword, a4:qword

  local l1:	byte,
	l2:	xmmword,
	l3:	byte,
	l4:	ymmword,
	l5:	byte

	lea	rax,l1
	lea	rax,l2
	lea	rax,l3
	lea	rax,l4
	lea	rax,l5

	mov	al,a1
	mov	ax,a2
	mov	eax,a3
	mov	rax,a4

	ret
p16	endp

	END
