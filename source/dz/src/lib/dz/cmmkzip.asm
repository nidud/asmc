; CMMKZIP.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include io.inc
include string.inc

	.data

default_zip db "default.zip"
	    db 128-11 dup(0)

	.code

cmmkzip PROC USES esi edi
local	path[_MAX_PATH]:BYTE

	lea edi,path

	.if cpanel_state()

		.if tgetline( addr cp_mkzip, strcpy( edi, addr default_zip ), 40, 256 or 8000h )

			.if BYTE PTR [edi]

				.ifs ogetouth(edi, M_WRONLY) > 0

					mov esi,eax
					strcpy(addr default_zip, edi)

					mov eax,cpanel
					mov edx,[eax].S_PANEL.pn_wsub
					mov eax,[edx].S_WSUB.ws_arch
					mov BYTE PTR [eax],0
					mov eax,[edx].S_WSUB.ws_flag
					and eax,not _W_ARCHIVE
					or  eax,_W_ARCHZIP
					mov [edx].S_WSUB.ws_flag,eax
					mov edx,[edx].S_WSUB.ws_file
					strcpy(edx, addr path)

					mov edx,edi
					mov eax,06054B50h
					stosd
					xor eax,eax
					mov ecx,5
					rep stosd

					oswrite(esi, edx, SIZE S_ZEND)
					_close(esi)
				.endif
			.endif
		.endif
	.endif
	ret

cmmkzip ENDP

	END
