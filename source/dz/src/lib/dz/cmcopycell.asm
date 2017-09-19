; CMCOPYCELL.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include string.inc
include io.inc

copyfile proto :qword, :dword, :dword

    .code

ccedit proc FASTCALL private uses esi edi ebx copy; rename or copy current file to a new name

    mov esi,copy

    .if panel_curobj(cpanel)

	mov edi,edx
	.if !(ecx & _FB_UPDIR or _FB_ROOTDIR)

	    .if ecx & _FB_ARCHIVE

		notsup()
	    .else

		strcpy(__srcfile, eax)
		strcpy(__outfile, eax)

		.if byte ptr [eax] != 0

		    mov eax,cpanel
		    mov eax,[eax].S_PANEL.pn_xl
		    sub ecx,ecx
		    mov cl,[eax].S_XCEL.xl_rect.rc_col
		    mov edx,[eax].S_XCEL.xl_rect
		    mov al,dh
		    scputw(edx, eax, ecx, 0720h)

		    .if dledit(__outfile, edx, _MAX_PATH-1, 0) != KEY_ESC

			.if strcmp(__outfile, __srcfile)

			    mov eax,__outfile
			    mov al,[eax]
			    .if al
				.if esi

				    mov eax,[edi]
				    .if !(eax & _FB_ARCHIVE)

					copyfile([edi].S_FBLK.fb_size,
					      [edi].S_FBLK.fb_time,
					      eax)
				    .endif
				.else
				    rename(__srcfile, __outfile)
				.endif
			    .endif
			.endif
		    .endif
		.endif
		mov eax,cpanel
		.if dlclose([eax].S_PANEL.pn_xl)

		    pcell_show(cpanel)
		.endif
		mov eax,1
	    .endif
	.else
	    xor eax,eax
	.endif
    .endif
    ret
ccedit	endp

cmcopycell proc
    ccedit(1)
    ret
cmcopycell endp

cmrename proc
    ccedit(0)
    ret
cmrename endp

    END
