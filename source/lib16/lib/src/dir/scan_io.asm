; SCAN_IO.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include dos.inc
include string.inc

extrn	cp_stdmask: BYTE
PUBLIC	fp_maskp
PUBLIC	fp_directory
PUBLIC	fp_fileblock
PUBLIC	scan_fblock

ATTRIB_ALL	equ 0B7h ;37h
ATTRIB_FILE	equ 0F7h ;27h

.data
fp_maskp	dd ?
fp_directory	p? ?
fp_fileblock	p? ?
scan_fblock	S_WFBLK <?>
scan_curpath	db WMAXPATH dup(?)
scan_curfile	db WMAXPATH dup(?)

.code

scan_init:
	mov	[bp-12],dx
	mov	[bp-10],ds
	mov	WORD PTR [bp-8],offset scan_fblock
	mov	[bp-6],ds
	xor	ax,ax
	mov	[bp-4],ax
	mov	[bp-16],ax
ifdef __LFN__
	cmp	_ifsmgr,al
	jne	@F
endif
	mov	ah,2Fh
	int	21h
	mov	[bp-16],es
	mov	[bp-14],bx
	lea	dx,[bp-62]
	mov	ah,1Ah
	int	21h
      @@:
	ret

scan_findfirst:
	mov dx,[bp-12]
      ifdef __LFN__
	.if _ifsmgr
	    mov ax,714Eh
	    mov si,1
	    les di,[bp-8]
	    stc
	    int 21h
	    jc scan_error
	    ret
	.endif
      endif
	mov ah,4Eh
	int 21h
	jnc scan_copy
	call restore_DTA
scan_error:
	call osmaperr
	cwd
	ret

scan_findnext:
ifdef __LFN__
	.if _ifsmgr
	    stc
	    mov ax,714Fh
	    mov bx,[bp-18]
	    mov si,1
	    les di,[bp-8]
	    int 21h
	    jnc @F
	    cmp ax,0057h
	    jne scan_error
	    mov ax,714Fh
	    int 21h
	    jc scan_error
	  @@:
	    sub ax,ax
	    ret
	.endif
endif
	mov ah,4Fh
	int 21h
	jc  scan_error
	jmp scan_copy

scan_close:
ifdef __LFN__
	.if _ifsmgr
	    mov bx,[bp-18]
	    mov ax,71A1h
	    int 21h
	    ret
	.endif
endif

restore_DTA:
	mov	ax,[bp-16]
	test	ax,ax
	jz	@F
	push	ds
	mov	ds,ax
	mov	dx,[bp-14]
	mov	ah,1Ah
	int	21h
	pop	ds
      @@:
	ret

scan_copy:
	push	si
	les	di,[bp-8]
	mov	si,di
	mov	cx,SIZE S_WFBLK/2
	xor	ax,ax
	cld?
	rep	stosw
	mov	di,si
	lea	si,[bp-62]
	mov	al,[si].S_FFBLK.ff_attrib
	mov	[di],al
	movmx	[di].S_WFBLK.wf_time,[si].S_FFBLK.ff_ftime
	movmx	[di].S_WFBLK.wf_sizeax,[si].S_FFBLK.ff_fsize
	add	si,S_FFBLK.ff_name
	add	di,S_WFBLK.wf_name
	mov	cx,6
	rep	movsw
	mov	ax,cx
	stosb
	pop	si
	ret

scan_directory PROC _CType PUBLIC USES ds si di flag:WORD, path:PTR BYTE
local locsp_d[62]:BYTE
	mov dx,offset scan_curpath
	call scan_init
	.if BYTE PTR flag & 1
	    pushm path
	    call fp_directory
	    mov [bp-4],ax
	    .if ax
		call restore_DTA
		jmp @F
	    .endif
	.endif
	invoke strlen,path
	add ax,offset scan_curpath
	mov [bp-2],ax
	invoke strfcat,[bp-12],path,addr cp_stdmask
	mov cx,ATTRIB_ALL
	call scan_findfirst
	.if ax != -1
	   mov [bp-18],ax
	   call scan_findnext
	   .if !ax
		.repeat
		    call scan_findnext
		    .break .if ax
		    .continue .if !(BYTE PTR scan_fblock & _A_SUBDIR)
		    mov	 ax,[bp-2]
		    inc	 ax
		    push ds
		    push ax
		    push [bp-6]
		    mov	 ax,[bp-8]
		    add	 ax,S_WFBLK.wf_name
		    push ax
		    call strcpy
		    invoke scan_directory,flag,[bp-12]
		    mov [bp-4],ax
		.until ax
	   .endif
	   call scan_close
	.endif
	xor ax,ax
	mov bx,[bp-2]
	mov [bx],al
      @@:
	mov ax,[bp-4]
	.if !(BYTE PTR flag & 1)
	    pushm path
	    call fp_directory
	.endif
	ret
scan_directory ENDP

scan_files PROC _CType PUBLIC USES ds si di fpath:PTR BYTE
local locsp_f[62]:BYTE
	mov dx,offset scan_curfile
	call scan_init
	invoke strfcat,[bp-12],fpath,fp_maskp
	mov cx,ATTRIB_FILE
	call scan_findfirst
	.if ax != -1
	    mov [bp-18],ax
	    .repeat
		.if !(BYTE PTR scan_fblock & _A_SUBDIR)
		    pushm fpath
		    pushm [bp-8]
		    call fp_fileblock
		    mov [bp-4],ax
		    .break .if ax
		.endif
		call scan_findnext
	    .until ax
	    call scan_close
	.endif
	mov ax,[bp-4]
	ret
scan_files ENDP

scansub PROC _CType PUBLIC directory:DWORD, smask:DWORD, sflag:size_t
	movmx	fp_maskp,smask
	invoke	scan_directory,sflag,directory
	ret
scansub ENDP

	END
