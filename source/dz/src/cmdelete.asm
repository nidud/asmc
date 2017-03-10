; CMDELETE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include string.inc
include confirm.inc
include progress.inc
include errno.inc

externdef	cp_delete:BYTE
setconfirmflag	PROTO

	.data

	__spath dd 0

	.code

	OPTION PROC: PRIVATE

open_progress PROC
	call	setconfirmflag
	progress_open( addr cp_delete, 0 )
	ret
open_progress ENDP

remove_file PROC USES esi directory, filename, attrib
	local	path[_MAX_PATH*2]:BYTE
	lea	esi,path

	.if	!progress_set( filename, directory, 0 )

		.if	confirm_delete_file( filename, attrib ) && eax != -1

			strfcat( esi, directory, filename )
			.if	BYTE PTR attrib & _A_RDONLY
				setfattr( esi, 0 )
			.endif

			mov	errno,0
			.if	remove( esi )
				erdelete( esi )
			.endif
		.endif
	.endif
	ret
remove_file ENDP

remove_directory PROC directory
	local	path[_MAX_PATH*2]:BYTE
	strfcat( addr path, __spath, directory )
	.if	confirm_delete_sub( eax ) == 1
		scan_directory( 0, addr path )
	.endif
	ret
remove_directory ENDP

fp_remove_file PROC directory, wfblock
	mov	edx,wfblock
	lea	eax,[edx].S_WFBLK.wf_name
	remove_file( directory, eax, [edx].S_WFBLK.wf_attrib )
	ret
fp_remove_file ENDP

fp_remove_directory PROC USES ebx directory
	mov	ebx,directory
	.if	!progress_set( 0, ebx, 1 )
		scan_files( ebx )
		push	eax
		setfattr( ebx, 0 )
		_rmdir ( ebx )
		pop	eax
	.endif
	ret
fp_remove_directory ENDP

cmdelete_remove PROC
	.if	cl & _A_SUBDIR
		remove_directory( eax )
	.else
		mov	errno,0
		remove_file( __spath, eax, ecx )
	.endif
	test	eax,eax
	ret
cmdelete_remove ENDP

	OPTION PROC: PUBLIC

cmdelete PROC USES ebx
	.switch
	  .case !cpanel_findfirst()
	  .case ecx & _FB_ROOTDIR
		xor	eax,eax
		.endc
	  .case ecx & _FB_ARCHEXT
		mov	eax,cpanel
		mov	eax,[eax].S_PANEL.pn_wsub
		warcdelete( eax, edx )
		xor	eax,eax
		.endc
	  .case ecx & _FB_ARCHZIP
		xor	eax,eax
		mov	ebx,edx
		open_progress()
		.repeat
			mov	eax,cpanel
			mov	eax,[eax].S_PANEL.pn_wsub
			mov	edx,ebx
			.break .if wzipdel()
			and	[ebx].S_FBLK.fb_flag,not _FB_SELECTED
			panel_findnext(cpanel)
			mov	ebx,edx
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

		.if !( ecx & _FB_SELECTED )

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
cmdelete ENDP

	END
