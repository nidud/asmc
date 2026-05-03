
; v2.21 - OPTION CSTACK to 64-bit
;
ifndef __ASMC64__
    .x64
    .model flat, fastcall
endif
	.code

	option win64:3
ifdef __ASMC__
	option cstack:off ; default is off..
endif
Cs_OFF	PROC USES rsi rdi rbx a1, a2, a3, a4
;	mov	[rsp+8],rcx
;	mov	[rsp+16],rdx
;	mov	[rsp+24],r8
;	mov	[rsp+32],r9
;	push	rbp
;	mov	rbp,rsp
;	push	rsi
;	push	rdi
;	push	rbx
	sub	rsp,rax ; fails..
	mov	ecx,a1	; [rbp+10H]
	mov	edx,a2	; [rbp+18H]
	mov	r8d,a3	; [rbp+20H]
	mov	r9d,a4	; [rbp+28H]
;	pop	rbx
;	pop	rdi
;	pop	rsi
;	leave
	ret
Cs_OFF	ENDP

ifdef __ASMC__
	option	cstack:on
endif
Cs_ON	PROC USES rsi rdi rbx a1, a2, a3, a4
;	mov	[rsp+8],rcx
;	mov	[rsp+16],rdx
;	mov	[rsp+24],r8
;	mov	[rsp+32],r9
;	push	rsi
;	push	rdi
;	push	rbx
;	push	rbp
;	mov	rbp,rsp
	sub	rsp,rax
	mov	ecx,a1	; [rbp+28H]
	mov	edx,a2	; [rbp+30H]
	mov	r8d,a3	; [rbp+38H]
	mov	r9d,a4	; [rbp+40H]
;	leave
;	pop	rbx
;	pop	rdi
;	pop	rsi
	ret
Cs_ON	ENDP

parse_pass PROC USES rsi rbx pInput:ptr

	xor	esi,esi
	mov	rbx,pInput
	.switch ecx
	  .case 1 : db 11 dup(0x90) : .endc
	  .case 2 : db 11 dup(0x90) : .endc
	  .case 3 : db 11 dup(0x90) : .endc
	  .case 4 : db 11 dup(0x90) : .endc
	  .case 5 : db 11 dup(0x90) : .endc
	  .case 6 : db 11 dup(0x90) : .endc
	  .case 7 : db 13 dup(0x90) : .endc
	  .case 8 : db 14 dup(0x90) : .endc
	  .case 9 : db 17 dup(0x90) : .endc
	.endsw
	ret

parse_pass ENDP

	option stackbase:rsp

Cs_RSP PROC USES rsi rdi rbx a1, a2, a3, a4
;	mov	[rsp+8],rcx
;	mov	[rsp+16],rdx
;	mov	[rsp+24],r8
;	mov	[rsp+32],r9
;	push	rsi
;	push	rdi
;	push	rbx
	sub	rsp,rax ; fails..
	mov	ecx,a1	; [rsp+40H]
	mov	edx,a2	; [rsp+48H]
	mov	r8d,a3	; [rsp+50H]
	mov	r9d,a4	; [rsp+58H]
;	pop	rbx
;	pop	rdi
;	pop	rsi
	ret
Cs_RSP	ENDP

	END
