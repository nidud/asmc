; OPFILTER.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include fblk.inc
include string.inc
include filter.inc
include conio.inc
include time.inc
include stdio.inc
include stdlib.inc

externdef	format_lu:BYTE
externdef	cp_stdmask:BYTE
externdef	IDD_OperationFilters:DWORD

ID_INCLUDE	equ 1*16
ID_EXCLUDE	equ 2*16
ID_MIN_DATE	equ 3*16
ID_MAX_DATE	equ 4*16
ID_MIN_SIZE	equ 5*16
ID_MAX_SIZE	equ 6*16
ID_RDONLY	equ 7*16
ID_HIDDEN	equ 8*16
ID_SYSTEM	equ 9*16
ID_VOLID	equ 10*16
ID_SUBDIR	equ 11*16
ID_ARCH		equ 12*16
ID_OK		equ 13*16
ID_CLEAR	equ 14*16
ID_CANCEL	equ 15*16

.code

filter_edit_clear:
	mov	dx,ds
	mov	cx,si
	lds	si,tdialog
	xor	ax,ax
	mov	bx,WORD PTR [si].S_TOBJ.to_data[ID_MIN_DATE]
	mov	[bx],al
	mov	bx,WORD PTR [si].S_TOBJ.to_data[ID_MAX_DATE]
	mov	[bx],al
	mov	bx,WORD PTR [si].S_TOBJ.to_data[ID_MIN_SIZE]
	mov	[bx],al
	mov	bx,WORD PTR [si].S_TOBJ.to_data[ID_MAX_SIZE]
	mov	[bx],al
	mov	ds,dx
	mov	si,cx
	invoke	memzero,filter,S_FILT
	les	bx,filter
	invoke	strcpy,addr es:[bx].S_FILT.of_include,addr cp_stdmask
	mov	es:[bx].S_FILT.of_flag,-1
	lodm	tdialog
	add	ax,ID_RDONLY
	invoke	tosetbitflag,dx::ax,6,_O_FLAGB,0FFFFFFFFh
	mov	ax,_C_REOPEN
	retx

filter_edit PROC _CType PUBLIC USES si di filt:DWORD, glcmd:DWORD
local	DLG_OperationFilters:DWORD
	sub ax,ax
	mov WORD PTR filter,ax
	.if rsopen(IDD_OperationFilters)
	    stom DLG_OperationFilters
	    mov	 di,ax
	    lodm filt
	    add	 ax,S_FILT.of_include
	    stom es:[di].S_TOBJ.to_data[ID_INCLUDE]
	    mov	 es:[di].S_TOBJ.to_count[ID_INCLUDE],8
	    add	 ax,128
	    stom es:[di].S_TOBJ.to_data[ID_EXCLUDE]
	    mov	 es:[di].S_TOBJ.to_count[ID_EXCLUDE],8
	    lodm glcmd
	    stom es:[di].S_TOBJ.to_data[ID_OK]
	    movp es:[di].S_TOBJ.to_proc[ID_CLEAR],filter_edit_clear
	    mov si,WORD PTR filt
	    .if [si].S_FILT.of_min_date
		invoke dwtolstr,es:[di].S_TOBJ.to_data[ID_MIN_DATE],[si].S_FILT.of_min_date
	    .endif
	    .if [si].S_FILT.of_max_date
		invoke dwtolstr,es:[di].S_TOBJ.to_data[ID_MAX_DATE],[si].S_FILT.of_max_date
	    .endif
	    lodm [si].S_FILT.of_min_size
	    .if ax
		invoke sprintf,es:[di].S_TOBJ.to_data[ID_MIN_SIZE],addr format_lu,dx::ax
	    .endif
	    lodm [si].S_FILT.of_max_size
	    .if ax || dx
		invoke sprintf,es:[di].S_TOBJ.to_data[ID_MAX_SIZE],addr format_lu,dx::ax
	    .endif
	    mov bx,di
	    add bx,ID_RDONLY
	    mov ax,[si].S_FILT.of_flag
	    invoke tosetbitflag,es::bx,6,_O_FLAGB,dx::ax
	    invoke dlinit,DLG_OperationFilters
	    movmx filter,filt
	    .if rsevent(IDD_OperationFilters,DLG_OperationFilters)
		invoke togetbitflag,addr es:[di][ID_RDONLY],6,_O_FLAGB
		or ax,0FFC0h
		mov [si].S_FILT.of_flag,ax
		invoke strtol,es:[di].S_TOBJ.to_data[ID_MAX_SIZE]
		stom [si].S_FILT.of_max_size
		invoke strtol,es:[di].S_TOBJ.to_data[ID_MIN_SIZE]
		stom [si].S_FILT.of_min_size
		invoke strtodw,es:[di].S_TOBJ.to_data[ID_MAX_DATE]
		mov [si].S_FILT.of_max_date,ax
		invoke strtodw,es:[di].S_TOBJ.to_data[ID_MIN_DATE]
		mov [si].S_FILT.of_min_date,ax
	    .else
		mov dx,ax
		stom filter
	    .endif
	    invoke thelp_pop
	    invoke dlclose,DLG_OperationFilters
	    mov ax,_C_NORMAL
	.endif
	ret
filter_edit ENDP

	END
