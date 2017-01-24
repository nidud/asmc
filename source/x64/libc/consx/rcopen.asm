include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

rcopen	PROC USES rsi rdi rbx rbp r12 rect, flag, attrib, ttl:LPSTR, wp:LPWSTR

	mov	esi,ecx
	mov	edi,edx
	mov	ebx,r8d
	mov	rbp,r9
	mov	r12,wp

	.if	!( edx & _D_MYBUF )
		rcalloc( ecx, edx )
		mov	r12,rax
		jz	toend
	.endif

	rcread( esi, r12 )
	mov	edx,edi
	and	edx,_D_CLEAR or _D_BACKG or _D_FOREG
	jz	toend

	shr	esi,16
	mov	eax,esi
	mul	ah
	mov	r8d,ebx

	.switch edx
	  .case _D_CLEAR : wcputw ( r12, eax, ' ' ) : .endc
	  .case _D_COLOR : wcputa ( r12, eax, r8d ) : .endc
	  .case _D_BACKG : wcputbg( r12, eax, r8d ) : .endc
	  .case _D_FOREG : wcputfg( r12, eax, r8d ) : .endc
	  .default
		mov	bh,bl
		mov	bl,' '
		mov	r8d,ebx
		wcputw( r12, eax, r8d )
	.endsw
	xor	eax,eax
	.if	rax != rbp
		and	esi,0FFh
		wctitle( r12, esi, rbp )
	.endif
toend:
	mov	rax,r12
	test	rax,rax
	ret
rcopen	ENDP

	END
