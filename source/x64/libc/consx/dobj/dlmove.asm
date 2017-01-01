include consx.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

dlmove	PROC USES rdi dobj:PTR S_DOBJ
	mov	rdi,rcx
	mov	ax,[rdi]
	and	eax,_D_DMOVE or _D_DOPEN or _D_ONSCR
	cmp	eax,_D_DMOVE or _D_DOPEN or _D_ONSCR
	jne	error
	call	mousep
	jz	error
	lea	rax,[rdi].S_DOBJ.dl_rect
	movzx	r8d,[rdi].S_DOBJ.dl_flag
	rcmsmove( rax, [rdi].S_DOBJ.dl_wp, r8d )
	mov	eax,1
toend:
	ret
error:
	xor	eax,eax
	jmp	toend
dlmove	ENDP

	END
