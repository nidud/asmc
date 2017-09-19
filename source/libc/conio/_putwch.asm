include conio.inc
include wchar.inc

	.code

_putwch proc wc
_putwch endp

_putwch_nolock proc wc

    local cchWritten

    .if _confh == -2
	__initconout()
    .endif

    .if _confh == -1
	mov eax,WEOF
    .else
	;
	; write character to console file handle
	;
	.if WriteConsoleW(_confh, &wc, 1, &cchWritten, NULL)
	    mov eax,wc
	.else
	    mov eax,WEOF
	.endif
    .endif
    ret

_putwch_nolock endp

    end
