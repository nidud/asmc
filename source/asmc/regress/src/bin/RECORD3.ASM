
;--- 64-bit records (in 64-bit code only)

ifndef __ASMC64__
    .x64
    .model flat
endif
ifdef __ASMC__
option masm:on
endif
	option casemap:none

	.data

REC1	RECORD res1:22,rf1:12=0fffh,bit12:30

v1	REC1 <>
	db -1

S1	struct
f1	db ?
f2	REC1 <>
f3	db ?
S1	ends

	.code

	mov rax, MASK rf1
	mov rax, [ebx].S1.f2
	nop

	end
