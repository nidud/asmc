; TIHEVENT.ASM--
; Copyright (C) 2015 Doszip Developers

include clip.inc
include conio.inc
include tinfo.inc

tiseto		PROTO
tiputs		PROTO
tievent		PROTO
ifdef __CLIP__
ticlipevent	PROTO
endif

	.code

tihndlevent PROC _CType PUBLIC USES di ti:size_t, event:size_t
	mov  di,tinfo
	mov  ax,ti
	mov  tinfo,ax
	call tiseto
	call tiputs
	mov  ax,event
	.if !ax
	    call tgetevent
	    mov event,ax
	.endif
  ifdef __CLIP__
	call ticlipevent
  endif
	call tievent
	push ax
	call tiseto
	call tiputs
	pop  dx
	xor  ax,ax
	.if dx == _TI_RETEVENT
	    mov ax,event
	.endif
	mov tinfo,di
	ret
tihndlevent ENDP

	END
