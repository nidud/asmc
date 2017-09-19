; CMDELETE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include string.inc
include errno.inc

externdef   cp_delete:byte
setconfirmflag	proto

    .data
    __spath dd 0

    .code

    option proc:private

open_progress proc
    setconfirmflag()
    progress_open(&cp_delete, 0)
    ret
open_progress endp

remove_file proc uses esi directory, filename, attrib
    local path[_MAX_PATH*2]:byte
    lea esi,path

    .if !progress_set(filename, directory, 0)

	.if confirm_delete_file(filename, attrib) && eax != -1

	    strfcat(esi, directory, filename)
	    .if byte ptr attrib & _A_RDONLY
		setfattr(esi, 0)
	    .endif

	    mov errno,0
	    .if remove(esi)
		erdelete(esi)
	    .endif
	.endif
    .endif
    ret
remove_file endp

remove_directory proc directory
local path[_MAX_PATH*2]:byte
    strfcat(&path, __spath, directory)
    .if confirm_delete_sub(eax) == 1
	scan_directory(0, &path)
    .endif
    ret
remove_directory endp

fp_remove_file proc directory, wfblock
    mov edx,wfblock
    remove_file(
	directory,
	&[edx].WIN32_FIND_DATA.cFileName,
	[edx].WIN32_FIND_DATA.dwFileAttributes
    )
    ret
fp_remove_file endp

fp_remove_directory proc uses ebx directory
    mov ebx,directory
    .if !progress_set(0, ebx, 1)
	scan_files(ebx)
	push eax
	setfattr(ebx, 0)
	_rmdir(ebx)
	pop eax
    .endif
    ret
fp_remove_directory endp

cmdelete_remove proc
    .if cl & _A_SUBDIR
	remove_directory(eax)
    .else
	mov errno,0
	remove_file(__spath, eax, ecx)
    .endif
    test eax,eax
    ret
cmdelete_remove endp

    option proc: PUBLIC

cmdelete proc uses ebx
    .switch
      .case !cpanel_findfirst()
      .case ecx & _FB_ROOTDIR
	xor eax,eax
	.endc
      .case ecx & _FB_ARCHEXT
	mov eax,cpanel
	mov eax,[eax].S_PANEL.pn_wsub
	warcdelete(eax, edx)
	xor eax,eax
	.endc
      .case ecx & _FB_ARCHZIP
	xor eax,eax
	mov ebx,edx
	open_progress()
	.repeat
	    mov eax,cpanel
	    .break .if wzipdel([eax].S_PANEL.pn_wsub, ebx)
	    and [ebx].S_FBLK.fb_flag,not _FB_SELECTED
	    panel_findnext(cpanel)
	    mov ebx,edx
	.untilz
	progress_close()
	.endc
      .default
	mov ebx,edx
	mov eax,cpanel
	mov edx,[eax].S_PANEL.pn_wsub
	mov eax,[edx].S_WSUB.ws_path
	mov __spath,eax

	mov fp_maskp,offset cp_stdmask
	mov fp_fileblock,fp_remove_file
	mov fp_directory,fp_remove_directory

	open_progress()
	mov edx,ebx
	mov ecx,[edx].S_FBLK.fb_flag
	lea eax,[edx].S_FBLK.fb_name

	.if !(ecx & _FB_SELECTED)

	    cmdelete_remove()
	.else
	    .repeat
		cmdelete_remove()
		.break .ifnz
		and [ebx].S_FBLK.fb_flag,not _FB_SELECTED
		panel_findnext(cpanel)
		mov ebx,edx
	    .untilz
	.endif
	progress_close()
    .endsw
    ret
cmdelete endp

    END
