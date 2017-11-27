include wsub.inc
include string.inc
include filter.inc
include time.inc
include winbase.inc

PUBLIC	filter
PUBLIC	filter_fblk
PUBLIC	filter_wblk

cmpwargs proto :LPSTR, :LPSTR

	.data
	filter	SIZE_T 0

	.code

	OPTION	PROC: PRIVATE

binary	PROC ; CX = flag, AX = date, BX:DX = size
	mov	esi,filter
	test	esi,esi
	jz	toend
	cmp	eax,[esi].S_FILT.of_min_date
	jb	fail
	cmp	[esi].S_FILT.of_max_date,0
	je	@min
	cmp	eax,[esi].S_FILT.of_max_date
	ja	fail
@min:
	cmp	edx,[esi].S_FILT.of_min_size
	jb	fail
@max:
	mov	eax,[esi].S_FILT.of_max_size
	test	eax,eax
	jz	@03
	cmp	edx,eax
	ja	fail
@03:
	mov	eax,ecx
	and	ax,[esi]
	cmp	eax,ecx
	jne	fail
toend:
	xor	eax,eax
	inc	eax
	ret
fail:
	xor	eax,eax
	ret
binary	ENDP

string	PROC
	xor	eax,eax
	cmp	al,[esi].S_FILT.of_include
	je	@01
	cmpwargs( ebx, addr [esi].S_FILT.of_include )
	jz	@02
	xor	eax,eax
@01:
	cmp	al,[esi].S_FILT.of_exclude
	je	@03
	cmpwargs( ebx, addr [esi].S_FILT.of_exclude )
	jz	@03
@02:
	xor	eax,eax
	ret
@03:
	xor	eax,eax
	inc	eax
	ret
string	ENDP

	OPTION	PROC: PUBLIC

filter_fblk PROC USES esi ebx fb:PTR S_FBLK
	mov	ebx,fb
	mov	eax,[ebx].S_FBLK.fb_time
	and	eax,0FFFF0000h
	mov	ecx,[ebx].S_FBLK.fb_flag
	mov	edx,dword ptr [ebx].S_FBLK.fb_size
	call	binary
	jz	@F
	test	esi,esi
	jz	@F
	mov	ebx,fb
	add	ebx,S_FBLK.fb_name
	call	string
@@:
	test	eax,eax
	ret
filter_fblk ENDP

filter_wblk PROC USES esi ebx wf:PTR WIN32_FIND_DATA
	mov	ebx,wf
	__FTToTime( addr [ebx].WIN32_FIND_DATA.ftLastWriteTime )
	and	eax,0xFFFF0000
	mov	ecx,[ebx].WIN32_FIND_DATA.dwFileAttributes
	mov	edx,[ebx].WIN32_FIND_DATA.nFileSizeLow
	mov	ebx,[ebx].WIN32_FIND_DATA.nFileSizeHigh
	call	binary
	jz	@F
	test	esi,esi
	jz	@F
	mov	ebx,wf
	add	ebx,WIN32_FIND_DATA.cFileName
	call	string
@@:
	test	eax,eax
	ret
filter_wblk ENDP

	END
