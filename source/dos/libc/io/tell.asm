; TELL.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc

	.code

tell	PROC _CType PUBLIC handle:size_t
	invoke lseek,handle,0,SEEK_SET
	ret
tell	ENDP

	END
