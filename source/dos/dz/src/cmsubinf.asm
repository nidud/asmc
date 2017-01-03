; CMSUBINF.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include dos.inc
include progress.inc
include stdlib.inc
include conio.inc
include string.inc
include math.inc

_DATA	segment

di_subdcount	dd ?
di_filecount	dd ?
qeax		dd ?
qedx		dd ?
cp_subsize	db "Directory Information",0
cp_bytesize	db "BKMGTPE",0
cp_location	db "Location:",0
cp_format	db "%10lu Files",10,"%10lu Directories",0
cp_total	db "total %s byte",0
cp_format_luc	db " %lu%c",0
cp_selected	db "Selected Files",0

_DATA	ENDS

_DZIP	segment

DI_CLEAR:
      ifdef __3__
	xor	eax,eax
	mov	qeax,eax
	mov	qedx,eax
	mov	di_filecount,eax
	mov	di_subdcount,eax
      else
	xor	ax,ax
	mov	WORD PTR qeax+2,ax
	mov	WORD PTR qeax,ax
	mov	WORD PTR qedx+2,ax
	mov	WORD PTR qedx,ax
	mov	WORD PTR di_filecount,ax
	mov	WORD PTR di_filecount+2,ax
	mov	WORD PTR di_subdcount,ax
	mov	WORD PTR di_subdcount+2,ax
      endif
	ret

DI_DOFILE PROC _CType PRIVATE directory:DWORD, wblk:DWORD
	incm di_filecount
	lodm directory
	.if dx
	    les bx,wblk
	    add bx,S_WFBLK.wf_name
	    .if !progress_set(es::bx,dx::ax,dx::ax)
		les bx,wblk
	      ifdef __3__
		mov eax,es:[bx].S_WFBLK.wf_sizeax
		mov edx,es:[bx].S_WFBLK.wf_sizedx
		add qeax,eax
		adc qedx,edx
	      else
		mov ax,WORD PTR es:[bx].S_WFBLK.wf_sizeax
		mov dx,WORD PTR es:[bx].S_WFBLK.wf_sizeax[2]
		mov cx,WORD PTR es:[bx].S_WFBLK.wf_sizedx[2]
		mov bx,WORD PTR es:[bx].S_WFBLK.wf_sizedx
		add WORD PTR qedx,bx
		adc WORD PTR qedx+2,cx
		add WORD PTR qeax,ax
		adc WORD PTR qeax+2,dx
		adc WORD PTR qedx,0
		adc WORD PTR qedx+2,0
	      endif
		sub ax,ax
	    .endif
	.endif
	ret
DI_DOFILE ENDP

DI_DOSUBD PROC _CType PRIVATE directory:DWORD
	invoke strlen, directory
	mov bx,WORD PTR directory
	add bx,ax
	mov ax,'\'
	dec bx
	.if [bx] == al
	    mov [bx],ah
	.endif
	.if !progress_set(0,directory,0)
	    incm di_subdcount
	    invoke scan_files,directory
	.endif
	ret
DI_DOSUBD ENDP

DI_SCANSUB:	; DX:AX Subdir
	push 1
	push dx
	push ax
	invoke progress_open,addr cp_subsize,0
	mov WORD PTR fp_maskp,offset cp_stdmask
	mov WORD PTR fp_maskp+2,ds
	movp fp_fileblock,DI_DOFILE
	movp fp_directory,DI_DOSUBD
	call scan_directory
	call progress_close
	test ax,ax
	ret

DI_SUBINFO PROC pascal PRIVATE USES si di s1:DWORD, s2:DWORD
	.if rsopen(IDD_DZSubInfo)
	    mov si,dx
	    mov di,ax
	    mov ch,0
	    mov cl,es:[di+6]
	    invoke wctitle,es:[di].S_DOBJ.dl_wp,cx,s2
	    invoke dlshow,si::di
	    mov bx,es:[di+4]
	    add bx,0205h
	    mov dl,bh
	    invoke scputs,bx,dx,0,0,addr cp_location
	    add bl,10
	    invoke scpath,bx,dx,20,s1
	    sub bl,11
	  ifdef __3__
	    mov eax,di_subdcount
	    dec eax
	    inc dx
	    invoke scputf,bx,dx,0,0,addr cp_format,di_filecount,eax
	  else
	    mov cx,dx
	    lodm di_subdcount
	    sub ax,1
	    sbb dx,0
	    inc cx
	    invoke scputf,bx,cx,0,0,addr cp_format,di_filecount,dx::ax
	  endif
	    invoke mkbstring,s1,qedx,qeax
	    push si
	    push di
	    mov es,si
	    mov bx,di
	    mov di,ax
	    mov si,dx
	    mov bx,es:[bx+4]
	    add bx,0606h
	    mov dl,bh
	    invoke scputf,bx,dx,0,0,addr cp_total,s1
	    .if di && si
		mov al,cp_bytesize[si]
		add bx,6
		inc dx
		invoke scputf,bx,dx,0,0,addr cp_format_luc,di,0,ax
	    .endif
	    call dlmodal
	.endif
	ret
DI_SUBINFO ENDP

DI_DOSELECTED PROC pascal PRIVATE USES si di s1:DWORD
	incm di_subdcount
	mov bx,cpanel
	mov bx,WORD PTR [bx].S_PANEL.pn_wsub
	mov di,WORD PTR [bx].S_WSUB.ws_fcb[2]
	xor si,si
	.repeat
	    mov ax,1
	    mov bx,cpanel
	    .break .if si >= [bx].S_PANEL.pn_fcb_count
	    mov es,di
	    mov bx,si
	    shl bx,2
	    add bx,4
	    mov dx,es:[bx+2]
	    mov bx,es:[bx]
	    mov es,dx
	    mov cx,es:[bx]
	    inc si
	    .continue .if !(cx &_A_SELECTED)
	    .if cx & _A_SUBDIR
		mov ax,bx
		mov bx,cpanel
		mov bx,WORD PTR [bx].S_PANEL.pn_wsub
		add ax,S_FBLK.fb_name
		invoke strfcat,s1,[bx].S_WSUB.ws_path,dx::ax
		call DI_SCANSUB
		.break .if ax
	    .else
	      ifdef __3__
		mov eax,es:[bx].S_FBLK.fb_size
		add qeax,eax
		adc qedx,0
		inc di_filecount
	      else
		lodm es:[bx].S_FBLK.fb_size
		add WORD PTR qeax,ax
		adc WORD PTR qeax+2,dx
		adc WORD PTR qedx,0
		adc WORD PTR qedx+2,0
		incm di_filecount
	      endif
	    .endif
	.until 0
	.if ax
	    mov bx,cpanel
	    mov bx,WORD PTR [bx].S_PANEL.pn_wsub
	    invoke strcpy,s1,[bx].S_WSUB.ws_path
	    invoke DI_SUBINFO,dx::ax,addr cp_selected
	.endif
	ret
DI_DOSELECTED ENDP

DI_CMSUBINFO PROC pascal PRIVATE USES si di panel:WORD
local path[WMAXPATH]:BYTE
	mov si,panel
	lea di,path
	mov ax,si
	.if panel_state()
	    mov bx,[si]
	    mov ax,[bx]
	    .if !(ax & _W_ARCHIVE or _W_ROOTDIR)
		call DI_CLEAR
		mov ax,si
		.if panel_findnext()
		    invoke DI_DOSELECTED,ss::di
		.else
		    mov bx,WORD PTR [si].S_PANEL.pn_wsub
		    invoke strcpy,ss::di,[bx].S_WSUB.ws_path
		    call DI_SCANSUB
		    .if !ax
			invoke DI_SUBINFO,ss::di,addr cp_subsize
		    .endif
		.endif
	    .else
		sub ax,ax
	    .endif
	.endif
	ret
DI_CMSUBINFO ENDP

cmsubinfo PROC _CType PUBLIC
	invoke DI_CMSUBINFO,cpanel
	ret
cmsubinfo ENDP

cmasubinfo PROC _CType PUBLIC
	invoke DI_CMSUBINFO,panela
	ret
cmasubinfo ENDP

cmbsubinfo PROC _CType PUBLIC
	invoke DI_CMSUBINFO,panelb
	ret
cmbsubinfo ENDP

cmsubsize PROC _CType PUBLIC
local path[WMAXPATH]:BYTE
	call DI_CLEAR
	mov ax,cpanel
	.if panel_curobj()
	    .if !(cx & _A_ARCHIVE or _A_UPDIR)
		mov bx,cpanel
		mov bx,WORD PTR [bx].S_PANEL.pn_wsub
		mov cx,ax
		invoke strfcat,addr path,[bx].S_WSUB.ws_path,dx::cx
		call DI_SCANSUB
		.if !ax
		    invoke DI_SUBINFO,addr path,addr cp_subsize
		.endif
	    .endif
	.endif
	sub ax,ax
	ret
cmsubsize ENDP

_DZIP	ENDS

	END
