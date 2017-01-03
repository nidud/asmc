; MAIN.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include libc.inc

dzmain	PROTO _CType

.code

main	PROC c PUBLIC
	call	dzmain
	ret
main	ENDP

	END
