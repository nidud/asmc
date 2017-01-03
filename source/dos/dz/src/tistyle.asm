; TISTYLE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include libc.inc
ifdef __TE__
include alloc.inc
include conio.inc
include tinfo.inc
include ctype.inc
include string.inc
include stdlib.inc
include ini.inc

tigetline	PROTO

ST_COUNT	equ 9

S_STYLE		STRUC
st_line		dw ?	; current line index
st_bp		dd ?	; current line adress
st_boff		dw ?	; offset start of visible line
st_bend		dw ?	; end of visible line
st_wbuf		dw ?	; screen buffer (int *)
st_type		db ?	; current type
st_attr		db ?	; current attrib
st_slen		dw ?	; length of line
st_string	dw ?	; offset of first word
st_quote_start	dw ?	; first " or ' in line
st_quote_end	dw ?	; last " or ' in line
S_STYLE		ENDS

	.data

format_label label size_t
	dw tidoattrib	; 1. A Attrib
	dw tidocontrol	; 2. O Control
	dw tidoquote	; 3. Q Quote
	dw tidonumber	; 4. D Digit
	dw tidochar	; 5. C Char
	dw tidostring	; 6. S String
	dw tidostart	; 7. B Begin
	dw tidoword	; 8. W Word
	dw tidonested	; 9. N Nested

.code

tisetat:
	push	ax
	push	bx
	mov	ax,di
	dec	ax		; = offset in text line
	cmp	ax,[bp].S_STYLE.st_boff
	jb	@F
	cmp	ax,[bp].S_STYLE.st_bend
	ja	@F
	sub	ax,[bp].S_STYLE.st_boff
	add	ax,ax
	mov	bx,[bp].S_STYLE.st_wbuf
	add	bx,ax		; = offset in screen line (*int)
	mov	al,[bp].S_STYLE.st_attr
	xchg	bx,bp
	mov	[bp+1],al	; set attrib for this char
	mov	bp,bx
      @@:
	pop	bx
	pop	ax
	ret

tisetlen:			; Set length of string in SI to BX
	push	si		; Increase SI if string[0] == '"'
	sub	ax,ax		; if string[0] == '"' AH = '"' on return
	mov	bx,ax
	lodsb
	cmp	al,'"'
	jne	tisetlen_noquote
	mov	ah,al
    tisetlen_loop:
	lodsb
    tisetlen_noquote:
	test	al,al
	jz	@F
	cmp	al,'"'
	je	@F
	inc	bx
	jmp	tisetlen_loop
      @@:
	pop	si
	cmp	ah,'"'
	jne	@F
	inc	si
      @@:
	test	bx,bx
	ret

tistrchr:			; scan for next char
	lodsb
	test	al,al
	jz	tistrchr_end
	repne	scasb
	je	@F
	test	cx,cx
	ret
      @@:
	test	al,al
    tistrchr_end:
	ret

ticmpi:			; scan for next char no case
	push	bx
	lodsb
	test	al,al
	jz	ticmpi_nul
	call	isupper
	mov	bl,al
	jz	@F
	or	bl,20h
      @@:
	mov	al,es:[di]
	inc	di
	call	isupper
	jz	@F
	or	al,20h
      @@:
	cmp	al,bl
    ticmpi_end:
	pop	bx
	ret
    ticmpi_nul:
	or	bl,1
	jmp	ticmpi_end

tistrchri:			; scan for next char no case
	push	bx
	lodsb
	test	al,al
	jz	tistrchri_end
	push	ax
	call	isupper
	mov	bl,al
	jz	tistrchri_scan
	or	bl,20h
    tistrchri_scan:
	mov	al,es:[di]
	inc	di
	call	isupper
	jz	@F
	or	al,20h
      @@:
	cmp	al,bl
	je	@F
	dec	cx
	jnz	tistrchri_scan
	pop	ax
	pop	bx
	ret
      @@:
	pop	ax
	test	al,al
    tistrchri_end:
	pop	bx
	ret

ticmpsbi:
	push	cx
	push	si
	push	di
	push	bx
	mov	cx,bx
    ticmpsbi_lup:
	lodsb
	mov	bl,es:[di]
	inc	di
	cmp	ah,al		; AH == '"' or 0
	je	ticmpsbi_equal
	dec	cx
	jz	ticmpsbi_end
	or	bl,20h
	or	al,20h
	cmp	al,bl
	je	ticmpsbi_lup
	xor	cx,cx
	jmp	ticmpsbi_end
    ticmpsbi_equal:
	inc	cx
    ticmpsbi_end:
	pop	bx
	pop	di
	pop	si
	pop	cx
	ret

ticmpsb:
	push	cx
	push	si
	push	di
	mov	cx,bx
	repe	cmpsb
	cmp	ah,[si-1]	; AH == '"' or 0
	je	ticmpsb_equal
	xor	cx,cx
	jmp	ticmpsb_end
    ticmpsb_equal:
	inc	cx
    ticmpsb_end:
	pop	di
	pop	si
	pop	cx
	ret

tistrstr:
	mov	di,dx
	mov	cx,[bp].S_STYLE.st_slen

tistrstrdi:
	call	tisetlen
	jz	tistrstr_fail
	lodsb

tistrnext:
	repne	scasb
	je	@F
	test	cx,cx
	jz	tistrstr_fail
      @@:
	test	cx,cx
	jnz	@F
	mov	cx,bx
      @@:
	call	ticmpsb
	jz	tistrnext
	call	isquote
	jnz	tistrstr_fail
	test	al,al
	ret

tigetquote:
	mov	al,es:[si]
	inc	si
	test	al,al
	jz	tigetquote_end
	cmp	al,"'"
	je	tigetquote_quote
	cmp	al,'"'
	jne	tigetquote
    tigetquote_quote:
	test	al,al
    tigetquote_end:
	ret

isquote:
	push	si
	push	ax
	mov	ax,di
	dec	ax
	cmp	ax,[bp].S_STYLE.st_quote_end
	ja	isquote_00
	mov	si,[bp].S_STYLE.st_quote_start
	cmp	si,di
	jae	isquote_00
    isquote_l1:
	call	tigetquote
	jz	isquote_00
	cmp	di,si
	jb	isquote_00
	mov	ah,al
    isquote_l2:
	call	tigetquote
	jz	isquote_01
	cmp	ah,al
	jne	isquote_l2
	cmp	di,si
	ja	isquote_l1
    isquote_01:
	test	si,si
	jmp	isquote_end
    isquote_00:
	xor	ax,ax
    isquote_end:
	pop	ax
	pop	si
	ret

; 01,attrib[,0,char],0,0

tidoattrib:
	mov	al,[si-1]
	mov	bx,ss:tinfo
	mov	ss:[bx].S_TEDIT.ti_stat,al
	mov	al,[si]
	test	al,al
	jz	tidoattrib_end
	mov	ss:[bx].S_TEDIT.ti_stch,al
    tidoattrib_end:
	ret

; 05: <attrib>,<'chars'>,0,0

tidochar:
	mov	di,dx
	mov	cx,[bp].S_STYLE.st_slen
	call	tistrchr
	jnz	tidochar_set
	or	al,al
	jnz	tidochar
	ret
    tidochar_scan:
	repne	scasb
	je	tidochar_set
	test	cx,cx
	jz	tidochar
    tidochar_set:
	call	isquote
	jnz	tidochar_scan
	call	tisetat
	jmp	tidochar_scan

tistrstr_fail:
	xor	al,al
	ret

; 03ATstring,0

tidostart:
	call	tistrstr
	jz	tidostart_end
    tidostart_set:
	call	tisetat
	mov	al,es:[di]
	inc	di
	test	al,al
	jnz	tidostart_set
    tidostart_end:
	lodsb
	test	al,al
	jnz	tidostart_end
	cmp	[si],al
	jne	tidostart
	ret

; 04ATstring1,0,string2,0,0

MAXNLINES equ 3000

tifind	PROC pascal PRIVATE string:size_t, line:size_t, max:size_t
	push	si
	push	di
	push	bx
	call	tisetlen
	jz	tifind_end
	dec	line
    tifind_line:
	mov	si,string
	mov	al,[si]
	push	ds
	push	ss
	pop	ds
	mov	ax,line
	call	tigetline
    tifind_notfound:
	pop	ds
	jz	tifind_end
	push	dx
	push	ax
	mov	di,ax
	call	strlen
	jz	tifind_next
	mov	cx,ax
	add	di,ax
	dec	di
    tifind_scan:
	lodsb
	test	al,al
	jz	tifind_next
	std
	repne	scasb
	cld
	jne	tifind_next
	add	di,2
	mov	ah,0
	call	ticmpsb
	jnz	tifind_found
	sub	di,2
	dec	si
	jmp	tifind_scan
    tifind_next:
	dec	max
	jz	tifind_end
	dec	line
	jmp	tifind_line
    tifind_end:
	pop	bx
	pop	di
	pop	si
	ret
    tifind_found:
	mov	ax,line
	mov	dx,di
	dec	dx
	inc	bx
	jmp	tifind_end
tifind	ENDP

tinested:
	mov	di,dx			; .st_bp
	push	si
	push	di
	push	bx
	mov	ax,[bp].S_STYLE.st_line
	test	ax,ax			; line index
	jz	tinested_end
	push	si			; find last start-string
	push	ax
	push	MAXNLINES
	call	tifind
	jz	tinested_notfound
	mov	di,ax			; match line
	mov	bx,dx			; match offset
    tinested_endword:
	lodsb
	test	al,al
	jnz	tinested_endword
	cmp	[si],al		; second word ?
	je	tinested_found		; start, no end - ok
	push	si			; DI end-string
	push	[bp].S_STYLE.st_line
	push	MAXNLINES
	call	tifind
	jz	tinested_found		; start+end
	cmp	ax,di
	ja	tinested_notfound
	jb	tinested_found
	cmp	dx,bx
	ja	tinested_notfound
    tinested_found:			; open, find end..
	mov	bx,1
	jmp	tinested_popl
    tinested_notfound:
	xor	bx,bx
    tinested_popl:
	mov	ax,[bp].S_STYLE.st_line ; back to this line
	push	ds
	push	ss
	pop	ds
	call	tigetline
	pop	ds
	mov	es,dx
	mov	dx,ax
	test	bx,bx
    tinested_end:
	pop	bx
	pop	di
	pop	si
	ret

stgetnextarg:
	lodsb
	test	al,al
	jnz	stgetnextarg
	ret

tidonested:
	call	tisetlen		; BX to length of first arg
	jz	tistrstr_fail
	call	tinested		; find start condition
	mov	cx,[bp].S_STYLE.st_slen ; CX to length of line
	jz	tidonested_line
	call	stgetnextarg
	jmp	tidonested_seek
    tidonested_next:
	mov	si,[bp].S_STYLE.st_string
	mov	cx,[bp].S_STYLE.st_slen
	sub	cx,di
	jle	tidonested_end
	call	tistrstrdi
	jz	tidonested_end
	jmp	tidonested_first
    tidonested_line:
	mov	si,[bp].S_STYLE.st_string
	call	tistrstr
	jz	tidonested_end
    tidonested_first:
	call	tisetat
	lodsb
	test	al,al
	jz	tidonested_seek
	inc	di
	assert	cx,0,jne,"nested"
	dec	cx
	jnz	tidonested_first
	call	tisetat
    tidonested_seek:
	test	cx,cx
	jz	tidonested_end
	lodsb
	test	al,al
	jz	tidonested_end
	push	si
	push	di
	call	tistrnext
	mov	cx,di
	pop	di
	pop	si
	jz	tidonested_null
	sub	cx,di
	jle	tidonested_end
    tidonested_pad:
	call	tisetat
	inc	di
	dec	cx
	jnz	tidonested_pad
	add	cx,bx
	jz	tidonested_end
	dec	di
    tidonested_endtag:
	inc	di
	call	tisetat
	dec	cx
	jnz	tidonested_endtag
    tidonested_end:
	cmp	di,[bp].S_STYLE.st_slen
	jb	tidonested_next
	ret
    tidonested_null:
	dec	di
	mov	cx,[bp].S_STYLE.st_slen
	sub	cx,di
	jg	tidonested_endtag
	jmp	tidonested_end

; 02FBstring1,0,string2,0,..,0

tiistart:		; test if di is the first char in a word
	push	ax	; di is match + 1, di-2 is char in front
	mov	ax,di
	dec	ax
	cmp	ax,WORD PTR [bp].S_STYLE.st_bp
	je	tiistart_ok	; start of line
	assertf jnb,"tiistart"
	mov	al,es:[di][-2]
	cmp	al,'_'
	je	@F
	call	getctype
	jz	tiistart_end
	and	ah,_UPPER or _LOWER or _DIGIT
	jz	tiistart_ok
      @@:
	sub	al,al
	jmp	tiistart_end
    tiistart_ok:
	inc	ax
    tiistart_end:
	pop	ax
	ret

tidoword:		; match on all equal words if not inside quote
	mov	di,dx
	mov	cx,[bp].S_STYLE.st_slen
	call	tisetlen
	jz	tidoword_end
    tidoword_scan:
	call	tistrchri
	jnz	tidoword_set
      @@:
	test	al,al
	jz	@F
	lodsb
	jmp	@B
      @@:
	lodsb
	test	al,al
	jz	tidoword_end
	dec	si
	jmp	tidoword
    tidoword_find:
	dec	si
	jmp	tidoword_scan
    tidoword_set:
	call	ticmpsbi
	jz	tidoword_find
	push	si
	push	bx
	push	ax
	call	isquote
	jnz	tidoword_pop	; = inside quote
	call	tiistart
	jz	tidoword_pop
	mov	al,es:[bx][di-1]
	call	islabel
	jnz	tidoword_pop
      @@:
	call	tisetat
	inc	di
	dec	bx
	jnz	@B
	dec	di
    tidoword_pop:
	pop	ax
	pop	bx
	pop	si
	jmp	tidoword_find
    tidoword_end:
	ret

tidocontrol:		; match on all control chars
	mov	di,[bp].S_STYLE.st_boff
    tidocontrol_loop:
	mov	al,es:[di]
	inc	di
	test	al,al
	jz	tidocontrol_end
	call	getctype
	test	ah,ah
	jz	@F
	and	ah,_CONTROL
	jz	tidocontrol_next
	cmp	al,TITABCHAR
	je	tidocontrol_next
	cmp	al,9
	je	tidocontrol_next
	mov	bx,ss:tinfo
	test	ss:[bx].S_TINFO.ti_flag,_T_SHOWTABS
	jz	tidocontrol_next
      @@:
	call	tisetat
    tidocontrol_next:
	cmp	di,[bp].S_STYLE.st_bend
	jb	tidocontrol_loop
    tidocontrol_end:
	ret

tidostring:		; match on all equal strings if not inside quote
	mov	di,dx
	mov	cx,[bp].S_STYLE.st_slen
	call	tisetlen
	jz	tidostring_end
	call	tistrchr
	jnz	tidostring_set
    tidostring_next:
	test	al,al
	jz	@F
	lodsb
	jmp	tidostring_next
      @@:
	lodsb
	test	al,al
	jz	tidostring_end
	dec	si
	jmp	tidostring
    tidostring_scan:
	repne	scasb
	test	cx,cx
	jz	tidostring_next
    tidostring_set:
	call	ticmpsb
	jz	tidostring_scan
	push	si
	push	bx
	call	isquote
	jnz	tidostring_pop	; = inside quote
      @@:
	call	tisetat
	inc	di
	dec	bx
	jnz	@B
	dec	di
    tidostring_pop:
	pop	bx
	pop	si
	jmp	tidostring_scan
    tidostring_end:
	ret

tidoquote:		; match on '"' and "'", fail on "\"C\""
	mov	di,WORD PTR [bp].S_STYLE.st_bp
    tidoquote_loop:
	mov	al,es:[di]
	inc	di
	test	al,al
	jz	tidoquote_end
	call	isquote
	jz	@F
	call	tisetat
      @@:
	cmp	di,[bp].S_STYLE.st_bend
	jb	tidoquote_loop
    tidoquote_end:
	ret

tidonumber:		; match on 0x 0123456789ABCDEF and Xh
	mov	di,[bp].S_STYLE.st_boff
    tidonumber_loop:
	mov	al,es:[di]
	inc	di
	call	getctype
	jz	tidonumber_end
	test	ah,_DIGIT
	jz	tidonumber_next
	call	isquote
	jnz	tidonumber_next
	call	tiistart
	jz	tidonumber_next
	mov	si,di
	cmp	al,'0'
	jne	@F
	mov	al,es:[si]
	inc	si
	or	al,20h
	cmp	al,'x'
	je	@F
	dec	si
      @@:
	mov	al,es:[si]
	inc	si
	call	getctype
	jz	tidonumber_set
	test	ah,_HEX
	jnz	@B
	or	al,20h
	cmp	al,'h'
	jne	@F
	inc	si
	jmp	tidonumber_set
      @@:
	and	ah,_UPPER or _LOWER
	jnz	tidonumber_next
    tidonumber_set:
	sub	si,di
      @@:
	call	tisetat
	inc	di
	dec	si
	jnz	@B
    tidonumber_next:
	cmp	di,[bp].S_STYLE.st_bend
	jb	tidonumber_loop
    tidonumber_end:
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

tisetquote:	; "s\"C\"e"
	push	si
	xor	ax,ax
	mov	[bp].S_STYLE.st_quote_start,ax
	mov	[bp].S_STYLE.st_quote_end,ax
	mov	si,WORD PTR [bp].S_STYLE.st_bp
	invoke	strlen,[bp].S_STYLE.st_bp	; set ES:SI line
	mov	cx,ax				; CX to eol
	add	cx,si
    tisetquote_00:
	sub	ax,ax
	call	tigetquote
	jz	tisetquote_end
	mov	ah,al
	mov	bx,si
	dec	bx
	mov	[bp].S_STYLE.st_quote_end,cx
      @@:
	call	tigetquote
	jz	tisetquote_eof
	cmp	ah,al
	jne	@B
	cmp	si,cx
	jbe	tisetquote_00
	mov	ax,bx
	cmp	ax,cx
	jnb	@F
	mov	ax,WORD PTR [bp].S_STYLE.st_bp
      @@:
	mov	[bp].S_STYLE.st_quote_start,ax
	mov	bx,si
      @@:
	call	tigetquote
	jz	@F
	mov	bx,si
	jmp	@B
      @@:
	mov	ax,bx
	dec	ax
	mov	[bp].S_STYLE.st_quote_end,ax
    tisetquote_end:
	pop	si
	ret
    tisetquote_eof:
	mov	ax,WORD PTR [bp].S_STYLE.st_bp
	mov	[bp].S_STYLE.st_quote_start,ax
	jmp	tisetquote_end

tistyle PROC pascal PUBLIC
local	style:S_STYLE
	push	si
	push	di
	push	bp
	push	ds
	lea	bp,style
	mov	[bp].S_STYLE.st_line,bx		; line id
	mov	WORD PTR [bp].S_STYLE.st_bp,ax	; pointer to line
	mov	WORD PTR [bp].S_STYLE.st_bp[2],di
	mov	[bp].S_STYLE.st_wbuf,dx		; output buffer (*int) (SS)
	mov	[bp].S_STYLE.st_slen,cx ; length of line
	add	ax,[si].S_TINFO.ti_boff ; start of line
	mov	[bp].S_STYLE.st_boff,ax
	mov	dx,ax
	add	ax,cx
	add	dx,TIMAXSCRLINE
	cmp	ax,dx
	jb	@F
	mov	ax,dx
	dec	ax
      @@:
	mov	[bp].S_STYLE.st_bend,ax		; end of line
	mov	si,tinfo
	lds	si,[si].S_TEDIT.ti_style	; DS:SI style
	test	si,si
	jz	tistyle_end
	call	tisetquote
    tistyle_loop:
	lodsw
	mov	[bp].S_STYLE.st_attr,ah
	mov	[bp].S_STYLE.st_type,al
	test	al,al
	je	tistyle_end
	mov	ah,0
	dec	ax
	cmp	al,ST_COUNT
	jnb	tistyle_end
	add	ax,ax
	mov	di,ax
	mov	[bp].S_STYLE.st_string,si
	mov	dx,WORD PTR [bp].S_STYLE.st_bp
	push	si
	call	ss:format_label[di]
	pop	si
      @@:
	lodsb
	test	al,al
	jnz	@B
	lodsb
	test	al,al
	jnz	@B
	jmp	tistyle_loop
    tistyle_end:
	pop	ds
	pop	bp
	pop	di
	pop	si
	ret
tistyle ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
; 1. Attrib	A -	Set background and forground color
; 2. Control	O -	Set color of CONTROL characters
; 3. Quote	Q -	Set color of quoted text
; 4. Digit	D -	Set color of numbers
; 5. Char	C -	Set color of chars
; 6. String	S -	Set color of string
; 7. Begin	B -	Set color from start of string
; 8. Word	W -	Set color of words
; 9. Nested	N -	Set color of nested strings
;
.data
externdef	cp_style:BYTE
externdef	configpath:BYTE
externdef	configfile:BYTE

cp_stdefault	db 'style_default',0
cp_typech	db 'aoqdcsbwn',0

ID_TYPE		equ 0
ID_ATTRIB	equ 1

ST_ATTRIB	equ 1	; attrib	<at> [<char>]
ST_CHAR		equ 2	; char		<at> <chars>
ST_WORD		equ 3	; word		<at> <words> ...
ST_START	equ 4	; start		<at> <string>
ST_NESTED	equ 5	; nested	<at> <string1> <string2>
ST_CONTROL	equ 6	; control	<at>
;ST_STRING	equ 7	; string	<at> <string>
ST_QUOTE	equ 8	; quote		<at>
ST_NUMBER	equ 9	; number	<at>
ST_COUNT	equ ST_NUMBER

S_RDST		STRUC
st_file		db 256 dup(?)
st_path		db 256 dup(?)
st_section	db 64 dup(?)
st_label	db 64 dup(?)
st_sp		dd ?
st_eof		dw ?	; style + SIZE style - 2
st_style	db STYLESIZE dup(?)
S_RDST		ENDS

.code

getentry:
	invoke	inientryid,ds::dx,ax
	ret

tireadlabel:
	push	si
	push	di
	lea	si,[bp].S_RDST.st_label
	mov	ax,ID_TYPE
	mov	dx,si
	call	getentry
	jz	tireadlabel_end
	les	di,[bp].S_RDST.st_sp
	cmp	di,[bp].S_RDST.st_eof
	ja	tireadlabel_end
	mov	bx,ax
	mov	ah,[bx]
	or	ah,20h
	xor	cx,cx
	xchg	cx,bx
      @@:
	mov	al,cp_typech[bx]
	cmp	al,ah
	je	@F
	inc	bx
	test	al,al
	jnz	@B
	jmp	tireadlabel_end
      @@:
	mov	al,bl
	inc	al
	mov	bx,cx
	stosb
	mov	ah,0
	mov	si,ax
	xor	cx,cx
      @@:
	inc	bx
	mov	al,[bx]
	call	islabel
	jnz	@B
	push	si
	mov	si,bx
    tireadlabel_loop:
	lodsb
	cmp	al,' '
	jne	@F
	mov	ax,si
	pop	si
	jmp	tireadlabel_attrib
      @@:
	test	al,al
	jnz	tireadlabel_loop
	pop	si
	push	es
	mov	ax,ID_ATTRIB
	mov	dx,bx
	call	getentry
	pop	es
	mov	cx,1
	jz	tireadlabel_break
    tireadlabel_attrib:
	mov	bx,ax
	add	ax,2
	push	ax
	mov	ax,[bx]
	or	ax,2020h
	cmp	al,'x'
	jne	tireadlabel_bg
	mov	al,ah
	call	getctype
	and	ah,_HEX or _DIGIT
	jz	tireadlabel_getat
	sub	al,'0'
	and	ah,_DIGIT
	jnz	@F
	sub	al,39
      @@:
	mov	bx,tinfo
	mov	ah,[bx].S_TEDIT.ti_stat
	and	ah,0F0h
	or	al,ah
	jmp	tireadlabel_stoat
    tireadlabel_getat:
	push	es
	push	cx
	invoke	xtol,dx::bx
	pop	cx
	pop	es
	jmp	tireadlabel_stoat
    tireadlabel_bg:
	cmp	ah,'x'
	jne	tireadlabel_getat
	call	getctype
	and	ah,_HEX or _DIGIT
	jz	tireadlabel_getat
	sub	al,'0'
	and	ah,_DIGIT
	jnz	@F
	sub	al,39
      @@:
	shl	al,4
	mov	bx,tinfo
	mov	ah,[bx].S_TEDIT.ti_stat
	and	ah,0Fh
	or	al,ah
    tireadlabel_stoat:
	stosb
	pop	bx
      @@:
	mov	ah,[bx]
	inc	bx
	cmp	ah,' '
	je	@B
	dec	bx
	cmp	si,ST_ATTRIB
	je	tireadlabel_char
	mov	si,cx
	inc	si
	mov	ax,bx
	jmp	tireadlabel_start
    tireadlabel_label:
	cmp	si,100
	je	tireadlabel_break
	mov	ax,si
	inc	si
	push	es
	lea	dx,[bp].S_RDST.st_label
	call	getentry
	pop	es
	jz	tireadlabel_break
    tireadlabel_start:
	mov	bx,si
	mov	cx,[bp].S_RDST.st_eof
	mov	si,ax
	cmp	BYTE PTR [si],0
	je	tireadlabel_endcopy
    tireadlabel_copy:
	lodsb
	cmp	di,cx
	jae	tireadlabel_endcopy
	cmp	al,' '
	jne	@F
	mov	al,0
	stosb
	jmp	tireadlabel_copy
      @@:
	stosb
	test	al,al
	jnz	tireadlabel_copy
    tireadlabel_endcopy:
	mov	si,bx
	jmp	tireadlabel_label
    tireadlabel_char:
	mov	si,tinfo
	mov	[si].S_TEDIT.ti_stat,al
	test	ah,ah
	jz	tireadlabel_break
	push	es
	invoke	xtol,ss::bx
	pop	es
	mov	[si].S_TEDIT.ti_stch,al
	stosb
    tireadlabel_break:
	sub	ax,ax
	cmp	es:[di][-1],al
	je	@F
	stosb
      @@:
	stosb
	mov	WORD PTR [bp].S_RDST.st_sp,di
	inc	ax
    tireadlabel_end:
	pop	di
	pop	si
	ret

tidosection:
	push	si
	push	di
	sub	sp,64
	mov	di,sp
	invoke	memcpy,ss::di,addr [bp].S_RDST.st_section,64
	xor	si,si
    tidosection_do:
	mov	ax,si
	inc	si
	lea	dx,[bp].S_RDST.st_section
	call	getentry
	jz	tidosection_end
	mov	di,ax
	mov	al,[di]
	cmp	al,'['
	jne	tidosection_label
	mov	bx,si
	mov	dx,di
	mov	si,di
	inc	si
	lea	di,[bp].S_RDST.st_section
      @@:
	lodsb
	stosb
	test	al,al
	jz	@F
	cmp	al,']'
	jne	@B
      @@:
	dec	di
	sub	ax,ax
	stosb
	mov	si,bx
	mov	di,dx
	call	tidosection
	mov	dx,sp
	invoke	strcpy,addr [bp].S_RDST.st_section,ds::dx
	jmp	tidosection_do
    tidosection_label:
	lea	ax,[bp].S_RDST.st_label
	invoke	strcpy,dx::ax,dx::di
	call	tireadlabel
	jmp	tidosection_do
    tidosection_end:
	add	sp,64
	pop	di
	pop	si
	ret

tireadstyle PROC pascal PUBLIC
local rdst:S_RDST
	push	si
	push	di
	push	bx
	push	bp
	lea	bp,rdst
	lea	ax,[bp].S_RDST.st_style
	mov	WORD PTR [bp].S_RDST.st_sp,ax
	mov	WORD PTR [bp].S_RDST.st_sp[2],ss
	push	ss
	pop	es
	mov	di,ax
	add	ax,STYLESIZE-4
	mov	[bp].S_RDST.st_eof,ax
	xor	ax,ax
	cld?
	mov	cx,STYLESIZE/2
	rep	stosw
	invoke	strcpy,addr [bp].S_RDST.st_section,addr cp_stdefault
	mov	si,tinfo
	invoke	strfn,[si].S_TEDIT.ti_file	; name || name.ext
	mov	di,ax
	invoke	strrchr,dx::ax,'.'		; *.ext ?
	jz	@F
	inc	ax
	mov	di,ax
     @@:
	invoke	inientry,addr cp_style,es::di,addr configfile
	jz	@F
	mov	cx,ax
	invoke	strcpy,addr [bp].S_RDST.st_section,dx::cx
     @@:
	call	tidosection
	les	di,[bp].S_RDST.st_sp
	xor	ax,ax
	stosw
	lea	si,[bp].S_RDST.st_style
	sub	di,si
	cmp	di,STYLESIZE
	ja	@F
	invoke	malloc,di
	mov	bx,tinfo
	stom	[bx].S_TEDIT.ti_style
	test	ax,ax
	jz	@F
	invoke	memcpy,dx::ax,ds::si,di
     @@:
	pop	bp
	pop	bx
	pop	di
	pop	si
	ret
tireadstyle ENDP
endif
	END
