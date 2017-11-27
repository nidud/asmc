; DZEMM.ASM--
; Copyright (c) 2012 Doszip Developers
;
; Change history:
; 2012-12-12 - created
;

USECLIPBOARD	equ 1

	.186
	.model	tiny
	.code
	assume	ds:_TEXT

	dd	-1			; pointer to next driver
	dw	8000h			; device attributes
	dw	strategy		; device strategy entry point
	dw	interrupt		; device interrupt entry point
	db	'EMMXXXX0'		; device name

strategy:
	mov	cs:drvseg,es
	mov	cs:drvoff,bx
	retf

interrupt:
	pusha
	push	ds
	push	es
	lds	bx,cs:drvptr
	sub	ax,ax
	cmp	cs:drvset,al
	jne	interrupt_end
	inc	cs:drvset
	cmp	[bx+3],al
	je	initdevice
    interrupt_end:
	mov	word ptr [bx+3],100h
	pop	es
	pop	ds
	popa
	retf

ifdef USECLIPBOARD
int_2F: cmp	ah,17h
	je	new_2F
	db	0EAh		; opcode for jmp SSSS:0000
old_2F	dw	0
	dw	0
new_2F: mov	ah,90h		; Clipboard is 90xx
endif
int_67: push	bp
	mov	bp,ax
	db	0B8h
vdd_67	dw	0
	dw	0C4C4h
	db	58h,02h
	pop	bp
	iret

drvptr	label dword
drvoff	dw ?
drvseg	dw ?
drvset	db ?
vddname db 'dzemm.dll',0
vddinit db 'DZEmmInitVDD',0
vdddisp db 'DZEmmCallVDD',0

initdevice:
	push	ds
	push	bx
	mov	ax,cs
	mov	ds,ax
	mov	es,ax
	mov	si,offset vddname
	mov	di,offset vddinit
	mov	bx,offset vdddisp
	dw	0C4C4h
	db	58h,00h
	jc	initdevice_end
	mov	vdd_67,ax
	mov	vdd_in,ax
	mov	ah,41h		; steal memory from EMM ;-)
	int	67h
	test	ah,ah
	jnz	@F
	mov	dx,bx
	jmp	initdevice_seg
      @@:
	mov	ax,5800h	; alloc one segment from dos
	int	21h		; get alloc and UMB state
	mov	si,ax
	mov	ax,5802h
	int	21h
	mov	ah,0
	mov	di,ax
	mov	ax,5801h	; set alloc and UMB strategy
	mov	bx,0082h	; last fit, try high then low memory
	int	21h
	mov	ax,5803h	; add UMBs to DOS memory chain
	mov	bx,0001h
	int	21h
	xor	bp,bp
	mov	ah,48h		; alloc segment
	mov	bx,1000h	; para
	int	21h
	jc	@F
	mov	bp,ax
      @@:
	mov	ax,5801h	; reset alloc and UMB strategy
	mov	bx,si
	int	21h
	mov	ax,5803h
	mov	bx,di
	int	21h
	mov	dx,bp		; call dzemm.dll(dx)
	test	dx,dx
ifdef ARG_NOXMS
	jnz	initdevice_seg
	mov	dx,0D000h
else
	jz	initdevice_end
endif
    initdevice_seg:
	mov	bp,5E00h
	db	0B8h
vdd_in	dw	0
	dw	0C4C4h
	db	58h,02h
	test	ax,ax
	jz	initdevice_end
	mov	dx,offset int_67
	mov	ax,2567h
	int	21h
ifdef USECLIPBOARD
	mov	ax,352Fh	; get/set vector
	int	21h
	mov	old_2F,bx
	mov	old_2F[2],es
	mov	dx,offset int_2F
	mov	ax,252Fh
	int	21h
endif
    initdevice_end:
	pop	bx
	pop	ds
	mov	word ptr [bx+0Eh],offset device_end
	mov	word ptr [bx+10h],cs
	jmp	interrupt_end

device_end:

	end	initdevice
