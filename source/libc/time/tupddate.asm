include time.inc
include consx.inc

strsdate proto :LPSTR, :LPSYSTEMTIME

	.data
	_day dd 0
	.code

tupddate PROC USES edi
local	t:SYSTEMTIME
	test	console,CON_UDATE
	jz	@F
	sub	eax,eax
	mov	ecx,SIZE SYSTEMTIME/4
	lea	edi,t
	rep	stosd
	GetLocalTime( addr t )
	movzx	eax,t.wDay
	cmp	_day,eax
	je	@F
	mov	_day,eax
	strsdate( addr t, addr t )
	mov	ecx,_scrcol
	sub	ecx,19
	scputs( ecx, 0, 0, 0, eax )
@@:
	ret
tupddate ENDP

	END
