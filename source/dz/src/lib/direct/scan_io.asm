include direct.inc
include io.inc
include string.inc
include alloc.inc
include wsub.inc
include crtl.inc

PUBLIC	fp_maskp
PUBLIC	fp_directory
PUBLIC	fp_fileblock
PUBLIC	scan_fblock

ATTRIB_ALL	equ 0B7h ;37h
ATTRIB_FILE	equ 0F7h ;27h

.data

fp_maskp	LPSTR 0
fp_directory	LPSTR 0
fp_fileblock	LPSTR 0
scan_fblock	dd 0
scan_curpath	dd 0
scan_curfile	dd 0

.code

scan_directory PROC USES esi edi ebx flag:UINT, directory:LPSTR
local	result

	xor eax,eax
	mov result,eax

	mov edi,scan_fblock
	.if BYTE PTR flag & 1

		push directory
		call fp_directory
		mov  result,eax
	.endif

	.if !eax

		add strlen(directory),scan_curpath
		mov ebx,eax

		.if wsfindfirst(strfcat(scan_curpath, directory, addr cp_stdmask),
			edi, ATTRIB_ALL) != -1

			mov esi,eax

			.if !wsfindnext( edi, esi )

				.while !wsfindnext( edi, esi )

					.continue .if !( BYTE PTR [edi].WIN32_FIND_DATA.dwFileAttributes & _A_SUBDIR )
					strcpy( addr [ebx+1],
						addr [edi].WIN32_FIND_DATA.cFileName )
					scan_directory( flag, scan_curpath )
					mov result,eax

					.break .if eax
				.endw
			.endif

			wscloseff( esi )
			mov BYTE PTR [ebx],0
		.endif

		mov eax,result
		.if !eax && !( BYTE PTR flag & 1 )

			push directory
			call fp_directory
		.endif
	.endif
	ret

scan_directory ENDP

scan_files PROC USES esi edi ebx directory:LPSTR

	xor edi,edi
	mov ebx,scan_fblock

	.if wsfindfirst( strfcat( scan_curfile, directory, fp_maskp ), ebx, ATTRIB_FILE ) != -1

		mov esi,eax

		.repeat
			.if !( BYTE PTR [ebx] & _A_SUBDIR )

				push ebx
				push directory
				call fp_fileblock
				mov  edi,eax

				.break .if eax
			.endif

		.until	wsfindnext( ebx, esi )

		wscloseff( esi )
	.endif

	mov	eax,edi
	ret

scan_files ENDP


scansub PROC directory:LPSTR, smask:LPSTR, sflag:UINT

	mov eax,smask
	mov fp_maskp,eax

	scan_directory( sflag, directory )
	ret

scansub ENDP

Install:
	mov scan_fblock,malloc( sizeof( WIN32_FIND_DATA ) + 2 * WMAXPATH )
	add eax,sizeof(WIN32_FIND_DATA)
	mov scan_curfile,eax
	add eax,WMAXPATH
	mov scan_curpath,eax
	ret

pragma_init Install,40

	END
