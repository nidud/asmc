; TRACE.ASM--
; Copyright (C) 2015 Doszip Developers

include errno.inc

systemerror PROTO _CType

	.code

trace	PROC _CType PUBLIC
	mov	ax,sys_ercode
	or	al,sys_erflag
	or	al,sys_erdrive
	test	ax,ax
	jnz	trace_err
    trace_end:
	ret
    trace_err:
	xor	ax,ax
	call	systemerror
	jmp	trace_end
trace	ENDP

	END
