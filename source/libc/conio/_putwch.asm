include conio.inc
include wchar.inc

	.code

_putwch proc wc

	;_mlock(_CONIO_LOCK)

	_putwch_nolock(wc)

	;_munlock(_CONIO_LOCK)

	ret

_putwch endp

_putwch_nolock proc wc

    local cchWritten

    .if _confh == -2
	__initconout()
    .endif

    .if _confh == -1
	mov eax,WEOF
    .else

	; write character to console file handle

	.if WriteConsoleW(_confh,
		       addr wc,
		       1,
		       addr cchWritten,
		       NULL)
	    mov eax,wc
	.else
	    mov eax,WEOF
	.endif
    .endif
    ret

_putwch_nolock endp

	END
