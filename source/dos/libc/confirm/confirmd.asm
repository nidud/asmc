; CONFIRMD.ASM--
; Copyright (C) 2015 Doszip Developers
include dos.inc
include conio.inc
include confirm.inc

extrn	IDD_ConfirmDelete:DWORD
;
; ret:	0 Cancel
;	1 Delete
;	2 Delete All
;	3 Jump
;
	.data
	cp_delselected	db "   You have selected %d file(s)",10
			db "Do you want to delete all the files",0
	cp_delflag	db "  Do you still wish to delete it?",0

	.code

confirm_delete PROC _CType PUBLIC USES bx info:PTR BYTE, selected:size_t
local	DLG_ConfirmDelete:DWORD
	.if rsopen(IDD_ConfirmDelete)
	    stom DLG_ConfirmDelete
	    invoke dlshow,dx::ax
	    les bx,DLG_ConfirmDelete
	    sub ax,ax
	    mov al,es:[bx][4]
	    mov dx,ax
	    mov al,es:[bx][5]
	    mov bx,ax
	    add bx,2		; y
	    add dx,12		; x
	    mov ax,selected
	    .if ax > 1 && ax < 8000h
		invoke scputf,dx,bx,0,0,addr cp_delselected,ax
	    .else
		push dx
		.if ax == -2
		    scputf(dx,bx,0,0,
			"The following file is marked System.\n\n%s",
			addr cp_delflag)
		.elseif ax == -1
		    sub dx,2
		    scputf(dx,bx,0,0,
			"The following file is marked Read only.\n\n  %s",
			addr cp_delflag)
		.else
		    add dx,6
		    scputf(dx,bx,0,0,"Do you wish to delete")
		.endif
		pop dx
		inc bx
		sub dx,9
		invoke scenter,dx,bx,53,info
	    .endif
	    invoke beep,50,6
	    invoke rsevent,IDD_ConfirmDelete,DLG_ConfirmDelete
	    invoke dlclose,DLG_ConfirmDelete
	    mov ax,dx
	.endif
	ret
confirm_delete ENDP

	END
