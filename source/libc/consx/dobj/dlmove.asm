include consx.inc

	.code

dlmove	PROC USES edi dobj:PTR S_DOBJ
	mov	edi,dobj
	mov	ax,[edi]
	and	eax,_D_DMOVE or _D_DOPEN or _D_ONSCR
	cmp	eax,_D_DMOVE or _D_DOPEN or _D_ONSCR
	jne	error
	call	mousep
	jz	error
	lea	eax,[edi].S_DOBJ.dl_rect
	movzx	ecx,[edi].S_DOBJ.dl_flag
	rcmsmove( eax, [edi].S_DOBJ.dl_wp, ecx )
	mov	eax,1
toend:
	ret
error:
	sub	eax,eax
	jmp	toend
dlmove	ENDP

	END
