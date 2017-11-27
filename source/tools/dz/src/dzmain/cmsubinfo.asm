; CMSUBINFO.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include stdlib.inc
include consx.inc
include string.inc
include crtl.inc

.data
qrax		label qword
qeax		dd 0
qedx		dd 0
di_subdcount	dd 0
di_filecount	dd 0
cp_bytesize	db "BKMGTPE",0
cp_subsize	db "Directory Information",0

    .code

di_fileblock:	; directory, wblk
    inc di_filecount
    mov ecx,[esp+8]
    mov eax,[ecx].WIN32_FIND_DATA.nFileSizeLow
    mov edx,[ecx].WIN32_FIND_DATA.nFileSizeHigh
    add qeax,eax
    adc qedx,edx
    sub eax,eax
    ret 8

di_directory:	; directory
    push esi
    mov esi,[esp+8]
    strlen(esi)
    lea edx,[esi+eax-1]
    mov eax,'\'
    .if [edx] == al
	mov [edx],ah
    .endif
    progress_set(0, esi, 0)
    .if ZERO?
	inc di_subdcount
	scan_files(esi)
    .endif
    pop esi
    ret 4

di_Init:
    xor eax,eax
    mov qeax,eax
    mov qedx,eax
    mov di_filecount,eax
    mov di_subdcount,eax
    ret

di_ReadDirectory:
    push    eax
    progress_open(addr cp_subsize,0)
    mov fp_maskp,offset cp_stdmask
    mov fp_fileblock,di_fileblock
    mov fp_directory,di_directory
    pop eax
    scan_directory(1,eax)
    progress_close()
    test    eax,eax
    ret

di_SubInfo proc private uses esi edi ebx s1, s2
  local x,y,col

    .if rsopen(IDD_DZSubInfo)

	mov edi,eax
	movzx	eax,[edi].S_DOBJ.dl_rect.rc_x
	add eax,5
	mov x,eax
	movzx	eax,[edi].S_DOBJ.dl_rect.rc_y
	add eax,2
	mov y,eax
	movzx	eax,[edi].S_DOBJ.dl_rect.rc_col
	mov col,eax
	wctitle([edi].S_DOBJ.dl_wp, eax, s2)
	dlshow(edi)

	mov edx,y
	mov ecx,x
	add cl,10
	scpath(ecx, edx, 20, s1)

	sub cl,11
	inc edx
	scputf(ecx, edx, 0, 0, "%10u", di_filecount)

	mov eax,di_subdcount
	dec eax
	inc edx
	scputf(ecx, edx, 0, 0, "%10u", eax)

	mov ebx,mkbstring(s1, qrax)
	mov esi,edx
	mov edx,y
	mov ecx,x
	add ecx,1
	add edx,4
	scputf(ecx, edx, 0, 0, "total %s byte", s1)

	.if ebx && esi

	    mov al,cp_bytesize[esi]
	    add ecx,6
	    inc edx
	    scputf(ecx, edx, 0, 0, "%u%c", ebx, eax)
	.endif
	dlmodal(edi)
    .endif
    ret

di_SubInfo endp

di_SelectedFiles proc private uses esi edi s1

    inc di_subdcount
    xor esi,esi

    .while  1
	mov eax,1
	mov edx,cpanel
	.break .if esi >= [edx].S_PANEL.pn_fcb_count

	mov eax,[edx].S_PANEL.pn_wsub
	mov eax,[eax].S_WSUB.ws_fcb
	mov eax,[eax+esi*4]
	mov ecx,[eax]
	inc esi

	.continue .if !(ecx &_FB_SELECTED)

	.if ecx & _A_SUBDIR

	    mov edx,cpanel
	    mov edx,[edx].S_PANEL.pn_wsub
	    add eax,S_FBLK.fb_name
	    strfcat(s1, [edx].S_WSUB.ws_path, eax)
	    di_ReadDirectory()
	    .break .if eax
	.else
	    mov edx,dword ptr [eax].S_FBLK.fb_size[4]
	    mov eax,dword ptr [eax].S_FBLK.fb_size
	    add qeax,eax
	    adc qedx,edx
	    inc di_filecount
	.endif
    .endw

    .if eax

	mov eax,cpanel
	mov eax,[eax].S_PANEL.pn_wsub
	di_SubInfo(strcpy(s1, [eax].S_WSUB.ws_path), "Selected Files")
    .endif

    ret
di_SelectedFiles endp

di_cmSubInfo proc private uses esi edi ebx panel

  local path[_MAX_PATH]:byte

    mov esi,panel
    lea edi,path

    .if panel_state(esi)

	mov ebx,[esi]
	mov eax,[ebx]

	.if !(eax & _W_ARCHIVE or _W_ROOTDIR)

	    di_Init()

	    .if panel_findnext(esi)

		di_SelectedFiles(edi)
	    .else
		mov ebx,[esi].S_PANEL.pn_wsub
		strcpy(edi, [ebx].S_WSUB.ws_path)
		di_ReadDirectory()
		.if !eax

		    di_SubInfo(edi, addr cp_subsize)
		.endif
	    .endif
	.else
	    xor eax,eax
	.endif
    .endif
    ret
di_cmSubInfo endp

cmsubinfo proc
    di_cmSubInfo(cpanel)
    ret
cmsubinfo endp

cmasubinfo proc
    di_cmSubInfo(panela)
    ret
cmasubinfo endp

cmbsubinfo proc
    di_cmSubInfo(panelb)
    ret
cmbsubinfo endp

cmsubsize proc

  local path[_MAX_PATH]:byte

    di_Init()

    .if panel_curobj(cpanel)

	.if !(ecx & _FB_ARCHIVE or _FB_UPDIR)

	    mov edx,cpanel
	    mov edx,[edx].S_PANEL.pn_wsub
	    mov ecx,eax
	    strfcat(addr path, [edx].S_WSUB.ws_path, ecx)

	    .if !di_ReadDirectory()

		di_SubInfo(addr path, addr cp_subsize)
	    .endif
	.endif
    .endif

    xor eax,eax
    ret

cmsubsize endp

    END
