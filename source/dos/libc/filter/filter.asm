; FILTER.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include fblk.inc
include string.inc
include filter.inc

PUBLIC	filter
PUBLIC	filter_fblk
PUBLIC	filter_wblk

.data
filter	dd ?

.code

binary: ; CX = flag, AX = date, BX:DX = size
	mov	si,WORD PTR filter
	test	si,si
	jz	binary_ok
	cmp	ax,[si].S_FILT.of_min_date
	jb	binary_fail
	cmp	[si].S_FILT.of_max_date,0
	je	binary_min
	cmp	ax,[si].S_FILT.of_max_date
	ja	binary_fail
    binary_min:
      ifdef __3__
	cmp	edx,[si].S_FILT.of_min_size
      else
	cmp	bx,WORD PTR [si].S_FILT.of_min_size[2]
	jb	binary_fail
	ja	binary_max
	mov	ax,dx
	cmp	ax,WORD PTR [si].S_FILT.of_min_size
      endif
	jb	binary_fail
    binary_max:
    ifndef __16__
	mov	eax,[si].S_FILT.of_max_size
	test	eax,eax
	jz	binary_03
	cmp	edx,eax
    else
	mov	ax,WORD PTR [si].S_FILT.of_max_size[2]
	test	ax,ax
	jz	@F
	cmp	bx,ax
	ja	binary_fail
	jb	binary_03
      @@:
	mov	ax,WORD PTR [si].S_FILT.of_max_size
	test	ax,ax
	jz	binary_03
	cmp	dx,ax
    endif
	ja	binary_fail
    binary_03:
	mov	ax,cx
	and	ax,[si]
	cmp	ax,cx
	jne	binary_fail
    binary_ok:
	xor	ax,ax
	inc	ax
    binary_end:
	ret
    binary_fail:
	xor	ax,ax
	jmp	binary_end

string:
	xor	ax,ax
	cmp	al,[si].S_FILT.of_include
	je	string_01
	push	es
	invoke	cmpwargs,es::bx,addr [si].S_FILT.of_include
	pop	es
	jz	string_02
	xor	ax,ax
    string_01:
	cmp	al,[si].S_FILT.of_exclude
	je	string_03
	invoke	cmpwargs,es::bx,addr [si].S_FILT.of_exclude
	jz	string_03
    string_02:
	xor	ax,ax
	ret
    string_03:
	xor	ax,ax
	inc	ax
	ret

filter_fblk PROC _CType PUBLIC USES si bx fb:DWORD
	les	bx,fb
	mov	ax,WORD PTR es:[bx].S_FBLK.fb_time+2
	mov	cx,WORD PTR es:[bx].S_FBLK.fb_flag
      ifndef __16__
	mov	edx,es:[bx].S_FBLK.fb_size
      else
	mov	dx,WORD PTR es:[bx].S_FBLK.fb_size
	mov	bx,WORD PTR es:[bx].S_FBLK.fb_size+2
      endif
	call	binary
	jz	@F
	test	si,si
	jz	@F
	les	bx,fb
	add	bx,S_FBLK.fb_name
	call	string
      @@:
	test	ax,ax
	ret
filter_fblk ENDP

filter_wblk PROC _CType PUBLIC USES si bx wf:DWORD
	les	bx,wf
	mov	ax,WORD PTR es:[bx].S_WFBLK.wf_time
	mov	cx,WORD PTR es:[bx].S_WFBLK.wf_attrib
      ifdef __3__
	mov	edx,es:[bx].S_WFBLK.wf_sizeax
      else
	mov	dx,WORD PTR es:[bx].S_WFBLK.wf_sizeax
	mov	bx,WORD PTR es:[bx].S_WFBLK.wf_sizeax[2]
      endif
	call	binary
	jz	filter_wblk_00
	test	si,si
	jz	filter_wblk_00
	les	bx,wf
	add	bx,S_WFBLK.wf_name
	call	string
    filter_wblk_00:
	test	ax,ax
	ret
filter_wblk ENDP

	END
