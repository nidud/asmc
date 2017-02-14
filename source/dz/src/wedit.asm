; WEDIT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include tinfo.inc
include io.inc
include wsub.inc

	.code

wedit	PROC fcb, count

	.while	fbffirst( fcb, count )

		and	[eax].S_FBLK.fb_flag,not _FB_SELECTED
		.if	!( ecx & _FB_ARCHIVE or _A_SUBDIR )

			add	eax,S_FBLK.fb_name
			topen ( eax, 0 )
			.breakz
		.endif
	.endw

	panel_redraw(cpanel)
	xor	eax,eax
	call	tmodal
	ret

wedit	ENDP

	END
