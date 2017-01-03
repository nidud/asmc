; EMMREAD.ASM--
; Copyright (C) 2015 Doszip Developers
include alloc.inc
include string.inc

conventional	equ 0
expanded	equ 1
emmpage		equ 4000h

S_EMM		STRUC
dlength		dd ? ; region length in bytes
src_type	db ? ; source memory type
src_handle	dw ? ; 0000h if conventional memory
src_off		dw ? ; within page if EMS, segment if convent
src_seg		dw ? ; segment or logical page (EMS)
des_type	db ? ; destination memory type
des_handle	dw ? ;
des_off		dw ? ; in page
des_seg		dw ? ; or page
S_EMM		ENDS

	.code

emmread PROC _CType PUBLIC dest:DWORD, emhnd:size_t, wpage:size_t
local emm:S_EMM
	push	si
	mov	WORD PTR emm.dlength+2,0
	mov	WORD PTR emm.dlength,emmpage
	mov	emm.des_type,conventional
	mov	emm.des_handle,0
	mov	ax,WORD PTR dest
	mov	emm.des_off,ax
	mov	ax,WORD PTR dest+2
	mov	emm.des_seg,ax
	mov	emm.src_type,expanded
	mov	ax,emhnd
	mov	emm.src_handle,ax
	mov	emm.src_off,0
	mov	ax,wpage
	mov	emm.src_seg,ax
	mov	ax,5700h
	lea	si,emm
	int	67h
	mov	al,ah
	mov	ah,0
	pop	si
	ret
emmread ENDP

	END
