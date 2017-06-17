include string.inc
include fltintrn.inc

	.code

    OPTION PROLOGUE:NONE, EPILOGUE:NONE
;
; '#' and precision == 0 means force a decimal point
;
_forcdecpt proc buffer:LPSTR

	mov r10,rcx
	.if !strchr(r10, '.')
	    strcat(r10, ".0")
	.endif
	ret

_forcdecpt endp

	END
