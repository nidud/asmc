include iost.inc
include io.inc
include string.inc

	.code

ioseek	PROC USES esi iost:PTR S_IOST, offs:qword, from
	mov	esi,iost
	mov	eax,dword ptr offs
	mov	edx,dword ptr offs[4]
	cmp	from,SEEK_CUR
	je	seekcur
	test	[esi].S_IOST.ios_flag,IO_MEMBUF
	jnz	seekset
seekoff:
	_lseeki64( [esi].S_IOST.ios_file, edx::eax, from )
	cmp	eax,-1
	je	toend
	mov	dword ptr [esi].S_IOST.ios_offset,eax
	mov	dword ptr [esi].S_IOST.ios_offset[4],edx
	sub	ecx,ecx
	mov	[esi].S_IOST.ios_i,ecx
	mov	[esi].S_IOST.ios_c,ecx
	inc	ecx
	jmp	toend
seekcur:
	mov	ecx,[esi].S_IOST.ios_c
	sub	ecx,[esi].S_IOST.ios_i
	cmp	ecx,eax
	jb	seekoff
	add	[esi].S_IOST.ios_i,eax
	jmp	done
seekset:
	cmp	eax,[esi].S_IOST.ios_c
	ja	fail
	mov	[esi].S_IOST.ios_i,eax
done:
	test	esi,esi
toend:
	ret
fail:
	sub	eax,eax
	mov	eax,-1
	mov	edx,eax
	jmp	toend
ioseek	ENDP

	END
