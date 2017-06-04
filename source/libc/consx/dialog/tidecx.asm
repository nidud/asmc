include consx.inc

	.code

	ASSUME	edx: PTR S_TEDIT

tidecx	PROC USES eax ecx ti:PTR S_TEDIT
	mov edx,ti

	mov eax,[edx].ti_boff
	add eax,[edx].ti_xoff
	jz  toend

	mov ecx,[edx].ti_boff
	mov eax,[edx].ti_xoff
	test eax,eax
	jz @F

	dec eax
	and edx,edx
	stc
	jmp done
@@:
	dec ecx
	test edx,edx
	clc
done:
	mov [edx].ti_xoff,eax
	mov [edx].ti_boff,ecx
toend:
	ret
tidecx	ENDP

tiincx	PROC USES eax ecx ti:PTR S_TEDIT
	mov edx,ti
	mov eax,[edx].ti_boff
	add eax,[edx].ti_xoff
	inc eax
	cmp eax,[edx].ti_bcol
	jb  @F
	sub eax,eax
	jmp toend
@@:
	mov ecx,[edx].ti_boff
	mov eax,[edx].ti_xoff
	inc eax
	cmp eax,[edx].ti_cols
	jb  @F
	mov eax,[edx].ti_cols
	dec eax
	inc ecx
@@:
	mov [edx].ti_xoff,eax
	mov [edx].ti_boff,ecx
toend:
	ret
tiincx ENDP

	END
