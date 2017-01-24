; CMSAVESETUP.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include errno.inc

	.code

cmsavesetup PROC

	.if rsmodal( IDD_DZSaveSetup )

		.if !config_save()

			eropen( __srcfile )
			inc	eax
		.endif
	.endif
	ret

cmsavesetup ENDP

	END
