; CMMKDIR.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include errno.inc

externdef cp_mkdir:BYTE

	.code

cmmkdir PROC USES esi edi ebx
	local	path[512]:BYTE
	lea	ebx,path
	mov	eax,cpanel
	mov	esi,[eax].S_PANEL.pn_wsub
	mov	edi,[esi].S_WSUB.ws_flag
	.if !( edi & _W_ROOTDIR )
		.if panel_state()
			mov BYTE PTR [ebx],0
			.if tgetline( addr cp_mkdir, ebx, 40, 512 )
				xor eax,eax
				.if [ebx] != al
					.if edi & _W_ARCHZIP
						wsmkzipdir( esi, ebx )
					.elseif _mkdir( ebx )
						ermkdir( ebx )
					.endif
				.endif
			.endif
		.endif
	.endif
	ret
cmmkdir ENDP

	END
