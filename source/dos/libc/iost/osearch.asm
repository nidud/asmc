; OSEARCH.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc
include io.inc
include string.inc
include conio.inc

extrn	IDD_Search:	DWORD
extrn	searchstring:	BYTE

	.data
	cp_search	db 'Search',0
	cp_notfoundmsg	db "Search string not found: '%s'",0
	cp_stlsearch	db 'Search for the string:',0
	hexstring	db 128 dup(?)
	hexstrlen	dw 0

	.code

ioseek:
	lodm	STDI.ios_bb	; current offset | line:offset
	mov	cx,STDI.ios_flag
	and	STDI.ios_flag,not (IO_SEARCHSET or IO_SEARCHCUR)
	test	cx,IO_SEARCHSET
	jz	@F
	sub	ax,ax
	mov	dx,ax
	jmp	ioseek_set
      @@:
	test	cx,IO_SEARCHCUR
	jnz	ioseek_set
	add	ax,1		; offset++ (continue)
	adc	dx,0
    ioseek_set:
	mov	di,ax
	mov	bp,dx
	invoke	oseek,dx::ax,SEEK_SET
	ret

seekbx:
	cmp	bx,STDI.ios_i
	ja	@F
	sub	di,bx
	sbb	bp,0
	sub	STDI.ios_i,bx
	ret
      @@:
	push	si
	mov	si,bx
      @@:
	call	oungetc
	sub	di,1
	sbb	bp,0
	dec	si
	jnz	@B
	pop	si
	ret

lodhex:
	mov	al,[si]
	test	al,al
	jz	lodhex_end
	inc	si
	cmp	al,'0'
	jb	lodhex
	cmp	al,'9'
	jbe	lodhex_ok
	or	al,20h
	cmp	al,'f'
	ja	lodhex
	sub	al,27h
    lodhex_ok:
	sub	al,'0'
	test	si,si
    lodhex_end:
	ret

searchfound:
	mov	ax,si
	sub	ax,dx
	inc	ax
	sub	di,ax
	sbb	bp,0
	mov	ax,di
	mov	dx,bp
	or	di,1
	ret

searchhex:
	push bp
	push si
	push di
	push bx
	.if (STDI.ios_flag & IO_LINEBUF)
	    sub ax,ax
	    jmp searchhex_end
	.endif
	call ioseek
	jz  searchhex_end
	xor cx,cx
	mov si,offset searchstring
	mov bx,offset hexstring
    searchhex_xtol:
	call lodhex
	jz searchhex_hexl
	mov ah,al
	call lodhex
	jnz searchhex_mkb
	xchg al,ah
    searchhex_mkb:
	shl ah,4
	or  al,ah
	mov [bx],al
	inc bx
	inc cx
	jmp searchhex_xtol
    searchhex_found:
	call searchfound
    searchhex_end:
	pop bx
	pop di
	pop si
	pop bp
	ret
    searchhex_hexl:
	mov hexstrlen,cx
    searchhex_scan:
	mov dl,hexstring
	mov cx,STDI.ios_l
	  @@:
	    call ogetc
	    jz searchhex_end
	    add di,1	; inc offset
	    adc bp,0
	    mov ah,al
	    sub ah,10
	    cmp ah,1
	    adc cx,0	; inc line
	    cmp al,dl
	    jne @B
	mov STDI.ios_l,cx
	mov si,offset hexstring
    searchhex_cmp:
	call	ogetc
	jz	searchhex_end
	add	di,1
	adc	bp,0
	inc	si
	mov	dx,offset hexstring
	mov	cx,si
	sub	cx,dx
	cmp	cx,hexstrlen
	je	searchhex_found
	cmp	al,[si]
	je	searchhex_cmp
	mov	bx,si
	sub	bx,dx
	call	seekbx
	jmp	searchhex_scan

search:
	sub ax,ax
	.if searchstring != al
	    .if STDI.ios_flag & IO_SEARCHHEX
		jmp searchhex
	    .endif
	    jmp searchtxt
	.endif
	ret

searchtxt:
	push bp
	push si
	push di
	call ioseek
	jz   searchtxt_end
    searchtxt_scan:
	sub cx,cx
	.if STDI.ios_flag & IO_SEARCHCASE
	    mov dl,searchstring
	  @@:
	    call ogetc
	    jz searchtxt_end
	    add di,1	; inc offset
	    adc bp,0
	    cmp al,10
	    je searchtxt_l12
	searchtxt_l11:
	    cmp al,dl
	    jne @B
	.else
	    mov al,searchstring
	    sub al,'A'
	    cmp al,'Z'-'A'+1
	    sbb ah,ah
	    and ah,'a'-'A'
	    add al,ah
	    add al,'A'
	    mov dl,al	; tolower(*searchstring)
	  @@:
	    call ogetc
	    jz searchtxt_end
	    add di,1
	    adc bp,0
	    cmp al,10
	    je searchtxt_l22
	searchtxt_l21:
	    sub al,'A'
	    cmp al,'Z'-'A'+1
	    sbb ah,ah
	    and ah,'a'-'A'
	    add al,ah
	    add al,'A'	; tolower(AL)
	    cmp al,dl
	    jne @B
	.endif
	.if !(STDI.ios_flag & IO_LINEBUF)
	    add STDI.ios_l,cx
	.endif
	mov si,offset searchstring
    searchtxt_cmp:
	call ogetc
	jz  searchtxt_end
	add di,1
	adc bp,0
	inc si
	mov dx,offset searchstring
	mov cl,al
	mov al,[si]
	test al,al
	jz searchtxt_found
	cmp al,cl
	je searchtxt_cmp
	.if !(STDI.ios_flag & IO_SEARCHCASE)
	    sub al,'A'
	    cmp al,'Z'-'A'+1
	    sbb ah,ah
	    and ah,'a'-'A'
	    add al,ah
	    add al,'A'	; tolower(AL)
	    xchg al,cl
	    sub al,'A'
	    cmp al,'Z'-'A'+1
	    sbb ah,ah
	    and ah,'a'-'A'
	    add al,ah
	    add al,'A'	; tolower(CL)
	    cmp al,cl
	    je searchtxt_cmp
	.endif
	mov	bx,si
	sub	bx,dx
	call	seekbx
	jmp	searchtxt_scan
    searchtxt_found:
	call	searchfound
    searchtxt_end:
	pop	di
	pop	si
	pop	bp
	ret
    searchtxt_l12:
	inc	cx
	jmp	searchtxt_l11
    searchtxt_l22:
	inc	cx
	jmp	searchtxt_l21

notfoundmsg:
	mov cp_notfoundmsg+24,' '
	invoke strlen,addr searchstring
	cmp ax,29
	jb @F
	mov cp_notfoundmsg+24,10
      @@:
	invoke stdmsg,addr cp_search,addr cp_notfoundmsg,addr searchstring
	ret

continuesearch PROC _CType PUBLIC
local	StatusLine[160]:BYTE
	sub ax,ax
	.if searchstring
	    invoke wcpushst,addr StatusLine,addr cp_stlsearch
	    mov al,_scrrow
	    invoke scputs,24,ax,0,80-24,addr searchstring
	    invoke oseekl,STDI.ios_bb,SEEK_SET
	    .if ax
		.if STDI.ios_flag & IO_SEARCHHEX
		    call searchhex
		.else
		    call searchtxt
		.endif
		.if !ZERO?
		    stom STDI.ios_bb
		    mov ax,1
		    jmp @F
		.endif
	    .endif
	    call notfoundmsg
	    xor ax,ax
	  @@:
	    push ax
	    invoke wcpopst,addr StatusLine
	    pop ax
	.endif
	ret
continuesearch ENDP

osearch PROC _CType PUBLIC USES bx h:size_t,fsize:DWORD,buf:DWORD,bsize:size_t,flag:size_t
	mov	ax,h
	mov	STDI.ios_file,ax
	invoke	lseek,ax,0,SEEK_CUR
	cmp	dx,-1
	jne	@F
	cmp	ax,-1
	je	osearch_err
      @@:
	stom	STDI.ios_bb
	sub	ax,ax
	mov	STDI.ios_c,ax
	mov	STDI.ios_i,ax
	movmx	STDI.ios_size,bsize
	movmx	STDI.ios_bp,buf
	mov	ax,flag
	or	ax,IO_SEARCHCUR
	mov	STDI.ios_flag,ax
	call	search
	jnz	osearch_end
    osearch_err:
	mov	ax,-1
	mov	dx,ax
    osearch_end:
	mov	cx,STDI.ios_l
	ret
osearch ENDP

cmsearchidd PROC _CType PRIVATE USES si bx sflag:size_t
local DLG_Search:DWORD
	invoke	rsopen,IDD_Search
	stom	DLG_Search
	jz	cmsearchidd_nul
	mov	es,dx
	mov	bx,ax
	mov	es:[bx].S_TOBJ.to_count[1*16],128 shr 4
	mov	WORD PTR es:[bx].S_TOBJ.to_data[1*16],offset searchstring
	mov	WORD PTR es:[bx].S_TOBJ.to_data[1*16+2],ds
	mov	ax,sflag
	mov	dl,_O_FLAGB
	test	ax,IO_SEARCHCASE
	jz	cmsearchidd_hex?
	or	es:[bx][2*16],dl
    cmsearchidd_hex?:
	test	ax,IO_SEARCHHEX
	jz	cmsearchidd_cur?
	or	es:[bx][3*16],dl
    cmsearchidd_cur?:
	mov	dl,_O_RADIO
	test	ax,IO_SEARCHCUR
	jz	cmsearchidd_rset
	or	es:[bx][6*16],dl
	jmp	cmsearchidd_event
    cmsearchidd_nul:
	xor	ax,ax
	jmp	cmsearchidd_end
    cmsearchidd_rset:
	or	es:[bx][7*16],dl
    cmsearchidd_event:
	invoke	dlinit,DLG_Search
	invoke	rsevent,IDD_Search,DLG_Search
	test	ax,ax
	jz	cmsearchidd_nul
	mov	ax,sflag
	and	ax,not IO_SEARCHMASK
	mov	dl,_O_FLAGB
	test	es:[bx][2*16],dl
	jz	cmsearchidd_hex
	or	ax,IO_SEARCHCASE
    cmsearchidd_hex:
	test	es:[bx][3*16],dl
	jz	cmsearchidd_cur
	or	ax,IO_SEARCHHEX
    cmsearchidd_cur:
	test	BYTE PTR es:[bx][6*16],_O_RADIO
	jz	cmsearchidd_set
	or	ax,IO_SEARCHCUR
	jmp	cmsearchidd_toend
    cmsearchidd_set:
	or	ax,IO_SEARCHSET
    cmsearchidd_toend:
	mov	dx,ax
	sub	ax,ax
	cmp	searchstring,al
	je	cmsearchidd_end
	inc	ax
    cmsearchidd_end:
	mov	si,dx
	invoke	dlclose,DLG_Search
	mov	ax,dx
	mov	dx,si
	test	ax,ax
	ret
cmsearchidd ENDP

cmdsearch PROC _CType PUBLIC offs:DWORD
	sub	ax,ax
	cmp	ax,WORD PTR offs+2
	jne	cmdsearch_00
	cmp	WORD PTR offs,16
	jb	cmdsearch_end
    cmdsearch_00:
	invoke	cmsearchidd,STDI.ios_flag
	jz	cmdsearch_end
	mov	STDI.ios_flag,dx
	and	dx,IO_SEARCHCUR or IO_SEARCHSET
	push	dx
	call	continuesearch
	pop	dx
	or	STDI.ios_flag,dx
    cmdsearch_end:
	ret
cmdsearch ENDP

	END
