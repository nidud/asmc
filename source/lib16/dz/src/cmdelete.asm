; CMDELETE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include dos.inc
include string.inc
include confirm.inc
include progress.inc
include errno.inc
ifdef __ZIP__
 include dzzip.inc
endif

_DATA	segment

__spath db  66 dup(?)
__cdir	db 256 dup(?)

_DATA	ENDS

_DZIP	segment

setconfirmflag PROC PUBLIC
	mov	dx,CFSELECTED
	mov	ax,config.c_confirm
	test	al,_C_CONFDELETE
	jz	@F
	or	dx,CFDELETEALL
      @@:
	test	al,_C_CONFDELSUB
	jz	@F
	or	dx,CFDIRECTORY
      @@:
	test	al,_C_CONFSYSTEM
	jz	@F
	or	dx,CFSYSTEM
      @@:
	test	al,_C_CONFRDONLY
	jz	@F
	or	dx,CFREADONY
      @@:
	mov	confirmflag,dx
	ret
setconfirmflag ENDP

open_progress:
	invoke	setconfirmflag
	invoke	progress_open,addr cp_delete,0
	ret

remove_file PROC pascal PRIVATE directory:DWORD, filename:DWORD, attrib:WORD
local	path[WMAXPATH]:BYTE
	invoke	progress_set,filename,directory,0
	jnz	remove_file_end
	invoke	confirm_delete_file,filename,attrib
	test	ax,ax
	jz	remove_file_end
	inc	ax ; -1 --> 1
	jnz	@F
	inc	ax
	jmp	remove_file_end
      @@:
	invoke	strfcat,addr path,directory,filename
	mov	ax,attrib
	test	al,_A_RDONLY
	jz	@F
	invoke	_dos_setfileattr,addr path,0
      @@:
	mov	errno,0
	invoke	remove,addr path
ifdef __LFN__
	.if ax && errno
	    invoke wlongpath,addr path,0
	    invoke remove,dx::ax
	.endif
endif
	test	ax,ax
	jz	remove_file_end
	invoke	erdelete,addr path
    remove_file_end:
	ret
remove_file ENDP

remove_directory PROC pascal PRIVATE directory:DWORD
ifdef __LFN__
	invoke	wshortname,directory
else
	lodm	directory
endif
	invoke	strfcat,addr __cdir,addr __spath,dx::ax
	invoke	confirm_delete_sub,dx::ax
	cmp	ax,1
	jne	@F
	invoke	scan_directory,0,addr __cdir
      @@:
	ret
remove_directory ENDP

fp_remove_file PROC _CType PRIVATE directory:DWORD, wfblock:DWORD
	les	bx,wfblock
	invoke	remove_file,directory,addr es:[bx].S_WFBLK.wf_name,
		WORD PTR es:[bx].S_WFBLK.wf_attrib
	ret
fp_remove_file ENDP

fp_remove_directory PROC _CType PRIVATE directory:DWORD
	invoke	progress_set,0,directory,1
	jnz	@F
	invoke	scan_files,directory
	push	ax
	invoke	_dos_setfileattr,directory,0
	invoke	rmdir,directory
	pop	ax
      @@:
	ret
fp_remove_directory ENDP

cmdelete_remove PROC PRIVATE
	mov	di,S_FBLK.fb_name+4
	test	dl,_A_SUBDIR
	jz	@F
	invoke	remove_directory,bp::di
	jmp	cmdelete_remove_end
      @@:
	mov	errno,0
	invoke	remove_file,ds::si,bp::di,dx
ifdef __LFN__
	.if ax && errno
	    invoke wshortname,bp::di
	    mov es,bp
	    sub di,S_FBLK.fb_name
	    invoke remove_file,ds::si,dx::ax,es:[di].S_FBLK.fb_flag
	.endif
endif
    cmdelete_remove_end:
	mov	di,ax
	test	ax,ax
	ret
cmdelete_remove ENDP

ifdef __ZIP__
cmdeletezip:  ; DX:BX = fblk, CX = flag
	push	bp
	push	si
	push	di
	mov	si,dx
	mov	di,bx
	mov	bp,cx
	sub	ax,ax
	test	cx,_A_ARCHZIP
	jz	cmdeletezip_end
	call	open_progress
      @@:
	mov	bx,cpanel
	mov	ax,WORD PTR [bx].S_PANEL.pn_wsub
	mov	bx,di
	mov	dx,si
	call	wsdeletearc
	test	ax,ax
	jnz	@F
	mov	ax,es:[di]
	and	ax,not _A_SELECTED
	mov	es:[di],ax
	mov	ax,cpanel
	call	panel_findnext
	jz	@F
	mov	si,dx
	mov	di,bx
	jmp	@B
      @@:
	call	ret_update_AB
    cmdeletezip_end:
	pop	di
	pop	si
	pop	bp
	ret
endif

cmdelete PROC _CType PUBLIC
	push	bp
	push	si
	push	di
	call	cpanel_findfirst
	jz	cmdelete_end
ifdef __ROT__
	test	cx,_A_ROOTDIR
	jnz	cmdelete_end
endif
ifdef __ZIP__
	test	cx,_A_ARCHIVE
	jz	@F
	call	cmdeletezip
	jmp	cmdelete_end
      @@:
endif
	mov	bp,dx
	mov	si,offset __spath
	mov	bx,cpanel
	mov	bx,[bx]
	mov	ax,[bx]
	and	ax,_W_NETWORK
	cmp	ax,_W_NETWORK
	jne	@F
	invoke	strcpy,ds::si,addr [bx].S_PATH.wp_path
	jmp	cmdelete_00
      @@:
	invoke	fullpath,ds::si,0
	test	ax,ax
	jz	cmdelete_end
    cmdelete_00:
	mov	WORD PTR fp_maskp,offset cp_stdmask
	mov	WORD PTR fp_maskp+2,ds
	movp	fp_fileblock,fp_remove_file
	movp	fp_directory,fp_remove_directory
	call	open_progress
	mov	es,bp
	mov	bx,4
	mov	dx,es:[bx]
	test	dx,_A_SELECTED
	jz	cmdelete_01
      @@:
	jz	cmdelete_02
	call	cmdelete_remove
	test	ax,ax
	jnz	cmdelete_02
	mov	es,bp
	mov	bx,4
	and	BYTE PTR es:[bx],not _A_SELECTED
	mov	ax,cpanel
	call	panel_findnext
	mov	bp,dx
	mov	dx,cx
	jmp	@B
    cmdelete_01:
	call	cmdelete_remove
    cmdelete_02:
	mov	ax,di
	call	ret_update_AB
    cmdelete_end:
	pop	di
	pop	si
	pop	bp
	ret
cmdelete ENDP

_DZIP	ENDS

	END
