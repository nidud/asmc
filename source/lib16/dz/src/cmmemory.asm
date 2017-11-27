; CMMEMORY.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include iost.inc
include conio.inc
include string.inc
include stdio.inc
include alloc.inc
include stdlib.inc

extrn	_psp:WORD
extrn	IDD_DZMemory:DWORD

LINESIZE	equ 64
MAXLINES	equ 64
ID_COUNT	equ 11

S_MCB		STRUC
mcb_flag	db ?
mcb_owner	dw ?
mcb_size	dw ?
mcb_unused	db 3 dup(?)
mcb_name	db 8 dup(?)
S_MCB		ENDS

_DATA	segment

format		db ' %05lX           %7lu byte %04X',0
formatz		db '%8lu',0
format_9lu	db '%10lu',0
o_list		dw ?
dialog		dd ?
memsize		dw ?
device		dw ?
cp_free		db '--free--',0
cp_system	db '-system-',0

_DATA	ENDS

_DZIP	segment

normalize:
	push	cx
	mov	cl,dh
	shl	dx,4
	add	ax,dx
	adc	cl,0
	shr	cl,4
	mov	dl,cl
	mov	dh,0
	pop	cx
	ret

copyname:
	push	ds
	push	si
	push	di
	mov	si,ax
	mov	ax,WORD PTR [bx].S_LOBJ.ll_list+2
	mov	es,ax
	mov	ds,cx
	mov	cx,8
	add	di,cx
      @@:
	lodsb
	test	al,al
	jz	@F
	stosb
	loop	@B
      @@:
	pop	di
	pop	si
	pop	ds
	ret

add_block:
	xor	ax,ax		; DX: size
	push	cx		; CX: owner
	call	normalize	; SI: segment
	push	dx		; DI: buffer
	push	ax
	mov	dx,si
	xor	ax,ax
	call	normalize
	push	dx
	push	ax
	mov	bx,o_list
	mov	ax,WORD PTR [bx].S_LOBJ.ll_list+2
	invoke	sprintf,ax::di,addr format
	add	sp,10
	ret

next_block:
	add	di,LINESIZE
	mov	bx,o_list
	inc	[bx].S_LOBJ.ll_count
	cmp	[bx].S_LOBJ.ll_count,MAXLINES
	ret

readmem:
	push	si
	push	di
	push	bp
	int	12h
	shl	ax,6
	mov	memsize,ax
	mov	bx,o_list
	mov	[bx].S_LOBJ.ll_count,0
	mov	di,WORD PTR [bx].S_LOBJ.ll_list
	mov	ah,52h
	int	21h
	mov	si,es:[bx-2]	; segment of first memory control block
    readmem_loop:
	mov	es,si
	xor	bx,bx
	mov	cx,es:[bx].S_MCB.mcb_owner
	mov	dx,es:[bx].S_MCB.mcb_size
	call	add_block
	xor	bx,bx
	mov	ax,es:[bx].S_MCB.mcb_owner
	mov	bx,o_list
	mov	dx,WORD PTR [bx].S_LOBJ.ll_list+2
	dec	ax
	cmp	ax,si
	je	readmem_copy
	inc	ax
	jz	readmem_free
	cmp	ax,8
	je	readmem_device
	cmp	ax,6
	je	readmem_next
	cmp	ax,7
	je	readmem_next
	cmp	ax,0FFF7h
	jb	readmem_next
	mov	ax,offset cp_system
	mov	cx,ds
	call	copyname
	jmp	readmem_next
    readmem_free:
	mov	ax,offset cp_free
	mov	cx,ds
	call	copyname
	jmp	readmem_next
    readmem_device:
	xor	bx,bx
	mov	ax,si
	inc	ax
	cmp	ax,memsize
	jae	readmem_next2
	mov	device,ax
      @@:
	mov	ax,si
	mov	es,ax
	add	ax,es:[bx].S_MCB.mcb_size
	cmp	device,ax
	jae	readmem_next2
	mov	cx,8
	mov	es,device
	mov	dx,es:[bx].S_MCB.mcb_size
	mov	ax,es:[0]
	push	ax
	push	si
	mov	si,device
	call	add_block
	pop	si
	pop	ax
	.if al == 'T' || al == 'D' || al == 'Q'
	    mov ax,8
	    mov cx,device
	.else
	    mov ax,offset cp_system
	    mov cx,ds
	.endif
	call	copyname
	call	next_block
	je	readmem_end
	mov	ax,device
	mov	es,ax
	inc	ax
	xor	bx,bx
	add	ax,es:[bx].S_MCB.mcb_size
	mov	device,ax
	jmp	@B
    readmem_copy:
	mov	ax,8
	mov	cx,si
	call	copyname
    readmem_next:
	call	next_block
	je	readmem_end
    readmem_next2:
	mov	es,si
	xor	bx,bx
	add	si,es:[bx].S_MCB.mcb_size
	inc	si
	mov	es,si
	cmp	si,memsize
	jb	readmem_loop
    readmem_end:
	pop	bp
	pop	di
	pop	si
	ret

init_list:
	push	si
	push	di
	push	bp
	push	ds
	cld
	mov	cx,ID_COUNT
	mov	bx,o_list
	mov	[bx].S_LOBJ.ll_numcel,0
	mov	ax,LINESIZE
	mul	[bx].S_LOBJ.ll_index
	add	ax,WORD PTR [bx].S_LOBJ.ll_list
	mov	dx,WORD PTR [bx].S_LOBJ.ll_list+2
	mov	bp,bx
	les	di,dialog
	lea	di,[di+16].S_TOBJ.to_data	; &object[0].data
	mov	ds,dx			; DS:SI to list
	mov	si,ax
    event_list_loop:
	mov	ax,7F80h
	or	es:[di-7],al		; object.flag to unused
	cmp	BYTE PTR [si],0		; entry in use ?
	jz	event_list_next
	and	es:[di-7],ah
	inc	[bp].S_LOBJ.ll_numcel
    event_list_next:
	mov	ax,si			; store pointer
	stosw
	mov	ax,ds
	stosw
	add	di,12			; next object
	add	si,LINESIZE		; next info line
	dec	cx
	jnz	event_list_loop
	pop	ds
	pop	bp
	pop	di
	pop	si
	ret

mevent_list PROC _CType PRIVATE
	call	init_list
	invoke	dlinit,dialog
	mov	ax,_C_NORMAL
	retx
mevent_list ENDP

ifdef __MEMVIEW__
mevent_view PROC _CType PRIVATE
	mov	STDI.ios_flag,IO_MEMREAD
	mov	bx,o_list
	mov	ax,[bx].S_LOBJ.ll_celoff
	inc	al
	shl	ax,4
	les	bx,dialog
	add	bx,ax
	lodm	es:[bx].S_TOBJ.to_data
	inc	ax
	invoke	xtol,dx::ax
	shr	ax,4
	shl	dx,4
	or	ah,dl
	xor	dx,dx
	xchg	ax,dx
	mov	cx,15
	mov	bx,-1
	invoke	tview,0,dx::ax,0,cx::bx
	mov	STDI.ios_flag,0
	ret
mevent_view ENDP
endif

cmmemory PROC _CType PUBLIC
local	list:S_LOBJ
	push	si
	push	di
	lea	ax,list
	mov	o_list,ax
	invoke	malloc,LINESIZE * MAXLINES
	jz	cmmemory_ernomem
	stom	list.ll_list	; pointer to list buffer
	invoke	memzero,dx::ax,LINESIZE * MAXLINES
	invoke	rsopen,IDD_DZMemory
	jz	cmmemory_free
	stom	dialog
	invoke	dlshow,dx::ax
	movp	list.ll_proc,mevent_list
	xor	ax,ax
	mov	list.ll_dcount,ID_COUNT ; number of cells (max)
	mov	list.ll_celoff,ID_COUNT ; cell offset
	mov	list.ll_dlgoff,ax	; start index in dialog
	mov	list.ll_numcel,ax	; number of visible cells
	mov	list.ll_count,ax	; total number of items in list
	mov	list.ll_index,ax	; index in list buffer
	call	readmem
	call	mevent_list
	int	12h
	mov	dx,1024
	mul	dx
	mov	bx,WORD PTR IDD_DZMemory
	mov	bx,[bx+6]
	add	bx,0E04h
	mov	cl,bh
	invoke	scputf,bx,cx,0,0,addr formatz,dx::ax
	mov	dx,_psp
	add	dx,2
	xor	ax,ax
	call	normalize
	inc	cl
	invoke	scputf,bx,cx,0,0,addr formatz,dx::ax
	add	bh,2
	mov	di,bx
	.if emmversion()
	    mov ah,42h
	    int 67h
	  ifdef __3__
	    mov eax,4000h
	    movzx edx,dx
	    mul edx
	    mov dx,di
	    mov dl,dh
	    sub di,2
	    mov ecx,eax
	    invoke scputf,di,dx,0,0,addr format_9lu,eax
	    mov eax,4000h
	    movzx edx,bx
	    mul edx
	    sub ecx,eax
	    mov dx,di
	    mov dl,dh
	    inc dl
	    invoke scputf,di,dx,0,0,addr format_9lu,ecx
	  else
	    mov	    si,dx
	    mov	    ax,4000h
	    mul	    si		; total number of pages
	    push    dx
	    push    ax
	    mov	    ax,4000h
	    mul	    bx		; number of unallocated pages
	    pop	    bx
	    pop	    cx
	    sub	    bx,ax
	    sbb	    cx,dx
	    push    cx
	    push    bx
	    add	    ax,bx
	    adc	    dx,cx
	    mov	    bx,di
	    sub	    bl,2
	    mov	    cl,bh
	    invoke  scputf,bx,cx,0,0,addr format_9lu,dx::ax
	    inc	    cl
	    invoke  scputf,bx,cx,0,0,addr format_9lu
	    add	    sp,4
	  endif
	.endif
    cmmemory_event:
	invoke	dllevent,dialog,addr list
      ifdef __MEMVIEW__
	jz	cmmemory_close
	cmp	ax,ID_COUNT
	ja	cmmemory_close
	call	mevent_view
	jmp	cmmemory_event
      endif
    cmmemory_close:
	invoke	dlclose,dialog
    cmmemory_free:
	invoke	free,list.ll_list
    cmmemory_toend:
	pop	di
	pop	si
	ret
    cmmemory_ernomem:
	xor	ax,ax
	jmp	cmmemory_toend
cmmemory ENDP

_DZIP	ENDS

	END
