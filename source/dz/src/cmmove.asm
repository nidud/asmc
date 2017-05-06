; CMMOVE.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include string.inc
include errno.inc
include consx.inc
include progress.inc

_COPY_IARCHIVE	equ 02h ; source is archive
_COPY_OARCHIVE	equ 04h ; target is archive
_COPY_IEXTFILE	equ 08h ; source is .DLL archive - %dz%/doc/plugins/.dll
_COPY_OEXTFILE	equ 40h ; target is .DLL archive

init_copy	PROTO :DWORD, :DWORD
fp_copydirectory PROTO :DWORD
fp_copyfile	PROTO :DWORD, :DWORD
copyfile	PROTO :QWORD, :DWORD, :DWORD
externdef	copy_jump:DWORD
externdef	copy_flag:BYTE
externdef	cp_move:BYTE

_COPY_TOZIP	equ 0004h
_COPY_TOARCHIVE equ _COPY_TOZIP

	.data

jmp_count dd 0

	.code

move_initfiles PROC PRIVATE filename

	strfcat(__outfile, __outpath, filename)
	strfcat(__srcfile, __srcpath, filename)
	ret

move_initfiles ENDP

move_deletefile PROC PRIVATE result, flag

	mov eax,result
	add eax,copy_jump
	.if eax

		mov eax,result
		.if !eax

			mov copy_jump,eax
			inc jmp_count
		.endif
	.else
		.if BYTE PTR flag & _A_RDONLY

			setfattr(__srcfile, 0)
		.endif
		remove(__srcfile)
		mov eax,result
	.endif
	ret

move_deletefile ENDP

fp_movedirectory PROC PRIVATE directory

	.if !progress_set(0, directory, 0)

		setfattr(directory, eax)
		.if _rmdir(directory)

			xor eax,eax
			.if jmp_count == eax

				erdelete(directory)
			.endif
		.endif
	.endif
	ret

fp_movedirectory ENDP

fp_movefile PROC PRIVATE directory, wfblk

	fp_copyfile(directory, wfblk)
	mov edx,wfblk
	move_deletefile(eax, [edx].S_WFBLK.wf_attrib)
	ret

fp_movefile ENDP

fblk_movefile PROC PRIVATE USES ebx fblk

	mov ebx,fblk
	.if !progress_set(addr [ebx].S_FBLK.fb_name, __outpath, [ebx].S_FBLK.fb_size)

		.if rename( __srcfile, __outfile )

			copyfile([ebx].S_FBLK.fb_size, [ebx].S_FBLK.fb_time, [ebx].S_FBLK.fb_flag)
			move_deletefile( eax, [ebx].S_FBLK.fb_flag )
		.endif
	.endif
	ret

fblk_movefile ENDP

fblk_movedirectory PROC PRIVATE USES esi edi fblk

  local path[512]:BYTE

	lea edi,path
	mov esi,fblk
	add esi,S_FBLK.fb_name

	.if !progress_set( esi, __outpath, 0 )

		move_initfiles(esi)
		.if rename(eax, __outfile)

			strfcat(edi, __srcpath, esi)
			mov fp_directory,fp_copydirectory
			.if scansub(edi, addr cp_stdmask, 1)

				mov eax,-1
			.else
				.if copy_jump == eax

					mov fp_directory,fp_movedirectory
					scansub(edi, addr cp_stdmask, 0)
				.else
					mov copy_jump,eax
					inc jmp_count
				.endif
			.endif
		.endif
	.endif
	ret
fblk_movedirectory ENDP

cmmove	PROC USES edi

	.if cpanel_findfirst()

		mov edi,edx

		.if ecx & (_FB_ARCHZIP or _FB_UPDIR)
			;
			; ...
			;
		.elseif init_copy( edi, 0 )

			.if !( copy_flag & _COPY_IARCHIVE or _COPY_OARCHIVE )

				mov jmp_count,0
				mov fp_fileblock,fp_movefile
				progress_open( addr cp_move, addr cp_move )

				mov eax,[edi]
				.if eax & _FB_SELECTED

					.while	1
						.if eax & _A_SUBDIR

							fblk_movedirectory(edi)
						.else
							mov eax,edi
							add eax,S_FBLK.fb_name
							move_initfiles(eax)
							fblk_movefile(edi)
						.endif
						.break .if eax
						mov eax,not _FB_SELECTED
						and [edi],eax
						.break .if !panel_findnext(cpanel)
						mov edi,edx
						mov eax,ecx
					.endw
				.else
					.if eax & _A_SUBDIR

						fblk_movedirectory(edi)
					.else
						fblk_movefile(edi)
					.endif
				.endif
				progress_close()
				mov eax,1
			.endif
		.endif
	.endif
	ret
cmmove	ENDP

	END
