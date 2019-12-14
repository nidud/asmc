; DZEMMD.ASM--
; Copyright (C) 2012 Doszip Developers
;
; Doszip Expanded Memory Manager
;
; Change history:
; 2012-12-12 - created
; 2012-12-29 - fixed Alter Page Map & Call (Japheth)
; 2012-12-30 - added clipboard functions
; 2013-01-16 - fixed bug in Exchange Memory Region (5701h)
;
.386
.MODEL FLAT
option casemap:none

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

VERSION		equ	0106h
USEDOSZIP	equ	1
USECLIPBOARD	equ	1

;DEBUG		equ	1
;DEBUG_STATE	equ	1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

includelib kernel32.lib
includelib ntvdm.lib
ifdef USECLIPBOARD
includelib user32.lib
endif

; kernel32.dll

GMEM_FIXED	equ 0
GMEM_DDESHARE	equ 2000h
GMEM_MOVEABLE	equ 2h
GMEM_ZEROINIT	equ 40h

GlobalFree	proto stdcall :dword
GlobalAlloc	proto stdcall :dword, :dword
ifdef USECLIPBOARD
GlobalLock	proto stdcall :dword
GlobalUnlock	proto stdcall :dword
GlobalSize	proto stdcall :dword
GetLastError	proto stdcall

; user32.dll

OpenClipboard	proto stdcall :dword
CloseClipboard	proto stdcall
EmptyClipboard	proto stdcall
GetClipboardData proto stdcall :dword
SetClipboardData proto stdcall :dword, :dword

endif

; ntvdm.exe

getBX		proto stdcall
getCX		proto stdcall
getSI		proto stdcall
getBP		proto stdcall
getSP		proto stdcall
getDI		proto stdcall
getIP		proto stdcall
getES		proto stdcall
getDS		proto stdcall
getCS		proto stdcall
getSS		proto stdcall
getDX		proto stdcall
setAL		proto stdcall :dword
setAH		proto stdcall :dword
setAX		proto stdcall :dword
setBX		proto stdcall :dword
setCX		proto stdcall :dword
setDX		proto stdcall :dword
setSP		proto stdcall :dword
setCS		proto stdcall :dword
setIP		proto stdcall :dword
MGetVdmPointer	proto stdcall :dword, :dword, :dword
VDDSimulate16	proto stdcall

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EMMPAGES	equ	4
EMMPAGE		equ	4000h
MAXPAGES	equ	4000h
MAXHANDLES	equ	255
MAXMAPLEVEL	equ	8
EMMH_INUSE	equ	01h


S_HANDLE	STRUC
h_memp		dd ?
h_size		dd ?
h_name		db 8 dup(?)
S_HANDLE	ENDS

S_EMAP		STRUC
m_maph		dd EMMPAGES dup(?)
m_mapp		dd EMMPAGES dup(?)
S_EMAP		ENDS

SIZESAVEARRAY	equ	S_EMAP

	.data
	ALIGN		4
	reg_AX		dd ?
	reg_BX		dd ?
	reg_CX		dd ?
	reg_DX		dd ?
	reg_SI		dd ?
	reg_DI		dd ?
	emm_page	dd ?
	emm_label	dd ?
	emm_seg16	dd ?
	emm_seg32	dd ?
	emmh		S_HANDLE <0,0,<'SYSTEM'>>
	emmh1		S_HANDLE MAXHANDLES-1 dup(<?>)
	emm_flag	db MAXHANDLES+1 dup(?)
	emm_maplevel	dd ?
	emm_maph	dd EMMPAGES dup(?)
	emm_mapp	dd EMMPAGES dup(?)
	emm_tmph	dd EMMPAGES*2*MAXMAPLEVEL dup(?)
	emm_tmp0	dd MAXMAPLEVEL dup(?)

ifdef	DEBUG
	not_defined	dd 0
	dreg_AX		dd ?
	dreg_BX		dd ?
	dreg_CX		dd ?
	dreg_DX		dd ?
endif

ifdef USECLIPBOARD
	ClipboardIsOpen dd ?
endif

	.code

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	assume	edx:ptr S_HANDLE

emm_needhandle:
	.if	!edx || edx >= MAXHANDLES
		pop	eax
		jmp	emm_error_83
	.endif
	ret

emm_getesdi:
	push	edx
	push	eax
	invoke	getES
	shl	eax,16
	mov	ax,di
	pop	edx
	invoke	MGetVdmPointer,eax,edx,0
	mov	edi,eax
	pop	edx
	ret

emm_getdssi:
	push	edx
	push	eax
	invoke	getDS
	shl	eax,16
	mov	ax,si
	pop	edx
	invoke	MGetVdmPointer,eax,edx,0
	mov	esi,eax
	pop	edx
	ret

emm_gethandle:
	sub	eax,eax
	mov	edx,offset emmh1
	mov	ecx,1
      @@:
	cmp	emm_flag[ecx],al
	je	@F
	add	edx,S_HANDLE
	inc	ecx
	cmp	ecx,MAXHANDLES
	jb	@B
	ret
      @@:
	mov	eax,edx
	ret

;----------------------------------------------------------
; Allocate Pages
;----------------------------------------------------------

AllocatePages:
	push	ebx	; pages to allocate
	push	edx
	shl	ebx,14
	.if	GlobalAlloc(GMEM_FIXED,ebx)
		mov	ecx,ebx
	.endif
	pop	edx	; return EAX --> ECX size of buffer
	pop	ebx
	ret

;----------------------------------------------------------
; Map/Unmap Handle Page
; AL = physical_page_number
; BX = logical_page_number
; DX = emm_handle
;----------------------------------------------------------

; - copy bytes from frame segment to logical page

emm_copymap:
	push	edx
	mov	edx,ebx
	mov	ecx,EMMPAGE
      @@:
	repe	cmpsb
	je	@F
	mov	eax,ecx
	sub	eax,EMMPAGE
	not	eax
	add	eax,edx		; target offset in lg page
	mov	ebx,esi
	dec	ebx		; start source
	repne	cmpsb		; get size of string
	.if	ZERO?
		inc	ecx
		dec	edi
		dec	esi
	.endif
	push	ecx
	mov	ecx,esi
	sub	ecx,ebx
	xchg	eax,edi
	xchg	ebx,esi
	rep	movsb
	pop	ecx
	mov	edi,eax
	mov	esi,ebx
	test	ecx,ecx
	jnz	@B
      @@:
	pop	edx
	ret

emm_pushmap:
	push	eax
	push	edx
	push	esi
	push	edi
	push	ebx
	sub	edx,edx
	mov	edi,emmh.h_memp
	mov	esi,emm_seg32
	.repeat
		.if	emm_maph[edx]
			mov	ebx,emm_mapp[edx]
			call	emm_copymap
		.else
			add	esi,EMMPAGE
			add	edi,EMMPAGE
		.endif
		add	edx,4
	.until	edx == SIZESAVEARRAY/2
	pop	ebx
	pop	edi
	pop	esi
	pop	edx
	pop	eax
	ret

emm_mappage:
	movzx	eax,al
	mov	emm_page,eax
	.if	al >= EMMPAGES
		mov	ah,8Bh
		ret
	.endif
	.if	!edx && bx != -1
		mov	ah,8Ah
		ret
	.endif
	.if	bx == -1
		jmp	emm_unmappage
	.endif
	.if	edx >= MAXHANDLES
		mov	ah,8Ah
		ret
	.endif
	shl	eax,14			; EDI to frame segment
	mov	edi,emm_seg32
	add	edi,eax
	shl	edx,4			; EDX to handle
	add	edx,offset emmh
	mov	esi,[edx].h_memp		; ESI to logical page
	.if	esi
		mov	ecx,esi
		add	ecx,[edx].h_size
		mov	eax,ebx
		shl	eax,14
		add	esi,eax
		mov	eax,esi
		add	eax,EMMPAGE
		.if	ecx < eax
			mov	ah,8Ah
		.else
			sub	eax,eax
		.endif
	.else
		mov	ah,8Ah
	.endif
	.if	ah
		ret
	.endif
	call	emm_pushmap
	mov	ebx,emm_page
	shl	ebx,2
	mov	emm_maph[ebx],edx
	mov	emm_mapp[ebx],esi
	mov	ecx,EMMPAGE/4
	rep	movsd
	mov	esi,emm_mapp[ebx]	; extra copy needed for compare..
	shl	ebx,12
	mov	edi,emmh.h_memp
	add	edi,ebx
	mov	ecx,EMMPAGE/4
	rep	movsd
	sub	eax,eax
	ret

emm_unmappage:
	mov	ebx,eax
	shl	ebx,2
	sub	eax,eax
	mov	edx,emm_maph[ebx]
	mov	emm_maph[ebx],eax		; - unmap page
	.if	edx && [edx].h_memp != eax
		mov	esi,emm_seg32
		mov	edi,emm_mapp[ebx]
		.if	esi && edi
			mov	ecx,ebx
			shl	ecx,12
			add	esi,ecx		; copy the frame to buffer
			mov	edx,edi		; save logical page address
			mov	ebx,emmh.h_memp
			add	ebx,ecx
			xchg	ebx,edi
			call	emm_copymap
			sub	eax,eax
			mov	ebx,emm_seg32
			.repeat			; find dublicate address
				.if	emm_maph[eax]
					.if	edx == emm_mapp[eax]
						mov	edi,ebx
						mov	esi,edx
						mov	ecx,EMMPAGE/4
						rep	movsd
					.endif
				.endif
				add	eax,4
				add	ebx,EMMPAGE
			.until	eax == SIZESAVEARRAY/2
		.endif
	.endif
	sub	eax,eax
	ret

emm_updatemap:
	push	edi
	push	ecx
	push	eax
	sub	eax,eax
	mov	ecx,EMMPAGES
	mov	edi,offset emm_maph
	.repeat
		mov	edx,[edi]
		.if	edx && [edx].h_memp == eax
			mov	[edi],eax
		.endif
		add	edi,4
	.untilcxz
	pop	eax
	pop	ecx
	pop	edi
	ret

emm_popmap:
	push	eax
	push	ecx
	push	ebx
	push	edi
	push	esi
	sub	eax,eax
	mov	ebx,eax
	mov	ebx,emm_seg32
	.if	ebx
		.repeat
			.if	emm_maph[eax]
				mov	esi,emm_mapp[eax]
				mov	edi,ebx
				mov	ecx,EMMPAGE/4
				rep	movsd
			.endif
			add	eax,4
			add	ebx,EMMPAGE
		.until	eax == SIZESAVEARRAY/2
	.endif
	pop	esi
	pop	edi
	pop	ebx
	pop	ecx
	pop	eax
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;----------------------------------------------------------
emm_01: ; Get Status					40h
;----------------------------------------------------------
ifdef	DEBUG
	mov	dreg_AX,eax
	mov	dreg_BX,ebx
	mov	dreg_CX,ecx
	mov	dreg_DX,edx
 ifdef	DEBUG_STATE
	jmp	emm_not_defined
 endif
endif
	invoke	setAX,1 ; Signature: 0001
	ret

;----------------------------------------------------------
emm_02: ; Get Page Frame Segment Address		41h
;----------------------------------------------------------
	.if	emm_seg16
		invoke	setBX,emm_seg16
		jmp	emm_success
	.endif
	jmp	emm_error_84

;----------------------------------------------------------
emm_03: ; Get Unallocated Page Count			42h
;----------------------------------------------------------
	xor	ebx,ebx
	mov	ecx,MAXHANDLES-1
	mov	edx,offset emmh1
	.repeat
		.if	[edx].h_memp
			mov	eax,[edx].h_size
			shr	eax,14
			add	ebx,eax
		.endif
		add	edx,S_HANDLE
	.untilcxz
	mov	eax,MAXPAGES
	.if	ebx > eax
		;mov	eax,MAXPAGES
		sub	eax,eax
	.else
		sub	eax,ebx
	.endif
	invoke	setBX,eax	; unallocated pages
	invoke	setDX,MAXPAGES	; total pages
	jmp	emm_success

;----------------------------------------------------------
emm_04: ; Allocate Pages				43h
;----------------------------------------------------------
	.if	!ebx
		jmp	emm_error_89
	.endif

;----------------------------------------------------------
emm_27: ; Allocate Standard Pages		      5A00h
	; Allocate Raw Pages			      5A01h
	;
	; BX = num_of_pages_to_alloc
	;
;----------------------------------------------------------
	.if	emm_gethandle()
		mov	emm_flag[ecx],EMMH_INUSE
		.if	!ebx
			invoke	setDX,ecx
			jmp	emm_success
		.endif
		mov	edi,eax
		mov	esi,ecx
		call	emm_pushmap
		.if	AllocatePages()
			mov	[edx].h_memp,eax
			mov	[edx].h_size,ecx
			invoke	setDX,esi
			jmp	emm_success
		.endif
		jmp	emm_error_87
	.endif
	jmp	emm_error_85

;----------------------------------------------------------
emm_05: ; Map/Unmap Handle Page				44h
	; AL = physical_page_number
	; BX = logical_page_number
	; DX = emm_handle
;----------------------------------------------------------
	.if	emm_mappage()
		jmp	emm_setAX
	.endif
	jmp	emm_success

;----------------------------------------------------------
emm_06: ; Deallocate Pages				45h
;----------------------------------------------------------
	.if	!edx
		jmp	emm_success
	.endif
	.if	edx < MAXHANDLES
		mov	emm_flag[edx],0
		shl	edx,4
		add	edx,offset emmh
		mov	edi,edx
		.if	[edx].h_memp
			invoke	GlobalFree,[edx].h_memp
		.endif
		mov	edx,edi
		sub	eax,eax
		mov	[edx].h_memp,eax
		mov	[edx].h_size,eax
		mov	edi,eax
		mov	ecx,EMMPAGES
		.repeat
			.if	emm_maph[edi] == edx
				mov	emm_maph[edi],eax
			.endif
			add	edi,4
		.untilcxz
		mov	[edx+8],eax
		mov	[edx+12],eax
		jmp	emm_success
	.endif
	jmp	emm_error_83

;----------------------------------------------------------
emm_07: ; Get Version					46h
;----------------------------------------------------------
	invoke	setAX,0040h
	ret

;----------------------------------------------------------
emm_08: ; Save Page Map					47h
;----------------------------------------------------------
	cmp	emm_maplevel,MAXMAPLEVEL-1
	jae	@F
	inc	emm_maplevel
	call	emm_pushmap
	mov	esi,offset emm_maph
	mov	edi,offset emm_tmph
	mov	ecx,S_EMAP * MAXMAPLEVEL - 1
	add	esi,ecx
	add	edi,ecx
	inc	ecx
	std
	rep	movsb
	cld
	.if	GlobalAlloc(GMEM_FIXED,EMMPAGES*EMMPAGE*2)
		mov	edi,eax
		mov	eax,emm_maplevel
		dec	eax
		shl	eax,2
		mov	emm_tmp0[eax],edi
		mov	esi,emmh.h_memp
		mov	ecx,(EMMPAGES*EMMPAGE)/4
		rep	movsd
		mov	esi,emm_seg32
		mov	ecx,(EMMPAGES*EMMPAGE)/4
		rep	movsd
	.endif
	jmp	emm_success
      @@:
	jmp	emm_error_8C

;----------------------------------------------------------
emm_09: ; Restore Page Map				48h
;----------------------------------------------------------
	cmp	emm_maplevel,0
	je	@B
	call	emm_pushmap
	dec	emm_maplevel
	mov	edi,offset emm_maph
	mov	esi,offset emm_tmph
	mov	ecx,S_EMAP * MAXMAPLEVEL
	rep	movsb
	mov	eax,emm_maplevel
	shl	eax,2
	mov	esi,emm_tmp0[eax]
	mov	emm_tmp0[eax],0
	.if	esi
		mov	ebx,esi
		mov	edi,emmh.h_memp
		mov	ecx,(EMMPAGES*EMMPAGE)/4
		rep	movsd
		mov	edi,emm_seg32
		mov	ecx,(EMMPAGES*EMMPAGE)/4
		rep	movsd
		invoke	GlobalFree,ebx
	.endif
	call	emm_updatemap
	call	emm_popmap
	jmp	emm_success

;----------------------------------------------------------
emm_10: ; Reserved 49h
emm_11: ; Reserved 4Ah
	jmp	emm_error_84

;----------------------------------------------------------
emm_12: ; Get Handle Count				4Bh
;----------------------------------------------------------
	mov	eax,1
	mov	ecx,MAXHANDLES-1
	mov	edx,offset emmh1
	.repeat
		.if	[edx].h_memp
			inc	eax
		.endif
		add	edx,S_HANDLE
	.untilcxz
	invoke	setBX,eax
	jmp	emm_success

;----------------------------------------------------------
emm_13: ; Get Handle Pages				4Ch
;----------------------------------------------------------
	.if	edx >= MAXHANDLES
		jmp	emm_error_83
	.endif
	shl	edx,4
	add	edx,offset emmh
	mov	eax,[edx].h_size
	shr	eax,14
	invoke	setBX,eax
	jmp	emm_success

;----------------------------------------------------------
emm_14: ; Get All Handle Pages				4Dh
;
;	  handle_page_struct	 STRUC
;	     emm_handle		     DW ?
;	     pages_alloc_to_handle   DW ?
;	  handle_page_struct	 ENDS
;
;	  ES:DI = pointer to handle_page
;----------------------------------------------------------
	mov	eax,4*MAXHANDLES
	call	emm_getesdi
	sub	ebx,ebx
	sub	esi,esi
	mov	ecx,MAXHANDLES
	mov	edx,offset emmh
	.repeat
		.if	[edx].h_memp
			mov	eax,[edx].h_size
			shl	eax,2
			mov	ax,si
			stosd
			inc	ebx
		.endif
		inc	esi
		add	edx,S_HANDLE
	.untilcxz
	invoke	setBX,ebx
	jmp	emm_success

;----------------------------------------------------------
emm_15: ; Get Page Map				      4E00h
;	  ES:DI = dest_page_map
;----------------------------------------------------------
	test	al,al
	jnz	emm_1501
	mov	eax,SIZESAVEARRAY
	call	emm_getesdi
	mov	esi,offset emm_maph
	mov	ecx,SIZESAVEARRAY
	rep	movsb
	jmp	emm_success

;----------------------------------------------------------
emm_1501:; Set Page Map				      4E01h
;	  DS:SI = source_page_map
;----------------------------------------------------------
	cmp	al,1
	jne	emm_1502
emm_150102:
	mov	eax,SIZESAVEARRAY
	call	emm_getdssi
	call	emm_pushmap
	mov	edi,offset emm_maph
	mov	ecx,SIZESAVEARRAY
	rep	movsb
	call	emm_updatemap
	call	emm_popmap
	jmp	emm_success

;----------------------------------------------------------
emm_1502:; Get & Set Page Map			      4E02h
;----------------------------------------------------------
	cmp	al,2
	jne	emm_1503
	mov	eax,SIZESAVEARRAY
	call	emm_getesdi
	push	esi
	mov	esi,offset emm_maph
	mov	ecx,SIZESAVEARRAY
	rep	movsb
	pop	esi
	jmp	emm_150102

;----------------------------------------------------------
emm_1503:; Get Size of Page Map Save Array	      4E03h
;----------------------------------------------------------
	invoke	setAX,SIZESAVEARRAY
	ret

;----------------------------------------------------------
emm_16: ; Get Partial Page Map			      4F00h
	;
	;  partial_page_map_struct     STRUC
	;     mappable_segment_count   DW  ?
	;     mappable_segment	 DW  (?) DUP (?)
	;  partial_page_map_struct     ENDS
	;
	;  DS:SI = partial_page_map
	;  ES:DI = dest_array
	;   pointer to the destination array address in
	;   Segment:Offset format.
;----------------------------------------------------------
	test	al,al
	jnz	emm_1601
	mov	eax,EMMPAGES*4
	call	emm_getesdi
	mov	eax,emm_seg16
	movzx	ecx,word ptr [edi]
	add	edi,2
      @@:
	stosw
	add	eax,EMMPAGE/16
	dec	ecx
	jnz	@B
	jmp	emm_success

;----------------------------------------------------------
emm_1601:; Set Partial Page Map			      4F01h
	; DS:SI = source_array
;----------------------------------------------------------
	cmp	al,1
	je	emm_150102

;----------------------------------------------------------
emm_1602:; Get Size of Partial Page Map Save Array    4F02h
;----------------------------------------------------------
	jmp	emm_1503

;----------------------------------------------------------
emm_17: ; Map/Unmap Multiple Handle Pages (Physical)  5000h
	;
	; log_to_phys_map_struct   STRUC
	;     log_page_number	   DW  ?
	;     phys_page_number	   DW  ?
	;  log_to_phys_map_struct  ENDS
	;
	;  DS:SI = pointer to log_to_phys_map array
	;  DX = handle
	;  CX = log_to_phys_map_len
;----------------------------------------------------------
	.if	!ecx || edx >= MAXHANDLES
		jmp	emm_error_8F
	.endif
	push	eax
	push	ecx
	mov	eax,ecx
	shl	eax,2
	call	emm_getdssi
	pop	ecx
	pop	eax
	test	al,al
	jnz	emm_1701
	.repeat
		push	esi
		push	ecx
		push	edx
		movzx	ebx,word ptr [esi]
		mov	al,[esi+2]
		call	emm_mappage
		pop	edx
		pop	ecx
		pop	esi
		.if	eax
			jmp	emm_setAX
		.endif
		add	esi,4
	.untilcxz
	jmp	emm_success

;----------------------------------------------------------
emm_1701:; Map/Unmap Multiple Handle Pages (Segment)  5001h
	;
	;  log_to_seg_map_struct	STRUC
	;     log_page_number		DW  ?
	;     mappable_segment_address	DW  ?
	;  log_to_seg_map_struct	ENDS
	;
	;  DX = handle
	;  CX = log_to_segment_map_len
	;  DS:SI = pointer to log_to_segment_map array
;----------------------------------------------------------
	.repeat
		push	esi
		push	ecx
		push	edx
		movzx	ebx,word ptr [esi]
		movzx	eax,word ptr [esi+2]
		sub	eax,emm_seg16
		shr	eax,10
		call	emm_mappage
		pop	edx
		pop	ecx
		pop	esi
		.if	eax
			jmp emm_setAX
		.endif
		add	esi,4
	.untilcxz
	jmp	emm_success

;----------------------------------------------------------
emm_18: ; Reallocate Pages				51h
	; DX = handle
	; BX = number of pages to be allocated to handle
	; return:
	; BX = actual number of pages allocated to handle
;----------------------------------------------------------
	;
	; No realloc of handle 0 !!
	;
	call	emm_needhandle
	call	emm_pushmap
	shl	edx,4
	add	edx,offset emmh
	.if	AllocatePages()
		mov	edi,eax		; pointer
		mov	ebx,ecx		; new size
		mov	esi,[edx].h_memp
		.if	esi
			;
			; Copy content from old buffer
			;
			mov	ecx,[edx].h_size
			.if	ecx > ebx
				mov ecx,ebx
			.endif
			rep	movsb
			mov	edi,eax
			mov	esi,edx
			invoke	GlobalFree,[edx].h_memp
			mov	edx,esi
		.endif
		;
		; Reset mapping table
		;
		sub	esi,esi
		mov	ecx,EMMPAGES
		.repeat
			.if	emm_maph[esi] == edx
				mov eax,emm_mapp[esi]
				sub eax,[edx].h_memp
				add eax,EMMPAGE
				.if	eax <= ebx
					sub eax,EMMPAGE
					add eax,edi
					mov emm_mapp[esi],eax
				.else
					sub eax,eax
					mov emm_maph[esi],eax
					;
					; @@ TODO !!
					;
				.endif
			.endif
			add	esi,4
		.untilcxz
		mov	[edx].h_memp,edi
		mov	[edx].h_size,ebx
		shr	ebx,14
		invoke	setBX,ebx
		jmp	emm_success
	.endif
	mov	[esi+8],eax
	mov	[esi+12],eax
	jmp	emm_error_87 ; There aren't enough expanded memory pages

;----------------------------------------------------------
emm_19: ; Get Handle Attribute			      5200h
;----------------------------------------------------------
	.if	edx >= MAXHANDLES
		jmp emm_error_83
	.endif
	.if	al == 2 || al == 0
		invoke	setAX,0 ; only volatile handles supported
		ret
	.endif
	jmp	emm_error_91

;----------------------------------------------------------
emm_20: ; Get Handle Name			      5300h
;	  DX = handle number
;	  ES:DI = pointer to handle_name array
;----------------------------------------------------------
	.if	edx >= MAXHANDLES
		jmp emm_error_83
	.endif
	cmp	al,00h
	jne	emm_2001
	mov	eax,8
	call	emm_getesdi
	shl	edx,4
	add	edx,offset emmh
	mov	eax,[edx+8]
	mov	[edi],eax
	mov	eax,[edx+12]
	mov	[edi+4],eax
	jmp	emm_success

;----------------------------------------------------------
emm_2001:; Set Handle Name			      5301h
;----------------------------------------------------------
	mov	eax,8
	call	emm_getdssi
	shl	edx,4
	add	edx,offset emmh
	mov	eax,[esi]
	mov	[edx+8],eax
	mov	eax,[esi+4]
	mov	[edx+12],eax
	jmp	emm_success

;----------------------------------------------------------
emm_21: ; Get Handle Directory				54h
;	  handle_dir_struct   STRUC
;	     handle_value     DW  ?
;	     handle_name      DB  8  DUP  (?)
;	  handle_dir_struct   ENDS
;
;	  ES:DI = pointer to handle_dir
;----------------------------------------------------------
	cmp	al,0
	jne	emm_2101
	mov	eax,10*MAXHANDLES
	call	emm_getesdi
	sub	ebx,ebx
	mov	ecx,MAXHANDLES
	mov	edx,offset emmh
	.repeat
		.if [edx].h_memp
			mov eax,ebx
			stosw
			mov eax,[edx+8]
			stosd
			mov eax,[edx+12]
			stosd
			inc ebx
		.endif
		add	edx,S_HANDLE
	.untilcxz
	invoke	setAX,ebx
	ret

;----------------------------------------------------------
emm_2101:; Search for Named Handle		      5401h
;----------------------------------------------------------
	cmp	al,1
	jne	emm_2102
	mov	eax,8
	call	emm_getdssi
	mov	eax,[esi]
	mov	edx,[esi+4]
	sub	ebx,ebx
	mov	edi,ebx
	mov	esi,offset emmh + 8
	.repeat
		.if	[esi] == eax && [esi+4] == edx
			sub esi,8
			mov ebx,esi
			.break
		.endif
		inc	edi
		add	esi,S_HANDLE
	.until	edi == MAXHANDLES
	.if	ebx
		.if !eax && !edx
			jmp	emm_error_A1
		.else
			invoke	setDX,edi
			jmp	emm_success
		.endif
	.else
		jmp	emm_error_A0
	.endif
	ret

;----------------------------------------------------------
emm_2102:; Get Total Handles			      5402h
;----------------------------------------------------------
	invoke	setBX,MAXHANDLES
	jmp	emm_success

;----------------------------------------------------------
emm_22: ; Alter Page Map & Jump (Physical page mode)  5500h
;----------------------------------------------------------
emm_2201:; Alter Page Map & Jump (Segment mode)	      5501h
;----------------------------------------------------------
	;
	;  log_phys_map_struct	     STRUC
	;     log_page_number	DW ?
	;     phys_page_number_seg   DW ?
	;  log_phys_map_struct	     ENDS
	;
	;  map_and_jump_struct	     STRUC
	;    target_address	     DD ?
	;    log_phys_map_len	DB ?
	;    log_phys_map_ptr	DD ?
	;  map_and_jump_struct	     ENDS
	;
	; AL = physical page number/segment selector
	;  0 = physical page numbers
	;  1 = segment address
	;
	; DX = handle number
	;
	; DS:SI = pointer to map_and_jump structure
	;
;----------------------------------------------------------
	.if	al > 1
		jmp emm_error_8F
	.endif
	push	eax
	mov	eax,9
	call	emm_getdssi
	movzx	ecx,byte ptr [esi+4]
	pop	eax
	mov	ah,50h
	push	esi
	mov	esi,[esi+5]
	call	emm_17
	pop	esi
	test	ah,ah
	jz	@F
	jmp	emm_setAX
      @@:
	mov	eax,[esi]
	shr	eax,16
	invoke	setCS,eax
	mov	eax,[esi]
	and	eax,0FFFEh
	invoke	setIP,eax
	jmp	emm_success

;----------------------------------------------------------
; Alter Page Map & Call (Physical page mode)	      5600h
; Alter Page Map & Call (Segment mode)		      5601h
;----------------------------------------------------------
	;
	;  log_phys_map_struct	     STRUC
	;     log_page_number	DW ?
	;     phys_page_number_seg   DW ?
	;  log_phys_map_struct	     ENDS
	;
	;  map_and_call_struct	     STRUC
	;     target_address	 DD ?
	;     new_page_map_len	     DB ?
	;     new_page_map_ptr	     DD ?
	;     old_page_map_len	     DB ?
	;     old_page_map_ptr	     DD ?
	;     reserved		     DW	 4 DUP (?)
	;  map_and_call_struct	     ENDS
	;
	;  AL = physical page number/segment selector
	;
	;  DX = handle number
	;
	;  DS:SI = pointer to map_and_call structure
	;
;----------------------------------------------------------

	.data

; -- from jemm/ems.asm --

;--- this is 16-bit code which is copied onto the client's stack
;--- to restore the page mapping in int 67h, ah=56h

;--- rewritten by Japheth 2012-12-29

VDDUnsimulate16 macro
db 0C4h, 0C4h, 0FEh
endm

clproc label byte
	db 9Ah
clp	dd 0
	VDDUnsimulate16
sizeclproc equ $ - offset clproc


	.code

emm_23:
	cmp	al,1
	ja	emm_2302
	mov	eax,22
	call	emm_getdssi
	push	esi
	movzx	ecx,byte ptr [esi+4]	; .new_page_map_len
	mov	esi,[esi+5]		; .new_page_map_ptr
	mov	eax,reg_AX		; AL: 0 or 1
	call	emm_17
	pop	esi
	test	ah,ah
	jz	@F
	jmp	emm_setAX
      @@:

;--- save client's CS:IP
	invoke	getCS			; Get CS:IP
	push	eax
	invoke	getIP
	push	eax

;--- adjust code that will be copied onto client's stack
	mov	ebx,[esi]		; .target_address
	mov	clp,ebx

;--- get client's SS:SP
	invoke	getSS
	mov	ebx, eax
	movzx	eax,ax
	shl	eax,4
	mov	edi,eax
	invoke	getSP
	push	eax	;save client's SP
	movzx	eax, ax

;--- reserve space for helper code on client's stack (8 bytes)
	sub	eax, sizeclproc
	add	edi, eax

;--- set client's new SP and CS:IP
	push	eax
	invoke	setSP, eax
	pop	eax
	invoke	setIP, eax
	invoke	setCS, ebx

;--- copy helper code onto client stack
;--- it's just 2 lines: call far16 client_proc + VDDUnsimulate()
	push	esi
	mov	ecx,sizeclproc		; copy function to stack
	mov	esi,offset clproc
	rep	movsb
	pop	esi

;--- run helper code
	call	VDDSimulate16

;--- restore client's SP and CS:IP
	pop	eax
	invoke	setSP, eax
	pop	eax
	invoke	setIP, eax
	pop	eax
	invoke	setCS, eax

;--- set old mapping
	movzx	ecx,byte ptr [esi+9]	; .old_page_map_len
	mov	esi,[esi+10]		; .old_page_map_ptr
	mov	eax,reg_AX		; AL: 0 or 1
	mov	edx,reg_DX		; restore handle
	call	emm_17
	jmp	emm_success

;----------------------------------------------------------
emm_2302:; Get Page Map Stack Space Size	      5602h
;----------------------------------------------------------
	.if	al != 2
		jmp emm_error_8F
	.endif
	invoke	setBX,sizeclproc+4
	jmp	emm_success

;----------------------------------------------------------
emm_24: ; Move Memory Region				57h
	; DS:SI = pointer to exchange_source_dest structure
;----------------------------------------------------------

conventional	equ 0
expanded	equ 1

S_EMM		STRUC
dlength		dd ? ; region length in bytes
src_type	db ? ; source memory type
src_handle	dw ? ; 0000h if conventional memory
src_offset	dw ? ; within page if EMS
src_seg_page	dw ? ; segment or logical page (EMS)
des_type	db ? ; destination memory type
des_handle	dw ? ;
des_offset	dw ? ;
des_seg_page	dw ? ;
S_EMM		ENDS

;	call	emm_pushmap
	mov	eax,S_EMM
	call	emm_getdssi
	mov	ebx,esi

	.if	[ebx].S_EMM.src_type == conventional
		mov	ax,[ebx].S_EMM.src_seg_page
		shl	eax,16
		mov	ax,[ebx].S_EMM.src_offset
		invoke	MGetVdmPointer,eax,[ebx].S_EMM.dlength,0
		mov	esi,eax
	.else
		movzx	eax,[ebx].S_EMM.src_seg_page
		movzx	edx,[ebx].S_EMM.src_handle
		cmp	edx,MAXHANDLES
		jae	emm_24_8F		; out of range..
		shl	edx,4
		add	edx,offset emmh
		mov	esi,[edx].h_memp
		test	esi,esi
		jz	emm_24_93		; out of range..
		mov	edx,[edx].h_size
		add	edx,esi		; limit
		shl	eax,14		; page * size of page (4000h)
		add	esi,eax		; ESI to page adress in buffer
		movzx	eax,[ebx].S_EMM.src_offset
		add	esi,eax
		mov	eax,esi
		add	eax,[ebx].S_EMM.dlength
		cmp	eax,edx
		ja	emm_24_93		; out of range..
	.endif
	.if	[ebx].S_EMM.des_type == conventional
		mov	ax,[ebx].S_EMM.des_seg_page
		shl	eax,16
		mov	ax,[ebx].S_EMM.des_offset
		invoke	MGetVdmPointer,eax,[ebx].S_EMM.dlength,0
		mov	edi,eax
	.else
		movzx	eax,[ebx].S_EMM.des_seg_page
		movzx	edx,[ebx].S_EMM.des_handle
		cmp	edx,MAXHANDLES
		jae	emm_24_8F	; out of range..
		shl	edx,4
		add	edx,offset emmh
		mov	edi,[edx].h_memp
		test	edi,edi
		jz	emm_24_93	; out of range..
		mov	edx,[edx].h_size
		add	edx,edi		; limit
		shl	eax,14		; page * size of page (4000h)
		add	edi,eax		; EDI to page adress in buffer
		movzx	eax,[ebx].S_EMM.des_offset
		add	edi,eax
		mov	eax,edi
		add	eax,[ebx].S_EMM.dlength
		cmp	eax,edx
		ja	emm_24_93	; out of range..
	.endif
	mov	ecx,[ebx].S_EMM.dlength
	cmp	byte ptr reg_AX,01h
	je	emm_2401
	cmp	edi,esi
	ja	emm_24_move
	rep	movsb
	jmp	emm_success
    emm_24_move:
	std
	add	esi,ecx
	add	edi,ecx
	sub	esi,1
	sub	edi,1
	rep	movsb
	cld
	jmp	emm_success

    emm_24_8F:
	jmp emm_error_8F ; The subfunction parameter is invalid
    emm_24_93:
	jmp emm_error_93 ; The length expands memory region specified

;----------------------------------------------------------
emm_2401:; Exchange Memory Region		      5701h
;----------------------------------------------------------
	mov	al,[edi]
	movsb
	mov	[esi-1],al
	dec	ecx
	jnz	emm_2401
	jmp	emm_success

;----------------------------------------------------------
emm_25: ; Get Mappable Physical Address Array	      5800h
;----------------------------------------------------------
	cmp	al,1
	je	emm_2501
;
;	  mappable_phys_page_struct   STRUC
;	     phys_page_segment	DW ?
;	     phys_page_number	 DW ?
;	  mappable_phys_page_struct   ENDS
;
;	  ES:DI = mappable_phys_page
;
	mov	eax,EMMPAGES*4
	call	emm_getesdi
	sub	ecx,ecx
	mov	eax,emm_seg16
      @@:
	mov	[edi],ax
	mov	[edi+2],cx
	add	eax,EMMPAGE/16
	add	edi,4
	inc	ecx
	cmp	ecx,EMMPAGES
	jne	@B

;------------------------------------------------------------------
emm_2501:; Get Mappable Physical Address Array Entries	      5801h
;------------------------------------------------------------------
	invoke	setCX,EMMPAGES
	jmp	emm_success

;------------------------------------------------------------------
emm_26: ; Get Hardware Configuration Array		      5900h
;
;	  hardware_info_struct	 STRUC
;	     raw_page_size	     DW ?
;	     alternate_register_sets   DW ?
;	     context_save_area_size    DW ?
;	     DMA_register_sets	 DW ?
;	     DMA_channel_operation     DW ?
;	  hardware_info_struct	 ENDS
;
;------------------------------------------------------------------
	cmp	al,1
	je	emm_2601
	mov	eax,10
	call	emm_getesdi
	sub	eax,eax
	mov	word ptr [edi],EMMPAGE/16
	mov	[edi+2],ax
	mov	word ptr [edi+4],SIZESAVEARRAY
	mov	[edi+6],eax
	jmp	emm_success

;------------------------------------------------------------------
emm_2601: ; Get Unallocated Raw Page Count		      5901h
;------------------------------------------------------------------
	jmp	emm_03

emm_28:		; Get Alternate Map Register Set 5B00h
emm_2801:	; Set Alternate Map Register Set 5B01h
emm_2802:	; Get Alternate Map Save Array Size 5B02h
emm_2803:	; Allocate Alternate Map Register Set 5B03h
emm_2804:	; Deallocate Alternate Map Register Set 5B04h
emm_2805:	; Allocate DMA Register Set 5B05h
emm_2806:	; Enable DMA on Alternate Map Register Set 5B06h
emm_2807:	; Disable DMA on Alternate Map Register Set 5B07h
emm_2808:	; Deallocate DMA Register Set 5B08h
emm_29:		; Prepare Expanded Memory Hardware for Warmboot 5Ch
emm_30:		; Enable OS/E Function Set 5D00h
emm_3001:	; Disable OS/E Function Set 5D01h
emm_3002:	; Return OS/E Access Key 5D02h
	jmp	emm_error_84

;----------------------------------------------------------
emm_31: ; Called from dzemm.com on init			5Eh
;----------------------------------------------------------

	.if	emm_seg16
		jmp emm_error_84
	.endif

	mov	emm_seg16,edx
	.if	edx
		shl	edx,16
		invoke	MGetVdmPointer,edx,EMMPAGES*EMMPAGE,0
		mov	emm_seg32,eax
		mov	ebx,EMMPAGES
		.if	AllocatePages()
			mov emmh.h_memp,eax
			mov emmh.h_size,ecx
			invoke setAX,1
		.endif
	.endif
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

emm_success:
	sub	ah,ah
emm_setAX:
	mov	al,byte ptr reg_AX
	push	eax
	invoke	setAX,eax
	pop	eax
	ret

emm_error_83:
	mov	ah,83h	; No EMM handle
	jmp	emm_setAX
emm_error_84:
	mov	ah,84h
ifdef DEBUG
	mov	not_defined,eax
endif
	jmp	emm_setAX
emm_error_85:
	mov	ah,85h	; All EMM handles are being used
	jmp	emm_setAX
emm_error_87:
	mov	ah,87h	; There aren't enough expanded memory pages
	jmp	emm_setAX
emm_error_89:
	mov	ah,89h	; Attempted to allocate zero pages
	jmp	emm_setAX
emm_error_8A:
	mov	ah,8Ah	; The logical page is out of the range of logical pages
	jmp	emm_setAX
emm_error_8C:
	mov	ah,8Ch	; There is no room to store the page mapping registers.
	jmp	emm_setAX
emm_error_8F:
	mov	ah,8Fh	; The subfunction parameter is invalid.
	jmp	emm_setAX
emm_error_91:
	mov	ah,91h	; This feature is not supported.
	jmp	emm_setAX
emm_error_93:
	mov	ah,93h	; The length expands memory region specified
	jmp	emm_setAX
emm_error_A0:
	mov	ah,0A0h
	jmp	emm_setAX
emm_error_A1:
	mov	ah,0A1h
	jmp	emm_setAX

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ifdef USEDOSZIP

;----------------------------------------------------------
emm_70: ; Version					70h
;----------------------------------------------------------
	invoke setAX,VERSION
	ret

;----------------------------------------------------------
emm_71: ; Memset Handle					71h
;----------------------------------------------------------
	call	emm_needhandle	; DX handle
	shl	edx,4		; AL char
	add	edx,offset emmh
	mov	edi,[edx].h_memp
	mov	ecx,[edx].h_size
	.if	ecx && edi
		rep stosb
		jmp emm_success
	.endif
	jmp	emm_error_8F

endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

ifdef USECLIPBOARD

memmove proc stdcall uses esi edi s1:dword, s2:dword, cnt:dword
	mov	edi,s1
	mov	esi,s2
	mov	ecx,cnt
	mov	eax,edi
	cld
	cmp	eax,esi
	jbe	@F
	std
	add	esi,ecx
	add	edi,ecx
	sub	esi,1
	sub	edi,1
      @@:
	rep	movsb
	cld
	ret
memmove endp

;----------------------------------------------------------
emm_90: ; Clipboard					90h
;----------------------------------------------------------
	movzx	eax,al
	.if	!al
		invoke	setAX,0103h
	.elseif al == 1			; Open Clipboard
		mov	eax,ClipboardIsOpen
		.if	!eax
			invoke OpenClipboard,eax
		.endif
		mov	ClipboardIsOpen,eax
		invoke	setAX,eax
	.elseif al == 2			; Empty Clipboard
		.if EmptyClipboard()
			invoke setAX,1
		.endif
	.elseif al == 3			; Write to clipboard
		shl	esi,16			; DX format
		mov	si,cx			; SI:CX size
		inc	esi
		.if	GlobalAlloc(GMEM_MOVEABLE or GMEM_DDESHARE,esi)
			mov ebx,eax
			.if	GlobalLock(eax)
				mov	reg_SI,eax
				invoke	getES
				shl	eax,16
				mov	ax,word ptr reg_BX
				mov	edi,eax
				invoke	MGetVdmPointer,edi,esi,0
				invoke	memmove,reg_SI,eax,esi
				invoke	GlobalUnlock,reg_SI
				invoke	SetClipboardData,reg_DX,ebx
				invoke	setAX,eax
				ret
			.endif
			invoke	GlobalFree,ebx
		.endif
		invoke	GetLastError
		invoke	setAX,eax
	.elseif al == 4			; Clipboard size
		.if	GetClipboardData(reg_DX); DX format
			invoke	GlobalSize,eax
			push	eax
			invoke	setAX,eax
			pop	eax
			shr	eax,16
			invoke	setDX,eax
		.else
			invoke	setAX,0
			invoke	setDX,0
		.endif
	.elseif al == 5			; Read clipboard
		invoke	getES		; ES:BX pointer
		shl	eax,16			; DX format
		mov	ax,word ptr reg_BX
		mov	esi,eax
		.if	GetClipboardData(reg_DX)
			mov	ebx,eax
			invoke	GlobalSize,eax
			mov	edi,eax
			.if	GlobalLock(ebx)
				mov	ebx,eax
				invoke	MGetVdmPointer,esi,edi,0
				invoke	memmove,eax,ebx,edi
				invoke	GlobalUnlock,ebx
				mov	eax,1
			.endif
		.endif
		invoke	setAX,eax
	.elseif al == 8			; Close Clipboard
		mov	eax,ClipboardIsOpen
		.if	eax
			.if	CloseClipboard()
				sub eax,eax
				mov ClipboardIsOpen,eax
				inc eax
			.endif
		.endif
		invoke	setAX,eax
	.elseif al == 9
		invoke	getCS
		invoke	setAX,eax
		invoke	setDX,reg_SI
	.endif
	ret

if 0

clip_getshiftcount:
	push	eax
	mov	eax,reg_CX
	shr	eax,7
	mov	ecx,6
	.repeat
		shr eax,1
		inc ecx
	.until	!eax
	pop	eax
	ret

clip_initsidi:
	call	clip_getshiftcount
	.if	cl > 10
		pop eax
		jmp emm_error_8F
	.endif
	shl	edx,cl
	add	esi,edx
	shl	ebx,cl
	add	edi,ebx
	movzx	eax,al
	.if	!eax || eax >= MAXHANDLES
		pop eax
		jmp emm_error_83
	.endif
	shl	eax,4
	add	eax,offset emmh
	mov	edx,eax
	.if	edi > [edx].h_size
		pop eax
		jmp emm_error_8F
	.endif
	ret

;----------------------------------------------------------
emm_91: ; Clipboard Copy				91h
;----------------------------------------------------------
; AL: handle
; DX: start line
; SI: start offset
; BX: end line
; DI: end offset
; CX: line size
	call	clip_initsidi
	mov	reg_DX,edx
	.if	GlobalAlloc([edx].h_size)
		mov	ebx,esi
		sub	ebx,reg_SI
		mov	edx,reg_DX
		mov	ecx,[edx].h_memp
		add	esi,ecx
		add	edi,ecx
		add	ebx,ecx
		mov	edx,edi
		mov	edi,eax
		mov	reg_AX,eax
		.repeat
			lodsb
			.break .if esi >= edx
			.if	!al
				mov al,0Dh
				stosb
				mov al,0Ah
				stosb
				add ebx,reg_CX
				mov esi,ebx
			.elseif al != 0Bh
				stosb
			.endif
		.until	esi >= edx
		mov	al,0
		stosb
		sub	edi,reg_AX
		.if	GlobalAlloc(GMEM_MOVEABLE or GMEM_DDESHARE,edi)
			mov	ebx,eax
			.if	GlobalLock(eax)
				mov	esi,eax
				invoke	memmove,eax,reg_AX,edi
				invoke	GlobalUnlock,esi
				invoke	SetClipboardData,1,ebx
				mov	eax,1
			.endif
			push	eax
			invoke	GlobalFree,ebx
			pop	eax
		.endif
		push	eax
		invoke	GlobalFree,reg_AX
		pop	eax
	.endif
	mov	ebx,eax
	invoke	setAX,eax
	ret

;----------------------------------------------------------
emm_92: ; Clipboard Cut					92h
;----------------------------------------------------------
; AL: handle
; DX: start line
; SI: start offset
; BX: end line
; DI: end offset
; CX: line size
	push	edx
	call	clip_initsidi
	push	esi
	push	edi
	call	emm_91
	pop	edi
	pop	esi
	pop	ecx
	sub	eax,eax
	.if	ebx
		mov	edx,reg_DX
		mov	eax,[edx].h_memp
		mov	ebx,esi
		.if	reg_SI
			sub ebx,reg_SI
			add ebx,reg_CX
		.endif
		add	ebx,eax
		sub	edi,reg_CX
		add	edi,eax
		add	esi,eax
		mov	ecx,eax
		add	ecx,[edx].h_size
		sub	ecx,edi
		mov	byte ptr [esi],0
		invoke	memmove,ebx,edi,ecx
		mov	eax,1
	.endif
	invoke	setAX,eax
	ret

;----------------------------------------------------------
emm_93: ; Clipboard Paste				93h
;----------------------------------------------------------
; AL: handle
; DX: start line
; SI: start offset
; BX: end line
; DI: end offset
; CX: line size

endif
endif

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	.data

emm_functionsAH label byte
	db 40h,41h,42h,43h,44h,45h,46h,47h,48h,49h,4Ah,4Bh,4Ch,4Dh,4Eh,4Fh
	db 50h,51h,52h,53h,54h,55h,56h,57h,58h,59h,5Ah,5Bh,5Ch,5Dh,5Eh
ifdef USEDOSZIP
	db 70h,71h
endif
ifdef USECLIPBOARD
	db 90h
endif
emm_funccount equ $ - offset emm_functionsAH

emm_functions label dword
	dd emm_01,emm_02,emm_03,emm_04,emm_05,emm_06,emm_07,emm_08
	dd emm_09,emm_10,emm_11,emm_12,emm_13,emm_14,emm_15,emm_16
	dd emm_17,emm_18,emm_19,emm_20,emm_21,emm_22,emm_23,emm_24
	dd emm_25,emm_26,emm_27,emm_28,emm_29,emm_30,emm_31
ifdef USEDOSZIP
	dd emm_70,emm_71
endif
ifdef USECLIPBOARD
	dd emm_90
endif
	dd emm_error_84

	.code

dzemm:
ifdef DEBUG
	invoke	getBP
	cmp	ax,5F00h
	jne	@F
	invoke	setAX,dreg_AX
	invoke	setBX,dreg_BX
	invoke	setCX,dreg_CX
	invoke	setDX,dreg_DX
	ret
      @@:
endif
	invoke	getBX
	movzx	eax,ax
	mov	reg_BX,eax
	invoke	getCX
	movzx	eax,ax
	mov	reg_CX,eax
	invoke	getDX
	movzx	eax,ax
	mov	reg_DX,eax
	invoke	getSI
	movzx	eax,ax
	mov	reg_SI,eax
	invoke	getDI
	movzx	eax,ax
	mov	reg_DI,eax
	invoke	getBP
	movzx	eax,ax
	mov	reg_AX,eax
	mov	al,ah
	mov	edi,offset emm_functionsAH
	mov	ecx,emm_funccount
	repne	scasb
	jne	@F
	dec	edi
      @@:
	sub	edi,offset emm_functionsAH
	shl	edi,2
	mov	eax,emm_functions[edi]
	mov	emm_label,eax
	mov	eax,reg_AX
	mov	ebx,reg_BX
	mov	ecx,reg_CX
	mov	edx,reg_DX
	mov	esi,reg_SI
	mov	edi,reg_DI
	call	emm_label
	ret

emm_dispatch:
	push	esi
	push	edi
	mov	edi,MAXHANDLES
	mov	esi,offset emmh
	.repeat
		mov	eax,[esi].S_HANDLE.h_memp
		.if	eax
			invoke GlobalFree,eax
		.endif
		add esi,S_HANDLE
		dec edi
	.until	!edi
	pop	edi
	pop	esi
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

DZEmmInitVDD proc export
	ret
DZEmmInitVDD endp

DZEmmCallVDD proc export
	push	esi
	push	edi
	push	ebx
	call	dzemm
	pop	ebx
	pop	edi
	pop	esi
	ret
DZEmmCallVDD endp

DLL_PROCESS_DETACH equ 0
DLL_PROCESS_ATTACH equ 1

LibMain proc stdcall hModule:dword, dwReason:dword, dwReserved:dword
	.if	dwReason == DLL_PROCESS_DETACH
		call emm_dispatch
	.endif
	mov	eax,1
	ret
LibMain endp

	end LibMain
